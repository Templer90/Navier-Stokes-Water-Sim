//
// Created by eric on 09.11.22.
//

#include <cmath>
#include "Physics.h"
#include "../../../Constants.h"

namespace Physic {
    void Init() {
        constexpr int N = GridWidth;
        Physics::IXBuffer = new int *[N];
        for (int i = 0; i < N; i++) {
            Physics::IXBuffer[i] = new int[N];
            for (int j = 0; j < N; j++) {
                Physics::IXBuffer[i][j] = (int) IX(i, j, N);
            }
        }
    }

    void Physics::SetBnd(Boundry b, float x[], int N) {
        float dir = b == Boundry::YAxis ? -1.0f : 1.0f;
        for (int i = 1; i < N - 1; i++) {
            x[Physics::IXBuffer[i][0]] = dir * x[Physics::IXBuffer[i][1]];
            x[Physics::IXBuffer[i][N - 1]] = dir * x[Physics::IXBuffer[i][N - 2]];
        }

        dir = b == Boundry::XAxis ? -1.0f : 1.0f;
        for (int j = 1; j < N - 1; j++) {
            x[Physics::IXBuffer[0][j]] = dir * x[Physics::IXBuffer[1][j]];
            x[Physics::IXBuffer[N - 1][j]] = dir * x[Physics::IXBuffer[N - 2][j]];
        }

        x[Physics::IXBuffer[0][ 0]] = 0.33f * (x[Physics::IXBuffer[1][ 0]]
                                  + x[Physics::IXBuffer[0][ 1]]
                                  + x[Physics::IXBuffer[0][ 0]]);
        x[Physics::IXBuffer[0][ N - 1]] = 0.33f * (x[Physics::IXBuffer[1][ N - 1]]
                                      + x[Physics::IXBuffer[0][ N - 2]]
                                      + x[Physics::IXBuffer[0][ N - 1]]);
        x[Physics::IXBuffer[N - 1][ 0]] = 0.33f * (x[Physics::IXBuffer[N - 2][ 0]]
                                      + x[Physics::IXBuffer[N - 1][ 1]]
                                      + x[Physics::IXBuffer[N - 1][ 0]]);
        x[Physics::IXBuffer[N - 1][ N - 1]] = 0.33f * (x[Physics::IXBuffer[N - 2][ N - 1]]
                                          + x[Physics::IXBuffer[N - 1][ N - 2]]
                                          + x[Physics::IXBuffer[N - 1][ N - 1]]);
    }

    void Physics::LinSolve(Boundry b, float x[], const float x0[], const float a, float c, int iter, int N) {
        float cRecip = 1.0f / c;
        int ij = 0;
        for (int k = 0; k < iter; k++) {
            for (int j = 1; j < N - 1; j++) {
                for (int i = 1; i < N - 1; i++) {
                    ij = Physics::IXBuffer[i][j];
                    x[ij] = (x0[ij]+ a * (
                              x[ij + 1]//Works because of formula (j*N)+i
                            + x[ij - 1]//Works because of formula (j*N)+i
                            + x[Physics::IXBuffer[i][j + 1]]
                            + x[Physics::IXBuffer[i][j - 1]]
                            + (x[ij] * 2.0f)
                    )) * cRecip;
                }
            }
            Physics::SetBnd(b, x, N);
        }
    }

    void Physics::Diffuse(Boundry b, float x[], float x0[], float diff, float dt, int iter, int N) {
        float a = dt * diff * (float)((N - 2) * (N - 2));
        Physics::LinSolve(b, x, x0, a, 1 + 6 * a, iter, N);
    }

    void Physics::Project(float vx[], float vy[], float p[], float div[], int iter, int N) {
        auto floatN=(float)N;
        int ij=0;

        for (int j = 1; j < N - 1; j++) {
            for (int i = 1; i < N - 1; i++) {
                ij = Physics::IXBuffer[i][j];
                div[ij] = -0.5f * (
                        vx[ij+1]//Works because of formula (j*N)+i
                        - vx[ij-1]//Works because of formula (j*N)+i
                        + vy[Physics::IXBuffer[i][j+1]]
                        - vy[Physics::IXBuffer[i][j-1]]
                ) / floatN;
                p[ij] = 0;
            }
        }

        Physics::SetBnd(Boundry::None, div, N);
        Physics::SetBnd(Boundry::None, p, N);
        Physics::LinSolve(Boundry::None, p, div, 1, 6, iter, N);

        for (int j = 1; j < N - 1; j++) {
            for (int i = 1; i < N - 1; i++) {
                ij = Physics::IXBuffer[i][j];
                vx[ij] -= 0.5f * (p[ij+1] - p[ij-1]) * floatN;//Works because of formula (j*N)+i
                vy[ij] -= 0.5f * (p[Physics::IXBuffer[i][j+1]] - p[Physics::IXBuffer[i][j-1]]) * floatN;
            }
        }
        Physics::SetBnd(Boundry::XAxis, vx, N);
        Physics::SetBnd(Boundry::YAxis, vy, N);
    }

    void Physics::Advect(Boundry b, float d[], const float d0[], const float vx[], const float vy[], float dt, int N) {
        float i0, i1, j0, j1;
        auto floatN = (float)N;

        float dtx = dt * (floatN - 2.0f);
        float dty = dt * (floatN - 2.0f);

        float s0, s1, t0, t1;
        float tmp1, tmp2, x, y;

        float ifloat, jfloat;

        int i, j;

        int ij=0;
        for (j = 1, jfloat = 1; j < N - 1; j++, jfloat++) {
            for (i = 1, ifloat = 1; i < N - 1; i++, ifloat++) {
                ij = Physics::IXBuffer[i][j];
                tmp1 = dtx * vx[ij];
                tmp2 = dty * vy[ij];
                x = ifloat - tmp1;
                y = jfloat - tmp2;

                if (x < 0.5f) x = 0.5f;
                if (x > floatN + 0.5f) x = floatN + 0.5f;
                i0 = ::floorf(x);
                i1 = i0 + 1.0f;

                if (y < 0.5f) y = 0.5f;
                if (y > floatN + 0.5f) y = floatN + 0.5f;
                j0 = ::floorf(y);
                j1 = j0 + 1.0f;

                s1 = x - i0;
                s0 = 1.0f - s1;
                t1 = y - j0;
                t0 = 1.0f - t1;

                int i0i = (int) i0;
                int i1i = (int) i1;
                int j0i = (int) j0;
                int j1i = (int) j1;

                d[ij] =
                        s0 * (t0 * d0[IX(i0i, j0i, N)] + t1 * d0[IX(i0i, j1i, N)]) +
                        s1 * (t0 * d0[IX(i1i, j0i, N)] + t1 * d0[IX(i1i, j1i, N)]);
            }
        }
        Physics::SetBnd(b, d, N);
    }
} // Physic