#ifndef CLOCK_H
#define CLOCK_H


namespace Kenton {

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
    int clocks_to_ms (int c) { return /*1000.0/CLOCKS_PER_SEC*/c;}
    int ms_to_clocks (int t) { return /*CLOCKS_PER_SEC/1000.0*/t;}
};

} //namespace Kenton

#endif // CLOCK_H
