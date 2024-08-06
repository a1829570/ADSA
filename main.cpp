#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

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



int main() {
    std::string I1, I2;
    int B;

    std::cin >> I1 >> I2 >> B;
    
    std::string sumResult = schoolAddition(I1, I2, B);
    std::cout << sumResult << " " << "0" << " 0" << std::endl;

    return 0;
}

