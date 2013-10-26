#!/usr/bin/perl

use strict;
use warnings;

use IO::All;

my $text = io("-")->slurp();

$text =~ s{<tr class="(saying|me_is)">\s*<td class="who">([^<]+)<\/td>\s*<td class="text">([^<]+)<\/td\>\s*<\/tr>}
[
    my ($class, $sayer, $what) = ($1, $2, $3);
    ($class eq "saying") ? "<li><b>${sayer}:</b> $what</li>\n" 
        : "<li><i>$sayer $what</i></li>"
]egms;

print $text;
