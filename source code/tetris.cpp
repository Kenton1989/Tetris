#include "tetris.h"
#include "windows.h"

using namespace Kenton;


Tetris::Tetris(int w, int h):
    entrance_(w/2+1, 0),
    brick_(randomDefaultBrick()),
    map_(w+2, h+1), painter_(w+2, h+1)
{
    brick_->set_pos(entrance_);
    info_.set_next_brick(randomDefaultBrick());
    set_map_border(map_);
    init_done_ = true;
}

void Tetris::init() {
    if(init_done_)
        return;
    brick_ = randomDefaultBrick();
    brick_->set_pos(entrance_);
    map_.clean_all();
    set_map_border(map_);
    info_.reset();
    info_.set_next_brick(randomDefaultBrick());
    gameover_ = false;
    init_done_ = true;
}

void Tetris::start() {
    if (!init_done_)
        init();
    init_done_ = false;

    show();

    bool displayChanged = false;
    clock.set_timer(info_.rate());
    while (!gameover_) {

        if (keyboard_.has_input())
            displayChanged = input(keyboard_.get_input());

        if (clock.times_up()) {
            default_action();
            displayChanged = true;
        }

        if (displayChanged) {
            show();
        }

        displayChanged = false;
        Sleep(50);
    }
    painter_.print_gameover();
}

void Tetris::default_action() {
    move_brick_down();
}

void Tetris::pause() {
    painter_.print_pause();
    int timer_rest = clock.timer_rest();
    while(true) {
        while (keyboard_.has_input()) {
            int input = keyboard_.get_input();
            if (input == 'p' || input == 'P')
                break;
        }
        Sleep(50);
    }
    painter_.print_pause(false);
    clock.set_timer(timer_rest);
}

//react input, if nothing is changed, returns true, or returns false
bool Tetris::input(int in) {
    static std::vector<Coord> tmp;
    switch (in) {
    case Keyboard::Key_id::UP_ARROW:
    case 'w': case 'W':
        brick_->transform();
        if (!map_.are_empty(brick_->shape_abs(&tmp))){
            brick_->transform_back();
            return false;
        }
        return true;
    case Keyboard::Key_id::DOWN_ARROW:
    case 's': case 'S':
        return move_brick_down();
    case Keyboard::Key_id::LEFT_ARROW:
    case 'a': case 'A':
        if(map_.are_empty(brick_->adjacent(Linear::LEFT, &tmp))) {
            brick_->move_by(Linear::LEFT);
            return true;
        } else {
            return false;
        }
    case Keyboard::Key_id::RIGHT_ARROW:
    case 'd': case 'D':
        if(map_.are_empty(brick_->adjacent(Linear::RIGHT, &tmp))) {
            brick_->move_by(Linear::RIGHT);
            return true;
        } else {
            return false;
        }
    case 'p': case 'P':
        pause();
        return false;
    default:
        break;
    }
    return false;
}

void Tetris::show() {
    painter_.print(map_);
    painter_.print(info_);
    painter_.print(*brick_);
}

bool Tetris::move_brick_down() {
    static std::vector<Coord> tmp_coord_v;
    static std::set<int> tmp_int_set;
    if(map_.are_empty(brick_->adjacent(Linear::DOWN, &tmp_coord_v))) {
        brick_->move_by(Linear::DOWN);
    } else {
        //draw_brick_on_map() return false if the brick exceed the range of map
        //that means gameover
        if (!draw_brick_on_map()) {
            gameover_ = true;
            return false;
        }
        //search whether ther are some rows are filled and increase the score;
        int filled_row = 0;
        for (int row: get_y_range(brick_->shape_abs(&tmp_coord_v), &tmp_int_set)) {
            if (map_.row_is_filled(row)) {
                ++filled_row;
               /* because the row in set will be loop increasingly (from upper to lower),
                * no need to worry about the change of the number of the row
                * caused by deleting a row
                */
                map_.remove_row(row);
                map_.add_first_row();
                map_.set(0, 0, Square::Type::WALL);
                map_.set(map_.width()-1, 0, Square::Type::WALL);
                info_.increase(filled_row);
            }
        }
        //refresh the brick
        brick_ = info_.set_next_brick(randomDefaultBrick());
        brick_->set_pos(entrance_);
        //in case of some overlapping situations
        for (const auto &c : brick_->shape_abs(&tmp_coord_v)) {
            if (map_.is_valid_pos(c) && !map_.is_empty(c)) {
                gameover_ = true;
                return false;
            }
        }
    }
    clock.set_timer(info_.rate());
    return true;
}

void Tetris::set_map_border(Map& m) {
    static Map::Pixel border_pixel = Square::Type::WALL;
    int h = m.height()-1, w = m.width();
    for (int i = 0; i < w; ++i)
        map_.set(i, h, border_pixel);
    --w;
    for (int i = 0; i < h; ++i) {
        map_.set(0, i, border_pixel);
        map_.set(w, i, border_pixel);
    }
}

bool Tetris::draw_brick_on_map() {
    static vector<Coord> tmp;
    static const Map::Pixel brick_pixel = Square::Type::BRICK;
    brick_->shape_abs(&tmp);
    if (!map_.are_valid_pos(tmp))
        return false;
    map_.set_all(tmp, brick_pixel);
    return true;
}

set<int> Tetris::get_y_range(const vector<Coord> &c_list, set<int> *output_set) {
    output_set->clear();
    for (const auto &c: c_list)
        output_set->insert(c.y);
    return *output_set;
}
