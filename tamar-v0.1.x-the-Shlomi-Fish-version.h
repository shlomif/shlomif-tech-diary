//
// tamar-v0.1.x-the-Shlomi-Fish-version.h
//
// Shlomi Fish <shlomif@cpan.org> disclaims all explicit and implicit
// copyrights/trademarks/patents/trade-secrets claims (or other
// "Intellectual Proprty" claims)
//

#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef signed long long tamar_int;
typedef bool tamar_boolean;
typedef char tamar_octet;
typedef tamar_boolean tamar_api_ret_code;
const tamar_int tamar_max_vampire_name_len = (tamar_int)(24LL * 1024LL);
const tamar_int tamar_max_time_to_leave = (tamar_int)(10 * 1000 * 1000);
typedef struct {
    tamar_int time_to_leave;
    tamar_int count_times_to_enforce_a_little_destruction;
    tamar_octet posessed_vampire_name[tamar_max_vampire_name_len];
} tamar_state;


static tamar_api_ret_code tamar_initialize(tamar_state * const new_tamar, const tamar_octet * const posessed_vampire_name, const tamar_int tamar_init_time_to_leave)
{
    memset(new_tamar->posessed_vampire_name, '\0', sizeof(new_tamar->posessed_vampire_name));
    tamar_int octet_i = 0;
    tamar_boolean name_was_short = false;
    while (octet_i < tamar_max_vampire_name_len)
    {
        const tamar_octet src = posessed_vampire_name[octet_i];
        if (! src)
        {
            name_was_short = true;
            break;
        }
        new_tamar->posessed_vampire_name[octet_i] = src;
        ++octet_i;
    }
    if (! name_was_short)
    {
        return false;
    }
    new_tamar->count_times_to_enforce_a_little_destruction = 1;
    if (tamar_init_time_to_leave > tamar_max_time_to_leave)
    {
        return false;
    }
    if (tamar_init_time_to_leave <= 0)
    {
        return false;
    }
    new_tamar->time_to_leave = tamar_init_time_to_leave;
    return true;
}
