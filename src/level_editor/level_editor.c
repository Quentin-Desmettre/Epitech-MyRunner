/*
** EPITECH PROJECT, 2021
** runner
** File description:
** level_editor.c
*/

#include "level_editor.h"
#include "runner.h"

void manage_camera_move(edit_level_t *l, sfKeyCode dir)
{
    if (dir == sfKeyLeft) {
        if (l->offset.x == 0)
            return;
        l->offset.x += 41;
    }
    if (dir == sfKeyRight)
        l->offset.x -= 41;
}

level_editor *create_level_editor(sfVideoMode mode, int fullscreen)
{
    level_editor *editor = malloc(sizeof(level_editor));

    editor->mode = (sfVideoMode){800, 600, 32};
    editor->window = sfRenderWindow_create(
    editor->mode, "My_runner", fullscreen ? sfFullscreen : sfClose, NULL);
    editor->blocks = init_block_pick(&editor->mode);
    editor->blocks_sprite = create_block_pick_sprite(editor->blocks,
    &editor->mode);
    editor->cursor = create_sprite(BLOCK_SHEET);
    sfSprite_scale(editor->cursor, (sfVector2f){0.25, 0.25});
    sfRenderWindow_setFramerateLimit(editor->window, 60);
    editor->level = create_edit_level(&editor->mode);
    editor->grid = sfSprite_create();
    sfSprite_setTexture(editor->grid, sfTexture_createFromFile(GRID, NULL), 0);
    sfSprite_setColor(editor->grid, (sfColor){255, 255, 255, 127});
    set_sprite_size(editor->grid, (sfVector2f){41, 41});
    if (!fullscreen)
        sfRenderWindow_setSize(editor->window,
        (sfVector2u){mode.width, mode.height});
    return editor;
}

void draw_grid(level_editor *win)
{
    sfVector2f pos = {0, win->mode.height * (0.8165) - 1};

    for (unsigned j = 0; j < win->mode.height / 10; j++) {
        for (unsigned i = 0; i < win->mode.width / 30; i++) {
            sfSprite_setPosition(win->grid, pos);
            sfRenderWindow_drawSprite(win->window, win->grid, NULL);
            pos.x += 41;
        }
        pos.y -= 41;
        pos.x = 0;
    }
}

block_t *create_block(int type, sfVector2f pos)
{
    block_t *block = malloc(sizeof(block_t));

    block->pos = pos;
    block->sprite = type;
    return block;
}

int get_draw_block_index(int x, int y, edit_level_t *level)
{
    linked_list_t *save = level->blocks;
    sfVector2f pos;
    sfVector2f o = level->offset;
    block_t *bl;

    for (int i = 0; level->blocks; i++) {
        bl = (block_t *)level->blocks->data;
        pos = bl->pos;
        if (x - o.x >= pos.x && x - o.x <= pos.x +
        block_rects[bl->sprite].width / 4.0 &&
        y - o.y >= pos.y && y - o.y <= pos.y +
        block_rects[bl->sprite].height / 4.0) {
            level->blocks = save;
            return i;
        }
        level->blocks = level->blocks->next;
    }
    level->blocks = save;
    return -1;
}
