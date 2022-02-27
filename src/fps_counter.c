/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** fps_counter.c
*/

#include "runner.h"

char *get_file_namee(char *file)
{
    int last_slash = 0;

    for (int i = 0; file[i]; i++)
        if (file[i] == '/')
            last_slash = i;
    return file + last_slash + 1;
}

void init_graph(sfClock **c, sfText **t, window_t *w)
{
    if (!(*t)) {
        *c = sfClock_create();
        *t = sfText_create();
        sfText_setFont(*t, sfFont_createFromFile("assets/fonts/pusab.otf"));
    }
    sfText_setCharacterSize(*t, w->mode.height / 30.0);
    sfText_setPosition(*t, (sfVector2f){w->mode.width * 0.8, 0});
}

void draw_fps(window_t *w)
{
    static sfClock *c = NULL;
    static sfText *t = NULL;
    static sfTime last_time = {0};
    float fps;
    char *fps_str;

    init_graph(&c, &t, w);
    fps = 1000000.0 /
    (sfClock_getElapsedTime(c).microseconds - last_time.microseconds);
    fps_str = float_to_str(fps, 2);
    last_time = sfClock_getElapsedTime(c);
    append(&fps_str, " FPS", 1);
    if (sfClock_getElapsedTime(c).microseconds > 500000) {
        sfText_setString(t, fps_str);
        sfClock_restart(c);
    } else
        free(fps_str);
    sfRenderWindow_drawText(w->window, t, NULL);
}
