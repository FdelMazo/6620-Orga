CC = gcc
CFLAGS = -g -std=c99 -Wall -Werror
CFLAGS += -Wbad-function-cast
CFLAGS += -Wtype-limits -Wshadow -Wno-unused-variable
CFLAGS += -Wpointer-arith -Wunreachable-code -Wformat=2
CFLAGS += -pedantic

FILE=glider
STATES=40
ROWS=10
COLS=10

SCALING_FACTOR=16
SPEED=8

run: conway
	./$< $(STATES) $(ROWS) $(COLS) $(FILE)
	for f in $(FILE)_*.pbm; do pnmscale $(SCALING_FACTOR) $$f | pgmtopbm | tee $${f%.pbm}_out.pbm; done > /dev/null 2>&1
	ffmpeg -y -r $(SPEED) -i "$(FILE)_%03d_out.pbm" "$(FILE).gif" -hide_banner

conway: conway.o matrix.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f conway *.pbm *.gif
