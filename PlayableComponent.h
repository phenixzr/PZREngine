#ifndef PLAYABLE_COMPONENT_H
#define PLAYABLE_COMPONENT_H

#include "InputComponent.h"

namespace pzr
{
    class PlayableComponent : public InputComponent
    {
    public:
        PlayableComponent();
        ~PlayableComponent();
    private:
        void processInput(GameObject* gameObject) override;
    };
}

#endif // !PLAYABLE_COMPONENT_H


