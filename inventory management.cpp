#include <iostream>
#include <string>
#include <stdexcept> // For exception handling
using namespace std;

class Account {
private:
    int accountNumber;
    string customerName;
    double balance;

protected:
    void setBalance(double bal) {
        balance = bal;
    }

public:
    Account(int accNum, string name, double bal) : accountNumber(accNum), customerName(name), balance(bal) {
        if (bal < 0) {
            throw invalid_argument("Initial balance cannot be negative.");
        }
    }

    // Getters and Setters for private members
    int getAccountNumber() const {
        return accountNumber;
    }

    void setAccountNumber(int accNum) {
        accountNumber = accNum;
    }

    string getCustomerName() const {
        return customerName;
    }

    void setCustomerName(const string &name) {
        customerName = name;
    }

    double getBalance() const {
        return balance;
    }

    virtual void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful. New balance: Ksh" << balance << endl;
        } else {
            throw invalid_argument("Deposit amount must be positive.");
        }
    }

    virtual void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful. New balance: Ksh" << balance << endl;
        } else {
            throw runtime_error("Insufficient balance or invalid withdrawal amount.");
        }
    }

    virtual void display() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Customer Name: " << customerName << endl;
        cout << "Balance: Ksh" << balance << endl;
    }

    virtual ~Account() {}
};

class SavingsAccount : public Account {
private:
    double interestRate; // in percentage

public:
    SavingsAccount(int accNum, string name, double bal, double rate)
        : Account(accNum, name, bal), interestRate(rate) {
        if (rate < 0) {
            throw invalid_argument("Interest rate cannot be negative.");
        }
    }

    void calculateInterest() {
        double interest = getBalance() * (interestRate / 100);
        setBalance(getBalance() + interest);
        cout << "Interest calculated and added to balance. New balance: Ksh" << getBalance() << endl;
    }

    void display() const override {
        cout << "....SAVINGS ACCOUNT DETAILS...." << endl;
        Account::display();
        cout << "Interest Rate: " << interestRate << "%" << endl;
    }
};

class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    CurrentAccount(int accNum, string name, double bal, double overdraft)
        : Account(accNum, name, bal), overdraftLimit(overdraft) {
        if (overdraft < 0) {
            throw invalid_argument("Overdraft limit cannot be negative.");
        }
    }

    void withdraw(double amount) override {
        if (amount > 0 && getBalance() + overdraftLimit >= amount) {
            setBalance(getBalance() - amount);
            cout << "Withdrawal successful. New balance: Ksh" << getBalance() << endl;
        } else {
            throw runtime_error("Withdrawal failed. Exceeds overdraft limit.");
        }
    }

    void display() const override {
        cout << "....CURRENT ACCOUNT DETAILS...." << endl;
        Account::display();
        cout << "Overdraft Limit: Ksh" << overdraftLimit << endl;
    }
};

int main() {
    int choice;
    int accountNumber;
    string customerName;
    double balance, interestRate, overdraftLimit, depositAmount, withdrawAmount;

    try {
        cout << "Welcome to the Bank System!\n";
        cout << "1. Create Savings Account\n";
        cout << "2. Create Current Account\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            // Create Savings Account
            cout << "\nEnter the account details for Savings Account:\n";
            cout << "Enter Account Number: ";
            cin >> accountNumber;
            cout << "Enter Customer Name: ";
            cin.ignore();
            getline(cin, customerName);
            cout << "Enter Initial Balance: ";
            cin >> balance;
            cout << "Enter Interest Rate (in %): ";
            cin >> interestRate;

            SavingsAccount savingsAcc(accountNumber, customerName, balance, interestRate);

            cout << "\n....SAVINGS ACCOUNT CREATED....\n";
            savingsAcc.display();

            cout << "Enter amount to deposit in Savings Account: ";
            cin >> depositAmount;
            savingsAcc.deposit(depositAmount);

            savingsAcc.calculateInterest();

            cout << "Enter amount to withdraw from Savings Account: ";
            cin >> withdrawAmount;
            savingsAcc.withdraw(withdrawAmount);

            savingsAcc.display();
        } else if (choice == 2) {
            // Create Current Account
            cout << "\nEnter the account details for Current Account:\n";
            cout << "Enter Account Number: ";
            cin >> accountNumber;
            cout << "Enter Customer Name: ";
            cin.ignore();
            getline(cin, customerName);
            cout << "Enter Initial Balance: ";
            cin >> balance;
            cout << "Enter Overdraft Limit: ";
            cin >> overdraftLimit;

            CurrentAccount currentAcc(accountNumber, customerName, balance, overdraftLimit);

            cout << "\n....CURRENT ACCOUNT CREATED....\n";
            currentAcc.display();

            cout << "Enter amount to deposit in Current Account: ";
            cin >> depositAmount;
            currentAcc.deposit(depositAmount);

            cout << "Enter amount to withdraw from Current Account: ";
            cin >> withdrawAmount;
            currentAcc.withdraw(withdrawAmount);

            cout << "Enter another amount to withdraw from Current Account (test overdraft): ";
            cin >> withdrawAmount;
            currentAcc.withdraw(withdrawAmount);

            currentAcc.display();
        } else {
            throw invalid_argument("Invalid choice! Exiting...");
        }
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
