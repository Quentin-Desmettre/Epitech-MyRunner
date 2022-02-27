/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** sprite_transfos.c
*/

#include "runner.h"

void scale_rtex_lpick(window_t *win)
{
    level_pick *lpick = win->lpick;

    sfRenderTexture_destroy(lpick->rtex);
    lpick->rtex = sfRenderTexture_create(win->mode.width, win->mode.height, 0);
    sfSprite_setScale(lpick->background, (sfVector2f)
    {win->mode.width / 1904.0, win->mode.height / 1068.0});
    move_lpick_buttons(win);
    scale_buttons(win->mode, win->home_screen->buttons);
    for (int i = 0; i < lpick->nb_level; i++) {
        if (!(lpick->levels[i]))
            continue;
        scale_level(lpick->levels[i], win);
    }
    if (win->player)
        scale_player(win->mode, win->player);
}

void scale_level(level_t *l, window_t *w)
{
    int char_w = w->mode.height / 12.0;

    sfSprite_setScale(l->background, (sfVector2f)
    {w->mode.width / 1722.0, w->mode.height / 960.0});
    l->rtex = sfRenderTexture_create(w->mode.width / 1.5,
    w->mode.height / 3.0, 0);
    sfText_setCharacterSize(l->name, char_w);
    sfText_setOrigin(l->name, (sfVector2f){0, char_w / 2.0});
    sfText_setPosition(l->name, (sfVector2f)
    {w->mode.width / 8.0, w->mode.height / 7.0});
    sfSprite_setScale(l->diff, (sfVector2f)
    {w->mode.width / 1750.0, w->mode.width / 1750.0});
    sfSprite_setPosition(l->diff, (sfVector2f)
    {w->mode.width / 14.0, w->mode.height / 6.5});
}

void scale_sprite(sfSprite *s, int size_rect, sfVector2u win_size)
{
    float current_size = block_rects[size_rect].width *
    sfSprite_getScale(s).x;
    float cible_size = win_size.y / BLOCK_PER_SCREEN;

    sfSprite_scale(s, (sfVector2f){cible_size / current_size,
    cible_size / current_size});
}

void set_sprite_size(sfSprite *s, sfVector2f size)
{
    sfIntRect tex_size = s ? sfSprite_getTextureRect(s) :
    (sfIntRect){0, 0, 0, 0};
    sfVector2f scale;
    sfVector2f actu_size;

    if (!tex_size.width || !tex_size.height)
        return;
    scale = sfSprite_getScale(s);
    actu_size = (sfVector2f){tex_size.width * scale.x,
    tex_size.height * scale.y};
    sfSprite_scale(s, (sfVector2f){size.x / actu_size.x,
    size.y / actu_size.y});
}

void move_sprite(sfSprite *s, sfVector2f pos,
sfVector2u win_size, float offset)
{
    float block_width = win_size.y / BLOCK_PER_SCREEN;

    sfSprite_setPosition(s, (sfVector2f)
    {block_width * pos.x - offset, win_size.y - block_width * (pos.y + 1)});
}
