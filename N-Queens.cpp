#include <iostream>
#include <vector>
using namespace std;

class Solution
{
private:
    bool canPlaceQueen(int r, int c, vector<string> &ans, int n)
    {
        if (ans[r][c] == 'Q')
            return false;
        for (int i = 0; i < n; ++i)
        {
            if (i != c && ans[r][i] == 'Q')
                return false;
            if (i != r && ans[i][c] == 'Q')
                return false;
            if (i + c - r < n && i + c - r >= 0)
                if (i != r && ans[i][i + c - r] == 'Q')
                    return false;
            if (c + r - i < n && c + r - i >= 0)
                if (i != r && ans[i][c + r - i] == 'Q')
                    return false;
        }
        return true;
    }

    void foo(vector<string> &ans, vector<vector<string>> &allAnswers, int &n, int r)
    {
        if (r == n)
        {
            allAnswers.push_back(ans);
            return;
        }
        for (int c = 0; c < n; ++c)
        {
            if (canPlaceQueen(r, c, ans, n))
            {
                ans[r][c] = 'Q';
                foo(ans, allAnswers, n, r + 1);
                ans[r][c] = '.';
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<string>> allAnswers;
        vector<string> ans(n, string(n, '.'));
        foo(ans, allAnswers, n, 0);
        return allAnswers;
    }
};

int main()
{
    Solution sol;
    auto allAnswers = sol.solveNQueens(4);
    for (auto i : allAnswers)
    {
        for (auto j : i)
            cout << j << "\n";
        cout << "\n";
    }
}

/*

This function appears to be correct, but it will generate the same answer multiple times.
Consider n = 4. One of the solutions is: [".Q..","...Q","Q...","..Q."]
We start by placing queen at coordinates {0,1} and then place the rest to arrive at the solution.
After that all 'Q's are replaced by '.'s to backtrack to previous state.
Now, we have all '.'s again after we reach to the topmost call.
Let us say it places a queen at coordinates {1,3}.
After this call we again start checking from {0,0} as to where we can place the queen.
Clearly we can place it at {0,1}.
This will again result in printing the previous solution.
To prevent this we use row variable as an identifier.
We only increment r to prevent the algorithm from going back and printing the same solution over and over again.

void foo(vector<string> &ans, vector<vector<string>> &allAnswers, int &n, int queensLeft)
{
    if (!queensLeft)
    {
        // All queens are placed so we can add this ans to allAnswers.
        allAnswers.push_back(ans);
        return;
    }

    for (int r = 0; r < n; ++r)
        for (int c = 0; c < n; ++c)
        {
            if (canPlaceQueen(r, c, ans, n))
            {
                ans[r][c] = 'Q';
                foo(ans, allAnswers, n, queensLeft - 1);
                ans[r][c] = '.';
            }
        }
}

foo(ans, allAnswers, n, n);
*/
