/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** sounds.c
*/

#include "runner.h"

int check_inter(window_t *win, sfFloatRect b, sfVector2i ij, int **tab)
{
    sfFloatRect inter;
    int tmp;
    sfFloatRect a = sfSprite_getGlobalBounds(win->player->skin);

    if (sfFloatRect_intersects(&a, &b, &inter)) {
        tmp = manage_intersection(inter, win, ij, tab);
        if (tmp == 1)
            return SPIKE;
        if (tmp == 2)
            return SPIKE + 1;
    }
    return 0;
}

void destroy_sound(sfSound *s)
{
    if (!s)
        return;
    sfSoundBuffer_destroy((sfSoundBuffer *)
    sfSound_getBuffer(s));
    sfSound_destroy(s);
}

sfMusic *init_music(char const *file)
{
    sfMusic *m = 0;
    FILE *f = fopen(file, "r");
    size_t tmp = 0;
    char *buf = 0;
    char *music = my_strdup("assets/musics/");
    for (int i = 0; i < 3 && f && getline(&buf, &tmp, f); i++) {
        if (i == 2) {
            append(&music, buf, 1);
            music[my_strlen(music) - 1] = 0;
            m = sfMusic_createFromFile(music);
            free(music);
        }
        free(buf);
        buf = 0;
    }
    if (m)
        sfMusic_setLoop(m, 1);
    if (f)
        fclose(f);
    return m;
}

sfSound *init_sound(char const *file)
{
    sfSound *s = sfSound_create();
    sfSoundBuffer *b = sfSoundBuffer_createFromFile(file);

    if (b)
        sfSound_setBuffer(s, b);
    else {
        sfSound_destroy(s);
        s = 0;
    }
    return s;
}

void destroy_musics(window_t *win)
{
    if (win->lobby_music)
        sfMusic_destroy(win->lobby_music);
    destroy_sound(win->death_sound);
    destroy_sound(win->lpick->launch_sound);
    destroy_sound(win->lvl_complete);
    if (win->play_level && win->play_level->music)
        sfMusic_destroy(win->play_level->music);
    destroy_sound(win->coin);
    destroy_sound(win->oof);
}
