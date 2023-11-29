#include <iostream>
#include <bitset>
#include <vector>

// Number of rounds in the Feistel cipher
const int NUM_ROUNDS = 16;

// Feistel cipher key
const uint64_t FEISTEL_KEY = 0x0F0F0F0F0F0F0F0F;

// Feistel function
uint32_t feistelFunction(uint32_t right, uint64_t roundKey) {
    // Example feistel function (XOR with round key)
    return right ^ static_cast<uint32_t>(roundKey);
}

// Feistel cipher round
void feistelRound(uint32_t& left, uint32_t& right, uint64_t roundKey) {
    uint32_t temp = left;
    left = right;
    right = temp ^ feistelFunction(right, roundKey);
}

// Feistel cipher encryption
void feistelEncrypt(uint64_t& block, uint64_t key) {
    uint32_t left = block >> 32;
    uint32_t right = static_cast<uint32_t>(block);

    for (int round = 0; round < NUM_ROUNDS; ++round) {
        feistelRound(left, right, key);
        key = (key << 1) | (key >> 63); // Key schedule (rotation)
    }

    block = (static_cast<uint64_t>(right) << 32) | left;
}

// Feistel cipher decryption
void feistelDecrypt(uint64_t& block, uint64_t key) {
    uint32_t left = block >> 32;
    uint32_t right = static_cast<uint32_t>(block);

    // Reverse the key schedule
    for (int round = 0; round < NUM_ROUNDS; ++round) {
        key = (key >> 1) | (key << 63); // Reverse key schedule (rotation)
        feistelRound(right, left, key);
    }

    block = (static_cast<uint64_t>(right) << 32) | left;
}

int main() {
    std::string inputText = "abcd1234abcd"; // Replace with your input text

    // Pad the input text to ensure it is a multiple of 8 bytes (64 bits)
    while (inputText.size() % 8 != 0) {
        inputText.push_back('\0');
    }

    std::vector<uint64_t> blocks;

    // Convert input text to blocks of 64 bits
    for (size_t i = 0; i < inputText.size(); i += 8) {
        uint64_t block = 0;
        for (int j = 0; j < 8; ++j) {
            block |= static_cast<uint64_t>(inputText[i + j]) << (8 * j);
        }
        blocks.push_back(block);
    }

    // Encryption
    for (uint64_t& block : blocks) {
        feistelEncrypt(block, FEISTEL_KEY);
    }

    // Decryption
    for (uint64_t& block : blocks) {
        feistelDecrypt(block, FEISTEL_KEY);
    }

    // Convert blocks back to characters
    std::string encryptedText;
    for (uint64_t block : blocks) {
        for (int j = 0; j < 8; ++j) {
            encryptedText.push_back(static_cast<char>(block >> (8 * j)));
        }
    }

    // Output results
    std::cout << "Original Text: " << inputText << std::endl;
    std::cout << "Encrypted Text: " << encryptedText << std::endl;
    std::cout << "Decrypted Text: " << inputText << std::endl;

    return 0;
}