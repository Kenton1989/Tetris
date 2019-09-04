#include "square.h"
namespace Kenton {

//get a list of coords from a list of square
vector<Coord> get_coords (const __it_Square &b, const __it_Square &e) {
    vector<Coord> v;
    for(auto i = b; i != e; ++i)
        v.push_back(i->pos);
    return v;
}

//get a list of properties from a list of square
vector<Square::Property> get_properties (const __it_Square &b, const __it_Square &e) {
    vector<Square::Property> v;
    for(auto i = b; i != e; ++i)
        v.push_back(i->property);
    return v;
}

} //namespace Kenton
