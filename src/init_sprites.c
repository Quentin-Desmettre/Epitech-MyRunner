/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** init_sprites.c
*/

#include "runner.h"

sfVector2f get_sprite_size(sfSprite *s)
{
    sfVector2f size = {0, 0};
    sfIntRect rect = sfSprite_getTextureRect(s);
    sfVector2f scale = sfSprite_getScale(s);

    size.x = rect.width * scale.x;
    size.y = rect.height * scale.y;
    return size;
}

sfSprite *init_sprite_from_file(char const *file)
{
    sfTexture *t = sfTexture_createFromFile(file, NULL);
    sfSprite *s = sfSprite_create();

    if (t)
        sfSprite_setTexture(s, t, 0);
    return s;
}

sfSprite *init_sprite_from_texture(sfTexture *tex,
const sfIntRect *rect, int centerize)
{
    sfSprite *s = sfSprite_create();
    sfVector2u size = tex ? sfTexture_getSize(tex) : (sfVector2u){0, 0};

    if (tex)
        sfSprite_setTexture(s, tex, 0);
    if (rect)
        sfSprite_setTextureRect(s, *rect);
    if (centerize)
        sfSprite_setOrigin(s, rect ? (sfVector2f)
        {rect->width / 2.0, rect->height / 2.0} :
        (sfVector2f){size.x / 2.0, size.y / 2.0});
    return s;
}
