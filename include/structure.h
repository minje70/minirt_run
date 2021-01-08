/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 01:16:22 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 01:16:23 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef int	t_bool;

# define LI 0
# define SP 1
# define PL 2
# define TR 3
# define CY 4
# define SQ 5
# define CAM 6
# define CU 7
# define PY 8

# define SOLID 0
# define CHECK_PATTERN 1
# define CHECK_UV_PATTERN 2
# define RAINBOW 3
# define WAVE 4
# define IMG_TEXTURE 5
# define SKY_BOX 6

typedef	struct s_vec		t_vec;
typedef	struct s_ray		t_ray;
typedef	struct s_std_set	t_std_set;
typedef	struct s_camera	t_camera;
typedef	struct s_objects	t_objects;
typedef	struct s_hitrec	t_hitrec;
typedef	struct s_sphere	t_sphere;
typedef	struct s_plane		t_plane;
typedef	struct s_triangle	t_triangle;
typedef	struct s_light		t_light;
typedef	struct s_cylinder	t_cylinder;
typedef	struct s_square	t_square;
typedef	struct s_pyramid	t_pyramid;
typedef	struct s_cube		t_cube;
typedef	struct s_data		t_data;
typedef	struct s_scene		t_scene;
typedef	struct s_cntl		t_cntl;
typedef	struct s_basket	t_basket;
typedef	struct s_texture	t_texture;
typedef struct s_hit_disc	t_hit_disc;

struct	s_vec
{
	double x;
	double y;
	double z;
};

typedef t_vec	t_rotate;
typedef t_vec	t_point3;
typedef t_vec	t_color;

struct	s_ray
{
	t_point3	orig;
	t_vec		dir;
};

struct	s_std_set
{
	int		height;
	int		width;
	t_color	color;
	double	amb_light;
};

struct	s_camera
{
	t_point3	origin;
	t_vec		w;
	double		fov;
	t_vec		horizontal;
	t_vec		vertical;
	t_point3	left_top_corner;
};

struct	s_objects
{
	int					type;
	void				*data;
	t_rotate			rotate;
	struct s_objects	*next;
};

struct	s_sphere
{
	double		radius;
	t_point3	center;
	t_color		obj_color;
	t_texture	*texture;
};

struct	s_plane
{
	t_point3	p;
	t_vec		normal;
	t_color		color;
	t_texture	*texture;
};

struct	s_triangle
{
	t_point3	p1;
	t_point3	p2;
	t_point3	p3;
	t_vec		normal;
	t_color		color;
	t_texture	*texture;
};

struct	s_light
{
	t_color		color;
	t_point3	point;
	double		brightness;
	t_color		light_color;
};

struct	s_cylinder
{
	t_point3	p;
	t_point3	p2;
	double		h;
	double		r;
	t_vec		v;
	t_color		color;
	t_texture	*texture;
};

struct	s_square
{
	t_point3	p;
	t_vec		n;
	t_color		color;
	double		len;
	t_texture	*texture;
};

struct	s_pyramid
{
	t_point3	p;
	double		len;
	t_square	*sq;
	t_triangle	*tr[4];
	t_color		color;
	t_texture	*texture;
};

struct	s_cube
{
	t_point3	p;
	double		len;
	t_square	*sq[6];
	t_color		color;
	t_texture	*texture;
};

struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};

struct	s_scene
{
	t_std_set	canv;
	t_objects	*cam_list;
	t_camera	*cam_onair;
	t_objects	*world;
	t_data		*img;
};

struct	s_cntl
{
	void		*mlx;
	void		*win;
	t_scene		*scene;
	t_objects	*selected;
	t_data		*img;
	int			mode;
	int			light_on;
};

struct	s_basket
{
	t_scene		*scene;
	int			lane;
	int			light_on;
};

struct	s_texture
{
	int		type;
	t_color	albedo1;
	t_color	albedo2;
	double	option;
	t_data	*img;
	int		l;
};

struct	s_hitrec
{
	t_point3	p;
	t_vec		normal;
	double		t;
	double		tmin;
	double		tmax;
	double		u;
	double		v;
	t_texture	texture;
	t_objects	*obj;
	t_color		obj_color;
	t_bool		front_face;
};

struct	s_hit_disc
{
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
	t_vec	oc;
};

#endif
