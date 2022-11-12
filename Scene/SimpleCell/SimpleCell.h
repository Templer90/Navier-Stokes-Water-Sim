//
// Created by eric on 08.11.22.
//

#ifndef WATER_SIMPLECELL_H
#define WATER_SIMPLECELL_H

#include "../Scene.h"
#include "../../helper/ButtonKeys.h"
#include "../../Tile.h"
#include "../../helper/TileAction.h"

namespace Scene {
    class SimpleCell : public Scene {
    protected:
        helper::TileAction *actions;
        Tile **grid{};
        int editState = 0;
    public:
        SimpleCell();

        void HandleInputs(helper::ButtonKeys Keys) override;

        void Display(int FrameCounter) override;

        void ButtonDown(helper::ButtonKeys Keys, unsigned char key, int x, int y) override;

        void ButtonUp(helper::ButtonKeys Keys, unsigned char key, int x, int y) override;

        void mouseMove(helper::ButtonKeys Keys, int x, int y) override;

        void mouseDown(helper::ButtonKeys Keys, int button, int x, int y) override;

        void mouseUp(helper::ButtonKeys Keys, int button, int x, int y) override;

        void mouseClick(helper::ButtonKeys Keys, int button, int state, int x, int y) override;
    };
}


#endif //WATER_SIMPLECELL_H
