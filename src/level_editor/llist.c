/*
** EPITECH PROJECT, 2021
** runner
** File description:
** llist.c
*/

#include "level_editor.h"

block_t **ll_to_block_array(linked_list_t *l, int size)
{
    block_t **ar = malloc(sizeof(block_t *) * (size + 1));
    int i = 0;

    for (i = 0; i < size; i++) {
        ar[i] = l->data;
        l = l->next;
    }
    ar[i] = 0;
    return ar;
}

void swap_blocks(block_t **array, int j)
{
    block_t *tmp;

    if (array[j]->pos.x > array[j + 1]->pos.x) {
        tmp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = tmp;
    }
}

void sort_block_array(block_t **array)
{
    for (int i = 0; array[i]; i++)
        for (int j = 0; array[j + i + 1]; j++)
            swap_blocks(array, j);
}

void delete_list(linked_list_t **l)
{
    while (*l)
        remove_node(l, 0);
}
