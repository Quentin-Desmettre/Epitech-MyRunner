/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** init_level_graphic.c
*/

#include "runner.h"

void init_background(play_level_t *p, window_t *win)
{
    sfTexture *t = sfTexture_createFromFile(PARA_S_BACK, NULL);

    if (t) {
        p->parallax[3] = init_sprite_from_texture(t, NULL, 0);
        set_sprite_size(p->parallax[3], (sfVector2f)
        {win->mode.width, win->mode.height});
    } else
        p->parallax[3] = sfSprite_create();
}

sfSprite *init_difficulty(sfTexture *tex, int diff)
{
    sfSprite *s = sfSprite_create();

    if (tex) {
        sfSprite_setTexture(s, tex, 0);
        sfSprite_setTextureRect(s, difficulties[diff]);
    }
    sfSprite_setOrigin(s, (sfVector2f)
    {difficulties[diff].width / 2.0, difficulties[diff].height / 2.0});
    return s;
}

sfText *init_text(char const *lvl_name)
{
    sfFont *font = sfFont_createFromFile(GD_FONT);
    sfText *n = sfText_create();

    sfText_setString(n, lvl_name);
    if (font)
        sfText_setFont(n, font);
    return n;
}

void init_lvl_back(level_t *l)
{
    sfTexture *t = sfTexture_createFromFile(ACTU_LVL_BACK, NULL);

    l->background = sfSprite_create();
    if (t)
        sfSprite_setTexture(l->background, t, 0);
}
