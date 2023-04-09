#include "rt.h"

#include <math.h>

void	camera_init(t_rt_conf *conf, t_camera *out)
{
	t_vec3	horiz;
	t_vec3	vert;
	double	fd;
	t_vec3	tmp;

	fd = conf->window_size.x / tan((conf->camera.fov / 180. * M_PI) / 2);
	tmp = conf->camera.origin;
	tmp = vec3_add(tmp, vec3_mul(fd, vec3_uv(conf->camera.direction,
					&horiz, &vert)));
	tmp = vec3_add(tmp, vec3_mul(-conf->window_size.x / 2, horiz));
	tmp = vec3_add(tmp, vec3_mul(-conf->window_size.y / 2, vert));
	out->origin = conf->camera.origin;
	out->left_top = tmp;
	out->horizontal = horiz;
	out->vertical = vert;
}

void	ray_from_camera(t_camera *cam, double x, double y, t_ray *out)
{
	t_pt3	target;

	target = cam->left_top;
	target = vec3_add(target, vec3_mul(x, cam->horizontal));
	target = vec3_add(target, vec3_mul(y, cam->vertical));
	out->origin = cam->origin;
	out->direction = vec3_unit(vec3_sub(target, out->origin));
	out->t_min = MIN_RAY_LENGTH;
	out->t_max = MAX_RAY_LENGTH;
}

void	ray_to_light(t_pt3 pt, t_list_light *light, t_ray *out)
{
	t_vec3	orientation;

	out->origin = pt;
	orientation = vec3_sub(light->origin, out->origin);
	out->direction = vec3_unit(orientation);
	out->t_min = MIN_RAY_LENGTH;
	out->t_max = vec3_len(orientation);
}

void	ray_next(t_pt3 pt, t_vec3 vec, t_ray *out)
{
	out->origin = pt;
	out->direction = vec3_unit(vec);
	out->t_min = MIN_RAY_LENGTH;
	out->t_max = MAX_RAY_LENGTH;
}

int	ray_try_doing_hit(t_list_object *world, t_ray *ray, t_hit *hit)
{
	t_list_object	*it;
	int				found;
	t_hit			hit_internal;

	found = 0;
	it = world;
	while (it)
	{
		if (it->on_hit(it, ray, &hit_internal))
		{
			found = 1;
			if (hit)
				*hit = hit_internal;
			ray->t_max = hit_internal.t;
		}
		it = it->next;
	}
	return (found);
}
