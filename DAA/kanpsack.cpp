
#include <iostream>
using namespace std;

#define MAX 100

class Knapsack
{
public:
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

                    dp[i][w] = max(include, exclude);
                }
                else
                {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }

        // Display DP Table
        cout << "\nDP Table:\n\n";

        cout << "Item/W\t";

        for (int w = 0; w <= W; w++)
            cout << w << "\t";

        cout << endl;

        for (int i = 0; i <= n; i++)
        {
            if (i == 0)
                cout << "None\t";
            else
                cout << i << "\t";

            for (int w = 0; w <= W; w++)
                cout << dp[i][w] << "\t";

            cout << endl;
        }

        // Maximum Profit
        cout << "\nMaximum Profit: " << dp[n][W] << endl;

        // Find Selected Items
        cout << "Selected Items: ";

        int w = W;

        for (int i = n; i > 0; i--)
        {
            if (dp[i][w] != dp[i - 1][w])
            {
                cout << "Item " << i << " ";
                w = w - weight[i - 1];
            }
        }

        cout << endl;
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

    Knapsack k;
    k.solve(n, W, profit, weight);

    return 0;
}

/*
PAPER WORK (STEP-BY-STEP SOLUTION OF THE EXAMPLE)
=====================================================================

   Item 1 = A (p=2,  w=1)
   Item 2 = B (p=4,  w=3)
   Item 3 = C (p=7,  w=5)
   Item 4 = D (p=10, w=7)
   W = 8   ->  table has 5 rows (i = 0..4) and 9 columns (w = 0..8)

---------------------------------------------------------------------
STEP 0 : Row i = 0 (no item)  ->  all zeros
---------------------------------------------------------------------

   V[0][w] = 0  for w = 0..8
   Row 0 :  0  0  0  0  0  0  0  0  0

---------------------------------------------------------------------
STEP 1 : Row i = 1, item A (p=2, wt=1)
---------------------------------------------------------------------

   w = 0 : wt 1 > 0, does not fit       -> V[0][0]               = 0
   w = 1 : max(V[0][1], V[0][0] + 2)    =  max(0, 0 + 2)          = 2
   w = 2 : max(V[0][2], V[0][1] + 2)    =  max(0, 0 + 2)          = 2
   w = 3..8 : same way                  =  max(0, 0 + 2)          = 2

   Row 1 :  0  2  2  2  2  2  2  2  2

---------------------------------------------------------------------
STEP 2 : Row i = 2, item B (p=4, wt=3)
---------------------------------------------------------------------

   w = 0,1,2 : wt 3 > w, does not fit   -> copy row 1   = 0, 2, 2
   w = 3 : max(V[1][3], V[1][0] + 4)    =  max(2, 0 + 4)          = 4
   w = 4 : max(V[1][4], V[1][1] + 4)    =  max(2, 2 + 4)          = 6
   w = 5 : max(V[1][5], V[1][2] + 4)    =  max(2, 2 + 4)          = 6
   w = 6 : max(V[1][6], V[1][3] + 4)    =  max(2, 2 + 4)          = 6
   w = 7 : max(V[1][7], V[1][4] + 4)    =  max(2, 2 + 4)          = 6
   w = 8 : max(V[1][8], V[1][5] + 4)    =  max(2, 2 + 4)          = 6

   Row 2 :  0  2  2  4  6  6  6  6  6

---------------------------------------------------------------------
STEP 3 : Row i = 3, item C (p=7, wt=5)
---------------------------------------------------------------------

   w = 0..4 : wt 5 > w, does not fit    -> copy row 2  = 0, 2, 2, 4, 6
   w = 5 : max(V[2][5], V[2][0] + 7)    =  max(6, 0 + 7)          = 7
   w = 6 : max(V[2][6], V[2][1] + 7)    =  max(6, 2 + 7)          = 9
   w = 7 : max(V[2][7], V[2][2] + 7)    =  max(6, 2 + 7)          = 9
   w = 8 : max(V[2][8], V[2][3] + 7)    =  max(6, 4 + 7)          = 11

   Row 3 :  0  2  2  4  6  7  9  9  11

---------------------------------------------------------------------
STEP 4 : Row i = 4, item D (p=10, wt=7)
---------------------------------------------------------------------

   w = 0..6 : wt 7 > w, does not fit    -> copy row 3 = 0, 2, 2, 4, 6, 7, 9
   w = 7 : max(V[3][7], V[3][0] + 10)   =  max(9,  0 + 10)        = 10
   w = 8 : max(V[3][8], V[3][1] + 10)   =  max(11, 2 + 10)        = 12

   Row 4 :  0  2  2  4  6  7  9  10  12

---------------------------------------------------------------------
STEP 5 : Final DP Table V[i][w]
---------------------------------------------------------------------

   +----+-------------+----+----+----+----+----+----+----+----+----+
   |  i | Item (p,wt) | w=0|  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |
   +----+-------------+----+----+----+----+----+----+----+----+----+
   |  0 |   none      |  0 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |
   |  1 |   A (2,1)   |  0 |  2 |  2 |  2 |  2 |  2 |  2 |  2 |  2 |
   |  2 |   B (4,3)   |  0 |  2 |  2 |  4 |  6 |  6 |  6 |  6 |  6 |
   |  3 |   C (7,5)   |  0 |  2 |  2 |  4 |  6 |  7 |  9 |  9 | 11 |
   |  4 |   D (10,7)  |  0 |  2 |  2 |  4 |  6 |  7 |  9 | 10 |[12]|
   +----+-------------+----+----+----+----+----+----+----+----+----+

   Maximum profit = V[4][8] = 12

---------------------------------------------------------------------
STEP 6 : Traceback (find which items are selected)
---------------------------------------------------------------------

   Start at i = 4, w = 8

   i = 4 (D): V[4][8] = 12,  V[3][8] = 11  -> different
              => D is SELECTED.   w = 8 - 7 = 1

   i = 3 (C): V[3][1] = 2,   V[2][1] = 2   -> same
              => C is NOT selected.  w stays 1

   i = 2 (B): V[2][1] = 2,   V[1][1] = 2   -> same
              => B is NOT selected.  w stays 1

   i = 1 (A): V[1][1] = 2,   V[0][1] = 0   -> different
              => A is SELECTED.   w = 1 - 1 = 0

   Traceback path in the table:
        V[4][8]=12 -> V[3][1]=2 -> V[2][1]=2 -> V[1][1]=2 -> V[0][0]=0

---------------------------------------------------------------------
STEP 7 : Verification
---------------------------------------------------------------------

   Selected items : A and D
   Total weight   = 1 + 7  = 8   (<= W = 8, fits exactly)
   Total profit   = 2 + 10 = 12

   Check other possible combinations (within W = 8):
      A + B       : wt 4, profit  6
      A + C       : wt 6, profit  9
      B + C       : wt 8, profit 11
      A + B + C   : wt 9  -> over capacity, not allowed
      A + D       : wt 8, profit 12   <- BEST
      B + D, C + D: over capacity, not allowed

FINAL ANSWER
------------
       Solution vector (A, B, C, D) = (1, 0, 0, 1)
       Items selected  = A, D
       Maximum profit  = 12
       Total weight    = 8

*/