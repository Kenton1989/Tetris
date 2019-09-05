#ifndef BLOCK_ORIENTATION_H
#define BLOCK_ORIENTATION_H

#include "brick_base.h"

namespace Kenton {

//"o" means Orientation

class Brick_4o: public Brick_base {
public:
    virtual void transform() override {
        rotate(Rotary::CLOCKWISE, 90);
    }
    virtual void transform_back() override {
        rotate(Rotary::CLOCKWISE, 270);
    }
};

class Brick_2o: public Brick_base {
public:
    virtual void transform() override {
        turn();
    }
    virtual void transform_back() override {
        turn();
    }
private:
    bool is_turned_ = false;
    void turn() {
        if (is_turned_)
            rotate(Rotary::CLOCKWISE, 270);
        else rotate(Rotary::CLOCKWISE, 90);
    }
};

class Brick_1o: public Brick_base {
public:
    virtual void transform() override {}
    virtual void transform_back() override {}
};

} //namespace Kenton

#endif // BLOCK_ORIENTATION_H
