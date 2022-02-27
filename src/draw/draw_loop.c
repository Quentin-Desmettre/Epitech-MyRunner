/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** draw_loop.c
*/

#include "runner.h"

void update_attempt(window_t *win)
{
    char *current = (char *)sfText_getString(win->play_level->attempt);
    int nb = my_getnbr(current + 8);
    char *app;

    current[8] = 0;
    app = nbr_to_str(nb + 1);
    append(&current, app, 0);
    sfText_setString(win->play_level->attempt, current);
}

void reset_player_clocks(player_t *p)
{
    p->last_jump = (sfTime){0};
    p->last_move = (sfTime){0};
    sfClock_restart(p->jump_clock);
    sfClock_restart(p->move_clock);
}

void update_color(window_t *win, sfSprite *s)
{
    int fac = win->is_transition * 24;

    if (win->is_transition &&
    sfClock_getElapsedTime(win->state_clock).microseconds > 33333) {
        if (win->lum.a == 39)
            switch_color_dir(win);
        win->lum.a -= fac;
        win->lum.b -= fac;
        win->lum.r -= fac;
        win->lum.g -= fac;
        sfSprite_setColor(s, win->lum);
        if (win->is_transition == -1 && win->lum.a == 255)
            win->is_transition = 0;
        check_changings(win);
        sfClock_restart(win->state_clock);
    }
    sfSprite_setColor(s, win->lum);
}

sfSprite *draw_level(window_t *win)
{
    if (win->lum.a == 255 &&
    win->play_level->is_pause == 0 &&
    (win->play_level->pbar->adv < 100 || win->play_level->is_infinite))
        update_blocks(win->play_level);
    return get_play_sprite(win->play_level, win->player, win);
}
