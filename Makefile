SRC = src

CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11 -O2 -march=native -ffast-math
LDFLAGS =

.PHONY: clean

raytracer: $(SRC)/main.o $(SRC)/image.o $(SRC)/sphere.o $(SRC)/point.o $(SRC)/ray.o
	$(CC) $(LDFLAGS) $^ -o $@

$(SRC)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm raytracer src/*.o
