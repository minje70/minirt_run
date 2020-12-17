#include "hit.h"

t_sphere *set_sphere(t_point3 center, double radius, t_color objcolor)
{
	t_sphere *sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	sphere->radius = radius;
	sphere->center = center;
	sphere->obj_color = objcolor;
	return (sphere);
}

t_plane *set_plane(t_point3 point, t_color color, t_vec normal)
{
	t_plane *plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	plane->p = point;
	plane->normal = vunit(normal);
	plane->color = color;
	return (plane);
}

t_triangle	*set_triangle(t_point3 p1, t_point3 p2, t_point3 p3, t_color color)
{
	t_triangle *tri;
	t_vec	temp;

	tri = (t_triangle *)malloc(sizeof(t_triangle));
	tri->p1 = p1;
	tri->p2 = p2;
	tri->p3 = p3;
	tri->color = color;
	temp = vcross(vminus(p2, p1), vminus(p3, p1));
	tri->normal = vdivide(temp, vlength(temp));
	return (tri);
}

t_cylinder	*set_cylinder(t_point3 p, t_point3 p2, double r, t_color color)
{
	t_cylinder	*cyl;

	cyl = (t_cylinder *)malloc(sizeof(t_cylinder));
	cyl->p = p;
	cyl->p2 = p2;
	cyl->r = r;
	cyl->v = vunit(vdivide(vminus(p2, p), vlength(vminus(p2, p))));
	cyl->color = color;
	return (cyl);
}

t_square	*set_square(t_point3 p, t_vec n, t_color color, double len)
{
	t_square	*square;

	square = (t_square *)malloc(sizeof(t_square));
	square->p = p;
	square->n = vunit(n);
	square->len = len;
	square->color = color;
	return (square);
}