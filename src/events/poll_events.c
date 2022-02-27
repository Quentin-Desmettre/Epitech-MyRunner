/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** home_screen_events.c
*/

#include "runner.h"

void check_sound_repeat(window_t *win, sfEvent *ev)
{
    if (sfMouse_isButtonPressed(sfMouseLeft) && win->state == SETTINGS_STATE &&
    sfClock_getElapsedTime(win->state_clock).microseconds > 1000000 / 25.0 &&
    sfClock_getElapsedTime(
    win->settings->repeat_clock).microseconds > REPEAT_DELAY) {
        ev->mouseButton.x = sfMouse_getPositionRenderWindow(win->window).x;
        ev->mouseButton.y = sfMouse_getPositionRenderWindow(win->window).y;
        ev->type = sfEvtResized;
        if (get_set_button_at(win->settings, ev) <= 4)
            return;
        manage_settings_press(ev, win);
        update_all_texts(win->settings);
        sfClock_restart(win->state_clock);
    }
}

void start_jump(window_t *win)
{
    win->player->velocity = Y_VELOCITY;
    sfClock_restart(win->player->jump_clock);
    win->player->last_jump.microseconds = -1000000.0 / win->framerate;
    anim_jump(win->player, win);
    win->player->state = 1;
    manage_collision(win);
}

void check_jump(window_t *win)
{
    if (sfKeyboard_isKeyPressed(sfKeySpace) ||
    sfMouse_isButtonPressed(sfMouseLeft))
        if (win->state == PLAY_STATE && win->player && !win->player->state &&
        win->player->anim_state != ANIM_DEATH) {
            start_jump(win);
        }
}

void manage_key_events(window_t *win, sfEvent *ev)
{
    if (ev->type == sfEvtMouseButtonPressed &&
    ev->mouseButton.button == sfMouseLeft)
        manage_press(win, ev);
    if (ev->type == sfEvtMouseButtonReleased &&
    ev->mouseButton.button == sfMouseLeft)
        manage_release(win, ev);
    if (ev->type == sfEvtMouseMoved)
        manage_mouse_move(win, ev);
    if (ev->type == sfEvtKeyReleased && ev->key.code == sfKeyEscape)
        if (win->state == PLAY_STATE)
            pause_game(win);
    if (ev->type == sfEvtKeyPressed)
        manage_key_press(win, ev);
}

void poll_events(window_t *win)
{
    sfEvent ev;

    while (sfRenderWindow_pollEvent(win->window, (&ev))) {
        if ((&ev)->type == sfEvtClosed)
            sfRenderWindow_close(win->window);
        if (win->is_transition || (win->next_state == PLAY_STATE &&
        win->state != PLAY_STATE))
            continue;
        manage_key_events(win, (&ev));
    }
    check_sound_repeat(win, (&ev));
    if (win->play_level && win->play_level->is_pause == 0)
        check_jump(win);
}
