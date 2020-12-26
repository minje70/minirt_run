#ifndef MOVE_H
# define MOVE_H
# include "structure.h"
# include "vector.h"
# include "uutil.h"
# include "hit.h"

void	rotate_r(t_ray *r, t_rotate rot);
t_point3	world2object_cy(t_ray *r, t_cylinder *cy, t_rotate *rot, t_point3 *offset);
t_point3	object2world_cy(t_cylinder *cy, t_rotate *rot, t_point3 *offset);
t_bool	check_cy_rotate(t_objects *obj, t_hitrec *rec, t_ray *r, t_point3 *offset);
t_bool	check_tr_rotate(t_objects *obj, t_hitrec *rec, t_ray *r, t_point3 *offset);
t_bool	check_sq_rotate(t_objects *obj, t_hitrec *rec, t_ray *r, t_point3 *offset);
void	ray_normal_back(t_hitrec *rec, t_rotate *rot, t_point3 *offset);

#endif