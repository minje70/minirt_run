#include "hit.h"

t_objects	*obj_last(t_objects *obj)
{
	if (obj == 0)
		return (0);
	while (obj->next)
		obj = obj->next;
	return (obj);
}

void	obj_add_back(t_objects **obj, t_objects *new_obj)
{
	if (*obj == 0)
	{
		*obj = new_obj;
		return ;
	}
	obj_last(*obj)->next = new_obj;
}

void object_clear(t_objects **obj)
{
	t_objects	*temp;
	while (*obj)
	{
		temp = (*obj)->next;
		free((*obj)->data);
		// 메모리 leak이 생길 수 있다. 주의!!
		// del((*lst)->content);
		free(*obj);
		*obj = temp;
	}
}

t_bool hit(t_ray *r, t_hitrec *rec, t_objects *object)
{
	t_hitrec temp_rec;
	t_bool hit_anything = 0;
	double closest_so_far = rec->tmax;
	temp_rec.tmax = rec->tmax;
	temp_rec.tmin = rec->tmin;
	while (object)
	{
		if (object_hit(r, &temp_rec, object))
		{
			hit_anything = 1;
			if (closest_so_far > temp_rec.t)
			{
				closest_so_far = temp_rec.t;
				*rec = temp_rec;
			}
		}
		object = object->next;
	}
	// dprintf(2, "%d\n", hit_anything);
	return (hit_anything);
}

t_bool object_hit(t_ray *r, t_hitrec *rec, t_objects *object)// 실린더 돌려보자!!!!!!!!!!!!!
{
	t_point3	offset;
	t_bool		result;

	offset = point3(0, 0, 0);
	if (object->type == SP)
		result = hit_sphere(object->data, r, rec);
	else if (object->type == PL)
		result = hit_plane(object->data, r, rec);
	else if (object->type == TR)
		result = hit_triangle(object->data, r, rec);
	else if (object->type == CY)
		result = check_cy_rotate(object, rec, r, &offset);
	else if (object->type == SQ)
		result = hit_square(object->data, r, rec);
	else
		result = 0;
	
	ray_normal_back(rec, &object->rotate, &offset);
	return (result);
}

t_objects *set_object(int type, void *data)
{
	t_objects *result;

	result = (t_objects *)malloc(sizeof(t_objects));
	result->data = data;
	result->type = type;
	result->next = 0;
	result->rotate = point3(0, 0, 30);
	return (result);
}
