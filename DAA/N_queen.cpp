
#include <iostream>
using namespace std;

#define MAX 20

class NQueens
{
    int board[MAX][MAX];
    int n;

public:

    // Check whether position is safe
    bool isSafe(int row, int col)
    {
        // Check same column
        for (int r = 0; r < row; r++)
        {
            if (board[r][col] == 1)
                return false;
        }

        // Check upper-left diagonal
        int r = row - 1;
        int c = col - 1;

        while (r >= 0 && c >= 0)
        {
            if (board[r][c] == 1)
                return false;

            r--;
            c--;
        }

        // Check upper-right diagonal
        r = row - 1;
        c = col + 1;

        while (r >= 0 && c < n)
        {
            if (board[r][c] == 1)
                return false;

            r--;
            c++;
        }

        return true;
    }

    // Solve using Backtracking
    bool solve(int row)
    {
        // All Queens placed
        if (row == n)
            return true;

        for (int col = 0; col < n; col++)
        {
            if (isSafe(row, col))
            {
                board[row][col] = 1;

                cout << "Place Q" << row + 1
                     << " at (" << row + 1
                     << ", " << col + 1 << ")" << endl;

                if (solve(row + 1))
                    return true;

                // Backtracking
                board[row][col] = 0;

                cout << "Backtrack: remove Q" << row + 1
                     << " from (" << row + 1
                     << ", " << col + 1 << ")" << endl;
            }
        }

        cout << "Dead end: no safe column for Q"
             << row + 1 << endl;

        return false;
    }

    // Display final matrix
    void printBoard()
    {
        cout << "\n--- Final N-Queens Matrix (1 = Queen) ---\n";

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << board[i][j] << " ";

            cout << endl;
        }

        cout << "\n--- Board ---\n";

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == 1)
                    cout << "Q ";
                else
                    cout << ". ";
            }

            cout << endl;
        }

        // Display Queen positions
        cout << "\nSolution (column of queen in each row) = [";

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == 1)
                {
                    cout << j + 1;

                    if (i != n - 1)
                        cout << ", ";
                }
            }
        }

        cout << "]" << endl;
    }

    // Main function
    void start()
    {
        cout << "Enter value of n: ";
        cin >> n;

        if (n <= 0 || n > MAX)
        {
            cout << "Invalid value of n!";
            return;
        }

        int first_col;

        cout << "Enter column (1-" << n
             << ") of first Queen in row 1: ";
        cin >> first_col;

        if (first_col < 1 || first_col > n)
        {
            cout << "Invalid column!";
            return;
        }

        // Initialize board
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                board[i][j] = 0;
        }

        // Place first Queen
        board[0][first_col - 1] = 1;

        cout << "\nFirst Queen Q1 placed at (1, "
             << first_col << ")" << endl;

        cout << "\n--- Backtracking Steps ---\n";

        if (solve(1))
        {
            printBoard();
        }
        else
        {
            cout << "\nNo solution exists with the first Queen at this position.";
        }
    }
};

int main()
{
    NQueens q;
    q.start();

    return 0;
}
/*
PAPER WORK - EXAMPLE 2 : n = 4, first Queen at (1, 1)
    (shows how BACKTRACKING works)
=====================================================================

---------------------------------------------------------------------
STEP 1 : Q1 fixed at (1,1). Try row 2
---------------------------------------------------------------------

   (2,1) : same column as Q1                               -> X
   (2,2) : |2-1| = |2-1| = 1  same diagonal                -> X
   (2,3) : safe                                            -> Q2 = (2,3)

            Q . . .
            . . Q .

---------------------------------------------------------------------
STEP 2 : Try row 3  (Q1=(1,1), Q2=(2,3))
---------------------------------------------------------------------

   (3,1) : same column as Q1                               -> X
   (3,2) : diagonal with Q2  |3-2| = |2-3| = 1             -> X
   (3,3) : same column as Q2                               -> X
   (3,4) : diagonal with Q2  |3-2| = |4-3| = 1             -> X

   DEAD END  ->  BACKTRACK : remove Q2 from (2,3)

---------------------------------------------------------------------
STEP 3 : Back in row 2, try next column
---------------------------------------------------------------------

   (2,4) : safe                                            -> Q2 = (2,4)

            Q . . .
            . . . Q

---------------------------------------------------------------------
STEP 4 : Try row 3  (Q1=(1,1), Q2=(2,4))
---------------------------------------------------------------------

   (3,1) : same column as Q1                               -> X
   (3,2) : vs Q1 |3-1|=2,|2-1|=1 ok ; vs Q2 |3-2|=1,|2-4|=2 ok
                                                           -> Q3 = (3,2)

            Q . . .
            . . . Q
            . Q . .

---------------------------------------------------------------------
STEP 5 : Try row 4  (Q1=(1,1), Q2=(2,4), Q3=(3,2))
---------------------------------------------------------------------

   (4,1) : same column as Q1                               -> X
   (4,2) : same column as Q3                               -> X
   (4,3) : diagonal with Q3  |4-3| = |3-2| = 1             -> X
   (4,4) : same column as Q2                               -> X

   DEAD END  ->  BACKTRACK : remove Q3 from (3,2)

---------------------------------------------------------------------
STEP 6 : Back in row 3, try remaining columns
---------------------------------------------------------------------

   (3,3) : diagonal with Q2  |3-2| = |3-4| = 1             -> X
   (3,4) : same column as Q2                               -> X

   DEAD END  ->  BACKTRACK : remove Q2 from (2,4)

---------------------------------------------------------------------
STEP 7 : Back in row 2, no columns left after column 4
---------------------------------------------------------------------

   DEAD END for Q2. Q1 is fixed by the user, so we cannot go back
   further.

   RESULT : NO SOLUTION exists for n = 4 with first queen at (1,1).

---------------------------------------------------------------------
STEP 8 : State Space Tree (Example 2)
---------------------------------------------------------------------

                              [ start ]
                                  |
                                x1=1          (given first queen)
                                  |
                             ( Q1 at 1 )
            _______________/   /     \   \_______________
           /                  /       \                  \
        x2=1              x2=2       x2=3               x2=4
          X                 X          |                  |
                                  ( Q2 at 3 )        ( Q2 at 4 )
                                 /  |    |  \       /    |    |   \
                             x3=1 x3=2 x3=3 x3=4 x3=1  x3=2 x3=3 x3=4
                               X    X    X    X    X     |    X    X
                                 DEAD END              |
                               <- backtrack       ( Q3 at 2 )
                                                 /   |   |   \
                                             x4=1 x4=2 x4=3 x4=4
                                               X    X    X    X
                                                  DEAD END
                                                <- backtrack

   Backtracking order (DFS):
     Q1=1 -> Q2=3 -> dead -> back -> Q2=4 -> Q3=2 -> dead -> back
          -> Q3=3,4 killed -> back -> Q2 exhausted -> NO SOLUTION

   This shows that the column chosen for the first queen matters:
   for n = 4 only columns 2 and 3 in row 1 lead to a solution.

*/