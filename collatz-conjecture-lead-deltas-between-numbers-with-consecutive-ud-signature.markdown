Inspired by
[Project Euler problem No. 277](https://projecteuler.net/problem=277) , we
can give the Collatz sequence of each positive integer (see
[the Collatz conjecture](http://en.wikipedia.org/wiki/Collatz_conjecture) ) a
signature of the steps taken to reach the number 1, by denoting “u” if we
first multiply by 3 and add 1 and then (necessarily) divide by 2 (if the
number is odd), or “d” if divide by 2 (if the number is even). So for example:

4 → 2 → 1 ⇒ “ddd”

3 → 5 → 8 → 4 → 2 → 1 ⇒ “uuddd”

Now, I've written a [computer program, with source](https://bitbucket.org/shlomif/collatz-conjecture/src/bfd666d84bf0e78d2f430567291cd377218e9999/3x+1/inspired-by-project-euler/euler-inspired-collatz.pl?at=default)
to start from the first number which has a certain signature prefix, and find
the higher integer which follows with either “u” or “d” appended to the
end of the signature (e.g: from “uud” to “uudu” or “uudd”), and I found out that the difference between the two
integers is almost always 0 or a whole power of 2. You give the program a
signature at the command line and it traverses its prefixes like so:

```
$ perl euler-inspired-collatz.pl udddud
{ l=1 }
D[exact] = NONE
D[d] = 0b100
D[u] = 0b10
{ l=2 }
D[exact] = 0b-100
D[d] = 0b0
D[u] = 0b100
{ l=3 }
D[exact] = NONE
D[d] = 0b0
D[u] = 0b1000
{ l=4 }
D[exact] = 0b0
D[d] = 0b10000
D[u] = 0b100000
{ l=5 }
D[exact] = NONE
D[d] = 0b100000
D[u] = 0b0
```

(“D” here is short for “difference” or “delta”.)

It can be seen that the powers of two gradually increase as l grows, and there
may be a lead here for the fact that they span all numbers. Can anyone prove that it is the case that the deltas are whole powers of two, or tell me if there
was any research about it?
