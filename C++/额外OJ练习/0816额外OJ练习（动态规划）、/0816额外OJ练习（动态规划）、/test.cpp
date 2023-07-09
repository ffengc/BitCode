#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

//64. 最小路径和
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        //总共需要的步数
        int row = grid.size();
        int col = grid[0].size();
        //创建dp数组
        vector<vector<int>>dp(row, vector<int>(col, 0));
        //初始化dp数组
        //注意 -- 这种初始化肯定是第一行和第一列都要初始化的
        dp[0][0] = grid[0][0];
        for (int i = 1; i < row; i++) {
            dp[i][0] = grid[i][0] + dp[i - 1][0];
        }
        for (int j = 1; j < col; j++) {
            dp[0][j] = grid[0][j] + dp[0][j - 1];
        }
        //动态规划
        for (int i = 1; i < row; i++) {//注意，这里是从1开始的
            for (int j = 1; j < col; j++) {//这里也是从1开始的
                dp[i][j] = min(dp[i][j - 1] + grid[i][j], dp[i - 1][j] + grid[i][j]);
            }
        }
        return dp[row - 1][col - 1];
    }
};
int main() {
    vector<vector<int>>arr = { {} };
    Solution().minPathSum(arr);
    return 0;
}