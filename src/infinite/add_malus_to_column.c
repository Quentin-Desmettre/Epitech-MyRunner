/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** add_malus_to_column.c
*/

#include "runner.h"

int get_max_height(char *column)
{
    int i_max = -1;
    int tmp;

    for (int i = 0; column[i]; i++)
        if (i && column[i - 1] == ':') {
            tmp = my_getnbr(column + i);
            i_max = (tmp > i_max) ? tmp : i_max;
        }
    return i_max;
}

void add_bonus_to_column(char **column, int can_spawn)
{
    unsigned height = 0;
    char *tmp;
    char *global;

    height = get_max_height(*column) + 1;
    tmp = nbr_to_str(height);
    global = char_to_str((can_spawn < 10) ? 'K' : 'L');
    re_alloc(&global, replace(global, 0, 0, "-"), 1);
    append(&global, ":", 1);
    append(&global, tmp, 1);
    free(tmp);
    append(column, global, 1);
    free(global);
}
