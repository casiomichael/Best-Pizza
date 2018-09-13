# Best-Pizza
A Computer Architecture (ECE250) assignment that reads a file input to identify the most cost-effective pizza one can order.

- This assignment was programmed in C and utilizes an insertion sort algorithm to return the list of pizzas in descending order of pizza-per-dollar. 
- This algorithm utilizes dynamic allocation/deallocation of memory to properly sort the given input.
- To mitigate the divide-by-zero situation, if the cost of the pizza is zero, the pizza-per-dollar is simply zero.
- To run tests, run ./bestPizza tests/bestPizza_input_#.txt where # is the file number. Each file input has a different set of pizzas.
