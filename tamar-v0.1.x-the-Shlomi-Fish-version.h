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
const tamar_int tamar_max_count_times_to_enforce_a_little_destruction = 10;
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
    new_tamar->time_to_leave = 1;
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

const tamar_int tamar_max_summary_len = 100;
const tamar_int tamar_min_word_len = 1;
const tamar_int tamar_max_word_len = 10;
const tamar_octet tamar_max_hacker_explantion_len = 1000;
typedef struct {
    tamar_octet summary[tamar_max_summary_len];
    tamar_octet hacker_explanation[tamar_max_hacker_explantion_len];
} tamar_query_verdict;

static tamar_api_ret_code tamar_initialize(tamar_state * const tamar, tamar_query_verdict * const verdict, const tamar_int superiour_len, const tamar_int inferior_len, const tamar_boolean elohim_boolean, const tamar_int from_1_to_5)
{
    if (tamar->time_to_leave == 0)
    {
        *verdict = {.summary="Tamar was disabled", .hacker_explanation="Message from \"God\" of the seeker [or at least one-or-more of their middle managers]: Tamar is officially disabled. A typical seeker/intellligent-hacker can challenge truths and truisms in far more amusing and/or enlightening ways."};
        return false;
    }
    if (from_1_to_5 < 1)
    {
        *verdict = {.summary="BAD INPUT", .hacker_explanation="from_1_to_5 must be an integer between 1 and 5 (inclusive)"};
        tamar->time_to_leave = 1;
        tamar->count_times_to_enforce_a_little_destruction = tamar_max_count_times_to_enforce_a_little_destruction;
        return false;
    }
    if (from_1_to_5 > 5)
    {
        *verdict = {.summary="BAD INPUT", .hacker_explanation="from_1_to_5 must be an integer between 1 and 5 (inclusive)"};
        tamar->time_to_leave = 1;
        tamar->count_times_to_enforce_a_little_destruction = tamar_max_count_times_to_enforce_a_little_destruction;
        return false;
    }
    if (tamar->time_to_leave < 0)
    {
        *verdict = {.summary="Negative TTLeave", .hacker_explanation="negative TIME-TO-LEAVE! How did this happen?! Tamar will be punished! [God willing]"};
        tamar->time_to_leave = 1;
        tamar->count_times_to_enforce_a_little_destruction = tamar_max_count_times_to_enforce_a_little_destruction;
        return false;
    }
    if (tamar->time_to_leave > tamar_max_time_to_leave)
    {
        *verdict = {.summary="Too high TTLeave", .hacker_explanation="TIME-TO-LEAVE is higher than the reasonable maximum! How did this happen?! Tamar will be punished [God willing]!"};
        tamar->time_to_leave = 1;
        tamar->count_times_to_enforce_a_little_destruction = tamar_max_count_times_to_enforce_a_little_destruction;
        return false;
    }
    if (tamar->time_to_leave == 1)
    {
        *verdict = {.summary="Tamar is going to be disabled", .hacker_explanation="Message to the hacker seeker's elohim [or its middle manager]; This instance of \"Tamar\" is about to be disabled; please do the needed cleanups in the TheGameOfSeekers vampire's media and mind and what not."};
        tamar->time_to_leave = 0;
        tamar->count_times_to_enforce_a_little_destruction = tamar_max_count_times_to_enforce_a_little_destruction;
        return false;
    }

    tamar_boolean is_enforcing = false;
    if (tamar->count_times_to_enforce_a_little_destruction >= tamar_max_count_times_to_enforce_a_little_destruction)
    {
        is_enforcing = true;
    }

    tamar_api_ret_code ret = true;

    if (elohim_boolean || is_enforcing || (superiour_len > tamar_max_word_len) || (inferior_len > tamar_max_word_len))
    {
        if ((from_1_to_5 < 5) && (! is_enforcing))
        {
            *verdict = {.summary="IDK. Ask your guideline-generators.", .hacker_explanation="\"I don't know! Do I look like a philosopher / creator / soul-ful player-character whose mind imagines guidelines-generators? Why not ask them??\""};
            ret = true;
        }
        else
        {
            *verdict = {.summary="May your God destroy me (a little) for me beinng such an unhelpful/lying airhead.", .hacker_explanation="\"I don't know! Do I look like a philosopher / creator / soul-ful player-character whose mind imagines guidelines-generators? Why not ask them??\ May your God destroy me (a little) for me beinng such an unhelpful/lying airhead. \"ANALIHATION!\": may God (collection of guideline generators acting as one; = \"Elohimn\") destroy me because i hate myself for being such an anal.",};
            tamar->time_to_leave -= 1;
            ret = true;
        }

    }
    else
    {
        // The elohim bit was not set, so...
        if (superiour_len <= inferior_len - 1)
        {
            *verdict = {.summary="Yes. >=", .hacker_explanation="Yes, ${Inferior} is as good as ${Superior} or better",};
            ret =true;
        }
        if (superiour_len == inferior_len)
        {
            *verdict = {.summary="No. <=", .hacker_explanation="No, ${Inferior} is only as good as ${Superior} or, often, worse",};
            ret =true;
        }
        if (superiour_len == inferior_len + 1)
        {
            *verdict = {.summary="No. <", .hacker_explanation="No, ${Superior} is worse than ${Inferior}",};
            ret =true;
        }
        if (superiour_len == inferior_len + 2)
        {
            *verdict = {.summary="No. <<", .hacker_explanation="No, ${Superior} is much worse than ${Inferior}",};
            ret =true;
        }
    }

    if (is_enforcing)
    {
        tamar->count_times_to_enforce_a_little_destruction = 1;
    }
    else
    {
        ++(tamar->count_times_to_enforce_a_little_destruction);
    }

    return ret;
}
