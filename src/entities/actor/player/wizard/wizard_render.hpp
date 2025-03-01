#ifndef WIZARD_RENDER_HPP
#define WIZARD_RENDER_HPP

#include "MGL/include/sprite_render.hpp"

#include "../../actor_render.hpp"

class WizardRender : ActorRender {
    public:
        WizardRender(const GameWindow * gw, const char * bmp_path);
        ~WizardRender();

        void renderActor();

    private:
        // Map the amount of sprites per action. For example with action numbered 4, the number of sprites for that action is sprite_amount_per_action_mapping_[4] = number of sprites.
        constexpr const int sprite_amount_per_action_mapping_[] = {
            5,
            5,
            5,
            5
        }
};

#endif