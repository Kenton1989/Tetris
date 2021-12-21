#ifndef BRICKBASE_H
#define BRICKBASE_H

#include "vec2d.h"
#include "cell.h"

#include <vector>

class BrickBase
{
public:
    using PosT = Vec2D<int>;

    BrickBase();

    virtual PosT pos() const { return pos_; }

    virtual PosT cellPos(int idx) const { return shape_[idx] + pos_; }
    virtual PosT cellRelativePos(int idx) const { return shape_[idx]; }
    virtual Cell cellOf(int idx) const { return cells_[idx]; }
    virtual size_t size() const { return shape_.size(); }

    virtual PosT max() { return max_; };
    virtual PosT min() { return min_; };

    virtual void setPos(PosT p) { pos_ = p; }

    virtual void addCell(PosT p, Cell c) {
        cells_.push_back(c);
        shape_.push_back(p);
    }
    virtual void clearCell() {
        cells_.clear();
        shape_.clear();
    }

    virtual void tranform() = 0;

    virtual ~BrickBase() {}
private:
    PosT pos_;
    std::vector<PosT> shape_;
    std::vector<Cell> cells_;
protected:
    PosT max_, min_;
};

#endif // BRICKBASE_H
