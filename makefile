CFLAGS:=-std=c99 -Wall -Werror -g
objects:=$(patsubst src/%.c,src/%.o,$(wildcard src/*.c))
test_objects:=$(patsubst test/%.c, test/%.o,$(wildcard test/*.c))

clean:
	@clear
	@echo "*** Cleaning project ***\n"
	@cd ~/projects/kata/c/RomanNumeralCalcInC
	@echo "CFLAGS ="$(CFLAGS)
	@echo "objects ="$(objects)
	@echo "test_objects ="$(test_objects)
	@rm -r -f src/*.o test/*.o output

build:  clean
	@echo "*** Building RomanNumeralCalcInC ***\n"
	@mkdir -p output
	@echo "Compiling..."
	gcc $(CFLAGS) -o output/tests $(objects) $(testObjects) 

test:  	build 
	@echo "*** Running tests ***\n"
