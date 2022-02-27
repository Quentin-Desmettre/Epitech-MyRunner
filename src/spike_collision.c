/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** spike_collision.c
*/

#include "runner.h"

int is_intersect(sfVector2f a0, sfVector2f a1, sfVector2f b0, sfVector2f b1)
{
    float aa = (a1.y - a0.y) / (a1.x - a0.x);
    float ab = a0.y - (aa * a0.x);
    float ba = (b1.y - b0.y) / (b1.x - b0.x);
    float bb = b0.y - (ba * b0.x);
    float x;

    if (aa == ba)
        return 0;
    x = (bb - ab) / (aa - ba);
    if (x < a0.x || x > a1.x)
        return 0;
    if (x < b0.x || x > b1.x)
        return 0;
    return 1;
}

static sfFloatRect get_block_bounds(block_t block, window_t *win)
{
    sfSprite *s = sfSprite_create();
    sfFloatRect bounds;

    sfSprite_setTextureRect(s, block_rects[28]);
    move_sprite(s, block.pos,
    (sfVector2u){win->mode.width, win->mode.height},
    win->play_level->x_offset);
    scale_sprite(s, 28,
    (sfVector2u){win->mode.width, win->mode.height});
    bounds = sfSprite_getGlobalBounds(s);
    sfSprite_destroy(s);
    return bounds;
}

static int player_intersect(player_t *p, block_t block, window_t *win)
{
    sfFloatRect p_bounds = sfSprite_getGlobalBounds(p->skin);
    sfFloatRect s_bounds = get_block_bounds(block, win);
    sfVector2f player_bl = BOTTOM_LEFT(p_bounds);
    sfVector2f player_br = BOTTOM_RIGHT(p_bounds);
    sfVector2f spike_bl = BOTTOM_LEFT(s_bounds);
    sfVector2f spike_mu = MID_UP(s_bounds);
    sfVector2f spike_br = BOTTOM_RIGHT(s_bounds);

    if (is_intersect(player_bl, player_br, spike_bl, spike_mu))
        return 1;
    else if (is_intersect(player_bl, player_br, spike_mu, spike_br))
        return 1;
    else
        return 0;
}

static int check_column(int i, block_t **blocks, player_t *p, window_t *win)
{
    for (int j = 0; blocks[i][j].sprite >= 0; j++) {
        if (blocks[i][j].sprite != SPIKE)
            continue;
        if (player_intersect(p, blocks[i][j], win))
            return 1;
    }
    return 0;
}

int check_spike_collision(block_t **blocks, player_t *p, window_t *win)
{
    for (int i = 1; blocks[0] && blocks[i] && i < 5; i++)
        if (check_column(i, blocks, p, win))
            return SPIKE;
    return -1;
}
