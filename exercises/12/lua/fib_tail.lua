
function fibonacci_tail(n)
  local function inner(m, a, b)
    if m == 0 then
      return a
    end
    return inner(m-1, b, a+b)
  end
  return inner(n, 0, 1)
end

for i = 0, 10000000 do
    res = fibonacci_tail(30)
end

