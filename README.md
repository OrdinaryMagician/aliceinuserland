# Alice in Userland

## What is this

Alice in Userland (Au for short) is a project to make an entire set of fully
functional core utilities for Linux (and in the future as part of the userland
in AliceOS).

It's not meant for normal use. The tools do not support the common GNU
coreutils options that have been adopted by a lot of software, so your system
WILL break.

## Why the name

I got some inspiration from the name of the project to port the Plan 9
coreutils to Linux, "Plan 9 from user space".

This project has gone through many names, but I decided to go with something
that wasn't a punny recursive acronym or was related to an animal.

By the way, Au is also the chemical symbol for gold.

## Why make it

I don't like GNU code. I think it's ugly and the GNU coreutils have a lot of
unnecessary features that are at times redundant, and at other times just plain
dumb.

Also I want to have a nice learning experience while I write all this (I find
programming to be real fun).

## POSIX compliance

I have ceased to keep the project POSIX compliant. It seems standards
compliance is considered harmful too. Well, less work for me. Smaller and more
compact binaries will come out of this now.

Also I think POSIX is also ugly.

## Compatibility

I generally check if Au can be built using Clang. I really love this compiler.
It's much more comfortable than GCC, it also produces smaller binaries.

Au has been tested to build and run flawlessly with the musl C library (both
dynamically and statically linked). Some minor tweaks are needed every once in
a while.

## Additions

Au is complemented by three other projects:

 * The Au Extrautils: A set of additional simple utilities that may or may not
   be useful, and small programs that provide the functionality of parts of
   bigger tools (for example echo's printing and de-escaping is separated into
   tools say and desc).
 * The Au Toyutils: Things that are obviously not useful, but could be fun to
   play around with.
 * te: text editor. (ed is to te as vi is to pico/nano)

## Suggestions and criticism

As long as you're not being rude I accept any suggestions about optimizing
and/or cleaning the code.

If you're being rude I will respond with more rudeness. I might also seem to
discard your suggestions, but you'll see later that I might accept them if they
ARE reasonable.

Right now I'd like to thank the people of /g/, mostly from the #/g/sicp IRC
channel (nice place most of the time), their advice has really served me well.

## Coding style and standards

Most of the code is written in a style similar to K&R. The most noticeable
difference is that ALL braces are put in a new line.

Variable and function notation is done in a descriptive style. Hungarian
notation is bad and anyone who uses it should feel bad.

I also try to follow some rules of the Linux coding standards (except when I
find it too hard to avoid having more than three indentation levels).

If you have any complaints about my coding style, you can send them to
/dev/null, thank you very much.

Code follows the C99 standard.
