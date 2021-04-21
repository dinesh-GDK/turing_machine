# Turing Machine
This is a simple program written in C to emulate two symbol turing machine.

## How to use it?
You need two text files to run the program
- Instruction cards
- Initial Tape

## Instruction cards
A regular turing machine instruction card would look something like this

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;**Card Number: 1**
|Symbol | Write | Shift | Next_Card |
| --- | --- | --- | --- |
|0      |  0    |  L    |   2       |
|1      |  1    |  R    |   3       |

First it contains the card number\
Then the actiosn to take when the two symbols are encountered in the tape\
For example in the card shown above\
If `0` is encountered write `0` to the tape, shift left and go to card 2\
If `1` is encountered write `1` to the tape, shift right and go to card 3

So, your text file would look like this
```
1
0 L 2
1 R 3
```
If you need more cards just append them below without any spaces\
:warning: ```The HAULT card number is always `0` ```\
:warning: ```The ENTRY card is the first card in the text file ```\
See the `cards` directory for some reference

## Initial Tape
You must provide a initial tape for the program to execute\
Your text file should contain contents like shown below
```
1 0 1 1 0 1
```
Write the symbols with a single space

## Compile
Compile the `main.c` file using the compiler of your choice
```
gcc main.c -o turing.out
```

## Execute
Then execute the code in the following format
```
./turing.out <path to cards file> <path to tape file>
```
For example
```
./turing.out ./cards/unary_addition.txt ./tapes/unary_addition.txt
./turing.out ./cards/bb3.txt ./tapes/bb.txt
```

I have added some interesting turing machine cards and tapes in the folders
- Unary Addition
- 1-state Busy Beaver
- 2-state Busy Beaver
- 2-state Busy Beaver
- 3-state Busy Beaver
- 4-state Busy Beaver

## Result
You can see how the tape changes at each and every step and also you can see the number of ones written by the machine on the tape
