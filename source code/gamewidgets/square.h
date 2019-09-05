#ifndef SQUARE_H
#define SQUARE_H

#include <algorithm>
#include <iterator>
#include <type_traits>
#include <vector>

namespace Kenton {

using std::vector;

struct Coord {
    //    x --->
    //  y
    //  |
    //  V
    int x = 0, y = 0;
    Coord() = default;
    Coord(const Coord& c) = default;
    Coord(int x0, int y0): x(x0), y(y0) {}
};

struct Square {
    //used to define the apperance of square.
    enum class Type {INVALID=-1, EMPTY, WALL, BRICK};
    struct Property{
        //can add color, pattern, etc. in the future.
        Type type = Type::EMPTY;
        //functions
        Property () = default;
        Property (const Property&) = default;
        Property& operator= (const Property&) = default;
        Property (Type t): type(t) {}
        bool operator== (const Property& p) const { return type == p.type; }
        bool operator!= (const Property& p) const { return !(type == p.type); }
    };
    //coord is for calculating.
    //property is for painting.
    Coord pos;
    Property property;
    //construtor for convenience.
    Square () = default;
    Square (const Square&) = default;
    Square& operator=(const Square&) = default;
    //other constuctor
    Square (int x, int y): pos(x, y) {}
    Square (int x, int y, Type t): pos(x, y), property(t) {}
    Square (int x, int y, Property p): pos(x, y), property(p) {}
    Square (Coord c, Property p): pos(c), property(p) {}
};

template <typename SquareInputIter>
struct __isSquareInputIter {
    static constexpr bool value =
            std::is_base_of<std::input_iterator_tag,
                            typename std::iterator_traits<SquareInputIter>::iterator_category>::value &&
            std::is_base_of<Square, decltype(*(SquareInputIter()))>::value;
};

//get a list of coords from a list of square
template <typename outputContainerType = std::vector<Coord>,
          typename SquareInputIter = std::initializer_list<Coord>,
          typename = typename std::enable_if<__isSquareInputIter<SquareInputIter>>::type
          >
outputContainerType get_coords (SquareInputIter first, SquareInputIter last) {
    outputContainerType coords;
    std::transform(first, last, std::back_inserter(coords),
                   [](const Square& sq) { return sq.pos; });
    return coords;
}

//get a list of properties from a list of square
template <typename outputContainerType = std::vector<Square::Property>,
          typename SquareInputIter = std::initializer_list<Coord>,
          typename = typename std::enable_if<__isSquareInputIter<SquareInputIter>>::type
          >
outputContainerType get_properties (SquareInputIter first, SquareInputIter last) {
    outputContainerType properties;
    std::transform(first, last, std::back_inserter(properties),
                   [](const Square& sq) { return sq.property; });
    return properties;
}

} //namespace Kenton

#endif // SQUARE_H
