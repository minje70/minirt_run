/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 01:21:40 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 01:21:44 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVE_H
# define MOVE_H
# include "structure.h"
# include "vector.h"
# include "uutil.h"
# include "hit.h"

void	rotate_r(t_ray *r, t_rotate rot);
t_bool	check_cy_rotate(t_objects *obj, t_hitrec *rec, t_ray *r);
t_bool	check_tr_rotate(t_objects *obj, t_hitrec *rec, t_ray *r);
t_bool	check_sq_rotate(t_objects *obj, t_hitrec *rec, t_ray *r);
t_bool	check_pl_rotate(t_objects *obj, t_hitrec *rec, t_ray *r);
void	ray_normal_back(t_hitrec *rec, t_rotate *rot, t_point3 *offset);
t_bool	check_cu_rotate(t_objects *obj, t_hitrec *rec, t_ray *r);
t_bool	check_py_rotate(t_objects *obj, t_hitrec *rec, t_ray *r);

#endif
