#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// Define helper functions

string padZeros(string num, int targetLength) {
    while (num.length() < targetLength) {
        num = '0' + num;
    }
    return num;
}

string trimLeadingZeros(string num) {
    while (!num.empty() && num[0] == '0') {
        num.erase(0, 1);
    }
    return num.empty() ? "0" : num;
}

string appendZeros(string num, int count) {
    while (count-- > 0) {
        num += '0';
    }
    return num;
}

void adjustLength(string &num1, string &num2) {
    num1 = trimLeadingZeros(num1);
    num2 = trimLeadingZeros(num2);
    int maxLength = max(num1.length(), num2.length());
    num1 = padZeros(num1, maxLength);
    num2 = padZeros(num2, maxLength);
}

string addStrings(string num1, string num2, int base) {
    adjustLength(num1, num2);
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());

    string sum = "";
    int carry = 0;

    for (int i = 0; i < max(num1.length(), num2.length()); i++) {
        int digit1 = num1[i] - '0';
        int digit2 = num2[i] - '0';
        int tempSum = digit1 + digit2 + carry;

        if (tempSum < base) {
            carry = 0;
        } else {
            carry = tempSum / base;
            tempSum %= base;
        }

        sum += (tempSum + '0');
    }

    if (carry != 0) {
        sum += (carry + '0');
    }

    reverse(sum.begin(), sum.end());
    return trimLeadingZeros(sum);
}

string subtractStrings(string num1, string num2, int base) {
    adjustLength(num1, num2);
    string difference = "";
    int borrow = 0;

    for (int i = num1.length() - 1; i >= 0; i--) {
        int digit1 = num1[i] - '0';
        int digit2 = num2[i] - '0';
        int tempDiff = digit1 - digit2 - borrow;

        if (tempDiff < 0) {
            tempDiff += base;
            borrow = 1;
        } else {
            borrow = 0;
        }

        difference = to_string(tempDiff) + difference;
    }

    return trimLeadingZeros(difference);
}

string multiplySingleDigit(string num1, string num2, int base) {
    int singleDigit = num2[0] - '0';
    string result = "0";

    for (int i = 0; i < singleDigit; i++) {
        result = addStrings(result, num1, base);
    }

    return result;
}

string karatsubaMultiply(string num1, string num2, int base) {
    num1 = trimLeadingZeros(num1);
    num2 = trimLeadingZeros(num2);

    if (num1 == "0" || num2 == "0") return "0";
    int length = max(num1.length(), num2.length());

    if (length <= 1) return multiplySingleDigit(num1, num2, base);

    if (length % 2 != 0) length++;
    int halfLength = length / 2;

    num1 = padZeros(num1, length);
    num2 = padZeros(num2, length);

    string high1 = num1.substr(0, halfLength);
    string low1 = num1.substr(halfLength);
    string high2 = num2.substr(0, halfLength);
    string low2 = num2.substr(halfLength);

    string z2 = karatsubaMultiply(high1, high2, base);
    string z0 = karatsubaMultiply(low1, low2, base);
    string z1 = subtractStrings(
        subtractStrings(
            karatsubaMultiply(addStrings(high1, low1, base), addStrings(high2, low2, base), base),
            z2,
            base),
        z0,
        base);

    z2 = appendZeros(z2, 2 * halfLength);
    z1 = appendZeros(z1, halfLength);

    return addStrings(addStrings(z2, z1, base), z0, base);
}

int main() {
    string num1, num2, baseStr;
    cin >> num1 >> num2 >> baseStr;

    int base = stoi(baseStr);

    string sum = trimLeadingZeros(addStrings(num1, num2, base));
    string product = trimLeadingZeros(karatsubaMultiply(num1, num2, base));

    cout << sum << " " << product << " 0" << endl;

    return 0;
}
