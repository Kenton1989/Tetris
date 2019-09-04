#ifndef BLOCK_BASE_H
#define BLOCK_BASE_H

#include "../square.h"
#include <vector>

namespace Kenton {

using std::vector;
enum Linear_Direction { UP, DOWN, LEFT, RIGHT };
enum Rotate_Direction { CLOCKWISE, COUNTERCLOCKWISE };

class Brick_base {
public:
    Brick_base() = default;
    Brick_base(const Brick_base&) = default;
    Brick_base(initializer_list<Square> l): _properties(get_properties(l.begin(), l.end())),
                                       _shape(get_coords(l.begin(), l.end())) {}

    int size() { return _shape.size(); }
    //Handling the postion of Brick_base
    const Coord pos() const { return _pos; }
    Brick_base& set_pos(int x, int y) { _pos.x = x, _pos.y = y; return *this; }
    Brick_base& set_pos(Coord c) { _pos = c; return *this; }
    Brick_base& move_by(int dx, int dy) { _pos.x += dx, _pos.y += dy; return *this; }
    Brick_base& move_by(Linear_Direction d, int step = 1);
    //Handling the shape
    const vector<Coord>& shape() const { return _shape; }
    //return the coord of each square with absolute coordination.
    vector<Coord>& shape_abs(vector<Coord> *output) const {
        output->clear();
        for (const auto &c: _shape)
            output->push_back(Coord(c.x+_pos.x, c.y+_pos.y));
        return *output;
    }
    //combine the former tow function
    vector<Coord> shape(bool absolute) const {
        if (absolute) {
            vector<Coord> v;
            return shape_abs(&v);
        }
        return _shape;
    }
    vector<Coord> shape(const Coord &ref) const {
        vector<Coord> v;
        return shape_at(ref, &v);
    }
    vector<Coord> shape_at(const Coord &ref ,vector<Coord> *output) const {
        output->clear();
        for (const auto &c: _shape)
            output->push_back(Coord(c.x+ref.x, c.y+ref.y));
        return *output;

    }
    //Add and remove block
    Brick_base& append_sq(const Square& sq) { _properties.push_back(sq.property), _shape.push_back(sq.pos); return *this; }
    Brick_base& pop_sq() { _properties.pop_back(), _shape.pop_back(); return *this; }
    Brick_base& clear() { _properties.clear(), _shape.clear(); return *this; }
    //Rotate functions
    Brick_base& rotate(Rotate_Direction d, int n_half_pi);
    //Handling Properties
    const vector<Square::Property>& properties() const {return _properties;}
    Brick_base& set_property(int index, Square::Property p) { _properties[index] = p; return *this; }
    //return the adjacent squares on the specific direction.
    vector<Coord>& adjacent(Linear_Direction d, vector<Coord> *output);
    vector<Coord> adjacent(Linear_Direction d);
    //all bricks but define their transform function
    virtual void transform() = 0;
private:
    //in the future, coord is usually used in calculation
    //for the convenience of loop through all coords, saperate coords from the square class
    vector<Square::Property> _properties;
    vector<Coord> _shape;
    Coord _pos = {0,0};
    bool _x_orient = false;
};

} //namespace Kenton

#endif // BLOCK_BASE_H
