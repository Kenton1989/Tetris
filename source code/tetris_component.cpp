#include "tetris_component.hpp"

namespace Kenton {

//get a list of coords from a list of square
vector<Coord> get_coords (const it_Square &b, const it_Square &e) {
    vector<Coord> v;
    for(auto i = b; i != e; ++i)
        v.push_back(i->pos);
    return v;
}
//get a list of properties from a list of square
vector<Square::Property> get_properties (const it_Square &b, const it_Square &e) {
    vector<Square::Property> v;
    for(auto i = b; i != e; ++i)
        v.push_back(i->property);
    return v;
}

Brick& Brick::move_by(Linear_Direction d, int step) {
    switch (d) {
    case UP:
        move_by(0, -step);
        break;
    case DOWN:
        move_by(0, step);
        break;
    case LEFT:
        move_by(-step, 0);
        break;
    case RIGHT:
        move_by(step, 0);
        break;
    default:
        break;
    }
    return *this;
}

Brick& Brick::rotate(Rotate_Direction d, int n_half_pi) {
    //Convert the counterclockwise to clockwise
    if (d == COUNTERCLOCKWISE) n_half_pi = 4 - n_half_pi;
    n_half_pi %= 4;
    //return if no need to rotate
    if (n_half_pi == 0) return *this;

    if (n_half_pi < 0) n_half_pi += 4;
    int tmp;
    switch (n_half_pi) {
    //case 0 is already excluded before
    case 1:
        for(auto& s: _shape) {
            tmp = s.y; s.y = s.x; s.x = -tmp;
        }
        break;
    case 2:
        for(auto& s: _shape) {
            s.y = -s.y, s.x = -s.x;
        }
        break;
    case 3:
        for(auto& s: _shape) {
            tmp = s.y; s.y = -s.x; s.x = tmp;
        }
        break;
    default:
        break;
    }
    return *this;
}

vector<Coord>& Brick::adjacent(Linear_Direction d, vector<Coord> *output) {
    shape_abs(output);
    switch (d) {
    case UP:
        for (auto &c: *output) --c.y;
        break;
    case DOWN:
        for (auto &c: *output) ++c.y;
        break;
    case LEFT:
        for (auto &c: *output) --c.x;
        break;
    case RIGHT:
        for (auto &c: *output) ++c.x;
        break;
    default:
        break;
    }
    return *output;
}

vector<Coord> Brick::adjacent(Linear_Direction d) {
    vector<Coord> v;
    return adjacent(d, &v);
}

const Map::Pixel Map::empty_pixel = Square::EMPTY;
const Map::Pixel Map::invalid_pixel = Square::INVALID;

void TetrisInfo::reset() {
    _step = 5;
    _counter = 0;
    _score = 0;
    _level = 1;
    _rate = 1000; //unit ms;
}


void TetrisInfo::increase(int n) {
    _counter += n;
    _score += n*_level;
    if (_counter > _level*_step) {
        ++_level;
        _rate = std::max(int(1000*(1 - 0.2*_level)), 1000/_level);
        _counter = 0;
    }
}

} //namespace Kenton
