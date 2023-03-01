#include <string.h>
#include <iostream>


#include "./headers/view_fabric.hh"

view * view_fabric::obj_ptr = nullptr;

view * view_fabric::get(char *mode)
{
    std::cout << "view_fabric in get\n";
    
    if(mode == nullptr)
        return obj_ptr;

    if (obj_ptr == nullptr)
    {
        if (!strcmp(mode, "text"))
        {
           obj_ptr = new text_vi(); 
        }
        else if (!strcmp(mode, "gui"))
        {
            obj_ptr = new graph_vi();
        }
    }

    return obj_ptr;
}
