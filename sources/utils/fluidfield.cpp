#include "utils/fluidfield.h"

namespace AT {

    FluidField::FluidField()
    {

    }

    FluidField::~FluidField()
    {
        delete[] tempDensity;
    }

    void FluidField::SetGridSize(int Width, int Height)
    {
        fluidSolver.Init(Width, Height);
        VectorField::SetGridSize(Width, Height);

        // to keep density values
        tempDensity = new float[Width * Height];
    }

    void FluidField::AddVelocity(float x, float y, float u, float v)
    {
        int cx = int(x / cellWidth) + 1;
        int cy = int(y / cellHeight) + 1;

        fluidSolver.AddU(cx, cy, u);
        fluidSolver.AddV(cx, cy, v);
    }

    void FluidField::AddDensity(float x, float y, float d)
    {
        int cx = int(x / cellWidth);
        int cy = int(y / cellHeight);

        AddDensityCell(cx, cy, d);
    }

    void FluidField::AddDensityCell(int x, int y, float d)
    {
        fluidSolver.AddD(x + 1, y + 1, d);
    }

    void FluidField::StoreDensity(int x, int y, float d)
    {
        tempDensity[y * gridWidth + x] = d;
    }

    void FluidField::RestoreDensity(int x, int y)
    {
        AddDensityCell(x, y, tempDensity[y * gridWidth + x]);
    }

    sf::Vector2f& FluidField::GetVector(int cellX, int cellY)
    {
        static sf::Vector2f result;

        cellX %= gridWidth;
        while(cellX < 0)
            cellX += gridWidth;
        cellY %= gridHeight;
        while(cellY < 0)
            cellY += gridHeight;

        result.x = fluidSolver.GetU(cellX + 1, cellY + 1);
        result.y = fluidSolver.GetV(cellX + 1, cellY + 1);

        return result;
    }

    void FluidField::ClearMap()
    {
        for(int y = 0; y < gridHeight; ++y) {
            for(int x = 0; x < gridWidth; ++x) {
                SetMap(x, y, false);
            }
        } 
    }

    void FluidField::Update(float dt)
    {
        fluidSolver.VelocitySolver(dt);
        fluidSolver.DensitySolver(dt);
        fluidSolver.MaintainDensity(0.0f, 0.8f * dt);
    }
}