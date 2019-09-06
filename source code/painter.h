#ifndef PAINTER_H
#define PAINTER_H

namespace Kenton {

class Painter {
public:
    Painter(int map_w, int map_h): _map_w(map_w), _px_map_w(map_w*2), _map_h(map_h), _next_brick_pos(_map_w+2, 3)  {
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
}

#endif // PAINTER_H
