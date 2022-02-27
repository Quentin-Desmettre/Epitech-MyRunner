/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** level_infos.c
*/

#include "runner.h"

int get_level(char **levels, int *i, FILE *f, int *nb)
{
    size_t tmp = 0;

    levels[*i] = 0;
    if (getline(levels + *i, &tmp, f) <= 0) {
        *nb = *i + 1;
        return 1;
    }
    if (!is_file_valid(levels[*i])) {
        levels[*i] = 0;
        (*i)--;
        (*nb)--;
    }
    return 0;
}

int get_difficulty(FILE *f)
{
    size_t tmp;
    char *buf = 0;
    char *diffs[6] = {"easy\n", "normal\n", "hard\n", "harder\n",
    "insane\n", "demon\n"};

    if (getline(&buf, &tmp, f) <= 0)
        return -1;
    for (int i = 0; i < 6; i++) {
        if (my_strcmp(diffs[i], buf) == 0)
            return i;
    }
    return -1;
}

int get_progression(FILE *f)
{
    size_t tmp;
    char *buf = 0;

    getline(&buf, &tmp, f);
    return my_getnbr(buf);
}

level_t *create_level(char *from, window_t *w, sfTexture *diff_tex)
{
    level_t *l = malloc(sizeof(level_t));
    char *buf = get_full_file_name(from);
    FILE *f = fopen(buf, "r");

    if (!f)
        return 0;
    l->descriptor = from;
    l->difficulty = get_difficulty(f);
    if (l->difficulty == -1)
        return 0;
    l->name = init_text(from);
    l->progression = get_progression(f);
    init_lvl_back(l);
    l->diff = init_difficulty(diff_tex, l->difficulty);
    l->p_bar = init_progress_bar(l->progression,
    (sfVector2f){w->mode.width / 1.5, w->mode.height / 15.0});
    scale_level(l, w);
    fclose(f);
    return l;
}

char **get_all_levels(int *size)
{
    FILE *f = fopen(LEVEL_PATH, "r");
    int nb = nb_levels(f) + 1;
    char **levels;

    if (nb == 1 || nb < 0)
        return 0;
    levels = malloc(sizeof(char *) * nb);
    for (int i = 0; i < nb - 1; i++)
        if (get_level(levels, &i, f, &nb))
            break;
    levels[nb ? nb - 1 : 0] = 0;
    *size = nb - 1;
    if (f)
        fclose(f);
    return levels;
}
