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
	return (hit_cylinder(&t_cy, &t_r, rec));
}

t_bool	check_tr_rotate(t_objects *obj, t_hitrec *rec, t_ray *r, t_point3 *offset)
{
	t_triangle	t_tr;
	t_ray		t_r;

	t_tr = *(t_triangle *)obj->data;
	t_r = *r;
	*offset = vdivide(vplus(t_tr.p1, vplus(t_tr.p2, t_tr.p3)), 3);
	t_r.orig = vminus(t_r.orig, *offset);
	t_tr.p1 = vminus(t_tr.p1, *offset);
	t_tr.p2 = vminus(t_tr.p2, *offset);
	t_tr.p3 = vminus(t_tr.p3, *offset);

	rotate_r(&t_r, obj->rotate);
	return (hit_triangle(&t_tr, &t_r, rec));
}

t_bool	check_sq_rotate(t_objects *obj, t_hitrec *rec, t_ray *r, t_point3 *offset)
{
	t_square	t_sq;
	t_ray		t_r;

	t_sq = *(t_square *)obj->data;
	t_r = *r;
	*offset = vminus(t_sq.p, point3(0.01,0.01,0.01));
	t_r.orig = vminus(t_r.orig, *offset);
	t_sq.p = vminus(t_sq.p, *offset);
	rotate_r(&t_r, obj->rotate);
	return (hit_square(&t_sq, &t_r, rec));
}

void	ray_normal_back(t_hitrec *rec, t_rotate *rot, t_point3 *offset) // 움직이면 light가 이상하게 적용되는거 같다..... 내일해보자.....
{
	rotate_iv(&rec->p, vmult(*rot, -1));
	rec->p = vplus(rec->p, *offset);
	rotate_iv(&rec->normal, vmult(*rot, -1));
	// dprintf(2, "%f %f %f\n", rec->normal.x, rec->normal.y, rec->normal.z);
	// if (vlength(rec->normal) != 0)
	// 	rec->normal = vunit(rec->normal);
}