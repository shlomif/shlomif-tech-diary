#!/usr/bin/env perl

use strict;
use warnings;

use Test::HTML::Tidy::Recursive;

Test::HTML::Tidy::Recursive->new({
        targets => ['./temp'],
        filename_filter => sub {
            my $fn = shift;
            return 1;
        },
    })->run;
