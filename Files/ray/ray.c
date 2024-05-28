#include "ray.h"

// Function to create a Ray given an origin and direction.
Ray
ray (Tuple origin, Tuple direction)
{
  Ray r;
  r.origin = origin;
  r.direction = direction;
  return r;
}



// Function to compute the position along the ray at distance t
Tuple
position (Ray r, double t)
{
  // The point on the ray is computed as: origin + t * direction
  Tuple scaled_direction = scalarMultTuple (t, r.direction);
  return addTuples (r.origin, scaled_direction);
}
