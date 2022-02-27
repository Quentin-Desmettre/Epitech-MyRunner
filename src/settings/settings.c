/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** settings.c
*/

#include "runner.h"

sfVector2f conv(sfVector2f c, window_t *win)
{
    float nx = win->mode.width / 800.0 * c.x;
    float ny = win->mode.height / 600.0 * c.y;

    return (sfVector2f){nx, ny};
}

button_t *init_set_button(sfTexture *tex, const sfIntRect *rect, int is_center)
{
    button_t *b = malloc(sizeof(button_t));

    b->is_hover = 0;
    b->is_press = 0;
    b->sprite = init_sprite_from_texture(tex, rect, is_center);
    return b;
}

void init_all_settings_button(settings_t *se)
{
    sfTexture *set_tex = sfTexture_createFromFile(SETTINGS_BUTTONS, NULL);

    se->framerate_button = init_set_button(set_tex, &set_rects[3], 1);
    se->res_button = init_set_button(set_tex, &set_rects[7], 1);
    se->sfx_minus = init_set_button(set_tex, &set_rects[0], 1);
    se->sfx_plus = init_set_button(set_tex, &set_rects[1], 1);
    se->music_minus = init_set_button(set_tex, &set_rects[0], 1);
    se->music_plus = init_set_button(set_tex, &set_rects[1], 1);
    se->sfx_vol_text = init_text("100");
    se->music_vol_text = init_text("100");
    se->sfx_text = init_text("SFX");
    se->music_text = init_text("Musics");
}

settings_t *init_settings(window_t *win)
{
    settings_t *se = malloc(sizeof(settings_t));
    sfTexture *t = sfTexture_createFromFile(BUTTONS_PNG, &buttons_rect[5]);

    se->vsync = init_check_box(0, CHECK_PNG, CHECK_BOX_EMPTY, "VSync");
    se->full_screen = init_check_box(0, CHECK_PNG,
    CHECK_BOX_EMPTY, "Fullscreen");
    se->sfx_vol = 100;
    se->music_vol = 100;
    se->framerate = 1;
    se->resolution = 0;
    se->back = init_set_button(t, NULL, 1);
    se->background = init_sprite_from_file(PICK_BACKGROUND);
    se->rtex = sfRenderTexture_create(win->mode.width, win->mode.height, 0);
    init_all_settings_button(se);
    rescale_settings(se, win);
    update_all_texts(se);
    se->repeat_clock = sfClock_create();
    return se;
}
