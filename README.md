# Quickplot

A complete rewrite of quickplot (Debian package quickplot) and quickscope
with libwayland, written in C.

New features of quickplot (here's the plan):

  0. All previous features of version 1.0.1rc that do not conflict with
     new features,
  1. interactive oscilloscope plotting,
  2. C code plotting interface that compiles and loads compiled C modules, and
  3. a subcomponent of an on-the-fly configurable programming framework.

So, internally quickplot will configure itself with compiled C modules.
This will make it so that users can change how quickplot behaves by
writing very small pieces of C code.

Any number of scope and/or static plots can be interleaved in one and/or
more graphs.


## Things that we looked at:

### Zig

We found that Zig is still too new to use, for it does not support dynamic
loading of shared object libraries yet, and it may never.  It appears that
the Zig community is not interested in supporting what we consider an
essential part of modern operating systems, that is the ability to load,
unload, and share mappings of compiled C code.  We see that having shared
read only memory mappings between processes is a very big system resource
savings.  I don't think that kernel developers will remove that feature,
but the Zig community is throwing away that operating system feature.  I
find it very disturbing.  To me, Zig is not a system level programming
language for that reason.  A system level programming language needs to
support all the features of the operating system.


### Rust

Rust looks to suffer from binary bloat, at many levels.  They seem to want
to though-away and replace everything the operating system does and
replace it with Rust.  Rust does support dynamic loading of shared object
libraries, but they make it messy/bloated and hard to do.  It reminds me of
Java.  I don't care for Java either.

All my Rust code ends up "unsafe".


### C++

C compiles at least ten (up too hundreds) times faster than C++.  Life is
short.  C is simple.  C++ tends to bloat code.  I'm not controlled by a
pointy haired manager that is telling me to use C++.  C is very compatible
with C++.


### Valgrind

Valgrind helps make C code robust.  Valgrind helps make C code be memory
safe.

