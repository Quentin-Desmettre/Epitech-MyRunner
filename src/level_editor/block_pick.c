/*
** EPITECH PROJECT, 2021
** runner
** File description:
** block_pick.c
*/

#include "level_editor.h"

block_pick_t *init_block_pick(sfVideoMode *dmode)
{
    block_pick_t *b = malloc(sizeof(block_pick_t));
    sfVector2f pos = {-20, 15};

    b->current_block = 0;
    b->blk_sheet = sfTexture_createFromFile(BLOCK_SHEET, NULL);
    b->blocks = sfRenderTexture_create(dmode->width, dmode->height / 5.45, 0);
    b->positions = malloc(sizeof(sfVector2f) * NB_BLOCK);
    for (int i = 0; i < NB_BLOCK; i++) {
        b->positions[i].y = 15 + 50 * (i % 2) + 30 -
        block_rects[i].height * 0.25;
        b->positions[i].x = pos.x + ((i + 1) % 2) * 40;
        pos.x += ((i + 1) % 2) * 40;
    }
    return b;
}

sfSprite *create_block_pick_sprite(block_pick_t *b, sfVideoMode *mode)
{
    sfTexture const *t = draw_block_pick(b);
    sfSprite *s = sfSprite_create();

    sfSprite_setTexture(s, t, 0);
    sfSprite_setPosition(s, (sfVector2f){0, mode->height * (0.8165)});
    return s;
}

sfTexture **create_block_textures(void)
{
    sfTexture **textures = malloc(sizeof(sfTexture *) * NB_BLOCK);

    for (int i = 0; i < NB_BLOCK; i++)
        textures[i] = sfTexture_createFromFile(BLOCK_SHEET, &block_rects[i]);
    return textures;
}

int get_block_index(int x, int y, sfVector2f *positions, sfVideoMode *mode)
{
    for (int i = 0; i < NB_BLOCK; i++) {
        if (x >= positions[i].x &&
        x <= positions[i].x + block_rects[i].width / 4 &&
        y - mode->height * (0.8165) >= positions[i].y &&
        y - mode->height * (0.8165) <=
        positions[i].y + block_rects[i].height / 4)
            return i;
    }
    return -1;
}

const sfTexture *draw_block_pick(block_pick_t *blk)
{
    sfSprite *tmp = sfSprite_create();

    sfRenderTexture_clear(blk->blocks, sfBlue);
    sfSprite_setTexture(tmp, blk->blk_sheet, 0);
    sfSprite_setScale(tmp, (sfVector2f){0.25, 0.25});
    for (int i = 0; i < NB_BLOCK; i++) {
        sfSprite_setTextureRect(tmp, block_rects[i]);
        sfSprite_setPosition(tmp, blk->positions[i]);
        sfRenderTexture_drawSprite(blk->blocks, tmp, NULL);
    }
    sfRenderTexture_display(blk->blocks);
    return sfRenderTexture_getTexture(blk->blocks);
}
