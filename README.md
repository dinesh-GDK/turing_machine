# Turing Machine Simulator

A lightweight two-symbol Turing machine emulator written in C.

## Overview

This simulator executes Turing machine programs defined by instruction cards operating on a binary tape. It supports standard Turing machine operations: read, write, move (left/right/stay), and state transitions. The program visualizes each computational step and reports the final tape state.

## Quick Start

```bash
# Compile
gcc main.c -o turing.out

# Run
./turing.out -c <cards_file> -t <tape_file> [options]

# Example: 3-state Busy Beaver
./turing.out -c cards/bb3.txt -t tapes/bb.txt

# Example: with step-by-step output
./turing.out -c cards/bb3.txt -t tapes/bb.txt -p

# Example: with custom step limit
./turing.out -c cards/bb4.txt -t tapes/bb.txt -m 50000

# Show help
./turing.out -h
```

## Input Files

### Instruction Cards

Each card defines the machine's behavior for a given state. Format:

```
<card_id>
<write_0> <move_0> <next_0>
<write_1> <move_1> <next_1>
```

| Field | Description |
|-------|-------------|
| `card_id` | State identifier (integer) |
| `write_x` | Symbol to write (0 or 1) |
| `move_x` | Head movement: `L` (left), `R` (right), `S` (stay) |
| `next_x` | Next state to transition to |

**Example** (`cards/bb3.txt`):
```
1
1 R 2
1 L 3

2
1 L 1
1 R 2

3
1 L 2
1 S 0
```

**Notes:**
- Card `0` is the **HALT** state
- The first card in the file is the **entry point**
- Append multiple cards without blank lines between them

### Initial Tape

Space-separated binary symbols:

```
0
```

or

```
1 0 1 1 0 1
```

## Output

The simulator displays:
- Validated cards and tape
- Step-by-step tape evolution
- Final tape state
- Count of `1` symbols on the tape

## Examples Included

| Program | Cards File | Tape File | Description |
|---------|-----------|-----------|-------------|
| Unary Addition | `cards/unary_addition.txt` | `tapes/unary_addition.txt` | Adds two unary numbers |
| Busy Beaver (1-state) | `cards/bb1.txt` | `tapes/bb.txt` | Writes 1 one |
| Busy Beaver (2-state) | `cards/bb2.txt` | `tapes/bb.txt` | Writes 4 ones |
| Busy Beaver (3-state) | `cards/bb3.txt` | `tapes/bb.txt` | Writes 6 ones |
| Busy Beaver (4-state) | `cards/bb4.txt` | `tapes/bb.txt` | Writes 13 ones |

## Command Line Options

| Option | Long Form | Required | Default | Description |
|--------|-----------|----------|---------|-------------|
| `-c` | `--cards` | Yes | - | Path to instruction cards file |
| `-t` | `--tape` | Yes | - | Path to initial tape file |
| `-m` | `--max-steps` | No | `10000` | Maximum steps before halting |
| `-p` | `--print-steps` | No | off | Print tape at each step |
| `-h` | `--help` | No | - | Show help message |

**Examples:**
```bash
# Basic usage
./turing.out -c cards/bb3.txt -t tapes/bb.txt

# Verbose mode - shows each step
./turing.out -c cards/bb3.txt -t tapes/bb.txt -p

# Custom step limit
./turing.out -c cards/bb4.txt -t tapes/bb.txt -m 50000

# Combined options
./turing.out -c cards/bb4.txt -t tapes/bb.txt -m 50000 -p
```

## License

MIT
