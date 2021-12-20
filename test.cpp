#include <bits/stdc++.h>
#include <fstream>
#include <utility>
using namespace std;

vector<pair<char, string>> huffman_table;
char alphbet[28];
int freq[28];
// A Huffman tree node
struct MinHeapNode
{
    char data;
    unsigned freq;

    MinHeapNode *left, *right;

    MinHeapNode(char data, unsigned freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};
struct compare
{
    bool operator()(MinHeapNode *l, MinHeapNode *r)
    {
        return l->freq > r->freq;
    }
};

void printCodes(struct MinHeapNode *root, string str, vector<pair<char, string>> &x)
{
    if (!root) //叶子空节点返回
        return;

    if (root->data != '$') //叶子节点返回哈夫曼编码
    {
        cout << root->data << ": " << str << "\n";
        x.push_back(pair<char, string>(root->data, str)); //存储哈夫曼编码
    }

    printCodes(root->left, str + "0", x);
    printCodes(root->right, str + "1", x);
}

// The main function that builds a Huffman Tree and
// print codes by traversing the built Huffman Tree
//构建哈夫曼树，从根节点开始便利输出哈夫曼编码，同时存储哈夫曼编码
void HuffmanCodes(char data[], int freq[], int size, vector<pair<char, string>> &x)
{
    struct MinHeapNode *left, *right, *top;

    // Create a min heap & inserts all characters of data[]
    priority_queue<MinHeapNode *, vector<MinHeapNode *>, compare> minHeap;

    for (int i = 0; i < size; ++i)
        minHeap.push(new MinHeapNode(data[i], freq[i]));

    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1)
    {
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        top = new MinHeapNode('$', left->freq + right->freq); //构造新节点，合并频率

        top->left = left;
        top->right = right;

        minHeap.push(top); //入堆
    }

    printCodes(minHeap.top(), "", x);
}

int dataInput(char alphbet[], int freq[])
{
    alphbet[0] = '#';
    int count = 0;

    for (int i = 1; i <= 26; i++)
        alphbet[i] = 'a' + i - 1;

    fstream f("input.txt", ios::in);
    if (f.is_open())
    {
        char ch;
        while (f >> ch)
        {
            tolower(ch);
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

int huff_code_len(char ch, vector<pair<char, string>> &x) // 返回对应哈夫曼节点的长度
{
    for (vector<pair<char, string>>::iterator it = x.begin(); it != x.end(); it++)
        if (it->first == ch)
            return it->second.length();
    return -1;
}

int bits_need(vector<pair<char, string>> &x) //输出文本中的哈夫曼编码总长度
{
    int counts = 0;
    fstream f("input.txt", ios::in);
    if (f.is_open())
    {
        char ch;
        while (f >> ch)
        {
            tolower(ch);
            counts += huff_code_len(ch, x);
        }
    }
    f.close();
    return counts;
}

void freq_print()
{
    cout << endl
         << "#: " << freq[0] << endl;
    for (int i = 1; i < 27; i++)
    {
        char ch = 'a' + i - 1;
        cout << ch << ": " << freq[i] << endl;
    }
}

int main()
{
    int count = dataInput(alphbet, freq);
    cout << count << endl;

    int size = sizeof(alphbet) / sizeof(alphbet[0]);

    HuffmanCodes(alphbet, freq, size - 1, huffman_table);

    cout << "fixed length: " << count * 5 << endl;

    cout << "huffcode length: " << bits_need(huffman_table);

    freq_print();
    return 0;
}