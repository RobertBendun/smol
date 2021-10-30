all: hello.out xlib_hello.out xlib_hello-dynamic.out

%.out: %.s
	nasm -fbin -o $@ $<
	chmod +x $@

xlib_hello.out: xlib_hello.c Makefile
	gcc $< -o $@ -lX11 -lc -fno-stack-protector -Os -s -march=native -fomit-frame-pointer -ffunction-sections -fdata-sections -Wl,--gc-sections -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-unroll-loops -fmerge-all-constants -fno-ident -Wl,-z,norelro -Wl,--build-id=none -z max-page-size=4096 -flto
	strip $@ -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag
	sstrip $@


xlib_hello-dynamic.out: xlib_hello-dynamic.cc Makefile
	gcc $< -o $@ -ldl -fno-stack-protector -Os -s -march=native -fomit-frame-pointer -ffunction-sections -fdata-sections -Wl,--gc-sections -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-unroll-loops -fmerge-all-constants -fno-ident -Wl,-z,norelro -Wl,--build-id=none -fno-exceptions -fno-rtti -z max-page-size=1024 -flto
	strip $@ -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag
	sstrip $@

.PHONY: clean
clean:
	rm -f *.o *.png *.out xlib_hello
