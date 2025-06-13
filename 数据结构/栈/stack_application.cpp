#include <iostream>
#include <stack>
#include <cctype>
#include <map>
#include <string>

using namespace std;

//栈的基本应用


//1.括号匹配
bool brackets_match(const string& str){
    stack<char> s;
    for(char ch : str){
        if(ch == '(' || ch == '{' || ch == '['){
            s.push(ch);
        } else if(ch == ')'){
            if(s.empty() || s.top() != '('){
                return false; // 不匹配
            }
            s.pop();
        } else if(ch == '}'){
            if(s.empty() || s.top() != '{'){
                return false; // 不匹配
            }
            s.pop();
        } else if(ch == ']'){
            if(s.empty() || s.top() != '['){
                return false; // 不匹配
            }
            s.pop();
        }
    }
    return s.empty(); // 如果栈为空，则匹配
}


//2.表达式
//2.1后缀表达式求值 如ba5+3*- 为b-(a+5)*3 第二个top对第一个top操作
int eval_postfix(const string& str){
    stack<char> s;
    for(char ch : str){
        if(isdigit(ch) && ch !='+' && ch != '-' && ch != '*' && ch != '/'){
            s.push(ch); 
        }
        else {
            int b = s.top(); // 栈顶元素
            s.pop();
            int a = s.top(); // 栈顶元素
            s.pop();
            switch(ch){
                case '+':
                    s.push(a + b);
                case - '*':
                    s.push(a * b);
                case '-':
                    s.push(a - b);
                case '/':
                    s.push(a / b);
                if(s.size() == 1) return s.top();
            }
        }
    }
}

//2.2前缀表达式求值 和后缀一样，反着遍历就行

//3 中缀表达式转后缀表达式 例：b-(a+5)*3
/*
初始化两个栈：运算符栈和结果栈（或者用队列，但通常结果用队列，这里我们用一个字符串来存储结果，运算符用栈）
从左到右扫描中缀表达式
遇到操作数（数字）时，直接将其输出（添加到结果字符串）
遇到运算符时：
a. 如果运算符栈为空，或者栈顶是左括号，直接压入运算符栈
b. 否则，若当前运算符优先级高于栈顶运算符，也直接压入栈
c. 否则，弹出栈顶运算符并输出到结果字符串，再次与新的栈顶运算符比较（重复步骤4）
遇到括号时：
a. 左括号：压入运算符栈
b. 右括号：弹出运算符栈中的运算符并输出，直到遇到左括号（左括号弹出但不输出）
表达式扫描完毕后，将运算符栈中剩余的运算符依次弹出并输出
*/
string infix_to_postfix(const string& str) {
    stack<char> op_stack;    // 用于存储运算符的栈
    string postfix;          // 存储后缀表达式结果
    // 定义运算符优先级映射
    map<char, int> precedence = {
        {'+', 1},
        {'-', 1},
        {'*', 2},
        {'/', 2}
    };
    
    for (int i = 0; i < str.length(); i++) {
        char c = str[i];
        
        // 跳过空格
        if (c == ' ') continue;
        
        // 处理数字（包括多位数）
        if (isdigit(c)) {
            // 连续读取整个数字
            while (i < str.length() && (isdigit(str[i]) || str[i] == '.')) {
                postfix += str[i];
                i++;
            }
            i--;  // 回退一个字符
            postfix += ' ';  // 数字后加空格分隔
        }
        // 处理左括号
        else if (c == '(') {
            op_stack.push(c);
        }
        // 处理右括号
        else if (c == ')') {
            // 弹出栈顶运算符直到遇到左括号
            while (!op_stack.empty() && op_stack.top() != '(') {
                postfix += op_stack.top();
                postfix += ' ';
                op_stack.pop();
            }
            // 弹出左括号但不输出
            if (!op_stack.empty()) op_stack.pop();
        }
        // 处理运算符
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            // 弹出优先级更高或相等的运算符
            while (!op_stack.empty() && op_stack.top() != '(' && 
                   precedence[c] <= precedence[op_stack.top()]) {
                postfix += op_stack.top();
                postfix += ' ';
                op_stack.pop();
            }
            op_stack.push(c);
        }
    }
    
    // 弹出栈中剩余的运算符
    while (!op_stack.empty()) {
        postfix += op_stack.top();
        postfix += ' ';
        op_stack.pop();
    }
    
    // 删除最后一个多余的空格
    if (!postfix.empty() && postfix.back() == ' ') {
        postfix.pop_back();
    }

    return postfix;
}
