## Profiling
### gprof

![](./output.png)

`cat gprof.log | gprof2dot | dot -Tpng -o output.png`

## Performance optimizations:

### Baseline
```
100 x fibonacci_naive(30)     time:  13.2963 s  --  832040
10000000 x fibonacci_tail(30) time:  12.2872 s  --  832040
25000000 x fibonacci_iter(30) time:  12.0387 s  --  832040
```

### `luaD_pretailcall`

Looking into gprof a lot time is spent in `ldo.c:543  luaD_pretailcall()`.
