/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** key_press.c
*/

#include "runner.h"

static void stop(window_t *win)
{
    sfText_setString(win->pause->l_name,
    win->play_level->is_from_file ?
    get_file_namee(win->custom_level_name) :
    sfText_getString(win->lpick->levels[win->lpick->current_level]->name));
    update_progress_bar(win->pause->pbar,
    win->play_level->is_from_file ? win->play_level->pbar->adv :
    win->lpick->levels[win->lpick->current_level]->progression,
    win->pause->pbar->size, win->play_level->is_infinite);
    scale_pause(win->pause, win);
    win->play_level->is_pause = 1;
    if (win->play_level->music)
        sfMusic_pause(win->play_level->music);
    sfRenderWindow_setMouseCursorVisible(win->window, 1);
}

void resume(window_t *win)
{
    win->play_level->is_pause = 0;
    if (win->play_level->music)
        sfMusic_play(win->play_level->music);
    win->player->last_jump =
    sfClock_getElapsedTime(win->player->jump_clock);
    win->player->last_move =
    sfClock_getElapsedTime(win->player->move_clock);
    sfRenderWindow_setMouseCursorVisible(win->window, 0);
    if (win->player->anim_state == ANIM_DEATH) {
        win->player->anim_state = NO_ANIM;
        reset_player(win);
        update_attempt(win);
        if (win->play_level->is_infinite)
            reset_random(win);
    }
}

void pause_game(window_t *win)
{
    if (win->player->anim_state == ANIM_DEATH || win->player->is_ending)
        return;
    if (win->play_level->is_pause == 0)
        stop(win);
    else
        resume(win);
}

void manage_key_press(window_t *win, sfEvent *ev)
{
    if (ev->key.code == sfKeyF3)
        win->fps = !win->fps;
    if (ev->key.code == sfKeyLeft || ev->key.code == sfKeyRight)
        if (win->state == LEVEL_STATE)
            move_lvl_index(ev->key.code == sfKeyLeft ? 6 : 7, win);
    if (ev->key.code == sfKeyEscape) {
        if (win->state == HOME_STATE)
            sfRenderWindow_close(win->window);
        if (win->state == SETTINGS_STATE || win->state == SKIN_STATE
        || win->state == EDITOR_STATE || win->state == LEVEL_STATE) {
            win->is_transition = 1;
            win->next_state = HOME_STATE;
        }
    }
    if ((ev->key.code == sfKeySpace || ev->key.code == sfKeyEnter)) {
        if (win->state == LEVEL_STATE)
            launch_current_level(win);
        if (win->state == PLAY_STATE && win->play_level->is_pause == 1)
            resume(win);
    }
}
