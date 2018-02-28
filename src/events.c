/*
** EPITECH PROJECT, 2018
** Project My_world
** File description:
** events
*/

#include "main.h"

void event_scrolled(window_t *win, map_t *map)
{
	if (win->event.type ==  sfEvtMouseWheelScrolled) {
		if (win->event.mouseWheelScroll.delta == 1 && map->zoom < 3)
			map->zoom += 0.01;
		if (win->event.mouseWheelScroll.delta == -1 && map->zoom > 0.1)
			map->zoom -= 0.01;
	}
}

void event_brush(all_t *all, map_t *map)
{
	if (sfMouse_isButtonPressed(sfMouseLeft) && all->obj->num_brush == 1) {
		up_tool_brush(map, all->obj);
	} else if (sfMouse_isButtonPressed(sfMouseRight) && all->obj->num_brush == 1) {
		down_tool_brush(map, all->obj);
	}
}

void event_button(all_t *all, window_t *win, int *box)
{
	sfVector2i mouse = {0, 0};

	if (win->event.type == sfEvtMouseButtonPressed) {
		mouse = sfMouse_getPositionRenderWindow(win->window);
		if (mouse.x > 1400 && mouse.x < 1850 && mouse.y > 10 && mouse.y < 80)
			*box = 1;
		/*switch (win->event.mouseButton.button) {
			case sfMouseLeft:
			up_tool(map, all->obj);
			break;
			case sfMouseRight:
			down_tool(map, all->obj);
			break;
			default:
			break;
		}*/
		switch (all->obj->num_button) {
			case 0:
			save(all);
			break;
			case 1:
			load(all);
			break;
			case 2:
			change_tool(all->obj);
			break;
			case 3:
			change_brush(all->obj);
			break;
		}
	}
}

void events(all_t *all, window_t *win, map_t *map)
{
	static int box = 0;

	if (win->event.type == sfEvtClosed)
		sfRenderWindow_close(win->window);
	if (win->event.type == sfEvtTextEntered && box == 1)
		textbox(win, map, &box);
	event_button(all, win, &box);
	event_brush(all, map);
	event_scrolled(win, map);
	event_keys(win, map, &box);
}