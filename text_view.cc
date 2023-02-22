#include "./headers/text_view.hh"
#include <sys/ioctl.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <cstdlib>


//x вниз y вправо
void text_vi::draw()
{
    std::cout << "Hello, it's text\n";

    printf("x = %d y = %d \n", x, y);
    sleep(1);
    for(int i = 0; 1; ++i)
    {
        clean();
        vline(1, '#');
        vline(x, '#');
        hline(1, '#');
        hline(y, '#');
        usleep(15000);
    }
    // draw frame
    // while(1)...
}

void text_vi::clean()
{
    puts("\e[H");
    puts("\e[2J");
}

void text_vi::chcolor(int fg, int bg)
{
}

void text_vi::put_xy(int x, int y, char *str)
{
    printf("\e[%d;%dH", x, y);
    puts(str);
    puts("\e[H");
}

void text_vi::put_xy(int x, int y, char c)
{
    printf("\e[%d;%dH", y, x);
    putchar(c);
    puts("\e[H");
}

void text_vi::vline(int n, char c)
{
    for (int i = 0; i < y; ++i)
    {
        put_xy(n, i, c);
    }
}

void text_vi::hline(int n, char c)
{
    for (int i = 0; i < x; ++i)
    {
        put_xy(i, n, c);
    }
}

point text_vi::getsz()
{
    struct winsize temp;
    ioctl(0, TIOCGWINSZ, &temp);
    struct point sz = {temp.ws_col, temp.ws_row};

    return sz;
}

text_vi::text_vi()
{
    struct point temp = getsz();

    x = temp.x;
    y = temp.y;
}

text_vi::~text_vi()
{
    delete this;
}
// need size, coordinates
// printf-like interface
// nline, vline, line
// cls
//