#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<unordered_map>
using namespace std;

//567. 字符串的排列
#if 0
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        //如果s1比s2长，肯定不满足题目条件
        if (s1.size() > s2.size())return false;
        //定义两个哈希数组
        //如果两个哈希数组等价了，说明满足条件
        vector<int>hash1(26, 0);
        vector<int>hash2(26, 0);
        //我们把滑动窗口控制在s1.size()的大小就行了，因为结果一定是s1.size()大小的
        for (int i = 0; i < s1.size(); i++) {
            ++hash1[s1[i] - 'a'];
            ++hash2[s2[i] - 'a'];
        }
        if (hash2 == hash1)return true;//滑动之前也要判断一次，要细心点
        //开始滑动
        for (int i = s1.size(); i < s2.size(); i++) {
            ++hash2[s2[i] - 'a'];
            --hash2[s2[i - s1.size()] - 'a'];
            if (hash2 == hash1)return true;
        }
        return false;
    }
};
#endif




//36. 有效的数独
//暴力检查
//注意:hash.clear()不是清零
//     它把size也置为0了
//需要一个to_0函数清空哈希表 -- 可能是我知识储备不够，应该不是这样清的
#if 0
class Solution {
private:
    void to_0(vector<int>& hash) {
        for (int i = 0; i < 10; i++) {
            hash[i] = 0;
        }
    }
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<int>hash(10, 0);
        //检查行
        for (int i = 0; i < 9; i++) {
            //把i行的数用哈希存储
            to_0(hash);
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    ++hash[board[i][j] - '0'];
                    if (hash[board[i][j] - '0'] > 1)return false;
                }
            }
        }
        to_0(hash);
        //检查列
        for (int i = 0; i < 9; i++) {
            //把i列的数用哈希存储
            to_0(hash);
            for (int j = 0; j < 9; j++) {
                if (board[j][i] != '.') {
                    ++hash[board[j][i] - '0'];
                    if (hash[board[j][i] - '0'] > 1)return false;
                }
            }
        }
        //检查九宫格
        //先去确定一个九宫格的范围
        to_0(hash);
        for (int i = 0; i <= 6; i += 3) {
            for (int j = 0; j <= 6; j += 3) {
                //所以此时该九宫格的左上角为(i,j)
                //右下角坐标为(i+2,j+2)
                //遍历这个矩阵即可
                to_0(hash);
                for (int x = i; x <= i + 2; x++) {
                    for (int y = j; y <= j + 2; y++) {
                        if (board[x][y] != '.') {
                            ++hash[board[x][y] - '0'];
                            if (hash[board[x][y] - '0'] > 1)return false;
                        }
                    }
                }
            }
        }
        return true;
    }
};
void copy(vector<vector<string>>board_org, vector<vector<char>>& board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board[i][j] = board_org[i][j][0];
        }
    }
}
int main() {
    Solution su;
    vector<vector<string>>board_org = { 
        {"8", "3", ".", ".", "7", ".", ".", ".", "."},
        {"6", ".", ".", "1", "9", "5", ".", ".", "."},
        {".", "9", "8", ".", ".", ".", ".", "6", "."},
        {"8", ".", ".", ".", "6", ".", ".", ".", "3"},
        {"4", ".", ".", "8", ".", "3", ".", ".", "1"},
        {"7", ".", ".", ".", "2", ".", ".", ".", "6"},
        {".", "6", ".", ".", ".", ".", "2", "8", "."},
        {".", ".", ".", "4", "1", "9", ".", ".", "5"},
        {".", ".", ".", ".", "8", ".", ".", "7", "9"} };
    vector < vector<char>>board(9, vector<char>(9));
    copy(board_org, board);
    int ret = su.isValidSudoku(board);
    return 0;
}
#endif

#if 0
class Solution {
private:
    static bool cmp(const void* e1, const void* e2) {
        return *((char*)e1) > *((char*)e2);
    }
public:
    bool isAnagram(string s, string t) {
        sort(s.begin(), s.end(), cmp);
        sort(t.begin(), t.end(), cmp);
        if (t == s) {
            return true;
        }
        return false;
    }
};
#endif


//1346. 检查整数及其两倍数是否存在
class Solution {
public:
    bool checkIfExist(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        int _max = arr[arr.size() - 1];
        int _mid = _max / 2;
        int i;
        for (i = arr.size() - 1; i > 0; i--) {
            if (arr[i] > _mid && arr[i - 1] <= _mid)break;
        }
        //此时的i就是要开始搜索的下标
        int index = arr.size() - 1;//这个是左边的指针
        while (i >= 0 && index >= 0) {
            if (arr[i] * 2 == arr[index] && i != index)return true;
            else if (arr[i] * 2 > arr[index])i--;
            else if (arr[i] * 2 < arr[index])index--;
            else i--;
        }
        return false;
    }
};
int main() {
    vector<int>arr = { -2,0,10,-19,4,6,-8};
    Solution su;
    su.checkIfExist(arr);
    return 0;
}