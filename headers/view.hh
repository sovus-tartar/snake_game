#pragma once

class view
{
    int x, y;

public:
    virtual void draw() = 0;

    //view();
    virtual ~view();

    static view * get();
};