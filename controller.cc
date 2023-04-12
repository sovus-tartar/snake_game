#include "./headers/controller.hh"



    void keyboard_ctrl::do_actions(char c)
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

        void keyboard_ctrl::setonkey(action func, char c)
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

        int keyboard_ctrl::poll_keyboard() //returns time of polling and doing actions
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