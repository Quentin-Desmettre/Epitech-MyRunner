/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** player.c
*/

#include "runner.h"

void reset_player_skin(sfVideoMode mode, player_t *p, window_t *win)
{
    float cible_size = mode.height / BLOCK_PER_SCREEN;
    sfVector2u actu_size;

    sfSprite_setTextureRect(p->skin,
    skins_rects[win->skin_select->skin_index * 4]);
    actu_size = (sfVector2u){sfSprite_getTextureRect(p->skin).width,
    sfSprite_getTextureRect(p->skin).height};
    sfSprite_scale(p->skin, (sfVector2f){cible_size / actu_size.x,
    cible_size / actu_size.y});
    sfSprite_setPosition(p->skin, (sfVector2f){cible_size * 2,
    mode.height - 2 * cible_size - cible_size / 2});
    sfSprite_setOrigin(p->skin, (sfVector2f){actu_size.x / 2.0,
    actu_size.y / 2.0});
    mod_pos_player(p, mode);
    p->is_ending = 0;
    sfText_setPosition(win->play_level->attempt, (sfVector2f)
    {win->mode.width / 2.0, win->mode.height / 3.0});
}

void reset_player(window_t *win)
{
    play_level_t *p = win->play_level;

    p->columns = p->start;
    for (int i = 0; p->blocks[i]; i++)
        free(p->blocks[i]);
    free(p->blocks);
    p->blocks = init_first_blocks(&(p->columns));
    win->player->rect = 0;
    sfSprite_setTexture(win->player->skin, win->player->tex, 1);
    sfSprite_setTextureRect(win->player->skin,
    skins_rects[win->skin_select->skin_index * 4]);
    reset_player_skin(win->mode, win->player, win);
    win->player->anim_state = NO_ANIM;
    win->player->progression = 0;
    p->i_block = 0;
    for (int i = 0; i < 3; i++)
        sfSprite_setTextureRect(p->parallax[i],
        (sfIntRect){0, 0, win->mode.width * 4, 2049.0});
    reset_player_clocks(win->player);
}

player_t *init_player(window_t *win)
{
    player_t *p = malloc(sizeof(player_t));
    sfTexture *t = sfTexture_createFromFile(SKINS_SHEET, NULL);

    p->state = 0;
    p->jump_clock = sfClock_create();
    p->skin = sfSprite_create();
    if (t)
        sfSprite_setTexture(p->skin, t, 0);
    reset_player_skin(win->mode, p, win);
    p->tex = t;
    p->anim_state = NO_ANIM;
    p->rect = 0;
    p->velocity = 0;
    p->progression = 0;
    p->move_clock = sfClock_create();
    p->anim_clock = sfClock_create();
    reset_player_clocks(p);
    return p;
}

void scale_player(sfVideoMode mode, player_t *p)
{
    float a = sfTexture_getSize(sfSprite_getTexture(p->skin)).x *
    sfSprite_getScale(p->skin).x;
    sfVector2u actu_size = sfSprite_getTexture(p->skin) ?
    (sfVector2u){a, a} : (sfVector2u){0, 0};
    float cible_size = mode.height / BLOCK_PER_SCREEN;

    sfSprite_scale(p->skin, (sfVector2f){cible_size / actu_size.x,
    cible_size / actu_size.y});
}

void anim_jump(player_t *p, window_t *win)
{
    sfInt64 dt = sfClock_getElapsedTime(win->player->jump_clock).microseconds
    - p->last_jump.microseconds;
    float block_size = win->mode.height / BLOCK_PER_SCREEN;
    float off = p->velocity * dt / 1000000.0 * block_size / 10.0;

    for (int i = 0; i < 10 &&
    (i < 3 || (has_land(win) < 0 || has_land(win) > SPIKE)); i++)
        sfSprite_move(win->player->skin, (sfVector2f)
        {0, off});
    p->velocity += GRAVITY * dt / 1000000.0 * block_size *
    600.0 / win->mode.height;
    if (p->velocity > 23)
        p->velocity = 23;
    p->last_jump = sfClock_getElapsedTime(win->player->jump_clock);
}
