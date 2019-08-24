# Minimum-Cut algorithm
The Stoer–Wagner algorithm is a recursive algorithm to solve the minimum cut problem in undirected weighted graph G with non-negative weights. This implementation runs on $O(n^3)$ time, $n = |V(G)|$.

### Inputs
It's assumed that the input file has the following structure:
1. The first line contains two integers, the number of vertices $n$ and the number of edges $m$ in the graph, separated by spaces.
2. The following $m$ lines contains 3 integers, $u_i, v_i, w_i$, representing the edge between vertex $u_i$ and vertex $v_i$ with weight $w_i$.

### Outputs
The first line of the output file contains the size of the minimum cut. The second one contains the indices of the vertices in the minimum cut separated by spaces. Finally, the third line contains he sum of the edges leaving the cut.

### Running the Code
Open a terminal and run the commands below:
```bash
./compile.sh
./exec.sh <input_file> <output_file>
```
