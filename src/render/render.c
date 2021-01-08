/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 00:43:25 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 13:30:01 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	dst = data->addr + (y * data->line_length + x *
		(data->bits_per_pixel / 8));
	*(unsigned int *)dst = (((xc << 8) + yc) << 8) + zc;
}

t_color	render_sub(t_basket *bask, int i, int j, t_color pixel_color)
{
	double	u;
	double	v;
	t_ray	r;

	u = (double)(j + random_double()) / (bask->scene->canv.width - 1);
	v = (double)(i + random_double()) / (bask->scene->canv.height - 1);
	r = ray(bask->scene->cam_onair->origin, vminus(vminus(vminus(
		bask->scene->cam_onair->left_top_corner,
		vmult(bask->scene->cam_onair->horizontal, u)),
		vmult(bask->scene->cam_onair->vertical, v)),
		bask->scene->cam_onair->origin));
	pixel_color = vplus(pixel_color, ray_color(&r, bask->scene->world,
		*bask->scene->cam_onair, bask->light_on));
	return (pixel_color);
}

void	*multi_all_render(void *arg)
{
	int			i;
	int			j;
	int			k;
	t_color		pixel_color;

	i = (*(t_basket *)arg).scene->canv.height - 1;
	while (i >= 0)
	{
		j = (*(t_basket *)arg).lane;
		while (j < ((t_basket *)arg)->scene->canv.width)
		{
			pixel_color = color(0, 0, 0);
			k = -1;
			while (++k < PIXEL_PER_COLOR)
				pixel_color = render_sub((t_basket *)arg, i, j, pixel_color);
			my_mlx_pixel_put(((t_basket *)arg)->scene->img, j, i,
								vdivide(pixel_color, PIXEL_PER_COLOR));
			j += THREAD;
		}
		i--;
	}
	return (0);
}

void	*multi_render(void *arg)
{
	int			i;
	int			j;
	t_color		pixel_color;
	t_basket	bask;

	bask = *(t_basket *)arg;
	i = bask.scene->canv.height - 1;
	while (i >= 0)
	{
		j = bask.lane;
		while (j < bask.scene->canv.width)
		{
			pixel_color = color(0, 0, 0);
			pixel_color = render_sub((t_basket *)arg, i, j, pixel_color);
			my_mlx_pixel_put(bask.scene->img, j, i, pixel_color);
			j += THREAD;
		}
		i--;
	}
	return (0);
}

void	all_render(t_cntl *cntl, int mode)
{
	pthread_t	new[THREAD];
	t_basket	bask[THREAD];
	int			i;
	int			j;

	ft_printf("rendering...............\n");
	i = -1;
	while (++i < THREAD)
	{
		bask[i].lane = i;
		bask[i].scene = cntl->scene;
		bask[i].light_on = cntl->light_on;
		if (mode == PRERANDER)
			pthread_create(&new[i], NULL, multi_render, &(bask[i]));
		else if (mode == ALLRANDER)
			pthread_create(&new[i], NULL, multi_all_render, &(bask[i]));
	}
	j = -1;
	while (++j < THREAD)
		pthread_join(new[j], NULL);
	ft_printf("*****rendering complete*****\n");
}
