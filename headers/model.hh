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

    int check_for_intersection();

public:
    ~snake()
    {
    }

    point get_head()
    {
        return points.front();
    }

    void check_for_rabbits(const std::list<point> rabbits);

    snake(int n, int x, int y);

    void change_direction(const int d)
    {
        direction = d;
    }

    void update_state();

    const std::list<point> &get_state()
    {
        return points;
    }

    void move(char d);
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

    void update_state(point snake_head);

private:
    int direction = 4;

    int possible_move();

};

class flock_rabbits : public character
{
public:
    flock_rabbits(int n_, int size_x_, int size_y_);

    void update_state(point snake_head);

    const std::list<point> get_state();

    void kill(const point& rabbit)
    {
        rabbits.erase(std::find(rabbits.begin(), rabbits.end(), rabbit));
    }

    int collide(int x_, int y_);

private:
    int n;
    std::list<rabbit> rabbits;
};