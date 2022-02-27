/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** open_map.c
*/

#include "level_editor.h"
#include "runner.h"

void create_blocks(char const *line, level_editor *win, int x)
{
    char **blocks = my_str_to_word_array(line, "-");
    sfMouseButtonEvent pos = {0, 0, x * 41, 0};
    int i = 0;

    for (i = 0; blocks[i]; i++) {
        pos.y = 490 - (my_getnbr(blocks[i] + 2)) * 41;
        win->blocks->current_block = (blocks[i][0] - 46);
        create_block_at(&pos, win);
        free(blocks[i]);
    }
    free(blocks);
}

void open_editor_map(char *map, level_editor *win)
{
    FILE *f = fopen(map, "r");
    char *line = 0;
    size_t t = 0;

    if (!f)
        return;
    for (int x = 0; getline(&line, &t, f) > 0; x++) {
        if (x > 2)
            create_blocks(line, win, x - 3);
        free(line);
        line = 0;
    }
    win->level->is_from_file = 1;
    win->level->file_name = map;
    fclose(f);
}
