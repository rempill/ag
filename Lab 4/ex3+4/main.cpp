#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;
//huffman code and decode
//input is:
//Loorrreem

using namespace std;

// Huffman Tree node
struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    Node(Node* left, Node* right) : ch('\0'), freq(left->freq + right->freq), left(left), right(right) {}
};

// Comparison for priority queue (min-heap)
struct Compare {
    bool operator()(Node* a, Node* b) {
        if (a->freq== b->freq) {
            return a->ch > b->ch; // tie-breaker for characters
        }
        return a->freq > b->freq;
    }
};

// Generate Huffman codes (DFS)
void encodeHuffman(Node* root, map<char, string>& huffCode, string code = "") {
    if (!root) return;
    if (!root->left && !root->right)
        huffCode[root->ch] = code;
    encodeHuffman(root->left, huffCode, code + "0");
    encodeHuffman(root->right, huffCode, code + "1");
}

// Decode bitstring using Huffman tree
string decodeHuffman(Node* root, const string& bits) {
    string result = "";
    Node* curr = root;
    for (char bit : bits) {
        if (bit == '0') curr = curr->left;
        else curr = curr->right;

        if (!curr->left && !curr->right) {
            result += curr->ch;
            curr = root;
        }
    }
    return result;
}

int main() {
    ifstream in("input.txt");
    string text;
    if (in.is_open()) {
        getline(in, text);
        in.close();
    } else {
        cerr << "Unable to open file";
        return 1;
    }

    // frequency map
    map<char, int> freq;
    for (char c : text) freq[c]++;

    // build tree for huffman coding
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& [c, f] : freq) {
        pq.push(new Node(c, f));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        pq.push(new Node(left, right));
    }

    Node* root = pq.top();

    //generate Huffman code
    map<char, string> huffCode;
    encodeHuffman(root, huffCode);

    //create encoded string
    string encoded = "";
    for (char c : text) {
        encoded += huffCode[c];
    }

    // output encoding
    cout << freq.size() << "\n";
    for (auto& p : freq) {
        cout << p.first << " " << p.second << "\n";
    }
    cout << encoded << "\n";

    // decode and output decoding
    string decoded = decodeHuffman(root, encoded);
    cout << decoded << "\n";

    return 0;
}
