
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

Choice if the crossing strategy depends on the values of crossing times. Several crossing strategies have been identified:

* __Piggyback strategy__: the fastest person escorts the others one at a time.

* __Non-piggyback strategy__: two slowest persons, who have not yet crossed, travel together. This offsets time wasted on traveling each person separately. however, additional arrangements are needed to bring the torch back.

* __Mixed strategy__: there are cases when an optimal solution switches between two strategies above.

### Analysis

To do computations under conditions of this problem, for example to compute crossing time or to find an optimal strategy, one has to be able to represent sequential states of the problem: what happens after each crossing (or move). One way is to use binary representation. Use one bit for each person and one bit for the torch. 

Let us suppose that the group of people crosses the bridge from "left" to "right". Let us denote "left" as `0` and "right" as `1`. Similarly for the torch. However, since the torch is special, I would like to separate it from the rest of representation. Let us denote the torch on the left side as `L` and on the right side as `R`.

Before any crossing the group of four people can be written as `0000L`. When the first person crosses the bridge (with the torch), the state becomes `1000R`. And so on.

During crossing of the bridge the states change from `L` to `R` and back to `R`, making a __path__.

While for a group of `N` people the number of possible distributions of people over two sides of the river is clearly `2^N`, not all such states are realizable. For example, `0000R` is impossible because it is not allowed to throw the torch over the river.

It can be shown that crossing of one person from left to right is not optimal because the strategy with such crossing together with bringing the torch back can be reduced to a more optimal strategy which does not have such crossings. Similarly, crossing of two people from right to left is not optimal because it moves us farther from the goal to have all people on the right.

Thus, the only moves worth considering are moving two people from left to right and having one person to move from right to left to bring back t he torch.

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



### Implementaton


