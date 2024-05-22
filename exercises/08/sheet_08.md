Exercise Sheet 8
================

A) False Sharing
----------------

Have a look at this git PR:
https://github.com/KhronosGroup/Vulkan-ValidationLayers/pull/5587

Explain the problem it tries to solve, and how it attempts to do so.

---

The idea was to refactor the padding of the lock, to use the stdlib expression for cacheline size, `std::hardware_destructive_interference_size`, and alignas.

The problem he encounters is that this does not yet work for some machines. 

He solves that by writing a wrapper for this expression, which currently only returns a constant, but can be changed in the future to use that expression.

B) Data Structure Selection
---------------------------

Search on Github for a merged pull request in a reasonably sized and popular project (>100 stars) which replaces a data structure in order to improve performance.

Examine the use of this data structure, evaluating all the decision criteria discussed in the lecture, and report your findings.
Do these criteria help indicate that the change in data structure would be beneficial?

---

> https://github.com/OpenModelica/OpenModelica/pull/11344

In this pull request, a new `UnorderedSet` is created to get better performance on making a list unique and sorted.

The original implementation is based on a List.

Criteria from lecture:

**Type of Data:** Int  
**Quantity of Data:** large n  
**Access Type:** n inserts, n accesses, all elements  
**Access Pattern:** Doesn't matter 

The idea behind this pr is, that creating a UnorderedSet is quicker than checking a regular list for duplicates. 
The usage of a set is possible as `Int` has equality. 
For n elements, algorithmical complexity for the original implementation is `O(n^2)` for getting a unique sorted list. 

Inserting into an unordered set can be done in `O(1)` on average, thus `O(n)` for n elements. If sorting is done in `O(n * log n)`, this implementation takes `O(n * log n)`.

This optimization makes sense for big n.

Submission
----------
Please submit your solutions by email to peter.thoman at UIBK, using the string "[Perf2024-sheet8]" in the subject line, before the start of the next VU at the latest.  
Try not to include attachments with a total size larger than 2 MiB.
