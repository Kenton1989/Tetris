#include "brick.h"
#include <ctime>
#include <random>

namespace Kenton {

//general brick generation function
unique_ptr<Brick> creatBrick(int orientation, const std::initializer_list<Square>& sq_list) {
    switch (orientation) {
    case 1:
        return unique_ptr<Brick>(new Brick_1o(sq_list));
        break;
    case 2:
        return unique_ptr<Brick>(new Brick_2o(sq_list));
        break;
    case 4:
        return unique_ptr<Brick>(new Brick_4o(sq_list));
    default:
        return nullptr;
    }
}

//function to store the shape of default shape
inline const std::initializer_list<Square>&
  brickShapeList(DefaultBrick type) {
    static std::initializer_list<Square> list[int(DefaultBrick::TOTAL_NUM)] = {
        {   //T_SHAPE
            Square(0,0,Square::Type::BRICK),
            Square(1,0,Square::Type::BRICK),
            Square(-1,0,Square::Type::BRICK),
            Square(0,1,Square::Type::BRICK),
        },
        {   //L_SHAPE1
            Square(-1,0,Square::Type::BRICK),
            Square(-1,1,Square::Type::BRICK),
            Square(0,1,Square::Type::BRICK),
            Square(1,1,Square::Type::BRICK),
        },
        {   //L_SHAPE2
            Square(1,0,Square::Type::BRICK),
            Square(-1,1,Square::Type::BRICK),
            Square(0,1,Square::Type::BRICK),
            Square(1,1,Square::Type::BRICK),
        },
        {   //I_SHAPE
            Square(-1,0,Square::Type::BRICK),
            Square(0,0,Square::Type::BRICK),
            Square(1,0,Square::Type::BRICK),
            Square(2,0,Square::Type::BRICK),
        },
        {   //Z_SHAPE1
            Square(0,0,Square::Type::BRICK),
            Square(0,1,Square::Type::BRICK),
            Square(1,0,Square::Type::BRICK),
            Square(1,-1,Square::Type::BRICK),
        },
        {   //Z_SHAPE2
            Square(0,0,Square::Type::BRICK),
            Square(0,1,Square::Type::BRICK),
            Square(1,0,Square::Type::BRICK),
            Square(-1,1,Square::Type::BRICK),
        },
        {   //SQ_SHAPE
            Square(0,0,Square::Type::BRICK),
            Square(0,1,Square::Type::BRICK),
            Square(1,0,Square::Type::BRICK),
            Square(1,1,Square::Type::BRICK),
        }/*
        {
            Square(,,Square::Type::BRICK),
            Square(,,Square::Type::BRICK),
            Square(,,Square::Type::BRICK),
            Square(,,Square::Type::BRICK),
        } */
    };
    return list[int(type)];
}
//generation function of default brick
unique_ptr<Brick> creatBrick(DefaultBrick type) {
    switch (type) {
    case DefaultBrick::T_SHAPE:
    case DefaultBrick::L_SHAPE1:
    case DefaultBrick::L_SHAPE2:
        return creatBrick(4, brickShapeList(type));
    case DefaultBrick::I_SHAPE:
    case DefaultBrick::Z_SHAPE1:
    case DefaultBrick::Z_SHAPE2:
        return creatBrick(2, brickShapeList(type));
    case DefaultBrick::SQ_SHAPE:
        return creatBrick(1, brickShapeList(type));
    default:
        return nullptr;
    }
}

} //namespace Kenton
