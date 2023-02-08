#include <string.h>

#include "view_fabric.hh"

view* view_fabric::obj_ptr = nullptr;

view *view_fabric::get(char *mode)
{
    if(mode == NULL)
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
