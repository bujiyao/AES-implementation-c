# AES Implementation in C
This repository contains a basic implementation of the Advanced Encryption Standard (AES) in the C programming language. The project demonstrates how AES encryption and decryption processes work in ECB (Electronic Codebook) mode.

## Files Overview

- **AES.c**: Contains the implementation of AES encryption and decryption algorithms.
- **AES.h**: Header file defining the interfaces and constants used in `AES.c`.
- **main.c**: The main program that demonstrates the usage of the AES implementation with different key sizes.
- **test_case.c**: Unit test cases to validate the correctness of the AES implementation.
- **Makefile**: A build script to compile the project easily.

## Features

- **AES Algorithm**: Implements AES encryption and decryption for 128-bit, 192-bit, and 256-bit key sizes.
- **ECB Mode**: Uses the Electronic Codebook (ECB) mode for encryption and decryption.
- **Test Cases**: Includes unit tests to ensure the functionality and correctness of the implementation.
- **Modular Design**: Code is organized into separate files for clarity and maintainability.

## How to Build and Run

To compile and run the project, use the provided `Makefile`. Below are the available commands:

### 1. Compile and Run the Main Program
The main program demonstrates encryption and decryption for 128-bit, 192-bit, and 256-bit keys.

```bash
make main
./main
```

Example Output:
```text
key_bit 128: 
    input  :  01 23 45 67 89 ab cd ef fe dc ba 98 76 54 32 10 
    encrypt:  ff 0b 84 4a 08 53 bf 7c 69 34 ab 43 64 14 8f b9 
    decrypt:  01 23 45 67 89 ab cd ef fe dc ba 98 76 54 32 10 
key_bit 192: 
    input  :  01 23 45 67 89 ab cd ef fe dc ba 98 76 54 32 10 
    encrypt:  66 4e 00 1d 2f cb 6c 48 c5 a7 f1 ac f3 0e 87 a8 
    decrypt:  01 23 45 67 89 ab cd ef fe dc ba 98 76 54 32 10 
key_bit 256: 
    input  :  01 23 45 67 89 ab cd ef fe dc ba 98 76 54 32 10 
    encrypt:  fb 6e ee fe bf ee 19 d8 ce 8b 99 42 73 b5 f0 02 
    decrypt:  01 23 45 67 89 ab cd ef fe dc ba 98 76 54 32 10 
```

### 2. Run Unit Tests
Unit tests validate the correctness of the AES implementation. To compile and execute the tests, use:

```bash
make test
```

Example Output:
```bash
Running AES unit tests:
[PASS] test_add_round_key
[PASS] test_sub_bytes
[PASS] test_shift_rows
[PASS] test_inv_shift_rows
[PASS] test_mix_columns
[PASS] test_inv_mix_columns
[PASS] test_aes_encrypt_decrypt
All tests completed.

```
### 3. Clean Build Files
To clean up the compiled files, use:

```bash
make clean
```

## Learn More About AES
If you'd like to explore these materials, you can refer to the following extended resources that I authored:  
- [AES 基本原理介紹](https://hackmd.io/5vtJGZFLQa-Prx6jw2MbBw)
- [AES Implementation in Chisel](https://hackmd.io/@sysprog/B10iX_eLyg)
