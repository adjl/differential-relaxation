CFLAGS=-std=c90 -g -pg -Wall -Wextra -Wunused -Wformat=2 -Waggregate-return -Wbad-function-cast -Wc++-compat -Wcast-align -Wcast-qual -Wconversion -Wdeclaration-after-statement -Wdisabled-optimization -Wfloat-equal -Winit-self -Winline -Winvalid-pch -Wjump-misses-init -Wlogical-op -Wmissing-declarations -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-prototypes -Wnested-externs -Wno-aggressive-loop-optimizations -Wno-sign-conversion -Wold-style-definition -Wpacked -Wpadded -Wredundant-decls -Wshadow -Wstack-protector -Wstrict-overflow=5 -Wstrict-prototypes -Wsuggest-attribute=const -Wsuggest-attribute=format -Wsuggest-attribute=noreturn -Wsuggest-attribute=pure -Wswitch-default -Wswitch-enum -Wtrampolines -Wundef -Wunsafe-loop-optimizations -Wunsuffixed-float-constants -Wunused-macros -Wwrite-strings -Werror -pedantic-errors -funsigned-char

all:
	gcc $(CFLAGS) -o diffrelax diffrelax.c

clean:
	rm diffrelax
