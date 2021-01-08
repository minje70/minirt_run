/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:32:54 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/07 13:53:25 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void	cntl_display_resolution(t_cntl *cntl)
{
	int	x;
	int	y;

	mlx_get_screen_size(cntl->mlx, &x, &y);
	if (cntl->scene->canv.width > x)
		cntl->scene->canv.width = x;
	if (cntl->scene->canv.height > y)
		cntl->scene->canv.height = y;
}
