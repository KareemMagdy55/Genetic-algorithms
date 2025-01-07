# Task Allocation Genetic Algorithm

## Description

This project implements a **Genetic Algorithm (GA)** to solve the **Task Allocation** problem, where tasks must be distributed between two processing cores. Each task has an execution time, and the goal is to minimize the total execution time while ensuring that neither core exceeds a specified time limit. The GA uses techniques like **roulette wheel selection**, **one-point crossover**, **bit-flip mutation**, and **elitism** to evolve optimal task distributions.

### Key Features:
- **Genetic Algorithm** for task allocation between two cores.
- **Binary chromosome representation** for core assignments.
- **Infeasible solution handling** to ensure no core exceeds the time limit.
- Customizable **population size** and **mutation/crossover probabilities**.
- Outputs the best solution for each test case, including the chromosome, evaluation score, and task distribution.

## Problem Description

The task allocation problem involves distributing a set of tasks with known execution times between two cores. The goal is to minimize the total execution time while ensuring that neither core exceeds a specified execution time limit. 

### Input Format

The input consists of multiple test cases. Each test case has the following format:
1. The maximum time limit for each core.
2. The number of tasks to be allocated.
3. A list of integers representing the execution time for each task.

### Output Format

For each test case, the output will display:
- The test case index.
- The best solution found.
- The evaluation score (total fitness).
- The chromosome representation of the solution.
- Tasks assigned to each core and their total execution time.


## How It Works

1. **Initialization**: A population of random chromosomes (solutions) is generated, where each chromosome represents a potential allocation of tasks to the cores.
2. **Selection**: **Roulette Wheel Selection** is used to select individuals (chromosomes) based on their fitness, where lower fitness represents a better solution (less total execution time).
3. **Crossover**: A **one-point crossover** technique is used to combine two parent chromosomes to create offspring with mixed task assignments.
4. **Mutation**: **Bit-flip mutation** is applied to randomly alter the task allocation in a chromosome.
5. **Replacement**: The offspring are evaluated, and if they represent a better solution, they replace the parents in the population.
6. **Termination**: The algorithm terminates after a specified number of generations, and the best solution found is returned.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/KareemMagdy55/Genetic-algorithms.git
   cd Task-Allocation-Genetic-Algorithm
Make sure you have a C++ compiler that supports C++11 or later.

2. Compile the code:
  ```bash
  g++ -o task_allocation main.cpp
  ```


3. Run the program:
  ```bash
  ./task_allocation
