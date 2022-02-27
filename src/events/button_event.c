/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** buttonc.c
*/

#include "runner.h"

void factor_color(sfSprite *s, float factor)
{
    sfColor c = sfSprite_getColor(s);

    c.r *= factor;
    c.g *= factor;
    c.b *= factor;
    sfSprite_setColor(s, c);
}

void move_lvl_index(int index, window_t *win)
{
    int *cur_lvl = &win->lpick->current_level;
    int nb_lvl = win->lpick->nb_level;

    *cur_lvl += (index == 6) ? -1 : 1;
    if (nb_lvl == 0)
        return;
    if (*cur_lvl < 0)
        *cur_lvl = nb_lvl - 1;
    if (*cur_lvl >= nb_lvl)
        *cur_lvl %= nb_lvl;
}

void hover_button(button_t *b, int is_on)
{
    if (is_on == b->is_hover)
        return;
    if (is_on) {
        sfSprite_scale(b->sprite, (sfVector2f){1.1, 1.1});
    } else {
        sfSprite_scale(b->sprite, (sfVector2f){0.909, 0.909});
    }
    b->is_hover = is_on;
}

void press_button(button_t *b, int is_press)
{
    if (is_press == b->is_press)
        return;
    if (is_press) {
        sfSprite_scale(b->sprite, (sfVector2f){0.833, 0.833});
        factor_color(b->sprite, 1.0 / 2);
    } else {
        sfSprite_scale(b->sprite, (sfVector2f){1.2, 1.2});
        factor_color(b->sprite, 2.0);
    }
    b->is_press = is_press;
}

void release_button(int index, window_t *win)
{
    int tab[6] = {SKIN_STATE, LEVEL_STATE, EDITOR_STATE,
    SETTINGS_STATE, CLOSE_STATE, HOME_STATE};

    if (index < 6)
        win->next_state = tab[index];
    if (index == 6 || index == 7) {
        move_lvl_index(index, win);
        return;
    }
    win->is_transition = 1;
    sfClock_restart(win->state_clock);
}
