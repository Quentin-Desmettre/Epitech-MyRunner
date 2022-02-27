/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** skin_select.c
*/

#include "runner.h"

void center_origin(sfSprite *s)
{
    sfIntRect rect;

    if (!s)
        return;
    rect = sfSprite_getTextureRect(s);
    sfSprite_setOrigin(s, (sfVector2f){rect.width / 2.0, rect.height / 2.0});
}

skin_select_t *init_skin_select(window_t *win)
{
    skin_select_t *sk = malloc(sizeof(skin_select_t));
    sfTexture *skins = sfTexture_createFromFile(SKINS_SHEET, NULL);

    sk->rtex = sfRenderTexture_create(win->mode.width, win->mode.height, 0);
    sk->back = win->home_screen->buttons[5];
    sk->background = win->settings->background;
    sk->cur_skin = init_sprite_from_texture(skins, &skins_rects[0], 1);
    sk->skin_index = 0;
    for (int i = 0; i < 4; i++) {
        sk->skins[i] = init_button(skins, -1, (sfVector2f){0, 0}, NULL);
        sfSprite_setTextureRect(sk->skins[i]->sprite, skins_rects[i * 4]);
        center_origin(sk->skins[i]->sprite);
    }
    sk->draw_clock = sfClock_create();
    sk->highlight = init_sprite_from_texture(skins, &skins_rects[16], 1);
    return sk;
}
