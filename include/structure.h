#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef int t_bool;

// 빛.
# define LI 0
// 구.
# define SP 1
// 평면
# define PL 2
// 삼각형
# define TR 3
// 원기둥 (무한)
# define CYI 4
// 정사각형
# define SQ 5

typedef struct s_vec
{
	double x;
	double y;
	double z;
} t_vec;

typedef t_vec t_point3;
typedef t_vec t_color;

typedef struct s_ray
{
	t_point3 orig;
	t_vec dir;
} t_ray;

typedef struct s_camera
{
	double viewport_h;
	double viewport_w;
	double focal_len;
	t_point3 origin;
	t_vec horizontal;
	t_vec vertical;
	t_point3 lower_left_corner;

} t_camera;

typedef struct s_hitrec
{
	t_point3 p;
	t_vec normal;
	double t;
	double tmin;
	double tmax;
	t_color obj_color;
	t_bool front_face;
} t_hitrec;

typedef struct s_objects
{
	int type;
	void *data;
	struct s_objects *next;
} t_objects;

typedef struct s_sphere
{
	double radius;
	t_point3 center;
	t_color obj_color;
} t_sphere;

typedef struct s_plane
{
	t_point3	p;
	t_vec		normal;
	t_color		color;
} t_plane;

typedef struct s_triangle
{
	t_point3	p1;
	t_point3	p2;
	t_point3	p3;
	t_vec		normal;
	t_color		color;
} t_triangle;

typedef struct s_light
{
	t_color color;
	t_point3 point;
} t_light;

typedef struct	s_cylinder
{
	t_point3	p;
	t_point3	p2;
	double		r;
	t_vec		v;
	t_color		color;
}	t_cylinder;

typedef struct	s_square
{
	t_point3	p;
	t_vec		n;
	t_color		color;
	double		len;
}	t_square;


#endif