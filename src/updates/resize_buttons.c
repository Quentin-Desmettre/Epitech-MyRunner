/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** resize_buttons.c
*/

#include "runner.h"

void move_lpick_buttons(window_t *win)
{
    button_t **buttons = win->home_screen->buttons;
    float scale = sfSprite_getScale(buttons[5]->sprite).x;
    sfVector2f pos = {win->mode.width / 22.0,
    scale * buttons_rect[5].height / 1.3};

    sfSprite_setPosition(buttons[5]->sprite, pos);
    buttons[5]->pos = pos;
    pos = (sfVector2f){pos.x, win->mode.height / 2.0};
    sfSprite_setPosition(buttons[6]->sprite, pos);
    buttons[6]->pos = pos;
    pos = (sfVector2f){win->mode.width * 0.954, pos.y};
    sfSprite_setPosition(buttons[7]->sprite, pos);
    buttons[7]->pos = pos;
}

void scale_buttons(sfVideoMode win_size, button_t **buttons)
{
    float dim_cible;
    float actu_dim_x;
    float actu_dim_y;
    float factors[8] = {5.0, 4.0, 5.0, 6.0, 6.0, 13.0, 13.0, 13.0};

    for (int i = 0; i < NB_BUTTONS; i++) {
        dim_cible = win_size.height / factors[i];
        actu_dim_x = buttons[i]->size.x;
        actu_dim_y = buttons[i]->size.y;
        sfSprite_scale(buttons[i]->sprite,
        (sfVector2f){dim_cible / actu_dim_x, dim_cible / actu_dim_y});
        buttons[i]->size = (sfVector2f){dim_cible, dim_cible};
    }
}

void move_settings_close(sfVideoMode win_size, button_t **buttons)
{
    float offset;
    sfVector2f pos;

    for (int i = 0; i < 2; i++) {
        offset = win_size.width / 3 * (i + 1);
        pos = (sfVector2f){offset, win_size.height / 1.2};
        sfSprite_setPosition(buttons[i + 3]->sprite, pos);
        buttons[i + 3]->pos = pos;
    }
}

void move_buttons(sfVideoMode win_size, button_t **buttons)
{
    float actu_scale = sfSprite_getScale(buttons[1]->sprite).x;
    float fir_scale = sfSprite_getScale(buttons[1]->sprite).x;
    float offset = win_size.width / 23.0;
    sfVector2f pos = {win_size.width / 2, win_size.height / 2.0};

    sfSprite_setPosition(buttons[1]->sprite, pos);
    buttons[1]->pos = pos;
    pos.x -= (buttons_rect[1].width * actu_scale + offset);
    for (int i = 0; i < 3; i++) {
        if (i == 1)
            continue;
        actu_scale = sfSprite_getScale(buttons[i]->sprite).x;
        sfSprite_setPosition(buttons[i]->sprite, pos);
        buttons[i]->pos = pos;
        pos.x += (buttons_rect[1].width * fir_scale + offset) * 2;
    }
    move_settings_close(win_size, buttons);
}
