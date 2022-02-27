/*
** EPITECH PROJECT, 2021
** runner
** File description:
** main.c
*/

#include "level_editor.h"
#include "runner.h"

sfSprite *create_sprite(char const *sheet)
{
    sfTexture *t = sfTexture_createFromFile(sheet, NULL);
    sfSprite *sprite = sfSprite_create();

    sfSprite_setTexture(sprite, t, 0);
    return sprite;
}

void draw_cursor(level_editor *win)
{
    sfVector2i cpos = sfMouse_getPositionRenderWindow(win->window);
    int i = win->blocks->current_block;
    sfVector2u size = sfRenderWindow_getSize(win->window);

    sfSprite_setPosition(win->cursor, (sfVector2f)
    {cpos.x * 800 / size.x, cpos.y * 600 / size.y});
    sfSprite_setTextureRect(win->cursor, block_rects[i]);
    sfSprite_setOrigin(win->cursor,
    (sfVector2f){block_rects[i].width / 2.0, block_rects[i].height / 2.0});
    sfRenderWindow_drawSprite(win->window, win->cursor, NULL);
}

void draw_edit(level_editor *win)
{
    sfRenderWindow_clear(win->window, sfGreen);
    draw_edit_level(win);
    sfRenderWindow_drawSprite(win->window, win->blocks_sprite, NULL);
    draw_cursor(win);
    sfRenderWindow_display(win->window);
}

int editor_main(sfVideoMode mode, int fullscreen, char *map)
{
    level_editor *win;
    sfEvent event;

    if (map && !is_file_valid(map)) {
        dprint(2, "Invalid map: '%s'.\n", map);
        return 84;
    }
    win = create_level_editor(mode, fullscreen);
    if (map)
        open_editor_map(map, win);
    while (sfRenderWindow_isOpen(win->window)) {
        poll_edit_events(win, &event);
        draw_edit(win);
    }
    return 0;
}
