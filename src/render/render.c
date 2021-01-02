#include "render.h"

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

void	*multi_render(void *arg)
{
	int			i;
	int			j;
	double		u;
	double		v;
	t_ray		r;
	t_color 	pixel_color;
	t_basket	bask;

	bask = *(t_basket *)arg;
	i = bask.scene->canv.height - 1;
	while (i >= 0)
	{
		j = bask.lane;
		while (j < bask.scene->canv.width)
		{
			pixel_color = color(0, 0, 0);
			u = (double)j / (bask.scene->canv.width - 1);
			v = (double)i / (bask.scene->canv.height - 1);
			r = ray(bask.scene->cam_onair->origin, vminus(vminus(vminus(bask.scene->cam_onair->left_top_corner, vmult(bask.scene->cam_onair->horizontal, u)), vmult(bask.scene->cam_onair->vertical, v)), bask.scene->cam_onair->origin));
			pixel_color = ray_color(&r, bask.scene->world, *bask.scene->cam_onair, bask.light_on);
			my_mlx_pixel_put(bask.scene->img, j, i, pixel_color);
			j += THREAD;
		}
		i--;
	}
	return (0);
}

void	all_render(t_cntl *cntl)
{
	pthread_t	new[THREAD];
	t_basket	bask[THREAD];
	clock_t		start, end;
	int			i;
	int			j;

	start = clock();
	i = -1;
	while (++i < THREAD)
	{
		bask[i].lane = i;
		bask[i].scene = cntl->scene;
		bask[i].light_on = cntl->light_on;
		pthread_create(&new[i], NULL, multi_render, &(bask[i]));
	}
	j = -1;
	while (++j < THREAD)
	{
		pthread_join(new[j], NULL);
	}
	end = clock();
	printf("렌더링 한번하는 시간%f\n", ((double)end - start)/CLOCKS_PER_SEC);
}

t_color draw_rainbow(t_hitrec *rec)
{
	return (vmult(vplus(rec->normal, color(1,1,1)), 0.5));
}