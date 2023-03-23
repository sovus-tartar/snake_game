#include "./headers/text_view.hh"
#include "./headers/model.hh"
#include "./headers/controller.hh"
#include <sys/ioctl.h>
#include <functional>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <cstdlib>
#include <iterator>
#include <termios.h>
#include <unistd.h>
#include <assert.h>

//x вправо y вниз
void text_vi::draw()
{

    std::cout << "Hello, it's text\n";
    snake S(10, x, y);
    controller ctrl;

    auto change_snake_dir = std::bind(&snake::snake_move, &S, std::placeholders::_1);
    auto quit_f = std::bind(&text_vi::stop_game, this);
    ctrl.setonkey(change_snake_dir, 'w');
    ctrl.setonkey(change_snake_dir, 'a');
    ctrl.setonkey(change_snake_dir, 's');
    ctrl.setonkey(change_snake_dir, 'd');
    ctrl.setonkey(quit_f, 'q');

    printf("x = %d y = %d \n", x, y);
    sleep(1);
    while(run_state)
    {
        
        clean();
        update_sz();
        draw_frame();

        ctrl.poll_keyboard();
        
        const std::list<point*> &temp = S.get_state();
        draw_list(temp);
        
        usleep(500000);
    }
    
}

void text_vi::draw_frame()
{
    vline(1, '|');
    vline(x, '|');
    hline(1, '-');
    hline(y, '-');
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
void text_vi::put_xy(point p, char c)
{
    printf("\e[%d;%dH", p.y, p.x);
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

point text_vi::get_sz()
{
    struct winsize temp;
    ioctl(0, TIOCGWINSZ, &temp);
    struct point sz = {temp.ws_col, temp.ws_row};

    return sz;
}

void text_vi::update_sz()
{
    struct point temp = get_sz();

    x = temp.x;
    y = temp.y;
}

text_vi::text_vi()
{
    update_sz();

    tcgetattr(1, &terminal_state);
    struct termios temp_terminal = terminal_state;

    cfmakeraw(&temp_terminal);
    tcsetattr(1, TCSANOW, &temp_terminal);


}

void text_vi::draw_list(const std::list<point*> & list)
{
    for(auto it = list.begin(); it != list.end(); ++it)
    {
        put_xy(**it, 's');
    }

    
}



text_vi::~text_vi()
{
    tcsetattr(1, TCSANOW, &terminal_state);
}
