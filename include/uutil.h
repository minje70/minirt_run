#ifndef UTIL_H
# define UTIL_H
# include <math.h>
# include "vector.h"
# include "structure.h"

# define infinity 1.0 / 0
# define pi M_PI;

// Utility Functions

double degrees_to_radians(double degrees);
double max_d(double d1, double d2);
t_bool	is_inside(t_triangle *tri, t_point3 p);
t_bool	is_inside_(t_point3 p1, t_point3 p2, t_point3 p3, t_point3 p);

#endif