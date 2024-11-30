# Dijkstra's Algorithm: Adjacency List vs Adjacency Matrix

This section of the repository focuses on the implementation and analysis of **Dijkstra's Algorithm** using two different graph representations: **Adjacency Lists** and **Adjacency Matrices** in C++. I have developed both methods and thoroughly tested their performance.

## Data Structures

The data structures implemented in this repository include:

- **Adjacency List Graph**: Represents the graph using lists where each vertex maintains a list of its adjacent vertices and edge weights. This is efficient for sparse graphs.

- **Adjacency Matrix Graph**: Represents the graph using a 2D matrix where each cell `(i, j)` contains the weight of the edge between vertex `i` and vertex `j`. This can be more efficient for dense graphs.

## Code

The code includes:

- **Graph.h**: Classes for the graph representations using adjacency lists and adjacency matrices.

- **Dijkstra.h**: Implementation of Dijkstra's Algorithm for both graph representations.

- **Random_Graph.h**: Functions to generate random graphs with specified densities.

- **Test.h**: Functions to measure the performance of Dijkstra's Algorithm on the generated graphs.

- **Main Program**: Provides functionality to generate graphs, execute Dijkstra's Algorithm, and measure execution time. It outputs the results for analysis.

## Experiments

My examination covers:

- **Performance Timing**: Measured the time taken to compute the shortest paths using Dijkstra's Algorithm with both graph representations.

- **Graph Density Analysis**: Investigated how different graph densities (sparse to dense) affect performance and memory usage.

- **Graph Size Variation**: Tested graphs of various sizes to evaluate scalability.

## Results and Report

Findings and analyses are compiled into the `Dijkstra_Algorithm_Report.pdf`, which includes:

- **Detailed Explanations**: Discussion of the implementations and the differences between adjacency lists and adjacency matrices.

- **Performance Metrics**: Graphs and charts demonstrating execution times under various conditions.

- **Comparative Analysis**: Highlighting the strengths and weaknesses of each graph representation in the context of Dijkstra's Algorithm.

The report offers insights into the practical considerations of choosing appropriate data structures based on application requirements.

**Note**: All tests and benchmarks are conducted with a focus on transparency and academic rigor.
