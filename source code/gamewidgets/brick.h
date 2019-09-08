#ifndef BRICK_H
#define BRICK_H
#include "bricks/brick_base.h"
#include "bricks/brick_orientation.h"
#include <ctime>
#include <memory>
#include <random>

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
using std::unique_ptr;

unique_ptr<Brick> creatBrick(int orientation, const std::initializer_list<Square>& sq_list);
unique_ptr<Brick> creatBrick(DefaultBrick brick_type);

static std::default_random_engine randUInt(time(0));
//random default brick type generater
inline DefaultBrick randomBrickType() {
    return static_cast<DefaultBrick>(randUInt()%static_cast<decltype(randUInt())>(DefaultBrick::TOTAL_NUM));
}
//random default brick generation function
inline unique_ptr<Brick> randomDefaultBrick() {
    std::uniform_int_distribution<int> randTimes(1, 4);
    unique_ptr<Brick> ret = creatBrick(randomBrickType());
    for (int i = randTimes(randUInt); i > 0; --i)
        ret->transform();
    return ret;
}

} //namespace Kenton

#endif // BRICK_H
