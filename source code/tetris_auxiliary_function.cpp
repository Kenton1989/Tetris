#include "tetris_auxiliary_function.hpp"
#include <random>

namespace Kenton {

Brick* brick_store() {
    static Brick bricks[Brick_Type::TOTAL_NUM];
    return bricks;
}


void make_brick(Brick& b, int orientation, initializer_list<Square> shape) {
    b = Brick(shape);
    b.set_orientation(orientation);
}

void create_bricks() {
    static bool finished = false;
    if (finished)
        return;

    make_brick(brick_store()[T_SHAPE], 4,
               {
                   Square(0,0,Square::BRICK),
                   Square(1,0,Square::BRICK),
                   Square(-1,0,Square::BRICK),
                   Square(0,1,Square::BRICK),
               });
    make_brick(brick_store()[L_SHAPE1], 4,
               {
                   Square(-1,0,Square::BRICK),
                   Square(-1,1,Square::BRICK),
                   Square(0,1,Square::BRICK),
                   Square(1,1,Square::BRICK),
               });
    make_brick(brick_store()[L_SHAPE2], 4,
               {
                   Square(1,0,Square::BRICK),
                   Square(-1,1,Square::BRICK),
                   Square(0,1,Square::BRICK),
                   Square(1,1,Square::BRICK),
               });
    make_brick(brick_store()[I_SHAPE], 2,
               {
                   Square(-1,0,Square::BRICK),
                   Square(0,0,Square::BRICK),
                   Square(1,0,Square::BRICK),
                   Square(2,0,Square::BRICK),
               });
    make_brick(brick_store()[Z_SHAPE1], 2,
               {
                   Square(0,0,Square::BRICK),
                   Square(0,1,Square::BRICK),
                   Square(1,0,Square::BRICK),
                   Square(1,-1,Square::BRICK),
               });
    make_brick(brick_store()[Z_SHAPE2], 2,
               {
                   Square(0,0,Square::BRICK),
                   Square(0,1,Square::BRICK),
                   Square(1,0,Square::BRICK),
                   Square(-1,1,Square::BRICK),
               });
    make_brick(brick_store()[SQ_SHAPE], 1,
               {
                   Square(0,0,Square::BRICK),
                   Square(0,1,Square::BRICK),
                   Square(1,0,Square::BRICK),
                   Square(1,1,Square::BRICK),
               });
    /*
    make_brick(brick_store()[], 4,
               {
                   Square(,,Square::BRICK),
                   Square(,,Square::BRICK),
                   Square(,,Square::BRICK),
                   Square(,,Square::BRICK),
               });
    */
    finished = true;
}

Brick generate_brick(Brick_Type t) {
    return brick_store()[t];
}

Brick random_brick() {
    static std::default_random_engine e(time(0));
    Brick b = brick_store()[e()%Brick_Type::TOTAL_NUM];
    b.rotate(CLOCKWISE, e()%b.orientation());
    return b;
}

} //namespace Kenton
