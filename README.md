# Bin Packing with GA

This repository contains Genetic Algorithm implementation for Bin Packing problem.

GA uses hyper parameters to place items to bins. Each item is placed with **Heuristic** provided below.

Example input and configuration files are provided inside **example_input** folder.


## Heuristics

- First Fit (FF) 
- Worst Fit (WF)
- Best Fit (BF) 
- Last Fit (LF)
- Next Fit (NF) 
- Filler (FL)
- Djang and Fitch (DJF) 
- Almost Worst Fit (AWF)

## Supported Crossovers

- SinglePoint
- TwoPoint

## Supported Mutations

- SingleBitFlip
- Inversion 
- Flip
- Multiple

## Supported Selections

- RouletteWheel
- Tournament

## Run

If you will not provide command line arguments it will use example input files.

With config file - **config.txt** you can provided arguments such as number of generations, probability of crossover and mutation etc.

```

javac *.java

java ResourceAllocationGA <path to bin file> <path to item file> <path to config file> <path to outputfile>

```