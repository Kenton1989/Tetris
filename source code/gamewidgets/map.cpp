#include "map.h"
namespace Kenton {

const Map::Pixel Map::empty_pixel = Square::EMPTY;
const Map::Pixel Map::invalid_pixel = Square::INVALID;

void TetrisInfo::reset() {
    _step = 5;
    _counter = 0;
    _score = 0;
    _level = 1;
    _rate = 1000; //unit ms;
}


void TetrisInfo::increase(int n) {
    _counter += n;
    _score += n*_level;
    if (_counter > _level*_step) {
        ++_level;
        _rate = std::max(int(1000*(1 - 0.2*_level)), 1000/_level);
        _counter = 0;
    }
}

} //namespace Kenton
