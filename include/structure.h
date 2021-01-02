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
# define CY 4
// 정사각형
# define SQ 5
// 카메라
# define CAM 6
// 보너스 큐브
# define CU 7
// 보너스 피라미드
# define PY 8

typedef struct s_vec
{
	double x;
	double y;
	double z;
} t_vec;

typedef t_vec t_rotate;
typedef t_vec t_point3;
typedef t_vec t_color;

typedef struct s_ray
{
	t_point3 orig;
	t_vec dir;
} t_ray;

typedef struct	s_std_set
{
	int		height;
	int		width;
	t_color	color;
	double	amb_light;
}				t_std_set;

typedef struct s_camera
{
	t_point3	origin;
	t_vec		w;
	double		fov;
	// double		ratio;
	// double		viewport_h;
	// double		viewport_w;
	// double		focal_len;
	t_vec		horizontal;
	t_vec		vertical;
	t_point3	left_top_corner;

} t_camera;


typedef struct s_objects
{
	int type;
	void *data;
	t_rotate	rotate;
	struct s_objects *next;
} t_objects;

typedef struct s_hitrec
{
	t_point3	p;
	t_vec		normal;
	double		t;
	double		tmin;
	double		tmax;
	t_objects	*obj;
	t_color		obj_color;
	t_bool		front_face;
} t_hitrec;

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
	t_color		color;
	t_point3	point;
	double		brightness;
	t_color		light_color;
} t_light;

typedef struct	s_cylinder
{
	t_point3	p;
	t_point3	p2;
	double		h;
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

typedef struct	s_pyramid
{
	t_point3	p;
	double		len;
	t_square	*sq;
	t_triangle	*tr[4];
	t_color		color;
}				t_pyramid;

typedef struct	s_cube
{
	t_point3	p;
	double		len;
	t_square	*sq[6];
	t_color		color;
}				t_cube;

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
}	t_data;

typedef struct	s_scene
{
	t_std_set	canv;
	t_objects	*cam_list;
	t_camera	*cam_onair;
	t_objects	*world;
	t_data		*img;
}				t_scene;

typedef struct	s_cntl
{
	void		*mlx;
	void		*win;
	t_scene		*scene;
	t_objects	*selected;
	t_data		*img;
	int			mode;
	int			light_on;
}				t_cntl;

typedef struct	s_basket
{
	t_scene		*scene;
	int			lane;
	int			light_on;
}				t_basket;

#endif