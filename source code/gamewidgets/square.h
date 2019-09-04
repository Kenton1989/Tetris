#ifndef SQUARE_H
#define SQUARE_H

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
    enum Type {EMPTY, WALL, BRICK, INVALID};
    struct Property{
        //can add color, pattern, etc. in the future.
        Type type = EMPTY;
        //functions
        Property () = default;
        Property (Type t): type(t) {}
        bool operator== (const Property& p) const {
            return type == p.type;
        }
        bool operator!= (const Property& p) const {
            return !(type == p.type);
        }
    };
    //coord is for calculating.
    //property is for painting.
    Coord pos;
    Property property;
    //construtor for convenience.
    Square () = default;
    Square (const Square&) = default;
    Square (int x, int y): pos(x, y) {}
    Square (int x, int y, Type t): pos(x, y), property(t) {}
    Square (int x, int y, Property p): pos(x, y), property(p) {}
    Square (Coord c, Property p): pos(c), property(p) {}
};

//define the iterator toward square.
using __it_Square = initializer_list<Square>::iterator;
//get a list of coords from a list of square
vector<Coord> get_coords (const __it_Square &b, const __it_Square &e);
//get a list of properties from a list of square
vector<Square::Property> get_properties (const __it_Square &b, const __it_Square &e);

} //namespace Kenton

#endif // SQUARE_H
