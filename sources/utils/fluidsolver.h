#ifndef _FLUID_SOLVER_H
#define _FLUID_SOLVER_H

#include <cmath>

#include "utils/helper.h"

#define I(i,j) (((j) * (width + 2)) + (i))

namespace AT {

    // from http://www.multires.caltech.edu/teaching/demos/java/stablefluids.htm

    class FluidSolver
    {
    private:
        int width, height;
        int size;

        float visc;
        float diff;

        float *tmp;

        float *d, *dOld;
        float *u, *uOld;
        float *v, *vOld;
        float *curl;
        bool *map;

        void Destroy();

        void AddSource(float *a, float *a0, float dt);
        void Boundary(int b, float *a);
        void LinearSolver(int b, float *arr, float *arr0, float a, float c);

        inline void SwapU() { tmp = u; u = uOld; uOld = tmp; }
        inline void SwapV() { tmp = v; v = vOld; vOld = tmp; }
        inline void SwapD() { tmp = d; d = dOld; dOld = tmp; }
    public:
        FluidSolver();
        ~FluidSolver();

        void Init(int Width, int Height);
        void Reset();

        inline float GetU(int x, int y)
        { return u[I(x, y)]; }
        inline float GetV(int x, int y)
        { return v[I(x, y)]; }
        inline float GetD(int x, int y)
        { return d[I(x, y)]; }

        inline void AddU(int x, int y, float u)
        { uOld[I(x, y)] += u; }
        inline void AddV(int x, int y, float v)
        { vOld[I(x, y)] += v; }
        inline void AddD(int x, int y, float d)
        {
            int i = I(x, y);
            dOld[i] += d;
            /*if(dOld[i] < 0.0f)
                dOld[i] = 0.0f;
            if(dOld[i] > 1.0f)
                dOld[i] = 1.0f;*/
        }

        inline bool Get(int x, int y)
        { return map[I(x, y)]; }
        inline void Set(int x, int y, bool v)
        { map[I(x, y)] = v; }

        /*
         * Calculate the curl at position (i, j) in the fluid grid.
         * Physically this represents the vortex strength at the
         * cell. Computed as follows: w = (del x U) where U is the
         * velocity vector at (i, j).
         */
        float Curl(int i, int j) const;

        /*
         * Calculate the vorticity confinement force for each cell
         * in the fluid grid. At a point (i,j), Fvc = N x w where
         * w is the curl at (i,j) and N = del |w| / |del |w||.
         * N is the vector pointing to the vortex center, hence we
         * add force perpendicular to N.
         */
        void VorticityConfinement(float *vX, float *vY);

        /*
         * Calculate the input array after advection. We start with an
         * input array from the previous timestep and an and output array.
         * For all grid cells we need to calculate for the next timestep,
         * we trace the cell's center position backwards through the
         * velocity field. Then we interpolate from the grid of the previous
         * timestep and assign this value to the current grid cell.
         */
        void Advect(int b, float *arr, float *arr0, float *du, float *dv, float dt);

        /*
         * Recalculate the input array with diffusion effects.
         * Here we consider a stable method of diffusion by
         * finding the densities, which when diffused backward
         * in time yield the same densities we started with.
         * This is achieved through use of a linear solver to
         * solve the sparse matrix built from this linear system.
         */
        void Diffuse(int b, float *arr, float *arr0, float diff, float dt);

        /*
         * Use project() to make the velocity a mass conserving,
         * incompressible field. Achieved through a Hodge
         * decomposition. First we calculate the divergence field
         * of our velocity using the mean finite differnce approach,
         * and apply the linear solver to compute the Poisson
         * equation and obtain a "height" field. Now we subtract
         * the gradient of this field to obtain our mass conserving
         * velocity field.
         */
        void Project(float *x, float *y, float *p, float *div);

        /*
         * The basic velocity solving routine as described by Stam.
         */
        void VelocitySolver(float dt);

        /*
         * The basic density solving routine.
         */
        void DensitySolver(float dt);

        /*
         * Try to maintain a constant density over time
         */
        void MaintainDensity(float densityRest, float changeRate);
    };

}

#undef I

#endif
