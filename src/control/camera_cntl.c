#include "control.h"

void	cntl_camera_off(t_cntl *cntl)
{
	cntl->mode = 0;
	printf("default mode!\n");
}

void	cntl_camera_on(t_cntl *cntl)
{
	cntl->mode = 2;
	printf("< camera mode >!\n[right arrow] key : next camera\n");
	printf("[w,a,s,d] : move\n[q,e] key : fov\n[mouse click, wheel] : rotate\n");
	printf("to default mode : [esc] key\n");
}

void	cntl_select_camera(t_cntl *cntl)
{
	t_objects	*temp;

	temp = (t_objects *)cntl->scene->cam_list;
	while (cntl->scene->cam_onair != (t_camera *)temp->data)
		temp = temp->next;
	if (temp->next == 0)
	{
		printf("마지막 캠입니다.\n");
		cntl->scene->cam_onair = (t_camera *)cntl->scene->cam_list->data;
	}
	else
	{
		printf("다음캠입니다.\n");
		cntl->scene->cam_onair = ((t_objects *)temp->next)->data;
	}
}

void	cntl_camera_translate(int keycode, t_cntl *cntl)
{
	t_camera	*camera;

	camera = cntl->scene->cam_onair;
	if (keycode == KEY_W) // w
		camera->origin = vplus(camera->origin, vmult(camera->w, 0.2));
	else if (keycode == KEY_S) // s
		camera->origin = vplus(camera->origin, vmult(camera->w, -0.2));
	else if (keycode == KEY_A) // a
		camera->origin = vplus(camera->origin, vcross(vmult(camera->w, -0.2), camera->vertical));
	else if (keycode == KEY_D) // d
		camera->origin = vplus(camera->origin, vcross(vmult(camera->w, 0.2), camera->vertical));
}

void	cntl_camera(t_cntl *cntl, int keycode)
{
	if (keycode == KEY_ESC) // 카메라 모드에서 나감. esc
		cntl_camera_off(cntl);
	else if (keycode == KEY_AR_R) // 카메라 바꾸기. 오른쪽 방향키
		cntl_select_camera(cntl);
	else if (keycode == KEY_E || keycode == KEY_Q) // 카메라 화각
		cntl_camera_fov(keycode, cntl);
	else					// 카메라 이동. wasd
		cntl_camera_translate(keycode, cntl);
	printf("now mode : %d\n", cntl->mode);
	set_camera(cntl->scene->cam_onair);
	all_render(cntl);
	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
}

void	cntl_camera_fov(int keycode, t_cntl *cntl)
{
	t_camera	*camera;

	camera = cntl->scene->cam_onair;
	if (keycode == KEY_Q) // q
	{
		camera->fov += 5;
		if (camera->fov >= 180)
			camera->fov = 180;
	}
	else if (keycode == KEY_E) // e
	{
		camera->fov -= 5;
		if (camera->fov <= 0)
			camera->fov = 0;
	}
}

void	cntl_cam_rotate(int button, t_cntl *cntl)
{
	t_camera	*cam;
	t_rotate	rot;

	cam = cntl->scene->cam_onair;
	if (button == 1 || button == 7) // -> 좌클릭
		rot = vec3(0, 10, 0);
	else if (button == 2 || button == 6) // -> 방향키 왼쪽
		rot = vec3(0,-10,0);
	else if (button == 5) // up
		rot = vec3(10,0,0);
	else if (button == 4) // down
		rot = vec3(-10,0,0);
	else
	{
		printf("you click button : %d\n", button);
		return ;
	}
	rotate_v(&cam->w, rot);
	set_camera(cntl->scene->cam_onair);
	all_render(cntl);
	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
}
