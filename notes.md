# Dining philosophers problem

In computer science, the dining philosophers problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them. It was originally formulated in 1965 by Edsger Dijkstra.

The problem was designed to illustrate the challenges of avoiding deadlock, a system state in which no progress is possible.

## Possible solutions
- Allow at most N-1 philosophers to be sitting simultaneously at the table.
- Allow a philosopher to pick up his forks only if both forks are available (to do this he must pick them up in a critical section).
	+ Introducing an arbitrator, e.g., a waiter. In order to pick up the forks, a philosopher must ask permission of the waiter. The waiter gives permission to only one philosopher at a time until the philosopher has picked up both of their forks. Putting down a fork is always allowed.
- Use an asymmetric solution; that is, an odd philosopher picks up first his left fork and then his right fork, whereas an even philosopher picks up his right fork and then his left fork.
	+ Resource hierarchy solution: This solution assigns a partial order to the resources (the forks, in this case), and establishes the convention that all resources will be requested in order, and that no two resources unrelated by order will ever be used by a single unit of work at the same time. Here, the resources (forks) will be numbered 1 through N and each unit of work (philosopher) will always pick up the lower-numbered fork first, and then the higher-numbered fork, from among the two forks they plan to use. The order in which each philosopher puts down the forks does not matter.
