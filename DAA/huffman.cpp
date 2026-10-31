
#include <iostream>
using namespace std;

#define MAX 100

// Node Class
class Node
{
public:
    char ch;
    int freq;
    int left, right;

    Node()
    {
        ch = '$';
        freq = 0;
        left = right = -1;
    }
};

// Huffman Class
class Huffman
{
    Node tree[2 * MAX];
    int active[2 * MAX];

public:

    // Display Huffman Codes
    void printCodes(int root, string code)
    {
        if (tree[root].left == -1 &&
            tree[root].right == -1)
        {
            cout << tree[root].ch << " : " << code << endl;
            return;
        }

        printCodes(tree[root].left, code + "0");
        printCodes(tree[root].right, code + "1");
    }

    // Huffman Encoding
    void huffmanEncoding(char ch[], int freq[], int n)
    {
        int total = 2 * n - 1;

        // Initialize arrays
        for (int i = 0; i < total; i++)
            active[i] = 0;

        // Insert characters
        for (int i = 0; i < n; i++)
        {
            tree[i].ch = ch[i];
            tree[i].freq = freq[i];
            tree[i].left = -1;
            tree[i].right = -1;

            active[i] = 1;
        }

        // Build Huffman Tree
        for (int i = n; i < total; i++)
        {
            int min1 = -1, min2 = -1;

            // Find two minimum frequencies
            for (int j = 0; j < i; j++)
            {
                if (active[j])
                {
                    if (min1 == -1 ||
                        tree[j].freq < tree[min1].freq)
                    {
                        min2 = min1;
                        min1 = j;
                    }
                    else if (min2 == -1 ||
                             tree[j].freq < tree[min2].freq)
                    {
                        min2 = j;
                    }
                }
            }

            // Create new internal node
            tree[i].freq = tree[min1].freq + tree[min2].freq;
            tree[i].left = min1;
            tree[i].right = min2;

            active[min1] = 0;
            active[min2] = 0;
            active[i] = 1;
        }

        // Display Huffman Codes
        cout << "\nHuffman Codes:\n";
        printCodes(total - 1, "");
    }
};

int main()
{
    int n;
    char ch[MAX];
    int freq[MAX];

    cout << "Enter number of characters: ";
    cin >> n;

    if (n <= 0 || n > MAX)
    {
        cout << "Invalid number of characters!";
        return 0;
    }

    // Input characters and frequencies
    for (int i = 0; i < n; i++)
    {
        cout << "Enter character " << i + 1 << ": ";
        cin >> ch[i];

        cout << "Enter frequency of " << ch[i] << ": ";
        cin >> freq[i];

        if (freq[i] <= 0)
        {
            cout << "Frequency must be positive!";
            return 0;
        }
    }

    Huffman h;
    h.huffmanEncoding(ch, freq, n);

    return 0;
}


/*
 PAPER WORK (STEP-BY-STEP SOLUTION OF THE EXAMPLE)
=====================================================================

Total number of characters = 12 + 15 + 7 + 13 + 9 = 56

---------------------------------------------------------------------
STEP 0 : Arrange all characters in ascending order of frequency
---------------------------------------------------------------------

   Min-Heap :  C(7)   E(9)   A(12)   D(13)   B(15)

---------------------------------------------------------------------
STEP 1 : Pick the two smallest  ->  C(7) and E(9)
---------------------------------------------------------------------

   New node N1 = 7 + 9 = 16

              N1(16)
             /      \
          C(7)      E(9)

   Min-Heap :  A(12)   D(13)   B(15)   N1(16)

---------------------------------------------------------------------
STEP 2 : Pick the two smallest  ->  A(12) and D(13)
---------------------------------------------------------------------

   New node N2 = 12 + 13 = 25

              N2(25)
             /      \
          A(12)    D(13)

   Min-Heap :  B(15)   N1(16)   N2(25)

---------------------------------------------------------------------
STEP 3 : Pick the two smallest  ->  B(15) and N1(16)
---------------------------------------------------------------------

   New node N3 = 15 + 16 = 31

              N3(31)
             /      \
          B(15)    N1(16)
                   /    \
                C(7)    E(9)

   Min-Heap :  N2(25)   N3(31)

---------------------------------------------------------------------
STEP 4 : Pick the two smallest  ->  N2(25) and N3(31)
---------------------------------------------------------------------

   New node ROOT = 25 + 31 = 56

   Min-Heap :  ROOT(56)     <- only one node left, so STOP.

   (Check: ROOT frequency 56 = total of all frequencies. Correct.)

---------------------------------------------------------------------
STEP 5 : Final Huffman Tree  (Left edge = 0, Right edge = 1)
---------------------------------------------------------------------

                         ROOT(56)
                       0 /      \ 1
                        /        \
                   N2(25)        N3(31)
                 0 /    \ 1    0 /    \ 1
                  /      \      /      \
               A(12)   D(13)  B(15)   N1(16)
                                     0 /    \ 1
                                      /      \
                                   C(7)      E(9)

---------------------------------------------------------------------
STEP 6 : Read the codes (path from ROOT to each leaf)
---------------------------------------------------------------------

   A : ROOT -> N2 (0) -> A (0)                  =  00
   D : ROOT -> N2 (0) -> D (1)                  =  01
   B : ROOT -> N3 (1) -> B (0)                  =  10
   C : ROOT -> N3 (1) -> N1 (1) -> C (0)        =  110
   E : ROOT -> N3 (1) -> N1 (1) -> E (1)        =  111

---------------------------------------------------------------------
STEP 7 : Huffman Code Table and Total Bits
---------------------------------------------------------------------

   +------+-----------+--------------+-------------+-----------------+
   | Char | Frequency | Huffman Code | Code Length | Bits = Freq*Len |
   +------+-----------+--------------+-------------+-----------------+
   |  A   |    12     |      00      |      2      |  12 x 2 =  24   |
   |  B   |    15     |      10      |      2      |  15 x 2 =  30   |
   |  C   |     7     |     110      |      3      |   7 x 3 =  21   |
   |  D   |    13     |      01      |      2      |  13 x 2 =  26   |
   |  E   |     9     |     111      |      3      |   9 x 3 =  27   |
   +------+-----------+--------------+-------------+-----------------+
   |Total |    56     |              |             |       128       |
   +------+-----------+--------------+-------------+-----------------+

---------------------------------------------------------------------


FINAL ANSWER
------------
       A = 00     B = 10     C = 110     D = 01     E = 111
       Total bits = 128   (vs 168 bits with fixed 3-bit code)
*/