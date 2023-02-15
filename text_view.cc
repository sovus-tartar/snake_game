#include "./headers/text_view.hh"

#include <iostream>

void text_vi::draw()
{
    std::cout << "Hello, it's text\n";
}

text_vi::~text_vi()
{
    delete this;
}
//need size, coordinates
//printf-like interface
//nline, vline, line
//cls
//