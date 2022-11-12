//
// Created by eric on 08.11.22.
//

#ifndef WATER_SCENELIST_H
#define WATER_SCENELIST_H

#include <vector>
#include <cstdarg>
#include "Scene.h"

namespace Scene {

    class SceneList {
    private:
        unsigned index;
        std::vector<Scene *> list = {};
    public:
        SceneList(std::initializer_list<Scene *> scenes) {
            index = 0;
            for (auto elem: scenes) {
                list.push_back(elem);
            }

        }

        SceneList &operator++() {
            index = (index + 1) % list.size();
            return *this;
        }

        SceneList &operator--() {
            if (index == 0) { index = list.size() - 1; } else { index--; }
            return *this;
        }

        SceneList operator++(int) {
            SceneList old = *this;
            operator++();
            return old;
        }

        SceneList operator--(int) {
            SceneList old = *this;
            operator--();
            return old;
        }

        Scene *current() {
            return list[index];
        }
    };


} // Scene

#endif //WATER_SCENELIST_H
