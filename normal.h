#pragma once
#include <iostream>
#include <limits>
using namespace std;

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <stdexcept>

// 模拟Python的print函数 - 无参数版本
void print() {
    cout << endl;
}

// 模拟Python的print函数 - 单个参数版本
template<typename T>
void print(const T& arg) {
    cout << arg << endl;
}

// 模拟Python的print函数 - 多个参数版本
template<typename T, typename... Args>
void print(const T& first, const Args&... args) {
    cout << first;
    int dummy[] = { 0, ((cout << args), 0)... };
    (void)dummy; // 避免未使用变量警告
    cout << endl;
}

// 模拟Python的input函数
string input(const string& prompt = "") {
    if (!prompt.empty()) {
        cout << prompt;
    }
    string line;
    getline(cin, line);
    return line;
}

// 模拟Python的split函数
vector<string> split(const string& s, char delimiter = ' ') {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// 模拟Python的range函数（简化版）
vector<int> range(int start, int stop, int step = 1) {
    vector<int> result;
    for (int i = start; i < stop; i += step) {
        result.push_back(i);
    }
    return result;
}

// 模拟Python的len函数
template<typename T>
size_t len(const T& container) {
    return container.size();
}

// 模拟Python的str.format函数（简化版）
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
                    result += "{}"; // 参数不足时保持原样
                }
                i++; // 跳过 '}'
            }
            else if (isdigit(fmt[i + 1])) {
                // 处理带索引的格式如 {0}
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
                    i = idx_start; // 跳过索引和 '}'
                }
                else {
                    result += fmt[i]; // 不是有效的索引格式，保持原样
                }
            }
            else {
                result += fmt[i]; // 不是有效的格式，保持原样
            }
        }
        else {
            result += fmt[i];
        }
    }
    return result;
}

// 模拟Python的类型转换函数
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
//    // 输入输出
//    print("欢迎使用Python风格的C++!");
//    string name = input("请输入你的名字: ");
//    print("你好,", name, "!");
//
//    // 数学运算
//    string num_input = input("请输入两个数字（用空格分隔）: ");
//    auto parts = split(num_input);
//    double a = float_cast(parts[0]);
//    double b = float_cast(parts[1]);
//    print(format("{} + {} = {}", { to_string(a), to_string(b), to_string(a + b) }));
//
//    // 循环和条件
//    print("1到5的偶数:");
//    for (int i : range(1, 6)) {
//        if (i % 2 == 0) {
//            print(i);
//        }
//    }
//
//    return 0;
//}