#include "./headers/model.hh"

int snake::check_for_intersection()
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

void snake::check_for_rabbits(const std::list<point> rabbits)
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

void snake::update_state()
{
    point temp = points.front() + direction_arr[direction];

    points.push_front(temp);

    if ((temp.x == size_x) || (temp.x == 0) || (temp.y == size_y) || (temp.y == 0) || check_for_intersection())
    {
        throw point(-1, -1);
    }
}

void snake::move(char d)
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

void rabbit::update_state(point snake_head)
{
    point vect = (*this) - snake_head;

    direction = std::rand() % 5;

    if (possible_move())
        (*this) += direction_arr[direction];
}

int rabbit::possible_move()
{

    point temp = *this + direction_arr[direction];

    if ((temp.x > 0) && (temp.x < size_x) && (temp.y > 0) && (temp.y < size_y))
        return 1;

    return 0;
}

void flock_rabbits::update_state(point snake_head)
{
    for (auto it = rabbits.begin(); it != rabbits.end(); ++it)
        it->update_state(snake_head);
}

const std::list<point> flock_rabbits::get_state()
{
    std::list<point> temp;

    for (auto it = rabbits.begin(); it != rabbits.end(); ++it)
        temp.emplace_back(*it);

    return temp;
}

int flock_rabbits::collide(int x_, int y_)
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

flock_rabbits::flock_rabbits(int n_, int size_x_, int size_y_) : n(n_)
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

snake::snake(int n, int x, int y)
{
    update_size(x, y);
    int x_temp = x / 2;
    int y_temp = y / 2;

    for (int i = 0; i < n; ++i)
    {
        points.emplace_front(point(x_temp + i, y_temp));
    }
};