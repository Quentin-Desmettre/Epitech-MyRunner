/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** draw_play_level.c
*/

#include "runner.h"

void draw_background(play_level_t *l, player_t *player)
{
    sfIntRect cur_rect;
    int restart = 0;
    int progression = my_getnbr(sfText_getString(l->pbar->percent));

    sfRenderTexture_drawSprite(l->rtex, l->parallax[3], NULL);
    for (int i = 2; i >= 0; i--) {
        cur_rect = sfSprite_getTextureRect(l->parallax[i]);
        if (sfClock_getElapsedTime(l->draw_clock).microseconds > 33333 &&
        (player && player->anim_state != ANIM_DEATH) && l->is_pause == 0 &&
        (progression < 100 || l->is_infinite)) {
            cur_rect.left += PARA_SPEED / pow(2, i);
            restart = 1;
        }
        sfSprite_setTextureRect(l->parallax[i], cur_rect);
        sfRenderTexture_drawSprite(l->rtex, l->parallax[i], NULL);
    }
    if (restart)
        sfClock_restart(l->draw_clock);
}

sfSprite *draw_progress_bar_my(
float adv, progress_bar_t *pbar, sfVector2f pos, int is_infinite)
{
    sfSprite *t;

    update_progress_bar(pbar, adv, pbar->size, is_infinite);
    t = sprite_progress_bar(pbar);
    sfSprite_setPosition(t, pos);
    return t;
}

void draw_play_pbar(sfSprite *s, play_level_t *l, window_t *win)
{
    sfVector2u size = sfRenderTexture_getSize(l->rtex);
    float block_size = win->mode.height / BLOCK_PER_SCREEN;

    sfSprite_destroy(s);
    s = draw_progress_bar_my(100.0 *
    (((float)l->i_block + l->x_offset / (float)block_size) /
    (l->nb_blocks - 4)), l->pbar,
    (sfVector2f){size.x / 2.0, size.y / 15.0}, win->play_level->is_infinite);
    sfRenderTexture_drawSprite(l->rtex, s, NULL);
    sfSprite_destroy(s);
    sfRenderTexture_display(l->rtex);
}

const sfTexture *get_play_texture(play_level_t *l,
player_t *player, window_t *win)
{
    sfSprite *s = sfSprite_create();

    sfSprite_setTexture(s, l->blocks_tex, 0);
    sfRenderTexture_clear(l->rtex, sfBlack);
    draw_background(l, player);
    if (l->blocks[0])
        scale_sprite(s, l->blocks[0][0].sprite + 2,
        sfRenderTexture_getSize(l->rtex));
    for (int i = 0; i < BLOCK_TO_LOAD && l->blocks[i]; i++) {
        for (int j = 0; l->blocks[i][j].sprite >= 0; j++) {
            sfSprite_setTextureRect(s,
            block_rects[l->blocks[i][j].sprite + 2]);
            move_sprite(s, l->blocks[i][j].pos,
            sfRenderTexture_getSize(l->rtex), l->x_offset);
            sfRenderTexture_drawSprite(l->rtex, s, NULL);
        }
    }
    draw_play_pbar(s, l, win);
    return sfRenderTexture_getTexture(l->rtex);
}

sfSprite *get_play_sprite(play_level_t *l, player_t *player, window_t *win)
{
    const sfTexture *t = get_play_texture(l, player, win);
    sfSprite *s = sfSprite_create();

    sfSprite_setTexture(s, t, 0);
    return s;
}
