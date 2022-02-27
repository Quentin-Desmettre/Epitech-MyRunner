/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** mouse_move.c
*/

#include "runner.h"

void home_mouse_move(window_t *win, sfEvent *ev)
{
    int tmp = get_home_button_at((sfVector2f)
    {ev->mouseMove.x, ev->mouseMove.y}, win->home_screen);

    if (tmp >= 0 && sfMouse_isButtonPressed(sfMouseLeft))
        press_button(win->home_screen->buttons[tmp], 1);
    else if (tmp >= 0)
        hover_button(win->home_screen->buttons[tmp], 1);
    reset_home_buttons(win, tmp);
}

void lpick_mouse_move(window_t *win, sfEvent *ev)
{
    int tmp = get_level_button_at((sfVector2f)
    {ev->mouseMove.x, ev->mouseMove.y}, win->home_screen, win);

    if (tmp >= 0 && sfMouse_isButtonPressed(sfMouseLeft) && tmp != NB_BUTTONS)
        press_button(win->home_screen->buttons[tmp], 1);
    else if (tmp >= 0 && tmp != NB_BUTTONS)
        hover_button(win->home_screen->buttons[tmp], 1);
    reset_home_buttons(win, tmp);
}

void manage_mouse_move(window_t *win, sfEvent *ev)
{
    if (win->state == HOME_STATE)
        home_mouse_move(win, ev);
    if (win->state == LEVEL_STATE)
        lpick_mouse_move(win, ev);
    if (win->state == SETTINGS_STATE)
        manage_settings_hover(ev, win);
    if (win->state == SKIN_STATE)
        ss_mouse_move(win, ev);
    if (win->state == PLAY_STATE && win->play_level->is_pause)
        pause_move(win, ev);
}
