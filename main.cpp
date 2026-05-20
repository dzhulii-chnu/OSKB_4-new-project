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
}