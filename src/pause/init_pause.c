/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** init_pause.c
*/

#include "runner.h"

void draw_pause(window_t *win)
{
    pause_t *p = win->pause;
    sfSprite *s = sprite_progress_bar(p->pbar);

    sfSprite_setPosition(s, (sfVector2f)
    {win->mode.width * 0.45, win->mode.height * 0.4});
    sfRenderTexture_clear(p->rtex, (sfColor){0, 0, 0, 0});
    sfRenderTexture_drawSprite(p->rtex, p->background, NULL);
    sfRenderTexture_drawText(p->rtex, p->l_name, NULL);
    sfRenderTexture_drawSprite(p->rtex, s, NULL);
    sfRenderTexture_drawSprite(p->rtex, p->quit->sprite, NULL);
    sfRenderTexture_drawSprite(p->rtex, p->resume->sprite, NULL);
    sfRenderTexture_display(p->rtex);
    sfSprite_destroy(s);
}

sfSprite *get_pause_sprite(window_t *win)
{
    sfSprite *s = sfSprite_create();
    sfIntRect r;

    draw_pause(win);
    sfSprite_setTexture(s,
    sfRenderTexture_getTexture(win->pause->rtex), 0);
    r = sfSprite_getTextureRect(s);
    sfSprite_setOrigin(s, (sfVector2f)
    {r.width / 2.0, r.height / 2.0});
    return s;
}

void move_pause(pause_t *p, window_t *win)
{
    float ori = my_strlen(sfText_getString(p->l_name)) *
    win->mode.height / 20.0;

    sfText_setOrigin(p->l_name, (sfVector2f)
    {ori / 2.0, win->mode.height / 20.0});
    sfText_setPosition(p->l_name, (sfVector2f)
    {win->mode.width * 0.45, win->mode.height * 0.15});
    sfSprite_setPosition(p->resume->sprite, (sfVector2f)
    {win->mode.width * 0.9 * 0.35, win->mode.height * 0.65});
    sfSprite_setPosition(p->quit->sprite, (sfVector2f)
    {win->mode.width * 0.9 * 0.65, win->mode.height * 0.65});
}

void scale_pause(pause_t *p, window_t *win)
{
    sfRenderTexture_destroy(p->rtex);
    p->rtex = sfRenderTexture_create(win->mode.width * 0.9,
    win->mode.height * 0.9, 0);
    set_sprite_size(p->background, (sfVector2f){win->mode.width * 0.9,
    win->mode.height * 0.9});
    update_progress_bar(p->pbar,
    my_getnbr(sfText_getString(p->pbar->percent)), (sfVector2f)
    {win->mode.width / 2.0, win->mode.height / 12.0},
    win->play_level ? win->play_level->is_infinite : 0);
    sfText_setCharacterSize(p->l_name, win->mode.height / 10.0);
    sfText_setOutlineThickness(p->l_name, win->mode.height / 100.0);
    set_sprite_size(p->resume->sprite,
    (sfVector2f){win->mode.height / 6.5, win->mode.height / 6.5});
    set_sprite_size(p->quit->sprite,
    (sfVector2f){win->mode.height / 6.5, win->mode.height / 6.5});
    move_pause(p, win);
}

pause_t *init_pause(window_t *win)
{
    pause_t *p = malloc(sizeof(pause_t));
    sfTexture *tex = sfTexture_createFromFile(BUTTONS_PNG, NULL);

    p->rtex = sfRenderTexture_create(win->mode.width * 0.9,
    win->mode.height * 0.9, 0);
    p->background = init_sprite_from_file(ACTU_LVL_BACK);
    sfSprite_setColor(p->background, (sfColor){100, 100, 100, 190});
    p->pbar = init_progress_bar(0, (sfVector2f)
    {win->mode.width / 2.0, win->mode.height / 15.0});
    p->l_name = sfText_create();
    sfText_setOutlineColor(p->l_name, sfBlack);
    sfText_setFont(p->l_name, sfFont_createFromFile(GD_FONT));
    p->resume = init_button(tex, -1, (sfVector2f){0, 0}, NULL);
    sfSprite_setTextureRect(p->resume->sprite, pause_buttons[0]);
    sfSprite_setOrigin(p->resume->sprite, (sfVector2f){104.5, 104.5});
    p->quit = init_button(tex, -1, (sfVector2f){0, 0}, NULL);
    sfSprite_setTextureRect(p->quit->sprite, pause_buttons[1]);
    sfSprite_setOrigin(p->quit->sprite, (sfVector2f){80.5, 80.5});
    scale_pause(p, win);
    return p;
}
