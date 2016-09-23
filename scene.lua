require "lualib.lib"

light_source = {
    x = -4,
    y = -1,
    z = 0.6
}

scene = union {
  translate(0, 1, 5.5) {
    rotateX(30) {
      cube(4.01, 4.01, 4.01, checkerboard)
    }
  },
  translate(0, 4, -1) {
    sphere(2, checkerboard)
  },
  translate(0, 1.5, -2) {
    sphere(1, color(0.4, 0.4, 0.9))
  },
  rotateX(30) {
    plane(-1, 0, 0, 2.01, checkerboard)
  }
}
