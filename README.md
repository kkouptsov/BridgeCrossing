
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

Two crossing strategies have been identified:

* __Piggyback strategy__: the fastest person escorts the others one at a time.

* __Non-piggyback strategy__: two slowest persons, who have not yet crossed, travel together. This offsets time wasted on traveling each person separately. however, additional arrangements are needed to bring the torch back.

Choice if the strategy depends on the values of crossing times. There are cases when an optimal solution switches from one strategy to another.

### Analysis



### Implementaton


