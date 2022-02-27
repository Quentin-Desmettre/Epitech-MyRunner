/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** release_events.c
*/

#include "runner.h"

void destroy_player(player_t *player)
{
    sfClock_destroy(player->anim_clock);
    sfClock_destroy(player->jump_clock);
    sfClock_destroy(player->move_clock);
    sfSprite_destroy(player->skin);
    if (player->tex)
        sfTexture_destroy(player->tex);
    free(player);
}

void launch_current_level(window_t *win)
{
    load_level(win);
    sfRenderWindow_setMouseCursorVisible(win->window, 0);
    if (!(win->play_level))
        return;
    if (win->lobby_music)
        sfMusic_stop(win->lobby_music);
    if (win->lpick->launch_sound)
        sfSound_play(win->lpick->launch_sound);
    win->next_state = PLAY_STATE;
    win->is_transition = 1;
    sfClock_restart(win->state_clock);
    if (win->player)
        destroy_player(win->player);
    win->player = init_player(win);
}

void release_level_pick(window_t *win, sfEvent *ev)
{
    int tmp = get_level_button_at((sfVector2f){ev->mouseButton.x,
    ev->mouseButton.y}, win->home_screen, win);

    if (tmp == NB_BUTTONS && !(win->lpick->is_error))
        launch_current_level(win);
    if (tmp >= 0 && tmp != NB_BUTTONS)
        release_button(tmp, win);
}

void release_home(window_t *win, sfEvent *ev)
{
    int tmp = get_home_button_at((sfVector2f){ev->mouseButton.x,
    ev->mouseButton.y}, win->home_screen);

    if (tmp >= 0) {
        press_button(win->home_screen->buttons[tmp], 0);
        release_button(tmp, win);
    }
}

void manage_release(window_t *win, sfEvent *ev)
{
    if (win->state == HOME_STATE)
        release_home(win, ev);
    else if (win->state == LEVEL_STATE)
        release_level_pick(win, ev);
    if (win->state == SETTINGS_STATE)
        manage_settings_release(ev, win);
    if (win->state == SKIN_STATE)
        ss_mouse_release(win, ev);
    if (win->state == PLAY_STATE && win->play_level->is_pause)
        pause_release(win, ev);
    reset_home_buttons(win, -1);
}
