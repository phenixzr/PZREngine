#ifndef COMPONENT_H
#define COMPONENT_H

#include "GameObject.h"

namespace pzr
{
    class Component
    {
    public:
        Component() {};
        virtual ~Component() {};
        virtual void update(GameObject* gameObject) = 0;
    };
} // ns pzr

#endif COMPONENT_H