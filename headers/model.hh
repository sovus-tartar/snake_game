#include <list>
#include "./view.hh"

const point direction_arr[5] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {0, 0}}; // up down left right 0

class snake
{
private:
    std::list<point *> points;
    int size_x, size_y;
    int direction = 2;

public:
    ~snake()
    {
        for (auto it = points.begin(); it != points.end(); ++it)
            delete *it;
    }

    snake(int n, int x, int y) : size_x(x), size_y(y)
    {
        int x_temp = x / 2;
        int y_temp = y / 2;

        for (int i = 0; i < n; ++i)
        {
            point *temp_point = new point(x_temp + i, y_temp);
            points.push_front(temp_point);
        }
    };

    void change_direction(const int d)
    {
        direction = d;
    }

    void update_state()
    {
        point *last = points.back();
        points.pop_back();
        delete last;

        point *prev = points.front();
        point *temp = new point;

        temp->x = prev->x;
        temp->y = prev->y;
        points.push_front(temp);
        *temp += direction_arr[direction];

        
        if ((temp->x == size_x) || (temp->x == 0) || (temp->y == size_y) || (temp->y == 0))
        {
            throw -1;
        }
    }

    const std::list<point *> &get_state()
    {
        return points;
    }

    void move(char d)
    {
        int dir = 0;
        switch (d)
        {
        case 'w':
            dir = 2;
            break;

        case 'a':
            dir = 0;
            break;

        case 's':
            dir = 3;
            break;

        case 'd':
            dir = 1;
            break;
        }

        change_direction(dir);
    }
};


class rabbit
{
    public:

    void move()
    {

    }

    void change_direction(const int d)
    {
        direction = d;
    }

    private:

    int direction = 0;
};