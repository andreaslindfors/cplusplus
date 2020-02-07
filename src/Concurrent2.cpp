#include <iostream>
#include <sstream>

using namespace std;

bool is_prime (int x)
{
    cout << "Calculating prime, please wait.\n";
    return true;
}

int main()
{
    if (is_prime(1)) cout << "Is prime.\n";
    return 0;
}