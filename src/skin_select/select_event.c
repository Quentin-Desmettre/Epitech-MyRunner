/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** select_event.c
*/

#include "runner.h"

void ss_mouse_move(window_t *win, sfEvent *ev)
{
    sfFloatRect r = sfSprite_getGlobalBounds(win->skin_select->back->sprite);

    if (sfFloatRect_contains(&r, (float)ev->mouseMove.x,
    (float)ev->mouseMove.y))
        hover_button(win->skin_select->back, 1);
    else
        hover_button(win->skin_select->back, 0);
}

void ss_mouse_press(window_t *win, sfEvent *ev)
{
    sfFloatRect r = sfSprite_getGlobalBounds(win->skin_select->back->sprite);

    if (sfFloatRect_contains(&r, (float)ev->mouseButton.x,
    (float)ev->mouseButton.y))
        press_button(win->skin_select->back, 1);
    else
        press_button(win->skin_select->back, 0);
}

void ss_mouse_release(window_t *win, sfEvent *ev)
{
    sfFloatRect r = sfSprite_getGlobalBounds(win->skin_select->back->sprite);

    if (sfFloatRect_contains(&r, (float)ev->mouseButton.x,
    (float)ev->mouseButton.y)) {
        win->is_transition = 1;
        win->next_state = HOME_STATE;
        return;
    }
    for (int i = 0; i < 4; i++) {
        r = sfSprite_getGlobalBounds(win->skin_select->skins[i]->sprite);
        if (sfFloatRect_contains(&r,
        (float)ev->mouseButton.x, (float)ev->mouseButton.y)) {
            sfSprite_setTextureRect(win->skin_select->cur_skin,
            skins_rects[i * 4]);
            sfSprite_setPosition(win->skin_select->highlight,
            sfSprite_getPosition(win->skin_select->skins[i]->sprite));
            win->skin_select->skin_index = i;
            break;
        }
    }
}
