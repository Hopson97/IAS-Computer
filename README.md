# ias-computer

## Registers

| Register        | Description                                                                                  |
|-----------------|----------------------------------------------------------------------------------------------|
| Accumulator     | Holds the results of certain operations                                                      |
| Memory Buffer   | Tempory buffer for the memory inside of memory address "memory address register"             |
| Memory Address  | The memory address to fetch the next instruction from                                        |
| Program Counter | Holds the memory address to fetch an instruction from; increments by 1 after a fetch         |
| Instruction     | Holds the contents of "memory buffer register" to have its opcode and address extracted from |

## Opcode

The computer has 3-bit instructions and 5-bit addresses.

This allows up to 8 instructions, and up to 32 memory locations addressable.

For example, `00100110` means "Adds the number stored in memory address `00110` to the accumulator register., because the first 3 bits is the opcode (in this case, 0x1), and the final 5 digits is the memory address (in this case, 0x6).


| Name     | Opcode | Mnemonic | Description                                                                                                                    | Example |
|----------|--------|----------|--------------------------------------------------------------------------------------------------------------------------------|---------|
| Add      | 0x0    | ADD      | Adds the number stored in memory address XX to the accumulator register.                                                       | ADD XX  |
| Subtract | 0x1    | SUB      | Subtracts the number stored in memory address XX from the accumulator register                                                 | SUB XX  |
| Store    | 0x2    | STA      | Stores the number stored in the accumulator to memory address XX                                                               | STA XX  |
| Load     | 0x3    | LDA      | Loads the number stored in memory address XX to the accumulator register                                                       | LDA XX  |
| Input    | 0x4    | INP      | Gets user input, stores result in the accumulator register                                                                     | INP     |
| Output   | 0x5    | OUT      | Outputs the number stored in the accumulator register                                                                          | OUT     |
| Jump     | 0x6    | JIP      | If the value stored in the accumulator register is postive, this instruction will set the program counter to memory address XX | JIP XX  |
| Exit     | 0x7    | END      | Ends the

## Building and Running

### Libraries

SFML is required.

These can be installed from your project manager. For example, on Debian/ Ubuntu:

```sh
sudo apt install libsfml-dev
```

If this is not possible (eg windows), you can install these manually from their respective websites:

https://www.sfml-dev.org/download.php

### Linux

To build, at the root of the project:

```sh
sh scripts/build.sh
```

To run, at the root of the project:

```sh
sh scripts/run.sh
```

To build and run in release mode, simply add the `release` suffix:

```sh
sh scripts/build.sh release
sh scripts/run.sh release
```

You can also create a deployable build (that can be sent) by doing:

```sh
sh scripts/deploy.sh
```
