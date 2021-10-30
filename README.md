# smol

This repository is a place of fun with self writing as little bytes as possible to make small binaries that execute given action. Goal is to make applications that are small enough to be embeded in for example QR code.

## Current results
```console
$ make; du -ab -d1 | grep .out | sort -n
173	./hello.out
5720	./xlib_hello-dynamic.out
9152	./xlib_hello.out
```

## Dependencies

- [Netwide Assembler (NASM)](https://nasm.us)
- [sstrip](http://www.muppetlabs.com/~breadbox/software/elfkickers.html)
- strip
- gcc
- Make
