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

use Carp                                   qw/ confess /;
use Getopt::Long                           qw/ GetOptions /;
use Path::Tiny                             qw/ cwd path tempdir tempfile /;
use Docker::CLI::Wrapper::Container v0.0.4 ();

sub run
{
    my $output_fn;

    my $obj = Docker::CLI::Wrapper::Container->new(
        { container => "rinutils--deb--test-build", sys => "debian:sid", } );

    GetOptions( "output|o=s" => \$output_fn, )
        or die "errror in cmdline args: $!";

    if ( !defined($output_fn) )
    {
        die "Output filename not specified! Use the -o|--output flag!";
    }

    #    $obj->do_system( { cmd => [ "git", "clone", "-b", $BRANCH, $URL, ] } );

    my $text = <<"EOF";
<section xml:id="mantra13">

<info>
<title>mantra</title>
</info>

<orderedlist>
EOF

    for ( my $idx = 0 ; $idx < 10 ; $idx++ )
    {
        $text .= "\n<listitem>\n\n";
        my @lines = split /[\n\r]+/ms, <<"EOF";
Die, fucker, die.
Yeah, Zine,
Suck, Dick,
Cock, Puke, Hack.
EOF

        foreach my $line (@lines)
        {
            $text .= "<para>\n$line\n</para>\n\n";
        }
        $text .= "</listitem>\n";
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
    $contents =~ s%\Q<section xml:id="mantra13">\E.*?\Q</section>\E\n%$text%ms
        or die "cannot subtitute mantra13 text";
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

=head1 COPYRIGHT AND LICENSE

This software is Copyright (c) 2007 by Shlomi Fish.

This is free software, licensed under:

  The MIT (X11) License

=cut
