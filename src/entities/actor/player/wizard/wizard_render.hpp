#ifndef WIZARD_RENDER_HPP
#define WIZARD_RENDER_HPP

#include <utility>

#include "MGL/include/sprite_render.hpp"

#include "../../actor_render.hpp"

class WizardRender : ActorRender {
    public:
        WizardRender(const GameWindow * gw, const char * bmp_path);
        ~WizardRender();
};

#endif