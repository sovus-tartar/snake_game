#include "view.hh"
#include <termios.h>
#include <sys/ioctl.h>
#include <list>

class text_vi : public view
{
public:
    virtual void draw();
    static point get_sz();
    text_vi();
    void clean();
    

private:
    struct termios terminal_state;
    int run_state = 1;

    virtual ~text_vi();
    void put_xy(int x, int y, char *str);
    void put_xy(int x, int y, char c);
    void put_xy(point p, char c);
    void hline(int n, char c);
    void vline(int n, char c);
    void chcolor(int fg, int bg);
    void draw_list(const std::list<point*> & list);
    void draw_frame();
    void update_sz();
    void stop_game()
    {
        run_state = 0;
    }
};