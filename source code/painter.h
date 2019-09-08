#ifndef PAINTER_H
#define PAINTER_H

#include "gamewidgets/all.h"
#include <algorithm>
#include <iostream>
#include <string>
#include "windows.h"

namespace Kenton {

using std::cout;
using std::endl;

class Painter {
public:
    Painter(int map_w, int map_h):
        map_w_(map_w), map_h_(map_h), px_map_w_(map_w*2),
        console_w_(px_map_w_+20), console_h_(map_h_+2),
        next_brick_pos_(map_w_+2, 3)  {
        //hide consor
        CONSOLE_CURSOR_INFO cci;
        GetConsoleCursorInfo(_hOut,&cci);
        cci.bVisible=false;
        SetConsoleCursorInfo(_hOut,&cci);
        //set the size of console
        system(("mode con cols="+std::to_string(console_w_)+" lines="+std::to_string(console_h_)).c_str());
    }
    void print(const Brick& b) {
        print_brick_base(b.shape_abs(), b.properties(), true);
    }
    void print(shared_ptr<const Brick> pb) {
        print_brick_base(pb->shape_abs(), pb->properties(), true);
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
    void print(const TetrisInfo& info) {
        set_consor_pos(px_map_w_, 0);
        cout << "Next:";
        set_consor_pos(px_map_w_, 7);
        cout << "Level: " << info.level();
        set_consor_pos(px_map_w_, 8);
        cout << "Score: " << info.score();
        clean(px_map_w_, 1, 10, 6);
        print_brick_base(info.next_brick().shape_at(next_brick_pos_), info.next_brick().properties(), false);
    }
    void print_pause(bool pause = true) {
        set_consor_pos(px_map_w_, 10);
        cout << (pause ? "PAUSE" : "     ");
    }
    void print_gameover() {
        static std::string gameOverMsg(" GAME OVER ");
        set_consor_pos(std::max((px_map_w_-gameOverMsg.size())/2, 0u), std::max(map_h_/2-1, 0));
        cout << gameOverMsg;
        set_consor_pos(0, map_h_);
    }
private:
    HANDLE _hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    int map_w_, map_h_, px_map_w_,
        console_w_, console_h_;
    Coord next_brick_pos_;

    bool invalid_brick_pos(const Coord& c) {
        return c.x<0 || c.x>=map_w_ ||
               c.y<0 || c.y>=map_h_;
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
    bool set_consor_pos(short x, short y) {
        if (!is_valid_pos(x, y))
            return false;
        SetConsoleCursorPosition(_hOut,{x, y});
        return true;
    }
    bool is_valid_pos(int x, int y) {
        return x>=0 && x<console_w_ &&
               y>=0 && y<console_h_;
    }
    void clean(int x, int y, int w, int h) {
        if (!is_valid_pos(x,y))
            return;
        w = std::min(w, console_w_-x);
        for (--h; h >= 0; --h) {
            if (!set_consor_pos(x, y+h))
                continue;
            for (int counter = w; counter > 0; --counter)
                cout << ' ';
        }
    }
    void print(const Square::Property& p) {
        switch (p.type) {
        case Square::Type::EMPTY:
            cout << ' ' << ' ';
            break;
        case Square::Type::WALL:
            cout << '/' << '/';
            break;
        case Square::Type::BRICK:
            cout << '[' << ']';
            break;
        default:
            break;
        }
    }
};
}

#endif // PAINTER_H
