#include <iostream>
#include <string.h>

#include "./headers/view_fabric.hh"

int main(int argc, char ** argv)
{
    if(argc < 2)
    {
        std::cout << "Too few arguments, exiting...\n";
        return -1;
    }  

    view * temp = view_fabric::get(argv[1]);

    temp->draw();
    
    //delete temp;
}