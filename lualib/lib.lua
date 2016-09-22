require "lualib.csg"
require "lualib.solids"
require "lualib.transformations"
require "lualib.materials"

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
