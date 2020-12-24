#include <stdio.h>
#include "structure.h"
#include "camera.h"
#include "vector.h"
#include "ray.h"
#include "hit.h"
#include "lighting.h"

// void	write_color(t_color color)
// {
// 	color.x = color.x > 1 ? 1 : color.x;
// 	color.y = color.y > 1 ? 1 : color.y;
// 	color.z = color.z > 1 ? 1 : color.z;
// 	printf("%d ", (int)(255.999 * color.x));
// 	printf("%d ", (int)(255.999 * color.y));
// 	printf("%d\n", (int)(255.999 * color.z));
// }

t_color draw_rainbow(t_hitrec *rec)
{
	return (vmult(vplus(rec->normal, color(1,1,1)), 0.5));
}

// t_color ray_color(t_ray *r, t_objects *object, t_camera camera)
// {
// 	t_hitrec rec;

// 	rec.tmin = 0.001;
// 	rec.tmax = infinity;
//     if (hit(r, &rec, object))
// 	{
// 	// dprintf(2, "test\n");
// 		// dprintf(2, "diff %f, %f, %f\n", diff.x, diff.y, diff.z);
// 		// dprintf(2, "rec.normal %f, %f, %f\n", rec.normal.x, rec.normal.y, rec.normal.z);
// 		// dprintf(2, "ambient %f, %f, %f\n", ambient.x, ambient.y, ambient.z);
//         return (hit_light(&rec, object, &camera));
// 	}
//     // t_vec unit_direction = vunit(r->dir);
// 	// double t = 0.5 * (unit_direction.y + 1.0);
//     // return (vplus(vmult(color(1.0, 1.0, 1.0), (1.0 - t)), vmult(color(0.5, 0.7, 1.0), t)));
// 	return (color(0.1, 0.1, 0.1));
// }

// int main()
// {
// 	int height = 400;
// 	double window_ratio = 16.0/9.0;
// 	int width = height * window_ratio;
// 	// camera
// 	t_camera camera;
// 	camera = set_camera(camera, window_ratio, 2);

// 	//world
// 	t_objects *object;
// 	object = 0;
// 	obj_add_back(&object, set_object(SP, set_sphere(point3(3, 0.1, -2), 0.6, color(0.1, 0.2, 0.9))));
// 	obj_add_back(&object, set_object(SP, set_sphere(point3(0, 1, -2), 0.5, color(0.8, 0.2, 0.1))));
// 	obj_add_back(&object, set_object(SP, set_sphere(point3(-1, 0.2,-1), 0.3, color(0.4, 0.2, 1))));

// 	obj_add_back(&object, set_object(CYI, set_cylinder(point3(0, -0.7, -2), point3(0, 1, -2), 0.3, color(0.8, 0.8, 0.2))));

// 	obj_add_back(&object, set_object(SQ, set_square(point3(2, 0.3, -2), vec3(1, 0, -1), color(0.2, 0.8, 0.2), 0.7)));

// 	obj_add_back(&object, set_object(PL, set_plane(point3(0, -0.7, 0), color(0.15, 0.8, 0.34), vec3(0, 1, 0))));

// 	obj_add_back(&object, set_object(TR, set_triangle(point3(-2, 1, -4),point3(0, 5, -4.5), point3(2, 1, -4), color(0.56, 0.34, 0.94))));

// 	obj_add_back(&object, set_object(LI, set_light(color(2, 2, 2), point3(0.5, 0, 0))));
// 	obj_add_back(&object, set_object(LI, set_light(color(2, 2, 2), point3(-1, 1, -1))));
// 	printf("P3\n%d %d\n255\n", width, height);
// 	int i = height - 1;
// 	int j;
// 	while (i >= 0)
// 	{
// 		j = 0;
// 		dprintf(2, "remain: %d\n", i);
// 		while (j < width)
// 		{
// 			double u = (double)j / (width - 1);
// 			double v = (double)i / (height - 1);
// 			t_ray r = ray(camera.origin, vminus(vplus(vplus(camera.lower_left_corner, vmult(camera.horizontal, u)), vmult(camera.vertical, v)), camera.origin));
// 			t_color pixel_color;
// 			// if (i == 197 && j == 362)
// 			// {
// 				pixel_color = ray_color(&r, object, camera);
// 			// }
// 			write_color(pixel_color);
// 			j++;
// 		}
// 		i--;
// 	}
// }