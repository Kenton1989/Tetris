#include "tetris.hpp"
#include "windows.h"

using namespace Kenton;


Tetris::Tetris(int w, int h): _entrance(w/2+1, 0),_map(w+2, h+1), _screen(w+2, h+1) {
    create_bricks();
    _brick = random_brick();
    _brick.set_pos(_entrance);
    _info.set_next_brick(random_brick());
    set_map_border(_map);
    _init_done = true;
}

void Tetris::init() {
    if(_init_done)
        return;
    _brick = random_brick();
    _brick.set_pos(_entrance);
    _map.clean();
    set_map_border(_map);
    _info.reset();
    _info.set_next_brick(random_brick());
    _gameover = false;
    _init_done = true;
}

void Tetris::start() {
    if (!_init_done)
        init();
    _init_done = false;
    bool changed = false;
    _clock.set_timer(_info.rate());
    show();
    while (!_gameover) {
         changed = false;

        if (_keyboard.has_input())
            changed = input(_keyboard.get_input());

        if (_clock.times_up()) {
            default_action();
            changed = true;
        }

        if (changed)
            show();

        Sleep(50);
    }
    _screen.print_gameover();
    _screen.set_consor_pos(0, _map.height());
}

void Tetris::default_action() {
    move_brick_down();
}

void Tetris::pause() {
    _screen.print_pause(true);
    int input, timer_rest = _clock.timer_rest();
    while(true) {
        if (_keyboard.has_input()) {
            input = _keyboard.get_input();
            if (input == 'p' || input == 'P')
                break;
        }
        Sleep(50);
    }
    _screen.print_pause(false);
    _clock.set_timer(timer_rest);
}

bool Tetris::input(int in) {
    static vector<Coord> tmp;
    switch (in) {
    case KeyboardInput::UP_ARROW:
    case 'w': case 'W':
        _brick.rotate();
        if (!_map.are_empty(_brick.shape_abs(&tmp))){
            _brick.rotate_back();
            return false;
        }
        return true;
    case KeyboardInput::DOWN_ARROW:
    case 's': case 'S':
        return move_brick_down();
    case KeyboardInput::LEFT_ARROW:
    case 'a': case 'A':
        if(_map.are_empty(_brick.adjacent(LEFT, &tmp))) {
            _brick.move_by(LEFT);
            return true;
        } else {
            return false;
        }
    case KeyboardInput::RIGHT_ARROW:
    case 'd': case 'D':
        if(_map.are_empty(_brick.adjacent(RIGHT, &tmp))) {
            _brick.move_by(RIGHT);
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
    _screen.print(_map);
    _screen.print(_info);
    _screen.print(_brick);
}

bool Tetris::move_brick_down() {
    static vector<Coord> tmp_coord_v;
    static set<int> tmp_int_set;
    if(_map.are_empty(_brick.adjacent(DOWN, &tmp_coord_v))) {
        _brick.move_by(DOWN);
    } else {
        if (!draw_brick_on_map()) {
            _gameover = true;
            return false;
        }
        //search whether ther are some rows are filled and increase the score;
        int filled_row = 0;
        for (int row: get_y_range(_brick.shape_abs(&tmp_coord_v), &tmp_int_set)) {
            if (_map.row_is_filled(row)) {
                ++filled_row;
               /* because the row in set will be loop increasingly,
                * no need to worry about the change of the number of the row
                * caused by deleting a row
                */
                _map.clean_row(row);
                _map.set(0, 0, Square::WALL);
                _map.set(_map.width()-1, 0, Square::WALL);
                _info.increase(filled_row);
            }
        }
        //refresh the brick
        _brick = _info.next_brick();
        _brick.set_pos(_entrance);
        _info.set_next_brick(random_brick());
        //in case of some overlapping situations
        for (const auto &c : _brick.shape_abs(&tmp_coord_v)) {
            if (_map.is_valid_pos(c) && !_map.is_empty(c)) {
                _gameover = true;
                return false;
            }
        }
    }
    _clock.set_timer(_info.rate());
    return true;
}

void Tetris::set_map_border(Map& m) {
    static Map::Pixel border_pixel = Square::WALL;
    int h = m.height()-1, w = m.width();
    for (int i = 0; i < w; ++i)
        _map.set(i, h, border_pixel);
    --w;
    for (int i = 0; i < h; ++i)
        _map.set(0, i, border_pixel).set(w, i, border_pixel);
}

bool Tetris::draw_brick_on_map() {
    static vector<Coord> tmp;
    static const Map::Pixel brick_pixel = Square::BRICK;
    _brick.shape_abs(&tmp);
    if (!_map.are_valid_pos(tmp))
        return false;
    _map.set_all(tmp, brick_pixel);
    return true;
}

set<int> Tetris::get_y_range(const vector<Coord> &c_list, set<int> *output_set) {
    output_set->clear();
    for (const auto &c: c_list)
        output_set->insert(c.y);
    return *output_set;
}
