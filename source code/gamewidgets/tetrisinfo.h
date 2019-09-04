#ifndef TETRISINFO_H
#define TETRISINFO_H

namespace Kenton {

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

} //namespace Kenton

#endif // TETRISINFO_H
