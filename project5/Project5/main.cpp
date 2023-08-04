#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
#include "sm3_self.h"

#define EVP_MAX_MD_SIZE 32
// SM3 hash function declaration
// Function to compute the Merkle root of a list of messages
void computeMerkleRoot(const std::vector<std::vector<uint8_t>>& messages, std::vector<uint8_t>& merkleRoot) {
    if (messages.empty()) {
        return;
    }

    std::vector<std::vector<uint8_t>> tree = messages;

    while (tree.size() > 1) {
        if (tree.size() % 2 != 0) {
            tree.push_back(tree.back());
        }

        std::vector<std::vector<uint8_t>> nextLevel;

        for (size_t i = 0; i < tree.size(); i += 2) {
            std::vector<uint8_t> concatenated(tree[i].size() + tree[i + 1].size());
            std::copy(tree[i].begin(), tree[i].end(), concatenated.begin());
            std::copy(tree[i + 1].begin(), tree[i + 1].end(), concatenated.begin() + tree[i].size());

            uint8_t hash[EVP_MAX_MD_SIZE];
            sm3_hash(concatenated.data(), concatenated.size(), hash);

            std::vector<uint8_t> hashedValue(hash, hash + sizeof(hash));
            nextLevel.push_back(hashedValue);
        }

        tree = nextLevel;
    }

    merkleRoot = tree[0];
}

int main() {
    // Test data
    std::vector<std::vector<uint8_t>> messages = {
        {0x61, 0x62, 0x63},
        {0x64, 0x65, 0x66},
        {0x67, 0x68, 0x69},
        {0x6A, 0x6B, 0x6C},
    };

    std::vector<uint8_t> merkleRoot;

    computeMerkleRoot(messages, merkleRoot);

    // Print the Merkle root
    std::cout << "Merkle Root: ";
    for (const auto& byte : merkleRoot) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    std::cout << std::dec << std::endl;

    return 0;
}

