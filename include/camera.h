#ifndef CAMERA_H
# define CAMERA_H

# include <math.h>
# include "structure.h"
# include "vector.h"
# include "uutil.h"

void	set_amblight(t_std_set *s_set, double lighting_ratio, t_color color);
void	set_viewport(t_std_set *s_set, int width, int height);
int		set_camera(t_camera *camera, t_std_set *s_set, t_point3 lookfrom, t_vec w, double fov);
int		set_camera2(t_camera *camera, t_point3 lookfrom, t_vec w);
#endif