/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** draw_level_pick.c
*/

#include "runner.h"

sfSprite *draw_home(window_t *win)
{
    const sfTexture *t = get_home_texture(win->home_screen);
    sfSprite *s = sfSprite_create();

    sfRenderTexture_drawSprite(win->home_screen->rtext,
    win->program_name, NULL);
    sfRenderTexture_display(win->home_screen->rtext);
    sfSprite_setTexture(s, t, 0);
    return s;
}

void draw_level_dots(level_pick *lpick, sfVideoMode mode)
{
    sfCircleShape *dot = sfCircleShape_create();
    int nb_level = lpick->nb_level;
    float radius = mode.height / 32.0;
    sfVector2f pos = {mode.width / 2.0 - nb_level * radius * 1.25,
    mode.height / 1.1};

    sfCircleShape_setRadius(dot, radius);
    for (int i = 0; i < nb_level; i++) {
        sfCircleShape_setFillColor(dot, (sfColor){123, 123, 123, 255});
        if (i == lpick->current_level)
            sfCircleShape_setFillColor(dot, sfWhite);
        sfCircleShape_setPosition(dot, pos);
        sfRenderTexture_drawCircleShape(lpick->rtex, dot, NULL);
        pos.x += radius * DOT_SPACING;
    }
}

void draw_progress_bar(window_t *win)
{
    sfSprite *p_bar;
    level_t *cur = win->lpick->levels[win->lpick->current_level];

    update_progress_bar(cur->p_bar, cur->progression,
    (sfVector2f){win->mode.width / 1.5, win->mode.height / 15.0},
    !my_strcmp(sfText_getString(cur->name), "Infinite mode"));
    p_bar = sprite_progress_bar(cur->p_bar);
    sfSprite_setPosition(p_bar,
    (sfVector2f){win->mode.width / 2.0, win->mode.height / 1.5});
    sfRenderTexture_drawSprite(win->lpick->rtex, p_bar, NULL);
    sfSprite_destroy(p_bar);
}

const sfTexture *get_level_pick_text(window_t *win)
{
    sfSprite *tmp;

    sfRenderTexture_clear(win->lpick->rtex, sfBlack);
    sfRenderTexture_drawSprite(win->lpick->rtex, win->lpick->background, NULL);
    if (!win->lpick->is_error) {
        tmp = draw_actu_level(win->lpick, win);
        sfRenderTexture_drawSprite(win->lpick->rtex, tmp, NULL);
        draw_progress_bar(win);
        sfSprite_destroy(tmp);
        draw_level_dots(win->lpick, win->mode);
    }
    draw_level_buttons(win);
    sfRenderTexture_display(win->lpick->rtex);
    return sfRenderTexture_getTexture(win->lpick->rtex);
}

sfSprite *draw_level_pick(window_t *win)
{
    const sfTexture *ltex = get_level_pick_text(win);
    sfSprite *s = sfSprite_create();

    sfSprite_setTexture(s, ltex, 0);
    return s;
}
