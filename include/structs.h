/*
** EPITECH PROJECT, 2021
** runner
** File description:
** structs.h
*/

#ifndef STRUCTS_H
    #define STRUCTS_H
    #include <SFML/Audio.h>
    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include <SFML/Window.h>
    #include "lib/libmy.h"

typedef struct {
    int sprite;
    sfVector2f pos;
} block_t;

typedef struct {
    sfRenderTexture *text;
    sfSprite *background;
    linked_list_t *blocks;
    unsigned nb_blocks;
    sfVector2f offset;
    sfVector2i last_block_pos;
    int max_x_offset;
    int is_from_file;
    char *file_name;
} edit_level_t;

typedef struct {
    sfRenderTexture *blocks;
    sfTexture *blk_sheet;
    sfVector2f *positions;
    int current_block;
} block_pick_t;

typedef struct {
    sfRenderWindow *window;
    edit_level_t *level;
    sfSprite *cursor;
    block_pick_t *blocks;
    sfSprite *blocks_sprite;
    sfSprite *grid;
    sfVideoMode mode;
} level_editor;

#endif
