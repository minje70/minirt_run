/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mijeong <minje70@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:06:47 by mijeong           #+#    #+#             */
/*   Updated: 2021/01/07 17:07:16 by mijeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"

t_objects	*obj_last(t_objects *obj)
{
	if (obj == 0)
		return (0);
	while (obj->next)
		obj = obj->next;
	return (obj);
}

void		obj_add_back(t_objects **obj, t_objects *new_obj)
{
	if (*obj == 0)
	{
		*obj = new_obj;
		return ;
	}
	obj_last(*obj)->next = new_obj;
}

void		object_clear(t_objects **obj)
{
	t_objects	*temp;

	while (*obj)
	{
		temp = (*obj)->next;
		free((*obj)->data);
		free(*obj);
		*obj = temp;
	}
}

t_objects	*set_object(int type, void *data)
{
	t_objects	*result;

	result = (t_objects *)malloc(sizeof(t_objects));
	result->data = data;
	result->type = type;
	result->next = 0;
	result->rotate = point3(0, 0, 0);
	return (result);
}
