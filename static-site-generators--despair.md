---
title: "See Also:"
---

# The Despair of a Static Site Generator Creator

## TL;DR

The main take-away from this essay is that I cannot in good conscience
recommend against writing your own custom/ad-hoc/home-grown [static site
generator](https://davidwalsh.name/introduction-static-site-generators)
("SSG") based on some lower-level tools, rather than going through the
trouble of learning an existing open source one. Feel free to publish
your own creation as open source as well, but you should anticipate that
it is most probably not going to be popular.

## Introduction

(A crowded room in a support group session:)

Me: Hi all! My name is Shlomi and I wrote several of my own static site
generators!

The others: Hello, Shlomi! We all love you!

(By inspiration from Kilmo.)

Yes, I wrote several static site generators (follow [this
link](https://davidwalsh.name/introduction-static-site-generators) to
learn more about SSGs in general and the motivation for them), and while
they have served me mostly well, I suspect few people use them except
me. They all were built on existing [preprocessors or template
systems](http://www.shlomifish.org/open-source/resources/text-processing-tools/),
some of which could be considered static site gens in their own right.

In this essay, I'd also like to give some historical perspective.

## Requirements for a static site generator

Your static site generator should have:

1.  A good preprocessor, generator, or template system.

2.  A good build system, but one that could be ad-hoc and hacked
    together in a [dynamic
    language](https://en.wikipedia.org/wiki/Dynamic_programming_language)
    or similar.

3.  The other [best
    practices](https://github.com/shlomif/Freenode-programming-channel-FAQ/blob/master/FAQ.mdwn#what-are-some-best-practices-in-programming-that-i-should-adopt)
    related to software dev, such as using version control, or CI.

## How it started

I originally learned how to write
[HTML](https://en.wikipedia.org/wiki/HTML) from an article in an
Internet magazine that my father bought me back around 1995. In 1996, I
started working as a web developer for Cortext Web Design where I wrote
HTML or CGI scripts generating it server-side in [Perl
5](https://en.wikipedia.org/wiki/Perl) and learned some other
technologies.

After a while, I set up my own web site consisting of several
hand-maintained HTML pages and maintained it for many years this way.
You can find an old [1998
snapshot](http://www.shlomifish.org/meta/old-site-snapshots/) of it.

A bit later while working on the Israeli Group of Linux Users' site, I
wrote my first static site generator, in PHP (version 3 if I recall
correctly) where it used PHP to preprocess the pages offline and
generate a static site. While it worked, the use of PHP for that seemed
suboptimal.

## The birth of Latemp

[Website META
Language](http://www.shlomifish.org/open-source/projects/website-meta-language/)
or WML for short was a relatively early and open source offline HTML
preprocessing toolkit that proved to be somewhat popular. I learnt about
it in a news digest that one of the Linux-Israel members posted, and
eventually decided to try it out. After writing some smaller projects
with it, I ended up converting most of my sites to it. This resulted in
some duplicate code, which I decided to extract into
[Latemp](http://www.shlomifish.org/open-source/projects/latemp/) (a play
on "Template" and [LaTeX](https://en.wikipedia.org/wiki/LaTeX)), which
was a static site generator that was marketed as an “offline content
management system”, which in turn caused me to be contacted by some
people seeking a server-side CMS such as
[Drupal](https://en.wikipedia.org/wiki/Drupal). To be fair: at that
point, I wasn't aware that "static site generator" was the more
conventional term.

WML and Latemp proved to be powerful and flexible, but on the other
hand, were relatively slow in comparison to other alternatives.

I should note that I ended up becoming the maintainer of WML.

## Facing some criticism

Back in the early to mid-200xs, a fellow Linux-IL worker kept telling me
that I should not generate static HTML sections of our sites and instead
should use PHP on the server side, implying that static HTML was no
longer a valid approach.

Furthermore, when a different contributor volunteered to create a site
and I told him to use static HTML and not depend on PHP, he asked me if
he could use HTML frames. Turns out that despite his years of experience
in PHP, he didn't realise that static HTML can be generated from
templates, something I had realised years ago.

Nowadays, with the advent of
[Jekyll](https://en.wikipedia.org/wiki/Jekyll_%28software%29) and other
popular SSGs, many clueful web-developers are more informed about them.
On the other hand, someone recently argued that Jekyll was the only
valid alternative to server-side PHP, and not SSG in general.

## Recent developments

Some time after [GitHub](https://en.wikipedia.org/wiki/GitHub) started,
it started offering the “GitHub pages” service for hosting static HTML
sites, and shortly afterwards Jekyll and other SSGs emerged and made the
concept of SSG more well-known. GitHub also allows previewing files in
several formats as rich text HTML directly from the repository view.

I tried using Jekyll for [Vim-Begin](http://vim.begin-site.org/) and
ended up not liking it out of finding it too opaque and hard to use. As
a result, I ended up creating a new SSG for Vim-Begin based on [Template
Toolkit](https://en.wikipedia.org/wiki/Template_Toolkit). Later, I used
it for the [Israeli Linux users’ site](http://www.linux.org.il/). One
possible indication of its ease-of-use is that it received some
pull-requests from other contributors on GitHub.

Moreover, it seems it is much faster than Latemp, as well.

My sites now incorporate such [industry best
practices](https://perlhacks.com/2012/03/you-must-hate-version-control-systems/)
as using version control, having an automated test suite, and using a
Continuous Integration service. They should also be mostly valid
HTML/XHTML markup. However, the Latemp-based ones take a while to build
and sometimes involve quite a few levels of
[indirection](https://en.wikipedia.org/wiki/Indirection) and
preprocessing. So I cannot recommend using Latemp, due to this and
because WML is quite complex.

I also found the hybrid approach taken by
[ikiwiki](https://en.wikipedia.org/wiki/Ikiwiki) of providing both an
SSG and a server-side CMS appealing, and used git repositories
containing files written in markdown and other markup languages, for a
good effect.

Like I said earlier, I find that writing your own custom SSG is not
hard, and probably less hard than learning an existing one. Also see
[ţhe list of Programs Every Programmer Has
Written](http://www.shlomifish.org/humour/bits/Programs-Every-Programmer-has-Written/).
So I expect more of them to emerge in the future.

Someone on chat told me he believed that SSGs won’t survive the trend
towards component-based client-side frameworks (such as React.js or
Vue.js) but I'm skeptical of such predictions and in my time saw several
similar ones not materialise. Also see [this funny critique of modern
JS](https://hackernoon.com/how-it-feels-to-learn-javascript-in-2016-d3a717dd577f).

So static site generation has proven to be a valid approach in the past
and into the near future. However, I maintain several sites using my own
custom ones (with all their quirks) and don't expect them to be of much
interest to anyone except me and future maintainers of the sites. And
here lies my despair.

## Licence

You can reuse this entry under the Creative Commons Attribution
Noncommercial (CC-by-nc) 3.0 Unported licence, or at your option any
later version. See the instructions on how to comply with it.

## See Also:

- [Four Ways to Build Web Apps :: Tom
  Hummel](https://tomhummel.com/posts/four-web-apps/)
- [How is shlomifish.org
  generated?](https://www.shlomifish.org/meta/FAQ/#how_site_is_generated)
