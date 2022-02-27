/*
** EPITECH PROJECT, 2021
** runner
** File description:
** level.c
*/

#include "level_editor.h"
#include "runner.h"

void create_block_at(sfMouseButtonEvent *evt, level_editor *win)
{
    sfVector2i pos = {evt->x, evt->y};
    block_t *block;

    pos.x = pos.x - (pos.x % 41) + 20.5 - win->level->offset.x;
    pos.y = pos.y - (pos.y % 41) + 20.5 - win->level->offset.y;
    if (win->level->last_block_pos.x == pos.x &&
    win->level->last_block_pos.y == pos.y)
        return;
    if (pos.y > win->mode.height * 0.8165)
        return;
    block = create_block(win->blocks->current_block,
    (sfVector2f){(float)pos.x, (float)pos.y});
    append_node(&win->level->blocks, block);
    win->level->last_block_pos = pos;
    win->level->nb_blocks++;
}

edit_level_t *create_edit_level(sfVideoMode *dmode)
{
    edit_level_t *level = malloc(sizeof(edit_level_t));
    sfTexture *t = sfTexture_createFromFile(BACKGROUND, NULL);

    level->background = sfSprite_create();
    sfTexture_setRepeated(t, 1);
    sfSprite_setTexture(level->background, t, 0);
    set_sprite_size(level->background,
    (sfVector2f){dmode->width, dmode->height});
    level->blocks = 0;
    level->text = sfRenderTexture_create(dmode->width,
    dmode->height / 1.22, 0);
    level->offset.x = 0;
    level->offset.y = 0;
    level->nb_blocks = 0;
    level->last_block_pos = (sfVector2i){-1, -1};
    level->is_from_file = 0;
    level->file_name = NULL;
    return level;
}

void draw_blocks(level_editor *win, sfSprite *tmp)
{
    edit_level_t *level = win->level;
    block_t *bl;
    sfVector2f *offset = &win->level->offset;

    while (level->blocks) {
        bl = level->blocks->data;
        sfSprite_setTextureRect(tmp, block_rects[bl->sprite]);
        set_sprite_size(tmp, (sfVector2f){41, 41});
        sfSprite_setPosition(tmp,
        (sfVector2f){bl->pos.x - 20.5 + (int)offset->x,
        bl->pos.y - 22.5 + (int)offset->y});
        sfRenderTexture_drawSprite(level->text, tmp, NULL);
        level->blocks = level->blocks->next;
    }
}

const sfTexture *get_level_texture(level_editor *win)
{
    edit_level_t *level = win->level;
    block_pick_t *blocks = win->blocks;
    sfSprite *tmp = sfSprite_create();
    sfIntRect tex_rect = sfSprite_getTextureRect(level->background);

    sfRenderTexture_clear(level->text, sfRed);
    sfSprite_setTexture(tmp, blocks->blk_sheet, 0);
    tex_rect.left = -level->offset.x;
    sfSprite_setTextureRect(level->background, tex_rect);
    sfRenderTexture_drawSprite(level->text, level->background, NULL);
    draw_blocks(win, tmp);
    sfRenderTexture_display(level->text);
    return sfRenderTexture_getTexture(level->text);
}

void draw_edit_level(level_editor *win)
{
    edit_level_t *level = win->level;
    linked_list_t *save = level->blocks;
    const sfTexture *t = get_level_texture(win);
    sfSprite *tmp = sfSprite_create();

    sfSprite_setTexture(tmp, t, 0);
    sfRenderWindow_drawSprite(win->window, tmp, NULL);
    draw_grid(win);
    sfSprite_destroy(tmp);
    level->blocks = save;
}
