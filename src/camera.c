#include "camera.h"

t_camera set_camera(t_camera camera, double ratio, double viewport_h)
{
	camera.viewport_h = viewport_h;
	camera.viewport_w = viewport_h * ratio;
	camera.focal_len = 1;

	camera.origin = point3(0, 0, 0);
	camera.horizontal = vec3(camera.viewport_w, 0, 0);
	camera.vertical = vec3(0, camera.viewport_h, 0);
	// origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_len)
	camera.lower_left_corner = vminus(vminus(vminus(camera.origin, vdivide(camera.horizontal, 2)), vdivide(camera.vertical, 2)), vec3(0, 0, camera.focal_len));

	return (camera);
}