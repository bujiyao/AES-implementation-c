#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "AES.c"  // Include your AES implementation

// Helper function to print test results
void assert_test(const char *test_name, int condition) {
    if (condition) {
        printf("[PASS] %s\n", test_name);
    } else {
        printf("[FAIL] %s\n", test_name);
    }
}

// Helper function to print 16-byte arrays
void print_array(const char *label, uint8_t *data, size_t len) {
    printf("%s", label);
    for (size_t i = 0; i < len; i++) {
        printf("%02x ", data[i]);
    }
    printf("\n");
}

// Test AddRoundKey function
void test_add_round_key() {
    uint8_t state[16] = {
        0x01, 0x02, 0x03, 0x04,
        0x05, 0x06, 0x07, 0x08,
        0x09, 0x0a, 0x0b, 0x0c,
        0x0d, 0x0e, 0x0f, 0x10
    };
    uint8_t key[16] = {
        0x05, 0x05, 0x05, 0x05,
        0x05, 0x05, 0x05, 0x05,
        0x05, 0x05, 0x05, 0x05,
        0x05, 0x05, 0x05, 0x05
    };
    uint8_t tmp_state[16];
    memcpy(tmp_state, state, sizeof(tmp_state));
    add_round_key(tmp_state, key);
    add_round_key(tmp_state, key);  // Revert the XOR operation
    assert_test("test_add_round_key", memcmp(tmp_state, state, 16) == 0);
}

// Test SubBytes function
void test_sub_bytes() {
    uint8_t state[16] = {
        0x01, 0x02, 0x03, 0x04,
        0x05, 0x06, 0x07, 0x08,
        0x09, 0x0a, 0x0b, 0x0c,
        0x0d, 0x0e, 0x0f, 0x10
    };
    uint8_t tmp_state[16];
    memcpy(tmp_state, state, sizeof(tmp_state));
    sub_bytes(tmp_state);
    inv_sub_bytes(tmp_state);  // Revert the substitution
    assert_test("test_sub_bytes", memcmp(tmp_state, state, 16) == 0);
}

// Test ShiftRows function
void test_shift_rows() {
    uint8_t state[16] = {
        0x01, 0x02, 0x03, 0x04,
        0x05, 0x06, 0x07, 0x08,
        0x09, 0x0a, 0x0b, 0x0c,
        0x0d, 0x0e, 0x0f, 0x10
    };
    uint8_t expected[16] = {
        0x01, 0x06, 0x0b, 0x10,
        0x05, 0x0a, 0x0f, 0x04,
        0x09, 0x0e, 0x03, 0x08,
        0x0d, 0x02, 0x07, 0x0c
    };
    shift_rows(state);
    assert_test("test_shift_rows", memcmp(state, expected, 16) == 0);
}

// Test InvShiftRows function
void test_inv_shift_rows() {
    uint8_t state[16] = {
        0x01, 0x06, 0x0b, 0x10,
        0x05, 0x0a, 0x0f, 0x04,
        0x09, 0x0e, 0x03, 0x08,
        0x0d, 0x02, 0x07, 0x0c
    };
    uint8_t expected[16] = {
        0x01, 0x02, 0x03, 0x04,
        0x05, 0x06, 0x07, 0x08,
        0x09, 0x0a, 0x0b, 0x0c,
        0x0d, 0x0e, 0x0f, 0x10
    };
    inv_shift_rows(state);
    assert_test("test_inv_shift_rows", memcmp(state, expected, 16) == 0);
}

// Test MixColumns function
void test_mix_columns() {
    uint8_t state[16] = {
        0x87, 0x6E, 0x46, 0xA6,
        0xF2, 0x4C, 0xE7, 0x8C,
        0x4D, 0x90, 0x4A, 0xD8,
        0x97, 0xEC, 0xC3, 0x95
    };
    uint8_t expected[16] = {
        0x47, 0x37, 0x94, 0xED,
        0x40, 0xD4, 0xE4, 0xA5,
        0xA3, 0x70, 0x3A, 0xA6,
        0x4C, 0x9F, 0x42, 0xBC
    };
    mix_columns(state);
    assert_test("test_mix_columns", memcmp(state, expected, 16) == 0);
}

// Test InvMixColumns function
void test_inv_mix_columns() {
    uint8_t state[16] = {
        0x47, 0x37, 0x94, 0xED,
        0x40, 0xD4, 0xE4, 0xA5,
        0xA3, 0x70, 0x3A, 0xA6,
        0x4C, 0x9F, 0x42, 0xBC
    };
    uint8_t expected[16] = {
        0x87, 0x6E, 0x46, 0xA6,
        0xF2, 0x4C, 0xE7, 0x8C,
        0x4D, 0x90, 0x4A, 0xD8,
        0x97, 0xEC, 0xC3, 0x95
    };
    inv_mix_columns(state);
    assert_test("test_inv_mix_columns", memcmp(state, expected, 16) == 0);
}

// Test aes_encrypt and aes_decrypt functions
void test_aes_encrypt_decrypt() {
    uint8_t text[16] = {
        0x01, 0x23, 0x45, 0x67,
        0x89, 0xab, 0xcd, 0xef,
        0xfe, 0xdc, 0xba, 0x98,
        0x76, 0x54, 0x32, 0x10
    };
    uint8_t key[16] = {
        0x0f, 0x15, 0x71, 0xc9,
        0x47, 0xd9, 0xe8, 0x59,
        0x0c, 0xb7, 0xad, 0xd6,
        0xaf, 0x7f, 0x67, 0x98
    };
    uint8_t cipher_text[16] = {0};
    uint8_t decrypted_text[16] = {0};
    aes_context ctx;

    aes_set_key(&ctx, key, 128);
    aes_encrypt_block(&ctx, cipher_text, text);
    aes_decrypt_block(&ctx, decrypted_text, cipher_text);

    assert_test("test_aes_encrypt_decrypt", memcmp(text, decrypted_text, 16) == 0);
}

// Main function to execute all tests
int main() {
    printf("Running AES unit tests:\n");
    test_add_round_key();
    test_sub_bytes();
    test_shift_rows();
    test_inv_shift_rows();
    test_mix_columns();
    test_inv_mix_columns();
    test_aes_encrypt_decrypt();
    printf("All tests completed.\n");
    return 0;
}
