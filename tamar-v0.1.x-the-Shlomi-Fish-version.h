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
const tamar_int tamar_max_time_to_leave = (tamar_int)
typedef struct {
    tamar_int time_to_leave;
    tamar_int count_times_to_enforce_a_little_destruction;
    tamar_octet posessed_vampire_name[tamar_max_vampire_name_len];
} tamar_state;


