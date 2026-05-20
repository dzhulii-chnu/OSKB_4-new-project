#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct database {
    string email;
    string fullname;
};

class Email {
private:
    vector<database> data;

public:
    int codeError; // 0 - ок, 1 - не знайдено

    Email() : codeError(0) {}

    friend void add_database(Email& dir, string email, string name);
    friend ostream& operator<<(ostream& os, const Email& dir);
    friend istream& operator>>(istream& is, Email& dir);

    // email -> pib
    string& operator[](const string& email_key) {
        for (auto& other : data) {
            if (other.email == email_key) {
                codeError = 0;
                return other.fullname;
            }
        }
        codeError = 1;
        static string empty = "";
        return empty;
    }

    // pib -> email
    string operator()(const string& fullname_key) {
        for (auto& other : data) {
            if (other.fullname == fullname_key) {
                codeError = 0;
                return other.email;
            }
        }
        codeError = 1;
        return "";
    }
};

void add_database(Email& dir, string email, string name) {
    dir.data.push_back({email, name});
}

ostream& operator<<(ostream& os, const Email& dir) {
    for (const auto& other : dir.data)
        os << other.email << " - " << other.fullname << "\n";
    return os;
}

istream& operator>>(istream& is, Email& dir) {
    int n;
    cout << "counter of valume: ";
    is >> n;
    is.ignore();
    for (int i = 0; i < n; i++) {
        string email, fullname;
        cout << "Email: ";
        getline(is, email);
        cout << "fullname: ";
        getline(is, fullname);
        add_database(dir, email, fullname);
    }
    return is;
}