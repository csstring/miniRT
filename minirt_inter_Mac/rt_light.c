#include "rt.h"

#include <math.h>

static t_vec3	_reflect(t_vec3 ray, t_vec3 normal)
{
	return (vec3_sub(ray, vec3_mul(2 * vec3_dot(ray, normal), normal)));
}

static t_vec3	_refract(t_vec3 ray, t_vec3 normal, double e, int f)
{
	double	cosine;
	t_vec3	perp;
	t_vec3	parallel;

	if (f)
		e = 1. / e;
	cosine = vec3_dot(vec3_neg(ray), normal);
	if (cosine > 1)
		cosine = 1;
	perp = vec3_mul(e, vec3_add(ray, vec3_mul(cosine, normal)));
	parallel = vec3_mul(sqrt(fabs(1 - vec3_len_sq(perp))), normal);
	return (vec3_sub(perp, parallel));
}

void	checkerboard_color(t_list_object *obj, t_vec3 uv, t_rgb *color,
					t_list_image *image_list);

static t_rgb	_get_ambient(t_rt *unit, t_ray *ray, t_hit *hit, int depth)
{
	t_rgb	color;
	t_rgb	amb;
	t_ray	next_ray;

	color = hit->obj->color;
	if (hit->obj->additional.checkerboard != 0)
		checkerboard_color(hit->obj, hit->uv, &color, unit->conf.images);
	amb = vec3_mul(hit->obj->material.ra * unit->conf.ambient.ratio,
			unit->conf.ambient.color);
	color = vec3_mul_v(vec3_div(255, amb), color);
	if (hit->obj->material.mirror)
	{
		ray_next(hit->collision,
			_reflect(ray->direction, hit->normal), &next_ray);
		color = vec3_add(color, vec3_mul_v(vec3_div(255, hit->obj->material.am),
					ray_color(unit, &next_ray, depth - 1)));
	}
	if (hit->obj->material.lens)
	{
		ray_next(hit->collision, _refract(ray->direction, hit->normal,
				hit->obj->material.e, hit->f), &next_ray);
		color = vec3_add(color, vec3_mul_v(vec3_div(255, hit->obj->material.al),
					ray_color(unit, &next_ray, depth - 1)));
	}
	return (color);
}

static t_rgb	_apply_phong(t_list_light *l, t_ray *ray, t_hit *hit,
	t_ray *shadow)
{
	t_rgb	color;
	double	diffuse;
	t_vec3	reflect;
	double	specular;

	color = (t_rgb){0., 0., 0.};
	diffuse = vec3_dot(shadow->direction, hit->normal);
	if (diffuse > 0)
		color = vec3_add(color, vec3_mul(
					hit->obj->material.rd * l->bright * diffuse, l->color));
	reflect = _reflect(shadow->direction, hit->normal);
	specular = vec3_dot(reflect, ray->direction);
	if (specular > 0)
	{
		specular = pow(specular, hit->obj->material.s);
		color = vec3_add(color, vec3_mul(
					hit->obj->material.rs * l->bright * specular, l->color));
	}
	return (color);
}

void	bump_normal(t_list_object *obj, t_vec3 uv, t_vec3 *normal,
					t_list_image *image_list);

t_vec3	ray_color(t_rt *unit, t_ray *ray, int depth)
{
	t_hit			hit;
	t_rgb			color;
	t_list_light	*it;
	t_ray			shadow;

	if (depth <= 0)
		return ((t_vec3){0., 0., 0.});
	if (ray_try_doing_hit(unit->conf.objects, ray, &hit))
	{
		if (hit.obj->additional.bumpmap != 0)
			bump_normal(hit.obj, hit.uv, &hit.normal, unit->conf.images);
		color = _get_ambient(unit, ray, &hit, depth);
		it = unit->conf.lights;
		while (it)
		{
			ray_to_light(hit.collision, it, &shadow);
			if (!ray_try_doing_hit(unit->conf.objects, &shadow, NULL))
				color = vec3_add(color, _apply_phong(it, ray, &hit, &shadow));
			it = it->next;
		}
		return (color);
	}
	return ((t_vec3){255, 255, 255});
}
