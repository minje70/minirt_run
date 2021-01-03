#ifndef HIT_H
# define HIT_H
# include "structure.h"
# include "vector.h"
# include "ray.h"
# include "lighting.h"
# include "uutil.h"
# include "move.h"

void set_face_normal(t_ray *r, t_hitrec *rec);
t_objects *set_object(int type, void *data);
t_sphere *set_sphere(t_point3 center, double radius, t_color objcolor);
t_plane *set_plane(t_point3 point, t_vec normal, t_color color);
t_triangle	*set_triangle(t_point3 p1, t_point3 p2, t_point3 p3, t_color color);
t_cylinder	*set_cylinder(t_point3 p, t_vec v, double r, double h, t_color color);
t_square	*set_square(t_point3 p, t_vec n, double len, t_color color);
t_cube		*set_cube(t_point3 p, double len, t_color color);
t_pyramid	*set_pyramid(t_point3 p, double len, double h, t_color color);

t_objects *obj_last(t_objects *obj);
void	obj_add_back(t_objects **obj, t_objects *new_obj);
void object_clear(t_objects **obj);
t_bool	hit(t_ray *r, t_hitrec *rec, t_objects *object);
t_bool	object_hit(t_ray *r, t_hitrec *rec, t_objects *object);
t_bool	hit_sphere(t_sphere *sphere, t_ray *r, t_hitrec *rec);
t_color	hit_light(t_hitrec *rec, t_objects *obj, t_camera *camera);
t_bool	hit_plane(t_plane *plane, t_ray *r, t_hitrec *rec);
t_bool	hit_triangle(t_triangle *tri, t_ray *r, t_hitrec *rec);
t_bool	hit_cylinder(t_cylinder *cy, t_ray *r, t_hitrec *rec);
t_bool	hit_square(t_square *sq, t_ray *r, t_hitrec *rec);
t_bool	hit_cube(t_cube *cu, t_ray *r, t_hitrec *rec);
t_bool	hit_pyramid(t_pyramid *py, t_ray *r, t_hitrec *rec);
t_bool	hit_cy_circle(t_plane *pl, t_ray *r, t_hitrec *rec, double radius);
t_bool	hit_cap_cylinder(t_cylinder *cy, t_ray *r, t_hitrec *rec);

#endif