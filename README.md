# CX-Word-Ladder
Word Ladder program for CX Interview

## Table of Contents

- [About](#about)
- [Features](#features)
- [How It Works](#how-it-works)
- [Getting Started](#getting-started)
  - [What You Need](#what-you-need)
  - [Setting It Up](#setting-it-up)
- [Using the Program](#using-the-program)
  - [Running the Application](#running-the-application)
  - [Running the Tests](#running-the-tests)
- [Project Layout](#project-layout)
- [License](#license)
- [Shoutouts](#shoutouts)

## About

Hello! Welcome to the **Word Ladder** project. This is a C++ application designed to find the shortest path from one word to another by changing one letter at a time. Each intermediate word must be a valid word from a provided list.

## Features

- **Find the Shortest Path:** Uses BFS to efficiently find the quickest transformation from your start word to your end word.
- **Case Insensitive:** Automatically converts all input words to uppercase, so you don't have to worry about letter casing.
- **Helpful Error Messages:** Provides some feedback if something goes wrong or if no ladder exists between your chosen words.
- **Thorough Testing:** Includes unit tests using Google Test
- **Modular Design:** Organized into several classes to keep the code manageable.

## How It Works

Here's a quick overview of the main classes and main.cpp:

1. **WordParser:** Loads and filters words from a file based on the length you need.
2. **NeighborGenerator:** Finds all the words that are one letter different from a given word.
3. **WordFinder:** Uses BFS to search for the shortest path between the start and end words.
4. **WordLadder:** Combines all components, handling initialization and running the ladder calculation. Could be seen as the manager.
5. **Main Program:** Takes your input from the command line and kicks everything off.

## Getting Started

### What You Need

Before you get started, make sure you have the following installed:

- **C++ Compiler:** Supports C++17 or later (e.g., `g++`, `clang++`).
- **CMake:** Version 3.14 or newer.
- **Google Test:** For running the unit tests.
- **Git:** Useful for version control (optional but recommended).

### Setting It Up

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/yourusername/CX-Word-Ladder.git
   cd word-ladder
   ```

2. **If you want to build: Create a Build Directory:**

   Keeping builds separate helps keep things organized.

   ```bash
   mkdir build
   cd build
   ```

3. **Configure with CMake:**

   ```bash
   cmake -DCMAKE_BUILD_TYPE=Release ..
   ```

4. **Build the Project:**

   ```bash
   cmake --build . --config Release
   ```

   Your executable (`wordladder.exe` on Windows or `wordladder` on Unix-based systems) will be in the `build/bin/Release/` folder.

5. **NOTE: Exe files will be included in the repo in case you do not want to build them yourself:**
   Executables will be in the `build/bin/Release/` folder

## Using the Program

### Running the Application

You'll need three things to run the program:

1. **Word List File:** A text file with a list of valid words. Demo files are included in the data folder.
2. **Start Word:** The word you want to start with.
3. **End Word:** The word you want to end with.

**How to Run main program:**
```bash
./wordladder(.exe for windows) <wordListFilePath> <startWord> <endWord>
```
**Example:**

If you have a word list called `words.txt`:
```bash
./wordladder ../data/word_list.txt DAMP LIKE
```
**What You'll See:**
Word Ladder: DAMP -> LAMP -> LIMP -> LIME -> LIKE
(If there's no possible ladder: No word ladder was found based on input.)


**How to Run test program:**
```bash
./wordladder_tests(.exe for windows)
```