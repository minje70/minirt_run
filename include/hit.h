/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 01:19:43 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 15:49:50 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H
# include "structure.h"
# include "vector.h"
# include "ray.h"
# include "lighting.h"
# include "uutil.h"
# include "move.h"

void		set_face_normal(t_ray *r, t_hitrec *rec);
t_objects	*set_object(int type, void *data);
t_sphere	*set_sphere(t_point3 center, double radius, t_color objcolor,
						int texture_type);
t_plane		*set_plane(t_point3 point, t_vec normal, t_color color,
						int texture_type);
t_triangle	*set_triangle(t_point3 p1, t_point3 p2, t_point3 p3,
						t_color objcolor);
t_cylinder	*set_cylinder(t_point3 p, t_vec v, double r, double h);
t_square	*set_square(t_point3 p, t_vec n, double len, t_color objcolor);
t_cube		*set_cube(t_point3 p, double len, t_color objcolor,
						int texture_type);
t_pyramid	*set_pyramid(t_point3 p, double len, double h, t_color objcolor);
t_texture	*set_texture(int type, t_color albedo1, t_color albedo2,
						double option);
t_light		*set_light(t_point3 point, double brightness, t_color color);

void		min_max_check(t_hitrec *rec, int *width, int *height);
int			saturate_w(int w, int l, t_hitrec *rec);
int			saturate_h(int h, int l, t_hitrec *rec);
void		set_skybox_img(t_cntl *cntl, t_cube *cu, char *filename);
void		get_square_uv(t_hitrec *rec, t_square *sq, t_point3 left_bottom_p);
void		get_sphere_uv(t_hitrec *rec);
t_color		skybox_albedo(t_hitrec *rec);
t_color		sine_wave_albedo(t_hitrec *rec);
t_color		checker_albedo(t_hitrec *rec);
t_color		checker_uv_albedo(t_hitrec *rec);
t_color		albedo(t_hitrec *rec);

t_objects	*obj_last(t_objects *obj);
void		obj_add_back(t_objects **obj, t_objects *new_obj);
void		object_clear(t_objects **obj);
t_bool		hit(t_ray *r, t_hitrec *rec, t_objects *object);
t_bool		object_hit(t_ray *r, t_hitrec *rec, t_objects *object);

t_bool		hit_sphere(t_sphere *sphere, t_ray *r, t_hitrec *rec);
t_color		hit_light(t_hitrec *rec, t_objects *obj, t_camera *camera);
t_bool		hit_plane(t_plane *plane, t_ray *r, t_hitrec *rec);
t_bool		hit_triangle(t_triangle *tri, t_ray *r, t_hitrec *rec);

t_bool		hit_cy_circle(t_plane *pl, t_ray *r, t_hitrec *rec, double radius);
void		set_cylinder_disc(t_cylinder *cy, t_ray *r, t_hit_disc *disc);
t_bool		hit_cylinder(t_cylinder *cy, t_ray *r, t_hitrec *rec);
t_bool		cylinder_root_check(t_cylinder *cy, t_ray *r, double root);
void		capcylinder_rec(t_hitrec *rec, t_hitrec *temp_rec, t_cylinder *cy,
							int *hit_anything);
void		cylinder_rec(t_cylinder *cy, t_ray *r, t_hitrec *rec, double root);
t_bool		hit_cap_cylinder(t_cylinder *cy, t_ray *r, t_hitrec *rec);

t_bool		hit_square(t_square *sq, t_ray *r, t_hitrec *rec);
t_bool		hit_cube(t_cube *cu, t_ray *r, t_hitrec *rec);
t_bool		hit_pyramid(t_pyramid *py, t_ray *r, t_hitrec *rec);

#endif
