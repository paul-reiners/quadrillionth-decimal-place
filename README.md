<h1>quadrillionth-decimal-place</h1>
An implementation in C of the Bailey–Borwein–Plouffe (BBP) formula that allows you to compute an arbitrary hexadecimal digit of pi without computing any of the preceding digits.


This is a project for HarvardX CS50x.

[![video on project](https://img.youtube.com/vi/1fPUBExEy_c/0.jpg)](https://www.youtube.com/watch?v=1fPUBExEy_c)

<h2>Overview</h2>

This project is an implementation in C of the Bailey–Borwein–Plouffe (BBP) formula. The BBP formula allows 
you to compute efficiently an arbitrary digit of irrational constants that can be expressed in a particular 
form. (See http://en.wikipedia.org/wiki/Bailey–Borwein–Plouffe_formula for more information.) In particular,
this program allows you to compute arbitrary hexadecimal digits of pi and arbitrary binary digits of 
log(2). It is accurate out to the 100 millionth hex digit of pi. It can compute the millionth digit in 
about 10 seconds, the 10 millionth digit in about 2 minutes and the 100 millionth digit in about 
20 minutes (the BBP algorithm is linear in d where d is the digit place). I used the GNU MP Bignum 
Library to achieve this level of precision.

<h2>Features</h2>
<ul>
    <li>
        Contains an implementation of the general BBP formula.
    </li>
    <li>
        Compute arbitrary hexadecimal digits of &pi; out to the 100 millionth digit.
    </li>
    <li>
        Compute arbitrary binary digits of log(2).
    </li>
</ul>

<h2>References</h2>
I was inspired to do this project by reading the short story "The Center of the Universe"
in the book 
<a href="http://www.amazon.com/Reality-Conditions-Short-Mathematical-Fiction/dp/0883855526">
<i>Reality Conditions</i></a> by Alex Kasman.  Before that, I first learned about 
the BBP formula in the "What is the Quadrillionth Decimal Place of &pi;?" chapter
of 
<a href="http://www.amazon.com/Computer-Crucible-Introduction-Experimental-Mathematics/dp/1568813430">
<i>The Computer as Crucible</i></a> by Jonathan Borwein and Keith Devlin.  (That (obviously) 
is
also where I stole the title of my project from.)


<h2>Documentation</h2>

The links below are relative to the installation directory.  (Not the GitHub project page.)

The user's manual is [here](./doc/documentation.html).

The design documentation is [here](./doc/documentation.html).

