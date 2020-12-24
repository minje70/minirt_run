#ifndef LIGHTING_H
# define LIGHTING_H
# include <math.h>
# include "structure.h"
# include "vector.h"
# include "uutil.h"
# include "hit.h"

t_color ambient_color(t_light *light, double ambient_strength);
t_color diff_color(t_light *light, t_hitrec *rec);
t_color specular_color(t_light *light, t_hitrec *rec, t_camera *camera);
t_light *set_light(t_point3 point, double brightness, t_color color);
t_bool shadow_color(t_light *light, t_objects *obj, t_hitrec *rec, t_camera *camera);

#endif