/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 01:34:38 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 01:35:20 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <time.h>
#include "get_next_line.h"
#include "structure.h"
#include "camera.h"
#include "vector.h"
#include "ray.h"
#include "hit.h"
#include "lighting.h"
#include "parsing.h"
#include "mlxutil.h"
#include "render.h"
#include "control.h"

void	scene_init(t_cntl *cntl)
{
	if ((cntl->scene = (t_scene *)malloc(sizeof(t_scene))) == 0)
		eerror("Error\nSceneinit Fail!!!\n");
	cntl->scene->world = 0;
	cntl->scene->canv.height = -1;
	cntl->scene->canv.width = -1;
	cntl->scene->canv.amb_light = -1;
	cntl->scene->canv.color = color(-1, -1, -1);
	cntl->scene->cam_list = 0;
	cntl->mode = 0;
	cntl->light_on = LIGHT_ON;
	if ((cntl->img = (t_data *)malloc(sizeof(t_data))) == 0)
		eerror("Error\nSceneinit Fail!!!\n");
}

void	set_cntl_win(t_cntl *cntl)
{
	cntl->win = mlx_new_window(cntl->mlx, cntl->scene->canv.width,
				cntl->scene->canv.height, "mijeong's minirt!");
	cntl->img->img = mlx_new_image(cntl->mlx, cntl->scene->canv.width,
				cntl->scene->canv.height);
	cntl->img->addr = mlx_get_data_addr(cntl->img->img,
				&cntl->img->bits_per_pixel, &cntl->img->line_length,
				&cntl->img->endian);
	cntl->scene->img = cntl->img;
}

int		main(int ac, char **av)
{
	t_cntl		cntl;
	t_std_set	s_set;

	if (ac != 2 && ac != 3)
		eerror("인수 갯수틀립니다.\n");
	cntl.mlx = mlx_init();
	scene_init(&cntl);
	parsing(&cntl, av[1]);
	cntl_display_resolution(&cntl);
	set_cntl_win(&cntl);
	cntl.scene->cam_onair = cntl.scene->cam_list->data;
	set_camera(cntl.scene->cam_onair);
	all_render(&cntl, PRERANDER);
	if (ac == 3 && ft_strncmp("--save", av[2], 6) == 0)
		bmp_save(&cntl);
	mlx_put_image_to_window(cntl.mlx, cntl.win, cntl.img->img, 0, 0);
	my_mlx_control(&cntl);
}
