#include "view.hh"
#include <termios.h>
#include <sys/ioctl.h>
#include <list>

class text_vi : public view
{
public:
    virtual void draw();
    static point getsz();
    text_vi();
    void clean();
    

private:
    virtual ~text_vi();
    void put_xy(int x, int y, char *str);
    void put_xy(int x, int y, char c);
    void put_xy(point p, char c);
    void hline(int n, char c);
    void vline(int n, char c);
    void chcolor(int fg, int bg);
    void draw_list(const std::list<point*> & list);

};