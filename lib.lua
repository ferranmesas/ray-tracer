-- helper functions
local function debug(...)
  io.stderr:write(table.concat({...}, ' ') .. '\n')
end

local abs = math.abs
local max = math.max
local min = math.min
local floor = math.floor

local function len(x, y, z)
  return math.sqrt(x * x + y * y + z * z)
end

local function dist(x, y, z, xx, yy, zz)
  return len(x - xx, y - yy, z - zz)
end

local function dot(x, y, z, xx, yy, zz)
  return x * xx + y * yy + z * zz
end

-- transformations of objects
function union(objects)
  return function(xx, yy, zz)
    local min_dist = math.huge
    local min_mat
    for _, obj in ipairs(objects) do
      local d, mat = obj(xx, yy, zz)
      if d < min_dist then
        min_dist = d
        min_mat = mat
      end
    end
    return min_dist, min_mat
  end
end

function translate(x, y, z)
  return function(object)
    return function(xx, yy, zz)
      if type(object) == "table" then
        object = union(object)
      end
      return object(xx - x, yy - y, zz - z)
    end
  end
end

-- shapes
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
  return function(xx, yy, zz)
    return (dot(a, b, c, xx, yy, zz) + d) / len(a, b, c), mat
  end
end

function mirror(x, y, z)
  return {
    color = {
      r = 0,
      g = 0,
      b = 0
    },
    reflectivity = 0.9
  }
end

function checkerboard(x, y, z)
  local color
  if floor(x) ^ floor(y) ^floor(z) then
    color = {0.9, 0.1, 0.1}
  else
    color = {0.9, 0.9, 0.9}

  end
  return {
    color = color,
    reflectivity = 0
  }
end

light_source = {
    x = -40,
    y = 0,
    z = -40
}

scene = union {
    translate(0, 2, -1.5) {
    sphere(0.4, mirror)
    },
    translate(-0.4, 4, -0.5) {
        cube(0.3, 1, 1.5, mirror)
    },
    translate(0, 2, 1.5) {
        sphere(0.4, checkerboard)
    },
    plane(-1, 0, 0, 1.01, checkerboard),
}
