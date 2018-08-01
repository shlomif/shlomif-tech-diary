Alien:: distributions on CPAN (see https://github.com/Perl5-Alien ) should
not be made an optional requirement by their reverse deps because this will
mean duplicate logic at best, and a broken build process at worst.

For more info and some solutions for common problems, see:

* https://github.com/petdance/html-tidy5/pull/9

* https://rt.cpan.org/Public/Bug/Display.html?id=125972
