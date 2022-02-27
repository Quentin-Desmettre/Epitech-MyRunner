/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** up_player_pos.c
*/

#include "runner.h"

void check_end(window_t *win, int progression, float mover)
{
    if (progression == 100 && !win->play_level->is_infinite) {
        sfSprite_move(win->player->skin, (sfVector2f){mover, 0});
        if (!win->player->is_ending &&
        win->lvl_complete && win->lvl_complete)
            sfSound_play(win->lvl_complete);
        if (!win->player->is_ending &&
        win->lvl_complete && win->play_level->music)
            sfMusic_stop(win->play_level->music);
        if (!win->player->is_ending &&
        win->lvl_complete)
            win->player->is_ending = 1;
    }
    win->player->last_move = sfClock_getElapsedTime(win->player->move_clock);
}

float float_mod(float a, float mod)
{
    while (a >= mod * (a > 0 ? 1 : -1))
        a -= mod;
    return a;
}

float round_to_up_block(sfVector2f pos, sfVideoMode mode)
{
    float block_size = mode.height / BLOCK_PER_SCREEN;
    float offset = 0;

    while (float_mod(pos.y, block_size) > 1) {
        offset -= 0.1;
        pos.y -= 0.1;
    }
    return offset;
}

void mod_pos_player(player_t *p, sfVideoMode mode)
{
    sfVector2f pos = sfSprite_getPosition(p->skin);
    sfVector2f tmp = {0,
    round_to_up_block(pos, mode) + mode.height / (BLOCK_PER_SCREEN * 2)};

    sfSprite_move(p->skin, tmp);
    p->state = 0;
}

void update_player_pos(window_t *win)
{
    int progression = win->play_level ?
    my_getnbr(sfText_getString(win->play_level->pbar->percent)) : 0;
    sfInt64 dt = sfClock_getElapsedTime(win->player->move_clock).microseconds
    - win->player->last_move.microseconds;
    float block_size = win->mode.height / BLOCK_PER_SCREEN;
    float mover = dt / 1000000.0 * X_VELOCITY * block_size;

    if ((progression < 100 || win->play_level->is_infinite) &&
    !win->play_level->is_pause) {
        win->play_level->x_offset += mover;
        sfText_move(win->play_level->attempt, (sfVector2f){-mover, 0});
    }
    if (sfSprite_getPosition(win->player->skin).x >
    win->mode.width + get_sprite_size(win->player->skin).x) {
        if (!win->lvl_complete ||
        sfSound_getStatus(win->lvl_complete) == sfStopped)
            exit_game(win);
        return;
    }
    check_end(win, progression, mover);
}
