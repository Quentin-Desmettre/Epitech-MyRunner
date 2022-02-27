/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** update_all_percentages.c
*/

#include "runner.h"

int get_percentage(char *file)
{
    FILE *f = fopen(file, "r");
    char *tmp = f ? NULL : LEVEL_DIR;
    size_t t = 0;
    int r = -1;
    if (!f) {
        append(&tmp, file, 0);
        f = fopen(tmp, "r");
        free(tmp);
        if (!f)
            return -1;
    }
    for (int i = 0; i < 2; i++) {
        if (getline(&tmp, &t, f) < 0)
            return -1;
        if (i)
            r = my_getnbr(tmp);
        free(tmp);
        tmp = 0;
    }
    return fclose(f) ? -1 : r;
}

void update_level_percentage(level_t *level)
{
    int per = get_percentage(level->descriptor);

    if (per < 0)
        return;
    update_progress_bar(level->p_bar, (float)per, level->p_bar->size, 0);
    level->progression = per;
}

void update_all_levels(level_t **levels, int nb)
{
    for (int i = 0; i < nb; i++)
        update_level_percentage(levels[i]);
}
