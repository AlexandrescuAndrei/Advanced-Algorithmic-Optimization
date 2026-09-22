# Advanced-Algorithmic-Optimization

A collection of advanced algorithmic problems implemented in **C++**, focused on optimization techniques, dynamic programming, mathematical preprocessing, and efficient search strategies.

The repository contains four independent competitive-programming-style problems: `feribot`, `stocks`, `prinel`, and `crypto`. Each problem requires a different algorithmic model, and the main challenge is identifying the structure that makes an efficient solution possible rather than attempting a direct brute-force approach.

The implementations cover binary search over a solution space, greedy feasibility checks, multidimensional dynamic programming, 0/1 knapsack, divisor-based state generation, mathematical preprocessing, wildcard handling, and subsequence-counting dynamic programming.

Together, the problems provide practice with designing states and transitions, proving monotonicity, transforming problems into known algorithmic models, reducing unnecessary computation, and analyzing both time and memory complexity.

## Ferry Load Optimization

The `feribot.cpp` problem asks for the minimum possible maximum load when a sequence of cars must be distributed across at most `k` ferries.

Instead of directly trying every possible partition of the cars, the implementation transforms the optimization problem into a decision problem.

For a candidate value `x`, the question becomes:

Can all cars be distributed in their original order using at most `k` ferries if no ferry is allowed to carry a total weight greater than `x`?

This condition can be checked greedily.

The cars are processed from left to right while maintaining the current ferry load. As long as another car can be added without exceeding the candidate limit, it is placed on the same ferry.

When the next car would cause the load to exceed the limit, a new ferry is started.

After processing the complete sequence, the number of ferries required tells us whether the candidate capacity is feasible.

The important property is monotonicity.

If a capacity `x` is large enough, then every capacity larger than `x` is also large enough.

Similarly, if `x` is too small, then every smaller capacity is also impossible.

This makes the solution space suitable for binary search.

The lower search bound is the maximum individual car weight because every car must fit on some ferry.

The upper search bound is the sum of all car weights, corresponding to the largest capacity that could ever be necessary.

For every middle value, the greedy validation is executed.

If the candidate works, it becomes a possible answer and the binary search continues toward smaller values.

If it fails, the search continues toward larger values.

This is a classic example of **binary search on the answer**, where binary search is applied not to an already sorted array, but to a monotonic predicate defined over possible solution values.

The complexity is approximately `O(n log S)`, where `n` is the number of cars and `S` is the sum of all car weights.

## Stock Portfolio Optimization

The `stocks.cpp` problem models an investment optimization problem with two simultaneous constraints.

Each stock is described by:

- its current price
- its minimum possible future price
- its maximum possible future price

From these values, the implementation derives the potential profit and the possible loss associated with purchasing that stock.

The potential profit is:

`maximum_price - current_price`

while the potential loss is:

`current_price - minimum_price`

The objective is to maximize the total potential profit while respecting both a total investment budget and a maximum accepted loss.

This turns the problem into a **two-dimensional 0/1 knapsack-style optimization**.

The dynamic programming state is represented by a matrix where a state stores the best profit obtainable for a particular amount of invested money and a particular amount of accepted loss.

Initially, all states are marked as unreachable except the state representing zero investment and zero loss.

Each stock is then processed exactly once.

For every currently reachable state, the implementation checks whether purchasing the current stock would remain inside both constraints.

If the transition is valid, a new state is created with:

- increased investment
- increased possible loss
- increased potential profit

An auxiliary matrix is used while processing each stock.

This is important because updates produced using the current stock must not immediately be reused during the same iteration.

Without this separation, the same stock could effectively be selected multiple times.

After all transitions for one stock have been evaluated, the auxiliary matrix becomes the new dynamic programming table.

The final answer is the largest profit found anywhere in the table because neither the budget nor the maximum loss has to be consumed exactly.

The solution has time complexity `O(n * B * L)`, where:

- `n` is the number of stocks
- `B` is the investment budget
- `L` is the maximum accepted loss

This problem demonstrates how an optimization problem with several independent constraints can be modeled by adding another dimension to the dynamic programming state.

## Prinel and Operation-Cost Preprocessing

The `prinel.cpp` problem combines mathematical preprocessing with a knapsack optimization.

The solution is split into two major stages.

The first stage determines the minimum number of operations required to reach every relevant target value starting from `1`.

A valid operation transforms a current value `i` into:

`i + d`

where `d` is a divisor of `i`.

Instead of solving this transformation problem independently for every target, the implementation calculates the minimum number of operations for all values up to the largest target.

A distance vector is created and initialized with a large value.

The starting state is:

`dist[1] = 0`

The values are then processed in increasing order.

For every reachable value `i`, its divisors are enumerated.

To avoid checking all numbers between `1` and `i`, divisors are generated in pairs by iterating only up to `sqrt(i)`.

If `d` divides `i`, then both:

`d`

and:

`i / d`

are available as divisors.

Each divisor can generate a possible next value, and the corresponding distance is relaxed when a shorter path is found.

After this preprocessing phase, the number of operations required for a target is available directly through:

`dist[target[i]]`

The original problem can then be transformed into a 0/1 knapsack problem.

Each target acts as an item.

Its cost is the number of operations required to reach it.

Its value is the number of points associated with that target.

The total number of available operations becomes the knapsack capacity.

A one-dimensional dynamic programming vector is used, where each position stores the maximum number of points obtainable using the corresponding number of operations.

The vector is traversed backwards for every item.

This reverse traversal is essential because each target can be selected at most once.

Processing capacities from large to small prevents a state updated by the current item from being reused immediately during the same iteration.

The final answer is the maximum value found in the dynamic programming vector.

The preprocessing phase has complexity approximately `O(T * sqrt(T))`, where `T` is the largest target value.

The knapsack phase has complexity `O(n * k)`, where `k` is the maximum allowed number of operations.

This problem is particularly interesting because the main optimization cannot be solved directly until a separate graph-like transformation problem has first been converted into item costs.

## Crypto and Subsequence Counting

The `crypto.cpp` problem uses dynamic programming to count how many ways a target string can be obtained as a subsequence of another string containing wildcard characters.

The source string `K` may contain the character `?`.

A wildcard can represent any distinct character appearing in the target string `S`.

Because the number of valid possibilities can become extremely large, all calculations are performed modulo:

`1,000,000,007`

The dynamic programming state is based on prefixes.

Conceptually:

`dp[i][j]`

represents the number of ways in which the first `j` characters of `S` can be formed using only the first `i` characters of `K`.

Every processed source character produces two main possibilities.

The first possibility is to ignore the current source character with respect to the subsequence.

If the character is a normal character, the existing number of possibilities is propagated.

If the source character is `?`, it may take any value from the distinct-character set extracted from `S`.

Therefore, the number of possibilities that do not extend the target prefix is multiplied by the number of distinct target characters.

The second possibility is to use the current source character as the next character of the subsequence.

This transition is available when:

- the current character in `K` matches the next required character in `S`, or
- the current character in `K` is `?`

When that happens, the number of ways for the shorter target prefix contributes to the state representing one additional matched character.

The algorithm processes the strings from left to right, so the ordering requirement of a subsequence is naturally preserved.

After the entire source string has been processed, the state representing the complete source prefix and the complete target prefix contains the answer.

The complexity is `O(n * l)`, where:

- `n` is the length of `K`
- `l` is the length of `S`

The problem extends the classical subsequence-counting dynamic programming technique by introducing wildcard characters and multiple possible substitutions.

## Dynamic Programming Design

Several problems in the repository depend on dynamic programming, but their states represent very different ideas.

In `stocks.cpp`, the state contains two independent resource constraints: invested money and accepted loss.

In `prinel.cpp`, the final optimization is a one-dimensional knapsack whose item costs are themselves produced by a separate preprocessing algorithm.

In `crypto.cpp`, the state represents how much of two string prefixes has already been processed.

This highlights one of the most important parts of dynamic programming: choosing the correct state representation.

Once the state has been defined correctly, the next step is determining which previous states can contribute to it and in what order transitions must be processed.

The direction of iteration is also important.

For example, the backwards traversal used in the knapsack stage of `prinel.cpp` ensures that each item is selected at most once.

Similarly, `stocks.cpp` uses a separate auxiliary table while processing an item to prevent repeated selection of the same stock.

These implementation details are part of the algorithm itself rather than only coding choices.

## Search-Space Reduction

The repository also contains several examples of reducing a very large solution space before performing the actual optimization.

The ferry problem could theoretically consider many possible partitions of the car sequence.

Instead, monotonicity reduces the problem to binary search over possible maximum capacities.

The Prinel problem could independently search for a transformation sequence for every target.

Instead, all required operation counts are precomputed once and later reused.

The Crypto problem could attempt to enumerate wildcard assignments and subsequence selections separately.

Instead, both sources of combinatorial growth are encoded inside a polynomial-size dynamic programming table.

This kind of transformation is central to efficient algorithm design.

The goal is not simply to make an existing brute-force approach faster, but to find a representation that avoids enumerating the exponential search space entirely.

## Complexity Considerations

Each solution was designed around the constraints of its corresponding problem.

The main complexities are:

- `feribot.cpp` — `O(n log S)`, where `S` is the sum of car weights
- `stocks.cpp` — `O(n * B * L)`
- `prinel.cpp` — approximately `O(T * sqrt(T) + n * k)`
- `crypto.cpp` — `O(n * l)`

The repository therefore includes problems whose efficient solutions depend on recognizing different complexity patterns.

Binary search reduces a numerical search space logarithmically.

Dynamic programming converts repeated combinatorial subproblems into table lookups.

Preprocessing avoids repeating the same expensive calculation for multiple targets.

Divisor enumeration reduces the number of mathematical candidates that have to be checked.

These decisions are essential for keeping the solutions within practical execution limits.

## Project Structure

The repository contains four standalone C++ programs:

- `feribot.cpp` — minimum maximum ferry load using binary search on the answer and greedy feasibility checking
- `stocks.cpp` — portfolio optimization using two-dimensional dynamic programming
- `prinel.cpp` — divisor-based minimum-operation preprocessing followed by 0/1 knapsack
- `crypto.cpp` — wildcard-aware subsequence counting using string dynamic programming
- `README` — original explanations and complexity analysis for the four problems

Each `.cpp` file contains its own `main` function and represents a completely independent algorithmic problem.

The programs use file-based input and output:

- `feribot.in` → `feribot.out`
- `stocks.in` → `stocks.out`
- `prinel.in` → `prinel.out`
- `crypto.in` → `crypto.out`

## Build and Run

Each program can be compiled independently using a modern C++ compiler such as GCC.

Because every source file contains its own entry point, there is no single executable for the entire repository.

To run a particular solution, the corresponding input file must be placed in the working directory using the filename expected by that program.

The compiled executable reads the problem data, computes the solution, and writes the result to the associated output file.

The implementations rely primarily on the C++ Standard Library, including containers such as `vector` and `set`, together with file streams and standard integer arithmetic.

## Technologies and Concepts

- C++
- Advanced algorithm design
- Competitive programming
- Optimization problems
- Binary search
- Binary search on the answer
- Monotonic predicates
- Greedy feasibility checking
- Dynamic programming
- Multidimensional dynamic programming
- State design
- Transition design
- 0/1 knapsack
- Multidimensional knapsack
- Mathematical preprocessing
- Divisor enumeration
- Distance relaxation
- Search-space reduction
- Subsequence counting
- String dynamic programming
- Prefix-based dynamic programming
- Wildcard processing
- Modular arithmetic
- Complexity analysis
- Time complexity
- Memory complexity
- `std::vector`
- `std::set`
- File I/O
- GCC
