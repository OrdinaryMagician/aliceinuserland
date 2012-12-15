# Alice in Userland

## What is this

Alice in Userland (Au for short) is a project to make an entire set of fully functional core utilities for Linux (and in the future as part of the userland in AliceOS).

It's not meant for normal use. The tools do not support the common GNU coreutils options that have been adopted by a lot of software, so your system WILL break.

## Why the name

I got some inspiration from the name of the project to port the Plan 9 coreutils to Linux, "Plan 9 from user space".

This project has gone through many names, but I decided to go with something that wasn't a punny recursive acronym or was related to an animal.

By the way, Au is also the chemical symbol for gold.

## Why make it

I don't like how GNU is the only fully usable system to run atop the Linux kernel. It's not like I hate GNU and the FSF or anything (well, I do dislike them a bit), I just don't find it fair that they are the only ones.

Oh and they're trying to get more merit than they deserve. Just see the Linux vs. GNU/Linux (or GNU+Linux as some say now) naming madness. Honestly, with Au no ridiculous naming schemes are imposed.

From what I've seen, GNU code is gross (really), unclean, bloated and not very easy to follow (my head hurts when I try to read it). I'm not the only one with this opinion, apparently.

The GNU project adds extra functionality that is absolutely unnecessary (just look at GNU Hello, seriously) and can be considered harmful (cat -v, anyone?).

Also I want to have a nice learning experience while I write all this (I find programming to be real fun).

## POSIX compliance

I have ceased to keep the project POSIX compliant. It seems standards compliance is considered harmful too. Well, less work for me. Smaller and more compact binaries will come out of this now.

## Compatibility

I generally check if Au can be built using Clang. I really love this compiler. It's much more comfortable and helpful than GCC, it also produces smaller binaries.

Au has been tested to build and run flawlessly with the musl C library (both dynamically and statically linked). Some minor tweaks are needed every once in a while.

## Additions

Au is complemented by three other projects:

 * The Au Extrautils: A set of additional simple utilities that may or may not be useful, and small programs that provide the functionality of parts of bigger tools (for example echo's printing and de-escaping is separated into tools say and desc).
 * The Au Toyutils: Things that are obviously not useful, but could be fun to play around with.
 * te: text editor. (ed is to te as vi is to pico/nano)

## Suggestions and criticism

As long as you're not being rude I accept any suggestions about optimizing and/or cleaning the code.

If you're being rude I will respond with more rudeness. I might also seem to discard your suggestions, but you'll see later that I might accept them if they ARE reasonable.

Right now I'd like to thank the people of /g/, mostly from the #/g/sicp IRC channel (nice place most of the time), their advice has really served me well.

## Coding style and standards

Most of the code is written in a style similar to K&R. The most noticeable difference is that ALL braces are put in a new line.

Variable and function notation is done in a descriptive style. Hungarian notation is bad and anyone who uses it should feel bad.

I also try to follow some rules of the Linux coding standards (except when I find it too hard to avoid having more than three indentation levels).

If you have any complaints about my coding style, you can send them to /dev/null, thank you very much.

Code follows the C99 standard.
