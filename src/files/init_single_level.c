/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** init_single_level.c
*/

#include "runner.h"

int first_check(FILE *fi)
{
    int rval = 1;
    char *buf = 0;
    size_t tmp = 0;

    if (!fi)
        return 0;
    if (get_difficulty(fi) < 0)
        rval = !dprint(2, "Invalid difficuly!\n");
    if (get_progression(fi) < 0 && rval)
        rval = !dprint(2, "Invalid progression!\n");
    if (rval)
        if (getline(&buf, &tmp, fi) <= 0 || my_strlen(buf) <= 1)
            rval = !dprint(2, "Invalid music!\n");
    if (buf)
        free(buf);
    return rval;
}

char *get_full_file_name(char *from)
{
    int len_dir = my_strlen(LEVEL_DIR);
    char *buf = malloc(sizeof(char) * my_strlen(from) +
    len_dir + 1);

    if (my_strncmp(from, LEVEL_DIR, len_dir))
        my_strcpy(buf, LEVEL_DIR);
    else
        buf[0] = 0;
    if (from[my_strlen(from) - 1] == '\n')
        from[my_strlen(from) - 1] = 0;
    my_strcat(buf, from);
    return buf;
}

static void continue_init_level(play_level_t *p, window_t *win)
{
    p->rtex = sfRenderTexture_create(win->mode.width, win->mode.height, 0);
    p->x_offset = 0;
    p->blocks = init_first_blocks(&(p->columns));
    p->blocks_tex = sfTexture_createFromFile(BLOCK_SHEET, NULL);
    p->i_block = 0;
    p->pbar = init_progress_bar(0, (sfVector2f)
    {win->mode.width / 2.0, win->mode.height / 30.0});
    p->draw_clock = sfClock_create();
    p->is_pause = 0;
    p->attempt = init_text(my_strdup("Attempt 1"));
    sfText_setCharacterSize(p->attempt, win->mode.height / BLOCK_PER_SCREEN);
    sfText_setOutlineColor(p->attempt, sfBlack);
    sfText_setOutlineThickness(p->attempt,
    win->mode.height / 200.0);
}

play_level_t *get_level_from_file(char *file, window_t *win, int is_inf)
{
    play_level_t *p = malloc(sizeof(play_level_t));
    float block_size = win->mode.height / BLOCK_PER_SCREEN;

    p->columns = is_inf ? get_inf_blocks(&p->nb_blocks) :
    get_all_blocks(file, &p->nb_blocks, win->mode.width / block_size + 2);
    p->is_infinite = is_inf;
    p->start = p->columns;
    if (p->columns == 0) {
        free(p);
        return 0;
    }
    p->is_from_file = 0;
    init_parralax(p, win);
    p->music = init_music(file);
    if (p->music)
        sfMusic_setVolume(p->music, win->settings->music_vol);
    continue_init_level(p, win);
    return p;
}

int open_map(window_t *win, char *map)
{
    if (!my_strcmp(map, "Infinite mode") || !is_file_valid(map))
        return 1;
    if (win->lobby_music)
        sfMusic_stop(win->lobby_music);
    win->play_level = get_level_from_file(map, win, is_infinite(map));
    if (!win->play_level)
        return 1;
    win->custom_level_name = my_strdup(map);
    win->play_level->is_from_file = 1;
    win->state = PLAY_STATE;
    win->player = init_player(win);
    if (win->play_level->music)
        sfMusic_play(win->play_level->music);
    return 0;
}
