#ifndef CLOCK_H
#define CLOCK_H

#include <type_traits>
#include <ctime>

namespace Kenton {

struct TheSame_t {};
struct Devidable_t {};
struct Undevidable_t {};
template <int IntFrom, int IntTo, typename ResultType, typename ValueType>
ResultType unit_cast_impl(ValueType val, TheSame_t) { return val; }
template <int IntFrom, int IntTo, typename ResultType, typename ValueType>
ResultType unit_cast_impl(ValueType val, Devidable_t) {
    static constexpr int ratio = IntTo/IntFrom;
    return ratio*val;
}
template <int IntFrom, int IntTo, typename ResultType, typename ValueType>
ResultType unit_cast_impl(ValueType val, Undevidable_t) {
    static constexpr double ratio = double(IntTo)/IntFrom;
    return ratio*val;
}

template <bool condition, typename TrueResult, typename FalseResult>
using conditional_t = typename std::conditional<condition, TrueResult, FalseResult>::type;

template <int IntFrom, int IntTo,
          typename ResultType = conditional_t<IntTo%IntFrom, double, int>,
          typename ValueType = int,
          typename ValueRelation = conditional_t<IntTo%IntFrom, Undevidable_t,
                                                 conditional_t<IntFrom==IntTo, TheSame_t, Undevidable_t>>>
ResultType unit_cast(ValueType value) {
    return unit_cast_impl<IntFrom, IntTo, ResultType, ValueType>
            (value, ValueRelation());
}

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
    static int clocks_to_ms (int c) { return unit_cast<CLOCKS_PER_SEC, 1000>(c);}
    static int ms_to_clocks (int t) { return unit_cast<1000, CLOCKS_PER_SEC>(t);}
};

} //namespace Kenton

#endif // CLOCK_H
