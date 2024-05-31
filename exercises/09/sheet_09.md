Exercise Sheet 9
================

A) Data Structure Benchmark Design and Implementation
-----------------------------------------------------

Create a benchmark setup which can measure a given set of mixes of insertion/deletion and read/write operations on different containers of arbitrary types and size. (Compare with the "The Dangers of Intuition" slide in the Optimization / Data Structures chapter)  
For the insertion/deletion and read/write categories, ensure a 50%/50% frequency each (i.e., after an even number of insertion/deletion operations the number of elements is the same as at the start). Also implement the requested instruction mix using the minimum spacing possible, that is, for a total of 100 instructions, a ratio of 20% ins/del and 80% read/write should be implemented as

```
read
write
read
write
insertion
read
write
read
write
deletion
... repeat x 10
```

rather than e.g.

```
read
write
... repeat x 40
insertion
deletion
... repeat x 10
```

Make sure to **follow all the best practices regarding benchmark design which we outlined in the lecture**, and try to avoid any perturbation unrelated to the effect we want to measure.

Some additional notes on implementation specifics:

 * Pre-initialize all the data structures to N elements (you may reserve N+1 for the array)
 * Perform linear traversal, wrapping around at the end (you can also, optionally and additionally, benchmark operations at random locations)
 * You are free to select a programming language, but please choose one that compiles a priori to machine code
 * For the write and read operations, ensure that the values are used in some way and not compile-time constants, and that the compiler can not throw away the operations
 * Your number of benchmark iterations should not necessarily be equal to the number of elements of the data structure! E.g. for the 10 and 1000 element cases it should be much larger; one option is to implement a fixed time frame for each benchmark and measure the number of operations completed during that time
 * For linked lists, to simulate a more realistic use case, allocate and free a new element each time insertion/deletion happens (you can also, optionally and additionally, benchmark using a single re-used element)
 * For linked lists, implement 2 different allocation policies: one which allocates the elements in sequence (as in, how they will be connected and traversed), and one which allocates them in a random order.


B) Array-like vs. Linked Lists
------------------------------

Apply your benchmark over the cross product of the following settings. Exclude combinations which would run out of memory.  
Run these benchmarks **on LCC3**, and also on some local hardware available to you.

**Data Structures**: Array, linked list

**Instruction Mix**:
| ins/del | read/write |
| -------:| ----------:|
|     0%  |      100%  |
|     1%  |       99%  |
|    10%  |       90%  |
|    50%  |       50%  |

**Element Size**: 8 Byte, 512 Byte, 8 MB

**Number of Elements**: 10, 1000, 100000, 10000000

Plot and discuss your results.

---

Results are somewhat as expected.
## Plots lcc3 (number of 100 instructions in 5 second):
### Element size = 8 Byte
The expectect result for the following plot would be, that array is the fastest. I think this is not shown in the plot, as there is too much other overhead.  
![](plots_lcc3/repetitions_elem_size_%208_num_elems_10.png)  
Here I didn't think that array would be that much faster. This may be due to caching.  
![](plots_lcc3/repetitions_elem_size_%208_num_elems_1000.png)  
This results stay quite similar, the difference is getting bigger  
![](plots_lcc3/repetitions_elem_size_%208_num_elems_100000.png)
![](plots_lcc3/repetitions_elem_size_%208_num_elems_10000000.png)
### Element size = 512 Byte  
Results are similar as before, but differences between array and linked list are smaller.  
![](plots_lcc3/repetitions_elem_size_%20512_num_elems_10.png)
![](plots_lcc3/repetitions_elem_size_%20512_num_elems_1000.png)
![](plots_lcc3/repetitions_elem_size_%20512_num_elems_100000.png)
![](plots_lcc3/repetitions_elem_size_%20512_num_elems_10000000.png)
### Element size = 8 MByte
difference for linked list disapears, probably as the overhead is bigger for gigantic elements.  
![](plots_lcc3/repetitions_elem_size_%208M_num_elems_10.png)
![](plots_lcc3/repetitions_elem_size_%208M_num_elems_1000.png)


## Plots local (number of 100 instructions in 1 second):
### Element size = 8 Byte
![](plots_local/repetitions_elem_size_%208_num_elems_10.png)
![](plots_local/repetitions_elem_size_%208_num_elems_1000.png)
![](plots_local/repetitions_elem_size_%208_num_elems_100000.png)
![](plots_local/repetitions_elem_size_%208_num_elems_10000000.png)
### Element size = 512 Byte
![](plots_local/repetitions_elem_size_%20512_num_elems_10.png)
![](plots_local/repetitions_elem_size_%20512_num_elems_1000.png)
![](plots_local/repetitions_elem_size_%20512_num_elems_100000.png)
![](plots_local/repetitions_elem_size_%20512_num_elems_10000000.png)
### Element size = 8 MByte
![](plots_local/repetitions_elem_size_%208M_num_elems_10.png)
![](plots_local/repetitions_elem_size_%208M_num_elems_1000.png)

Submission
----------
Please submit your solutions by email to peter.thoman at UIBK, using the string "[Perf2024-sheet9]" in the subject line, before the start of the next VU at the latest.  
Try not to include attachments with a total size larger than 2 MiB.
