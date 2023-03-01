#pragma once

struct point
{
    public:
    int x, y;

    point(): x(0), y(0) {};
    point(int x_, int y_): x(x_), y(y_) {};

    point operator +=(point p2)
    {
        x += p2.x;
        y += p2.y;

        return *this;
    };
};

class view
{
public:
    int x, y;
    
    virtual void draw() = 0;

    //view();
    virtual ~view();

};