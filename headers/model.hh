#include <list>
#include "./view.hh"

const point direction_arr[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; //up down left right

class snake
{
    private:
        std::list<point *> points; 
        int size_x, size_y;
        int direction = 2;

    public:

    snake(int n, int x, int y): size_x(x), size_y(y)
    {  
        int x_temp = x / 2;
        int y_temp = y / 2;

        for(int i = 0; i < n; ++i)
        {
            point * temp_point = new point(x_temp + i, y_temp);
            points.push_front(temp_point);
        }
    };


    const std::list<point *> & get_state()
    {
        point * last = points.back();
        points.pop_back();
        delete last;

        point * prev = points.front();
        point * temp = new point;

        temp->x = prev->x;
        temp->y = prev->y;
        points.push_front(temp);
        *temp += direction_arr[direction];

        return points;
    }
};