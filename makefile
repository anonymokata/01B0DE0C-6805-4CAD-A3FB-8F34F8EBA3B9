CFLAGS := -std=c99 -Wall -Werror -g
objects := $(patsubst src/%.c,src/%.o,$(wildcard src/*.c))
testObjects := $(patsubst test/%.c, test/%.o,$(wildcard test/*.c))

clean:
	@clear
	@echo "*** Cleaning project ***\n"
	@rm -r -f src/*.o test/*.o output

build:  clean
	@echo "*** Building RomanNumeralCalcInC ***\n"

test:  	build 
	@echo "*** Running tests ***\n"

