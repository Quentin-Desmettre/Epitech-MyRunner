/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** press_event.c
*/

#include "runner.h"

int is_level_click(sfVector2f pos, window_t *win)
{
    float x_span = win->mode.width / 3.0;
    float y_span = win->mode.width / 6.0;
    float half_width = win->mode.width / 2.0;
    float half_height = win->mode.height / 2.5;

    if (pos.x >= half_width - x_span && pos.x <= half_width + x_span &&
    pos.y >= half_height - y_span && pos.y <= half_height + y_span)
        return 1;
    return 0;
}

int get_level_button_at(sfVector2f pos, scene_t *win, window_t *w)
{
    int x = pos.x;
    int y = pos.y;
    button_t *a;

    if (is_level_click(pos, w))
        return NB_BUTTONS;
    for (int i = 5; i < NB_BUTTONS; i++) {
        a = win->buttons[i];
        if (x >= a->pos.x - a->size.x / 2 && x <= a->pos.x + a->size.x / 2 &&
        y >= a->pos.y - a->size.y / 2 && y <= a->pos.y + a->size.y / 2)
            return i;
    }
    return -1;
}

void home_press(window_t *win, sfEvent *ev)
{
    int tmp = get_home_button_at((sfVector2f){ev->mouseButton.x,
    ev->mouseButton.y}, win->home_screen);

    if (tmp >= 0)
        press_button(win->home_screen->buttons[tmp], 1);
}

void lpick_press(window_t *win, sfEvent *ev)
{
    int tmp = get_level_button_at((sfVector2f){ev->mouseButton.x,
    ev->mouseButton.y}, win->home_screen, win);

    if (tmp == NB_BUTTONS)
        return;
    if (tmp >= 0)
        press_button(win->home_screen->buttons[tmp], 1);
}

void manage_press(window_t *win, sfEvent *ev)
{
    if (win->state == HOME_STATE)
        home_press(win, ev);
    else if (win->state == LEVEL_STATE)
        lpick_press(win, ev);
    if (win->state == SETTINGS_STATE)
        manage_settings_press(ev, win);
    if (win->state == SKIN_STATE)
        ss_mouse_press(win, ev);
    if (win->state == PLAY_STATE && win->play_level->is_pause)
        pause_press(win, ev);
}
