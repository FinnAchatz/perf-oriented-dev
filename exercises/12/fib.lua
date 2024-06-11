
function fibonacci_naive(n)
    if n < 2 then
        return n
    end
    return fibonacci_naive(n-1) + fibonacci_naive(n-2)
end

function measure(reps, f, ...)
  local start = os.clock()
  local res
  for i = 0, reps do
    res = f(...)
  end
  local time = (os.clock() - start)
  
  return time, res
end

t, v = measure(1, fibonacci_naive, 20)
print(string.format("1 x fibonacci_naive(20)     time: %8.4f s  --  %s", t, v))
