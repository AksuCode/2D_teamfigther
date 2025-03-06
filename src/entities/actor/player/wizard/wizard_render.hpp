#ifndef WIZARD_RENDER_HPP
#define WIZARD_RENDER_HPP

#include "MGL/include/sprite_render.hpp"

#include "../../actor_render.hpp"

class WizardRender : public ActorRender {
    public:
        WizardRender(GameWindow * gw, const char bmp_path[]  = "./assets/sprites/wizard/default.bmp");
        ~WizardRender();
};

#endif