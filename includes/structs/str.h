//
// Created by sergey on 24.01.2021.
//

#ifndef PHILLYSHELL_STR_H
#define PHILLYSHELL_STR_H

#include "retcodes.h"
#include <stdlib.h>


typedef struct s_string String;

t_ret string_new(String **s, size_t len, size_t cap);
void string_free(String *s);
t_ret string_grow(String *s, size_t cap);
t_ret string_insert(String *s, size_t idx, char c);
t_ret string_erase_from_idx(String *s, size_t idx);
t_ret string_append(String *s, char c);
char string_get(String *s, size_t idx);
String *string_slice(String *s, size_t start, size_t end);
size_t string_len(String *s);
size_t string_cap(String *s);
char *string_to_c_str(String *s);
t_ret string_copy(String **dst, String *src);

#endif//PHILLYSHELL_STR_H
