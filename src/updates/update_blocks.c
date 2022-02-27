/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** update_blocks.c
*/

#include "runner.h"

void rotate_blocks(play_level_t *l)
{
    for (int i = 0; l->blocks[i]; i++) {
        l->blocks[i] = l->blocks[i + 1];
        if (!(l->blocks[i]))
            break;
        for (int j = 0; l->blocks[i][j].sprite >= 0; j++)
            l->blocks[i][j].pos.x = i;
    }
}

void update_blocks(play_level_t *l)
{
    sfVector2u win_size = sfRenderTexture_getSize(l->rtex);
    float cible_size = win_size.y / BLOCK_PER_SCREEN;
    char **tmp_blocks = 0;

    if (l->x_offset >= cible_size) {
        l->x_offset = 0;
        l->i_block++;
        free(l->blocks[0]);
        rotate_blocks(l);
        if (!(l->columns))
            append_struct(&(l->columns));
        tmp_blocks = my_str_to_word_array(l->columns->data, SEPARATOR_STR);
        create_column(l->blocks,
        count_occurences(SEPARATOR_CHAR, l->columns->data) + 1, tmp_blocks,
        BLOCK_TO_LOAD - 1);
        free_str_array(tmp_blocks, 1);
        l->columns = l->columns->next;
    }
}
