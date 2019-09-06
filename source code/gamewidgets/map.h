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
    using Pixel = Square::Property;
    using size_type = std::size_t;
    using Matric_type = vector<deque<Pixel>>
    static const Pixel invalid_pixel;

    Map(size_type width, size_type height):
        width_(width), height_(height), matrix_(width, deque<Pixel>(height)) {}
    Map(const Map&) = default;
    Map(Map&&) = default;
    Map& operator=(const Map&) = default;
    Map& operator=(Map&&) = default;
    ~Map() = default;
    //Get/Set width
    size_type width() const { return width_; }
    size_type height() const { return height_; }
    void set_width(size_type width) {
        if (width < width_){
            matrix_.resize(width);
            width_ = width;
        }
        else if (width > width_) {
            matrix_.reserve(width);
            while (width_ < width) {
                matrix_.emplace_back(height_);
                width_++;
            }
        }
    }
    void set_height(size_type height) {
        for (auto& col: matrix_)
            col.resize(height);
        height_ = height;
    }
    //Get/Set sigle Pixel
    const Pixel& get(int x, int y) const {
        return is_valid_pos(x, y) ? matrix_[x][y] : invalid_pixel;
    }
    const Pixel& get(const Coord& c) const { return get(c.x, c.y); }
    void set(int x, int y, Pixel p) {
        if (is_valid_pos(x, y))
            matrix_[x][y] = p;
    }
    void set(const Coord &c, const Pixel& p) { set(c.x, c.y, p); }
    //Set multiple pixels
    void set_all(const Pixel& p) {
        for (auto& col: matrix_)
            for (auto& pixel: col)
                pixel = p;
    }

    template <typename CoordContainer>
    void set_all(const CoordContainer& c_list, const Pixel& p) {
        for (const auto &c: c_list)
            set(c, p);
        return *this;
    }
    //clean pixel (set them to empty_pixel)
    void clean(int x, int y) {
        set(x,y,empty_pixel);
    }
    void clean(const Coord& c) {
        clean(c.x, c.y);
    }
    //clean multiple pixel
    void clean_all() {
        set_all(empty_pixel);
    }

    template <typename CoordContainer>
    void clean_all(const CoordContainer& c_list) {
        set_all(c_list, empty_pixel);
    }
    //remove/add row/column
    void remove_row(int y) {
        for (auto &col: matrix_)
            col.erase(col.begin()+y);
    }
    void add_first_row() {
        for (auto &col: matrix_)
            col.push_front(empty_pixel);
    }
    void add_last_row() {
        for (auto &col: matrix_)
            col.push_back(empty_pixel);
    }
    void remove_col(int x) {
        matrix_.erase(matrix_.begin()+x);
    }
    void add_first_col() {
        matrix_.insert(matrix_.begin(), deque<Pixel>(height_));
    }
    void add_last_col() {
        matrix_.emplace_back(height_);
    }
    //Pixel verifiers
    //check whether there is a empty pixel
    static bool is_empty_pixel(const Pixel& p) {
        return p.type == Square::Type::EMPTY;
    }
    static bool is_invalid_pixel(const Pixel& p) {
        return p.type == Square::Type::INVALID;
    }
    //check if the position valid
    bool is_valid_pos(int x, int y) const {
        return x>=0 && x<width_ &&
               y>=0 && y<height_;
    }
    bool is_valid_pos(const Coord& c) const {
        return is_valid_pos(c.x, c.y);
    }
    //verify the validity of a series of position
    template <typename CoordInputIter>
    bool are_valid_pos(CoordInputIter first, CoordInputIter last) const {
        return std::all_of(first, last,
                           [this](const Coord& c){ return is_valid_pos(c); });
    }

    template <typename CoordContainer>
    bool are_valid_pos(const CoordContainer &c_list) const {
        return are_valid_pos(c_list.begin(), c_list.end());
    }

    template <typename CoordInputIter>
    bool are_all(CoordInputIter first, CoordInputIter last, const Pixel& p) const {
        return std::all_of(first, last,
                           [this, &p](const Coord& c) { get(c) == p; });
    }

    template <typename CoordContainer>
    bool are_all(const CoordContainer& c_list, const Pixel& p) const {
        return are_all(c_list.begin(), c_list.end(), p);
    }

    bool is_empty(int x, int y) const { return !is_valid_pos(x, y) || is_empty_pixel(matrix_[x][y]); }
    bool is_empty(const Coord& c) const { return is_empty(c.x, c.y); }

    template <typename CoordInputIter>
    bool are_empty(CoordInputIter first, CoordInputIter last) const {
        return std::are_all(first, last,
                            [this](const Coord& c){ is_empty(c); });
    }

    template <typename CoordContainer>
    bool are_empty(const CoordContainer& c_list) const {
        return are_empty(c_list.begin(), c_list.end());
    }
    //this is an abrupt but useful function _(:3 」 ∠)_
    bool row_is_filled(int y) {
        for (const auto &col: matrix_)
            if (is_empty_pixel(col[y]))
                return false;
        return true;
    }
private:
    static const Pixel empty_pixel;

    size_type width_, height_;
    Matrix_type matrix_;
};

} //namespace Kenton

#endif // MAP_H
