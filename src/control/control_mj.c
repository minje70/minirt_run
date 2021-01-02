#include "control.h"

// void	cntl_display_resolution(t_cntl *cntl)
// {
// 	int	x;
// 	int	y;

// 	mlx_get_screen_size(cntl->mlx, &x, &y);
// 	if (cntl->scene->canv.width > x)
// 		cntl->scene->canv.width = x;
// 	if (cntl->scene->canv.height > y)
// 		cntl->scene->canv.height = y;
// }

// void	cntl_camera_off(t_cntl *cntl)
// {
// 	cntl->mode = 0;
// 	printf("default mode!\n");
// }

// void	cntl_camera_on(t_cntl *cntl)
// {
// 	cntl->mode = 2;
// 	printf("< camera mode >!\n[right arrow] key : next camera\n");
// 	printf("[w,a,s,d] : move\n[q,e] key : fov\n[mouse click, wheel] : rotate\n");
// 	printf("to default mode : [esc] key\n");
// }

// void	cntl_select_camera(t_cntl *cntl)
// {
// 	t_objects	*temp;

// 	temp = (t_objects *)cntl->scene->cam_list;
// 	while (cntl->scene->cam_onair != (t_camera *)temp->element)
// 		temp = temp->next;
// 	if (temp->next == 0)
// 	{
// 		printf("마지막 캠입니다.\n");
// 		cntl->scene->cam_onair = (t_camera *)cntl->scene->cam_list->element;
// 	}
// 	else
// 	{
// 		printf("다음캠입니다.\n");
// 		cntl->scene->cam_onair = ((t_objects *)temp->next)->element;
// 	}
// }

// void	cntl_camera_translate(int keycode, t_cntl *cntl)
// {
// 	t_camera	*camera;

// 	camera = cntl->scene->cam_onair;
// 	if (keycode == 13) // w
// 		camera->orig = vplus(camera->orig, vmult(camera->dir, 0.1));
// 	else if (keycode == 1) // s
// 		camera->orig = vplus(camera->orig, vmult(camera->dir, -0.1));
// 	else if (keycode == 0) // a
// 		camera->orig = vplus(camera->orig, vcross(vmult(camera->dir, -0.1), camera->vertical));
// 	else if (keycode == 2) // d
// 		camera->orig = vplus(camera->orig, vcross(vmult(camera->dir, 0.1), camera->vertical));
// }

// void	cntl_camera(t_cntl *cntl, int keycode)
// {
// 	if (keycode == 53) // 카메라 모드에서 나감. esc
// 		cntl_camera_off(cntl);
// 	else if (keycode == 124) // 카메라 바꾸기. 오른쪽 방향키
// 		cntl_select_camera(cntl);
// 	else if (keycode == 12 || keycode == 14) // 카메라 화각
// 		cntl_camera_hfov(keycode, cntl);
// 	else					// 카메라 이동. wasd
// 		cntl_camera_translate(keycode, cntl);
// 	printf("now mode : %d\n", cntl->mode);
// 	camera_set(&cntl->scene->canv, cntl->scene->cam_onair);
// 	(cntl->scene, cntl->img);
// 	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
// }

// void	cntl_camera_hfov(int keycode, t_cntl *cntl)
// {
// 	t_camera	*camera;

// 	camera = cntl->scene->cam_onair;
// 	if (keycode == 12) // q
// 	{
// 		camera->hfov += 5;
// 		if (camera->hfov >= 180)
// 			camera->hfov = 180;
// 	}
// 	else if (keycode == 14) // e
// 	{
// 		camera->hfov -= 5;
// 		if (camera->hfov <= 0)
// 			camera->hfov = 0;
// 	}
// }