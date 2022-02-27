/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** level_pick.c
*/

#include "runner.h"

void init_all_levels(level_pick *lpick, char **all_files,
int size, window_t *w)
{
    sfTexture *diff_tex = sfTexture_createFromFile(DIFF_PNG, NULL);

    lpick->is_error = 0;
    lpick->levels = malloc(sizeof(level_t *) * size);
    lpick->nb_level = size;
    for (int i = 0; all_files[i]; i++) {
        lpick->levels[i] = create_level(all_files[i], w, diff_tex);
        if (!lpick->levels[i])
            i--;
    }
    lpick->current_level = 0;
}

int is_list_valid(void)
{
    FILE *f = fopen(LEVEL_PATH, "r");
    char *buf = 0;
    size_t tmp = 0;

    if (!f)
        return 0;
    if (getline(&buf, &tmp, f) <= 0) {
        fclose(f);
        return 0;
    }
    fclose(f);
    if (!contain_only(buf, "0123456789\n") ||
    my_strlen(buf) == 1)
        return 0;
    return 1;
}

int nb_levels(FILE *f)
{
    char *buf = 0;
    size_t tmp = 0;

    if (!f || !is_list_valid())
        return 0;
    getline(&buf, &tmp, f);
    return my_getnbr(buf);
}

static void init_left(window_t *win, level_pick *lpick)
{
    lpick->launch_sound = init_sound(LAUNCH_SOUND);
    lpick->rtex = sfRenderTexture_create(win->mode.width, win->mode.height, 0);
    scale_buttons(win->mode, win->home_screen->buttons);
    move_lpick_buttons(win);
}

level_pick *create_level_pick(window_t *win)
{
    int size = 0;
    char **all_files = get_all_levels(&size);
    level_pick *lpick = malloc(sizeof(level_pick));
    sfTexture *t = sfTexture_createFromFile(PICK_BACKGROUND, NULL);

    lpick->background = sfSprite_create();
    if (t)
        sfSprite_setTexture(lpick->background, t, 0);
    sfSprite_scale(lpick->background, (sfVector2f)
    {win->mode.width / 1904.0, win->mode.height / 1068.0});
    if (all_files && size)
        init_all_levels(lpick, all_files, size, win);
    else {
        lpick->is_error = 1;
        lpick->nb_level = 0;
    }
    init_left(win, lpick);
    return lpick;
}
