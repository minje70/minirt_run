#ifndef RAY_H
# define RAY_H
# include "structure.h"
# include "vector.h"
# include "uutil.h"
# include "hit.h"
# include "control.h"
# include "render.h"

t_ray	ray(t_point3 orig, t_vec dir);
t_vec	ray_at(t_ray ray, double t);
t_color ray_color(t_ray *r, t_objects *object, t_camera camera, int light_on);

#endif