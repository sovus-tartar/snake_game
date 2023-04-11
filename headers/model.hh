#include <list>
#include <algorithm>
#include <unordered_map>
#include <algorithm>
#include "./view.hh"

const point direction_arr[5] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {0, 0}}; // up down left right 0

struct character
{
    int size_x, size_y;

    void update_size(int x, int y)
    {
        size_x = x, size_y = y;
    }
};

class snake : public character
{
private:
    std::list<point> points;

    int direction = 2;

    int check_for_intersection()
    {
        point head = points.front();

        auto it = points.begin();
        ++it;

        for (it; it != points.end(); ++it)
        {
            if (head == (*it))
                return 1;
        }

        return 0;
    }

public:
    ~snake()
    {
    }

    void check_for_rabbits(const std::list<point> rabbits)
    {
        int collision = 0;
        for (auto it = rabbits.begin(); it != rabbits.end(); ++it)
        {
            if (*it == points.front())
            {
                collision = 1;
            }
        }

        if (collision == 0)
        {
            points.pop_back();
        }
        if (collision == 1)
            throw points.front();
    }

    snake(int n, int x, int y)
    {
        update_size(x, y);
        int x_temp = x / 2;
        int y_temp = y / 2;

        for (int i = 0; i < n; ++i)
        {
            points.emplace_front(point(x_temp + i, y_temp));
        }
    };

    void change_direction(const int d)
    {
        direction = d;
    }

    void update_state()
    {
        point temp = points.front() + direction_arr[direction];

        points.push_front(temp);

        if ((temp.x == size_x) || (temp.x == 0) || (temp.y == size_y) || (temp.y == 0) || check_for_intersection())
        {
            throw point(-1, -1);
        }
    }

    const std::list<point> &get_state()
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

class rabbit : public character, public point
{
public:
    rabbit(int sz_x, int sz_y, int x_, int y_)
    {
        size_x = sz_x;
        size_y = sz_y;
        x = x_;
        y = y_;
    }

    void move()
    {
        (struct point)(*this) += direction_arr[direction];
    }

    void change_direction(const int d)
    {
        direction = d;
    }

private:
    int direction = 4;
};

class flock_rabbits : public character
{
public:
    flock_rabbits(int n_, int size_x_, int size_y_) : n(n_)
    {
        size_x = size_x_, size_y = size_y_;

        std::srand(std::time(nullptr));

        for (int i = 0; i < n; ++i)
        {
            int x_rand = 1 + std::rand() % (size_x - 1);
            int y_rand = 1 + std::rand() % (size_y - 1);
            rabbit temp(size_x, size_y, x_rand, y_rand);

            rabbits.push_front(temp);
        }
    }

    const std::list<point> get_state()
    {
        std::list<point> temp;

        for (auto it = rabbits.begin(); it != rabbits.end(); ++it)
            temp.emplace_back(*it);

        return temp;
    }

    void kill(const point& rabbit)
    {
        rabbits.erase(std::find(rabbits.begin(), rabbits.end(), rabbit));
    }

    int collide(int x_, int y_)
    {
        point temp = {x_, y_};

        auto it = rabbits.begin();
        for (it = rabbits.begin(); it != rabbits.end(); ++it)
        {
            if (*it == temp)
                break;
        }

        if (it == rabbits.end())
            return 0;

        rabbits.erase(it);
        return 1;
    }

private:
    int n;
    std::list<rabbit> rabbits;
};