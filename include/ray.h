#ifndef RAY_H
# define RAY_H
# include "structure.h"
# include "vector.h"

t_ray ray(t_point3 orig, t_vec dir);
t_vec ray_at(t_ray ray, double t);

#endif