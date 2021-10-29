all: hello.out

%.out: %.s
	nasm -fbin -o $@ $<
	chmod +x $@

.PHONY: clean
clean:
	rm -f *.o *.png *.out
