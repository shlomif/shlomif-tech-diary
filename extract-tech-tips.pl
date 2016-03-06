#!/usr/bin/perl

use strict;
use warnings;

package Shlomif::TechTips::Entry;

use MooX qw/late/;

has 'date' => (is => 'ro');
has 'tags' => (is => 'ro', isa => 'Str');
has 'title' => (is => 'ro', isa => 'Str');
has 'xml' => (is => 'ro');

package main;

use XML::LibXML;
use HTML::Selector::XPath qw();
my @entries;

use Getopt::Long qw/GetOptions/;

my @filenames;

GetOptions(
    'file=s' => \@filenames,
) or die "Wrong options - $!";

sub get_xpath
{
    return HTML::Selector::XPath->new(shift)->to_xpath(root => '.', prefix => 'xhtml');
}

my $div_xpath = get_xpath('div.entry');
my $h2_xpath = get_xpath('h2');

my $DATE_RE = qr/[0-9]{4}-[0-9]{2}-[0-9]{2}/;

foreach my $fn (@filenames)
{
    my $doc = XML::LibXML->load_xml(location => $fn);
    my $xc = XML::LibXML::XPathContext->new($doc);
    $xc->registerNs('xhtml', 'http://www.w3.org/1999/xhtml');
    foreach my $node ( $xc->findnodes($div_xpath) )
    {
        # Extract the date.
        my $date = sub {
            if (my ($title_date) = ($node->getAttribute('title') // '') =~ /\A($DATE_RE):/)
            {
                return $title_date;
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
                if (my ($h2_date) = $h2->textContent =~ /\A($DATE_RE):/)
                {
                    return $h2_date;
                }
                else
                {
                    die "Cannot find date in $node";
                }
            }
        }->();

        push @entries , Shlomif::TechTips::Entry->new({
                date => $date,
                xml => $node,
            });
    }
}

1;

