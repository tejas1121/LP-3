#include <iostream>
using namespace std;

// Recursive Function
int fibonacciRecursive(int n)
{
    if (n == 0)
        return 0;

    if (n == 1)
        return 1;

    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

// Non-Recursive (Iterative) Function
void fibonacciIterative(int n)
{
    int a = 0, b = 1, c;

    cout << "Non-Recursive Fibonacci Series: ";

    for (int i = 0; i < n; i++)
    {
        cout << a << " ";

        c = a + b;
        a = b;
        b = c;
    }

    cout << endl;
}

// Main Function
int main()
{
    int n;

    cout << "Enter number of terms: ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Please enter a positive number.";
        return 0;
    }

    // Non-Recursive Method
    fibonacciIterative(n);

    // Recursive Method
    cout << "Recursive Fibonacci Series: ";

    for (int i = 0; i < n; i++)
    {
        cout << fibonacciRecursive(i) << " ";
    }

    cout << endl;

    return 0;
}

/*
4. Time and Space Complexity Analysis
A. Non-Recursive Approach
Time Complexity:
- The loop executes n times.
- Each iteration performs constant-time operations.
Therefore,
\[
T(n)=O(n)
\]

Space Complexity:
- Only three variables (a, b, c) are used.
- No extra data structure is required.
\[
S(n)=O(1)
\]

B. Recursive Approach
Time Complexity:
- Each function call generates two recursive calls.
- The same Fibonacci values are calculated repeatedly.
Recurrence relation:
\[
T(n)=T(n-1)+T(n-2)+O(1)
\]

Therefore,
\[
T(n)=O(2^n)
\]

More precisely, the time complexity is \(O(\phi^n)\), where \(\phi\) is the golden ratio.

Space Complexity:
- Recursive calls are stored in the function call stack.
- Maximum recursion depth is proportional to n.
\[
S(n)=O(n)
\]
*/


/* Don't Write on paper this is for Oral
5. Comparison Table
Parameter	Non-Recursive	Recursive
Technique	Iteration	Function calls
Time Complexity	O(n)	O(2ⁿ)
Space Complexity	O(1)	O(n)
Execution Speed	Faster	Slower
Memory Usage	Less	More
Repeated Calculations	No	Yes
*/