Inspired by
[Project Euler problem No. 277](https://projecteuler.net/problem=277) , we
can give the Collatz sequence of each positive integer (see
[the Collatz conjecture](http://en.wikipedia.org/wiki/Collatz_conjecture) ) a
signature of the sequence of steps taken to reach the number 1.

Let's denote:

* “u” for the two consecutive steps of multiplying an odd number by 3 and
adding one and then dividing by two.

* “d” if divide by 2 (if the number is even).

So for example:

4 → 2 → 1 ⇒ “dd”

3 → 5 → 8 → 4 → 2 → 1 ⇒ “uuddd”

Now, I've written a [computer program, with source](https://github.com/shlomif/collatz-conjecture/blob/master/3x%2B1/inspired-by-project-euler/euler-inspired-collatz.pl)
to investigate the signatures of these numbers. Let's say that n is the lowest
natural number whose signature begins with a certain signature prefix
`[p[1],p[2]...p[k]]` where k>=1 and every p[i] is either “u” or “d”.

Let's call the smallest integer (naturally above or equal to n) whose
signature starts with `[p[1],p[2]...p[k],“u”]` as m[u] and likewise the
smallest
integer whose signature starts with the sequence `[p[1],p[2]...p[k],“d”]`
as m[d].

It turns out that usually m[d]-n and m[u]-n are either zero or a whole power
of 2.

```
$ perl euler-inspired-collatz.pl udddud
{ seq prefix = < u > }
    n with <u> = 0b11
    m[d] = 0b101
        diff of m[d] - n = 0b10
    m[u] = 0b11
        diff of m[u] - n = 0b0
{ seq prefix = < ud > }
    n with <ud> = 0b101
    m[d] = 0b101
        diff of m[d] - n = 0b0
    m[u] = 0b1001
        diff of m[u] - n = 0b100
{ seq prefix = < udd > }
    n with <udd> = 0b101
    m[d] = 0b101
        diff of m[d] - n = 0b0
    m[u] = 0b1101
        diff of m[u] - n = 0b1000
{ seq prefix = < uddd > }
    n with <uddd> = 0b101
    m[d] = 0b10101
        diff of m[d] - n = 0b10000
    m[u] = 0b100101
        diff of m[u] - n = 0b100000
{ seq prefix = < udddu > }
    n with <udddu> = 0b100101
    m[d] = 0b1000101
        diff of m[d] - n = 0b100000
    m[u] = 0b100101
        diff of m[u] - n = 0b0
```

It can be seen that the powers of two gradually increase as l grows, and there
may be a lead here for the fact that they span all numbers. Can anyone prove
that it is the case that the deltas are whole powers of two, or tell me if
there was any research about it?
