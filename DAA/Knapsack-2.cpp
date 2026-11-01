
#include <iostream>
using namespace std;

#define MAX 100

class Knapsack
{
public:

    // Function to print spaces for alignment
    void printSpaces(int n)
    {
        for (int i = 0; i < n; i++)
            cout << " ";
    }

    // Function to print aligned numbers
    void printNumber(int num, int width)
    {
        int temp = num;
        int digits = 1;

        while (temp >= 10)
        {
            digits++;
            temp = temp / 10;
        }

        cout << num;
        printSpaces(width - digits);
    }

    void solve(int n, int W, int profit[], int weight[])
    {
        int dp[MAX][MAX] = {0};

        // Dynamic Programming
        for (int i = 1; i <= n; i++)
        {
            for (int w = 0; w <= W; w++)
            {
                if (weight[i - 1] <= w)
                {
                    int include = profit[i - 1] +
                                  dp[i - 1][w - weight[i - 1]];

                    int exclude = dp[i - 1][w];

                    if (include > exclude)
                        dp[i][w] = include;
                    else
                        dp[i][w] = exclude;
                }
                else
                {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }

        // Display DP Table
        cout << "\nDP Table:\n\n";

        cout << "Item/W    ";

        for (int w = 0; w <= W; w++)
            printNumber(w, 5);

        cout << endl;

        for (int j = 0; j < 10 + (W + 1) * 5; j++)
            cout << "-";

        cout << endl;

        for (int i = 0; i <= n; i++)
        {
            if (i == 0)
                cout << "None      ";
            else
                cout << "Item " << i << "    ";

            for (int w = 0; w <= W; w++)
                printNumber(dp[i][w], 5);

            cout << endl;
        }

        // Display Maximum Profit
        cout << "\nMaximum Profit: " << dp[n][W] << endl;

        // Backtracking to find selected items
        cout << "Selected Items: ";

        int w = W;
        int totalWeight = 0;

        for (int i = n; i > 0; i--)
        {
            if (dp[i][w] != dp[i - 1][w])
            {
                cout << "Item " << i << " ";

                totalWeight += weight[i - 1];

                w = w - weight[i - 1];
            }
        }

        cout << "\nTotal Weight: " << totalWeight << endl;
    }
};

int main()
{
    int n, W;
    int profit[MAX], weight[MAX];

    cout << "Enter number of items: ";
    cin >> n;

    if (n <= 0 || n >= MAX)
    {
        cout << "Invalid number of items!";
        return 0;
    }

    cout << "Enter knapsack capacity: ";
    cin >> W;

    if (W < 0 || W >= MAX)
    {
        cout << "Invalid capacity!";
        return 0;
    }

    // Input item details
    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter profit of item " << i + 1 << ": ";
        cin >> profit[i];

        cout << "Enter weight of item " << i + 1 << ": ";
        cin >> weight[i];

        if (profit[i] < 0 || weight[i] <= 0)
        {
            cout << "Invalid profit or weight!";
            return 0;
        }
    }

    // Create object and solve
    Knapsack k;
    k.solve(n, W, profit, weight);

    return 0;
}


/*
PAPER WORK (STEP-BY-STEP SOLUTION OF THE EXAMPLE)
=====================================================================

   Item 1 = A (p=18, wt=9)
   Item 2 = B (p=10, wt=4)
   Item 3 = C (p=12, wt=6)
   Item 4 = D (p=10, wt=2)
   W = 15  ->  table has 5 rows (i = 0..4) and 16 columns (w = 0..15)

---------------------------------------------------------------------
STEP 0 : Row i = 0 (no item)  ->  all zeros
---------------------------------------------------------------------

   Row 0 :  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0

---------------------------------------------------------------------
STEP 1 : Row i = 1, item A (p=18, wt=9)
---------------------------------------------------------------------

   w = 0..8  : wt 9 > w, does not fit  -> V[0][w]              = 0
   w = 9     : max(V[0][9],  V[0][0] + 18) = max(0, 0 + 18)     = 18
   w = 10..15: max(V[0][w],  V[0][w-9] + 18) = max(0, 0 + 18)   = 18

   Row 1 :  0  0  0  0  0  0  0  0  0  18 18 18 18 18 18 18

---------------------------------------------------------------------
STEP 2 : Row i = 2, item B (p=10, wt=4)
---------------------------------------------------------------------

   w = 0..3  : wt 4 > w, does not fit  -> copy row 1            = 0
   w = 4  : max(V[1][4],  V[1][0] + 10)  = max(0,  0 + 10)      = 10
   w = 5  : max(V[1][5],  V[1][1] + 10)  = max(0,  0 + 10)      = 10
   w = 6  : max(V[1][6],  V[1][2] + 10)  = max(0,  0 + 10)      = 10
   w = 7  : max(V[1][7],  V[1][3] + 10)  = max(0,  0 + 10)      = 10
   w = 8  : max(V[1][8],  V[1][4] + 10)  = max(0,  0 + 10)      = 10
   w = 9  : max(V[1][9],  V[1][5] + 10)  = max(18, 0 + 10)      = 18
   w = 10 : max(V[1][10], V[1][6] + 10)  = max(18, 0 + 10)      = 18
   w = 11 : max(V[1][11], V[1][7] + 10)  = max(18, 0 + 10)      = 18
   w = 12 : max(V[1][12], V[1][8] + 10)  = max(18, 0 + 10)      = 18
   w = 13 : max(V[1][13], V[1][9] + 10)  = max(18, 18 + 10)     = 28
   w = 14 : max(V[1][14], V[1][10] + 10) = max(18, 18 + 10)     = 28
   w = 15 : max(V[1][15], V[1][11] + 10) = max(18, 18 + 10)     = 28

   Row 2 :  0  0  0  0  10 10 10 10 10 18 18 18 18 28 28 28

---------------------------------------------------------------------
STEP 3 : Row i = 3, item C (p=12, wt=6)
---------------------------------------------------------------------

   w = 0..5  : wt 6 > w, does not fit  -> copy row 2  = 0 0 0 0 10 10
   w = 6  : max(V[2][6],  V[2][0] + 12)  = max(10, 0 + 12)      = 12
   w = 7  : max(V[2][7],  V[2][1] + 12)  = max(10, 0 + 12)      = 12
   w = 8  : max(V[2][8],  V[2][2] + 12)  = max(10, 0 + 12)      = 12
   w = 9  : max(V[2][9],  V[2][3] + 12)  = max(18, 0 + 12)      = 18
   w = 10 : max(V[2][10], V[2][4] + 12)  = max(18, 10 + 12)     = 22
   w = 11 : max(V[2][11], V[2][5] + 12)  = max(18, 10 + 12)     = 22
   w = 12 : max(V[2][12], V[2][6] + 12)  = max(18, 10 + 12)     = 22
   w = 13 : max(V[2][13], V[2][7] + 12)  = max(28, 10 + 12)     = 28
   w = 14 : max(V[2][14], V[2][8] + 12)  = max(28, 10 + 12)     = 28
   w = 15 : max(V[2][15], V[2][9] + 12)  = max(28, 18 + 12)     = 30

   Row 3 :  0  0  0  0  10 10 12 12 12 18 22 22 22 28 28 30

---------------------------------------------------------------------
STEP 4 : Row i = 4, item D (p=10, wt=2)
---------------------------------------------------------------------

   w = 0..1  : wt 2 > w, does not fit  -> copy row 3            = 0
   w = 2  : max(V[3][2],  V[3][0] + 10)  = max(0,  0 + 10)      = 10
   w = 3  : max(V[3][3],  V[3][1] + 10)  = max(0,  0 + 10)      = 10
   w = 4  : max(V[3][4],  V[3][2] + 10)  = max(10, 0 + 10)      = 10
   w = 5  : max(V[3][5],  V[3][3] + 10)  = max(10, 0 + 10)      = 10
   w = 6  : max(V[3][6],  V[3][4] + 10)  = max(12, 10 + 10)     = 20
   w = 7  : max(V[3][7],  V[3][5] + 10)  = max(12, 10 + 10)     = 20
   w = 8  : max(V[3][8],  V[3][6] + 10)  = max(12, 12 + 10)     = 22
   w = 9  : max(V[3][9],  V[3][7] + 10)  = max(18, 12 + 10)     = 22
   w = 10 : max(V[3][10], V[3][8] + 10)  = max(22, 12 + 10)     = 22
   w = 11 : max(V[3][11], V[3][9] + 10)  = max(22, 18 + 10)     = 28
   w = 12 : max(V[3][12], V[3][10] + 10) = max(22, 22 + 10)     = 32
   w = 13 : max(V[3][13], V[3][11] + 10) = max(28, 22 + 10)     = 32
   w = 14 : max(V[3][14], V[3][12] + 10) = max(28, 22 + 10)     = 32
   w = 15 : max(V[3][15], V[3][13] + 10) = max(30, 28 + 10)     = 38

   Row 4 :  0  0  10 10 10 10 20 20 22 22 22 28 32 32 32 38

---------------------------------------------------------------------
STEP 5 : Final DP Table V[i][w]
---------------------------------------------------------------------

 +---+----------+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+----+
 | i | Item     |w=0| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |10 |11 |12 |13 |14 | 15 |
 |   | (p,wt)   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |    |
 +---+----------+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+----+
 | 0 | none     | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |  0 |
 | 1 | A (18,9) | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |18 |18 |18 |18 |18 |18 | 18 |
 | 2 | B (10,4) | 0 | 0 | 0 | 0 |10 |10 |10 |10 |10 |18 |18 |18 |18 |28 |28 | 28 |
 | 3 | C (12,6) | 0 | 0 | 0 | 0 |10 |10 |12 |12 |12 |18 |22 |22 |22 |28 |28 | 30 |
 | 4 | D (10,2) | 0 | 0 |10 |10 |10 |10 |20 |20 |22 |22 |22 |28 |32 |32 |32 |[38]|
 +---+----------+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+----+

   Maximum profit = V[4][15] = 38

---------------------------------------------------------------------
STEP 6 : Traceback (find which items are selected)
---------------------------------------------------------------------

   Start at i = 4, w = 15

   i = 4 (D): V[4][15] = 38,  V[3][15] = 30  -> different
              => D is SELECTED.      w = 15 - 2 = 13

   i = 3 (C): V[3][13] = 28,  V[2][13] = 28  -> same
              => C is NOT selected.  w stays 13

   i = 2 (B): V[2][13] = 28,  V[1][13] = 18  -> different
              => B is SELECTED.      w = 13 - 4 = 9

   i = 1 (A): V[1][9]  = 18,  V[0][9]  = 0   -> different
              => A is SELECTED.      w = 9 - 9 = 0

   Traceback path in the table:
        V[4][15]=38 -> V[3][13]=28 -> V[2][13]=28 -> V[1][9]=18 -> V[0][0]=0

---------------------------------------------------------------------
STEP 7 : Verification
---------------------------------------------------------------------

   Selected items : A, B and D
   Total weight   = 9 + 4 + 2   = 15 kg  (<= W = 15, fits exactly)
   Total profit   = 18 + 10 + 10 = Rs. 38

   Check other possible combinations (within W = 15):
      A + B       : wt 13, profit 28
      A + C       : wt 15, profit 30
      A + D       : wt 11, profit 28
      B + C + D   : wt 12, profit 32
      A + B + D   : wt 15, profit 38   <- BEST
      A + C + D   : wt 17  -> over capacity, not allowed
      A + B + C   : wt 19  -> over capacity, not allowed

FINAL ANSWER
------------
       Solution vector (A, B, C, D) = (1, 1, 0, 1)
       Items selected  = A, B, D
       Maximum profit  = Rs. 38
       Total weight    = 15 kg


*/