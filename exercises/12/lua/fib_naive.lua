
function fibonacci_naive(n)
    if n < 2 then
        return n
    end
    return fibonacci_naive(n-1) + fibonacci_naive(n-2)
end

for i = 0, 100 do
    res = fibonacci_naive(30)
end
