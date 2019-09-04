#include "Brick_base.h"
namespace Kenton {

Brick_base& Brick_base::move_by(Linear_Direction d, int step) {
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

Brick_base& Brick_base::rotate(Rotate_Direction d, int n_half_pi) {
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

vector<Coord>& Brick_base::adjacent(Linear_Direction d, vector<Coord> *output) {
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

vector<Coord> Brick_base::adjacent(Linear_Direction d) {
    vector<Coord> v;
    return adjacent(d, &v);
}

} //namespace Kenton

