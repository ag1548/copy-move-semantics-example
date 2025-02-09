#include <iostream>
#include <utility>

class MyInt {
public:
    MyInt() = delete;
    explicit MyInt(int value) {
        pInt  = new int;
        *pInt = value;
    }

    // Copy Constructor
    MyInt(const MyInt & other) noexcept
        : MyInt(*other.pInt) {
        std::cout << "Calling copy constructor" << std::endl;
    }

    // Move Constructor
    MyInt(MyInt && other) noexcept
        : pInt(other.pInt) {
        std::cout << "Calling move constructor" << std::endl;
        other.pInt = nullptr;
    }

    // Copy assignment
    MyInt & operator=(const MyInt & other) {
        std::cout << "Calling copy assignment" << std::endl;
        if (this == &other) {
            return *this;
        }

        MyInt temp(other);
        std::swap(pInt, temp.pInt);

        return *this;
    }

    // Move assignment
    MyInt & operator=(MyInt && other) noexcept {
        std::cout << "Calling move assignment" << std::endl;

        MyInt temp(std::move(other));
        std::swap(pInt, temp.pInt);

        return *this;
    }

    ~MyInt() { delete pInt; }

    int GetValue() const { return *pInt; }

private:
    int * pInt;
};

int main() {
    // Copy constructor
    MyInt myint(5);
    MyInt myotherint = myint;
    std::cout << "myint: " << myint.GetValue() << std::endl;
    std::cout << "myotherint: " << myotherint.GetValue() << std::endl;

    // Move constructor
    MyInt myint2 = std::move(MyInt(8));
    std::cout << "myint2: " << myint2.GetValue() << std::endl;

    // Copy assignment
    MyInt myint3(1);
    myint3 = myint2;
    std::cout << "myint3: " << myint3.GetValue() << std::endl;

    // Move assignment
    MyInt myint4(2);
    myint4 = std::move(MyInt(9));
    std::cout << "myint4: " << myint4.GetValue() << std::endl;

    return 0;
}
