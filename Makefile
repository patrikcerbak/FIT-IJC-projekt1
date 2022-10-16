#
# soubor:      Makefile
# autor:       Patrik Čerbák - xcerba00, FIT
# projekt:     IJC DU1, příklad A+B)
# překladač:   gcc 11.2.1
# datum:       22.3.2022
#

CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -lm -O2

all: primes primes-i steg-decode

run: primes primes-i
	ulimit -s 40000 && ./primes && ./primes-i

primes: primes.o bitset.o eratosthenes.o error.o
	$(CC) $(CFLAGS) primes.o bitset.o eratosthenes.o error.o -o primes

primes-i: i_primes.o i_eratosthenes.o i_bitset.o error.o
	$(CC) $(CFLAGS) -DUSE_INLINE i_primes.o i_bitset.o i_eratosthenes.o error.o -o primes-i

steg-decode: steg-decode.o ppm.o bitset.o eratosthenes.o error.o
	$(CC) $(CFLAGS) steg-decode.o ppm.o bitset.o eratosthenes.o error.o -o steg-decode

# překlad object souborů
%.o: %.c
	$(CC) $(CFLAGS) -c $^
# překlad object souborů s USE_INLINE parametrem
i_%.o: %.c
	$(CC) $(CFLAGS) -DUSE_INLINE -c $^ -o $@

# clean a zip pro zjednodušení práce
clean:
	rm -f *.o primes primes-i steg-decode
zip:
	zip xcerba00.zip *.c *.h Makefile
