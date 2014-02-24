#ifndef _FLOW_H
#define _FLOW_H

#include <vector>

namespace AT {

    class Flow
    {
    public:
        struct Velocity
        {
            float x, y;
            float u, v;
        };
        typedef std::vector<Velocity> Velocities;
    private:
        Velocities velocities;
    public:
        Flow() {}
        ~Flow() {}

        void Clear()
        { velocities.clear(); }
        void Add(Velocity Velocity)
        { velocities.push_back(Velocity); }
        const Velocities& GetVelocities() const
        { return velocities; }
    };
}

#endif