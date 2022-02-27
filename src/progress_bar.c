/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** progress_bar.c
*/

#include "runner.h"

sfText *init_percent_text(float percent, sfVector2f size)
{
    sfText *text = sfText_create();
    sfFont *font = sfFont_createFromFile(GD_FONT);
    char *percent_str = nbr_to_str((int)percent);
    int char_size = size.y * 0.98;
    float half_size = char_size / 2.0;
    float half_len = my_strlen(percent_str) * half_size;

    append_char(&percent_str, '%', 1);
    sfText_setString(text, percent_str);
    if (font)
        sfText_setFont(text, font);
    sfText_setCharacterSize(text, char_size);
    sfText_setOutlineColor(text, sfBlack);
    sfText_setOutlineThickness(text, size.x / 400.0);
    sfText_setOrigin(text, (sfVector2f)
    {half_len, half_size});
    sfText_setPosition(text, (sfVector2f)
    {size.x / 2.0 + half_len / 6.0, size.y / 3.0});
    free(percent_str);
    return text;
}

sfRectangleShape *init_filled_bar(float percent, sfVector2f size)
{
    sfRectangleShape *bar = sfRectangleShape_create();

    sfRectangleShape_setSize(bar, (sfVector2f)
    {size.x * 0.0098 * percent, size.y * 0.90});
    sfRectangleShape_setPosition(bar, (sfVector2f)
    {size.x * 0.01, size.y * 0.05});
    sfRectangleShape_setFillColor(bar, (sfColor){0, 255, 53, 255});
    return bar;
}

progress_bar_t *init_progress_bar(float percent, sfVector2f size)
{
    progress_bar_t *pb = malloc(sizeof(progress_bar_t));

    pb->tex = sfRenderTexture_create(size.x, size.y, 0);
    pb->percent = init_percent_text(percent, size);
    pb->size = size;
    pb->adv = percent;
    return pb;
}

void update_progress_bar(
progress_bar_t *p_bar, float percent, sfVector2f size, int is_infinite)
{
    int char_size = size.y * 0.98;
    char *percent_str;
    float half_len;

    percent_str = nbr_to_str((int)percent);
    sfRenderTexture_destroy(p_bar->tex);
    p_bar->tex = sfRenderTexture_create(size.x, size.y, 0);
    append(&percent_str, is_infinite ? " BLOCKS" : "%", 1);
    sfText_setString(p_bar->percent, percent_str);
    half_len = my_strlen(percent_str) * (char_size / 2.5);
    sfText_setCharacterSize(p_bar->percent, char_size);
    sfText_setOrigin(p_bar->percent, (sfVector2f)
    {half_len, char_size / 2.0});
    sfText_setPosition(p_bar->percent, (sfVector2f)
    {size.x / 2.0 + half_len / 6.0, size.y / 3.0});
    sfText_setOutlineThickness(p_bar->percent, size.x / 400.0);
    free(percent_str);
    p_bar->size = size;
    p_bar->adv = percent;
}

sfSprite *sprite_progress_bar(progress_bar_t *p_bar)
{
    sfRectangleShape *bar = init_filled_bar(p_bar->adv, p_bar->size);
    sfSprite *s = sfSprite_create();

    sfRenderTexture_clear(p_bar->tex, (sfColor){0, 0, 0, 120});
    sfRenderTexture_drawRectangleShape(p_bar->tex, bar, NULL);
    sfRenderTexture_drawText(p_bar->tex, p_bar->percent, NULL);
    sfRenderTexture_display(p_bar->tex);
    sfSprite_setTexture(s, sfRenderTexture_getTexture(p_bar->tex), 0);
    sfRectangleShape_destroy(bar);
    sfSprite_setOrigin(s, (sfVector2f){p_bar->size.x / 2.0,
    p_bar->size.y / 2.0});
    return s;
}
