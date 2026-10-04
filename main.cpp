#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

struct Expense {
    string name;
    string category;
    double amount;
};

int getInteger(const string& message) {
    int value;
    while (true) {
        cout << message;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input! Please enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double getAmount() {
    double amount;
    while (true) {
        cout << "Enter amount: ";
        if (cin >> amount && amount > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return amount;
        }
        cout << "Invalid amount! Please enter a positive number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string getText(const string& message) {
    string text;
    while (true) {
        cout << message;
        getline(cin, text);
        if (!text.empty()) return text;
        cout << "Input cannot be empty. Please try again.\n";
    }
}

void addExpense(vector<Expense>& expenses) {
    Expense expense;
    cout << "\n===== Add Expense =====\n";
    expense.name = getText("Enter expense name: ");
    expense.category = getText("Enter category: ");
    expense.amount = getAmount();
    expenses.push_back(expense);
    cout << "\nExpense added successfully!\n";
}

void listExpenses(const vector<Expense>& expenses) {
    cout << "\n===== All Expenses =====\n";
    if (expenses.empty()) {
        cout << "No expenses recorded yet.\n";
        return;
    }

    cout << left << setw(5) << "No."
         << setw(25) << "Name"
         << setw(20) << "Category"
         << "Amount\n";
    cout << string(65, '-') << '\n';

    for (size_t i = 0; i < expenses.size(); ++i) {
        cout << left << setw(5) << i + 1
             << setw(25) << expenses[i].name
             << setw(20) << expenses[i].category
             << "Rs. " << fixed << setprecision(2)
             << expenses[i].amount << '\n';
    }
}

double calculateTotal(const vector<Expense>& expenses) {
    double total = 0;
    for (const Expense& expense : expenses)
        total += expense.amount;
    return total;
}

void categoryTotal(const vector<Expense>& expenses) {
    cout << "\n===== Category Total =====\n";
    if (expenses.empty()) {
        cout << "No expenses recorded yet.\n";
        return;
    }

    string category = getText("Enter category: ");
    double total = 0;
    bool found = false;

    for (const Expense& expense : expenses) {
        if (expense.category == category) {
            total += expense.amount;
            found = true;
        }
    }

    if (found)
        cout << "Total for " << category << ": Rs. "
             << fixed << setprecision(2) << total << '\n';
    else
        cout << "No expenses found in this category.\n";
}

void overallTotal(const vector<Expense>& expenses) {
    cout << "\n===== Overall Total =====\n";
    cout << "Total Expenses: Rs. "
         << fixed << setprecision(2)
         << calculateTotal(expenses) << '\n';
}

void showMenu() {
    cout << "\n====================================\n";
    cout << "          EXPENSE TRACKER\n";
    cout << "====================================\n";
    cout << "1. Add Expense\n";
    cout << "2. List Expenses\n";
    cout << "3. Category Total\n";
    cout << "4. Overall Total\n";
    cout << "5. Exit\n";
    cout << "====================================\n";
}

int main() {
    vector<Expense> expenses;

    cout << "Welcome to the Expense Tracker!\n";

    while (true) {
        showMenu();
        int choice = getInteger("Enter your choice (1-5): ");

        switch (choice) {
            case 1: addExpense(expenses); break;
            case 2: listExpenses(expenses); break;
            case 3: categoryTotal(expenses); break;
            case 4: overallTotal(expenses); break;
            case 5:
                cout << "\nThank you for using Expense Tracker!\n";
                cout << "Program exited successfully.\n";
                return 0;
            default:
                cout << "Invalid choice! Please select 1 to 5.\n";
        }
    }
}
