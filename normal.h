#pragma once
#include <iostream>
#include <limits>
using namespace std;

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <stdexcept>

// ģ��Python��print���� - �޲����汾
void print() {
    cout << endl;
}

// ģ��Python��print���� - ���������汾
template<typename T>
void print(const T& arg) {
    cout << arg << endl;
}

// ģ��Python��print���� - ��������汾
template<typename T, typename... Args>
void print(const T& first, const Args&... args) {
    cout << first;
    int dummy[] = { 0, ((cout << args), 0)... };
    (void)dummy; // ����δʹ�ñ�������
    cout << endl;
}

// ģ��Python��input����
string input(const string& prompt = "") {
    if (!prompt.empty()) {
        cout << prompt;
    }
    string line;
    getline(cin, line);
    return line;
}

// ģ��Python��split����
vector<string> split(const string& s, char delimiter = ' ') {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// ģ��Python��range�������򻯰棩
vector<int> range(int start, int stop, int step = 1) {
    vector<int> result;
    for (int i = start; i < stop; i += step) {
        result.push_back(i);
    }
    return result;
}

// ģ��Python��len����
template<typename T>
size_t len(const T& container) {
    return container.size();
}

// ģ��Python��str.format�������򻯰棩
string format(const string& fmt, const vector<string>& args) {
    string result;
    size_t arg_idx = 0;
    for (size_t i = 0; i < fmt.size(); ++i) {
        if (fmt[i] == '{' && i + 1 < fmt.size()) {
            if (fmt[i + 1] == '}') {
                if (arg_idx < args.size()) {
                    result += args[arg_idx++];
                }
                else {
                    result += "{}"; // ��������ʱ����ԭ��
                }
                i++; // ���� '}'
            }
            else if (isdigit(fmt[i + 1])) {
                // ����������ĸ�ʽ�� {0}
                size_t idx_start = i + 1;
                while (idx_start < fmt.size() && isdigit(fmt[idx_start])) {
                    idx_start++;
                }
                if (idx_start < fmt.size() && fmt[idx_start] == '}') {
                    string idx_str = fmt.substr(i + 1, idx_start - i - 1);
                    int idx = stoi(idx_str);
                    if (idx >= 0 && static_cast<size_t>(idx) < args.size()) {
                        result += args[idx];
                    }
                    else {
                        result += "{" + idx_str + "}";
                    }
                    i = idx_start; // ���������� '}'
                }
                else {
                    result += fmt[i]; // ������Ч��������ʽ������ԭ��
                }
            }
            else {
                result += fmt[i]; // ������Ч�ĸ�ʽ������ԭ��
            }
        }
        else {
            result += fmt[i];
        }
    }
    return result;
}

// ģ��Python������ת������
int int_cast(const string& s) {
    try {
        return stoi(s);
    }
    catch (const invalid_argument&) {
        throw invalid_argument("invalid literal for int() with base 10: '" + s + "'");
    }
    catch (const out_of_range&) {
        throw out_of_range("int() argument out of range");
    }
}

double float_cast(const string& s) {
    try {
        return stod(s);
    }
    catch (const invalid_argument&) {
        throw invalid_argument("could not convert string to float: '" + s + "'");
    }
    catch (const out_of_range&) {
        throw out_of_range("float() argument out of range");
    }
}



//int main() {
//    // �������
//    print("��ӭʹ��Python����C++!");
//    string name = input("�������������: ");
//    print("���,", name, "!");
//
//    // ��ѧ����
//    string num_input = input("�������������֣��ÿո�ָ���: ");
//    auto parts = split(num_input);
//    double a = float_cast(parts[0]);
//    double b = float_cast(parts[1]);
//    print(format("{} + {} = {}", { to_string(a), to_string(b), to_string(a + b) }));
//
//    // ѭ��������
//    print("1��5��ż��:");
//    for (int i : range(1, 6)) {
//        if (i % 2 == 0) {
//            print(i);
//        }
//    }
//
//    return 0;
//}