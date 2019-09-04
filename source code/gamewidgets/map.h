#ifndef MAP_H
#define MAP_H
#include "square.h"
#include <deque>
#include <vector>

namespace Kenton {

using std::vector;
using std::deque;

class Map {
public:
    typedef Square::Property Pixel;
    static const Pixel invalid_pixel;

    Map(int width, int height): _width(width), _height(height), _matrix(width, deque<Pixel>(height)) {}

    int width() const { return _width; }
    int height() const { return _height; }
    bool is_valid_pos(int x, int y) const {
        return x>=0 && x<_width &&
               y>=0 && y<_height;
    }
    bool is_valid_pos(const Coord& c) const {
        return is_valid_pos(c.x, c.y);
    }
    bool are_valid_pos(const vector<Coord> &c_list) const {
        for (const auto &c: c_list)
            if (!is_valid_pos(c))
                return false;
        return true;
    }
    const Pixel& get(int x, int y) const { return is_valid_pos(x, y) ? _matrix[x][y] : invalid_pixel; }
    const Pixel& get(Coord c) const { return get(c.x, c.y);}
    Map& set(int x, int y, Pixel p) {
        if (is_valid_pos(x, y))
            _matrix[x][y] = p;
        return *this;
    }
    Map& set(const Coord &c, Pixel p) { return set(c.x, c.y, p); }
    Map& set_all(const vector<Coord> & c_list, Pixel p) {
        for (const auto &c: c_list)
            set(c, p);
        return *this;
    }
    Map& clean() {
        for (auto &col: _matrix)
            for (auto &p: col)
                p = empty_pixel;
        return *this;
    }
    Map& clean_row(int y) {
        for (auto &col: _matrix){
            col.erase(col.begin()+y);
            col.push_front(empty_pixel);
        }
        return *this;
    }

    bool are_all(const vector<Coord>& c_list, const Pixel& p) const {
        for (const auto &c: c_list)
            if (get(c) != p)
                return false;
        return true;
    }
    bool is_empty(int x, int y) const { return !is_valid_pos(x, y) || is_empty_pixel(_matrix[x][y]); }
    bool is_empty(const Coord& c) const { return is_empty(c.x, c.y); }
    bool are_empty(const vector<Coord>& c_list) const {
        for (const auto& c: c_list) {
            if (!is_empty(c))
                return false;
        }
        return true;
    }
    bool row_is_filled(int y) {
        for (const auto &col: _matrix)
            if (is_empty_pixel(col[y]))
                return false;
        return true;
    }
private:
    static const Pixel empty_pixel;
    int _width, _height;
    vector<deque<Pixel>> _matrix;
    bool is_empty_pixel(const Pixel& p) const {
        return p.type == Square::Type::EMPTY;
    }
};

} //namespace Kenton

#endif // PIXEL_MAP_H
