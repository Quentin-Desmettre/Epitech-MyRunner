/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** button.c
*/

#include "runner.h"

void set_button_tex_rect(int rect, button_t *b, sfVector2u tex_size)
{
    if (rect < 0)
        sfSprite_setOrigin(b->sprite,
        (sfVector2f){tex_size.x / 2.0, tex_size.y / 2.0});
    else
        sfSprite_setOrigin(b->sprite,
        (sfVector2f){buttons_rect[rect].width / 2,
        buttons_rect[rect].height / 2});
}

button_t *init_button(sfTexture *tex, int rect,
sfVector2f pos, char const *text)
{
    button_t *b = malloc(sizeof(button_t));
    sfVector2u tex_size = tex ? sfTexture_getSize(tex) : (sfVector2u){0, 0};

    b->sprite = sfSprite_create();
    if (tex) {
        sfSprite_setTexture(b->sprite, tex, 0);
        if (rect >= 0)
            sfSprite_setTextureRect(b->sprite, buttons_rect[rect]);
    }
    sfSprite_setPosition(b->sprite, pos);
    set_button_tex_rect(rect, b, tex_size);
    b->is_hover = 0;
    b->is_press = 0;
    b->pos = pos;
    b->size = (sfVector2f){buttons_rect[rect].width,
    buttons_rect[rect].height};
    b->text = init_text(text);
    return b;
}

void set_button_size(button_t *b, sfVector2f size)
{
    sfVector2u tex_size = sfTexture_getSize(sfSprite_getTexture(b->sprite));
    sfVector2f scale = sfSprite_getScale(b->sprite);
    sfVector2f spr_size = {tex_size.x * scale.x, tex_size.y * scale.y};

    sfSprite_scale(b->sprite, (sfVector2f)
    {size.x / spr_size.x, size.y / spr_size.y});
    b->size = size;
}

button_t **create_home_buttons(void)
{
    button_t **bu = malloc(sizeof(button_t) * (NB_BUTTONS + 1));
    sfTexture *t = sfTexture_createFromFile(BUTTONS_PNG, NULL);
    sfVector2f pos = {0, 0};

    if (t)
        sfTexture_setSmooth(t, 1);
    for (int i = 0; i < NB_BUTTONS; i++)
        bu[i] = init_button(t, i, pos, "");
    bu[NB_BUTTONS] = NULL;
    return bu;
}
