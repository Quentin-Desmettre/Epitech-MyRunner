/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** draw_settings.c
*/

#include "runner.h"

void draw_set_button(sfRenderTexture *r, button_t *b)
{
    sfRenderTexture_drawSprite(r, b->sprite, NULL);
}

void draw_settings(settings_t *se)
{
    sfRenderTexture_clear(se->rtex, sfBlack);
    sfRenderTexture_drawSprite(se->rtex, se->background, NULL);
    draw_set_button(se->rtex, se->back);
    draw_check_box(se->rtex, se->full_screen);
    draw_check_box(se->rtex, se->vsync);
    draw_set_button(se->rtex, se->framerate_button);
    draw_set_button(se->rtex, se->res_button);
    draw_set_button(se->rtex, se->sfx_minus);
    draw_set_button(se->rtex, se->sfx_plus);
    draw_set_button(se->rtex, se->music_minus);
    draw_set_button(se->rtex, se->music_plus);
    sfRenderTexture_drawText(se->rtex, se->sfx_text, NULL);
    sfRenderTexture_drawText(se->rtex, se->music_text, NULL);
    sfRenderTexture_drawText(se->rtex, se->sfx_vol_text, NULL);
    sfRenderTexture_drawText(se->rtex, se->music_vol_text, NULL);
    sfRenderTexture_display(se->rtex);
}

sfSprite *get_settings_sprite(window_t *win)
{
    sfSprite *s = sfSprite_create();
    settings_t *se = win->settings;

    draw_settings(se);
    sfSprite_setTexture(s, sfRenderTexture_getTexture(se->rtex), 1);
    return s;
}
