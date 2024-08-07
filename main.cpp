#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

// Helper function to find the maximum length of two strings
int maxlen(const std::string& I1, const std::string& I2) {
    return std::max(I1.length(), I2.length());
}

// Helper function to convert a string from a specified base to base-10
long long convertBaseXToBase10(const std::string& number, int base) {
    long long result = 0;
    for (char c : number) {
        int digit = (c >= '0' && c <= '9') ? (c - '0') : (c - 'A' + 10);
        result = result * base + digit;
    }
    return result;
}

// Helper function to convert a base-10 number to a string in a specified base
std::string convertBase10ToBaseX(long long number, int base) {
    if (base < 2 || base > 36) return "Base out of range"; // Base should be between 2 and 36

    if (number == 0) return "0";

    std::string result;
    bool isNegative = (number < 0);
    if (isNegative) number = -number;

    while (number > 0) {
        int remainder = number % base;
        if (remainder < 10) result += (remainder + '0'); // '0' to '9'
        else result += (remainder - 10 + 'A'); // 'A' to 'Z'
        number /= base;
    }

    if (isNegative) result += '-';
    std::reverse(result.begin(), result.end());
    return result;
}

// Addition function in base B
std::string schoolAddition(const std::string& strI1, const std::string& strI2, int B) {
    int len1 = strI1.length();
    int len2 = strI2.length();
    int n = maxlen(strI1, strI2);

    std::string result;
    int carry = 0;

    std::string num1 = std::string(n - len1, '0') + strI1;
    std::string num2 = std::string(n - len2, '0') + strI2;

    for (int i = 0; i < n; i++) {
        int digit1 = num1[num1.length() - 1 - i] - '0';
        int digit2 = num2[num2.length() - 1 - i] - '0';
        int sum = digit1 + digit2 + carry;
        result.push_back((sum % B) + '0');
        carry = sum / B;
    }

    if (carry > 0) {
        result.push_back(carry + '0');
    }

    std::reverse(result.begin(), result.end());
    return result;
}

// Karatsuba multiplication function
std::string karatsuba(std::string strI1, std::string strI2, int base) {
    int n = maxlen(strI1, strI2);

    while (strI1.length() < n) strI1.insert(strI1.begin(), '0');
    while (strI2.length() < n) strI2.insert(strI2.begin(), '0');

    if (n <= 1) {
        int product = (strI1[0] - '0') * (strI2[0] - '0');
        return convertBase10ToBaseX(product, base);
    }

    int k = n / 2;

    std::string a1 = strI1.substr(0, n - k);
    std::string a0 = strI1.substr(n - k);
    std::string b1 = strI2.substr(0, n - k);
    std::string b0 = strI2.substr(n - k);

    std::string P0 = karatsuba(a0, b0, base);
    std::string P1 = karatsuba(a1, b1, base);

    std::string sumA = schoolAddition(a0, a1, base);
    std::string sumB = schoolAddition(b0, b1, base);

    std::string P2 = karatsuba(sumA, sumB, base);

    long long p0 = convertBaseXToBase10(P0, base);
    long long p1 = convertBaseXToBase10(P1, base);
    long long p2 = convertBaseXToBase10(P2, base);

    long long powBaseK = static_cast<long long>(pow(base, k));
    long long powBase2K = static_cast<long long>(pow(base, 2 * k));

    std::string result1 = convertBase10ToBaseX(p1 * powBase2K, base);
    std::string result2 = convertBase10ToBaseX((p2 - p1 - p0) * powBaseK, base);
    std::string result3 = P0;

    std::string finalResult = schoolAddition(result1, result2, base);
    finalResult = schoolAddition(finalResult, result3, base);

    return finalResult;
}

int main() {
    std::string I1, I2;
    int B;

    std::cin >> I1 >> I2 >> B;

    std::string sumResult = schoolAddition(I1, I2, B);
    std::string multiplication = karatsuba(I1, I2, B);

    std::cout << sumResult << " " << multiplication << " 0" << std::endl;

    return 0;
}
