/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** save.c
*/

#include "level_editor.h"
#include "runner.h"
#include "diffs.h"

void write_block(sfVector2i i_fd, block_t **blocks_array,
level_editor *win, int *last_x)
{
    if (!i_fd.x)
        *last_x = blocks_array[i_fd.x]->pos.x;
    if (*last_x != blocks_array[i_fd.x]->pos.x) {
        for (int z = 0; z < (blocks_array[i_fd.x]->pos.x - *last_x) / 41; z++)
            write(i_fd.y, "\n", 1);
        *last_x = blocks_array[i_fd.x]->pos.x;
    }
    dprint(i_fd.y, "%c:%d", blocks_array[i_fd.x]->sprite + 46,
    (int)(ABS(blocks_array[i_fd.x]->pos.y -
    win->mode.height * 0.8165) / 41.0));
    if (blocks_array[i_fd.x + 1] &&
    *last_x == blocks_array[i_fd.x + 1]->pos.x)
        write(i_fd.y, SEPARATOR_STR, 1);
}

int write_file(level_editor *win, int fd)
{
    linked_list_t *blocks = win->level->blocks;
    block_t **blocks_array = ll_to_block_array(blocks, win->level->nb_blocks);
    int last_x = -1;

    sort_block_array(blocks_array);
    if (fd < 0)
        return 1;
    if (blocks_array[0] && blocks_array[0]->pos.x != 0)
        for (int z = 1; z < blocks_array[0]->pos.x / 41.0; z++)
            write(fd, "\n", 1);
    for (int i = 0; blocks_array[i]; i++)
        write_block((sfVector2i){i, fd}, blocks_array, win, &last_x);
    write(fd, "\n", 1);
    print("Done!\n");
    close(fd);
    return 0;
}

char *try_get_diff(void)
{
    int is_valid = 0;
    char *d = get_input("Difficulty: ");

    for (int i = 0; i < 6; i++) {
        if (my_strcmp(d, diffs[i]) == 0)
            is_valid = 1;
    }
    if (!is_valid) {
        dprint(2, "Wrong difficulty. The supported difficulties are:\n");
        for (int i = 0; i < 6; i++) {
            dprint(2, "%s\n", diffs[i]);
        }
        free(d);
        return 0;
    }
    return d;
}

int get_file_name(char **file_name)
{
    int fd = -1;
    char *tmp;

    while (fd < 0) {
        *file_name = get_input("Level name: ");
        tmp = replace(*file_name, 0, 0, "assets/levels/");
        fd = open(tmp, O_WRONLY | O_TRUNC | O_CREAT,
        S_IROTH | S_IRGRP | S_IRUSR | S_IWUSR | S_IWGRP | S_IWOTH);
        if (fd < 0) {
            dprint(2, "Unable to create '%s'. "
            "Please try again.\n\n", tmp);
            free(*file_name);
        }
        free(tmp);
    }
    return fd;
}

void save(level_editor *win)
{
    char *file_name;
    char *diff = 0;
    char *music = 0;
    int fd;

    sfRenderWindow_close(win->window);
    fd = win->level->is_from_file ? 0 : get_file_name(&file_name);
    if (win->level->is_from_file)
        get_file_infos(win, &diff, &music, &fd);
    else {
        while (!diff)
            diff = try_get_diff();
        music = get_input("Level music: ");
    }
    if (fd > 0) {
        dprint(fd, "%s\n0\n%s\n", diff, music);
        if (!write_file(win, fd) && !win->level->is_from_file)
            add_level_to_list(file_name);
        close(fd);
    }
}
