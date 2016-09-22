require "lualib.utils"

function sphere(r, mat)
  return function(x, y, z)
    return len(x, y, z) - r, mat
  end
end

function cube(a, b, c, mat)
  return function(x, y, z)
    x = abs(x) - a
    y = abs(y) - b
    z = abs(z) - c
    return min(max(x, y, z), 0) + len(max(x, 0), max(y, 0), max(z, 0)), mat
  end
end

function plane(a, b, c, d, mat)
  local len = len(a, b, c)
  a = a / len
  b = b / len
  c = c / len
  d = d / len
  return function(xx, yy, zz)
    return dot(a, b, c, xx, yy, zz) + d, mat
  end
end
