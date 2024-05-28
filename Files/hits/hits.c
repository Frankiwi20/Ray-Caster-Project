#include "hits.h"
#include "../surfaces/sphere.h"

IRec
intersection (double t, Sphere sphere)
{
  IRec rec;
  rec.t = t;
  rec.object = sphere;
  return rec;
}

IRecs
intersections (unsigned int count, ...)
{
  va_list args;
  va_start (args, count);
  IRecs recs;
  recs.count = count;
  recs.records = (IRec *) malloc (count * sizeof (IRec));
  for (unsigned int i = 0; i < count; i++)
    {
      recs.records[i] = va_arg (args, IRec);
    }
  va_end (args);
  return recs;
}

IRec
hit (IRecs recs)
{
  IRec closest;
  closest.t = INVALID_T;	// Initialize with invalid value
  for (unsigned int i = 0; i < recs.count; i++)
    {
      if (recs.records[i].t < 0)
	continue;		// Skip negative t values
      if (closest.t == INVALID_T || recs.records[i].t < closest.t)
	{
	  closest = recs.records[i];
	}
    }
  return closest;
}
