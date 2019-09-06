#ifndef BRICK_H
#define BRICK_H
#include "bricks/brick_base.h"
#include "bricks/brick_orientation.h"
#include "memory"

namespace Kenton {

enum class DefaultBrick {
    T_SHAPE,
    L_SHAPE1,
    L_SHAPE2,
    I_SHAPE,
    Z_SHAPE1,
    Z_SHAPE2,
    SQ_SHAPE,
    TOTAL_NUM
};

using Brick = Brick_base;
using BrickPtr = std::unique_ptr<Brick>;

BrickPtr creatBrick(int orientation, std::initializer_list<Square> sq_list);
BrickPtr creatBrick(DefaultBrick brick_type);

//random default brick type generater
inline DefaultBrick randomBrickType() {
    static std::default_random_engine randUInt(time(nullptr));
    return static_cast<DefaultBrick>(randUInt()%DefaultBrick::TOTAL_NUM);
}
//random default brick generation function
inline BrickPtr randomDefaultBrick() {
    return creat_brick(randBrickType());
}

} //namespace Kenton

#endif // BRICK_H
