SRC = src

CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11 -Wno-unused-variable -Wno-unused-parameter
LDFLAGS =

.PHONY: clean

raytracer: $(SRC)/main.o $(SRC)/image.o $(SRC)/sphere.o $(SRC)/point.o $(SRC)/ray.o
	$(CC) $(LDFLAGS) $^ -o $@

$(SRC)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm raytracer src/*.o
