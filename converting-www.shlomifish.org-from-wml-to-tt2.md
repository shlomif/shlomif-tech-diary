Hi all!

TL;DR: a partial conversion of the https://www.shlomifish.org/ 's sources from
WML to [Template Toolkit 2](http://template-toolkit.org/) appears to have sped
up the rendering, and also uncovered some broken content errors, but is/was very
time consuming.

---

My home site's sources ( https://github.com/shlomif/shlomi-fish-homepage ) are
quite large (but probably much smaller than https://salsa.debian.org/webmaster-team/webwml/ )
and also has used [WML](https://github.com/thewml/website-meta-language) along with
other technologies (some of which were created by me and made FOSS). A full
rebuild of the site currently takes about 4 minutes on my sandy bridge Core i3
machine and it used to be much worse, before it was optimised.

As I previously posted on https://lists.debian.org/debian-www/2019/04/msg00106.html , I converted
https://github.com/shlomif/perl-begin from wml to TT2 and later converted
https://github.com/shlomif/fc-solve/tree/master/fc-solve/site/wml from wml
to [jinja2](https://en.wikipedia.org/wiki/Jinja_%28template_engine%29). Since I
liked TT2 better and since jinja2's scoping is weird and restrictive, and
since I use a lot of perl 5 code in my site, I decided to go with TT2 for shlomifish.org.

I set up a branch - https://github.com/shlomif/shlomi-fish-homepage/tree/wml2tt - and started
converting the pages one by one based on earlier TT2 sites, and while using some hacky scripts
in perl, bash, and vimscript:

* https://github.com/shlomif/shlomi-fish-homepage/blob/wml2tt/bin/wml2tt.pl
* https://github.com/shlomif/shlomi-fish-homepage/blob/wml2tt/bin/refact.vim
* https://github.com/shlomif/shlomi-fish-homepage/blob/wml2tt/bin/tot.bash

They are under the https://opensource.org/licenses/Apache-2.0 and can be reused but I
doubt they will be adequate for debian.org where a parser-based approach
may be needed (see https://perl-begin.org/uses/text-parsing/ and
https://www.shlomifish.org/open-source/resources/text-processing-tools/ ).

So far, the TT2 part seems to be much faster:

```
shlomif[homepage]:$trunk$ time make fastrender-wml
gunzip < t2/humour/TheEnemy/The-Enemy-English-rev5.xhtml.gz | perl ./bin/extract-xhtml.pl -o lib/htmls/The-Enemy-English-rev5.html-part -
gunzip < t2/humour/TheEnemy/The-Enemy-English-rev6.xhtml.gz | perl ./bin/extract-xhtml.pl -o lib/htmls/The-Enemy-English-rev6.html-part -
gunzip < t2/humour/TheEnemy/The-Enemy-Hebrew-rev5.xhtml.gz | perl ./bin/extract-xhtml.pl -o lib/htmls/The-Enemy-rev5.html-part -
make fastrender-wml
make fastrender-wml  42.04s user 5.02s system 321% cpu 14.657 total
shlomif[homepage]:$trunk$ time make fastrender-tt2
make fastrender-tt2
perl bin/tt-render.pl
make fastrender-tt2  3.57s user 0.15s system 99% cpu 3.722 total
```

Also note that the TT2 stage is not yet parallelised and that there are several
potential optimisations I have in mind that are not there yet.

Like I said the conversion took a long time and is not complete yet. I can
merge in the branch into master even now thanks to https://github.com/shlomif/testing-static-sites .

It also motivated some fixes in the master branch.

Finally note that the site's build process has quite a lot of overhead which
is common for both wml and tt2, e.g: DocBook rendering, generating ".epub"s / etc.

---

While the debian.org site is large, I think the current 2-3 hours build is very bad, and
deprives from the dev experience:

* https://www.xkcd.com/303/
* http://blogs.perl.org/users/ovid/2010/08/your-test-suite-is-broken.html

While I maintain wml and applied many cleanups and optimisations, the only
large scale improvement I can think of next is to convert the C executables
to https://en.wikipedia.org/wiki/Library_(computing)#Shared_libraries and load
them in process and reuse them. This may be time consuming and may not make
a big difference.

I do not necessarily advocate using TT2 instead, as there is no shortage of
[SSGs](https://staticsitegenerators.net/) and lower level template systems
and preprocessors ( https://www.shlomifish.org/open-source/resources/text-processing-tools/ ).
I was told TT2 is slower than https://metacpan.org/pod/HTML::Template and
https://metacpan.org/pod/Text::Template and yet it is still much faster than wml.

Note that the conversion can be done incrementally and without breaking
production, similar to the conversion process I've done for my sites.

Regards,

— Shlomi Fish
