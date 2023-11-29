#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

// Node structure for the Huffman tree
struct HuffmanNode {
    char data;
    unsigned frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, unsigned frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

// Comparison structure for priority queue
struct CompareNodes {
    bool operator()(HuffmanNode* lhs, HuffmanNode* rhs) {
        return lhs->frequency > rhs->frequency;
    }
};

// Utility function to build the Huffman tree
HuffmanNode* buildHuffmanTree(const std::unordered_map<char, unsigned>& frequencies) {
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNodes> minHeap;

    // Create a leaf node for each character and add it to the priority queue
    for (const auto& entry : frequencies) {
        minHeap.push(new HuffmanNode(entry.first, entry.second));
    }

    // Build the Huffman tree by combining nodes
    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();

        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        HuffmanNode* internalNode = new HuffmanNode('\0', left->frequency + right->frequency);
        internalNode->left = left;
        internalNode->right = right;

        minHeap.push(internalNode);
    }

    // The remaining node is the root of the Huffman tree
    return minHeap.top();
}

// Utility function to generate Huffman codes
void generateHuffmanCodes(HuffmanNode* root, const std::string& code, std::unordered_map<char, std::string>& huffmanCodes) {
    if (root) {
        if (!root->left && !root->right) {
            huffmanCodes[root->data] = code;
        }

        generateHuffmanCodes(root->left, code + "0", huffmanCodes);
        generateHuffmanCodes(root->right, code + "1", huffmanCodes);
    }
}

// Utility function to encode text using Huffman codes
std::string huffmanEncode(const std::string& text, const std::unordered_map<char, std::string>& huffmanCodes) {
    std::string encodedText;
    for (char c : text) {
        encodedText += huffmanCodes.at(c);
    }
    return encodedText;
}

// Utility function to decode Huffman-encoded text
std::string huffmanDecode(const std::string& encodedText, const HuffmanNode* root) {
    std::string decodedText;
    const HuffmanNode* current = root;

    for (char bit : encodedText) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        if (!current->left && !current->right) {
            decodedText += current->data;
            current = root;
        }
    }

    return decodedText;
}

int main() {
    std::string inputText = "hello, world!";
    
    // Calculate character frequencies
    std::unordered_map<char, unsigned> frequencies;
    for (char c : inputText) {
        frequencies[c]++;
    }

    // Build Huffman tree
    HuffmanNode* huffmanTree = buildHuffmanTree(frequencies);

    // Generate Huffman codes
    std::unordered_map<char, std::string> huffmanCodes;
    generateHuffmanCodes(huffmanTree, "", huffmanCodes);

    // Encode and decode
    std::string encodedText = huffmanEncode(inputText, huffmanCodes);
    std::string decodedText = huffmanDecode(encodedText, huffmanTree);

    // Output results
    std::cout << "Original Text: " << inputText << std::endl;
    std::cout << "Encoded Text: " << encodedText << std::endl;
    std::cout << "Decoded Text: " << decodedText << std::endl;

    return 0;
}