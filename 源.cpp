#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// 队列数据结构
class Queue {
public:
    void push(int x) {
        inStack.push(x);
    }

    int pop() {
        if (outStack.empty()) {
            while (!inStack.empty()) {
                outStack.push(inStack.top());
                inStack.pop();
            }
        }
        int x = outStack.top();
        outStack.pop();
        return x;
    }

    bool empty() {
        return inStack.empty() && outStack.empty();
    }

private:
    stack<int> inStack;
    stack<int> outStack;
};

// 计算矩形最大面积的函数
int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    vector<int> left(n), right(n);
    stack<int> monoStack;

    // 找到每个柱子左边第一个小于它的柱子
    for (int i = 0; i < n; i++) {
        while (!monoStack.empty() && heights[monoStack.top()] >= heights[i]) {
            monoStack.pop();
        }
        left[i] = monoStack.empty() ? -1 : monoStack.top();
        monoStack.push(i);
    }

    // 清空栈
    while (!monoStack.empty()) {
        monoStack.pop();
    }

    // 找到每个柱子右边第一个小于它的柱子
    for (int i = n - 1; i >= 0; i--) {
        while (!monoStack.empty() && heights[monoStack.top()] >= heights[i]) {
            monoStack.pop();
        }
        right[i] = monoStack.empty() ? n : monoStack.top();
        monoStack.push(i);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, (right[i] - left[i] - 1) * heights[i]);
    }
    return ans;
}

int main() {
    // 随机生成10组数据进行测试
    for (int i = 0; i < 10; i++) {
        vector<int> heights;
        int n = rand() % 105 + 1;
        for (int j = 0; j < n; j++) {
            heights.push_back(rand() % 10001);
        }
        int ans = largestRectangleArea(heights);
        cout << "Test " << i + 1 << ": " << ans << endl;
    }
    return 0;
}