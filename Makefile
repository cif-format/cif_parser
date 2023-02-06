CC := gcc
CFLAGS := -Iinclude -std=gnu99 \
					-g -Wall -Wextra -pedantic \
					-O3

override CFILES := $(shell find ./src/ -type f)
override OFILES := $(shell find ./obj/ -type f)

all: cif_parser
.PHONY: all

cif_parser:
	@mkdir -p obj/ bin/
	$(foreach file, $(CFILES), $(CC) $(CFLAGS) -c $(file) -o obj/$(basename $(notdir $(file))).o;)
	@gcc $(CFLAGS) $(OFILES) -o bin/cif_parse -lgcc

clean:
	rm -rf obj/ bin/

check:
	rm bin/f.cif || true
	@curl -L -o bin/f.cif https://raw.githubusercontent.com/cif-format/cif/master/examples/1x1-red.cif
	./bin/cif_parse bin/f.cif