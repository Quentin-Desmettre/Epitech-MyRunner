/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** anim_player.c
*/

#include "runner.h"

void anim_skin(player_t *p)
{
    sfIntRect r = sfSprite_getTextureRect(p->skin);

    if (p->state)
        r.left = 48;
    else if (r.left >= 32)
        r.left = 0;
    else
        r.left += 16;
    sfSprite_setTextureRect(p->skin, r);
    sfClock_restart(p->anim_clock);
}

void start_death(window_t *win)
{
    win->player->anim_state = ANIM_DEATH;
    if (win->play_level->music)
        sfMusic_stop(win->play_level->music);
    if (win->death_sound)
        sfSound_play(win->death_sound);
    sfClock_restart(win->player->jump_clock);
    sfSprite_setTexture(win->player->skin, win->death_effet, 0);
    sfSprite_setTextureRect(win->player->skin, death_effet[0]);
    sfSprite_setScale(win->player->skin, (sfVector2f){1, 1});
    sfSprite_setOrigin(win->player->skin, (sfVector2f)
    {128, 128});
    actu_percentage(win);
}

void anim_death(window_t *win)
{
    if (sfClock_getElapsedTime(win->player->jump_clock).microseconds >
    33333 && win->player->rect < 29) {
        sfSprite_setTextureRect(win->player->skin,
        death_effet[win->player->rect + 1]);
        win->player->rect++;
        sfClock_restart(win->player->jump_clock);
    }
    if (win->player->rect >= 29 && !win->play_level->is_pause) {
        win->play_level->is_pause = 1;
        sfText_setString(win->pause->l_name, random_death_phrase());
        update_progress_bar(win->pause->pbar,
        win->play_level->pbar->adv,
        win->pause->pbar->size, win->play_level->is_infinite);
        scale_pause(win->pause, win);
        sfRenderWindow_setMouseCursorVisible(win->window, 1);
    }
    sfRenderWindow_drawSprite(win->window, win->player->skin, NULL);
}

void anim_jump_player(window_t *win)
{
    int land = has_land(win);

    if (win->player->state == 1) {
        if (land < 0 || land > SPIKE)
            anim_jump(win->player, win);
        else
            win->player->state = 0;
    }
    if (land < 0 && win->player->state != 1 && land <= SPIKE) {
        if (win->player->state != -1 && land <= SPIKE) {
            win->player->state = -1;
            win->player->last_jump = (sfTime){0};
            sfClock_restart(win->player->jump_clock);
            win->player->velocity = Y_VELOCITY / -3.0;
        }
        anim_jump(win->player, win);
    }
}

void anim_player(window_t *win)
{
    if (win->player->anim_state == ANIM_DEATH) {
        anim_death(win);
        return;
    }
    if (sfSprite_getPosition(win->player->skin).y > win->mode.height)
        start_death(win);
    else {
        if (win->play_level->is_pause) {
            sfRenderWindow_drawSprite(win->window, win->player->skin, NULL);
            return;
        }
        if (sfClock_getElapsedTime(win->player->anim_clock).microseconds >
        50000)
            anim_skin(win->player);
        anim_jump_player(win);
        update_player_pos(win);
        if (win->player)
            sfRenderWindow_drawSprite(win->window, win->player->skin, NULL);
    }
}
