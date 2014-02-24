#ifndef _FLUID_FIELD_H
#define _FLUID_FIELD_H

#include <SFML/Graphics.hpp>

#include "utils/vectorfield.h"
#include "utils/fluidsolver.h"

namespace AT {

    class FluidField : public VectorField
    {
    protected:
        FluidSolver fluidSolver;

        float *tempDensity;
    public:
        FluidField();
        virtual ~FluidField();

        void SetGridSize(int Width, int Height);
        
        void AddVelocity(float x, float y, float u, float v);
        void AddDensity(float x, float y, float d);
        void AddDensityCell(int x, int y, float d);

        void StoreDensity(int x, int y, float d);
        void RestoreDensity(int x, int y);

        inline float GetDensity(int x, int y)
        { return fluidSolver.GetD(x + 1, y + 1); }
        inline float GetDensity(float x, float y)
        {
            int cx = int(x / cellWidth);
            int cy = int(y / cellHeight);
            return GetDensity(cx, cy);
        }

        inline bool GetMap(float x, float y)
        {
            int cx = int(x / cellWidth);
            int cy = int(y / cellHeight);
            return GetMap(cx, cy);
        }
        inline bool GetMap(int x, int y)
        { return fluidSolver.Get(x + 1, y + 1); }
        inline void SetMap(float x, float y, bool v)
        {
            int cx = int(x / cellWidth);
            int cy = int(y / cellHeight);
            SetMap(cx, cy, v);
        }
        inline void SetMap(int x, int y, bool v)
        { fluidSolver.Set(x + 1, y + 1, v); }
        inline void ToggleMap(float x, float y)
        {
            int cx = int(x / cellWidth);
            int cy = int(y / cellHeight);
            ToggleMap(cx, cy);
        }
        inline void ToggleMap(int x, int y)
        {
            x += 1;
            y += 1;
            fluidSolver.Set(x, y, !fluidSolver.Get(x, y));
        }
        void ClearMap();

        sf::Vector2f& GetVector(int cellX, int cellY);
        void Update(float dt);
    };
}

#endif
