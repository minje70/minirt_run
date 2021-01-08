/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 23:51:01 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 00:04:17 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"

void	min_max_check(t_hitrec *rec, int *width, int *height)
{
	if (*height >= 3 * rec->texture.l)
		*height = 3 * rec->texture.l - 1;
	else if (*height < 0)
		*height = 0;
	if (*width >= 4 * rec->texture.l)
		*width = 4 * rec->texture.l - 1;
	else if (*width < 0)
		*width = 0;
}

void	set_skybox_img(t_cntl *cntl, t_cube *cu, char *filename)
{
	int	width;
	int	height;

	cu->texture->img = (t_data *)malloc(sizeof(t_data));
	if (cu->texture->img == 0)
		eerror("Error\nsky box can not init!!\n");
	cu->texture->img->img = mlx_png_file_to_image(cntl->mlx, filename, &width,
				&height);
	cu->texture->img->addr = mlx_get_data_addr(cu->texture->img->img,
				&cu->texture->img->bits_per_pixel,
				&cu->texture->img->line_length, &cu->texture->img->endian);
	cu->texture->l = width / 4;
}

int		saturate_w(int w, int l, t_hitrec *rec)
{
	if (rec->normal.z == 1.0)
		w = 2 * l + w;
	else if (rec->normal.z == -1.0)
		w = 4 * l + w;
	else if (rec->normal.x == 1.0)
		w = 1 * l + w;
	else if (rec->normal.x == -1.0)
		w = 3 * l + w;
	else if (rec->normal.y == 1.0)
		w = 1 * l - w;
	else if (rec->normal.y == -1.0)
		w = 1 * l - w;
	return (w);
}

int		saturate_h(int h, int l, t_hitrec *rec)
{
	if (rec->normal.z == 1.0)
		h = 2 * l - h;
	else if (rec->normal.z == -1.0)
		h = 2 * l - h;
	else if (rec->normal.x == 1.0)
		h = 2 * l - h;
	else if (rec->normal.x == -1.0)
		h = 2 * l - h;
	else if (rec->normal.y == 1.0)
		h = 2 * l + h;
	else if (rec->normal.y == -1.0)
		h = 0 * l + h;
	return (h);
}
