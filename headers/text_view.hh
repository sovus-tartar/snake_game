#include "view.hh"
#include <termios.h>
#include <sys/ioctl.h>

class text_vi : public view
{
public:
    virtual void draw();
    static point getsz();
    text_vi();
    void clean();
    void put_xy(int x, int y, char *str);
    void put_xy(int x, int y, char c);
    void hline(int n, char c);
    void vline(int n, char c);
    void chcolor(int fg, int bg);

private:
    virtual ~text_vi();
};