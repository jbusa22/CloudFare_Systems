# EECS 281: Lab 4 - Connected Components

#
## Introduction

This assignment supplements the Union-Find material covered in this lab and gives students the opportunity to implement a Union-Find container using path compression.

## Problem Statement

A graph is a collection of vertices and edges (we will cover graphs in more detail after the midterm). We call a graph connected if there exists a path between every pair of vertices. Similarly, a connected component is a subgraph that is connected, and where no vertex in the subgraph has an edge to a vertex outside the subgraph. For example, in this illustration, there are three connected components:



Image Source: https://en.wikipedia.org/wiki/Connected_component_(graph_theory) 

You are given the scaffolding of a graph abstract data type in connected_components.cpp, and a main() that reads in and constructs a graph given the edges listed in a file. Your task is to write a program that calculates and prints out the number of connected components in the graph represented by the file.

For your convenience in understanding and testing, the input file is formatted as follows, listing each of the edges in the graph:
```
<number of vertices> <number of edges>
<start vertex> <end vertex>
<start vertex> <end vertex>
… // etc… As many as <number of edges> lines
```
For example, the following input:
```
4 2
0 1
0 2
```
describes a graph where vertex 0 is connected to both vertex 1 and vertex 2.


## Submitting to the Autograder

Make sure you write your program in the connected_components.cpp file. You will be able to make three submissions per day. To submit to the autograder, use the Makefile to generate a .tar.gz file. Simply run the following command in the directory of the connected_components.cpp file and Makefile: 
```
make fullsubmit 
```
If you are working with a partner, make sure that both of you submit to the autograder. Only students who submit code to the autograder will receive points. Both of you can submit the same code for this assignment.

Make sure you include the assignment identifier on all code files you submit to the autograder.

## Testing

You will be given three test case files on Canvas. The solutions to these three test cases will not be released in this document. However, if you get any of these cases wrong when you submit to the autograder, the autograder will tell you the solution you got, as well as the correct solution you should have gotten. Thus, it is in your best interest to make your first submission early.

To get an idea of what answers you should be getting for these three test cases, you should expect outputs that fall in the range [1, 10]. If you get anything outside of this range, then you are doing something incorrectly.

However, you may not assume that the answers to all 18 test cases on the autograder will fall into the range [1, 10]. In fact, several of these cases will produce answers that are quite large. In addition, you cannot assume that there is a limit to the number of vertices or edges you will be given. The test cases that are run on the autograder may have vertex or edge counts in the tens of millions.

Since the cases we provide publicly are still quite large, it is important that you also write smaller test files of your own, especially if you aren’t passing the ones that are given. This will simplify the debugging process and will make your life easier. An additional test case is provided below.

To actually run a test, simply use the Makefile provided to make an executable. This executable will be named connected. Running the test_case1.in test, for example, can be done using the command:
```
./connected < test_case1.in
```
## Additional Test Case

Here is an additional test case for debugging:
```
20 15
7 3
7 1
9 2
2 1
1 3
2 4
7 8
16 12
17 11
17 14
14 16
12 10
10 11
11 16
18 13
```
should produce a graph with 8 connected components:
```
{0} 
{1, 2, 3, 4, 7, 8, 9} 
{5} 
{6} 
{10, 11, 12, 14, 16, 17} 
{13, 18} 
{15} 
{19}
```
