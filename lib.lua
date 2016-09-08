-- helper functions
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
        for _, obj in ipairs(objects) do
            local d = obj(xx, yy, zz)
            if d < min_dist then
                min_dist = d
             end
        end
        return min_dist
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
function sphere(r)
    return function(xx, yy, zz)
        return len(xx, yy, zz) - r
    end
end

function plane(a, b, c, d)
    return function(xx, yy, zz)
        return (dot(a, b, c, xx, yy, zz) + d) / len(a, b, c)
    end
end

scene = union {
    translate(0, 2, -1.5) {
    sphere(0.4)
    },
    translate(0, 2, -0.5) {
        sphere(0.4)
    },
    translate(0, 2, 0.5) {
        sphere(0.4)
    },
    translate(0, 2, 1.5) {
        sphere(0.4)
    },
    plane(-1, 0, 0, 1.01),
}