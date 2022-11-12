//
// Created by eric on 09.11.22.
//

#include <cmath>
#include "Physics.h"
#include "../../../Constants.h"

namespace Physic {
    unsigned int IX(unsigned int x, unsigned int y, unsigned int N);

    void Physics::SetBnd(Boundry b, float x[], int N) {
        for (int i = 1; i < N - 1; i++) {
            x[IX(i, 0, N)] = b == Boundry::YAxis ? -x[IX(i, 1, N)] : x[IX(i, 1, N)];
            x[IX(i, N - 1, N)] = b == Boundry::YAxis ? -x[IX(i, N - 2, N)] : x[IX(i, N - 2, N)];
        }

        for (int j = 1; j < N - 1; j++) {
            x[IX(0, j, N)] = b == Boundry::XAxis ? -x[IX(1, j, N)] : x[IX(1, j, N)];
            x[IX(N - 1, j, N)] = b == Boundry::XAxis ? -x[IX(N - 2, j, N)] : x[IX(N - 2, j, N)];
        }

        x[IX(0, 0, N)] = 0.33f * (x[IX(1, 0, N)]
                                  + x[IX(0, 1, N)]
                                  + x[IX(0, 0, N)]);
        x[IX(0, N - 1, N)] = 0.33f * (x[IX(1, N - 1, N)]
                                      + x[IX(0, N - 2, N)]
                                      + x[IX(0, N - 1, N)]);
        x[IX(N - 1, 0, N)] = 0.33f * (x[IX(N - 2, 0, N)]
                                      + x[IX(N - 1, 1, N)]
                                      + x[IX(N - 1, 0, N)]);
        x[IX(N - 1, N - 1, N)] = 0.33f * (x[IX(N - 2, N - 1, N)]
                                          + x[IX(N - 1, N - 2, N)]
                                          + x[IX(N - 1, N - 1, N)]);
    }

    void Physics::LinSolve(Boundry b, float x[], const float x0[], float a, float c, int iter, int N) {
        float cRecip = 1.0f / c;
        for (int k = 0; k < iter; k++) {
            for (int j = 1; j < N - 1; j++) {
                for (int i = 1; i < N - 1; i++) {
                    x[IX(i, j, N)] = (x0[IX(i, j, N)] + a * (
                              x[IX(i + 1, j, N)]
                            + x[IX(i - 1, j, N)]
                            + x[IX(i, j + 1, N)]
                            + x[IX(i, j - 1, N)]
                            + x[IX(i, j, N)]
                            + x[IX(i, j, N)]
                    )
                                     ) * cRecip;
                }
            }
            Physics::SetBnd(b, x, N);
        }
    }

    void Physics::Diffuse(Boundry b, float x[], float x0[], float diff, float dt, int iter, int N) {
        float a = dt * diff * (N - 2) * (N - 2);
        Physics::LinSolve(b, x, x0, a, 1 + 6 * a, iter, N);
    }

    void Physics::Project(float vx[], float vy[], float p[], float div[], int iter, int N) {
        for (int j = 1; j < N - 1; j++) {
            for (int i = 1; i < N - 1; i++) {
                div[IX(i, j, N)] = -0.5f * (
                        vx[IX(i + 1, j, N)]
                        - vx[IX(i - 1, j, N)]
                        + vy[IX(i, j + 1, N)]
                        - vy[IX(i, j - 1, N)]
                ) / N;
                p[IX(i, j, N)] = 0;
            }
        }

        Physics::SetBnd(Boundry::None, div, N);
        Physics::SetBnd(Boundry::None, p, N);
        Physics::LinSolve(Boundry::None, p, div, 1, 6, iter, N);

        for (int j = 1; j < N - 1; j++) {
            for (int i = 1; i < N - 1; i++) {
                vx[IX(i, j, N)] -= 0.5f * (p[IX(i + 1, j, N)] - p[IX(i - 1, j, N)]) * N;
                vy[IX(i, j, N)] -= 0.5f * (p[IX(i, j + 1, N)] - p[IX(i, j - 1, N)]) * N;
            }
        }
        Physics::SetBnd(Boundry::XAxis, vx, N);
        Physics::SetBnd(Boundry::YAxis, vy, N);
    }

    void Physics::Advect(Boundry b, float d[], float d0[], float vx[], float vy[], float dt, int N) {
        float i0, i1, j0, j1;

        float dtx = dt * (N - 2.0f);
        float dty = dt * (N - 2.0f);

        float s0, s1, t0, t1;
        float tmp1, tmp2, x, y;

        float Nfloat = N;
        float ifloat, jfloat;

        int i, j;

        for (j = 1, jfloat = 1; j < N - 1; j++, jfloat++) {
            for (i = 1, ifloat = 1; i < N - 1; i++, ifloat++) {
                tmp1 = dtx * vx[IX(i, j, N)];
                tmp2 = dty * vy[IX(i, j, N)];
                x = ifloat - tmp1;
                y = jfloat - tmp2;

                if (x < 0.5f) x = 0.5f;
                if (x > Nfloat + 0.5f) x = Nfloat + 0.5f;
                i0 = ::floorf(x);
                i1 = i0 + 1.0f;
                if (y < 0.5f) y = 0.5f;
                if (y > Nfloat + 0.5f) y = Nfloat + 0.5f;
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

                d[IX(i, j, N)] =
                        s0 * (t0 * d0[IX(i0i, j0i, N)] + t1 * d0[IX(i0i, j1i, N)]) +
                        s1 * (t0 * d0[IX(i1i, j0i, N)] + t1 * d0[IX(i1i, j1i, N)]);
            }
        }
        Physics::SetBnd(b, d, N);
    }
} // Physic