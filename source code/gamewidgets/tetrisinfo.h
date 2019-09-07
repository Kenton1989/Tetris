#ifndef TETRISINFO_H
#define TETRISINFO_H

#include "brick.h"
#include <memory>

namespace Kenton {

using std::shared_ptr;

class TetrisInfo {
    using BrickPtr = unique_ptr<Brick>;
public:
    int score() const { return score_; }
    int level() const  { return level_; }
    int rate()  const  { return rate_; }
    const Brick& next_brick()  const  { return *next_; }
    BrickPtr set_next_brick(BrickPtr&& newBrick) {
        BrickPtr oldVal = std::move(next_);
        next_ = std::move(newBrick);
        return oldVal;
    }

    void reset();
    void increase(int n = 1);
private:
    int step_ = 5;
    int counter_ = 0;
    int score_ = 0;
    int level_ = 1;
    int rate_ = 1000; //unit ms;
    BrickPtr next_ = nullptr;
};

} //namespace Kenton

#endif // TETRISINFO_H
