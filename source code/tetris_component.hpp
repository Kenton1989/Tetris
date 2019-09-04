#ifndef TETRIS_COMPONENT_HPP
#define TETRIS_COMPONENT_HPP

#include <ctime>
#include <vector>
#include <deque>
#include <iterator>
#include <initializer_list>
#include <iostream>

#include "conio.h"
#include "windows.h"

using std::cout;
using std::deque;
using std::endl;
using std::forward_iterator_tag;
using std::initializer_list;
using std::iterator;
using std::vector;

namespace Kenton {

enum Linear_Direction { UP, DOWN, LEFT, RIGHT };
enum Rotate_Direction { CLOCKWISE, COUNTERCLOCKWISE };
/*
struct Coord {
    //  0 x --->
    //  y
    //  |
    //  V
    int x = 0, y = 0;
    Coord() = default;
    Coord(const Coord& c) = default;
    Coord(int x0, int y0): x(x0), y(y0) {}
};
*/
//struct Square;
class Brick;
class Map;
class TetrisInfo;

class Clock;
class KeyboardInput;
class Screen;
/*
struct Square {
    //used to define the apperance of square.
    enum Type {EMPTY, WALL, BRICK, INVALID};
    struct Property{
        //can add color, pattern, etc. in the future.
        Type type = EMPTY;
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
using it_Square = initializer_list<Square>::iterator ;
//get a list of coords from a list of square
vector<Coord> get_coords (const it_Square &b, const it_Square &e);
//get a list of properties from a list of square
vector<Square::Property> get_properties (const it_Square &b, const it_Square &e);
*/
/*
class Brick {
public:
    Brick() = default;
    Brick(const Brick&) = default;
    Brick(initializer_list<Square> l): _properties(get_properties(l.begin(), l.end())),
                                       _shape(get_coords(l.begin(), l.end())) {}

    int orientation() const { return _orientation; }
    Brick& set_orientation(int n) {
        switch (n) {
        case 1:
            rotate_default = rotate_back_default = &rotate_1o;

            break;
        case 2:
            rotate_default = rotate_back_default = &rotate_2o;
            break;
        case 4:
            rotate_default = &rotate_4o;
            rotate_back_default = &rotate_back_4o;
            break;
        default:
            return *this;
        }
        _orientation = n;
        return *this;
    }
    int size() { return _shape.size(); }
    //Handling the postion of brick
    const Coord pos() const { return _pos; }
    Brick& set_pos(int x, int y) { _pos.x = x, _pos.y = y; return *this; }
    Brick& set_pos(Coord c) { _pos = c; return *this; }
    Brick& move_by(int dx, int dy) { _pos.x += dx, _pos.y += dy; return *this; }
    Brick& move_by(Linear_Direction d, int step = 1);
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
    Brick& append_sq(const Square& sq) { _properties.push_back(sq.property), _shape.push_back(sq.pos); return *this; }
    Brick& pop_sq() { _properties.pop_back(), _shape.pop_back(); return *this; }
    Brick& clear() { _properties.clear(), _shape.clear(); return *this; }
    //Rotate functions
    Brick& rotate(Rotate_Direction d, int n_half_pi);
    Brick& rotate() { return (this->*rotate_default)(); }
    Brick& rotate_back() { return (this->*rotate_back_default)(); }
    //Handling Properties
    const vector<Square::Property>& properties() const {return _properties;}
    Brick& set_property(int index, Square::Property p) { _properties[index] = p; return *this; }
    //return the adjacent squares on the specific direction.
    vector<Coord>& adjacent(Linear_Direction d, vector<Coord> *output);
    vector<Coord> adjacent(Linear_Direction d);
private:
    //in the future, coord is usually used in calculation
    //for the convenience of loop through all coords, saperate coords from the square class
    vector<Square::Property> _properties;
    vector<Coord> _shape;
    Coord _pos = {0,0};
    int _orientation = 4;
    bool _x_orient = false;

    Brick& rotate_4o() { return rotate(CLOCKWISE, 1); }
    Brick& rotate_back_4o() { return rotate(CLOCKWISE, 3); }
    Brick& rotate_2o() {
        _x_orient = !_x_orient;
        if(_x_orient)
            return rotate(CLOCKWISE, 1);
        else
            return  rotate(CLOCKWISE, 3);
    }
    Brick& rotate_1o() { return *this; }
    decltype(&rotate_4o) rotate_default = &rotate_4o; //default rotate function, will very for diffent bricks
    decltype(&rotate_4o) rotate_back_default = &rotate_back_4o; //default rotate function, will very for diffent bricks
};
*/
/*
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
    vector< deque<Pixel> > _matrix;
    bool is_empty_pixel(const Pixel& p) const {
        return p.type == Square::Type::EMPTY;
    }
};
*/
/*
class TetrisInfo {
public:
    int score() const { return _score; }
    int level() const  { return _level; }
    int rate()  const  { return _rate; }
    const Brick& next_brick()  const  { return _next; }
    void set_next_brick(const Brick& b) { _next = b; }

    void reset();
    void increase(int n = 1);
private:
    int _step = 5;
    int _counter = 0;
    int _score = 0;
    int _level = 1;
    int _rate = 1000; //unit ms;
    Brick _next;
};
*/
/*
class Clock {
public:
    void set_timer(int t) {
        _clocks_end = clock()+ms_to_clocks(t);
    }
    int timer_rest() {
        return clocks_to_ms(_clocks_end - time(0));
    }
    bool times_up() {
        return clock()>=_clocks_end;
    }
    void set_stop_watch() {
        _clocks_beg = clock();
    }
    int counted_time() {
        return clocks_to_ms(clock()-_clocks_beg);
    }
private:
    int _clocks_beg = 0;
    int _clocks_end = 0;
    //for my lience, CLOCKS_PER_SEC == 1000
    int clocks_to_ms (int c) { return /*1000.0/CLOCKS_PER_SEC*  /c;}
    int ms_to_clocks (int t) { return /*CLOCKS_PER_SEC/1000.0* /t;}
};
*/
/*
class KeyboardInput {
public:
    enum Key_id {
        UP_ARROW = 224 + (72 << 8),
        DOWN_ARROW = 224 + (80 << 8),
        LEFT_ARROW = 224 + (75 << 8),
        RIGHT_ARROW = 224 + (77 << 8)
    };
    int get_input() {
        if (kbhit()) {
            int ret = getch();
            if (ret == 224)
                ret += getch() << 8;
            return ret;
        }
        return 0;
    }
    bool has_input() {
        return kbhit();
    }
};
*/
class Screen {
public:
    Screen(int map_w, int map_h): _map_w(map_w), _px_map_w(map_w*2), _map_h(map_h), _next_brick_pos(_map_w+2, 3)  {
        //hide consor
        CONSOLE_CURSOR_INFO cci;
        GetConsoleCursorInfo(_hOut,&cci);
        cci.bVisible=false;
        SetConsoleCursorInfo(_hOut,&cci);
        //set the size of console
        system(("mode con cols="+std::to_string(_px_map_w+20)+" lines="+std::to_string(_map_h+2)).c_str());
    }
    void clean(int x, int y, int w, int h) {
        for (--h; h >= 0; --h) {
            set_consor_pos(x, y+h);
            for (int counter = w; counter > 0; --counter)
                cout << ' ';
        }
    }
    void set_consor_pos(short x, short y) {
        SetConsoleCursorPosition(_hOut,{x, y});
    }
    void print(const Square::Property& p) {
        switch (p.type) {
        case Square::EMPTY:
            cout << ' ' << ' ';
            break;
        case Square::WALL:
            cout << '/' << '/';
            break;
        case Square::BRICK:
            cout << '[' << ']';
            break;
        default:
            break;
        }
    }
    void print(const TetrisInfo& info) {
        set_consor_pos(_px_map_w, 0);
        cout << "Next:";
        set_consor_pos(_px_map_w, 7);
        cout << "Level: " << info.level();
        set_consor_pos(_px_map_w, 8);
        cout << "Score: " << info.score();
        clean(_px_map_w, 1, 10, 6);
        print_brick_base(info.next_brick().shape(_next_brick_pos), info.next_brick().properties(), false);
    }
    void print_pause(bool pause) {
        set_consor_pos(_px_map_w, 10);
        cout << (pause ? "PAUSE" : "     ");
    }
    void print(const Map& m) {
        set_consor_pos(0,0);
        for (int y = 0; y < m.height(); ++y) {
            for (int x = 0; x < m.width(); ++x) {
                print(m.get(x, y));
            }
            cout << endl;
        }
    }
    void print(const Brick& b) {
        print_brick_base(b.shape(true), b.properties(), true);
    }
    void print_gameover() {
        set_consor_pos(std::max(_px_map_w/2-5, 0), std::max(_map_h/2-1, 0));
        cout << " GAME OVER ";
    }
private:
    HANDLE _hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    int _map_w, _px_map_w, _map_h;
    Coord _next_brick_pos;
    bool invalid_brick_pos(const Coord& c) {
        return c.x<0 || c.x>=_map_w ||
               c.y<0 || c.y>=_map_h;
    }

    void print_brick_base(const vector<Coord> &shape, const vector<Square::Property> &properties, bool need_validate) {
        int i = 0;
        for (const auto& pos: shape) {
            if(need_validate && invalid_brick_pos(pos))
                continue;
            set_consor_pos(pos.x*2, pos.y);
            print(properties[i]);
            ++i;
        }
    }
};

} //namespace Kenton

#endif // TETRIS_COMPONENT_HPP
