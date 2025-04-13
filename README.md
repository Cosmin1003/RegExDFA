# RegExDFA - Regular Expression to DFA Converter

A C++ implementation of a Deterministic Finite Automaton (DFA) that converts regular expressions into their corresponding automaton representation. This project demonstrates the practical application of formal language theory concepts in computer science.

## Project Description

RegExDFA is a command-line application that:
- Takes a regular expression as input
- Validates the expression
- Constructs the corresponding Deterministic Finite Automaton (DFA)
- Provides functionality to check if words are accepted by the automaton
- Displays the automaton's structure in a human-readable format

The implementation includes:
- A `DeterministicFiniteAutomaton` class that represents the DFA
- Methods for automaton validation, word checking, and visualization
- Regular expression parsing and conversion to DFA
- File-based input/output operations

## Technical Details

The project is implemented in C++ and follows object-oriented programming principles. It demonstrates:
- Formal language theory concepts
- Regular expression parsing
- DFA construction and validation
- File handling
- Command-line interface design

## Features

- **Automaton Validation**: Verifies if the constructed DFA is valid according to formal language theory rules
- **Word Checking**: Determines if a given word is accepted by the automaton
- **Visualization**: Displays the automaton's structure in a clear, readable format
- **File I/O**: Supports reading regular expressions from files and saving automaton representations
- **Error Handling**: Comprehensive error checking for invalid inputs and automaton states

## Usage

1. Compile the project using your preferred C++ compiler
2. Run the executable
3. Input a regular expression when prompted
4. Use the menu to:
   - View the regular expression
   - Display the constructed DFA
   - Check if specific words are accepted by the automaton

## Project Structure

- `DeterministicFiniteAutomaton.h` - Header file containing the DFA class definition
- `DeterministicFiniteAutomaton.cpp` - Implementation of the DFA class
- `main.cpp` - Main program entry point and user interface

## Building the Project

1. Open the solution file `RegExDFA.sln` in Visual Studio
2. Build the solution (F7 or Ctrl+Shift+B)
3. Run the executable from the output directory