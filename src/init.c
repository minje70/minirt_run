#include "hit.h"

t_sphere *set_sphere(t_point3 center, double radius, t_color objcolor)
{
	t_sphere *sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (sphere == 0)
		eerror("Error\nsphere init fail!!\n");
	sphere->radius = radius;
	sphere->center = center;
	sphere->obj_color = objcolor;
	return (sphere);
}

t_plane *set_plane(t_point3 point, t_vec normal, t_color color)
{
	t_plane *plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	if (plane == 0)
		eerror("Error\nplane init fail!!\n");
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
	if (tri == 0)
		eerror("Error\ntriangle init fail!!\n");
	tri->p1 = p1;
	tri->p2 = p2;
	tri->p3 = p3;
	tri->color = color;
	temp = vcross(vminus(p2, p1), vminus(p3, p1));
	tri->normal = vdivide(temp, vlength(temp));
	return (tri);
}

t_cylinder	*set_cylinder(t_point3 p, t_vec v, double r, double h, t_color color)
{
	t_cylinder	*cyl;

	cyl = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (cyl == 0)
		eerror("Error\ncylinder init fail!!\n");
	cyl->h = h;
	cyl->p = p;
	cyl->p2 = vplus(p, vmult(v, h));
	cyl->r = r;
	cyl->v = vunit(v);
	cyl->color = color;
	return (cyl);
}

t_square	*set_square(t_point3 p, t_vec n, double len, t_color color)
{
	t_square	*square;

	square = (t_square *)malloc(sizeof(t_square));
	if (square == 0)
		eerror("Error\nsquare init fail!!\n");
	square->p = p;
	square->n = vunit(n);
	if (square->n.y == 1)
		square->n = vec3(0,0.999,0.00001);
	else if (square->n.y == -1)
		square->n = vec3(0, -0.999, 0.00001);
	square->len = len;
	square->color = color;
	return (square);
}
t_cube		*set_cube(t_point3 p, double len, t_color color)
{
	t_cube	*cube;

	cube = (t_cube *)malloc(sizeof(t_cube));
	if (cube == 0)
		eerror("Error\ncube init fail!!\n");
	cube->sq[0] = set_square(vplus(p, vmult(vec3(0, 0, 1), len / 2)), vec3(0, 0, 1), len, color);
	cube->sq[1] = set_square(vplus(p, vmult(vec3(0, 0, -1), len / 2)), vec3(0, 0, -1), len, color);
	cube->sq[2] = set_square(vplus(p, vmult(vec3(0, 1, 0), len / 2)), vec3(0, 1, 0), len, color);
	cube->sq[3] = set_square(vplus(p, vmult(vec3(0, -1, 0), len / 2)), vec3(0, -1, 0), len, color);
	cube->sq[4] = set_square(vplus(p, vmult(vec3(1, 0, 0), len / 2)), vec3(1, 0, 0), len, color);
	cube->sq[5] = set_square(vplus(p, vmult(vec3(-1, 0, 0), len / 2)), vec3(-1, 0, 0), len, color);
	return (cube);
}

t_pyramid	*set_pyramid(t_point3 p, double len, double h, t_color color)
{
	t_pyramid	*py;
	t_point3	pp[4];
	t_point3	top;

	py = (t_pyramid *)malloc(sizeof(t_pyramid));
	if (py == 0)
		eerror("Error\npyramid init fail!!\n");
	py->color = color;
	py->p = p;
	py->len = len;
	py->sq = set_square(p, vec3(0,-1,0), len, color);
	pp[0] = vmult(vunit(vcross(vminus(yzero(py->sq->p), py->sq->p), py->sq->n)), py->sq->len / 2);
	pp[2] = vmult(vunit(vcross(vminus(py->sq->p, yzero(py->sq->p)), py->sq->n)), py->sq->len / 2);
	pp[2] = vplus(vplus(pp[2], vmult(vunit(vcross(pp[0], py->sq->n)), py->sq->len / 2)), py->sq->p);
	pp[0] = vplus(vplus(pp[0], vmult(vunit(vcross(pp[0], py->sq->n)), py->sq->len / 2)), py->sq->p);
	pp[1] = vsymmetric(pp[0], py->sq->p);
	pp[3] = vsymmetric(pp[2], py->sq->p);
	top = vplus(p, vmult(vec3(0, 1, 0), h));
	py->tr[0] = set_triangle(pp[0], pp[2], top, color);
	py->tr[1] = set_triangle(pp[2], pp[1], top, color);
	py->tr[2] = set_triangle(pp[1], pp[3], top, color);
	py->tr[3] = set_triangle(pp[3], pp[0], top, color);
	return (py);
}