#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "conio.h"
namespace Kenton {

class Keyboard {
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

} //namespace Kenton

#endif // KEYBOARD_H
