CFLAGS:=-std=c99 -Wall -Werror -g
objects:=$(patsubst src/%.c,src/%.o,$(wildcard src/*.c))
test_objects:=$(patsubst test/%.c,test/%.o,$(wildcard test/*.c))

clean:
	@clear
	@echo "*** Cleaning project ***\n"
	@cd ~/projects/kata/c/RomanNumeralCalcInC
	@rm -r -f src/*.o test/*.o output

build:  clean $(objects) $(test_objects)
	@echo "\n*** Building RomanNumeralCalcInC ***\n"
	@mkdir -p output
	@gcc $(CFLAGS) -o output/tests $(test_objects) $(objects) `pkg-config --cflags --libs check`

test:  	build 
	@echo "\n*** Running tests ***\n"
	@output/tests
