#include "../ray/ray.h"
#include "../surfaces/sphere.h"

// Function to create a sphere given a center point and radius
Sphere
sphere (Tuple center, double radius)
{
  Sphere s;
  s.center = center;
  s.radius = radius;
  return s;
}

#define INVALID_T -999
Isect
intersect (Sphere sphere, Ray ray)
{
  Isect is;

  /* See: https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection */

  Tuple o_minus_c = subTuples (ray.origin, sphere.center);

  double a = dotProduct (ray.direction, ray.direction);
  double b = 2 * dotProduct (ray.direction, o_minus_c);
  double c = dotProduct (o_minus_c, o_minus_c) - pow (sphere.radius, 2);

  double discr = pow (b, 2) - 4 * a * c;

  if (discr < 0)
    {
      is.count = 0;
      is.t_vals[0] = INVALID_T;
      is.t_vals[1] = INVALID_T;

      return is;
    }

  double t1 = (-b - sqrt (discr)) / (2 * a);
  double t2 = (-b + sqrt (discr)) / (2 * a);

  is.count = 2;
  is.t_vals[0] = t1;
  is.t_vals[1] = t2;

  /* done for hitstest phase */
  is.object = sphere;

  return is;
}
