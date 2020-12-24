#include "hit.h"

t_bool	hit_cylinder(t_cylinder *cy, t_ray *r, t_hitrec *rec)
{
	// obj->rotate 가지고 회전시키기.
	double a = vlength2(vminus(r->dir, vmult(cy->v, vdot(cy->v, r->dir))));
	double half_b = vdot(vminus(r->dir, vmult(cy->v, vdot(cy->v, r->dir))), vminus(vminus(r->orig, cy->p), vmult(cy->v ,vdot(cy->v, vminus(r->orig, cy->p)))));
	double c = vlength2(vminus(vminus(r->orig, cy->p), vmult(cy->v ,vdot(cy->v, vminus(r->orig, cy->p))))) - cy->r * cy->r;
	double discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
		return (0);
	double sqrtd = sqrt(discriminant);
	double root = (-half_b - sqrtd) / a;

	if (root < rec->tmin || root > rec->tmax)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || root > rec->tmax)
			return (0);
		else if (vdot(cy->v, vminus(cy->p2, ray_at(*r, root))) < 0 || vdot(cy->v, vminus(cy->p, ray_at(*r, root))) > 0)
			return (0);
	}
	else if (vdot(cy->v, vminus(cy->p2, ray_at(*r, root))) < 0 || vdot(cy->v, vminus(cy->p, ray_at(*r, root))) > 0)
	{
		root = (-half_b + sqrtd) / a;
		if (vdot(cy->v, vminus(cy->p2, ray_at(*r, root))) < 0 || vdot(cy->v, vminus(cy->p, ray_at(*r, root))) > 0)
			return (0);
	}
	rec->t = root;
	rec->p = ray_at(*r, rec->t);
	rec->normal = vdivide(vminus(vminus(rec->p, cy->p), vmult(cy->v, vdot(cy->v, vminus(rec->p, cy->p)))), cy->r);
	rec->obj_color = cy->color;
	set_face_normal(r, rec);
	return (1);
}

t_bool	hit_square(t_square *sq, t_ray *r, t_hitrec *rec)
{
	t_point3	p1;
	t_point3	p2;
	t_point3	p3;
	t_point3	p4;
	t_vec		temp;
	double		root;

	root = vdot(vminus(sq->p, r->orig), sq->n) / vdot(sq->n, r->dir);
	if (root < 0 || root < rec->tmin || root > rec->tmax)
	{
		return (0);
	}
	p1 = vmult(vunit(vcross(vminus(yzero(sq->p), sq->p), sq->n)), sq->len / 2);
	p3 = vmult(vunit(vcross(vminus(sq->p, yzero(sq->p)), sq->n)), sq->len / 2);
	p3 = vplus(vplus(p3, vmult(vunit(vcross(p1, sq->n)), sq->len / 2)), sq->p);
	p1 = vplus(vplus(p1, vmult(vunit(vcross(p1, sq->n)), sq->len / 2)), sq->p);
	p2 = vsymmetric(p1, sq->p);
	p4 = vsymmetric(p3, sq->p);
	// dprintf(2, "p1:%f, %f, %f\np2:%f, %f, %f\np3:%f, %f, %f\np4:%f, %f, %f\n", p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z, p4.x, p4.y, p4.z);
	temp = ray_at(*r, root);
	// dprintf(2, "temp:%f, %f, %f\n\n", temp.x, temp.y, temp.z);
	// dprintf(2, "inside check : %d\n", (is_inside_(p1, p2, p4, temp)));
	if (!(is_inside_(p1, p2, p3, temp) || is_inside_(p1, p2, p4, temp)))
	{
		return (0);
	}
	rec->t = root;
	rec->p = temp;
	rec->normal = sq->n;
	rec->obj_color = sq->color;
	set_face_normal(r, rec);
	return (1);
}