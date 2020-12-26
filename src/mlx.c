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
        return (hit_light(&rec, object, &camera));
	}
	return (color(0.1, 0.1, 0.1));
}

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
	if (parsing(&camera, &object, &s_set, "temp.rt") == -1)
		return (-1);
	t_vec vec = vec3(0, 0, 1);
	rotate_v(&vec, vec3(90,90,90));
	// rotate_v(&vec, vec3(0,90,0));
	dprintf(2, "test:%f %f %f\n", vec.x, vec.y, vec.z);

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
		// dprintf(2, "remain: %d\n", i);
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