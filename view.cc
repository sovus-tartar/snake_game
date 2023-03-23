#include "./headers/view.hh"
#include <termios.h>
#include <string.h>


view::~view()
{
    delete this;
}