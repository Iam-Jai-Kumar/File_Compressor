#include <bits/stdc++.h>
using namespace std;

struct Node
{
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare
{
    bool operator()(Node *a, Node *b)
    {
        return a->freq > b->freq;
    }
};

void buildCodeTable(Node *root, string str, unordered_map<char, string> &huffCode)
{
    if (!root)
        return;
    if (!root->left && !root->right)
        huffCode[root->ch] = str;
    buildCodeTable(root->left, str + "0", huffCode);
    buildCodeTable(root->right, str + "1", huffCode);
}

Node *buildHuffmanTree(unordered_map<char, int> &freq)
{
    priority_queue<Node *, vector<Node *>, Compare> pq;
    for (auto &[ch, f] : freq)
        pq.push(new Node(ch, f));

    while (pq.size() > 1)
    {
        Node *l = pq.top();
        pq.pop();
        Node *r = pq.top();
        pq.pop();
        Node *newNode = new Node('\0', l->freq + r->freq);
        newNode->left = l;
        newNode->right = r;
        pq.push(newNode);
    }
    return pq.top();
}

void saveEncodedFile(string &binaryStr, const string &outPath)
{
    ofstream out(outPath, ios::binary);
    for (int i = 0; i < binaryStr.size(); i += 8)
    {
        bitset<8> bits(binaryStr.substr(i, min(8, (int)binaryStr.size() - i)));
        out.put((char)bits.to_ulong());
    }
    out.close();
}

void compressFile(const string &inputPath, const string &outputPath, const string &metaPath)
{
    ifstream in(inputPath, ios::binary);
    string text((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();

    unordered_map<char, int> freq;
    for (char ch : text)
        freq[ch]++;

    Node *root = buildHuffmanTree(freq);

    unordered_map<char, string> huffCode;
    buildCodeTable(root, "", huffCode);

    string encodedStr = "";
    for (char ch : text)
        encodedStr += huffCode[ch];

    saveEncodedFile(encodedStr, outputPath);

    ofstream meta(metaPath);
    for (auto &[ch, f] : freq)
        meta << (int)(unsigned char)ch << " " << f << "\n";
    meta.close();

    cout << "Compression complete.\n";
}

Node *rebuildTree(unordered_map<char, int> &freq)
{
    return buildHuffmanTree(freq);
}

void decodeFile(const string &encodedPath, const string &metaPath, const string &outputPath)
{
    unordered_map<char, int> freq;
    ifstream meta(metaPath);
    int ch, f;
    while (meta >> ch >> f)
        freq[(char)ch] = f;
    meta.close();

    Node *root = rebuildTree(freq);

    unordered_map<string, char> revMap;
    unordered_map<char, string> codeMap;
    buildCodeTable(root, "", codeMap);
    for (auto &[ch, code] : codeMap)
        revMap[code] = ch;

    ifstream in(encodedPath, ios::binary);
    string bitStr;
    char byte;
    while (in.get(byte))
    {
        bitset<8> bits((unsigned char)byte);
        bitStr += bits.to_string();
    }
    in.close();

    Node *curr = root;
    string decodedText = "";
    for (char bit : bitStr)
    {
        curr = (bit == '0') ? curr->left : curr->right;
        if (!curr->left && !curr->right)
        {
            decodedText += curr->ch;
            curr = root;
        }
    }

    ofstream out(outputPath);
    out << decodedText;
    out.close();

    cout << "Decompression complete.\n";
}

int main()
{
    string input = "input.txt";
    string encoded = "compressed.bin";
    string metadata = "meta.txt";
    string output = "output.txt";

    cout << "1. Compress\n2. Decompress\nChoose: ";
    int choice;
    cin >> choice;

    if (choice == 1)
        compressFile(input, encoded, metadata);
    else
        decodeFile(encoded, metadata, output);

    return 0;
}
