#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item{
    int weight;
    int value;
};

int knapsack(int capacity, vector<int> &weights, vector<int> &values)
{
    int numItems = weights.size();
    vector<vector<int>> dp(numItems + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= numItems; ++i)
    {
        for (int w = 1; w <= capacity; ++w)
        {
            if (weights[i - 1] <= w)
            {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[numItems][capacity];
}

int main(){
    int numItems, capacity;
            cout << "\nEnter the number of items: ";
            cin >> numItems;

            vector<int> weights(numItems);
            vector<int> values(numItems);

            cout << "Enter the weight and value of each item:" << endl;
            for (int i = 0; i < numItems; ++i)
            {
                cin >> weights[i] >> values[i];
            }

            cout << "Enter the capacity of the knapsack: ";
            cin >> capacity;

            int maxValue = knapsack(capacity, weights, values);

            cout << "\nThe maximum value that can be obtained is: " << maxValue << endl;
}