#include <iostream>

int findGCD(int x, int y) {
    while (x % y != 0) {
        int temp = x;
        x = y;
        y = temp % y;
    }
    return y;
}

int findLCM(unsigned int m, unsigned int n) {
    return (m * n) / findGCD(m, n);
}

int main() {
    int num1, num2;
    std::cout << "Enter two unsigned numbers: ";
    std::cin >> num1 >> num2;
    std::cout << "\nGCD of numbers " << num1 << " and " << num2 << " is " << findGCD(num1, num2);
    std::cout << "\nLCM of numbers " << num1 << " and " << num2 << " is " << findLCM(num1, num2);
}