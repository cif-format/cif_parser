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
	printf '\xdb\xfe\x01\x20\x01\xff\x00\x00\xff\xff\xff\xff' > bin/f.cif
	./bin/cif_parse bin/f.cif