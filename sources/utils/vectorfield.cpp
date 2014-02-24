#include "utils/vectorfield.h"

namespace AT {

    VectorField::VectorField()
        :width(0), height(0), cellWidth(0), cellHeight(0), gridWidth(1), gridHeight(1), vectors(NULL)
    {
        
    }

    VectorField::~VectorField()
    {
        Clear();
    }

    void VectorField::Clear()
    {
        delete[] vectors;
        vectors = NULL;
    }

    void VectorField::SetSize(int Width, int Height)
    {
        width = Width;
        height = Height;

        SetGridSize(gridWidth, gridHeight);
    }

    void VectorField::SetGridSize(int GridWidth, int GridHeight)
    {
        gridWidth = GridWidth;
        gridHeight = GridHeight;

        cellWidth = float(width) / gridWidth;
        cellHeight = float(height) / gridHeight;
        
        Clear();
        vectors = new sf::Vector2f[gridWidth * gridHeight];
        Reset();
    }

    void VectorField::Reset()
    {
        for(int i = 0; i < gridWidth * gridHeight; ++i) {
            sf::Vector2f& v = vectors[i];
            v.x = 0.0f;
            v.y = 0.0f;
        }
    }

    void VectorField::InitRandom()
    {
        for(int i = 0; i < gridWidth * gridHeight; ++i) {
            sf::Vector2f& v = vectors[i];
            v.x = sf::Randomizer::Random(-2.0f, +2.0f);
            v.y = sf::Randomizer::Random(-2.0f, +2.0f);
        }
    }

    sf::Vector2f& VectorField::GetVector(int cellX, int cellY)
    {
        cellX %= gridWidth;
        while(cellX < 0)
            cellX += gridWidth;
        cellY %= gridHeight;
        while(cellY < 0)
            cellY += gridHeight;

        return vectors[cellY * gridWidth + cellX];
    }

    sf::Vector2f VectorField::Interpolate(float x, float y)
    {
        int cx1 = int(x / cellWidth);
        int cy1 = int(y / cellHeight);
        int cx2 = cx1 + 1;
        int cy2 = cy1 + 1;

        float x1 = cx1 * cellWidth;
        float y1 = cy1 * cellHeight;
        float x2 = cx2 * cellWidth;
        float y2 = cy2 * cellHeight;

        // Bilinear interpolation
        // Weights
        float divWeight = 1.0f / ((x2 - x1) * (y2 - y1));
        float w11 = ((x2 - x) * (y2 - y)) * divWeight;
        float w21 = ((x - x1) * (y2 - y)) * divWeight;
        float w12 = ((x2 - x) * (y - y1)) * divWeight;
        float w22 = ((x - x1) * (y - y1)) * divWeight;

        // Result
        sf::Vector2f result(0.0f, 0.0f), temp;
        temp = GetVector(cx1, cy1); temp *= w11; result += temp;
        temp = GetVector(cx2, cy1); temp *= w21; result += temp;
        temp = GetVector(cx1, cy2); temp *= w12; result += temp;
        temp = GetVector(cx2, cy2); temp *= w22; result += temp;

        return result;
    }
}