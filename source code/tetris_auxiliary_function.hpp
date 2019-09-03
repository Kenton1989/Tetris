#ifndef TETRIS_AUXILIARY_FUNCTIONS_HPP
#define TETRIS_AUXILIARY_FUNCTIONS_HPP
#include "tetris_component.hpp"

namespace Kenton {

enum Brick_Type {
    T_SHAPE,
    L_SHAPE1,
    L_SHAPE2,
    I_SHAPE,
    Z_SHAPE1,
    Z_SHAPE2,
    SQ_SHAPE,
    TOTAL_NUM
};
void create_bricks();
Brick generate_brick(Brick_Type);
Brick random_brick();

} //namespace Kenton

#endif // TETRIS_AUXILIARY_FUNCTIONS_HPP
