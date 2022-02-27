/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** play_level_utility.c
*/

#include "runner.h"

void free_sprite(sfSprite *s, int free_tex)
{
    if (free_tex && sfSprite_getTexture(s))
        sfTexture_destroy((sfTexture *)sfSprite_getTexture(s));
    sfSprite_destroy(s);
}

void free_text(sfText *t, int free_font)
{
    if (free_font && sfText_getFont(t))
        sfFont_destroy((sfFont *)sfText_getFont(t));
    sfText_destroy(t);
}

void free_pl_graphic(play_level_t *p)
{
    if (p->blocks_tex)
        sfTexture_destroy(p->blocks_tex);
    sfClock_destroy(p->draw_clock);
    free_text(p->attempt, 1);
    if (p->music)
        sfMusic_destroy(p->music);
    for (int i = 0; p->blocks[i]; i++)
        free(p->blocks[i]);
    free(p->blocks);
    free(p);
}

void free_play_level(play_level_t *p)
{
    linked_list_t *save;

    sfRenderTexture_destroy(p->rtex);
    for (int i = 0; i < 4; i++)
        free_sprite(p->parallax[i], 1);
    p->columns = p->start;
    free_text(p->pbar->percent, 1);
    sfRenderTexture_destroy(p->pbar->tex);
    free(p->pbar);
    while (p->columns) {
        save = p->columns->next;
        free(p->columns->data);
        free(p->columns);
        p->columns = save;
    }
    free_pl_graphic(p);
}

void load_level(window_t *win)
{
    if (win->play_level)
        free_play_level(win->play_level);
    win->play_level = init_play_level(win->lpick->levels
    [win->lpick->current_level], win);
}
