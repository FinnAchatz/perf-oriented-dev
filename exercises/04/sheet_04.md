Exercise Sheet 4
================

For this exercise, perform all measurments on LCC3. You can of course (and probably should) run analysis tools (e.g. massif-visualizer) locally.

A) Memory profiling
-------------------

In `larger_samples` you find two somewhat larger C programs. The first one you are already familiar with. The second one, "SSCA2", takes a "scale" as its command line parameter -- use `ssca2 17` for this exercise.

For both programs:
 * Use the valgrind "massif" tool in Valgrind to determine the largest sources of heap memory utilization, and visualize the results with "massif-visualizer".
 * How significant is the perturbation in execution time caused by using massif?

Summarize, interpret and report your findings.

---

To use massif one should compile with debugging info (`-g`)

I ran massif using the following comand:
`valgrind --tool=massif --massif-out-file="massif-ssca2.out" ./ssca2 17`

ssca2 uses 24.5 MiB at the peak snapshot. 12 MiB of that is used in `compute_graph` and another 12 MiB in `genScalData`.
This peak only exists for two snapshots and then heap consumption goes bach ddown to 8.5 MiB. It slowly increases linearly to another maxima of 20 MiB, with `betweenCentrality` using 10 MiB and `computGraph` 8 MiB.

npb_bt is much less interresting with 8.5 MiB max usage. The only calls using heap memory are `__fopen_internal` and `_IO_file_deallocate`.


Perturbation in execution time is quite significant using massif.  
For ssca2, the execution time more then doubles, from 32s to 68s.  
bt_npb with massif takes 650s instead of 73s, so there is an increase of almost 800%!

B) Measuring CPU counters
-------------------------

For both programs, measure **all** events in the `[Hardware cache event]` category reported by `perf list`. Note that as discussed in the lecture, there is a limit on the number of hardware counters you can measure in a single run.

For both programs:
 * Report the results in **relative** metrics, and compare these between the programs.
 * How significant is the perturbation in execution time caused by using perf to measure performance counters?

Summarize, interpret and report your findings.

---


|         ssca2  | % | bt_npb | % |event |
|           ---  | ---| --- | --- | --- | 
|  4,129,953,633 | **36.35%** |   6,837,444,728 |    4.36%   | L1-dcache-load-misses:u 
| 11,362,653,613 |            | 156,661,883,424 |            | L1-dcache-loads:u          
|    181,248,869 |**107.53%** |   1,785,294,907 |   53.28%   | L1-dcache-prefetch-misses:u
|    168,552,526 |            |   3,350,609,874 |            | L1-dcache-prefetches:u     
|    648,859,227 | **24.42%** |   2,418,979,113 |    3.27%   | L1-dcache-store-misses:u   
|  2,657,295,482 |            |  73,902,800,217 |            | L1-dcache-stores:u         
|        506,088 |    0.0%    |      53,743,261 |    0.0%    | L1-icache-load-misses:u
| 32,690,305,314 |            | 141,726,325,449 |            | L1-icache-loads:u    
|    292,473,371 |   10.53%   |     307,865,196 | **52.45%** | LLC-load-misses:u    
|  2,778,078,815 |            |     587,013,474 |            | LLC-loads:u          
|        905,126 |   17.96%   |     480,254,420 | **62.41%** | LLC-prefetch-misses:u
|      5,038,334 |            |     769,430,218 |            | LLC-prefetches:u     
|     42,439,038 |    2.19%   |      29,350,282 |    6.6%    | LLC-store-misses:u   
|  1,939,523,126 |            |     444,413,187 |            | LLC-stores:u
| 10,801,879,904 |**185.59%** |   1,832,594,108 | **99.03%** | branch-load-misses:u
|  5,820,242,534 |            |   1,850,489,448 |            | branch-loads:u      
|    738,602,243 |    6.5%    |       1,210,825 |    0.0%    | dTLB-load-misses:u  
| 11,363,848,511 |            | 156,580,950,081 |            | dTLB-loads:u        
|    141,201,051 |    5.32%   |         300,332 |    0.0%    | dTLB-store-misses:u 
|  2,655,820,556 |            |  73,893,050,552 |            | dTLB-stores:u       
|        239,578 |    0.0%    |         762,612 |    0.0%    | iTLB-load-misses:u  
| 34,324,379,689 |            | 383,113,014,309 |            | iTLB-loads:u          
|            350 |    0.0%    |           1,999 |    0.0%    | node-load-misses:u    
|    293,959,536 |            |     304,996,198 |            | node-loads:u          
|            136 |    0.0%    |           1,760 |    0.0%    | node-prefetch-misses:u
|      1,031,418 |            |     476,822,034 |            | node-prefetches:u     
|              0 |    0.0%    |               0 |    0.0%    | node-store-misses:u   
|     40,683,085 |            |      27,224,757 |            | node-stores:u         

The data shows, that ssca2 has a much higher L1 data cache miss rate then bt_npb. There could be potential for optimization.  
For LLC its quite the oposite, with bt_npb at about 52% load and 62% prefetch misses.  
Branch prediction is for both programs pretty bad, with ssca2 at 185% branch load misses and bt_npb at 99%.

All other events don't show significant numbers.

Perburtation is much better with perf, as it only reads hardware counters. There is no noticable difference in execution times for both programs.

Submission
----------
Please submit your solutions by email to peter.thoman at UIBK, using the string "[Perf2024-sheet4]" in the subject line, before the start of the next VU at the latest.  
Try not to include attachments with a total size larger than 2 MiB.
