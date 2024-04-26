CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c11 -O3

#TILE_SIZES = 64 128 256 512 1024
TILE_SIZES = 128 256

# Generate combinations of TILE_X, TILE_Y
COMBINATIONS = $(foreach x,$(TILE_SIZES),$(foreach y,$(TILE_SIZES),TILE_X=$(x) TILE_Y=$(y)))

# Source file
SRC = mmul.c
DIR = build/

# Executable names
EXECUTABLES_MULT = $(foreach x,$(TILE_SIZES),$(foreach y,$(TILE_SIZES),mmul_MULT_$(x)_$(y)))
EXECUTABLES_INIT = $(foreach x,$(TILE_SIZES),$(foreach y,$(TILE_SIZES),mmul_INIT_$(x)_$(y)))
EXECUTABLES_INIT_MULT = $(foreach x,$(TILE_SIZES),$(foreach y,$(TILE_SIZES),mmul_INIT_MULT_$(x)_$(y)))

all: $(EXECUTABLES_MULT) $(EXECUTABLES_INIT) $(EXECUTABLES_INIT_MULT) mmul_REFERENCE

define compile_rule
mmul_MULT_$(x)_$(y): mmul.c
	$(CC) $(CFLAGS) -o $(DIR)mmul_MULT_$(x)_$(y) $(SRC) -DTILE_X=$(x) -DTILE_Y=$(y) -DTILE_MULT

mmul_INIT_$(x)_$(y): mmul.c
	$(CC) $(CFLAGS) -o $(DIR)mmul_INIT_$(x)_$(y) $(SRC) -DTILE_X=$(x) -DTILE_Y=$(y) -DTILE_INIT

mmul_INIT_MULT_$(x)_$(y): mmul.c
	$(CC) $(CFLAGS) -o $(DIR)mmul_INIT_MULT_$(x)_$(y) $(SRC) -DTILE_X=$(x) -DTILE_Y=$(y) -DTILE_MULT -DTILE_INIT

endef

$(foreach x,$(TILE_SIZES),$(foreach y,$(TILE_SIZES),$(eval $(call compile_rule,$(x),$(y)))))

mmul_REFERENCE: mmul.c
	$(CC) $(CFLAGS) -o $(DIR)$@ $(SRC)

clean:
	rm -f $(DIR)$(EXECUTABLES_MULT) $(DIR)$(EXECUTABLES_INIT) $(DIR)$(EXECUTABLES_INIT_MULT) mmul_REFERENCE

