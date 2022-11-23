# API Project 2020/2021

Project for Algorithms and Data structure exam

Grade: 30L/30  
Prof: Davide Martinenghi

<img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/c/c-original.svg" width="30"/>

## GraphRanker
The goal of the project is the management of a ranking between weighed directed graphs. Chart tracks "best" k graphs.
The program to be realized receives in input two parameters, only once (on the first row of the file, separated by space) 
- d: the number of nodes of the graphs
- k: the length of the ranking

A sequence of commands between
- Aggiungigrafo [matrix] 
- Topk

d, k and the number of graphs are representable with 32-bit integers.

![C](https://img.shields.io/badge/C-A8B9CC?logo=C&logoColor=white&style=for-the-badge)

### AggiungiGrafo

It requires adding a graph to those considered to draw up the ranking. It is followed by the graph’s own adjacency matrix, printed one line for each row, with elements separated by commas.
The nodes of the graph are to be considered logically labeled with an integer index between 0 and d-1; the node in position 0 is the one whose outgoing star is described from the first row of the matrix.


### TopK

Consider every graph from the start of the program to the Topk command labeled with an integer index corresponding to the number of graphs read before it (starting from 0)
Topk requires the program to print integer indices of k graphs having k values smaller than the following metric:
- Sum of the shortest paths between node 0 and all other nodes in the graph reachable from 0
- If there are several graphs with the same value of the metric, it gives precedence to the first ones
- Node distances not reachable from 0 are considered null
- Whole indices are printed, on a single staff, separated by a space, in any order
