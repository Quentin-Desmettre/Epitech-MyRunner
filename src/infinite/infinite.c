/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** infinite.c
*/

#include "structures.h"
#include "runner.h"

char *random_death_phrase(void)
{
    char *phrases[NB_PHRASE] = {
    "You lose !",
    "Cheh !",
    "Game over !",
    "Try jump ?",
    "Did you die ?",
    "U good ?",
    "ur ok ?",
    "Alt F4 to win",
    "So close !",
    "u noob",
    };
    return phrases[rand() % NB_PHRASE];
}

void reset_random(window_t *win)
{
    play_level_t *p = win->play_level;

    p->columns = p->start;
    while (p->columns) {
        free(p->columns->data);
        p->columns = p->columns->next;
    }
    p->columns = get_inf_blocks(&p->nb_blocks);
    p->start = p->columns;
}

int is_infinite(char const *file)
{
    int last_slash = -1;

    for (int i = 0; file[i]; i++)
        if (file[i] == '/')
            last_slash = i;
    if (my_strcmp(file + last_slash + 1, "Infinite mode"))
        return 0;
    return 1;
}

void append_struct(linked_list_t **blocks)
{
    int i_struct = rand() % NB_STRUCT;
    int can_spawn = rand() % 100;
    int i_spawn = -1;
    char **lines;

    for (int i = 0; i < 2 && i_struct == 4; i++)
        i_struct = rand() % NB_STRUCT;
    lines = my_str_to_word_array(structures[i_struct], "\n");
    if (can_spawn < 20) {
        for (i_spawn = 0; lines[i_spawn]; i_spawn++);
        i_spawn = rand() % i_spawn;
    }
    for (int i = 0; lines[i]; i++) {
        if (i == i_spawn)
            add_bonus_to_column(lines + i, can_spawn);
        append_node(blocks, lines[i]);
    }
}

linked_list_t *get_inf_blocks(int *nb_blocks)
{
    linked_list_t *l = NULL;

    *nb_blocks = 100;
    for (int i = 0; i < 15; i++)
        append_node(&l, my_strdup("2:0-3:1"));
    for (int i = 0; i < 10; i++)
        append_struct(&l);
    return l;
}
