function debug(...)
  io.stderr:write(table.concat({...}, ' ') .. '\n')
end

xor = require("bit32").bxor
abs = math.abs
floor, ceil = math.floor, math.ceil

max, min = math.max, math.min
sin, cos = math.sin, math.cos

function len(x, y, z)
  return math.sqrt(x * x + y * y + z * z)
end

function dist(x, y, z, xx, yy, zz)
  return len(x - xx, y - yy, z - zz)
end

function dot(x, y, z, xx, yy, zz)
  return x * xx + y * yy + z * zz
end
