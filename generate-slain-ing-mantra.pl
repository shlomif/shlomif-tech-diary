#! /usr/bin/env perl
#
# Short description for generate-slain-ing-mantra.pl
#
# Version 0.0.1
# Copyright (C) 2023 Shlomi Fish < https://www.shlomifish.org/ >
#
# Licensed under the terms of the MIT license.

use strict;
use warnings;
use 5.014;
use autodie;
use utf8;

use Carp                                   qw/ confess /;
use Getopt::Long                           qw/ GetOptions /;
use Path::Tiny                             qw/ cwd path tempdir tempfile /;
use Docker::CLI::Wrapper::Container v0.0.4 ();

sub _text_to_markup
{
    my ($TEXT) = @_;
    my @lines  = split /[\n\r]+/ms, $TEXT;
    my $out    = "";
    foreach my $line ( grep { /\S/ and ( not /\A#/ ) } @lines )
    {
        $out .= "<para>\n$line\n</para>\n\n";
    }

    return $out;
}

sub run
{
    my $output_fn;

    my $obj = Docker::CLI::Wrapper::Container->new(
        { container => "rinutils--deb--test-build", sys => "debian:sid", } );

    if (0)
    {

        GetOptions( "output|o=s" => \$output_fn, )
            or die "errror in cmdline args: $!";

        if ( !defined($output_fn) )
        {
            die "Output filename not specified! Use the -o|--output flag!";
        }
    }

    #    $obj->do_system( { cmd => [ "git", "clone", "-b", $BRANCH, $URL, ] } );

    my $text = <<"EOF";
<section xml:id="mantra1">

<info>
<title>mantra</title>
</info>

<orderedlist>
EOF

    my @lines1 = ( "Now fuck off!", "Fuck off, now!", "Do, suck, ass!™" );
    my $idx    = 0;
    foreach my $fairy_type ( "fucker", "hacker" )
    {
        foreach my $changing_line (@lines1)
        {
            $text .= "\n<listitem>\n\n";
            my $OUT = _text_to_markup(<<"EOF");
Die, $fairy_type, die.
Yeah, Zine,
Hallelujah.
$changing_line

# Suck, Cock,
# Dick, Rock, Hack.
EOF

            $text .= $OUT;
            $text .= "</listitem>\n";
        }
        continue
        {
            ++$idx;
        }
    }
    $text .= <<"EOF";

</orderedlist>
</section>
EOF

    if (0)
    {
        print $text, "\n";
    }
    my $fh       = path("multiverse-cosmology-v0.4.x.docbook5.xml");
    my $contents = $fh->slurp_utf8();
    $contents =~ s%\Q<section xml:id="mantra1">\E.*?\Q</section>\E\n%$text%ms
        or die "cannot subtitute mantra1 text";
    $fh->spew_utf8($contents);
    exit(0);
}

run();

1;

__END__

=encoding UTF-8

=head1 NAME

=head1 VERSION

=head1 REJECTS

sack, fuck.

Die, fucker, die.
Yeah, zine.
suck, dick.
Cool, java, hack.

Die, fucker, die.
Yeah, zine.
suck, dick.
Armageddon us.

Die, fucker, die.
Yeah, Zine,
Suck, Dick,
Cock, Puke, Hack.

Die, fucker, die.
Yeah, Zine,
Suck, Dick,
Cock, Fuck, Hack.

=head1 COPYRIGHT AND LICENSE

This software is Copyright (c) 2007 by Shlomi Fish.

This is free software, licensed under:

  The MIT (X11) License

=cut
