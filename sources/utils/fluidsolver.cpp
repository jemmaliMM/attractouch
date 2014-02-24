#include "utils/fluidsolver.h"

namespace AT {

#define I(i,j) (((j) * (width + 2)) + (i))

    FluidSolver::FluidSolver()
        :width(0), height(0), size(0), visc(0.0f), diff(0.0001f), tmp(0), d(0), dOld(0), u(0), uOld(0), v(0), vOld(0), curl(0), map(0)
    {
        
    }

    FluidSolver::~FluidSolver()
    {
        Destroy();
    }

    void FluidSolver::Destroy()
    {
        delete[] d;
        d = 0;
        delete[] dOld;
        dOld = 0;
        delete[] u;
        u = 0;
        delete[] uOld;
        uOld = 0;
        delete[] v;
        v = 0;
        delete[] vOld;
        vOld = 0;
        delete[] curl;
        curl = 0;
        delete[] map;
        map = 0;
    }

    void FluidSolver::Init(int Width, int Height)
    {
        width = Width;
        height = Height;
        size = (width + 2) * (height + 2);

        // so we can call Init multiple times
        Destroy();

        d = new float[size];
        dOld = new float[size];
        u = new float[size];
        uOld = new float[size];
        v = new float[size];
        vOld = new float[size];
        curl = new float[size];
        map = new bool[size];

        Reset();
    }

    void FluidSolver::Reset()
    {
        // set all values to 0.0f
        for(int i = 0; i < size; ++i) {
            u[i] = uOld[i] = v[i] = vOld[i] = 0.0f;
            d[i] = dOld[i] = curl[i] = 0.0f;
            map[i] = false;
        }

        // borders
        /*for(int i = 0; i <= width + 1; ++i) {
            map[I(i, 0)] = true;
            map[I(i, height + 1)] = true;
        }
        for(int i = 0; i <= height + 1; ++i) {
            map[I(0, i)] = true;
            map[I(width + 1, i)] = true;
        }*/
    }

    void FluidSolver::AddSource(float *a, float *a0, float dt)
    {
        for(int i = 0; i < size; ++i) {
            a[i] += a0[i] * dt;
        }
    }

    void FluidSolver::Boundary(int b, float *a)
    {
        for(int j = 1; j <= height; ++j) {
            a[I(  0, j  )] = b == 1 ? -a[I(1, j)] : a[I(1, j)];
            a[I(width+1, j  )] = b == 1 ? -a[I(width, j)] : a[I(width, j)];
        }
        for(int i = 1; i <= width; ++i) {
            a[I(  i, 0  )] = b == 2 ? -a[I(i, 1)] : a[I(i, 1)];
            a[I(  i, height+1)] = b == 2 ? -a[I(i, height)] : a[I(i, height)];
        }
        
        for(int i = 1; i <= width; ++i) {
            for(int j = 1; j <= height; ++j) {
                bool gx0 = map[I(i, j)] != map[I(i + 1, j)];
                bool gx1 = map[I(i - 1, j)] != map[I(i, j)];
                bool gy0 = map[I(i, j)] != map[I(i, j + 1)];
                bool gy1 = map[I(i, j - 1)] != map[I(i, j)];
                if(b == 1) { // x
                    if(gx0) {
                        a[I(i + 1, j)] = -a[I(i, j)];
                    }
                    if(gx1) {
                        a[I(i - 1, j)] = -a[I(i, j)];
                    }
                } else
                if(b == 2) { // y
                    if(gy0) {
                        a[I(i, j + 1)] = -a[I(i, j)];
                    }
                    if(gy1) {
                        a[I(i, j - 1)] = -a[I(i, j)];
                    }
                } else { // not x or y
                    
                }
            }
        }

        a[I(  0,   0)] = 0.5f * (a[I(1, 0  )] + a[I(  0, 1)]);
        a[I(  0, height+1)] = 0.5f * (a[I(1, height+1)] + a[I(  0, height)]);
        a[I(width+1,   0)] = 0.5f * (a[I(width, 0  )] + a[I(width+1, 1)]);
        a[I(width+1, height+1)] = 0.5f * (a[I(width, height+1)] + a[I(width+1, height)]);
    }


    float FluidSolver::Curl(int i, int j) const
    {
        float du_dy = (u[I(i, j + 1)] - u[I(i, j - 1)]) * 0.5f;
        float dv_dx = (v[I(i + 1, j)] - v[I(i - 1, j)]) * 0.5f;

        return du_dy - dv_dx;
    }

    void FluidSolver::VorticityConfinement(float *vX, float *vY)
    {
        float dw_dx, dw_dy;
        float length;
        float c;

        // Calculate magnitude of curl(u,v) for each cell. (|w|)
        for(int i = 1; i <= width; ++i) {
            for(int j = 1; j <= height; ++j) {
                c = Curl(i, j);
                curl[I(i, j)] = c < 0.0f ? -c : +c;
            }
        }

        for(int i = 2; i < width; ++i) {
            for(int j = 2; j < height; ++j) {
                // Find derivative of the magnitude (n = del |w|)
                dw_dx = (curl[I(i + 1, j)] - curl[I(i - 1, j)]) * 0.5f;
                dw_dy = (curl[I(i, j + 1)] - curl[I(i, j - 1)]) * 0.5f;

                length = sqrtf(dw_dx * dw_dx + dw_dy * dw_dy) + 0.000001f;

                // N = ( n/|n| )
                dw_dx /= length;
                dw_dy /= length;

                c = Curl(i, j);

                // N x w
                vX[I(i, j)] = dw_dy * -c;
                vY[I(i, j)] = dw_dx * +c;
            }
        }
    }

    void FluidSolver::Advect(int b, float *arr, float *arr0, float *du, float *dv, float dt)
    {
        int i0, j0, i1, j1;
        float x, y, s0, t0, s1, t1, dt0x, dt0y;

        dt0x = dt * width;
        dt0y = dt * height;

        for(int i = 1; i <= width; ++i) {
            for(int j = 1; j <= height; ++j) {
                // go backwards through velocity field
                x = i - dt0x * du[I(i, j)];
                y = j - dt0y * dv[I(i, j)];

                // interpolate results
                if (x > width + 0.5) x = width + 0.5f;
                if (x < 0.5)     x = 0.5f;

                i0 = (int) x;
                i1 = i0 + 1;

                if (y > height + 0.5) y = height + 0.5f;
                if (y < 0.5)     y = 0.5f;

                j0 = (int) y;
                j1 = j0 + 1;

                s1 = x - i0;
                s0 = 1 - s1;
                t1 = y - j0;
                t0 = 1 - t1;

                arr[I(i, j)] = s0 * (t0 * arr0[I(i0, j0)] + t1 * arr0[I(i0, j1)])
                           + s1 * (t0 * arr0[I(i1, j0)] + t1 * arr0[I(i1, j1)]);

            }
        }
        Boundary(b, arr);
    }

    void FluidSolver::Diffuse(int b, float *arr, float *arr0, float diff, float dt)
    {
        float a = dt * diff * width * height;
        LinearSolver(b, arr, arr0, a, 1 + 4 * a);
    }

    void FluidSolver::Project(float *x, float *y, float *p, float *div)
    {
        for(int i = 1; i <= width; ++i) {
            for(int j = 1; j <= height; ++j) {
                div[I(i, j)] = (x[I(i+1, j)] - x[I(i-1, j)]
                              + y[I(i, j+1)] - y[I(i, j-1)])
                                  * - 0.5f / width;
                p[I(i, j)] = 0;
            }
        }

        Boundary(0, div);
        Boundary(0, p);

        LinearSolver(0, p, div, 1, 4);

        for(int i = 1; i <= width; ++i) {
            for(int j = 1; j <= height; ++j) {
                x[I(i, j)] -= 0.5f * width * (p[I(i+1, j)] - p[I(i-1, j)]);
                y[I(i, j)] -= 0.5f * height * (p[I(i, j+1)] - p[I(i, j-1)]);
            }
        }

        Boundary(1, x);
        Boundary(2, y);
    }

    void FluidSolver::LinearSolver(int b, float *arr, float *arr0, float a, float c)
    {
        // default was 20 iterations
        for (int k = 0; k < 4; ++k) {
            for (int i = 1; i <= width; ++i) {
                for (int j = 1; j <= height; ++j) {
                    arr[I(i, j)] = (a * (arr[I(i - 1, j)] + arr[I(i + 1, j)]
                                    +    arr[I(i, j - 1)] + arr[I(i, j + 1)])
                                    +   arr0[I(i, j)]) / c;
                }
            }
            Boundary(b, arr);
        }
    }

    void FluidSolver::VelocitySolver(float dt)
    {
        // add velocity that was input by mouse
        AddSource(u, uOld, dt);
        AddSource(v, vOld, dt);

        // add in vorticity confinement force
        VorticityConfinement(uOld, vOld);
        AddSource(u, uOld, dt);
        AddSource(v, vOld, dt);

        // swapping arrays for economical mem use
        // and calculating diffusion in velocity.
        SwapU();
        Diffuse(0, u, uOld, visc, dt);

        SwapV();
        Diffuse(0, v, vOld, visc, dt);

        // we create an incompressible field
        // for more effective advection.
        Project(u, v, uOld, vOld);

        SwapU(); SwapV();

        // self advect velocities
        Advect(1, u, uOld, uOld, vOld, dt);
        Advect(2, v, vOld, uOld, vOld, dt);

        // make an incompressible field
        Project(u, v, uOld, vOld);

        // clear all input velocities for next frame
        for(int i = 0; i < size; ++i) {
            uOld[i] = vOld[i] = 0.0f;
        }
    }

    void FluidSolver::DensitySolver(float dt)
    {
        // add density inputted by mouse
        AddSource(d, dOld, dt);
        SwapD();

        Diffuse(0, d, dOld, diff, dt);
        SwapD();

        Advect(0, d, dOld, u, v, dt);

        // clear input density array for next frame
        for(int i = 0; i < size; ++i) {
            dOld[i] = 0.0f;
        }
    }

    void FluidSolver::MaintainDensity(float densityRest, float changeRate)
    {
        for (int i = 0; i < size; i++) {
            d[i] += (densityRest - d[i]) * changeRate;
        }
    }

}