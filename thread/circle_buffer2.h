/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// @author Bo Hu (bhu@fb.com)
// @author Jordan DeLong (delong.j@fb.com)

#pragma once

#include <atomic>
#include <cassert>
#include <cstdlib>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>


#define mb()  asm volatile("mfence":::"memory")
#define rmb() asm volatile("lfence":::"memory")
#define wmb() asm volatile("sfence" ::: "memory")


namespace folly {

/*
 * circle_buffer2 is a one producer and one consumer queue
 * without locks.
 */
template <class T>
struct circle_buffer2 {
  typedef T value_type;

  circle_buffer2(const circle_buffer2&) = delete;
  circle_buffer2& operator=(const circle_buffer2&) = delete;

  // size must be >= 2.
  //
  // Also, note that the number of usable slots in the queue at any
  // given time is actually (size-1), so if you start with an empty queue,
  // isFull() will return true after size-1 insertions.
  explicit circle_buffer2(uint32_t size)
      : size_(size),
        records_(static_cast<T*>(std::malloc(sizeof(T) * size))),
        readIndex_(0),
        writeIndex_(0) {
    assert(size >= 2);
    if (!records_) {
      throw std::bad_alloc();
    }
  }

  ~circle_buffer2() {
    // We need to destruct anything that may still exist in our queue.
    // (No real synchronization needed at destructor time: only one
    // thread can be doing this.)
    if (!std::is_trivially_destructible<T>::value) {
      size_t readIndex = readIndex_;
      size_t endIndex = writeIndex_;
      while (readIndex != endIndex) {
        records_[readIndex].~T();
        if (++readIndex == size_) {
          readIndex = 0;
        }
      }
    }

    std::free(records_);
  }

  template <class... Args>
  bool write(Args&&... recordArgs) {
    auto const currentWrite = writeIndex_;
    auto nextRecord = currentWrite + 1;
    if (nextRecord == size_) {
      nextRecord = 0;
    }
    if (nextRecord != readIndex_) {
      new (&records_[currentWrite]) T(std::forward<Args>(recordArgs)...);
      writeIndex_ = nextRecord;
      /// wmb ();
      return true;
    }

    // queue is full
    return false;
  }

  // move (or copy) the value at the front of the queue to given variable
  bool read(T& record) {
    auto const currentRead = readIndex_;
    if (currentRead == writeIndex_) {
      // queue is empty
      return false;
    }

    auto nextRecord = currentRead + 1;
    if (nextRecord == size_) {
      nextRecord = 0;
    }
    record = std::move(records_[currentRead]);
    records_[currentRead].~T();
    readIndex_ = nextRecord;
    /// rmb ();
    return true;
  }

  // pointer to the value at the front of the queue (for use in-place) or
  // nullptr if empty.
  T* frontPtr() {
    auto const currentRead = readIndex_;
    if (currentRead == writeIndex_) {
      // queue is empty
      return nullptr;
    }
    return &records_[currentRead];
  }

  // queue must not be empty
  void popFront() {
    auto const currentRead = readIndex_;
    assert(currentRead != writeIndex_);

    auto nextRecord = currentRead + 1;
    if (nextRecord == size_) {
      nextRecord = 0;
    }
    records_[currentRead].~T();
    readIndex_ = nextRecord;

  }

  bool isEmpty() const {
      wmb ();
    return readIndex_ == writeIndex_;
  }

  bool isFull() const {
    wmb ();
    auto nextRecord = writeIndex_ + 1;
    if (nextRecord == size_) {
      nextRecord = 0;
    }
    if (nextRecord != readIndex_) {
      return false;
    }
    // queue is full
    return true;
  } 

  // * If called by consumer, then true size may be more (because producer may
  //   be adding items concurrently).
  // * If called by producer, then true size may be less (because consumer may
  //   be removing items concurrently).
  // * It is undefined to call this from any other thread.
  size_t sizeGuess() const {
    int ret = writeIndex_ - readIndex_;
    if (ret < 0) {
      ret += size_;
    }
    return ret;
  }

  // maximum number of items in the queue.
  size_t capacity() const { return size_ - 1; }

 private:
  /// using AtomicIndex = std::atomic<unsigned int>;
  using AtomicIndex = uint32_t;
  char pad0_[64];
  const uint32_t size_;
  T* const records_;

  alignas(64) AtomicIndex readIndex_;
  alignas(64) AtomicIndex writeIndex_;

  char pad1_[64 - sizeof(AtomicIndex)];
};

} // namespace folly
