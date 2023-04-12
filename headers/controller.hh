#include <unordered_map>
#include <list>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/uio.h>
#include <unistd.h>
#include <poll.h>
#include <functional>

class keyboard_ctrl
{
    using action = std::function<void (int)>;

private:
    std::list<char> used_button_list;
    std::unordered_map<char, std::list<action> *> buttons;

    void do_actions(char c);

    int get_time()
    {
        struct timeval tp;

        gettimeofday(&tp, NULL);

        return (tp.tv_sec * 1000000 + tp.tv_usec);
    }

public:
    keyboard_ctrl() {};

    void setonkey(action func, char c);

    int poll_keyboard(); //returns time of polling and doing actions


    ~keyboard_ctrl()
    {
        for (auto it = used_button_list.begin(); it != used_button_list.end(); ++it)
            delete buttons.find(*it)->second;
    };
};