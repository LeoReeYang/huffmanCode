#include <bits/stdc++.h>
#include <fstream>
using namespace std;

// A Huffman tree node
struct MinHeapNode
{

    // One of the input characters
    char data;

    // Frequency of the character
    unsigned freq;

    // Left and right child
    MinHeapNode *left, *right;

    MinHeapNode(char data, unsigned freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

// For comparison of
// two heap nodes (needed in min heap)
struct compare
{
    bool operator()(MinHeapNode *l, MinHeapNode *r)
    {
        return l->freq > r->freq;
    }
};

// Prints huffman codes from
// the root of Huffman Tree.
void printCodes(struct MinHeapNode *root, string str)
{
    if (!root) //叶子空节点返回
        return;

    if (root->data != '$') //叶子节点返回哈夫曼编码
        cout << root->data << ": " << str << "\n";

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

// The main function that builds a Huffman Tree and
// print codes by traversing the built Huffman Tree
void HuffmanCodes(char data[], int freq[], int size)
{
    struct MinHeapNode *left, *right, *top;

    // Create a min heap & inserts all characters of data[]
    priority_queue<MinHeapNode *, vector<MinHeapNode *>, compare> minHeap;

    for (int i = 0; i < size; ++i)
        minHeap.push(new MinHeapNode(data[i], freq[i]));

    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1)
    {

        // Extract the two minimum
        // freq items from min heap
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with
        // frequency equal to the sum of the
        // two nodes frequencies. Make the
        // two extracted node as left and right children
        // of this new node. Add this node
        // to the min heap '$' is a special value
        // for internal nodes, not used
        top = new MinHeapNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        minHeap.push(top);
    }

    // Print Huffman codes using
    // the Huffman tree built above
    printCodes(minHeap.top(), "");
}
char alphbet[28];
int freq[28];
// Driver Code

int dataInput(char alphbet[], int freq[])
{
    char start = 'a';
    alphbet[0] = '#';
    int count = 0;

    for (int i = 1; i <= 26; i++)
        alphbet[i] = start + i - 1;

    fstream f;
    f.open("input.txt", ios::in);
    if (f.is_open())
    {
        char ch;
        while (f >> ch)
        {
            count++;
            if (ch >= 'a' and ch <= 'z')
                freq[ch - 'a' + 1]++;
            else
                freq[0]++;
        }
    }
    f.close();
    return count;
}
// char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
// int freq[] = {5, 9, 12, 13, 16, 45};

int main()
{
    int count = dataInput(alphbet, freq);
    cout << count << endl;

    int size = sizeof(alphbet) / sizeof(alphbet[0]);

    HuffmanCodes(alphbet, freq, size);

    return 0;
}

// This code is contributed by Aditya Goel
