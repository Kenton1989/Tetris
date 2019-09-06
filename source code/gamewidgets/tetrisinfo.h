#ifndef TETRISINFO_H
#define TETRISINFO_H

namespace Kenton {

class TetrisInfo {
public:
    int score() const { return score_; }
    int level() const  { return level_; }
    int rate()  const  { return rate_; }
    const Brick& next_brick()  const  { return next_; }
    void set_next_brick(const Brick& b) { next_ = b; }

    void reset();
    void increase(int n = 1);
private:
    int step_ = 5;
    int counter_ = 0;
    int score_ = 0;
    int level_ = 1;
    int rate_ = 1000; //unit ms;
    Brick next_;
};

} //namespace Kenton

#endif // TETRISINFO_H
