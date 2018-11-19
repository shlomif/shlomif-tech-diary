#!/usr/bin/perl

use strict;
use warnings;
use utf8;
use autodie;

package Shlomif::TechTips::Entry;

use MooX qw/late/;
use DateTime ();

has 'date'  => ( is => 'ro', isa => 'DateTime', required => 1, );
has 'tags'  => ( is => 'ro', isa => 'HashRef',  required => 1, );
has 'title' => ( is => 'ro', isa => 'Str',      required => 1, );
has 'xml' => ( is => 'ro', required => 1, );

package main;

use XML::LibXML;
use HTML::Selector::XPath qw();
my @entries;

use Getopt::Long qw/GetOptions/;
use DateTime::Format::Strptime qw();
use Path::Tiny qw/path/;

my @filenames;
my $output_fn;
my $xhtml_wrap = 0;

GetOptions(
    'file=s'     => \@filenames,
    'output|o=s' => \$output_fn,
    'wrap!'      => \$xhtml_wrap,
) or die "Wrong options - $!";

if ( !defined($output_fn) )
{
    die "Output filename is not specified.";
}

sub get_xpath
{
    return HTML::Selector::XPath->new(shift)
        ->to_xpath( root => './', prefix => 'xhtml' );
}

my $div_xpath = get_xpath('div.entry');
my $h2_xpath  = get_xpath('h2');

my $DATE_RE = qr/[0-9]{4}-[0-9]{2}-[0-9]{2}/;

my $strp = DateTime::Format::Strptime->new(
    pattern   => '%Y-%m-%d',
    locale    => 'en_GB',
    time_zone => 'Asia/Jerusalem',
);

foreach my $fn (@filenames)
{
    my $doc = XML::LibXML->load_xml( location => $fn );
    my $xc  = XML::LibXML::XPathContext->new($doc);
    $xc->registerNs( 'xhtml', 'http://www.w3.org/1999/xhtml' );
NODES:
    foreach my $node ( $xc->findnodes($div_xpath) )
    {
        # Extract the date.
        my ( $title_type, $title_s, $date_s ) = sub {
            my $title = ( $node->getAttribute('title') // '' );
            if ( $title =~ s/\A($DATE_RE):\s*// )
            {
                return ( 'title', $title, $1 );
            }
            else
            {
                my $xc = XML::LibXML::XPathContext->new($node);
                $xc->registerNs( 'xhtml', 'http://www.w3.org/1999/xhtml' );
                my @h2_tags = $xc->findnodes($h2_xpath);
                if ( !@h2_tags )
                {
                    die "Cannot find date in $node";
                }
                my $h2 = shift(@h2_tags);
                $title = $h2->textContent;
                if ( $title =~ s/\A($DATE_RE):\s*// )
                {
                    return ( 'h2', $title, $1 );
                }
                else
                {
                    die "Cannot find date in $node";
                }
            }
            }
            ->();

        if ( !defined($title_s) or !defined($date_s) )
        {
            die "undefined stuffs";
        }

        my $date = $strp->parse_datetime($date_s);

        my @tags = map {
            my $text = $_->data;
            $text =~ s/\A\s*Tags:\s*// ? ($text) : ()
        } $node->findnodes('./comment()');

        if ( @tags > 1 )
        {
            die "Too many tag comments at $node.";
        }
        elsif ( !@tags )
        {
            next NODES;
        }

        my $labels = $tags[0];

        my %l =
            map { $_ => 1 }
            map { s/\A\s+//r =~ s/\s+\z//r; }
            split( /\s*,\s*/, $labels =~ s/\s+/ /gr );
        if (
            not( exists( $l{'tech tip'} )
                or ( exists( $l{'tech'} ) and exists( $l{'tip'} ) ) )
            )
        {
            next NODES;
        }

        if ( $title_type eq 'title' )
        {
            die "Node contains title='' insteaf of <h2>!"
                . $node->toString() . "!";
        }

        push @entries,
            Shlomif::TechTips::Entry->new(
            {
                date  => $date,
                xml   => $node,
                tags  => ( \%l ),
                title => $title_s,
            }
            );
    }
}

my $buffer = '';

if ($xhtml_wrap)
{
    $buffer .= <<'EOF';
<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE
    html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
    "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en-US">
<head>
<title>Shlomi Fish’s Collection of Tech Tips</title>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
</head>
<body>
EOF
}

my $XSI_XMLNS = q# xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"#;
foreach my $entry ( reverse sort { $a->date <=> $b->date } @entries )
{
    $buffer .= ( $entry->xml->toString =~ s#\Q$XSI_XMLNS\E([ >])#$1#gr );
}

if ($xhtml_wrap)
{
    $buffer .= <<'EOF';
</body>
</html>
EOF
}

path($output_fn)->spew_utf8($buffer);

1;

=head1 COPYRIGHT & LICENSE

Copyright 2016 by Shlomi Fish

This program is distributed under the MIT (X11) License:
L<http://www.opensource.org/licenses/mit-license.php>

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

=cut
