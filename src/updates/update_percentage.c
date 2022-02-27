/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** update_percentage.c
*/

#include "runner.h"

int nb_lines(char const *file)
{
    FILE *f = fopen(file, "r");
    int counter = 0;
    char *tmp = 0;
    size_t t = 0;

    if (!f)
        return 0;
    for (counter = 0; getline(&tmp, &t, f) > 0; counter++);
    fclose(f);
    return counter;
}

void rewrite_file(char const *lvl, char **array)
{
    int fd = open(lvl, O_WRONLY | O_TRUNC);

    if (fd < 0)
        return;
    for (int i = 0; array[i]; i++)
        dprint(fd, "%s", array[i]);
}

int finish_update(char **array, FILE *f, int new_percentage, char *full)
{
    int rval = 0;

    if (my_getnbr(array[1]) < new_percentage) {
        free(array[1]);
        array[1] = nbr_to_str(new_percentage);
        append(array + 1, "\n", 1);
        rval = 1;
    }
    rewrite_file(full, array);
    fclose(f);
    free(full);
    free_str_array(array, 1);
    return rval;
}

int update_percentage(char const *lvl_name, int new_percentage)
{
    char *full = get_full_file_name((char *)lvl_name);
    int n_line = nb_lines(full);
    char **array;
    size_t t = 0;
    FILE *f;

    if (!n_line)
        return 0;
    array = malloc(sizeof(char *) * (n_line + 1));
    array[n_line] = 0;
    f = fopen(full, "r");
    my_memset(array, 0, sizeof(char *) * n_line);
    for (int i = 0; i < n_line; i++)
        getline(array + i, &t, f);
    return finish_update(array, f, new_percentage, full);
}

void actu_percentage(window_t *win)
{
    int new_progression = win->play_level->pbar->adv;
    int cur_lvl = win->lpick->current_level;

    if (win->play_level->is_from_file) {
        if (update_percentage(
        get_file_namee(win->custom_level_name), new_progression))
            update_all_levels(win->lpick->levels, win->lpick->nb_level);
        return;
    }
    if (update_percentage(sfText_getString(win->lpick->levels[cur_lvl]->name),
    new_progression))
        win->lpick->levels[cur_lvl]->progression = new_progression;
}
