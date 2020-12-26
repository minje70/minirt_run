#include "hit.h"

void vpoint(t_point3 p)
{
	dprintf(2, "%f, %f, %f ", p.x, p.y, p.z);
}

t_sphere *set_sphere(t_point3 center, double radius, t_color objcolor)
{
	t_sphere *sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	sphere->radius = radius;
	sphere->center = center;
	sphere->obj_color = objcolor;
	dprintf(2, "sphere\n");
	return (sphere);
}

t_plane *set_plane(t_point3 point, t_vec normal, t_color color)
{
	t_plane *plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	plane->p = point;
	plane->normal = vunit(normal);
	plane->color = color;
	dprintf(2, "plane\n");
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
	dprintf(2, "triangle\n");
	return (tri);
}

t_cylinder	*set_cylinder(t_point3 p, t_vec v, double r, double h, t_color color)
{
	t_cylinder	*cyl;

	cyl = (t_cylinder *)malloc(sizeof(t_cylinder));
	cyl->p = p;
	cyl->p2 = vplus(p, vmult(v, h));
	cyl->r = r;
	cyl->v = vunit(v);
	cyl->color = color;
	dprintf(2, "cylinder\n");
	return (cyl);
}

t_square	*set_square(t_point3 p, t_vec n, double len, t_color color)
{
	t_square	*square;

	square = (t_square *)malloc(sizeof(t_square));
	square->p = p;
	square->n = vunit(n);
	square->len = len;
	square->color = color;
	dprintf(2, "square\n");
	return (square);
}