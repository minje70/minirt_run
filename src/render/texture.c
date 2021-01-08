/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 23:51:05 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 16:32:01 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"

t_color	skybox_albedo(t_hitrec *rec)
{
	int	dst;
	int	width;
	int	height;

	width = rec->u * rec->texture.l;
	height = rec->v * rec->texture.l;
	width = saturate_w(width, rec->texture.l, rec);
	height = saturate_h(height, rec->texture.l, rec);
	height = height - 1;
	min_max_check(rec, &width, &height);
	dst = *(int *)(rec->texture.img->addr + (height *
			rec->texture.img->line_length + width *
			(rec->texture.img->bits_per_pixel / 8)));
	rec->texture.albedo1.x = (dst >> 16 & 0xFF) / 255.0;
	rec->texture.albedo1.y = (dst >> 8 & 0xFF) / 255.0;
	rec->texture.albedo1.z = (dst & 0xFF) / 255.0;
	return (rec->texture.albedo1);
}

t_color	sine_wave_albedo(t_hitrec *rec)
{
	double	wave;

	wave = sin(rec->p.x * 40) + 1;
	wave = wave * 0.5;
	return (vmult(rec->texture.albedo1, wave));
}

t_color	checker_albedo(t_hitrec *rec)
{
	double	sines;

	sines = sin(10 * rec->p.x) * sin(10 * rec->p.y) *
			sin(10 * rec->p.z);
	if (sines < 0)
		return (rec->texture.albedo1);
	else
		return (color(1, 1, 1));
}

t_color	checker_uv_albedo(t_hitrec *rec)
{
	double	sines;

	sines = sin(40 * rec->u) * sin(40 * rec->v);
	if (sines < 0)
		return (rec->texture.albedo1);
	else
		return (color(1, 1, 1));
}

t_color	albedo(t_hitrec *rec)
{
	if (rec->texture.type == SOLID)
		return (rec->texture.albedo1);
	else if (rec->texture.type == RAINBOW)
		return (vmult(vplus(rec->normal, color(1, 1, 1)), 0.5));
	else if (rec->texture.type == CHECK_PATTERN)
		return (checker_albedo(rec));
	else if (rec->texture.type == CHECK_UV_PATTERN)
		return (checker_uv_albedo(rec));
	else if (rec->texture.type == WAVE)
		return (sine_wave_albedo(rec));
	else if (rec->texture.type == SKY_BOX)
		return (skybox_albedo(rec));
	return (color(0, 0, 0));
}
