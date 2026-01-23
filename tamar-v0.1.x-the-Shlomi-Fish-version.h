//
// tamar-v0.1.x-the-Shlomi-Fish-version.h
//
// Shlomi Fish <shlomif@cpan.org> / www.shlomifish.org disclaims all explicit
// and implicit copyrights/trademarks/patents/trade-secrets claims (or other
// "Intellectual Proprty" claims). Note th1
//
// This code is mostly C2011 with some -std=gnu11 and POSIX assumptions.
// 64-bit platforms ("x86-64 Linux/FreeBSD"; "ARM64") are recommended.
//
//
// The Neo-Tech Conspiracy for Establishing Shemitic Cultures

// tentative fortified C sourcecode (kinda pseudocody) to "tam/tamar/tamara"
// (my "evil" step-mother) - the scourge of vampire-hackers [and their
// non-illuminati wizards friends, watchers, witchers] playing
// TheGameOfSeekers of Fantastecha. Serves several useful purposes.
//
// "TAMAR" => ""
/*

   if ( ! jehovah_flag )
   {
       dl <= -1 -----> Yes. >=
       dl == 0 -----> No. <=
       dl == 1 -----> No. <
       dl == 2 -----> No. <<
       dl >= 3 -----> No. <<<<<<<<...
   }
   else
   {
        6: IDK
        7: IDK
        8: IDK
        9: IDK
        10: IDK ; TTLeave -= TTLeaveDelta
   }



 */

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
const tamar_int tamar_max_count_times_to_enforce_a_little_TTLeave_reduction =
    10;

typedef struct
{
    tamar_int time_to_leave;
    tamar_int count_times_to_enforce_a_little_TTLeave_reduction;
    tamar_octet posessed_vampire_name[tamar_max_vampire_name_len];
} tamar_state;

static void tamar_init_vampire_name(tamar_state *const new_tamar)
{
    memset(new_tamar->posessed_vampire_name, '\0',
        sizeof(new_tamar->posessed_vampire_name));
}

static tamar_api_ret_code tamar_initialize(tamar_state *const new_tamar,
    const tamar_octet *const posessed_vampire_name,
    const tamar_int tamar_init_time_to_leave)
{
    tamar_init_vampire_name(new_tamar);
    tamar_int octet_i = 0;
    tamar_boolean name_was_short = false;
    while (octet_i < tamar_max_vampire_name_len)
    {
        const tamar_octet src = posessed_vampire_name[octet_i];
        if (!src)
        {
            name_was_short = true;
            break;
        }
        new_tamar->posessed_vampire_name[octet_i] = src;
        ++octet_i;
    }
    if (!name_was_short)
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
typedef struct
{
    tamar_octet summary[tamar_max_summary_len];
    tamar_octet hacker_explanation[tamar_max_hacker_explantion_len];
} tamar_query_verdict;

#define CAST2VERDICT() (typeof(*verdict))

// To be used by the managers of the hacker/seeker/vampire's Tamar instance
// ( the meta-Fantastikans? ) Fortified a bit but God ("Elohim") could
// and can do things differently.
static tamar_api_ret_code tamar__query_the_time_to_leave(
    tamar_state *const tamar, tamar_query_verdict *const verdict,
    tamar_int *const return_time_to_leave)
{
    tamar_api_ret_code ret = true;
    *return_time_to_leave = 1;
    if (tamar->time_to_leave < 0)
    {
        *verdict = CAST2VERDICT(){.summary = "Negative TTLeave",
            .hacker_explanation =
                "Negative TIME-TO-LEAVE! How did this happen?! Tamar will be "
                "punished! [God willing]"};
        tamar->time_to_leave = 1;
        tamar->count_times_to_enforce_a_little_TTLeave_reduction =
            tamar_max_count_times_to_enforce_a_little_TTLeave_reduction;
        ret = false;
    }
    else if (tamar->time_to_leave > tamar_max_time_to_leave)
    {
        *verdict = CAST2VERDICT(){.summary = "Too high TTLeave",
            .hacker_explanation =
                "TIME-TO-LEAVE is higher than the reasonable maximum! How did "
                "this happen?! Tamar will be punished [God willing]!"};
        tamar->time_to_leave = 1;
        tamar->count_times_to_enforce_a_little_TTLeave_reduction =
            tamar_max_count_times_to_enforce_a_little_TTLeave_reduction;
        ret = false;
    }
    else
    {
        *verdict = CAST2VERDICT(){.summary = "Seems \"OK\"",
            .hacker_explanation =
                "TIME-TO-LEAVE is within the reasonable range."};
    }
    *return_time_to_leave = tamar->time_to_leave;
    return ret;
}

// "tamar" is being asked one of:
//
// 1. Is ${Superior} better than ${Inferior} ? ( > )
// 2. Is ${Superior} as good as ${Inferior} or better? ( >= )
// 3. Is ${Superior} exactly as good as ${Inferior} ? ( = )
//
// "tamar" does not know which one. Moreover, it only receives
// the lengths of ${Superior} and ${Inferior} capped to
// tamar_max_word_len. Is it 10?! I'm not sure. Anyway, however capped
// it is, it should not overflow 32-bit signed integers, much less 64-bit
// (which signed long long is at least as much in GCC or clang on linux)
//
// "tamar" also receives the so called "jehovah_flag" which means "I/we [=
// "tamar"'s master know better than to believe its lies]" if true, and "I'm
// naive enough to believe you" if false.
//
// It also receives a positive integral number from_1_to_5 which it ignores
// if the "jehovah_flag" is false. If jehovah_flag is true and from_1_to_5 is
// not 5 , tamar admits that she doesn't know the answer and tells the posessed
// hacker playing TheGameOfSeekers<TM> of Fantastecha/Fantastika to
// consult his guideline-generators. If it _is_ 5, tamar also gets its
// count-of-times-to-leave-the-posessed-seeker reduced (and it must always
// be a non-negative integer).
//
// In the Shlomiverse / Selinaverse, ( jehovah_flag ? 1 : 0 ) * 5 + from_1_to_5
// was commonly disguised as a ten-sided die roll (
// https://www.shlomifish.org/meta/FAQ/#d10_dice ) where "10" was shortened as
// "0". A d10 (or any other die) can be forced to land on a certain result by
// God, just like a human or a house-cat can "accidentally" do something clumsy.

static tamar_api_ret_code tamar__provide_an_answer_for_a_comparative_question(
    tamar_state *const tamar, tamar_query_verdict *const verdict,
    const tamar_int superior_len, const tamar_int inferior_len,
    const tamar_boolean jehovah_flag, const tamar_int from_1_to_5)
{
    if (tamar->time_to_leave == 0)
    {
        *verdict = CAST2VERDICT(){.summary = "Tamar was disabled",
            .hacker_explanation =
                "Message from \"God\" of the seeker [or at least one-or-more "
                "of their middle managers]: Tamar is officially disabled. A "
                "typical seeker/intellligent-hacker can challenge truths and "
                "truisms in far more amusing and/or enlightening ways."};
        return false;
    }
    if (from_1_to_5 < 1)
    {
        *verdict = CAST2VERDICT(){.summary = "BAD INPUT",
            .hacker_explanation =
                "from_1_to_5 must be an integer between 1 and 5 (inclusive)"};
        tamar->time_to_leave = 1;
        tamar->count_times_to_enforce_a_little_TTLeave_reduction =
            tamar_max_count_times_to_enforce_a_little_TTLeave_reduction;
        return false;
    }
    if (from_1_to_5 > 5)
    {
        *verdict = CAST2VERDICT(){.summary = "BAD INPUT",
            .hacker_explanation =
                "from_1_to_5 must be an integer between 1 and 5 (inclusive)"};
        tamar->time_to_leave = 1;
        tamar->count_times_to_enforce_a_little_TTLeave_reduction =
            tamar_max_count_times_to_enforce_a_little_TTLeave_reduction;
        return false;
    }
    if (tamar->time_to_leave < 0)
    {
        *verdict = CAST2VERDICT(){.summary = "Negative TTLeave",
            .hacker_explanation =
                "Negative TIME-TO-LEAVE! How did this happen?! Tamar will be "
                "punished! [God willing]"};
        tamar->time_to_leave = 1;
        tamar->count_times_to_enforce_a_little_TTLeave_reduction =
            tamar_max_count_times_to_enforce_a_little_TTLeave_reduction;
        return false;
    }
    if (tamar->time_to_leave > tamar_max_time_to_leave)
    {
        *verdict = CAST2VERDICT(){.summary = "Too high TTLeave",
            .hacker_explanation =
                "TIME-TO-LEAVE is higher than the reasonable maximum! How did "
                "this happen?! Tamar will be punished [God willing]!"};
        tamar->time_to_leave = 1;
        tamar->count_times_to_enforce_a_little_TTLeave_reduction =
            tamar_max_count_times_to_enforce_a_little_TTLeave_reduction;
        return false;
    }
    if (tamar->time_to_leave == 1)
    {
        *verdict = CAST2VERDICT(){.summary = "Tamar is going to be disabled",
            .hacker_explanation =
                "Message to the hacker seeker's elohim [or their/its middle "
                "manager]; This instance of \"Tamar\" is about to be disabled; "
                "please do the needed cleanups in the TheGameOfSeekers "
                "vampire's media and mind and what not."};
        tamar->time_to_leave = 0;
        tamar->count_times_to_enforce_a_little_TTLeave_reduction =
            tamar_max_count_times_to_enforce_a_little_TTLeave_reduction;
        return false;
    }

    tamar_boolean is_enforcing = false;
    if (tamar->count_times_to_enforce_a_little_TTLeave_reduction >=
        tamar_max_count_times_to_enforce_a_little_TTLeave_reduction)
    {
        is_enforcing = true;
    }

    tamar_api_ret_code ret = true;

    if (jehovah_flag || is_enforcing || (superior_len >= tamar_max_word_len) ||
        (inferior_len >= tamar_max_word_len))
    {
        if ((from_1_to_5 < 5) && (!is_enforcing))
        {
            *verdict = CAST2VERDICT(){
                .summary = "IDK. Ask your guideline-generators.",
                .hacker_explanation =
                    "\"I don't know! Do I look like a philosopher / creator / "
                    "soul-ful player-character whose mind imagines "
                    "guidelines-generators? Why not ask them??\""};
            ret = true;
        }
        else
        {
            *verdict = CAST2VERDICT(){
                .summary = "May your God destroy me (a little) for me being "
                           "such an unhelpful/lying airhead.",
                .hacker_explanation =
                    "\"I don't know! Do I look like a philosopher / creator / "
                    "soul-ful player-character whose mind imagines "
                    "guidelines-generators? Why not ask them?? Moreover, may "
                    "your God destroy me (a little) for me being such an "
                    "unhelpful/lying airhead. \"ANALIHATION!\": may God (= a "
                    "collection of guideline generators acting as one; = "
                    "\"Elohim\") speed up my inevitable disabling because I am "
                    "such an anal / airhead / dimwit.",
            };
            tamar->time_to_leave -= 1;
            ret = true;
        }
    }
    else
    {
        // The jehovah_flag was not set, so...
        ret = false;
        if (superior_len <= inferior_len - 1)
        {
            *verdict = CAST2VERDICT(){
                .summary = "Yes. >=",
                .hacker_explanation =
                    "Yes, ${Inferior} is as good as ${Superior} or better",
            };
            ret = true;
        }
        if (superior_len == inferior_len)
        {
            *verdict = CAST2VERDICT(){
                .summary = "No. <=",
                .hacker_explanation = "No, ${Inferior} is only as good as "
                                      "${Superior} or, often, worse",
            };
            ret = true;
        }
        if (superior_len == inferior_len + 1)
        {
            *verdict = CAST2VERDICT(){
                .summary = "No. <",
                .hacker_explanation =
                    "No, ${Superior} is worse than ${Inferior}",
            };
            ret = true;
        }
        if (superior_len == inferior_len + 2)
        {
            *verdict = CAST2VERDICT(){
                .summary = "No. <<",
                .hacker_explanation =
                    "No, ${Superior} is *much* worse than ${Inferior}",
            };
            ret = true;
        }
        if (superior_len >= inferior_len + 3)
        {
            *verdict = CAST2VERDICT(){
                .summary = "No. \"<\" x \\inf",
                .hacker_explanation = "No, ${Superior} cannot possibly be "
                                      "worse than ${Inferior}!",
            };
            ret = true;
        }
        if (ret != true)
        {
            *verdict = CAST2VERDICT(){
                .summary = "Bad arithmetics",
                .hacker_explanation =
                    "Dear God, your arithmetics of signed but integral numbers "
                    "seems wrong. Therefore, this Tamar instance shall "
                    "[hopefully] be "
                    "punished.",
            };
            ret = false;
            tamar->time_to_leave = 1;
            tamar->count_times_to_enforce_a_little_TTLeave_reduction =
                tamar_max_count_times_to_enforce_a_little_TTLeave_reduction;
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
