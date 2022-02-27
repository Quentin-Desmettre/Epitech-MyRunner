/*
** EPITECH PROJECT, 2021
** runner
** File description:
** events.c
*/

#include "level_editor.h"

void do_click(level_editor *win, sfVector2f pos, sfMouseButtonEvent *evt)
{
    evt->x = (int)pos.x;
    evt->y = (int)pos.y;
    manage_click(evt, win);
}

void set_block_cursor(sfMouseButtonEvent *evt, level_editor *win)
{
    int tmp = get_block_index(evt->x, evt->y,
    win->blocks->positions, &win->mode);

    if (tmp >= 0)
        win->blocks->current_block = tmp;
}

void remove_block_at(sfMouseButtonEvent *evt, level_editor *win)
{
    int tmp = get_draw_block_index(evt->x + 15, evt->y + 15, win->level);
    if (tmp >= 0) {
        remove_node(&win->level->blocks, tmp);
        win->level->nb_blocks--;
        win->level->last_block_pos = (sfVector2i){-1, -1};
    }
}

void manage_click(sfMouseButtonEvent *evt, level_editor *win)
{
    int tmp = get_block_index(evt->x, evt->y,
    win->blocks->positions, &win->mode);

    if (evt->y > win->mode.height * (0.8165)) {
        if (tmp == 2) {
            save(win);
        }
        if (tmp == CLEAR_ALL) {
            delete_list(&win->level->blocks);
            win->level->nb_blocks = 0;
            win->level->last_block_pos = (sfVector2i){-1, -1};
        }
        if (tmp != 2 && tmp != CLEAR_ALL)
            set_block_cursor(evt, win);
        return;
    }
    if (win->blocks->current_block == ERASE)
        remove_block_at(evt, win);
    else if (win->blocks->current_block)
        create_block_at(evt, win);
}

void poll_edit_events(level_editor *win, sfEvent *event)
{
    sfVector2f pos = sfSprite_getPosition(win->cursor);
    sfMouseButtonEvent evt;

    if (!sfRenderWindow_hasFocus(win->window))
        return;
    while (sfRenderWindow_pollEvent(win->window, event)) {
        if ((event->type == sfEvtKeyPressed &&
        event->key.code == sfKeyEscape) || event->type == sfEvtClosed)
            sfRenderWindow_close(win->window);
        if (event->type == sfEvtMouseButtonPressed)
            do_click(win, pos, &evt);
        if (event->type == sfEvtKeyPressed)
            manage_camera_move(win->level, event->key.code);
    }
    if (sfMouse_isButtonPressed(sfMouseLeft) &&
    pos.y < win->mode.height * (0.8165)) {
        evt.button = sfMouseLeft;
        do_click(win, pos, &evt);
    }
}
