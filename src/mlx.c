#include <mlx.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "structure.h"
#include "camera.h"
#include "vector.h"
#include "ray.h"
#include "hit.h"
#include "lighting.h"
#include "parsing.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, t_color color)
{
	char	*dst;
	int		xc;
	int		yc;
	int		zc;

	color.x = color.x > 1 ? 1 : color.x;
	color.y = color.y > 1 ? 1 : color.y;
	color.z = color.z > 1 ? 1 : color.z;
	xc = (int)(255.999 * color.x);
	yc = (int)(255.999 * color.y);
	zc = (int)(255.999 * color.z);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8)); // addr이 어디까지 할당되어 있는가...
	*(unsigned int *)dst = (((xc << 8) + yc) << 8) + zc;
}

void	write_color(t_color color)
{
	color.x = color.x > 1 ? 1 : color.x;
	color.y = color.y > 1 ? 1 : color.y;
	color.z = color.z > 1 ? 1 : color.z;
	printf("%d ", (int)(255.999 * color.x));
	printf("%d ", (int)(255.999 * color.y));
	printf("%d\n", (int)(255.999 * color.z));
}

t_color ray_color(t_ray *r, t_objects *object, t_camera camera)
{
	t_hitrec rec;

	rec.tmin = 0.001;
	rec.tmax = infinity;
    if (hit(r, &rec, object))
	{
	// dprintf(2, "test\n");
		// dprintf(2, "diff %f, %f, %f\n", diff.x, diff.y, diff.z);
		// dprintf(2, "rec.normal %f, %f, %f\n", rec.normal.x, rec.normal.y, rec.normal.z);
		// dprintf(2, "ambient %f, %f, %f\n", ambient.x, ambient.y, ambient.z);
        return (hit_light(&rec, object, &camera));
	}
    // t_vec unit_direction = vunit(r->dir);
	// double t = 0.5 * (unit_direction.y + 1.0);
    // return (vplus(vmult(color(1.0, 1.0, 1.0), (1.0 - t)), vmult(color(0.5, 0.7, 1.0), t)));
	return (color(0.1, 0.1, 0.1));
}

// void	put_circle(t_data *data, int x, int y, int r) // 그냥 double형을 이용해 원을 그릴 때에 문제가 생김.
// {
// 	int	i;
// 	double	temp;

// 	double r1, x1, y1;
// 	r1 = r;
// 	x1 = x;
// 	y1 = y;
// 	i = 0;
// 	while (i < r * 2)
// 	{
// 		temp = sqrt(fabs((r1 * r1) - ((i - x1) * (i - x1))));
// 		my_mlx_pixel_put(data, i, (int)(y1 + temp), 0x00ff0000);
// 		my_mlx_pixel_put(data, i, (int)(y1 - temp), 0x00ff0000);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < r * 2)
// 	{
// 		temp = sqrt(fabs((r1 * r1) - ((i - y1) * (i - y1))));
// 		my_mlx_pixel_put(data, (int)(y1 + temp), i, 0x00ff0000);
// 		my_mlx_pixel_put(data, (int)(y1 - temp), i, 0x00ff0000);
// 		i++;
// 	}
// }

int		main()
{
	t_data	img;
	void	*mlx;
	void	*mlx_win;

	// main
	// camera
	t_camera	camera;
	t_std_set	s_set;
	//world
	t_objects *object;
	object = 0;
	// obj_add_back(&object, set_object(SP, set_sphere(point3(3, 0.1, -2), 0.6, color(0.1, 0.2, 0.9))));
	// obj_add_back(&object, set_object(SP, set_sphere(point3(-1, 0.2,-1), 0.3, color(0.4, 0.2, 1))));

	// obj_add_back(&object, set_object(SP, set_sphere(point3(0, 1, -2), 0.5, color(0.8, 0.2, 0.1))));

	obj_add_back(&object, set_object(CY, set_cylinder(point3(-1, 0, 0), point3(1, 0, 0), 0.3, color(0.8, 0.8, 0.2))));

	// obj_add_back(&object, set_object(TR, set_triangle(point3(-2, 1, -4),point3(0, 5, -4.5), point3(2, 1, -4), color(0.56, 0.34, 0.94))));

	// obj_add_back(&object, set_object(SQ, set_square(point3(2, 0.3, -2), vec3(1, 0, -1), color(0.2, 0.8, 0.2), 0.7)));

	// obj_add_back(&object, set_object(PL, set_plane(point3(0, -0.7, 0), color(0.15, 0.8, 0.34), vec3(0, 1, 0))));

	parsing(&camera, object, &s_set, "temp.rt");

	dprintf(2, "height:%d,width:%d\n", s_set.height, s_set.width);
	mlx = mlx_init(); // mlx를 사용하기 전 초기화 해주는 함수. 최근 MLX인스턴스를 리턴함.
	mlx_win = mlx_new_window(mlx, s_set.width, s_set.height, "minirt!"); // MLX인스턴스, 가로길이, 세로길이, 
	img.img = mlx_new_image(mlx, s_set.width, s_set.height); // bit를 하나하나 찍는거 보다는 이미지로 저장을 해서 한번에 찍어내는게 효율적이기 때문에 사용.
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	int i = s_set.height - 1;
	int j;
	while (i >= 0)
	{
		j = 0;
		dprintf(2, "remain: %d\n", i);
		while (j < s_set.width)
		{
			double u = (double)j / (s_set.width - 1);
			double v = (double)i / (s_set.height - 1);
			t_ray r = ray(camera.origin, vminus(vminus(vplus(camera.higher_left_corner, vmult(camera.horizontal, u)), vmult(camera.vertical, v)), camera.origin));
			t_color pixel_color;
			pixel_color = ray_color(&r, object, camera);
			my_mlx_pixel_put(&img, j, i, pixel_color);
			j++;
		}
		i--;
	}

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx); // 반복해서 돌리는 역할. 
}