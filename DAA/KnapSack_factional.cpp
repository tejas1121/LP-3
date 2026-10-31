
#include <iostream>
using namespace std;

#define MAX 100

class Knapsack
{
public:
    void solve(int n, float W, float weight[], float profit[])
    {
        float ratio[MAX], fraction[MAX];
        int item[MAX];

        // Calculate profit/weight ratio
        for (int i = 0; i < n; i++)
        {
            ratio[i] = profit[i] / weight[i];
            item[i] = i;
            fraction[i] = 0;
        }

        // Sort items in descending order of ratio
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (ratio[i] < ratio[j])
                {
                    float temp;

                    temp = ratio[i];
                    ratio[i] = ratio[j];
                    ratio[j] = temp;

                    temp = weight[i];
                    weight[i] = weight[j];
                    weight[j] = temp;

                    temp = profit[i];
                    profit[i] = profit[j];
                    profit[j] = temp;

                    int t = item[i];
                    item[i] = item[j];
                    item[j] = t;
                }
            }
        }

        float totalProfit = 0;
        float remaining = W;

        // Select items greedily
        for (int i = 0; i < n; i++)
        {
            if (remaining >= weight[i])
            {
                fraction[i] = 1;
                remaining -= weight[i];
                totalProfit += profit[i];
            }
            else if (remaining > 0)
            {
                fraction[i] = remaining / weight[i];
                totalProfit += fraction[i] * profit[i];
                remaining = 0;
            }
            else
            {
                break;
            }
        }

        // Display result
        cout << "\nItem\tWeight\tProfit\tFraction\n";

        for (int i = 0; i < n; i++)
        {
            cout << item[i] + 1 << "\t"
                 << weight[i] << "\t"
                 << profit[i] << "\t"
                 << fraction[i] << endl;
        }

        cout << "\nMaximum Profit = " << totalProfit << endl;
    }
};

int main()
{
    int n;
    float W;
    float weight[MAX], profit[MAX];

    cout << "Enter number of items: ";
    cin >> n;

    if (n <= 0 || n > MAX)
    {
        cout << "Invalid number of items!";
        return 0;
    }

    cout << "Enter knapsack capacity: ";
    cin >> W;

    if (W <= 0)
    {
        cout << "Invalid capacity!";
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter weight of item " << i + 1 << ": ";
        cin >> weight[i];

        cout << "Enter profit of item " << i + 1 << ": ";
        cin >> profit[i];

        if (weight[i] <= 0 || profit[i] < 0)
        {
            cout << "Invalid weight or profit!";
            return 0;
        }
    }

    Knapsack k;
    k.solve(n, W, weight, profit);

    return 0;
}

/*
PAPER WORK (STEP-BY-STEP SOLUTION OF THE EXAMPLE)
=====================================================================

---------------------------------------------------------------------
STEP 1 : Find Profit / Weight ratio of each item
---------------------------------------------------------------------

   +------+--------+--------+---------------------+
   | Item | Weight | Profit | Ratio = Profit/Wt   |
   +------+--------+--------+---------------------+
   |  1   |   3    |   10   |  10 / 3  =  3.33    |
   |  2   |   3    |   15   |  15 / 3  =  5.00    |
   |  3   |   2    |   10   |  10 / 2  =  5.00    |
   |  4   |   5    |   12   |  12 / 5  =  2.40    |
   |  5   |   1    |    8   |   8 / 1  =  8.00    |
   +------+--------+--------+---------------------+

---------------------------------------------------------------------
STEP 2 : Sort items in decreasing order of ratio
---------------------------------------------------------------------

   +------+------+--------+--------+-------+
   | Rank | Item | Weight | Profit | Ratio |
   +------+------+--------+--------+-------+
   |  1   |  5   |   1    |    8   | 8.00  |
   |  2   |  2   |   3    |   15   | 5.00  |
   |  3   |  3   |   2    |   10   | 5.00  |
   |  4   |  1   |   3    |   10   | 3.33  |
   |  5   |  4   |   5    |   12   | 2.40  |
   +------+------+--------+--------+-------+

   (Items 2 and 3 have the same ratio 5.00; either order gives the
    same final profit.)

   Order of selection :  Item 5 -> Item 2 -> Item 3 -> Item 1 -> Item 4

---------------------------------------------------------------------
STEP 3 : Fill the knapsack greedily (W = 10)
---------------------------------------------------------------------

   Start : Remaining capacity = 10, Profit = 0

   (i) Item 5 (w=1, p=8)
       1 <= 10  -> take FULL item 5,  x5 = 1
       Remaining = 10 - 1 = 9
       Profit    =  0 + 8 = 8

   (ii) Item 2 (w=3, p=15)
       3 <= 9   -> take FULL item 2,  x2 = 1
       Remaining = 9 - 3  = 6
       Profit    = 8 + 15 = 23

   (iii) Item 3 (w=2, p=10)
       2 <= 6   -> take FULL item 3,  x3 = 1
       Remaining = 6 - 2   = 4
       Profit    = 23 + 10 = 33

   (iv) Item 1 (w=3, p=10)
       3 <= 4   -> take FULL item 1,  x1 = 1
       Remaining = 4 - 3   = 1
       Profit    = 33 + 10 = 43

   (v) Item 4 (w=5, p=12)
       5 > 1    -> take only a FRACTION of item 4
       x4        = Remaining / w4 = 1 / 5 = 0.2
       Profit    = 43 + (12 x 1/5) = 43 + 2.4 = 45.4
       Remaining = 1 - 1 = 0          -> knapsack is FULL, stop.

---------------------------------------------------------------------
STEP 4 : Summary Table
---------------------------------------------------------------------

   +------+------+--------+--------+----------+------------+-----------+
   | Step | Item | Weight | Profit | Fraction | Wt. added  | Profit    |
   |      |      |        |        |   (xi)   | (xi * wi)  | (xi * pi) |
   +------+------+--------+--------+----------+------------+-----------+
   |  1   |  5   |   1    |    8   |    1     |    1       |    8.0    |
   |  2   |  2   |   3    |   15   |    1     |    3       |   15.0    |
   |  3   |  3   |   2    |   10   |    1     |    2       |   10.0    |
   |  4   |  1   |   3    |   10   |    1     |    3       |   10.0    |
   |  5   |  4   |   5    |   12   |   1/5    |    1       |    2.4    |
   +------+------+--------+--------+----------+------------+-----------+
   |                                 Total   |   10 kg    |   45.4    |
   +------+------+--------+--------+----------+------------+-----------+

---------------------------------------------------------------------
STEP 5 : Verification
---------------------------------------------------------------------

   Total weight = 1 + 3 + 2 + 3 + (1/5 x 5) = 10 kg   (= W, full)
   Total profit = 8 + 15 + 10 + 10 + 2.4    = 45.4

FINAL ANSWER
------------
   Solution vector  x = (x1, x2, x3, x4, x5) = (1, 1, 1, 1/5, 1)

   Items 1, 2, 3, 5 are taken fully and 1/5 (1 kg) of item 4 is taken.

   Maximum profit = 45.4


=====================================================================
 4. TIME ANALYSIS (ON PAPER)
=====================================================================

   Let n = number of items.

   +---+---------------------------------------+---------------------+
   | # | Step                                  | Time                |
   +---+---------------------------------------+---------------------+
   | 1 | Compute ratio pi/wi for every item    | O(n)                |
   | 2 | Sort items by ratio (Merge/Quick/Tim) | O(n log n)          |
   | 3 | Greedy loop: visit each item once,    | O(n)                |
   |   | O(1) work per item                    |                     |
   +---+---------------------------------------+---------------------+
   |   | TOTAL  T(n) = O(n) + O(n log n) + O(n)| O(n log n)          |
   +---+---------------------------------------+---------------------+

   Sorting is the dominant step, so:

      Time Complexity  = O(n log n)
      (If the items are already sorted by ratio, it is only O(n).)

      Space Complexity = O(n)   (ratio list + solution vector x)

   For this example: n = 5
      ratios   : 5 divisions
      sorting  : about n log2 n = 5 x 2.32 = ~12 comparisons
      greedy   : 5 iterations
      -> very fast, since the work grows only as n log n.

   Comparison with 0-1 Knapsack (Dynamic Programming):
      0-1 Knapsack (DP)        : O(n * W)
      Fractional Knapsack      : O(n log n)   (no table needed)


*/