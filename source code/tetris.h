#ifndef TETRIS_HPP
#define TETRIS_HPP
#include <set>
#include "gamewidgets/all.h"
#include "systemwidgets/all.h"
#include "painter.h"

namespace Kenton {

using std::set;

class Tetris {
    using BrickPtr = std::unique_ptr<Brick>;
public:
    Tetris(int w, int h);
    void init();
    void start();
private:
    bool init_done_ = false;
    bool gameover_ = false;
    Coord entrance_;
    BrickPtr brick_;
    Map map_;
    TetrisInfo info_;
    Clock clock;
    Keyboard keyboard_;
    Painter painter_;

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
