/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** draw.c
*/

#include "runner.h"

void draw_classic(window_t *win, sfSprite *s)
{
    sfRenderWindow_drawSprite(win->window, s, NULL);
    if (win->state == PLAY_STATE && !win->is_transition)
        anim_player(win);
    if (win->state == PLAY_STATE && win->play_level && !win->is_transition)
        sfRenderWindow_drawText(win->window, win->play_level->attempt, NULL);
}

void check_changings(window_t *win)
{
    if (win->is_transition == 0 && win->state == PLAY_STATE
    && win->play_level->music)
        sfMusic_play(win->play_level->music);
    if (win->state == PLAY_STATE && win->is_transition == 0) {
        win->player->last_jump = (sfTime){0};
        win->player->last_move = (sfTime){0};
        sfClock_restart(win->player->jump_clock);
        sfClock_restart(win->player->move_clock);
    }
}

void switch_color_dir(window_t *win)
{
    win->is_transition = -1;
    win->state = win->next_state;
    if (win->state == CLOSE_STATE || win->state == EDITOR_STATE)
        sfRenderWindow_close(win->window);
}

void draw_global(window_t *win, sfSprite *s)
{
    sfSprite *tmp;
    if (win->play_level && win->play_level->is_pause) {
        tmp = get_pause_sprite(win);
        sfSprite_setPosition(tmp, (sfVector2f)\
        {win->mode.width / 2.0, win->mode.height / 2.0});
        sfSprite_setColor(s, (sfColor){127, 127, 127, 255});
        sfRenderWindow_drawSprite(win->window, s, NULL);
        anim_player(win);
        if (win->state == PLAY_STATE && win->play_level &&
        !win->is_transition)
            sfRenderWindow_drawText(win->window,
            win->play_level->attempt, NULL);
        sfRenderWindow_drawSprite(win->window, tmp, NULL);
        sfSprite_destroy(tmp);
    } else
        draw_classic(win, s);
    if (win->play_level && win->play_level->pbar->adv >= 100.0
    && win->state == PLAY_STATE && !win->is_transition &&
    !win->play_level->is_infinite)
        sfRenderWindow_drawSprite(win->window, win->comp_spr, NULL);
}

void draw(window_t *win)
{
    sfSprite *s;
    sfSprite *(*to_draw[])(window_t *) = {draw_home, draw_level_pick,
    NULL, get_skin_select, get_settings_sprite, draw_home, draw_level};

    sfRenderWindow_clear(win->window, sfBlack);
    s = to_draw[win->state](win);
    update_color(win, s);
    if (win->state == PLAY_STATE && !win->is_transition) {
        if (win->player->anim_state != ANIM_DEATH &&
        win->play_level->is_pause == 0)
            manage_collision(win);
    }
    draw_global(win, s);
    if (win->fps)
        draw_fps(win);
    sfSprite_destroy(s);
    sfRenderWindow_display(win->window);
}
