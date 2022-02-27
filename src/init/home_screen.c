/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** home_screen.c
*/

#include "runner.h"

void rescale_home(scene_t *home, sfVideoMode win_size)
{
    set_sprite_size(home->background,
    (sfVector2f){win_size.width, win_size.height});
    sfRenderTexture_destroy(home->rtext);
    home->rtext = sfRenderTexture_create(win_size.width, win_size.height, 0);
    scale_buttons(win_size, home->buttons);
    move_buttons(win_size, home->buttons);
}

scene_t *init_home_screen(sfVideoMode *win_size)
{
    scene_t *home = malloc(sizeof(scene_t));
    sfTexture *t = sfTexture_createFromFile(PICK_BACKGROUND, NULL);

    home->background = sfSprite_create();
    if (t)
        sfSprite_setTexture(home->background, t, 0);
    sfSprite_scale(home->background,
    (sfVector2f){win_size->width / 1366.0, win_size->height / 763.0});
    home->buttons = create_home_buttons();
    home->sprites = NULL;
    home->texts = NULL;
    home->rtext = sfRenderTexture_create(win_size->width,
    win_size->height, 0);
    return home;
}

int get_home_button_at(sfVector2f pos, scene_t *home)
{
    int x = pos.x;
    int y = pos.y;
    button_t *a;

    for (int i = 0; i < 5; i++) {
        a = home->buttons[i];
        if (x >= a->pos.x - a->size.x / 2 && x <= a->pos.x + a->size.x / 2 &&
        y >= a->pos.y - a->size.y / 2 && y <= a->pos.y + a->size.y / 2)
            return i;
    }
    return -1;
}

void reset_home_buttons(window_t *win, int except)
{
    for (int i = 0; i < NB_BUTTONS; i++) {
        if (i == except)
            continue;
        press_button(win->home_screen->buttons[i], 0);
        hover_button(win->home_screen->buttons[i], 0);
    }
}

const sfTexture *get_home_texture(scene_t *home)
{
    sfRenderTexture_clear(home->rtext, sfBlack);
    sfRenderTexture_drawSprite(home->rtext, home->background, NULL);
    for (int i = 0; i < 5; i++)
        sfRenderTexture_drawSprite(home->rtext,
        home->buttons[i]->sprite, NULL);
    sfRenderTexture_display(home->rtext);
    return sfRenderTexture_getTexture(home->rtext);
}
