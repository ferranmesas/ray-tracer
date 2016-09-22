local compose = require "lualib.compose"
require "lualib.utils"

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
