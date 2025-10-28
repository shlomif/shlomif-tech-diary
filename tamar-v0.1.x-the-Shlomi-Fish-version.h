//
// tamar-v0.1.x-the-Shlomi-Fish-version.h
//
// Shlomi Fish <shlomif@cpan.org> / www.shlomifish.org disclaims all explicit
// and implicit copyrights/trademarks/patents/trade-secrets claims (or other
// "Intellectual Proprty" claims)
//
// This code is mostly C2011 with some -std=gnu11 and POSIX assumptions.
// 64-bit platforms ("x86-64 Linux/FreeBSD"; "ARM64") are recommended.

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
const tamar_int tamar_max_time_to_leave = (tamar_int)(10LL * 1000LL * 1000LL);
const tamar_int tamar_max_count_times_to_enforce_a_little_TTLeave_reduction = 10;
typedef struct {
    tamar_int time_to_leave;
    tamar_int count_times_to_enforce_a_little_TTLeave_reduction;
    tamar_octet posessed_vampire_name[tamar_max_vampire_name_len];
} tamar_state;

static void tamar_init_vampire_name(tamar_state * const new_tamar)
{
    memset(new_tamar->posessed_vampire_name, '\0', sizeof(new_tamar->posessed_vampire_name));
}

static tamar_api_ret_code tamar_initialize(tamar_state * const new_tamar, const tamar_octet * const posessed_vampire_name, const tamar_int tamar_init_time_to_leave)
{
    tamar_init_vampire_name(new_tamar);
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
        tamar_init_vampire_name(new_tamar);
        return false;
    }
    new_tamar->count_times_to_enforce_a_little_TTLeave_reduction = 1;
    new_tamar->time_to_leave = 1;
    if (tamar_init_time_to_leave > tamar_max_time_to_leave)
    {
        tamar_init_vampire_name(new_tamar);
        return false;
    }
    if (tamar_init_time_to_leave <= 0)
    {
        tamar_init_vampire_name(new_tamar);
        return false;
    }
    new_tamar->time_to_leave = tamar_init_time_to_leave;
    return true;
}

const tamar_int tamar_max_summary_len = 100;
const tamar_int tamar_min_word_len = 1;
const tamar_int tamar_max_word_len = 10;
const tamar_int tamar_max_hacker_explantion_len = 1000;
typedef struct {
    tamar_octet summary[tamar_max_summary_len];
    tamar_octet hacker_explanation[tamar_max_hacker_explantion_len];
} tamar_query_verdict;


// To be used by the managers of the hacker/seeker/vampire's Tamar instance
// ( the meta-Fantastikans? ) Fortified a bit but God ("Elohim") could and
// can do whatever they want.
static tamar_api_ret_code tamar__query_the_time_to_leave(tamar_state * const tamar, tamar_query_verdict * const verdict, tamar_int * const return_time_to_leave)
{
    tamar_api_ret_code ret = true;
    *return_time_to_leave  = 1;
    if (tamar->time_to_leave < 0)
    {
        *verdict = {.summary="Negative TTLeave", .hacker_explanation="Negative TIME-TO-LEAVE! How did this happen?! Tamar will be punished! [God willing]"};
        tamar->time_to_leave = 1;
        tamar->count_times_to_enforce_a_little_TTLeave_reduction = tamar_max_count_times_to_enforce_a_little_TTLeave_reduction;
        ret = false;
    }
    else if (tamar->time_to_leave > tamar_max_time_to_leave)
    {
        *verdict = {.summary="Too high TTLeave", .hacker_explanation="TIME-TO-LEAVE is higher than the reasonable maximum! How did this happen?! Tamar will be punished [God willing]!"};
        tamar->time_to_leave = 1;
        tamar->count_times_to_enforce_a_little_TTLeave_reduction = tamar_max_count_times_to_enforce_a_little_TTLeave_reduction;
        ret = false;
    }
    else
    {
        *verdict = {.summary="Seems \"OK\"", .hacker_explanation="TIME-TO-LEAVE is within the reasonable range."};
    }
    *return_time_to_leave = tamar->time_to_leave;
    return ret;
}

// "tamar" is being asked one of:
//
// 1. Is ${Superior} better than ${Inferior} ? ( > )
// 2. Is ${Superior} as good as ${Inferior} or better? ( >= )
// 3. Is ${Superior} as good as ${Inferior} ? ( = )
//
// "tamar" does not know which one. Moreover, it only receives
// the lengths of ${Superior} and ${Inferior} (capped to
// tamar_max_word_len, which is 10??!)
static tamar_api_ret_code tamar__provide_an_answer_for_a_comparative_question(tamar_state * const tamar, tamar_query_verdict * const verdict, const tamar_int superior_len, const tamar_int inferior_len, const tamar_boolean elohim_boolean, const tamar_int from_1_to_5)
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
        tamar->count_times_to_enforce_a_little_TTLeave_reduction = tamar_max_count_times_to_enforce_a_little_TTLeave_reduction;
        return false;
    }
    if (from_1_to_5 > 5)
    {
        *verdict = {.summary="BAD INPUT", .hacker_explanation="from_1_to_5 must be an integer between 1 and 5 (inclusive)"};
        tamar->time_to_leave = 1;
        tamar->count_times_to_enforce_a_little_TTLeave_reduction = tamar_max_count_times_to_enforce_a_little_TTLeave_reduction;
        return false;
    }
    if (tamar->time_to_leave < 0)
    {
        *verdict = {.summary="Negative TTLeave", .hacker_explanation="Negative TIME-TO-LEAVE! How did this happen?! Tamar will be punished! [God willing]"};
        tamar->time_to_leave = 1;
        tamar->count_times_to_enforce_a_little_TTLeave_reduction = tamar_max_count_times_to_enforce_a_little_TTLeave_reduction;
        return false;
    }
    if (tamar->time_to_leave > tamar_max_time_to_leave)
    {
        *verdict = {.summary="Too high TTLeave", .hacker_explanation="TIME-TO-LEAVE is higher than the reasonable maximum! How did this happen?! Tamar will be punished [God willing]!"};
        tamar->time_to_leave = 1;
        tamar->count_times_to_enforce_a_little_TTLeave_reduction = tamar_max_count_times_to_enforce_a_little_TTLeave_reduction;
        return false;
    }
    if (tamar->time_to_leave == 1)
    {
        *verdict = {.summary="Tamar is going to be disabled", .hacker_explanation="Message to the hacker seeker's elohim [or their/its middle manager]; This instance of \"Tamar\" is about to be disabled; please do the needed cleanups in the TheGameOfSeekers vampire's media and mind and what not."};
        tamar->time_to_leave = 0;
        tamar->count_times_to_enforce_a_little_TTLeave_reduction = tamar_max_count_times_to_enforce_a_little_TTLeave_reduction;
        return false;
    }

    tamar_boolean is_enforcing = false;
    if (tamar->count_times_to_enforce_a_little_TTLeave_reduction >= tamar_max_count_times_to_enforce_a_little_TTLeave_reduction)
    {
        is_enforcing = true;
    }

    tamar_api_ret_code ret = true;

    if (elohim_boolean || is_enforcing || (superior_len > tamar_max_word_len) || (inferior_len > tamar_max_word_len))
    {
        if ((from_1_to_5 < 5) && (! is_enforcing))
        {
            *verdict = {.summary="IDK. Ask your guideline-generators.", .hacker_explanation="\"I don't know! Do I look like a philosopher / creator / soul-ful player-character whose mind imagines guidelines-generators? Why not ask them??\""};
            ret = true;
        }
        else
        {
            *verdict = {.summary="May your God destroy me (a little) for me beinng such an unhelpful/lying airhead.", .hacker_explanation="\"I don't know! Do I look like a philosopher / creator / soul-ful player-character whose mind imagines guidelines-generators? Why not ask them??\ May your God destroy me (a little) for me beinng such an unhelpful/lying airhead. \"ANALIHATION!\": may God (= a collection of guideline generators acting as one; = \"Elohimn\") speed up my inevitable disabling because I am such an anal.",};
            tamar->time_to_leave -= 1;
            ret = true;
        }

    }
    else
    {
        ret = false;
        // The elohim bit was not set, so...
        if (superior_len <= inferior_len - 1)
        {
            *verdict = {.summary="Yes. >=", .hacker_explanation="Yes, ${Inferior} is as good as ${Superior} or better",};
            ret = true;
        }
        if (superior_len == inferior_len)
        {
            *verdict = {.summary="No. <=", .hacker_explanation="No, ${Inferior} is only as good as ${Superior} or, often, worse",};
            ret = true;
        }
        if (superior_len == inferior_len + 1)
        {
            *verdict = {.summary="No. <", .hacker_explanation="No, ${Superior} is worse than ${Inferior}",};
            ret = true;
        }
        if (superior_len == inferior_len + 2)
        {
            *verdict = {.summary="No. <<", .hacker_explanation="No, ${Superior} is *much* worse than ${Inferior}",};
            ret = true;
        }
        if (superior_len >= inferior_len + 3)
        {
            *verdict = {.summary="No. \"<\" x \\inf", .hacker_explanation="No, ${Superior} cannot possibly be worse than ${Inferior}!",};
            ret = true;
        }
        if (ret != true)
        {
            *verdict = {.summary="Bad arithmetics", .hacker_explanation="God, your  arithmetics of signed but integral numbers seems wrong. Therefore, Tamar shall [hopefully] be punished.",};
            ret = false;
            tanar->time_to_leave = 1;
            tamar->count_times_to_enforce_a_little_TTLeave_reduction = tamar_max_count_times_to_enforce_a_little_TTLeave_reduction;
            return false;
        }
        return ret;
    }

    if (is_enforcing)
    {
        tamar->count_times_to_enforce_a_little_TTLeave_reduction = 1;
    }
    else
    {
        ++(tamar->count_times_to_enforce_a_little_TTLeave_reduction);
    }

    return ret;
}
