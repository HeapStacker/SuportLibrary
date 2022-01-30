#include "fileSuport.h"
#include "vectorSuport.h"
#include "vectorSuport.h"
#include "terminalSuport.h"

class test {
    int number = 0;
    int hardness = 10;
public:
    test() {
        cout << "test created\n";
    }
    ~test() {
        cout << "test deleted\n";
    }
    string toString() {
        stringstream ss;
        ss << "Test number " << number << "\tTest hardness " << hardness;
        return ss.str();
    }
};

int main(void)
{
    return 0;
}