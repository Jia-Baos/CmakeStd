#include <iostream>

inline int Max(int x, int y)
{
    return (x > y) ? x : y;
}

class Box
{
private:
    // 私有成员变量或函数在类的外部是不可访问的，甚至是不可查看的，
    // 只有类和友元函数可以访问私有成员，默认情况下，类的所有成员都是私有的。
    double price;

protected:
    // 保护成员变量或函数与私有成员十分相似，
    //但有一点不同，保护成员在派生类（即子类）中是可访问的。
    double length;  // 盒子的长度
    double breadth; // 盒子的宽度
    double height;  // 盒子的高度

public:
    static int BoxCount;                      // 静态成员变量，实例化对象计数
    Box();                                    // 构造函数
    virtual ~Box();                           // 析构函数
    void Vist() const;                        // const，访问Box的参数
    // 若此处使用传值的方式，则会多调用一次析构函数
    friend void Visit_friend(const Box &box); // 友元函数，不可被子类继承，访问Box的参数

    // 静态成员函数没有 this 指针，只能访问静态成员（包括静态成员变量和静态成员函数)
    static int GetBoxCount_static();    // 静态成员函数，实例化对象的个数
    inline double GetBoxVolume_inline() // 内联函数，盒子的体积
    {
        double volume = length * breadth * height;
        std::cout << "Base, box's volume: " << volume << std::endl;
        return volume;
    }
    virtual double GetBoxVolume_virtual(); // 虚函数，盒子的体积
};

class SmallBox : public Box
{
public:
    SmallBox();                            // 构造函数
    virtual ~SmallBox();                   // 析构函数
    virtual double GetBoxVolume_virtual(); // 盒子的体积
};