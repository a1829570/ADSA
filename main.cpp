#include <iostream>
#include <string>
#include <algorithm>

int maxlen(std::string I1, std::string I2) {

    if (I1.length() >= I2.length()) {

        return I1.length();

    }

    else {

        return I2.length();
    }
}

std::string schoolAddition(std::string strI1, std::string strI2, int B) {

    // calculate the length of the bigger integer to set bounds for for loop
    int n = maxlen(strI1, strI2);
    std::string result;
    int carry = 0;

    for(int i = 0; i < n; i++) {

        int sum = (strI1[strI1.length() - 1 - i] - '0') + (strI2[strI2.length() - 1 - i] - '0') + carry;
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

int main () {

    int I1, I2, B;

    std::cin >> I1 >> I2 >> B;
    std::string strI1 = std::to_string(I1);
    std::string strI2 = std::to_string(I2);

    std::string result = schoolAddition(strI1, strI2, B);

    std::cout << result << std::endl;

    return 0;
}

