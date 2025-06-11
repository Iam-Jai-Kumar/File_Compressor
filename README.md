# Huffman File Compressor

A lightweight and efficient file compressor built using the **Huffman Encoding algorithm** in C++.
This tool allows you to **compress and decompress text files**, showcasing one of the most fundamental lossless compression techniques used in real-world systems (e.g., ZIP, PNG).

---

## 📌 Features

- 📥 Compress any text file using Huffman Encoding
- 📤 Decompress the file back to its original form
- 🧠 Custom implementation of Huffman Tree using Min Heap
- 🧾 Binary I/O with frequency metadata preservation
- ✅ Supports variable-length encoding for characters
- 🧪 Clean, modular C++ code for easy learning and extension

---

## 🧱 How It Works

1. **Compression Phase**
   - Reads the input file
   - Calculates character frequencies
   - Builds a Huffman Tree based on frequencies
   - Generates binary codes for each character
   - Converts original text into compressed binary data
   - Stores both:
     - Encoded binary file
     - Metadata (character frequencies or Huffman codes)

2. **Decompression Phase**
   - Rebuilds the Huffman Tree from metadata
   - Reads the binary file and decodes it using the tree
   - Outputs the exact original text file

---

## 📁 File Structure
📦 file_compressor
├── huffman_compressor.cpp # Main C++ source file
├── input.txt # Input text file to be compressed
├── compressed.bin # Output of compressed data (binary)
├── meta.txt # Metadata (frequency table or Huffman codes)
├── output.txt # Decompressed file (should match input.txt)
└── README.md # This file

---

## 🚀 How to Run

### 🖥️ Requirements

- C++17 or later
- A terminal (Git Bash, PowerShell, Linux, etc.)
- g++ compiler or VS Code with C++ support

---

### 🔧 Compilation

bash
g++ -std=c++17 huffman_compressor.cpp -o huffman

▶️ Run the Program
bash
./huffman

You will see:

1. Compress
2. Decompress
Choose:
Choose 1 to compress input.txt, or 2 to decompress compressed.bin.

### 📌 Example
✅ Input: input.txt
Hello Huffman!

🗜️ Compression generates:
compressed.bin — Encoded binary data
meta.txt — Character frequency table

🔁 Decompression:
Regenerates output.txt identical to input.txt

📦 Compression Format
Huffman Codes are generated and stored in meta.txt (or a frequency table)
Binary data is written bit-by-bit using character-to-code mapping
Bit padding and total length tracking ensure byte-alignment

## ⚠️ Limitations
Only supports text files
Doesn't currently support:
  Unicode/multibyte input
  Image/audio compression
Padding bits are manually managed

## 🧠 Concepts Demonstrated
Greedy algorithms (Huffman)
Priority Queue / Min Heap
Recursion / Tree traversal
Bit manipulation
File I/O in binary mode

## 🙌 Acknowledgements
Based on the classic Huffman algorithm taught in Data Structures courses.
Inspired by real-world compression formats like ZIP, GZIP, and PNG.

## 📫 Contact
Created by Jai Kumar
📧 Email: jaikumar913276@gmail.com
🔗 GitHub: Iam-Jai-Kumar
