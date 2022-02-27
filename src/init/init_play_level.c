/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** play_level.c
*/

#include "runner.h"

void init_parralax(play_level_t *p, window_t *win)
{
    sfTexture *paras[4] = {sfTexture_createFromFile(PARA_FRONT, NULL),
    sfTexture_createFromFile(PARA_MID, NULL),
    sfTexture_createFromFile(PARA_BACK, NULL)};

    p->parallax = malloc(sizeof(sfSprite *) * 4);
    for (int i = 0; i < 3; i++) {
        p->parallax[i] = sfSprite_create();
        if (!(paras[i]))
            continue;
        sfTexture_setRepeated(paras[i], 1);
        sfSprite_setTexture(p->parallax[i], paras[i], 0);
        sfSprite_setColor(p->parallax[i],
        (sfColor){18, 25 + i * 30, 241, 255});
        sfSprite_setTextureRect(p->parallax[i],
        (sfIntRect){0, 0, win->mode.width * 4, 2049.0});
        sfSprite_scale(p->parallax[i], (sfVector2f)
        {win->mode.height / 2049.0, win->mode.height / 2049.0});
    }
    init_background(p, win);
}

void create_column(block_t **first_blocks, int nb_block,
char **tmp_blocks, int i)
{
    first_blocks[i] = malloc(sizeof(block_t) * (nb_block + 1));
    for (int j = 0; tmp_blocks[j]; j++) {
        first_blocks[i][j].sprite = tmp_blocks[j][0] - 48;
        first_blocks[i][j].pos.y = my_getnbr(tmp_blocks[j] + 2);
        first_blocks[i][j].pos.x = i;
    }
    first_blocks[i][nb_block].sprite = -1;
}

block_t **init_first_blocks(linked_list_t **columns)
{
    block_t **first_blocks = malloc(sizeof(block_t *) * (BLOCK_TO_LOAD + 1));
    char **tmp_blocks = 0;
    int nb_block;

    my_memset(first_blocks, 0, (BLOCK_TO_LOAD + 1) * sizeof(block_t *));
    for (int i = 0; i < BLOCK_TO_LOAD && *columns; i++) {
        tmp_blocks = my_str_to_word_array((*columns)->data, SEPARATOR_STR);
        nb_block = count_occurences(SEPARATOR_CHAR, (*columns)->data) + 1;
        create_column(first_blocks, nb_block, tmp_blocks, i);
        free_str_array(tmp_blocks, 1);
        (*columns) = (*columns)->next;
    }
    return first_blocks;
}

linked_list_t *get_all_blocks(char *buf, int *i, int nb_more)
{
    FILE *f = fopen(buf, "r");
    linked_list_t *columns = 0;
    char *n = 0;
    size_t tmp = 0;

    if (!(f))
        return dprint(2, "ERROR: Cannot access: %s\n", buf) ? NULL : NULL;
    else if (!is_file_valid(buf))
        return dprint(2, "ERROR: File not valid: %s\n", buf) ? NULL : NULL;
    for (*i = 0; getline(&n, &tmp, f) > 0; (*i)++) {
        if (*i >= 3)
            append_node(&columns, my_strdup(n));
        free(n);
        n = 0;
    }
    for (int j = 0; j < nb_more; j++)
        append_node(&columns, my_strdup("3:0\n"));
    fclose(f);
    return columns;
}

play_level_t *init_play_level(level_t *lvl, window_t *win)
{
    char *buf = get_full_file_name(lvl->descriptor);
    play_level_t *p = get_level_from_file(buf, win,
    is_infinite(lvl->descriptor));

    free(buf);
    return p;
}
