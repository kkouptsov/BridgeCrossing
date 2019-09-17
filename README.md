
### Quick start

```
$ cd src
$ make
$ ./run-tests ../tests/scala.yaml
```

To compile you will need "YAML parser and emitter in C++": https://github.com/jbeder/yaml-cpp

### Introduction

This is a classical puzzle about crossing the river by several people over a narrow bridge.

*A group of people walking together in a forest at night encounters a bridge that they have to cross. The bridge can hold only two people at a time. The group has one torch, which must be used to cross the bridge. People can walk with different speed, so each person needs different time to cross the bridge. When crossing the bridge, a pair of people walks at the slowest person's pace. What is the minimum time the group can cross the bridge?*

A classical setup, for example as [mentioned in Wikipedia](https://en.wikipedia.org/wiki/Bridge_and_torch_problem), involves four people, A, B, C, and D with times to cross the bridge 1, 2, 5, and 8 minutes correspondingly. Other formulations use crossing times `{1, 2, 5, 10}`, `{1, 2, 4, 10}`, or `{1, 4, 5, 10}`. The problem can be easily extended to more people, which have to cross the bridge under the same conditions.

There have been numerous rigorous studies of the problem. In the `/doc` directory there are three articles that I found useful: [Calude](https://github.com/kkouptsov/BridgeCrossing/blob/master/doc/Calude%20-%20The%20Bridge%20Crossing%20Problem.pdf), [Rote](https://github.com/kkouptsov/BridgeCrossing/blob/master/doc/Rote%20-%20Crossing%20the%20bridge%20at%20night.pdf), and [Ranu](https://github.com/kkouptsov/BridgeCrossing/blob/master/doc/Ranu%20-%20Optimization%20Rules%20in%20DLV%20for%20the%20Bridge%20Crossing%20Problem.pdf).

The sources mentioned above use different formulations of the problem, with four and more people in the group, and provide optimal crossing times among other things. This data, albeit unreliable, may serve as a test cases for the solver algorithm to be written. This data was harvested into several files in the `/tests` directory. Most of the sources contain crossing times, which was chosen as a default. If some example contained bridge length and walking speeds, the data has also been converted to a list of crossing times.

The choice of the crossing strategy depends on the values of crossing times. Several crossing strategies have been identified:

* __Piggyback strategy__: the fastest person escorts the others one at a time.

* __Non-piggyback strategy__: two slowest persons, who have not yet crossed, travel together. This offsets time wasted on traveling each person separately. However, additional crossings are needed to bring the torch back.

* __Mixed strategy__: there are cases when an optimal solution switches between two strategies above.

### Analysis

To do computations under conditions of this problem, for example to find crossing time or an optimal strategy, one has to be able to represent sequential states of the problem: where people and torch are after each crossing (move). One way is to use binary representation: one bit for each person and one bit for the torch. 

Let us suppose that the group of people crosses the bridge from "left" to "right". Let us denote "left" as `0` and "right" as `1`. Similarly for the torch. However, since the torch is special, I would like to separate it from the rest of representation. Let us denote the torch on the left side as `L` and on the right side as `R`.

Before any crossing the group of four people can be written as `0000L` (state __code__). When the first person crosses the bridge (with the torch), the state becomes `1000R`. And so on.

During crossing of the bridge the states change from `L` to `R` and back to `R`, making a __path__, a sequence of codes.

While for a group of `N` people the number of possible distributions of people over two sides of the river is clearly `2^N`, not all such states are realizable. For example, `0000R` is impossible because it is not allowed to throw the torch over the river.

It can be shown that crossing of one person from left to right is not optimal because the path with such crossing together with bringing the torch back can be reduced to a more optimal path which does not have such crossings. Similarly, crossing of two people from right to left is not optimal because it moves us farther from the goal to have all people on the right.

Thus, the only moves worth considering are two people crossing from left to right and one person crossing from right to left to bring back the torch.

The moves can be enumerated. For example, for the problem of four people, the possible first moves `L->R` are:

```
0000L -> {1100R, 1010R, 1001R, 0110R, 0101R, 0011R}
```

and for each of the these cases the following `R->L` move has only two possibilities:

```
1100R -> {1000L, 0100L}
```

(`1100R -> 0100L` means that the first person took the torch and crossed the bridge back.)

Each such move has an associated weight, which is the number of minutes spent on crossing. Thus, the states and transitions between them can be viewed as directed graph. (Directed because we eliminated moves such as `0100L -> 1100R`, where one person crosses the bridge, as non-optimal.)

One possible way to find the optimal strategy is to enumerate all the paths and choose the one with the smallest cost. 

A mockup of this algorithm is done in [`python/direct.py`](https://github.com/kkouptsov/BridgeCrossing/blob/master/python/direct.py). Starting from the initial "left" state, all possible moves are enumerated, and for each new "right" state all possible moves back are enumerated. The algorithm recursively continues until the end state `1111R` is encountered. Due to eliminated back-moves, the transition graph is acyclic, so the recursion will eventually stop.

The algorithm has terrible complexity and is suitable only for relatively small input data (4-5 hikers). This method, however, emunerates all possible paths with their weights thereby rigorously arriving at the optimal path (proof by enumeration). The path such obtained can be used as a reliable test case for a more optimal algorithm.

Another, more efficient, method is based on Dijkstra's shortest path algorithm. A mockup of this method is done in [`/python/dijkstra.py`](https://github.com/kkouptsov/BridgeCrossing/blob/master/python/dijkstra.py).

Typically, for Dijkstra's algorithm we have a list of nodes of the graph and a list of edges with their weight. For the "bridge and torch" problem, this approach is not feasible. It makes no sense to enumerate all nodes because some of them may not be accessed, and similarly for the edges. The code uses a modified algorithm where adjacent edges and their weights are generated (discovered) when a specific node is processed. Then, discovered state codes are used to create a node object, which together with the weight and other parameters is stored in a hashmap. The state code (a string) is used as a key to identify the node object: 

```
all_nodes["1011R'] = <node, weight, flags, ...>
```

Why it is done this way? The state code (for example '1011R') can be generated in various ways when enumerating achievable states. But for every such code there must exist only one node object.

After the Dijkstra' algorithm finishes, `all_nodes` will contains all discovered nodes. In order to get the optimal path, the node object must store the backtrace information. The optimal path can then be recovered by starting from the end node and tracing back to the beginning.

### Implementaton

C++ code implements Dijkstra's algorithm. It is structured similarly to the mockup python code.

The input of the program is the `.yaml` test file, which contains several separate problem setiings (test cases). The `main.cpp` code uses [`yaml-cpp`](https://github.com/jbeder/yaml-cpp) library to extract individual problem parameters.

`test.{h,cpp}` runs an individual test. It implements Dijkstra's algorithm.

`state.{h,cpp}` implement `class State` to work with the state representation (code), including enumeration of neighbor states.

`node.{h,cpp}` implement `class Node` as an object to store node parameters. Node also contains static map to store all encountered nodes.

### Example

Compute optimal path from `00..0L` to `11..1R`.

```
$ ./run-tests ../tests/scala.yaml
Test: 25
Computed crossing time: 17
Expected crossing time: 17
Test suceeded.
0000L 1100R 0100L 0111R 0011L 1111R
----------------------------------------------------
Test: 26
Computed crossing time: 132.5
Expected crossing time: 132.5
Test suceeded.
00000L 11000R 01000L 01011R 00011L 11011R 01011L 11111R
----------------------------------------------------
Test: 27
Computed crossing time: 40.5
Expected crossing time: 40.5
Test suceeded.
000000L 110000R 010000L 011010R 001010L 111010R 011010L 011111R 001111L 111111R
```

PS. Other test cases may not necessarily succeed because the expected crossing times were not confirmed by other computations, so may be wrong.


