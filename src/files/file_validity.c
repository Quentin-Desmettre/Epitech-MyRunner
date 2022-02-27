/*
** EPITECH PROJECT, 2021
** B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
** File description:
** file_validity.c
*/

#include "runner.h"

static int is_multi_semicolon(char const *line)
{
    for (int i = 0; line[i]; i++) {
        if (line[i] == SEPARATOR_CHAR && line[i + 1] == SEPARATOR_CHAR)
            return 1;
    }
    return 0;
}

static int is_y_valid(char const *line)
{
    for (int i = 2; line[i]; i++) {
        if (!(line[i + 1]) && line[i] == '\n')
            break;
        if (!contain("0123456789", line[i]))
            return 0;
    }
    if (my_getnbr(line + 2) > 11 || my_getnbr(line + 2) < 0)
        return 0;
    return 1;
}

static int is_element_valid(char const *el)
{
    if (!el || el[0] == '\n')
        return 0;
    if (my_strlen(el) < 3)
        return 0;
    if (el[0] < '2' || el[0] > 'J')
        return 0;
    if (el[1] != ':')
        return 0;
    if (!is_y_valid(el))
        return 0;
    return 1;
}

static int is_line_valid(char *line)
{
    int rvalue = 1;
    char **blocks = my_str_to_word_array(line, SEPARATOR_STR);

    if (!blocks || !(blocks[0]))
        rvalue = 0;
    if (!(blocks[1]) && blocks[0][0] == '\n')
        rvalue = 0;
    if (is_multi_semicolon(line))
        rvalue = 0;
    for (int i = 0; blocks[i] && rvalue; i++)
        rvalue = is_element_valid(blocks[i]);
    for (int i = 0; blocks[i]; i++)
        free(blocks[i]);
    free(blocks);
    if (!rvalue)
        free(line);
    return rvalue;
}

int is_file_valid(char *file)
{
    char *f_name = get_full_file_name(file);
    FILE *fi = fopen(f_name, "r");
    char *buf = 0;
    size_t tmp;
    int rval = 1;
    int i = 0;

    free(f_name);
    if (!fi || !first_check(fi))
        rval = 0;
    while (rval && getline(&buf, &tmp, fi) > 0) {
        if (!is_line_valid(buf))
            rval = 0;
        buf = 0;
        i++;
    }
    if (fi)
        fclose(fi);
    return i <= 2 ? 0 : rval;
}
