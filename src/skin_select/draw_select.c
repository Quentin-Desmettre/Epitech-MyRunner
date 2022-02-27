/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** draw_select.c
*/

#include "runner.h"

void anim_skin_select(skin_select_t *select)
{
    sfIntRect rect = sfSprite_getTextureRect(select->cur_skin);

    if (sfClock_getElapsedTime(select->draw_clock).microseconds
    < 50000)
        return;
    sfClock_restart(select->draw_clock);
    if (rect.left == 32)
        rect.left = 0;
    else
        rect.left += 16;
    sfSprite_setTextureRect(select->cur_skin, rect);
}

void draw_skin_select(skin_select_t *s)
{
    sfRenderTexture_clear(s->rtex, sfBlack);
    sfRenderTexture_drawSprite(s->rtex, s->background, NULL);
    sfRenderTexture_drawSprite(s->rtex, s->back->sprite, NULL);
    sfRenderTexture_drawSprite(s->rtex, s->cur_skin, NULL);
    sfRenderTexture_drawSprite(s->rtex, s->highlight, NULL);
    for (int i = 0; i < 4; i++)
        sfRenderTexture_drawSprite(s->rtex, s->skins[i]->sprite, NULL);
    sfRenderTexture_display(s->rtex);
}

sfSprite *get_skin_select(window_t *win)
{
    sfSprite *s = sfSprite_create();

    anim_skin_select(win->skin_select);
    draw_skin_select(win->skin_select);
    sfSprite_setTexture(s,
    sfRenderTexture_getTexture(win->skin_select->rtex), 0);
    return s;
}
