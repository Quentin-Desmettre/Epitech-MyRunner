/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** collision.c
*/

#include "runner.h"

int manage_intersection(sfFloatRect inter, window_t *win,
sfVector2i ij, int *tab[])
{
    play_level_t *l = win->play_level;
    int type;

    *(tab[0]) = l->blocks[ij.y][ij.x].sprite;
    if (*(tab[0]) != SPIKE)
        *(tab[1]) = 0;
    if (*(tab[0]) > SPIKE) {
        l->blocks[ij.y][ij.x].sprite = -1;
        type = *(tab[0]) == 27 ? 1 : -1;
        l->i_block =
        (l->i_block + type * 100 < 0) ? 0 : l->i_block + type * 100;
        sfSound_play(type < 0 ? win->oof : win->coin);
        return 2;
    } else if (inter.width * inter.height > win->mode.width * 0.875) {
        *(tab[1]) = 1;
        *(tab[0]) = 1;
        return 1;
    }
    return 0;
}

void draw_hitbox(sfFloatRect f, window_t *win, sfColor c)
{
    sfRectangleShape *s = sfRectangleShape_create();

    sfRectangleShape_setFillColor(s, c);
    sfRectangleShape_setSize(s, (sfVector2f){f.width, f.height});
    sfRectangleShape_setPosition(s, (sfVector2f){f.left, f.top});
    sfRenderWindow_drawRectangleShape(win->window, s, NULL);
    sfRectangleShape_destroy(s);
}

int collision_column(sfSprite *s, window_t *win, int j, int *tab[])
{
    sfFloatRect b;
    play_level_t *l = win->play_level;
    int tmp;

    for (int i = 0; l->blocks[j][i].sprite >= 0; i++) {
        sfSprite_setTextureRect(s,
        block_rects[l->blocks[j][i].sprite + 2]);
        move_sprite(s, l->blocks[j][i].pos,
        sfRenderTexture_getSize(l->rtex), l->x_offset);
        b = sfSprite_getGlobalBounds(s);
        tmp = check_inter(win, b, (sfVector2i){i, j}, tab);
        if (tmp)
            return tmp;
    }
    return 0;
}

int has_land(window_t *win)
{
    int v = -1;
    int only_spike = 1;
    sfSprite *s = sfSprite_create();
    play_level_t *l = win->play_level;
    int tmp;

    if (l->blocks[0])
        scale_sprite(s, l->blocks[0][0].sprite + 2,
        sfRenderTexture_getSize(l->rtex));
    for (int j = 1; l->blocks[0] && l->blocks[j] && j < BLOCK_TO_LOAD; j++) {
        tmp = collision_column(s, win, j, (int *[2]){&v, &only_spike});
        if (tmp >= SPIKE)
            return tmp;
    }
    if (only_spike && v >= 0)
        return check_spike_collision(l->blocks, win->player, win);
    return v >= 0 ? 1 : -1;
}

void manage_collision(window_t *win)
{
    int land = has_land(win);

    if (land < 0 || land > SPIKE)
        return;
    if (land == SPIKE) {
        start_death(win);
    } else if (land)
        mod_pos_player(win->player, win->mode);
    win->player->state = 0;
}
