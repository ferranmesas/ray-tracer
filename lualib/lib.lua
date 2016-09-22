compose = require "lualib.compose"

-- "rng" functions: given an array of numbers, it always returns
-- the same "random" number.
local function prng(seed)
  if seed == nil then
    seed = os.time()
  end

  local m = math.pow(2, 32)
  local a = 1103515245
  local c = 12345
  local function _prng(n, ...)
    local arg = {...}
    local tmp
    if #arg == 0 then
      tmp = seed
    else
      tmp = _prng(unpack(arg))
    end
    return (c + n * a * tmp) % m
  end
  return _prng
end

prng = prng()

-- helper functions
function debug(...)
  io.stderr:write(table.concat({...}, ' ') .. '\n')
end

local xor = require("bit32").bxor
local abs = math.abs
local floor = math.floor

local max, min = math.max, math.min
local sin, cos = math.sin, math.cos

local function len(x, y, z)
  return math.sqrt(x * x + y * y + z * z)
end

local function dist(x, y, z, xx, yy, zz)
  return len(x - xx, y - yy, z - zz)
end

local function dot(x, y, z, xx, yy, zz)
  return x * xx + y * yy + z * zz
end

-- csg functions of objects
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

function intersection(objects)
  return function(xx, yy, zz)
    local max_dist = -math.huge
    local max_mat
    for _, obj in ipairs(objects) do
      local d, mat = obj(xx, yy, zz)
      if d > max_dist then
        max_dist = d
        max_mat = mat
      end
    end
    return max_dist, max_mat
  end
end

-- coordinate transforms
function transformation(transform_func)
  return function (...)
    local func = transform_func(...)
    return function(object)
        object = union(object)
      return function(xx, yy, zz)
        local d, m = object(func(xx, yy, zz))
        return d, compose(m, func)
      end
    end
  end
end

translate = transformation(
  function(x, y, z)
    return function(xx, yy, zz)
      return xx - x, yy - y, zz - z
    end
  end
)

rotateX = transformation(
  function(angle)
    local angle_rad = math.rad(angle)
    local _sin = sin(angle_rad)
    local _cos = cos(angle_rad)
    return function(xx, yy, zz)
      return xx, yy * _cos - zz * _sin, yy * _sin + zz * _cos
    end
  end
)
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
  local len = len(a, b, c)
  a = a / len
  b = b / len
  c = c / len
  d = d / len
  return function(xx, yy, zz)
    return dot(a, b, c, xx, yy, zz) + d, mat
  end
end

function mirror(x, y, z)
  return {
    color = {
      r = 0,
      g = 0,
      b = 0
    },
    reflectivity = 0.8
  }
end

function checkerboard(x, y, z)
  local color
  x = floor(x) % 2
  y = floor(y) % 2
  z = floor(z) % 2
  if xor(x, y, z) == 0 then
    return {
      color = {0.9, 0.1, 0.1},
      reflectivity = 0.1
    }
  else
    return {
      color = {0.9, 0.9, 0.9},
      reflectivity = 0.2
    }
  end
end
