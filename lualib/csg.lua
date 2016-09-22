require "lualib.utils"

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
