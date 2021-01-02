#include "vector.h"

//벡터3 생성자
t_vec	vec3(double x, double y, double z)
{
	t_vec vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

//포인트3 생성자
t_point3 point3(double x, double y, double z)
{
	t_point3 point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

//색상3 생성자
t_point3 color(double r, double g, double b)
{
	t_color color;

	color.x = r;
	color.y = g;
	color.z = b;
	return (color);
}

// 벡터 값 설정
void	vset(t_vec *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

// 벡터 길이 제곱
double	vlength2(t_vec vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

// 벡터 길이
double	vlength(t_vec vec)
{
	return (sqrt(vlength2(vec)));
}

// 벡터합
t_vec	vplus(t_vec vec, t_vec vec2)
{
	vec.x += vec2.x;
	vec.y += vec2.y;
	vec.z += vec2.z;
	return (vec);
}

// 벡터합2
t_vec	vplus_(t_vec vec, double x, double y, double z)
{
	vec.x += x;
	vec.y += y;
	vec.z += z;
	return (vec);
}

// 벡터차
t_vec	vminus(t_vec vec, t_vec vec2)
{
	vec.x -= vec2.x;
	vec.y -= vec2.y;
	vec.z -= vec2.z;
	return (vec);
}

t_vec	vminus_(t_vec vec, double x, double y, double z)
{
	vec.x -= x;
	vec.y -= y;
	vec.z -= z;
	return (vec);
}

// 벡터 * 스칼라 곱연산
t_vec	vmult(t_vec vec, double t)
{
	vec.x *= t;
	vec.y *= t;
	vec.z *= t;
	return (vec);
}

// 벡터 축 값끼리 곱연산
t_vec	vmult_(t_vec vec, t_vec vec2)
{
	vec.x *= vec2.x;
	vec.y *= vec2.y;
	vec.z *= vec2.z;
	return (vec);
}

// 벡터 스칼라 나누기
t_vec	vdivide(t_vec vec, double t)
{
	double temp;
	temp = 1 / t;
	vec.x *= temp;
	vec.y *= temp;
	vec.z *= temp;

	return vec;
}

// 벡터 내적
double	vdot(t_vec vec, t_vec vec2)
{
	return (vec.x * vec2.x + vec.y * vec2.y + vec.z * vec2.z);
}

// 벡터 외적
t_vec	vcross(t_vec vec, t_vec vec2)
{
	t_vec new;

	new.x = vec.y * vec2.z - vec.z * vec2.y;
	new.y = vec.z * vec2.x - vec.x * vec2.z;
	new.z = vec.x * vec2.y - vec.y * vec2.x;
	return (new);
}

// 단위 벡터
t_vec	vunit(t_vec vec)
{
	double len = vlength(vec);
	if (len == 0)
	{
		perror("Devider is 0");
		exit(1);
	}
	len = 1/len;
	vec.x *= len;
	vec.y *= len;
	vec.z *= len;
	return (vec);
}

t_vec	yzero(t_vec vec)
{
	vec.y = 0;
	return (vec);
}

t_vec	vsymmetric(t_point3 p1, t_point3 stan)
{
	t_point3	result;

	result.x = 2 * stan.x - p1.x;
	result.y = 2 * stan.y - p1.y;
	result.z = 2 * stan.z - p1.z;

	return (result);
}