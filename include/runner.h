/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** runner.h
*/

#ifndef RUNNER_H
    #define RUNNER_H

    // Libs
    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include <SFML/Window.h>
    #include <SFML/Audio.h>
    #include <math.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include "lib/libmy.h"
    #include "level_editor.h"
    #include <time.h>

    // sprites
    #define HOME_BACKGROUND "assets/sprites/background.png"
    #define BUTTONS_PNG "assets/sprites/buttons.png"
    #define PICK_BACKGROUND "assets/sprites/level_background.png"
    #define ACTU_LVL_BACK "assets/sprites/lvl_back.png"
    #define DIFF_PNG "assets/sprites/difficulties.png"
    #define BLOCK_SHEET "assets/sprites/ssheet.png"
    #define SKIN_PNG "assets/sprites/skin.png"
    #define DEATH_EFFET "assets/sprites/death_effect.png"
    #define CHECK_PNG "assets/sprites/checked.png"
    #define CHECK_BOX_EMPTY "assets/sprites/box.png"
    #define EMPTY_BUTTON "assets/sprites/button.png"
    #define SETTINGS_BUTTONS "assets/sprites/set_but.png"
    #define SKINS_SHEET "assets/sprites/players.png"
    #define COMPLETE_PNG "assets/sprites/lvl_complete.png"
    #define BONUS "assets/sprites/bonus.png"
    #define MALUS "assets/sprites/malus.png"
    #define DOT_SPACING 2.5
    #define DE_SIZE 256
    #define BAD_ARGS "Wrong arguments. ./my_runner -h for more informations.\n"

    // Parallax
    #define PARA_FRONT "assets/sprites/front.png"
    #define PARA_MID "assets/sprites/mid.png"
    #define PARA_BACK "assets/sprites/back.png"
    #define PARA_S_BACK "assets/sprites/play_background.png"
    #define PARA_SPEED 10

    // sfx
    #define DEATH_SOUND "assets/sfx/death.ogg"
    #define LAUNCH_SOUND "assets/sfx/launch.ogg"
    #define LVL_COMPLETE "assets/sfx/level_complete.ogg"

    // Musics
    #define LOBBY_MUSIC "assets/musics/lobby.ogg"

    // Levels
    #define LEVEL_PATH "assets/levels/list"
    #define LEVEL_DIR "assets/levels/"

    // Fonts
    #define GD_FONT "assets/fonts/pusab.otf"

    // Render states
    #define HOME_STATE 0
    #define LEVEL_STATE 1
    #define CLOSE_STATE 2
    #define SKIN_STATE 3
    #define SETTINGS_STATE 4
    #define EDITOR_STATE 5
    #define PLAY_STATE 6

    // Blocks
    #define NB_BUTTONS 8
    #define BLOCK_WIDTH 122
    #define BLOCK_HEIGHT 122
    #define BLOCK_PER_SCREEN 12.0
    #define BLOCK_TO_LOAD 35

    // Physics
    #define Y_VELOCITY -21.4
    #define GRAVITY 1.6
    #define X_VELOCITY 8.0
    #define ABS(x) (((x) < 0) ? -(x) : (x))
    #define REPEAT_DELAY 180000

    // Anim state
    #define NO_ANIM 0
    #define ANIM_DEATH 1
    #define SPIKE 26
    #define FRAMERATE 60
    #define NB_PHRASE 10

    // spike collision
    #define BOTTOM_LEFT(x) (sfVector2f){x.left, x.top + x.height}
    #define BOTTOM_RIGHT(x) (sfVector2f){x.left + x.width, x.top + x.height}
    #define MID_UP(x) (sfVector2f){x.left + x.width / 2.0, x.top}

typedef struct {
    sfSprite *skin;
    sfClock *jump_clock;
    sfTime last_jump;
    sfClock *move_clock;
    sfClock *anim_clock;
    sfTime last_move;
    sfTexture *tex;
    int anim_state;
    int rect;
    int state;
    float velocity;
    int progression;
    int sprite_type;
    int is_ending;
} player_t;

typedef struct {
    sfRenderTexture *tex;
    sfText *percent;
    float adv;
    sfVector2f size;
} progress_bar_t;

typedef struct {
    sfSprite *sprite;
    int is_press;
    int is_hover;
    sfVector2f pos;
    sfVector2f size;
    sfText *text;
} button_t;

typedef struct {
    sfRenderTexture *rtex;
    sfSprite *background;
    button_t *back;
    sfSprite *cur_skin;
    button_t *skins[4];
    sfClock *draw_clock;
    sfSprite *highlight;
    int skin_index;
} skin_select_t;

typedef struct {
    sfRenderTexture *rtext;
    sfSprite *background;
    sfText **texts;
    sfSprite **sprites;
    button_t **buttons;
} scene_t;

typedef struct {
    sfSprite **parallax;
    sfRenderTexture *rtex;
    linked_list_t *columns;
    linked_list_t *start;
    block_t **blocks;
    sfTexture *blocks_tex;
    progress_bar_t *pbar;
    sfClock *draw_clock;
    sfMusic *music;
    sfText *attempt;
    float x_offset;
    int is_from_file;
    int i_block;
    int nb_blocks;
    int is_pause;
    int is_infinite;
} play_level_t;

typedef struct {
    sfRenderTexture *rtex;
    sfSprite *background;
    char *descriptor;
    sfSprite *diff;
    int difficulty;
    sfText *name;
    int progression;
    progress_bar_t *p_bar;
} level_t;

typedef struct {
    sfRenderTexture *rtex;
    sfSprite *background;
    sfSprite *error;
    int current_level;
    level_t **levels;
    sfSound *launch_sound;
    int nb_level;
    int is_error;
} level_pick;

typedef struct {
    sfSprite *box;
    sfSprite *check;
    sfText *text;
    int is_checked;
} check_box;

typedef struct {
    check_box *vsync;
    check_box *full_screen;

    button_t *framerate_button;
    button_t *res_button;

    sfText *sfx_vol_text;
    sfText *sfx_text;
    button_t *sfx_plus;
    button_t *sfx_minus;

    sfText *music_vol_text;
    sfText *music_text;
    button_t *music_plus;
    button_t *music_minus;

    button_t *back;
    sfSprite *background;

    sfRenderTexture *rtex;

    sfClock *repeat_clock;

    int sfx_vol;
    int music_vol;
    int framerate;
    int resolution;
} settings_t;

typedef struct {
    sfRenderTexture *rtex;
    sfSprite *background;
    progress_bar_t *pbar;
    sfText *l_name;
    button_t *resume;
    button_t *quit;
} pause_t;

typedef struct {
    sfVideoMode mode;
    scene_t *home_screen;
    sfRenderWindow *window;
    level_pick *lpick;
    sfClock *state_clock;
    button_t **all_buttons;
    play_level_t *play_level;
    player_t *player;
    sfTexture *death_effet;
    sfMusic *lobby_music;
    sfSound *death_sound;
    sfSound *lvl_complete;
    settings_t *settings;
    skin_select_t *skin_select;
    pause_t *pause;
    sfSprite *comp_spr;
    sfSound *oof;
    sfSound *coin;
    sfSprite *program_name;
    char *custom_level_name;
    sfColor lum;
    int state;
    int is_transition;
    int next_state;
    int framerate;
    int fps;
} window_t;

static const sfIntRect death_effet[30] = {
    {0, 0, DE_SIZE, DE_SIZE},
    {256, 0, DE_SIZE, DE_SIZE},
    {512, 0, DE_SIZE, DE_SIZE},
    {768, 0, DE_SIZE, DE_SIZE},
    {1024, 0, DE_SIZE, DE_SIZE},
    {1280, 0, DE_SIZE, DE_SIZE},
    {0, 256, DE_SIZE, DE_SIZE},
    {256, 256, DE_SIZE, DE_SIZE},
    {512, 256, DE_SIZE, DE_SIZE},
    {768, 256, DE_SIZE, DE_SIZE},
    {1024, 256, DE_SIZE, DE_SIZE},
    {1280, 256, DE_SIZE, DE_SIZE},
    {0, 512, DE_SIZE, DE_SIZE},
    {256, 512, DE_SIZE, DE_SIZE},
    {512, 512, DE_SIZE, DE_SIZE},
    {768, 512, DE_SIZE, DE_SIZE},
    {1024, 512, DE_SIZE, DE_SIZE},
    {1280, 512, DE_SIZE, DE_SIZE},
    {0, 768, DE_SIZE, DE_SIZE},
    {256, 768, DE_SIZE, DE_SIZE},
    {512, 768, DE_SIZE, DE_SIZE},
    {768, 768, DE_SIZE, DE_SIZE},
    {1024, 768, DE_SIZE, DE_SIZE},
    {1280, 768, DE_SIZE, DE_SIZE},
    {0, 1024, DE_SIZE, DE_SIZE},
    {256, 1024, DE_SIZE, DE_SIZE},
    {512, 1024, DE_SIZE, DE_SIZE},
    {768, 1024, DE_SIZE, DE_SIZE},
    {1024, 1024, DE_SIZE, DE_SIZE},
    {1280, 1024, DE_SIZE, DE_SIZE}
};

static const sfIntRect buttons_rect[8] = {
    {210, 0, 160, 160},
    {0, 0, 210, 210},
    {370, 0, 161, 160},
    {531, 0, 143, 143},
    {674, 0, 124, 124},
    {0, 210, 91, 107},
    {91, 210, 87, 180},
    {178, 210, 87, 180}
};

static const sfIntRect difficulties[6] = {
    {0, 0, 112, 111},
    {112, 0, 112, 111},
    {224, 0, 112, 111},
    {336, 0, 112, 111},
    {448, 0, 112, 111},
    {560, 0, 126, 114}
};

static const sfVideoMode available_modes[] = {
    {800, 600, 32},
    {1024, 800, 32},
    {1920, 1080, 32}
};

static const int available_framerates[] = {
    30, 60, 90, 120, 144
};

static const sfIntRect set_rects[] = {
    {0, 0, 74, 74},
    {74, 0, 74, 74},
    {0, 74, 1375, 208},
    {0, 282, 1375, 208},
    {0, 490, 1375, 208},
    {0, 698, 1375, 208},
    {0, 906, 1375, 208},
    {1375, 74, 1375, 208},
    {1375, 282, 1375, 208},
    {1375, 490, 1375, 208}
};

static const sfIntRect skins_rects[] = {
    {0, 0, 16, 16},
    {16, 0, 16, 16},
    {32, 0, 16, 16},
    {48, 0, 16, 16},
    {0, 16, 16, 16},
    {16, 16, 16, 16},
    {32, 16, 16, 16},
    {48, 16, 16, 16},
    {0, 32, 16, 16},
    {16, 32, 16, 16},
    {32, 32, 16, 16},
    {48, 32, 16, 16},
    {0, 48, 16, 16},
    {16, 48, 16, 16},
    {32, 48, 16, 16},
    {48, 48, 16, 16},
    {0, 64, 16, 16}
};

static const sfIntRect pause_buttons[] = {
    {278, 169, 209, 209},
    {493, 190, 161, 161}
};

void update_all_levels(level_t **levels, int nb);
char *get_file_namee(char *file);
void draw_fps(window_t *w);
void destroy_sound(sfSound *s);
void launch_current_level(window_t *win);
char *random_death_phrase(void);
int manage_intersection(sfFloatRect inter, window_t *win,
sfVector2i ij, int *tab[]);
int check_inter(window_t *win, sfFloatRect b, sfVector2i ij, int **tab);
void add_bonus_to_column(char **column, int can_spawn);
void reset_random(window_t *win);
void append_struct(linked_list_t **blocks);
linked_list_t *get_inf_blocks(int *nb_blocks);
int is_infinite(char const *file);
int usage(void);
int check_spike_collision(block_t **blocks, player_t *p, window_t *win);
void rewrite_file(char const *lvl, char **array);
int nb_lines(char const *file);
int editor_main(sfVideoMode mode, int fullscreen, char *map);
void check_changings(window_t *win);
void update_attempt(window_t *win);
void reset_player_clocks(player_t *p);
void exit_game(window_t *win);
sfVector2f get_sprite_size(sfSprite *s);
void actu_percentage(window_t *win);
void resume(window_t *win);
void pause_release(window_t *win, sfEvent *ev);
void pause_move(window_t *win, sfEvent *ev);
void pause_press(window_t *win, sfEvent *ev);
sfMusic *init_music(char const *file);
sfSprite *draw_home(window_t *win);
void anim_death(window_t *win);
void anim_jump_player(window_t *win);
void anim_player(window_t *win);
void move_lvl_index(int index, window_t *win);
void hover_button(button_t *b, int is_on);
void press_button(button_t *b, int is_press);
void release_button(int index, window_t *win);
int get_is_death(sfFloatRect a, window_t *win);
void draw_hitbox(sfFloatRect s, window_t *win, sfColor c);
int has_land(window_t *win);
void manage_collision(window_t *win);
button_t *init_button(sfTexture *tex, int rect,
sfVector2f pos, char const *text);
button_t **create_home_buttons(void);
void draw_level_buttons(window_t *win);
const sfTexture *get_actu_level_tex(level_pick *lpick);
sfSprite *draw_actu_level(level_pick *lpick, window_t *win);
sfSprite *draw_home(window_t *win);
void switch_color_dir(window_t *win);
void update_color(window_t *win, sfSprite *s);
sfSprite *draw_level(window_t *win);
void draw(window_t *win);
void draw_level_dots(level_pick *lpick, sfVideoMode mode);
void draw_progress_bar(window_t *win);
const sfTexture *get_level_pick_text(window_t *win);
sfSprite *draw_level_pick(window_t *win);
void draw_background(play_level_t *l, player_t *player);
const sfTexture *get_play_texture(play_level_t *l,
player_t *player, window_t *win);
sfSprite *get_play_sprite(play_level_t *l, player_t *player, window_t *win);
int is_file_valid(char *file);
void rescale_home(scene_t *home, sfVideoMode win_size);
scene_t *init_home_screen(sfVideoMode *win_size);
int get_home_button_at(sfVector2f pos, scene_t *home);
void reset_home_buttons(window_t *win, int except);
const sfTexture *get_home_texture(scene_t *home);
int get_difficulty(FILE *f);
int get_progression(FILE *f);
char *get_full_file_name(char *from);
level_t *create_level(char *from, window_t *w, sfTexture *diff_tex);
char **get_all_levels(int *size);
sfSprite *init_difficulty(sfTexture *tex, int diff);
sfText *init_text(char const *lvl_name);
void init_lvl_back(level_t *l);
void init_all_levels(level_pick *lpick, char **all_files,
int size, window_t *w);
int is_list_valid(void);
int nb_levels(FILE *f);
level_pick *create_level_pick(window_t *win);
void init_parralax(play_level_t *p, window_t *win);
void create_column(block_t **first_blocks, int nb_block,
char **tmp_blocks, int i);
block_t **init_first_blocks(linked_list_t **columns);
linked_list_t *get_all_blocks(char *buf, int *i, int nb_more);
play_level_t *init_play_level(level_t *lvl, window_t *win);
void resize_window(window_t *win);
void manage_key_press(window_t *win, sfEvent *ev);
window_t *create_window(char *map);
void home_mouse_move(window_t *win, sfEvent *ev);
void lpick_mouse_move(window_t *win, sfEvent *ev);
void manage_mouse_move(window_t *win, sfEvent *ev);
void reset_player_skin(sfVideoMode mode, player_t *p, window_t *win);
void reset_player(window_t *win);
player_t *init_player(window_t *win);
void scale_player(sfVideoMode mode, player_t *p);
void anim_jump(player_t *p, window_t *win);
void free_play_level(play_level_t *p);
void load_level(window_t *win);
void check_jump(window_t *win);
void manage_key_events(window_t *win, sfEvent *ev);
void poll_events(window_t *win);
int is_level_click(sfVector2f pos, window_t *win);
int get_level_button_at(sfVector2f pos, scene_t *win, window_t *w);
void home_press(window_t *win, sfEvent *ev);
void lpick_press(window_t *win, sfEvent *ev);
void manage_press(window_t *win, sfEvent *ev);
sfText *init_percent_text(float percent, sfVector2f size);
sfRectangleShape *init_filled_bar(float percent, sfVector2f size);
progress_bar_t *init_progress_bar(float percent, sfVector2f size);
void update_progress_bar(
progress_bar_t *p_bar, float percent, sfVector2f size, int is_infinite);
sfSprite *sprite_progress_bar(progress_bar_t *p_bar);
void release_level_pick(window_t *win, sfEvent *ev);
void release_home(window_t *win, sfEvent *ev);
void manage_release(window_t *win, sfEvent *ev);
void move_lpick_buttons(window_t *win);
void scale_buttons(sfVideoMode win_size, button_t **buttons);
void move_settings_close(sfVideoMode win_size, button_t **buttons);
void move_buttons(sfVideoMode win_size, button_t **buttons);
void scale_rtex_lpick(window_t *win);
void scale_level(level_t *l, window_t *w);
void scale_sprite(sfSprite *s, int size_rect, sfVector2u win_size);
void move_sprite(sfSprite *s, sfVector2f pos,
sfVector2u win_size, float offset);
void rotate_blocks(play_level_t *l);
void update_blocks(play_level_t *l);
float float_mod(float a, float mod);
float round_to_90_sup(float rota);
float round_to_up_block(sfVector2f pos, sfVideoMode mode);
void mod_pos_player(player_t *p, sfVideoMode mode);
void update_player_pos(window_t *win);
void start_death(window_t *win);
play_level_t *get_level_from_file(char *file, window_t *win, int is_inf);
int open_map(window_t *win, char *map);
sfSound *init_sound(char const *file);
int first_check(FILE *fi);
check_box *init_check_box(int check, char const *check_tex,
char const *not_check_tex, char const *text);
void draw_check_box(sfRenderTexture *rtex, check_box *c);
sfSprite *init_sprite_from_file(char const *file);
settings_t *init_settings(window_t *win);
sfSprite *get_settings(window_t *win);
void scale_check_box(check_box *c, sfVector2f factors);
void set_box_pos(check_box *c, sfVector2f pos);
void rescale_settings(settings_t *se, window_t *win);
sfSound *init_sound(char const *file);
void set_sprite_size(sfSprite *s, sfVector2f size);
void destroy_musics(window_t *win);
void rescale_settings(settings_t *se, window_t *win);
sfSprite *get_settings_sprite(window_t *se);
void move_settings(settings_t *se, window_t *win);
sfVector2f conv(sfVector2f c, window_t *win);
sfSprite *init_sprite_from_texture(sfTexture *tex,
const sfIntRect *rect, int centerize);
sfSprite *init_sprite_from_file(char const *file);
void manage_settings_hover(sfEvent *ev, window_t *win);
void manage_settings_press(sfEvent *ev, window_t *win);
void manage_settings_release(sfEvent *ev, window_t *win);
void update_all_texts(settings_t *se);
void go_back(settings_t *se, window_t *win);
void update_full_screen(settings_t *se, window_t *win);
void update_vsync(settings_t *se, window_t *win);
void update_res(settings_t *se, window_t *win);
void update_framerate(settings_t *se, window_t *win);
sfFloatRect bounds(sfSprite *s);
int get_set_button_at(settings_t *se, sfEvent *ev);
void sfx_minus(settings_t *se, window_t *win);
void sfx_plus(settings_t *se, window_t *win);
void music_minus(settings_t *se, window_t *win);
void music_plus(settings_t *se, window_t *win);
void reset_set_buttons(settings_t *se);
skin_select_t *init_skin_select(window_t *win);
sfSprite *get_skin_select(window_t *win);
void rescale_select(window_t *win);
void ss_mouse_move(window_t *win, sfEvent *ev);
void ss_mouse_press(window_t *win, sfEvent *ev);
void ss_mouse_release(window_t *win, sfEvent *ev);
void init_background(play_level_t *p, window_t *win);
int first_check(FILE *fi);
void rescale_all(window_t *win);
sfSprite *get_pause_sprite(window_t *win);
pause_t *init_pause(window_t *win);
void scale_pause(pause_t *p, window_t *win);
void pause_game(window_t *win);

#endif
