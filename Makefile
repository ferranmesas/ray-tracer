SRC = src

CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11 -Wno-unused-variable
LDFLAGS =

.PHONY: clean

raytracer: $(SRC)/main.o $(SRC)/image.o $(SRC)/sphere.o $(SRC)/point.o
	$(CC) $(LDFLAGS) $^ -o $@

$(SRC)/%.o: $(SRC)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm src/*.o
