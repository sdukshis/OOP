#include <iostream>
#include <cmath>
#include <exception>
#include <vector>
#include <numeric>
#include <memory>
#include <iomanip>

class Account {
public:
    explicit Account(int start_balance = 0)
        : balance(start_balance) {}

    virtual ~Account() = default;

    int get_balance() const {
        return balance;
    }

    virtual void deposit(int money) {
        balance += money;
    }

    virtual void withdraw(int money) {
        if (balance < money) {
            throw std::logic_error("Insufficient funds");
        }
        balance -= money;
    }

protected:
    int balance;
};

class AccountWithOverdraft : public Account {
public:
    explicit AccountWithOverdraft(int maximum_overdraft)
        : max_overdraft(maximum_overdraft) {}

    int get_max_overdraft() const {
        return max_overdraft;
    }

    void withdraw(int money) override {
        if (balance + max_overdraft < money) {
            throw std::logic_error("Overdraft limit exceeded");
        }
        balance -= money;
    }

private:
    int max_overdraft;
};

class AccountGroup {
public:
    AccountGroup() {}

    void add_account(std::unique_ptr<Account> account) {
        accounts.emplace_back(std::move(account));
    }

    int total_balance() const {
        int total = 0;
        for (const auto &account : accounts) {
            total += account->get_balance();
        }
        return total;
    }

    void print_report(std::ostream &stream) const {
        stream << "| Account | Balance |\n";
        stream << "|--------:|--------:|\n";
        for (size_t i = 0; i < accounts.size(); ++i) {
            stream << "|" << std::setw(9) << i << "|" << std::setw(9)
                   << accounts[i]->get_balance() << "|\n";
        }
    }

    void transaction(size_t credit, size_t debit, int money) {
        if (credit != debit) {
            accounts.at(credit)->withdraw(money);
            accounts.at(debit)->deposit(money);
        }
    }

private:
    std::vector<std::unique_ptr<Account>> accounts;
};

int main() {
    AccountGroup account_group;

    account_group.add_account(std::make_unique<Account>(100));
    account_group.add_account(std::make_unique<AccountWithOverdraft>(50));

    size_t from;
    size_t to;
    int money;

    do {
        account_group.print_report(std::cout);
        std::cout << "from: ";
        std::cin >> from;
        std::cout << "to: ";
        std::cin >> to;
        std::cout << "money: ";
        std::cin >> money;
        try {
            account_group.transaction(from, to, money);
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
    } while (money != 0);

    return 0;
}
