//
// Created by eric on 07.11.22.
//

#ifndef WATER_BUTTONKEYS_H
#define WATER_BUTTONKEYS_H

namespace helper{
    struct ButtonKeys {
        int esc;
        int mouseL;
        int mouseM;
        int mouseR;
        int mouseMove;

        int mouseX;
        int mouseY;
    };
    enum MouseButtons {
        L = 0,
        M = 1,
        R = 2
    };
}


#endif //WATER_BUTTONKEYS_H
