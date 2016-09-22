require "lualib.lib"

light_source = {
    x = -4,
    y = -1,
    z = 0.6
}

scene = union {
  translate(0, 2, 5.5) {
    rotateX(15) {
      cube(4, 4, 4, mirror)
    }
  },
  translate(0, 4, -1) {
    sphere(1, mirror)
  },
  translate(0, 1.5, -2) {
    sphere(1, checkerboard)
  },
  rotateX(15) {
    plane(-1, 0, 0, 2.01, checkerboard)
  }
}
