#ifndef _VECTOR_FIELD_H
#define _VECTOR_FIELD_H

#include <SFML/Graphics.hpp>

namespace AT {

    class VectorField
    {
    protected:
        int width, height;
        float cellWidth, cellHeight;

        int gridWidth, gridHeight;

        sf::Vector2f *vectors;
        void Clear();
    public:
        VectorField();
        virtual ~VectorField();

        virtual void SetSize(int Width, int Height);
        virtual void SetGridSize(int GridWidth, int GridHeight);
        
        int GetWidth() const
        { return width; }
        int GetHeight() const
        { return height; }
        float GetCellWidth() const
        { return cellWidth; }
        float GetCellHeight() const
        { return cellHeight; }
        int GetGridWidth() const
        { return gridWidth; }
        int GetGridHeight() const
        { return gridHeight; }

        void Reset();
        void InitRandom();

        virtual sf::Vector2f& GetVector(int cellX, int cellY);
        sf::Vector2f Interpolate(float x, float y);
    };
}

#endif
