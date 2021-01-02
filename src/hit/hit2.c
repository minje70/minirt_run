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
	rec->p = vplus(rec->p, vmult(rec->normal, 0.001));
	// rec->p = vplus(rec->p, rec->normal);
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
		return (0);
	p1 = vmult(vunit(vcross(vminus(yzero(sq->p), sq->p), sq->n)), sq->len / 2);
	p3 = vmult(vunit(vcross(vminus(sq->p, yzero(sq->p)), sq->n)), sq->len / 2);
	p3 = vplus(vplus(p3, vmult(vunit(vcross(p1, sq->n)), sq->len / 2)), sq->p);
	p1 = vplus(vplus(p1, vmult(vunit(vcross(p1, sq->n)), sq->len / 2)), sq->p);
	p2 = vsymmetric(p1, sq->p);
	p4 = vsymmetric(p3, sq->p);
	temp = ray_at(*r, root);
	if (!(is_inside_(p1, p2, p3, temp) || is_inside_(p1, p2, p4, temp)))
		return (0);
	rec->t = root;
	rec->p = temp;
	rec->normal = sq->n;
	rec->obj_color = sq->color;
	set_face_normal(r, rec);
	// rec->p = vplus(rec->p, vmult(rec->normal, 0.001));
	return (1);
}

t_bool	hit_cube(t_cube *cu, t_ray *r, t_hitrec *rec)
{
	int			i;
	int			hit_anything;
	t_hitrec	*temp_rec;

	temp_rec = rec;
	hit_anything = 0;
	i = -1;
	while (++i < 6)
	{
		if (hit_square(cu->sq[i], r, temp_rec))
		{
			hit_anything = 1;
			temp_rec->tmax = temp_rec->t;
			*rec = *temp_rec;
		}
	}
	return (hit_anything);
}

t_bool	hit_pyramid(t_pyramid *py, t_ray *r, t_hitrec *rec)
{
	int			i;
	int			hit_anything;
	t_hitrec	*temp_rec;

	temp_rec = rec;
	hit_anything = 0;
	i = -1;
	while (++i < 4)
	{
		if (hit_triangle(py->tr[i], r, temp_rec))
		{
			hit_anything = 1;
			temp_rec->tmax = temp_rec->t;
			*rec = *temp_rec;
		}
	}
	if (hit_square(py->sq, r, temp_rec))
	{
		hit_anything = 1;
		temp_rec->tmax = temp_rec->t;
		*rec = *temp_rec;
	}
	return (hit_anything);
}