#pragma once

struct point
{
    public:
    int x, y;
};

class view
{
public:
    int x, y;
    
    virtual void draw() = 0;

    //view();
    virtual ~view();

    static view * get();
};