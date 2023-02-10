#include <iostream>
#include <string>

/*
将若干功能独立的类通过继承的方式实现模块复用的C++模板编程技巧。
其基本做法是将模板参数作为派生类的基类

应用：
std::nested_exception
*/

template <typename... Mixins>
class Point : public Mixins... 
{
public:
    double x, y;
    Point () : Mixins ()..., x (0.0), y (0.0) {}
    Point (double x, double y) : Mixins ()..., x (x), y (y) {}
};

class Label 
{
public:
    std::string label;
    Label () : label ("") {}
};

class Color 
{
public:
    uint8_t red {0}; 
    uint8_t green {0}; 
    uint8_t blue {0};
};

class Transparent
{
public:
    int percent {0};
};

using MyPoint = Point<Label, Color, Transparent>;

int
main ()
{
    MyPoint p (3, 3);
    p.label = "ppp1";
    p.red = 100;
    p.green = 5;
    p.blue = 50;
    p.percent = 50;
}
