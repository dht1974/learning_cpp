/*
    Copyright (c) 2007-2016 Contributors as noted in the AUTHORS file

    This file is part of libzmq, the ZeroMQ core engine in C++.

    libzmq is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    As a special exception, the Contributors give you permission to link
    this library with independent modules to produce an executable,
    regardless of the license terms of these independent modules, and to
    copy and distribute the resulting executable under terms of your choice,
    provided that you also meet, for each linked independent module, the
    terms and conditions of the license of that module. An independent
    module is a module which is not derived from or based on this library.
    If you modify this library, you must extend this exception to your
    version of the library.

    libzmq is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
    License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __ZMQ_ATOMIC_PTR_HPP_INCLUDED__
#define __ZMQ_ATOMIC_PTR_HPP_INCLUDED__

#include <atomic>

namespace zmq
{

//  This class encapsulates several atomic operations on pointers.

template <typename T> class atomic_ptr_t
{
  public:
    //  Initialise atomic pointer
    inline atomic_ptr_t () noexcept { _ptr = nullptr; }

    //  Set value of atomic pointer in a non-threadsafe way
    //  Use this function only when you are sure that at most one
    //  thread is accessing the pointer at the moment.
    inline void set (T *ptr_) noexcept { _ptr = ptr_; }

    //  Perform atomic 'exchange pointers' operation. Pointer is set
    //  to the 'val_' value. Old value is returned.
    inline T *xchg (T *val_) noexcept
    {
        return _ptr.exchange (val_, std::memory_order_acq_rel);
    }

    //  Perform atomic 'compare and swap' operation on the pointer.
    //  The pointer is compared to 'cmp' argument and if they are
    //  equal, its value is set to 'val_'. Old value of the pointer
    //  is returned.
    inline T *cas (T *cmp_, T *val_) noexcept
    {
        _ptr.compare_exchange_strong (cmp_, val_, std::memory_order_acq_rel);
        return cmp_;
    }

  private:
    std::atomic<T *> _ptr;
};

struct atomic_value_t
{
    atomic_value_t (const int value_) noexcept : _value (value_) {}

    atomic_value_t (const atomic_value_t &src_) noexcept
        : _value (src_.load ())
    {
    }

    void store (const int value_) noexcept
    {
        _value.store (value_, std::memory_order_release);
    }

    int load () const noexcept
    {
        return _value.load (std::memory_order_acquire);
    }

  private:
    std::atomic<int> _value;

  private:
    atomic_value_t &operator= (const atomic_value_t &src_);
};
}

#endif
