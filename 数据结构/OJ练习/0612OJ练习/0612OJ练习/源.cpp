#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

//412. Fizz Buzz
class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string>ret;
        for (int i = 1; i <= n; i++) {
            if ((i) % 3 == 0 && (i) % 5 == 0) {
                ret.push_back("FizzBuzz");
            }
            else if ((i) % 3 == 0) {
                ret.push_back("Fizz");
            }
            else if ((i) % 5 == 0) {
                ret.push_back("Buzz");
            }
            else {
                ret.push_back(to_string(i));
            }
        }
        return ret;
    }
};



//面试题 08.07. 无重复字符串的排列组合
class Solution {
private:
    vector<string>ret;
    string path;
    void dfs(string s, vector<bool>used) {
        if (path.size() == s.size()) {
            ret.push_back(path);
            return;
        }
        for (int i = 0; i < s.size(); i++) {
            if (used[i] == true)continue;
            path += s[i];
            used[i] = true;
            dfs(s, used);
            used[i] = false;
            path.pop_back();
        }
    }
public:
    vector<string> permutation(string S) {
        vector<bool>used(S.size() + 1, false);
        dfs(S, used);
        return ret;
    }
};


//合并区间
class Solution {
private:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    }
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        //先创建一个结果二维vector
        vector<vector<int>> result;
        if (intervals.size() == 0) {//如果没有元素传进来
            return result;//直接返回空的即可
        }

        //排序
        sort(intervals.begin(), intervals.end(), cmp);
        //tips:排序时的参数也可以食用Lambda表达式

        //先把第一个插进来先
        result.push_back(intervals[0]);
        //开始遍历,从第二个元素,即下标为1的位置开始遍历
        for (int i = 1; i < intervals.size(); i++) {
            if (result.back()[1] >= intervals[i][0]) {//结果容器最后到达的位置大于准备插入元素的位置时，合并！
            //注意!是>=即可
                                                     //tips:元素指的是一个区间
                result.back()[1] = max(result.back()[1], intervals[i][1]);//更新result容器里面最后到达的位置
                                     ///两者之间挑大的那个，因为合并了
            }
            else {
                result.push_back(intervals[i]);//不能合并 直接插进来
            }
        }
        return result;
    }
};