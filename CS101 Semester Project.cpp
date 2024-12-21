#include <iostream>
#include <string>
#include <fstream>
using namespace std;


void saveExpenses(const string categories[], const double expenses[], int count, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Error opening file for writing.\n";
        return;
    }
    for (int i = 0; i < count; i++) {
        file << categories[i] << " " << expenses[i] << endl;
    }
    file.close();
    cout << "Expenses saved to " << filename << endl;
}


void loadExpenses(string categories[], double expenses[], int& count, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "No previous expenses found. Starting fresh.\n";
        return;
    }
    count = 0;
    while (file >> categories[count] >> expenses[count]) {
        count++;
    }
    file.close();
    cout << "Expenses loaded from " << filename << endl;
}


void addExpense(string categories[], double expenses[], int& count, int maxExpenses) {
    if (count >= maxExpenses) {
        cout << "Expense limit reached. Cannot add more expenses.\n";
        return;
    }
    
    cout << "Enter expense category (e.g., Food, Entertainment, Bills): ";
    cin >> categories[count];
    cout << "Enter amount spent: ";
    cin >> expenses[count];
    
    count++;
}

void displayExpenses(const string categories[], const double expenses[], int count) {
    cout << "\n--- Expense List ---\n";
    for (int i = 0; i < count; i++) {
        cout << "Category: " << categories[i] << " - Amount: $" << expenses[i] << endl;
    }
}


double calculateTotal(const double expenses[], int count) {
    double total = 0;
    for (int i = 0; i < count; i++) {
        total += expenses[i];
    }
    return total;
}


void displayByCategory(const string categories[], const double expenses[], int count, const string& targetCategory) {
    cout << "\n--- Expenses for Category: " << targetCategory << " ---\n";
    double categoryTotal = 0;
    bool found = false;

    for (int i = 0; i < count; i++) {
        if (categories[i] == targetCategory) {
            cout << "Amount: $" << expenses[i] << endl;
            categoryTotal += expenses[i];
            found = true;
        }
    }
    
    if (found) {
        cout << "Total for " << targetCategory << ": $" << categoryTotal << endl;
    } else {
        cout << "No expenses found for this category.\n";
    }
}

int main() {
    const int maxExpenses = 100;
    string categories[maxExpenses];
    double expenses[maxExpenses];
    int count = 0;
    string filename = "expenses.txt";

    loadExpenses(categories, expenses, count, filename);
    
    int choice;
    do {
        cout << "\n--- Expense Tracker Menu ---\n";
        cout << "1. Add Expense\n";
        cout << "2. Display All Expenses\n";
        cout << "3. Display Total Expenses\n";
        cout << "4. Display Expenses by Category\n";
        cout << "5. Save and Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                addExpense(categories, expenses, count, maxExpenses);
                break;
            case 2:
                displayExpenses(categories, expenses, count);
                break;
            case 3: {
                double total = calculateTotal(expenses, count);
                cout << "Total Expenses: $" << total << endl;
                break;
            }
            case 4: {
                string category;
                cout << "Enter category to display: ";
                cin >> category;
                displayByCategory(categories, expenses, count, category);
                break;
            }
            case 5:
                saveExpenses(categories, expenses, count, filename);
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
    
    return 0;
}
