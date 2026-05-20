#include <iostream>
using namespace std;
class VectorLong
{
public:
    long* data;
    int size;
    int codeError;
    static int count;
    // 0 -немає помилки, 1 - не вистачило памʼяті 2- вийшли за межі 3 - не коректні дані(ділення на 0)

    VectorLong() {
        size = 1;
        data = new(nothrow) long[size];
        if (!data) {
            codeError = 1;
            return;
        }
        data[0] = 0;
        codeError = 0;
        count++;
    }

    VectorLong(int size)
    {
        this->size = size;
        data = new(nothrow) long[size];
        if (!data) { codeError = 1; return; }
        for (int i = 0; i < size; i++) data[i] = 0;
        codeError = 0;
        count++;
    }

    // БАГ 1 ВИПРАВЛЕНО: додано this->size = size;
    // БАГ 2 ВИПРАВЛЕНО: count++ один раз після циклу, а не всередині циклу
    VectorLong(int size, long value)
    {
        this->size = size;
        data = new(nothrow) long[size];
        if (!data)
        {
            codeError = 1;
            return;
        }
        for (int i = 0; i < size; i++)
        {
            data[i] = value;
        }
        codeError = 0;
        count++;
    }


    VectorLong(const VectorLong& other)
    {
        size = other.size;
        data = new(nothrow) long[size];
        if (!data)
        {
            codeError = 1;
            return;
        }
        for (int i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
        codeError = other.codeError;
        count++;
    }

    ~VectorLong() {
        delete[] data;
        count--;
    }

    void print() const {
        for (int i = 0; i < size; i++)
        {
            cout << data[i] << " ";
        }
        cout << endl;
    }
    void set(int index, long value) {
        if (index >= size) {
            codeError = 2;
            return;
        }
        data[index] = value;
        codeError = 0;
    }

    long get(int index) {
        if (index >= size) {
            codeError = 2;
            return 0;
        }
        codeError = 0;
        return data[index];
    }

    VectorLong& operator++()
    {
        for (int i = 0; i < size; i++)
        {
            ++data[i];
        }
        return *this;
    }
    VectorLong operator++(int)
    {
        VectorLong tmp = *this;
        ++(*this);
        return tmp;
    }
    VectorLong& operator--()
    {
        for (int i = 0; i < size; i++)
        {
            --data[i];
        }
        return *this;
    }
    VectorLong operator--(int)
    {
        VectorLong tmp = *this;
        --(*this);
        return tmp;
    }

    bool operator !()const
    {
        if (size != 0)
        {
            return true;
        }
        else return false;
    }
    VectorLong operator~()
    {
        VectorLong tmp = *this;
        for (int i = 0; i < tmp.size; i++)
        {
            tmp.data[i] = ~data[i];
        }
        return tmp;
    }

    VectorLong operator-()
    {
        VectorLong tmp = *this;
        for (int i = 0; i < tmp.size; i++)
        {
            tmp.data[i] = -data[i];
        }
        return tmp;
    }
    VectorLong& operator=(const VectorLong& other) {
        if (this == &other)
            return *this;

        delete[] data;

        size = other.size;
        data = new(nothrow) long[size];
        if (!data) {
            codeError = 1;
            return *this;
        }

        for (int i = 0; i < size; i++)
            data[i] = other.data[i];

        codeError = other.codeError;
        return *this;
    }
    VectorLong& operator+=(const VectorLong& other) {
        int s = min(size, other.size);
        for (int i = 0; i < s; i++)
        {
            data[i] += other.data[i];
        }
        return *this;
    }
    VectorLong& operator-=(const VectorLong& other)
    {
        int s = min(size, other.size);
        for (int i = 0; i < s; i++)
        {
            data[i] -= other.data[i];
        }
        return *this;
    }
    VectorLong& operator*=(long value)
    {
        for (int i = 0; i < size; i++)
        {
            data[i] *= value;
        }
        return *this;
    }
    VectorLong& operator/=(long value)
    {
        if (value == 0)
        {
            codeError = 3;
            return *this;
        }
        for (int i = 0; i < size; i++)
        {
            data[i] /= value;
            return *this;
        }
    }
    VectorLong& operator%=(long value)
    {
        if (value != 0)
        {
            for (int i = 0; i < size; i++)
            {
                data[i] %= value;
            }
            codeError = 0;
        }
        else codeError = 3;
        return *this;
    }
    VectorLong& operator|=(VectorLong& other)
    {
        int s = min(size, other.size);
        for (int i = 0; i < s; i++)
        {
            data[i] |= other.data[i];
        }
        return *this;
    }
    VectorLong& operator^=(VectorLong& other)
    {
        int s = min(size, other.size);
        for (int i = 0; i < s; i++)
        {
            data[i] ^= other.data[i];
        }
        return *this;
    }
    VectorLong& operator&=(VectorLong& other)
    {
        int s = min(size, other.size);
        for (int i = 0; i < s; i++)
        {
            data[i] &= other.data[i];
        }
        return *this;
    }
    VectorLong operator+(const VectorLong& other) {
        int s = min(size, other.size);
        VectorLong result(s, 0);
        for (int i = 0; i < s; i++) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }
    VectorLong operator-(const VectorLong& other)
    {
        int s = min(size, other.size);
        VectorLong result(s, 0);
        for (int i = 0; i < s; i++)
        {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }
    VectorLong operator*(long value)const
    {
        VectorLong tmp(*this);
        for (int i = 0; i < tmp.size; i++)
        {
            tmp.data[i] = data[i] * value;
        }
        return tmp;
    }
    VectorLong operator/(long value)
    {
        VectorLong tmp(*this);
        if (value == 0)
        {
            codeError = 3;
        }
        else {
            for (int i = 0; i < tmp.size; i++)
            {
                tmp.data[i] = data[i] / value;
            }
        }
        return tmp;
    }
    VectorLong operator%(long value)
    {
        VectorLong tmp(*this);
        if (value == 0)
        {
            codeError = 3;
        }
        else
        {
            for (int i = 0; i < tmp.size; i++)
            {
                tmp.data[i] = data[i] % value;
            }
        }
        return tmp;
    }

    VectorLong operator&(const VectorLong& other) const {
        int s = min(size, other.size);
        VectorLong tmp(*this);
        for (int i = 0; i < s; i++) {
            tmp.data[i] = data[i] & other.data[i];
        }
        return tmp;
    }

    VectorLong operator^(const VectorLong& other) const
    {
        int s = min(size, other.size);
        VectorLong tmp(*this);
        for (int i = 0; i < s; i++)
        {
            tmp.data[i] = data[i] ^ other.data[i];
        }
        return tmp;
    }
    VectorLong operator|(const VectorLong& other) const
    {
        int s = min(size, other.size);
        VectorLong tmp(*this);
        for (int i = 0; i < s; i++)
        {
            tmp.data[i] = data[i] | other.data[i];
        }
        return tmp;
    }

    friend ostream& operator<<(ostream& os, const VectorLong& v);
    friend istream& operator>>(istream& is, VectorLong& v);

    bool operator==(const VectorLong& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; i++)
            if (data[i] != other.data[i]) return false;
        return true;
    }

    bool operator!=(const VectorLong& other) const {
        return !(*this == other);
    }

    long& operator[](int index) {
        if (index < 0 || index >= size) {
            codeError = 2;
            return data[size - 1];
        }
        codeError = 0;
        return data[index];
    }
    long& operator()(int index) {
        if (index < 0 || index >= size) {
            codeError = 2;
            return data[size - 1];
        }
        codeError = 0;
        return data[index];
    }
    bool operator>(const VectorLong& other) const {
        int s = min(size, other.size);
        for (int i = 0; i < s; i++) {
            if (data[i] <= other.data[i])
                return false;
        }
        return true;
    }
    bool operator>=(const VectorLong& other) const {
        int s = min(size, other.size);
        for (int i = 0; i < s; i++) {
            if (data[i] < other.data[i])
                return false;
        }
        return true;
    }
    bool operator<(const VectorLong& other) const {
        int s = min(size, other.size);
        for (int i = 0; i < s; i++) {
            if (data[i] >= other.data[i])
                return false;
        }
        return true;
    }
    bool operator<=(const VectorLong& other) const {
        int s = min(size, other.size);
        for (int i = 0; i < s; i++) {
            if (data[i] > other.data[i])
                return false;
        }
        return true;
    }

    static int getCount() {
        return count;
    }
};

int VectorLong::count = 0;

ostream& operator<<(ostream& os, const VectorLong& v) {
    for (int i = 0; i < v.size; i++)
        os << " " << v.data[i] << " ";
    return os;
}

istream& operator>>(istream& is, VectorLong& v) {
    for (int i = 0; i < v.size; i++)
        is >> v.data[i];
    return is;
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
void Task1()
{
    cout << "test const 1: 1 element = 0: " << endl;
    VectorLong v1;
    v1.print();

    cout << "test const 2: n element = 0: " << endl;
    VectorLong v2(3);
    v2.print();

    cout << "test const 3: n element = s: " << endl;
    VectorLong v3(3, 4);
    v3.print();
    cout << "test ++v; v++; --v; v--\n";
    VectorLong v4(3, 5);
    v4.print();
    ++v4; v4.print();//префіксний
    v4++; v4.print();//постфіксний
    --v4; v4.print();
    v4--; v4.print();

    cout << "test !v4 = " << boolalpha << !v4 << "\n";// без boolalpha true =1
    VectorLong v5 = ~v3;// 0->1 a yaksho 5=-(x+1)
    v5.print();
    VectorLong v6 = -v3;
    v6.print();
    cout<<"test +=/-=/*=/=/%="<<endl;
    VectorLong v7(3, 2);
    VectorLong v8(3, 4);
    v7.print();
    v8.print();
    (v7 += v8).print();
    (v7 -= v8).print();
    (v7 *= 2).print();
    (v7 /= 3).print();
    (v7 %= 3).print();
    cout<< "test bit operation"<<endl;
    VectorLong v9(3, 1010);
    VectorLong v10(3, 1011);
    (v9 |= v10).print();
    (v9 &= v10).print();
    (v9 ^= v10).print();
    cout<< "test aref operation"<<endl;
    VectorLong v11(3,  4);
    VectorLong v12(3,  5);
    (v11 + v12).print();
    (v11 - v12).print();
    (v11 * 2).print();
    (v11 / 3).print();
    (v11 % 3).print();
    cout<< "test bit binar operation"<<endl;
    VectorLong v13(3,  0b1000L);//8
    VectorLong v14(3,  0b1011L);//11
    (v13 | v14).print();
    (v13 & v14).print();
    (v13 ^ v14).print();
    cout<< "test io"<<endl;
    VectorLong vio(3, 7L);
    cout << "vio = " << vio << "\n";
    VectorLong x(3, 5), y(3, 3);
    x.print(); y.print();
    cout << "x >  y: " << (x >  y) << "\n";
    cout << "x >= y: " << (x >= y) << "\n";
    cout << "x <  y: " << (x <  y) << "\n";
    cout << "x <= y: " << (x <= y) << "\n";
    cout << "x == y: " << (x == y) << "\n";
    cout << "x != y: " << (x != y) << "\n";
    cout << "test index"<<endl;
    cout << "x[2] = " << x[2] << "\n";
    cout << "num of value =  " << VectorLong::getCount() << endl;
}
void Task2() {
    Email email1;
    add_database(email1, "Olishuk@gmail.com", "O O Olishuk");
    add_database(email1, "pararuri@gmail.net", "D D Dzhulii");

    cout << email1;

    cout << "\ntest [] email->pib\n";
    cout << email1["pararuri@gmail.net"] << "\n";
    cout << "codeError=" << email1.codeError << "\n";

    cout << "\ntest () pib->email\n";
    cout << email1("D D Dzhulii") << "\n";
    cout << "codeError=" << email1.codeError << "\n";


}
int main()
{
    int choice;

    do {
        cout << endl;
        cout << "MENU" << endl;
        cout << "1 - Task 1" << endl;
        cout << "2 - Task 2" << endl;

        cout << "0 - Exit" << endl;
        cout << "Choose: ";
        cin >> choice;

        switch (choice)
        {
        case 1: Task1(); break;
        case 2: Task2(); break;

        case 0: cout << "Exit program" << endl; break;
        default: cout << "Wrong choice" << endl;
        }

    } while (choice != 0);

    return 0;
}