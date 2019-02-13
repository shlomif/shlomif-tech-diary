#!/usr/bin/perl

use strict;
use warnings;

use Markdent::Simple::Fragment ();
use Path::Tiny qw/ path /;
use Text::WrapAsUtf8 qw/ print_utf8 /;

print_utf8(
    <<"EOF",
<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE
    html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
    "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en-US">
<head>
<title>Static Site Gens</title>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
</head>
<body>
EOF
    Markdent::Simple::Fragment->new->markdown_to_html(
        markdown => path( shift @ARGV )->slurp_utf8,
        dialects => [qw/ GitHub /],
    ),
    <<"EOF",
</body>
</html>
EOF
);
