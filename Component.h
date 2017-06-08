#ifndef COMPONENT_H
#define COMPONENT_H

namespace pzr
{
    class Component
    {
    public:
        Component() {};
        virtual ~Component() {};
        void update() {};
    };
} // ns pzr

#endif COMPONENT_H