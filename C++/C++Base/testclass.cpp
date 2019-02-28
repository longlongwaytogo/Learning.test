#include <iostream>
using namespace std;

//声明抽象基类Shape
class Shape
{
public:
    virtual float area()const //虚函数
    {
        return 0.0;
    }


    virtual void shapeName()const  = 0;//纯虚函数
    //shapeNamea函数的作用是输出具体的形状，在派生类中定义，因此声明为纯虚函数
};

//声明Point类
class Point:public Shape
{
public:
    Point(float a = 0.0, float b = 0.0)
    {
        x = a;
        y = b;
    }

    void setPoint(float a, float b)
    {
        x = a;
        y = b;
    }

    float getX()const
    {
        return x;
    }

    float getY()const
    {
        return y;
    }

    virtual void shapeName()const
    {
        cout<<"Point:";
    }

    friend ostream & operator <<(ostream &_cout, const Point &p)
    {
        _cout<<"["<<p.x<<","<<p.y<<"]";
        return _cout;
    }

protected:
    float x;
    float y;
};

//声明Ciircle类
class Circle:public Point
{
public:
    Circle(float a = 0.0, float b = 0.0, float r = 0.0)
        :Point(a, b)
        ,radius(r)
    {}

    void setRadius(float r)

    {
        radius = r;
    }

    float getRadius()const
    {
        return radius;
    }

    virtual float area()const
    {
        return 3.1415926*radius*radius;
    }

    virtual void shapeName()const
    {
        cout<<"Circle:";
    }

    friend ostream & operator <<(ostream &_cout, const Circle &c)
    {
        _cout<<"["<<c.x<<","<<c.y<<"],r="<<c.radius;
        return _cout;
    }

protected:
    float radius;
};

int main()
{
    Point point(3.2, 4.5);  // 建立Point类对象point
    Circle circle(2.4, 1.2, 5.6);  //建立Circle类对象circle

    point.shapeName();        //静态关联
    cout<<point<<endl;

    circle.shapeName();       //静态关联
    cout<<circle<<endl;

    Shape* pt;    //定义基类指针
    pt = &point;
    pt->shapeName();
    cout<<"x="<<point.getX()<<",y="<<point.getY()<<endl;
    cout<<"area="<<pt->area()<<endl;

    pt = &circle;    //指针指向Circle类对象
    pt->shapeName();   //动态关联
    cout<<"x="<<circle.getX()<<",y="<<circle.getY()<<endl;
    cout<<"area="<<pt->area()<<endl;

    system("pause");
    return 0;
}