#include "tetrisinfo.h"
namespace Kenton {


void TetrisInfo::reset() {
    step_ = 5;
    counter_ = 0;
    score_ = 0;
    level_ = 1;
    rate_ = 1000; //unit ms;
}


void TetrisInfo::increase(int n) {
    counter_ += n;
    score_ += n*level_;
    if (counter_ > level_*step_) {
        ++level_;
        rate_ = std::max(int(1000*(1 - 0.2*level_)), 1000/level_);
        counter_ = 0;
    }
}

} //namespace Kenton
