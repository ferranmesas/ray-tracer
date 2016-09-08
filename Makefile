SRC = src

CFLAGS += $(shell pkg-config --cflags lua) -Wall -Wextra -pedantic -std=c11
LDFLAGS += $(shell pkg-config --libs lua)

OPTFLAGS = -O2 -march=native -ffast-math -fomit-frame-pointer -g

.PHONY: clean

raytracer: $(SRC)/main.o $(SRC)/sphere.o $(SRC)/point.o $(SRC)/ray.o $(SRC)/scene.o $(SRC)/plane.o $(SRC)/color.o $(SRC)/utils.o
	$(CC) $^ $(LDFLAGS) -o $@

$(SRC)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) $(CFLAGS) $(OPTFLAGS) -c $< -o $@

clean:
	rm -f raytracer src/*.o
