#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int weight;
    int value;
};

bool val_we_ratio(const Item &item1, const Item &item2) {
    double ratio1 = static_cast<double>(item1.value) / item1.weight;
    double ratio2 = static_cast<double>(item2.value) / item2.weight;
    return ratio1 > ratio2;
}

double Fractional(vector<Item> &items, int capacity) {
    sort(items.begin(), items.end(), val_we_ratio);

    double totalValue = 0.0;
    cout << "Item      Weight    Value    Value/Weight Ratio\n";
    for (int i = 0; i < items.size(); i++) {
        cout << items[i].weight << "\t\t" << items[i].value << "\t\t";
        cout << fixed << static_cast<double>(items[i].value) / items[i].weight << "\n";
    }

    cout << "\nItems in Knapsack:\n";
    cout << "Item      Weight    Value\n";

    for (const Item &item : items) {
        if (capacity >= item.weight) {
            cout << capacity << "\t\t" << item.weight << "\t\t" << item.value << "\n";
            totalValue += item.value;
            capacity -= item.weight;
        } else {
            double fraction = static_cast<double>(capacity) / item.weight;
            cout << capacity << "\t\t" << item.weight << "\t\t";
            cout << fixed << fraction * item.value << "\n";
            totalValue += (fraction * item.value);
            break;
        }
    }
    return totalValue;
}

int main() {
    int numItems, capacity;
    cout << "Enter the number of items: ";
    cin >> numItems;

    cout << "Enter capacity of knapsack: ";
    cin >> capacity;

    vector<Item> items(numItems);
    cout << "Enter the weight and value of each item:\n";
    for (int i = 0; i < numItems; i++) {
        cout << "Item " << i + 1 << ": ";
        cin >> items[i].weight >> items[i].value;
    }

    double maxValue = Fractional(items, capacity);
    cout << "\nMax value is: " << fixed << maxValue << endl;

    return 0;
}
