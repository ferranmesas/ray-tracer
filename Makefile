SRC = src

CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11
OPTFLAGS = -O2 -march=native -ffast-math -fomit-frame-pointer -g
LDFLAGS =

.PHONY: clean

raytracer: $(SRC)/main.o $(SRC)/sphere.o $(SRC)/point.o $(SRC)/ray.o $(SRC)/scene.o
	$(CC) $(LDFLAGS) $^ -o $@

$(SRC)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) $(CFLAGS) $(OPTFLAGS) -c $< -o $@

clean:
	rm raytracer src/*.o
