#include <iostream>
#include <string.h>

int main(int argc, char ** argv)
{
    if(argc < 2)
    {
        std::cout << "Too few arguments, exiting...\n";
        return -1;
    }  

    if(!strcmp(argv[2], "text"))
    {
        
    }
    else if (!strcmp(argv[2], "gui"))
    {

    }
    else
    {
        std::cout << "Wrong arguments, aborting...\n";
        return -1;
    }

}