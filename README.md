# Teleword Puzzle Solver (C++)

A console-based Teleword Puzzle Solver built using C++ and object-oriented programming concepts. The program reads a 15x15 grid and a list of words from a file, searches for each word in all possible directions (horizontal, vertical, and diagonal), and highlights the results.

## Features

* Searches words in 8 directions
* Step-by-step or instant solving modes
* Colored grid output for found words
* Teleword extraction (remaining letters)
* Statistics:

  * Word length analysis
  * Direction distribution
  * Execution time
  * Heaviest row & column

## Input Format

* A file (`teleword_1.txt`) containing:

  * 15x15 character grid
  * List of words ending with a full stop

## How to Run

1. Compile:

   ```bash
   g++ 22L-6681Proj_1.cpp -o teleword
   ```
2. Run:

   ```bash
   ./teleword
   ```

## Modes

* `S` → Solve completely
* `T` → Step-by-step solving
* `X` → Show statistics

## Concepts Used

* Object-Oriented Programming
* File Handling
* 2D Arrays
* String Processing
* Algorithmic Searching

## Output

* Highlighted puzzle grid
* Found words list
* Teleword (remaining letters)
* Detailed statistics (optional)

---

Simple, efficient, and designed for learning core C++ and problem-solving concepts.
