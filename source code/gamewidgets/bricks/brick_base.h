#ifndef BLOCK_BASE_H
#define BLOCK_BASE_H

#include "../square.h"
#include <algorithm>
#include <initializer_list>
#include <vector>

namespace Kenton {

using std::vector;
using std::initializer_list;

enum class Linear { UP, DOWN, LEFT, RIGHT };
enum class Rotary { CLOCKWISE, COUNTERCLOCKWISE };


/* For the function with a pointer to Container "output" (Container *output) as a parameter:
 * The result will be put in the "output" to avoid Ctor/Dtor in function.
 * The other part of program where repeating calling this function will happen
 * can construct the container first and pass it to the function
 * to reduce the times of calling Ctor/Dtor to once.
 */
class Brick_base {
public:
    using CoordContainer = vector<Coord>;
    using PropertyContainer = vector<Square::Property>;
    using size_type = CoordContainer::size_type;
    //5 default function
    Brick_base() = default;
    Brick_base(const Brick_base&) = default;
    Brick_base& operator= (const Brick_base&) = default;
    Brick_base(Brick_base&&) = default;
    Brick_base& operator= (Brick_base&&) = default;
    virtual ~Brick_base();
    //other constructor
    Brick_base(initializer_list<Square> l): properties_(get_properties(l.begin(), l.end())),
                                            shape_(get_coords(l.begin(), l.end())) {}
    Brick_base(CoordContainer shape, PropertyContainer properties):
        properties_(properties), shape_(shape) {}

    int size() { return shape_.size(); }
    //Get/Add/Remove/Set Square
    const Square square(size_type index) {
        return Square(shape_[index], properties_[index]);
    }
    void append_sq(const Square& sq) {
        properties_.push_back(sq.property), shape_.push_back(sq.pos);
    }
    void pop_sq() {
        properties_.pop_back(), shape_.pop_back();
    }
    void clear() {
        properties_.clear(), shape_.clear();
    }
    void set_sq(size_type index, const Square& sq) {
        if (index >= shape_.size())
            throw(std::invalid_argument("The index exceed the size of brick"));
        shape_[index] = sq.pos;
        properties_[index] = sq.property;
    }
    //Get/Set Properties
    const PropertyContainer& properties() const { return properties_; }
    const Square::Property& property(size_type index) const {
        if (index >= properties_.size())
            throw(std::invalid_argument("The index exceed the size of brick"));
        return properties_[index];
    }
    void set_property(size_type index, Square::Property p) {
        if (index >= properties_.size())
            throw(std::invalid_argument("The index exceed the size of brick"));
        properties_[index] = p;
    }
    //Get/Set the postion of Brick_base
    const Coord pos() const { return pos_; }
    void set_pos(int x, int y) { pos_.x = x, pos_.y = y; }
    void set_pos(Coord c) { pos_ = c; }
    //Get/Set position of single square
    const Coord& shape(size_type index) const {
        if (index >= shape_.size())
            throw(std::invalid_argument("The index exceed the size of brick"));
        return shape_[index];
    }
    void set_shape(size_type index, const Coord& pos) {
        if (index >= shape_.size())
            throw(std::invalid_argument("The index exceed the size of brick"));
        shape_[index] = pos;
    }
    //Get whole shape
    const CoordContainer& shape() const { return shape_; }
    //Set whole shape
    template <typename CoordInputIter>
    void set_shape(CoordInputIter first, CoordInputIter last) {
        shape_.assign(first, last);
        properties_.resize(shape_.size());
    }
    template <typename Container>
    void set_shape(const Container& c) {
        set_shape(c.begin(), c.end());
    }
    void set_shape(CoordContainer &&v) {
        shape_ = std::move(v);
        properties_.resize(shape_.size());
    }
    //return the coord of each square refer to the Coord ref
    template<typename Container = CoordContainer>
    Container& shape_at(const Coord &ref ,Container *output) const {
        output->clear();
        std::transform(shape_.begin(), shape_.end(), std::back_inserter(*output),
                       [](const Coord&) { return Coord(c.x+ref.x, c.y+ref.y); });
        return *output;

    }
    CoordContainer shape_at(const Coord &ref) const {
        CoordContainer ret;
        shape_at(ref, &ret);
        //not "return shape_at(ref, &ret);". reason: for RVO
        return ret;
    }
    //return the absolute position of all square (the position refer to pos_).
    template<typename Container = CoordContainer>
    Container& shape_abs(Container* output) const {
        return shape_at(pos_, output);
    }
    CoordContainer shape_abs() const {
        CoordContainer ret;
        shape_abs(&ret);
        //not "return shape_abs(ref, &ret);". reason: for RVO
        return ret;
    }
    //return the adjacent squares on the specific direction.
    template <typename Container = CoordContainer>
    Container& adjacent(Linear d, Container *output);

    CoordContainer adjacent(Linear d) {
        CoordContainer v;
        return adjacent(d, &v);
    }
    //Shape Transformation Function
    //straight move
    Brick_base& move_by(int dx, int dy) { pos_.x += dx, pos_.y += dy; }
    Brick_base& move_by(Linear d, int step = 1);
    //Rotate functions
    void rotate(Rotary d, int degree);
    //all bricks but define their transform function
    //to react the input of up-arrow key during game
    virtual void transform() = 0;
    //provide a way to undo transforming
    virtual void transform_back() = 0;
private:
    //in the later part, coord is usually used in calculation
    //for the convenience of loop through all coords, saperate coords from the square class
    PropertyContainer properties_;
    CoordContainer shape_;
    Coord pos_ = {0,0};
};

template <typename Container>
Container& adjacent(Linear d, Container *output) {
    shape_abs(output);
    switch (d) {
    case Linear::UP:
        for (auto &c: *output) --c.y;
        break;
    case Linear::DOWN:
        for (auto &c: *output) ++c.y;
        break;
    case Linear::LEFT:
        for (auto &c: *output) --c.x;
        break;
    case Linear::RIGHT:
        for (auto &c: *output) ++c.x;
        break;
    }
    return *output;
}

} //namespace Kenton

#endif // BLOCK_BASE_H
