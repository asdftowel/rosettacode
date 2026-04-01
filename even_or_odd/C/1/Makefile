.POSIX: ;

CC     = gcc
NAME   = even_odd
SRCDIR = .
CFLAGS = -O3 -march=native -flto=auto
WFLAGS = -Wall -Wextra -Wshadow -Wconversion -Wpointer-arith -Werror -pedantic-errors
PGOGEN = -fprofile-generate
PGOUSE = -fprofile-use
PROFEX = gcda
PFILES = # for compilers like clang which require explicit profile names
         # for example "=*.$(PROFEX)"

$(NAME): $(SRCDIR)/even_odd.c
	echo "CCLD $<"
	$(CC) $(CFLAGS) $(WFLAGS) -o $@ $<

check: $(SRCDIR)/test_eo.sh
	prefix='./' name=$(NAME) sh $<

clean:
	rm $(NAME)

pgo-instr: $(SRCDIR)/even_odd.c
	echo "CCLD $<"
	$(CC) $(CFLAGS) $(WFLAGS) -o $(NAME) $< $(PGOGEN)

pgo-build: $(SRCDIR)/even_odd.c
	echo "CCLD $<"
	$(CC) $(CFLAGS) $(WFLAGS) -o $(NAME) $< $(PGOUSE)$(PFILES)
	rm *.$(PROFEX)

pgo: pgo-instr check pgo-build

.SILENT: $(NAME) check clean pgo-instr pgo-build pgo
