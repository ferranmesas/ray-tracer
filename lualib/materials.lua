require "lualib.utils"

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

function color(r, g, b, reflectivity)
  if reflectivity == nil then
    reflectivity = 0
  end
  return function()
    return {
      color = {r, g, b},
      reflectivity = reflectivity
    }
  end
end
