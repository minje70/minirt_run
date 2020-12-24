#include "move.h"

void	rotate_r(t_ray *r, t_rotate rot)
{
	rotate_v(&r->orig, rot);
	rotate_v(&r->dir, rot);
}

// obj 받아서 obj 다 변경

t_bool	check_cy_rotate(t_objects *obj, t_hitrec *rec, t_ray *r, t_point3 *offset)
{
	t_cylinder	t_cy;
	t_ray		t_r;

	// dprintf(2, "1obj%f, %f, %f\n", (t_cy).p.x, (t_cy).p.y, (t_cy).p.z);
	t_cy = *(t_cylinder *)obj->data;
	t_r = *r;
	*offset = vmult(vplus((*(t_cylinder *)obj->data).p, (*(t_cylinder *)obj->data).p2), 0.5);
	t_r.orig = vminus(t_r.orig, *offset);
	t_cy.p2 = vminus(t_cy.p2, *offset);
	t_cy.p = vminus(t_cy.p, *offset);
	rotate_r(&t_r, obj->rotate);
	*offset = vmult(*offset, -1.0);
	return (hit_cylinder(&t_cy, &t_r, rec));
}

void	ray_normal_back(t_hitrec *rec, t_rotate *rot, t_point3 *offset)
{
	rotate_v(&rec->p, vmult(*rot, -1));
	rec->p = vminus(rec->p, *offset);
	rotate_v(&rec->normal, vmult(*rot, -1));
}