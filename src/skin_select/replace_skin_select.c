/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** replace_skin_select.c
*/

#include "runner.h"

void move_select(window_t *win)
{
    skin_select_t *s = win->skin_select;
    float scale = sfSprite_getScale(s->back->sprite).x;
    sfVector2f pos = {win->mode.width / 22.0,
    scale * buttons_rect[5].height / 1.3};
    float skin_spacing = win->mode.width / 20.0;

    sfSprite_setPosition(s->back->sprite, pos);
    sfSprite_setPosition(s->cur_skin, (sfVector2f)
    {win->mode.width / 2.0, win->mode.height / 3.0});
    pos.x = win->mode.width / 2.0 - win->mode.height / 2.0;
    pos.y = win->mode.height * 0.70;
    for (int i = 0; i < 4; i++) {
        sfSprite_setPosition(s->skins[i]->sprite, pos);
        if (i == s->skin_index)
            sfSprite_setPosition(s->highlight, pos);
        pos.x += win->mode.height / 4.0 + skin_spacing;
    }
}

void rescale_select(window_t *win)
{
    skin_select_t *s = win->skin_select;

    sfRenderTexture_destroy(s->rtex);
    s->rtex = sfRenderTexture_create(win->mode.width, win->mode.height, 0);
    set_sprite_size(s->background,
    (sfVector2f){win->mode.width, win->mode.height});
    sfSprite_setScale(s->back->sprite,
    (sfVector2f){win->mode.height / 1183.0, win->mode.height / 1391.0});
    set_sprite_size(s->cur_skin, (sfVector2f)
    {win->mode.height / 4.0, win->mode.height / 4.0});
    for (int i = 0; i < 4; i++)
        set_sprite_size(s->skins[i]->sprite, (sfVector2f)
        {win->mode.height / 4.0, win->mode.height / 4.0});
    set_sprite_size(s->highlight, (sfVector2f)
    {win->mode.height / 4.0, win->mode.height / 4.0});
    move_select(win);
}
