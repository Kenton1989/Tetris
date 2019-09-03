#ifndef TETRIS_HPP
#define TETRIS_HPP
#include <set>

#include "tetris_component.hpp"
#include "tetris_auxiliary_function.hpp"

using std::set;

namespace Kenton {

class Tetris {
public:
    Tetris(int w, int h);
    void init();
    void start();
private:
    bool _init_done = false;
    bool _gameover = false;
    Coord _entrance;
    Brick _brick;
    Map _map;
    TetrisInfo _info;
    Clock _clock;
    KeyboardInput _keyboard;
    Screen _screen;

    void default_action();
    void pause();
    bool input(int in);
    void show();
    bool move_brick_down();
    void set_map_border(Map& m);
    bool draw_brick_on_map();
    set<int> get_y_range(const vector<Coord> &c_list, set<int> *output_set);
};

} //namespace Kenton


#endif // TETRIS_HPP
