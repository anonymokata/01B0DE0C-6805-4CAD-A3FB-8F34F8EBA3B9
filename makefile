CFLAGS := -std=c99 -Wall -Werror -g
objects := $(patsubst src/%.c,src/%.o,$(wildcard src/*.c))
testObjects := $(patsubst test/%.c, test/%.o,$(wildcard test/*.c))

clean:
	@echo "Echo *** Cleaning project ***\n"
	@rm -r -f src/*.o test/*.o output
