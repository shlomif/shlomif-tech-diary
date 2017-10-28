# The Despair of a Static Site Generator Creator

**TL;DR**: the main take-away from this essay is that I cannot in good
conscience recommend against writing your own custom/adhoc/home-grown
[static site generator](https://davidwalsh.name/introduction-static-site-generators) based on some lower-level tools, rather than going through the trouble
of learning an existing open source one. Feel free to publish it as open
source as well, but you should expect that it is most probably not
going to be popular.

## Introduction

(A crowded room in a support group session:)

Me: Hi all! My name is Shlomi and I wrote several of my own static site generators!

The others: Hello, Shlomi! We all love you!

(By inspiration from Kilmo.)

Yes, I wrote several static site generators (follow [this link](https://davidwalsh.name/introduction-static-site-generators) to learn more about them and the motivation for them.), and while they have served me mostly well, I suspect few
people use them except me. They all were built on existing
[preprocessors or template systems](http://www.shlomifish.org/open-source/resources/text-processing-tools/), some of which could be considered static site gens
in their own right.

In this essay, I'd also like to give some historical perspective.

## Requirements for a static site generator

Your static site generator should have:

<ol>

<li>
A good preprocessor, generator, or template system.
</li>

<li>
A good build system, but one that could be ad-hoc and hacked together in
a [dynamic language](https://en.wikipedia.org/wiki/Dynamic_programming_language)
or similar.
</li>

<li>
The other [best practices](https://github.com/shlomif/Freenode-programming-channel-FAQ/blob/master/FAQ.mdwn#what-are-some-best-practices-in-programming-that-i-should-adopt) related
to software dev, such as using version control, or CI.
</li>

</ol>


