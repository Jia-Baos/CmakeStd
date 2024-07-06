#include "class.h"

// 初始化类 Box 的静态成员
int Box::BoxCount = 0;

Box::Box()
{
    std::cout << "Base, init the paprameter~" << std::endl;
    length = 10;
    breadth = 20;
    height = 30;
    price = 100;
    BoxCount++;
}

Box::~Box()
{
    std::cout << "Base, destory the instance of Box~" << std::endl;
}

void Box::Vist() const
{
    // 在 C++ 中，每一个对象都能通过 this 指针来访问自己的地址
    // this 指针是所有成员函数的隐含参数。因此，在成员函数内部，它可以用来指向调用对象。
    std::cout << "Base, box's lenght: " << this->length << std::endl;
    std::cout << "Base, box's breadth: " << this->breadth << std::endl;
    std::cout << "Base, box's height: " << this->height << std::endl;
}

void Visit_friend(const Box &box)
{
    std::cout << "Base, box's lenght: " << box.length << std::endl;
    std::cout << "Base, box's breadth: " << box.breadth << std::endl;
    std::cout << "Base, box's height: " << box.height << std::endl;
}

int Box::GetBoxCount_static()
{
    std::cout << "Base, box's num: " << BoxCount << std::endl;
    return BoxCount;
}

double Box::GetBoxVolume_virtual()
{
    double volume = length * breadth * height;
    std::cout << "Base, box's volume: " << volume << std::endl;
    return volume;
}

double SmallBox::GetBoxVolume_virtual()
{
    double volume = length * breadth * height;
    std::cout << "Derived, box's volume: " << volume << std::endl;
    return volume;
}

SmallBox::SmallBox()
{
    std::cout << "Derived, init the paprameter~" << std::endl;
    length = 20;
    breadth = 40;
    height = 60;
    this->BoxCount++;
}

SmallBox::~SmallBox()
{
    std::cout << "Derived, destory the instance of Box~" << std::endl;
}