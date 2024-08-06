#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

// Function declarations
int maxlen(const std::string& I1, const std::string& I2);
std::string schoolAddition(const std::string& strI1, const std::string& strI2, int B);
std::string karatsuba(const std::string& a, const std::string& b);

// Helper functions for Karatsuba
std::pair<std::string, std::string> split(const std::string& num, int mid);
std::string addStrings(const std::string& num1, const std::string& num2);
std::string subtractStrings(const std::string& num1, const std::string& num2);
std::string padZeros(const std::string& str, int numZeros);

int main() {
    std::string I1, I2;
    int B;

    std::cin >> I1 >> I2 >> B;
    
    std::string sumResult = schoolAddition(I1, I2, B);
    std::string productResult = karatsuba(I1, I2);

    std::cout << sumResult << " " << productResult << " 0" << std::endl;

    return 0;
}

int maxlen(const std::string& I1, const std::string& I2) {
    return std::max(I1.length(), I2.length());
}

std::string schoolAddition(const std::string& strI1, const std::string& strI2, int B) {
    int len1 = strI1.length();
    int len2 = strI2.length();
    int n = maxlen(strI1, strI2);
    
    std::string result;
    int carry = 0;

    // Make sure both strings are of the same length by padding with zeros
    std::string num1 = std::string(n - len1, '0') + strI1;
    std::string num2 = std::string(n - len2, '0') + strI2;

    for (int i = 0; i < n; i++) {
        int digit1 = num1[num1.length() - 1 - i] - '0';
        int digit2 = num2[num2.length() - 1 - i] - '0';
        int sum = digit1 + digit2 + carry;
        result.push_back((sum % B) + '0');
        carry = sum / B;
    }

    // account for the last carry value, as it is the last sum value
    if (carry > 0) {
        result.push_back(carry + '0');
    }

    std::reverse(result.begin(), result.end());
    return result;
}

std::pair<std::string, std::string> split(const std::string& num, int mid) {
    return { num.substr(0, mid), num.substr(mid) };
}

std::string addStrings(const std::string& num1, const std::string& num2) {
    std::string result;
    int carry = 0, i = num1.size() - 1, j = num2.size() - 1;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += num1[i--] - '0';
        if (j >= 0) sum += num2[j--] - '0';
        result.push_back(sum % 10 + '0');
        carry = sum / 10;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

std::string subtractStrings(const std::string& num1, const std::string& num2) {
    std::string result;
    int borrow = 0, i = num1.size() - 1, j = num2.size() - 1;
    while (i >= 0 || j >= 0) {
        int diff = borrow;
        if (i >= 0) diff += num1[i--] - '0';
        if (j >= 0) diff -= num2[j--] - '0';
        if (diff < 0) {
            diff += 10;
            borrow = -1;
        } else {
            borrow = 0;
        }
        result.push_back(diff + '0');
    }
    while (result.size() > 1 && result.back() == '0') {
        result.pop_back();
    }
    std::reverse(result.begin(), result.end());
    return result;
}

std::string padZeros(const std::string& str, int numZeros) {
    return str + std::string(numZeros, '0');
}

std::string karatsuba(const std::string& a, const std::string& b) {
    int n = maxlen(a, b);
    if (n < 4) {
        return std::to_string(std::stoi(a) * std::stoi(b));
    }
    int k = (n + 1) / 2;

    std::pair<std::string, std::string> aSplit = split(a, a.size() - k);
    std::pair<std::string, std::string> bSplit = split(b, b.size() - k);

    std::string a1 = aSplit.first;
    std::string a0 = aSplit.second;
    std::string b1 = bSplit.first;
    std::string b0 = bSplit.second;

    std::string P0 = karatsuba(a0, b0);
    std::string P2 = karatsuba(a1, b1);
    std::string P1 = karatsuba(addStrings(a0, a1), addStrings(b0, b1));

    std::string term1 = padZeros(P2, 2 * k);
    std::string term2 = padZeros(subtractStrings(subtractStrings(P1, P2), P0), k);
    
    return addStrings(addStrings(term1, term2), P0);
}
