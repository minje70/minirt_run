/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 01:02:00 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/08 01:04:49 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec		vunit(t_vec vec)
{
	double	len;

	len = vlength(vec);
	if (len == 0)
	{
		perror("Devider is 0");
		exit(1);
	}
	len = 1 / len;
	vec.x *= len;
	vec.y *= len;
	vec.z *= len;
	return (vec);
}

t_vec		yzero(t_vec vec)
{
	vec.y = 0;
	return (vec);
}

t_vec		vsymmetric(t_point3 p1, t_point3 stan)
{
	t_point3	result;

	result.x = 2 * stan.x - p1.x;
	result.y = 2 * stan.y - p1.y;
	result.z = 2 * stan.z - p1.z;
	return (result);
}
