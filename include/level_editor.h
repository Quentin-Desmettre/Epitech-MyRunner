/*
** EPITECH PROJECT, 2021
** runner
** File description:
** level_editor.h
*/

#ifndef LEVEL_EDITOR_H
    #define LEVEL_EDITOR_H
    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include <SFML/Window.h>
    #include <stdlib.h>
    #include "consts.h"
    #include "structs.h"
    #include <fcntl.h>
    #include <unistd.h>
    #include <math.h>

void delete_list(linked_list_t **l);
void add_level_to_list(char const *file_name);
block_pick_t *init_block_pick(sfVideoMode *mode);
sfSprite *create_block_pick_sprite(block_pick_t *b, sfVideoMode *mode);
sfTexture **create_block_textures(void);
int get_block_index(int x, int y, sfVector2f *positions, sfVideoMode *mode);
const sfTexture *draw_block_pick(block_pick_t *blk);
void set_block_cursor(sfMouseButtonEvent *evt, level_editor *win);
void create_block_at(sfMouseButtonEvent *evt, level_editor *win);
void remove_block_at(sfMouseButtonEvent *evt, level_editor *win);
void manage_click(sfMouseButtonEvent *evt, level_editor *win);
void poll_edit_events(level_editor *win, sfEvent *event);
edit_level_t *create_edit_level(sfVideoMode *mode);
void draw_blocks(level_editor *win, sfSprite *tmp);
const sfTexture *get_level_texture(level_editor *win);
void draw_edit_level(level_editor *win);
void manage_camera_move(edit_level_t *l, sfKeyCode dir);
level_editor *create_level_editor(sfVideoMode mode, int fullscreen);
void draw_grid(level_editor *win);
block_t *create_block(int type, sfVector2f pos);
int get_draw_block_index(int x, int y, edit_level_t *level);
void append_node(linked_list_t **begin, void *data);
void remove_node(linked_list_t **l, int index);
sfSprite *create_sprite(char const *sheet);
void draw_cursor(level_editor *win);
void draw_edit(level_editor *win);
void save(level_editor *win);
void sort_block_array(block_t **array);
block_t **ll_to_block_array(linked_list_t *l, int size);
void open_editor_map(char *map, level_editor *win);
void get_file_infos(level_editor *win, char **diff,
char **music, int *fd);

#endif
