#include "view.hh"
#include "text_view.hh"
#include "graph_view.hh"

class view_fabric
{
    static view* obj_ptr;

    public:
        static view* get(char * mode = NULL);
};