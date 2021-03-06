/*
Unit tests for grav_prism.c functions.
*/

#include <stdio.h>
#include <math.h>
#include "../src/lib/grav_sphere.h"
#include "../src/lib/grav_prism.h"
#include "../src/lib/geometry.h"
#include "../src/lib/constants.h"


char msg[1000];

int sign(double x)
{
    if(x >= 0)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

static char * test_safe_atan2_sign()
{
    double res,
           y[] = {1, -1,  1, -1},
           x[] = {1,  1, -1, -1};
    register int i;

    for(i = 0; i < 4; i++)
    {
        res = safe_atan2(y[i], x[i]);
        sprintf(msg, "safe_atan2=%g for y=%g x=%g", res, y[i], x[i]);
        mu_assert(sign(y[i]*x[i]) == sign(res), msg);
    }
    return 0;
}

static char * test_safe_atan2_zero()
{
    double res,
           x[] = {1,  -1, 0};
    register int i;
    for(i = 0; i < 3; i++)
    {
        res = safe_atan2(0, x[i]);
        sprintf(msg, "safe_atan2=%g for x=%g", res, x[i]);
        mu_assert(res == 0, msg);
    }
    return 0;
}

static char * test_pot_around()
{
    PRISM prism = {1000,-3000,3000,-3000,3000,-3000,3000,0,0,0};
    double planes[6], dist = 5000, i, j;
    register int p, k;

    for(i = -10000; i <= 10000; i += 100)
    {
        for(j = -10000; j <= 10000; j += 100)
        {
            planes[0] = prism_pot(prism, i, j, -dist);
            planes[1] = prism_pot(prism, i, j, dist);
            planes[2] = prism_pot(prism, -dist, i, j);
            planes[3] = prism_pot(prism, dist, i, j);
            planes[4] = prism_pot(prism, i, -dist, j);
            planes[5] = prism_pot(prism, i, dist, j);
            for(p = 0; p < 5; p++)
            {
                for(k = p + 1; k < 6; k++)
                {
                    sprintf(msg, "point (%g, %g) on planes %d n %d = (%.8f %.8f)",
                            i, j, p, k, planes[p], planes[k]);
                    mu_assert_almost_equals(planes[p], planes[k], 10E-10, msg);
                }
            }
        }
    }
    return 0;
}

static char * test_gx_around()
{
    PRISM prism = {1000,-3000,3000,-3000,3000,-3000,3000,0,0,0};
    double gz, above, below, north, south, east, west, dist = 5000, i, j;

    for(i = -10000; i <= 10000; i += 100)
    {
        for(j = -10000; j <= 10000; j += 100)
        {
            above = prism_gx(prism, i, j, -dist);
            below = prism_gx(prism, i, j, dist);
            north = prism_gx(prism, dist, i, j);
            south = prism_gx(prism, -dist, i, j);
            east = prism_gx(prism, i, dist, j);
            west = prism_gx(prism, i, -dist, j);
            gz = prism_gz(prism, i, j, -dist);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "above", "below", above, below);
            mu_assert_almost_equals(above, below, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "north", "south", north, south);
            mu_assert_almost_equals(north, -south, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "east", "west", east, west);
            mu_assert_almost_equals(east, west, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "east", "above", east, above);
            mu_assert_almost_equals(east, above, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "north", "gz", north, gz);
            mu_assert_almost_equals(north, -gz, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "south", "gz", south, gz);
            mu_assert_almost_equals(south, gz, 10E-10, msg);
        }
    }
    return 0;
}

static char * test_gy_around()
{
    PRISM prism = {1000,-3000,3000,-3000,3000,-3000,3000,0,0,0};
    double gz, above, below, north, south, east, west, dist = 5000, i, j;

    for(i = -10000; i <= 10000; i += 100)
    {
        for(j = -10000; j <= 10000; j += 100)
        {
            above = prism_gy(prism, i, j, -dist);
            below = prism_gy(prism, i, j, dist);
            north = prism_gy(prism, dist, j, i);
            south = prism_gy(prism, -dist, j, i);
            east = prism_gy(prism, i, dist, j);
            west = prism_gy(prism, i, -dist, j);
            gz = prism_gz(prism, i, j, -dist);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "above", "below", above, below);
            mu_assert_almost_equals(above, below, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "north", "south", north, south);
            mu_assert_almost_equals(north, south, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "east", "west", east, west);
            mu_assert_almost_equals(east, -west, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "north", "above", north, above);
            mu_assert_almost_equals(north, above, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "east", "gz", east, gz);
            mu_assert_almost_equals(east, -gz, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "west", "gz", west, gz);
            mu_assert_almost_equals(west, gz, 10E-10, msg);
        }
    }
    return 0;
}

static char * test_gz_around()
{
    PRISM prism = {1000,-3000,3000,-3000,3000,-3000,3000,0,0,0};
    double gy, above, below, north, south, east, west, dist = 5000, i, j;

    for(i = -10000; i <= 10000; i += 100)
    {
        for(j = -10000; j <= 10000; j += 100)
        {
            above = prism_gz(prism, i, j, -dist);
            below = prism_gz(prism, i, j, dist);
            north = prism_gz(prism, dist, i, j);
            south = prism_gz(prism, -dist, i, j);
            east = prism_gz(prism, i, dist, j);
            west = prism_gz(prism, i, -dist, j);
            gy = prism_gy(prism, i, j, -dist);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "above", "below", above, below);
            mu_assert_almost_equals(above, -below, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "north", "south", north, south);
            mu_assert_almost_equals(north, south, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "east", "west", east, west);
            mu_assert_almost_equals(east, west, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "north", "gy", north, gy);
            mu_assert_almost_equals(north, gy, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "south", "gy", south, gy);
            mu_assert_almost_equals(south, gy, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "east", "gy", east, gy);
            mu_assert_almost_equals(east, gy, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "west", "gy", west, gy);
            mu_assert_almost_equals(west, gy, 10E-10, msg);
        }
    }
    return 0;
}

static char * test_gxx_around()
{
    PRISM prism = {1000,-3000,3000,-3000,3000,-3000,3000,0,0,0};
    double gzz, above, below, north, south, east, west, dist = 5000, i, j;

    for(i = -10000; i <= 10000; i += 100)
    {
        for(j = -10000; j <= 10000; j += 100)
        {
            above = prism_gxx(prism, i, j, -dist);
            below = prism_gxx(prism, i, j, dist);
            north = prism_gxx(prism, dist, i, j);
            south = prism_gxx(prism, -dist, i, j);
            east = prism_gxx(prism, i, dist, j);
            west = prism_gxx(prism, i, -dist, j);
            gzz = prism_gzz(prism, i, j, -dist);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "above", "below", above, below);
            mu_assert_almost_equals(above, below, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "north", "south", north, south);
            mu_assert_almost_equals(north, south, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "east", "west", east, west);
            mu_assert_almost_equals(east, west, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "east", "above", east, above);
            mu_assert_almost_equals(east, above, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "north", "gzz", north, gzz);
            mu_assert_almost_equals(north, gzz, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "south", "gzz", south, gzz);
            mu_assert_almost_equals(south, gzz, 10E-10, msg);
        }
    }
    return 0;
}

static char * test_gxy_around()
{
    PRISM prism = {1000, -3000, 3000, -3000, 3000, -3000, 3000, 0, 0, 0};
    double gyz, above, below, north, south, east, west, dist = 5000, i, j;

    for(i = -10000; i <= 10000; i += 100)
    {
        for(j = -10000; j <= 10000; j += 100)
        {
            above = prism_gxy(prism, i, j, -dist);
            below = prism_gxy(prism, i, j, dist);
            north = prism_gxy(prism, dist, j, i);
            south = prism_gxy(prism, -dist, j, i);
            east = prism_gxy(prism, j, dist, i);
            west = prism_gxy(prism, j, -dist, i);
            gyz = prism_gyz(prism, i, j, -dist);
            sprintf(msg, " p (%g %g %g) on planes %s n %s = (%.15f n %.15f)",
                    i, j, dist, "above", "below", above, below);
            mu_assert_almost_equals(above, below, 1e-5, msg);
            sprintf(msg, " p (%g %g %g) on planes %s n %s = (%.15f n %.15f)",
                    i, j, dist, "north", "south", north, south);
            mu_assert_almost_equals(north, -south, 1e-5, msg);
            sprintf(msg, " p (%g %g %g) on planes %s n %s = (%.15f n %.15f)",
                    i, j, dist, "east", "west", east, west);
            mu_assert_almost_equals(east, -west, 1e-5, msg);
            sprintf(msg, " p (%g %g %g) on planes %s n %s = (%.15f n %.15f)",
                    i, j, dist, "east", "north", east, north);
            mu_assert_almost_equals(east, north, 1e-5, msg);
            sprintf(msg, " p (%g %g %g) on planes %s n %s = (%.15f n %.15f)",
                    i, j, dist, "west", "south", west, south);
            mu_assert_almost_equals(west, south, 1e-5, msg);
            sprintf(msg, " p (%g %g %g) on planes %s n %s = (%.15f n %.15f)",
                    i, j, dist, "north", "gyz", north, gyz);
            mu_assert_almost_equals(north, -gyz, 1e-5, msg);
            sprintf(msg, " p (%g %g %g) on planes %s n %s = (%.15f n %.15f)",
                    i, j, dist, "south", "gyz", south, gyz);
            mu_assert_almost_equals(south, gyz, 1e-5, msg);
        }
    }

    return 0;
}

static char * test_gxz_around()
{
    PRISM prism = {3000, -3000, 3000, -3000, 3000, -3000, 3000, 0, 0, 0};
    double other, above, below, north, south, east, west, dist = 5000, i, j;

    for(i = -10000; i <= 10000; i += 100)
    {
        for(j = -10000; j <= 10000; j += 100)
        {
            above = prism_gxz(prism, i, j, -dist);
            below = prism_gxz(prism, i, j, dist);
            north = prism_gxz(prism, dist, j, i);
            south = prism_gxz(prism, -dist, j, i);
            east = prism_gxz(prism, i, dist, j);
            west = prism_gxz(prism, i, -dist, j);
            other = prism_gxy(prism, i, j, -dist);
            sprintf(msg, " p (%g %g %g) on planes %s n %s = (%.15f %.15f)",
                    i, j, dist, "above", "below", above, below);
            mu_assert_almost_equals(above, -below, 1e-5, msg);
            sprintf(msg, " p (%g %g %g) on planes %s n %s = (%.15f %.15f)",
                    i, j, dist, "north", "south", north, south);
            mu_assert_almost_equals(north, -south, 1e-5, msg);
            sprintf(msg, " p (%g %g %g) on planes %s n %s = (%.15f %.15f)",
                    i, j, dist, "east", "west", east, west);
            mu_assert_almost_equals(east, west, 1e-5, msg);
            sprintf(msg, " p (%g %g %g) on planes %s n %s = (%.15f %.15f)",
                    i, j, dist, "below", "north", below, north);
            mu_assert_almost_equals(below, north, 1e-5, msg);
            sprintf(msg, " p (%g %g %g) on planes %s n %s = (%.15f %.15f)",
                    i, j, dist, "above", "south", above, south);
            mu_assert_almost_equals(above, south, 1e-5, msg);
            sprintf(msg, " p (%g %g %g) on planes %s n %s = (%.15f %.15f)",
                    i, j, dist, "east", "gxy", east, other);
            mu_assert_almost_equals(east, other, 1e-5, msg);
            sprintf(msg, " p (%g %g %g) on planes %s n %s = (%.15f %.15f)",
                    i, j, dist, "west", "gxy", west, other);
            mu_assert_almost_equals(west, other, 1e-5, msg);
        }
    }
    return 0;
}

static char * test_gyy_around()
{
    PRISM prism = {1000,-3000,3000,-3000,3000,-3000,3000,0,0,0};
    double other, above, below, north, south, east, west, dist = 5000, i, j;

    for(i = -10000; i <= 10000; i += 100)
    {
        for(j = -10000; j <= 10000; j += 100)
        {
            above = prism_gyy(prism, i, j, -dist);
            below = prism_gyy(prism, i, j, dist);
            north = prism_gyy(prism, dist, j, i);
            south = prism_gyy(prism, -dist, j, i);
            east = prism_gyy(prism, i, dist, j);
            west = prism_gyy(prism, i, -dist, j);
            other = prism_gzz(prism, i, j, -dist);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "above", "below", above, below);
            mu_assert_almost_equals(above, below, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "north", "south", north, south);
            mu_assert_almost_equals(north, south, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "east", "west", east, west);
            mu_assert_almost_equals(east, west, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "above", "north", above, north);
            mu_assert_almost_equals(above, north, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "east", "gzz", east, other);
            mu_assert_almost_equals(east, other, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "west", "gzz", west, other);
            mu_assert_almost_equals(west, other, 10E-10, msg);
        }
    }
    return 0;
}

static char * test_gyz_around()
{
    PRISM prism = {1000, -3000, 3000, -3000, 3000, -3000, 3000, 0, 0, 0};
    double other, above, below, north, south, east, west, dist = 5000, i, j;

    for(i = -10000; i <= 10000; i += 100)
    {
        for(j = -10000; j <= 10000; j += 100)
        {
            above = prism_gyz(prism, i, j, -dist);
            below = prism_gyz(prism, i, j, dist);
            north = prism_gyz(prism, dist, j, i);
            south = prism_gyz(prism, -dist, j, i);
            east = prism_gyz(prism, i, dist, j);
            west = prism_gyz(prism, i, -dist, j);
            other = prism_gxy(prism, i, j, -dist);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "above", "below", above, below);
            mu_assert_almost_equals(above, -below, 1e-5, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "north", "south", north, south);
            mu_assert_almost_equals(north, south, 1e-5, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "east", "west", east, west);
            mu_assert_almost_equals(east, -west, 1e-5, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "below", "east", below, east);
            mu_assert_almost_equals(below, east, 1e-5, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "above", "west", above, west);
            mu_assert_almost_equals(above, west, 1e-5, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "north", "gxy", north, other);
            mu_assert_almost_equals(north, other, 1e-5, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "south", "gxy", south, other);
            mu_assert_almost_equals(south, other, 1e-5, msg);
        }
    }
    return 0;
}

static char * test_gzz_around()
{
    PRISM prism = {1000,-3000,3000,-3000,3000,-3000,3000,0,0,0};
    double other, above, below, north, south, east, west, dist = 5000, i, j;

    for(i = -10000; i <= 10000; i += 100)
    {
        for(j = -10000; j <= 10000; j += 100)
        {
            above = prism_gzz(prism, i, j, -dist);
            below = prism_gzz(prism, i, j, dist);
            north = prism_gzz(prism, dist, i, j);
            south = prism_gzz(prism, -dist, i, j);
            east = prism_gzz(prism, i, dist, j);
            west = prism_gzz(prism, i, -dist, j);
            other = prism_gyy(prism, i, j, -dist);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "above", "below", above, below);
            mu_assert_almost_equals(above, below, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "north", "south", north, south);
            mu_assert_almost_equals(north, south, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "east", "west", east, west);
            mu_assert_almost_equals(east, west, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "north", "east", north, east);
            mu_assert_almost_equals(north, east, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "north", "gyy", north, other);
            mu_assert_almost_equals(north, other, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "south", "gyy", south, other);
            mu_assert_almost_equals(south, other, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "east", "gyy", east, other);
            mu_assert_almost_equals(east, other, 10E-10, msg);
            sprintf(msg, "point (%g, %g) on planes %s n %s = (%.8f %.8f)",
                    i, j, "west", "gyy", west, other);
            mu_assert_almost_equals(west, other, 10E-10, msg);
        }
    }
    return 0;
}

static char * test_gxx_below()
{
    PRISM prism = {3000,-5000,5000,-5000,5000,-5000,5000,0,0,0};
    double dist, restop, resbelow;

    for(dist=5010; dist <= 500000; dist += 100)
    {
        restop = prism_gxx(prism, 0, 0,-dist);
        resbelow = prism_gxx(prism, 0, 0, dist);

        sprintf(msg, "(distance %g m) top = %.5f  below = %.5f", dist,
                restop, resbelow);
        mu_assert_almost_equals(resbelow, restop, 0.1, msg);
    }

    return 0;
}

static char * test_gxy_below()
{
    PRISM prism = {3000,-5000,5000,-5000,5000,-5000,5000,0,0,0};
    double dist, restop, resbelow;

    for(dist=5010; dist <= 500000; dist += 100)
    {
        restop = prism_gxy(prism, 5000, 5000, -dist);
        resbelow = prism_gxy(prism, 5000, 5000, dist);

        sprintf(msg, "(distance %g m) top = %.5f  below = %.5f", dist,
                restop, resbelow);
        mu_assert_almost_equals(resbelow, restop, 1, msg);
    }

    return 0;
}

static char * test_gxz_below()
{
    PRISM prism = {3000,-5000,5000,-5000,5000,-5000,5000,0,0,0};
    double dist, restop, resbelow;

    for(dist=5010; dist <= 500000; dist += 100)
    {
        restop = prism_gxz(prism, 5000, 0,-dist);
        resbelow = prism_gxz(prism, 5000, 0, dist);

        sprintf(msg, "(distance %g m) top = %.5f  below = %.5f", dist,
                restop, resbelow);
        mu_assert_almost_equals(resbelow, -restop, 0.1, msg);
    }

    return 0;
}

static char * test_gyy_below()
{
    PRISM prism = {3000,-5000,5000,-5000,5000,-5000,5000,0,0,0};
    double dist, restop, resbelow;

    for(dist=5010; dist <= 500000; dist += 100)
    {
        restop = prism_gyy(prism, 0, 0,-dist);
        resbelow = prism_gyy(prism, 0, 0, dist);

        sprintf(msg, "(distance %g m) top = %.5f  below = %.5f", dist,
                restop, resbelow);
        mu_assert_almost_equals_rel(resbelow, restop, 1, msg);
    }

    return 0;
}

static char * test_gyz_below()
{
    PRISM prism = {3000,-5000,5000,-5000,5000,-5000,5000,0,0,0};
    double dist, restop, resbelow;

    for(dist=5010; dist <= 500000; dist += 100)
    {
        restop = prism_gyz(prism, 0, 5000, -dist);
        resbelow = prism_gyz(prism, 0, 5000, dist);

        sprintf(msg, "(distance %g m) top = %.5f  below = %.5f", dist,
                restop, resbelow);
        mu_assert_almost_equals(resbelow, -restop, 0.1, msg);
    }

    return 0;
}

static char * test_gzz_below()
{
    PRISM prism = {3000,-5000,5000,-5000,5000,-5000,5000,0,0,0};
    double dist, restop, resbelow;

    for(dist=5010; dist <= 500000; dist += 100)
    {
        restop = prism_gzz(prism, 0, 0, -dist);
        resbelow = prism_gzz(prism, 0, 0, dist);

        sprintf(msg, "(distance %g m) top = %.5f  below = %.5f", dist,
                restop, resbelow);
        mu_assert_almost_equals(resbelow, restop, 0.1, msg);
    }

    return 0;
}

static char * test_prism2sphere_pot()
{
    SPHERE sphere;
    PRISM prism = {3000,-5000,5000,-5000,5000,-5000,5000,0,0,0};
    double dist, resprism, ressphere;

    /* Make a sphere with the same mass as the prism and put it at the origin */
    prism2sphere(prism, 0, 0, 0, &sphere);

    for(dist=50000; dist <= 500000; dist += 500)
    {
        resprism = prism_pot(prism,0,0,-dist);
        ressphere = sphere_pot(sphere,0,90,dist);

        sprintf(msg, "(distance %g m) prism = %.5f  sphere = %.5f", dist,
                resprism, ressphere);
        mu_assert_almost_equals(resprism, ressphere, 0.001, msg);
    }

    return 0;
}

static char * test_prism2sphere_gx()
{
    SPHERE sphere;
    PRISM prism = {3000,-5000,5000,-5000,5000,-5000,5000,0,0,0};
    double dist, resprism, ressphere;

    /* Make a sphere with the same mass as the prism and put it at the origin */
    prism2sphere(prism, 0, 0, 0, &sphere);

    for(dist=10000; dist <= 500000; dist += 500)
    {
        resprism = prism_gx(prism,0,0,-dist);
        ressphere = sphere_gx(sphere,0,90,dist);

        sprintf(msg, "(distance %g m) prism = %.5f  sphere = %.5f", dist,
                resprism, ressphere);
        mu_assert_almost_equals(resprism, ressphere, 0.00000001, msg);
    }

    return 0;
}


static char * test_prism2sphere_gy()
{
    SPHERE sphere;
    PRISM prism = {3000,-5000,5000,-5000,5000,-5000,5000,0,0,0};
    double dist, resprism, ressphere;

    /* Make a sphere with the same mass as the prism and put it at the origin */
    prism2sphere(prism, 0, 0, 0, &sphere);

    for(dist=10000; dist <= 500000; dist += 500)
    {
        resprism = prism_gy(prism,0,0,-dist);
        ressphere = sphere_gy(sphere,0,90,dist);

        sprintf(msg, "(distance %g m) prism = %.5f  sphere = %.5f", dist,
                resprism, ressphere);
        mu_assert_almost_equals(resprism, ressphere, 0.00000001, msg);
    }

    return 0;
}


static char * test_prism2sphere_gz()
{
    SPHERE sphere;
    PRISM prism = {3000,-5000,5000,-5000,5000,-5000,5000,0,0,0};
    double dist, resprism, ressphere;

    /* Make a sphere with the same mass as the prism and put it at the origin */
    prism2sphere(prism, 0, 0, 0, &sphere);

    for(dist=50000; dist <= 500000; dist += 500)
    {
        resprism = prism_gz(prism,0,0,-dist);
        ressphere = sphere_gz(sphere,0,90,dist);

        sprintf(msg, "(distance %g m) prism = %.5f  sphere = %.5f", dist,
                resprism, ressphere);
        mu_assert_almost_equals(resprism, -1*ressphere, 0.01, msg);
    }

    return 0;
}


static char * test_prism2sphere_gxx()
{
    SPHERE sphere;
    PRISM prism = {3000,-5000,5000,-5000,5000,-5000,5000,0,0,0};
    double dist, resprism, ressphere;

    /* Make a sphere with the same mass as the prism and put it at the origin */
    prism2sphere(prism, 0, 0, 0, &sphere);

    for(dist=50000; dist <= 500000; dist += 500)
    {
        resprism = prism_gxx(prism,0,0,-dist);
        ressphere = sphere_gxx(sphere,0,90,dist);

        sprintf(msg, "(distance %g m) prism = %.5f  sphere = %.5f", dist,
                resprism, ressphere);
        mu_assert_almost_equals(resprism, ressphere, 0.001, msg);
    }

    return 0;
}


static char * test_prism2sphere_gxy()
{
    SPHERE sphere;
    PRISM prism = {3000,-5000,5000,-5000,5000,-5000,5000,0,0,0};
    double dist, resprism, ressphere;

    /* Make a sphere with the same mass as the prism and put it at the origin */
    prism2sphere(prism, 0, 0, 0, &sphere);

    for(dist=50000; dist <= 500000; dist += 500)
    {
        resprism = prism_gxy(prism,0,0,-dist);
        ressphere = sphere_gxy(sphere,0,90,dist);

        sprintf(msg, "(distance %g m) prism = %.5f  sphere = %.5f", dist,
                resprism, ressphere);
        mu_assert_almost_equals(resprism, ressphere, 0.001, msg);
    }

    return 0;
}


static char * test_prism2sphere_gxz()
{
    SPHERE sphere;
    PRISM prism = {3000,-5000,5000,-5000,5000,-5000,5000,0,0,0};
    double dist, resprism, ressphere;

    /* Make a sphere with the same mass as the prism and put it at the origin */
    prism2sphere(prism, 0, 0, 0, &sphere);

    for(dist=50000; dist <= 500000; dist += 500)
    {
        resprism = prism_gxz(prism,0,0,-dist);
        ressphere = sphere_gxz(sphere,0,90,dist);

        sprintf(msg, "(distance %g m) prism = %.5f  sphere = %.5f", dist,
                resprism, ressphere);
        mu_assert_almost_equals(resprism, -1*ressphere, 0.001, msg);
    }

    return 0;
}


static char * test_prism2sphere_gyy()
{
    SPHERE sphere;
    PRISM prism = {3000,-5000,5000,-5000,5000,-5000,5000,0,0,0};
    double dist, resprism, ressphere;

    /* Make a sphere with the same mass as the prism and put it at the origin */
    prism2sphere(prism, 0, 0, 0, &sphere);

    for(dist=50000; dist <= 500000; dist += 500)
    {
        resprism = prism_gyy(prism,0,0,-dist);
        ressphere = sphere_gyy(sphere,0,90,dist);

        sprintf(msg, "(distance %g m) prism = %.5f  sphere = %.5f", dist,
                resprism, ressphere);
        mu_assert_almost_equals(resprism, ressphere, 0.001, msg);
    }

    return 0;
}


static char * test_prism2sphere_gyz()
{
    SPHERE sphere;
    PRISM prism = {3000,-5000,5000,-5000,5000,-5000,5000,0,0,0};
    double dist, resprism, ressphere;

    /* Make a sphere with the same mass as the prism and put it at the origin */
    prism2sphere(prism, 0, 0, 0, &sphere);

    for(dist=50000; dist <= 500000; dist += 500)
    {
        resprism = prism_gyz(prism,0,0,-dist);
        ressphere = sphere_gyz(sphere,0,90,dist);

        sprintf(msg, "(distance %g m) prism = %.5f  sphere = %.5f", dist,
                resprism, ressphere);
        mu_assert_almost_equals(resprism, -1*ressphere, 0.001, msg);
    }

    return 0;
}


static char * test_prism2sphere_gzz()
{
    SPHERE sphere;
    PRISM prism = {3000,-5000,5000,-5000,5000,-5000,5000,0,0,0};
    double dist, resprism, ressphere;

    /* Make a sphere with the same mass as the prism and put it at the origin */
    prism2sphere(prism, 0, 0, 0, &sphere);

    for(dist=60000; dist <= 500000; dist += 500)
    {
        resprism = prism_gzz(prism,0,0,-dist);
        ressphere = sphere_gzz(sphere,0,90,dist);

        sprintf(msg, "(distance %g m) prism = %.5f  sphere = %.5f", dist,
                resprism, ressphere);
        mu_assert_almost_equals(resprism, ressphere, 0.001, msg);
    }

    return 0;
}

static char * test_prism_tensor_trace()
{
    #define N 4
    TESSEROID tesses[N] = {
        {1,0,1,0,1,6000000,6001000},
        {1,180,183,80,81.5,6300000,6302000},
        {1,200,203,-90,-88,5500000,5500100},
        {1,-10,-7,7,7.5,6500000,6505000}};
    PRISM prism;
    int i;
    double trace, dist, x, y;

    for(i = 0; i < N; i++)
    {
        tess2prism_flatten(tesses[i], &prism);
        x = 0.5*(prism.x1 + prism.x2);
        y = 0.5*(prism.y1 + prism.y2);

        for(dist=1000; dist <= 5000000; dist += 1000)
        {

            trace = prism_gxx(prism, x, y, prism.z1 - dist)
                    + prism_gyy(prism, x, y, prism.z1 - dist)
                    + prism_gzz(prism, x, y, prism.z1 - dist);

            sprintf(msg, "(prism %d dist %g) trace %.10f", i, dist, trace);
            mu_assert_almost_equals(trace, 0, 0.0000000001, msg);
        }
    }
    #undef N
    return 0;
}

int grav_prism_run_all()
{
    int failed = 0;
    failed += mu_run_test(test_safe_atan2_sign,
                "safe_atan2 result has same sign as angle");
    failed += mu_run_test(test_safe_atan2_zero,
                "safe_atan2 returns 0 for y == 0");
    failed += mu_run_test(test_pot_around,
                "prism_pot results equal around the prism");
    failed += mu_run_test(test_gx_around,
                "prism_gx results consistent around the prism");
    failed += mu_run_test(test_gy_around,
                "prism_gy results consistent around the prism");
    failed += mu_run_test(test_gz_around,
                "prism_gz results consistent around the prism");
    failed += mu_run_test(test_gxx_around,
                "prism_gxx results consistent around the prism");
    failed += mu_run_test(test_gxy_around,
                "prism_gxy results consistent around the prism");
    failed += mu_run_test(test_gxz_around,
                "prism_gxz results consistent around the prism");
    failed += mu_run_test(test_gyy_around,
                "prism_gyy results consistent around the prism");
    failed += mu_run_test(test_gyz_around,
                "prism_gyz results consistent around the prism");
    failed += mu_run_test(test_gzz_around,
                "prism_gzz results consistent around the prism");
    failed += mu_run_test(test_gxx_below,
                "prism_gxx results equal above and below the prism");
    failed += mu_run_test(test_gxy_below,
                "prism_gxy results equal above and below the prism");
    failed += mu_run_test(test_gxz_below,
                "prism_gxz results equal above and below the prism");
    failed += mu_run_test(test_gyy_below,
                "prism_gyy results equal above and below the prism");
    failed += mu_run_test(test_gyz_below,
                "prism_gyz results equal above and below the prism");
    failed += mu_run_test(test_gzz_below,
                "prism_gzz results equal above and below the prism");
    failed += mu_run_test(test_prism2sphere_pot,
                "prism_pot results equal to sphere of same mass at distance");
    failed += mu_run_test(test_prism2sphere_gx,
                "prism_gx results equal to sphere of same mass at distance");
    failed += mu_run_test(test_prism2sphere_gy,
                "prism_gy results equal to sphere of same mass at distance");
    failed += mu_run_test(test_prism2sphere_gz,
                "prism_gz results equal to sphere of same mass at distance");
    failed += mu_run_test(test_prism2sphere_gxx,
                "prism_gxx results equal to sphere of same mass at distance");
    failed += mu_run_test(test_prism2sphere_gxy,
                "prism_gxy results equal to sphere of same mass at distance");
    failed += mu_run_test(test_prism2sphere_gxz,
                "prism_gxz results equal to sphere of same mass at distance");
    failed += mu_run_test(test_prism2sphere_gyy,
                "prism_gyy results equal to sphere of same mass at distance");
    failed += mu_run_test(test_prism2sphere_gyz,
                "prism_gyz results equal to sphere of same mass at distance");
    failed += mu_run_test(test_prism2sphere_gzz,
                "prism_gzz results equal to sphere of same mass at distance");
    failed += mu_run_test(test_prism_tensor_trace,
        "trace of GGT for prism in Cartesian coordinates is zero");
    return failed;
}
