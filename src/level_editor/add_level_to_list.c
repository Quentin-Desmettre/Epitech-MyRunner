/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** add_level_to_list.c
*/

#include "runner.h"

void get_file_infos(level_editor *win, char **diff,
char **music, int *fd)
{
    FILE *f = fopen(win->level->file_name, "r");
    size_t t = 0;
    char *tmp = NULL;

    if (!f)
        return;
    if (getline(diff, &t, f) <= 0)
        *diff = NULL;
    else
        diff[0][my_strlen(*diff) - 1] = 0;
    getline(&tmp, &t, f);
    free(tmp);
    if (getline(music, &t, f) <= 0)
        *music = NULL;
    else
        music[0][my_strlen(*music) - 1] = 0;
    *fd = open(win->level->file_name, O_WRONLY | O_TRUNC);
    fclose(f);
}

char **get_all_lines(char const *full)
{
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
    if (f)
        fclose(f);
    return array;
}

void increment_nb_files(char ***lines)
{
    int new_size;

    if (*lines) {
        new_size = my_getnbr((*lines)[0]) + 1;
        free(lines[0][0]);
        (*lines)[0] = nbr_to_str(new_size);
        append_char(lines[0], '\n', 1);
    } else {
        *lines = malloc(sizeof(char *) * 2);
        (*lines)[0] = my_strdup("1\n");
        (*lines)[1] = NULL;
    }
}

void add_level_to_list(char const *file_name)
{
    char **lines = get_all_lines(LEVEL_PATH);
    int fd = open(LEVEL_PATH, O_WRONLY | O_CREAT,
    S_IROTH | S_IRGRP | S_IRUSR | S_IWUSR | S_IWGRP | S_IWOTH);

    if (fd < 0) {
        dprint(2, "ERROR: Cannot open file '%s'.\n", LEVEL_PATH);
        return;
    }
    increment_nb_files(&lines);
    for (int i = 0; lines[i]; i++)
        dprint(fd, "%s", lines[i]);
    dprint(fd, "%s\n", file_name);
}
