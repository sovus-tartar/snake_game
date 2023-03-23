#include <unordered_map>
#include <list>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/uio.h>
#include <unistd.h>
#include <poll.h>
#include <functional>

class controller
{
    using action = std::function<void (int)>;

private:
    std::list<char> used_button_list;
    std::unordered_map<char, std::list<action> *> buttons;

    void do_actions(char c)
    {
        auto it = buttons.find(c);

        if(it != buttons.end())
        {
            for(auto list_it = it->second->begin(); list_it != it->second->end(); ++list_it)
            {
                action temp = *list_it;
                temp(c);
            }
            
        }
    }

    int get_time()
    {
        struct timeval tp;

        gettimeofday(&tp, NULL);

        return (tp.tv_sec * 1000000 + tp.tv_usec);
    }

public:
    controller() {};

    void setonkey(action func, char c)
    {
        auto it = buttons.find(c);

        if (it == buttons.end()) // if no such list
        {
            used_button_list.push_back(c);
            std::list<action> *temp_list = new std::list<action>;
            temp_list->push_back(func);
            buttons[c] = temp_list;
        }
        else
        {
            it->second->push_back(func);
        }
    };

    int poll_keyboard() //returns time of polling and doing actions
    {
        char c[4097], temp;
        struct pollfd keyb = {0, POLLIN, 0};
        int bytes_read = 0;
        
        int time = get_time();

        while (poll(&keyb, 1, 0) == 1)
        {
            bytes_read = read(0, c, 4096);

            for(int i = 0; i < bytes_read; ++i)
                do_actions(c[i]);
        }

        return (time -= get_time());
    };

    ~controller()
    {
        for (auto it = used_button_list.begin(); it != used_button_list.end(); ++it)
            delete buttons.find(*it)->second;
    };
};