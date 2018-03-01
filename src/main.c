/*
** EPITECH PROJECT, 2018
** Project My_world
** File description:
** Main file.
*/

#include "main.h"

void	my_free(all_t *all)
{
	for (int i = 0; i < all->map->map_x; i++) {
		free (all->map->map_2d[i]);
		free (all->map->map_3d[i]);
	}
	free (all->map->map_2d);
	free (all->map->map_3d);
	sfCircleShape_destroy(all->brs->brush_circle);
	free (all->map);
	for (int i = 0; i < 8; i++) {
		sfSprite_destroy(all->obj[i].sprite);
		sfTexture_destroy(all->obj[i].text);
	}
	free (all->obj);
	sfRectangleShape_destroy(all->button->rect);
	free (all->button);
	sfRenderWindow_destroy(all->win->window);
	free (all->win);
	free (all);
}

void	which_button(window_t *win, obj_t *obj)
{
	for (int i = 0; i != 8; i++) {
		if (buttonIsClicked(obj, win->mouse_pos, i) == 1) {
			obj->num_button = i;
			break;
		} else
			obj->num_button = -1;
	}
}

void	terraforming(window_t *win, map_t *map, settings_t *stg, brush_t *brs)
{
	for (int i = 0; i < map->map_x; i++)
		free (map->map_2d[i]);
	free (map->map_2d);
	map->map_2d =  create_2d_map(map->map_3d, map, stg);
	draw_2d_map(win->window, map, stg);
	select_brush(win, map, stg, brs);
}

int	main()
{
	all_t *all = malloc(sizeof(*all));
	init_all(all);
	while (sfRenderWindow_isOpen(all->win->window)) {
		which_button(all->win, all->obj);
		while (RW_PE(all->win->window, &(all->win->event)))
			events(all, all->win, all->map, all->stg, all->brs);
		terraforming(all->win, all->map, all->stg, all->brs);
		draw_toolbox(all->win, all->obj, all->button);
		draw_window(all->win);
	}
	my_free(all);
	return (0);
}
