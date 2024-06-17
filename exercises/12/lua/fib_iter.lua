
function fibonacci_iter(n)
    local a, b = 0, 1
    for i = 1, n do
        a, b = b, a + b
    end
    return a
end

for i = 0, 25000000 do
    res = fibonacci_iter(30)
end
