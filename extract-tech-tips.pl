#!/usr/bin/perl

use strict;
use warnings;

package Shlomif::TechTips::Entry;

use MooX qw/late/;
use DateTime ();

has 'date' => (is => 'ro', isa => 'DateTime', required => 1,);
has 'tags' => (is => 'ro', isa => 'HashRef', required => 1,);
has 'title' => (is => 'ro', isa => 'Str', required => 1,);
has 'xml' => (is => 'ro', required => 1,);

package main;

use XML::LibXML;
use HTML::Selector::XPath qw();
my @entries;

use Getopt::Long qw/GetOptions/;
use DateTime::Format::Strptime qw();

my @filenames;

GetOptions(
    'file=s' => \@filenames,
) or die "Wrong options - $!";

sub get_xpath
{
    return HTML::Selector::XPath->new(shift)->to_xpath(root => './', prefix => 'xhtml');
}

my $div_xpath = get_xpath('div.entry');
my $h2_xpath = get_xpath('h2');

my $DATE_RE = qr/[0-9]{4}-[0-9]{2}-[0-9]{2}/;

my $strp = DateTime::Format::Strptime->new(
    pattern   => '%Y-%m-%d',
    locale    => 'en_GB',
    time_zone => 'Asia/Jerusalem',
);

foreach my $fn (@filenames)
{
    my $doc = XML::LibXML->load_xml(location => $fn);
    my $xc = XML::LibXML::XPathContext->new($doc);
    $xc->registerNs('xhtml', 'http://www.w3.org/1999/xhtml');
    NODES:
    foreach my $node ( $xc->findnodes($div_xpath) )
    {
        # Extract the date.
        my ($title_s, $date_s) = sub {
            my $title = ($node->getAttribute('title') // '');
            if ($title =~ s/\A($DATE_RE):\s*//)
            {
                return ($title, $1);
            }
            else
            {
                my $xc = XML::LibXML::XPathContext->new($node);
                $xc->registerNs('xhtml', 'http://www.w3.org/1999/xhtml');
                my @h2_tags = $xc->findnodes($h2_xpath);
                if (!@h2_tags)
                {
                    die "Cannot find date in $node";
                }
                my $h2 = shift(@h2_tags);
                $title = $h2->textContent;
                if ($title =~ s/\A($DATE_RE):\s*//)
                {
                    return ($title, $1);
                }
                else
                {
                    die "Cannot find date in $node";
                }
            }
        }->();

        if (!defined($title_s) or !defined($date_s))
        {
            die "Flutterflutter";
        }

        my $date = $strp->parse_datetime($date_s);

        my @tags = map { my $text = $_->data; $text =~ s/\A\s*Tags:\s*// ? ($text) : () } $node->findnodes('./comment()');

        if (@tags > 1)
        {
            die "Too many tag comments at $node.";
        }
        elsif (!@tags)
        {
            next NODES;
        }

        my $labels = $tags[0];

        my %l = map { $_ => 1 } map { s/\A\s+//r =~ s/\s+\z//r; } split(/\s*,\s*/, $labels =~ s/\s+/ /gr);
        if (not (exists ($l{'tech tip'}) or (
                    exists($l{'tech'}) and exists($l{'tip'})
                )
            ))
        {
            next NODES;
        }

        print "Foo\n";
        push @entries , Shlomif::TechTips::Entry->new({
                date => $date,
                xml => $node,
                tags => (\%l),
                title => $title_s,
            });
    }
}

1;

