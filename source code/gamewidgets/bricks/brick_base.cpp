#include "Brick_base.h"
#include <exception>

namespace Kenton {

Brick_base::~Brick_base() {}

void Brick_base::move_by(Linear d, int step) {
    switch (d) {
    case Linear::UP:
        move_by(0, -step);
        break;
    case Linear::DOWN:
        move_by(0, step);
        break;
    case Linear::LEFT:
        move_by(-step, 0);
        break;
    case Linear::RIGHT:
        move_by(step, 0);
        break;
    }
}

void Brick_base::rotate(Rotary d, int degree) {
    //Convert the counterclockwise to clockwise
    if (d == Rotary::COUNTERCLOCKWISE) degree = -degree;
    degree %= 360;
    int tmp;
    switch (degree) {
    case 0:
        break;
    case 90:
    case -270:
        for(auto& s: shape_) {
            tmp = s.y; s.y = s.x; s.x = -tmp;
        }
        break;
    case 180:
    case -180:
        for(auto& s: shape_) {
            s.y = -s.y, s.x = -s.x;
        }
        break;
    case 270:
    case -90:
        for(auto& s: shape_) {
            tmp = s.y; s.y = -s.x; s.x = tmp;
        }
        break;
    default:
        throw(std::invalid_argument("the degree to rotate must be the multiple of 90."));
    }
}



} //namespace Kenton

