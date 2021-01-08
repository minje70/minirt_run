/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 01:23:53 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 01:23:59 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# define THREAD 16

# include "structure.h"
# include "hit.h"
# include "pthread.h"
# include "uutil.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, t_color color);
void	all_render(t_cntl *cntl, int mode);
t_color	draw_rainbow(t_hitrec *rec);

#endif
