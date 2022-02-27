/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** draw_actu_level.c
*/

#include "runner.h"

void draw_level_buttons(window_t *win)
{
    level_pick *lpick = win->lpick;

    for (int i = 5; i < NB_BUTTONS; i++) {
        sfRenderTexture_drawSprite(lpick->rtex,
        win->home_screen->buttons[i]->sprite, NULL);
    }
}

const sfTexture *get_actu_level_tex(level_pick *lpick)
{
    level_t *cur = lpick->levels[lpick->current_level];
    sfRenderTexture_clear(cur->rtex, (sfColor){255, 255, 255, 0});

    sfRenderTexture_drawSprite(cur->rtex, cur->background, NULL);
    sfRenderTexture_drawText(cur->rtex, cur->name, NULL);
    sfRenderTexture_drawSprite(cur->rtex, cur->diff, NULL);
    sfRenderTexture_display(cur->rtex);
    return sfRenderTexture_getTexture(cur->rtex);
}

sfSprite *draw_actu_level(level_pick *lpick, window_t *win)
{
    const sfTexture *ltex = get_actu_level_tex(lpick);
    sfSprite *s = sfSprite_create();

    if (ltex) {
        sfSprite_setTexture(s, ltex, 0);
        sfSprite_setOrigin(s, (sfVector2f)
        {sfTexture_getSize(ltex).x / 2.0, sfTexture_getSize(ltex).y / 2.0});
    }
    sfSprite_setPosition(s, (sfVector2f)
    {win->mode.width / 2.0, win->mode.height / 2.5});
    return s;
}
