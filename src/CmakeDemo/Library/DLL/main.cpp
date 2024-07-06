#include <iostream>

#include "class.h"

int main(int argc, char *argv[])
{
    Box box1;
    box1.Vist();
    double volume1 = box1.GetBoxVolume_inline();
    volume1 = box1.GetBoxVolume_virtual();
    Box::GetBoxCount_static();
    Visit_friend(box1);

    SmallBox box2;
    box2.Vist();
    double volume2 = box2.GetBoxVolume_inline();
    volume2 = box2.GetBoxVolume_virtual();
    SmallBox::GetBoxCount_static();

    // 多态测试
    // 当子类与基类中的函数同名，则基类中的函数被隐藏，具体分为以下两类
    // 1. 参数不同，此时无论是否有关键字 virtual，基类中的函数均被隐藏（不同于重载，重载发生在类内）
    // 2. 参数相同，无关键字 virtual，基类中的函数被隐藏（不同于覆盖，覆盖有关键字 virtual）
    Box *pointer_base = &box2;         // 基类类型指针，指向子类对象
    SmallBox *pointer_derived = &box2; // 子类类型指针，指向子类对象

    pointer_base->GetBoxVolume_virtual();    // 调用子类方法，多态性
    pointer_derived->GetBoxVolume_virtual(); //调用自己的方法

    return 0;
}