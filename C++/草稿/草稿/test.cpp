
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<queue>
using namespace std;


class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        //先找到最远的位置在哪里
        priority_queue<long long>pq_max;
        for (size_t i = 0; i < buildings.size(); i++)
        {
            pq_max.push(max(buildings[i][0], buildings[i][1]));
        }
        long long pq_size = pq_max.top();
        //pq_size就是建筑物最远的地方
        //每一个横坐标构建一个优先队列，每一个横坐标都维护
        vector<priority_queue<long long>>arr(pq_size + (long long)2);
        for (size_t i = 0; i < buildings.size(); i++)
        {
            int height = buildings[i][2];
            int left = buildings[i][0];
            int right = buildings[i][1];
            for (size_t j = left; j <= right; j++)
            {
                arr[j].push(height);
            }
        }
        //此时已经找到天际线了
        vector<int>h;
        for (size_t i = 0; i < arr.size(); i++)
        {
            if (arr[i].size() == 0)
            {
                h.push_back(0); continue;
            }
            h.push_back(arr[i].top());
        }
        //此时arr存的就是天际线
        vector<vector<int>>ret;
        for (size_t i = 0; i < h.size(); i++)
        {
            if (i == 0)
            {
                if (h[i] != 0)
                {
                    ret.push_back({ 0,h[i] });
                }
                continue;
            }
            if (h[i] > h[i - 1])
            {
                ret.push_back({ (int)i,h[i] });
            }
            else if (h[i] < h[i - 1])
            {
                ret.push_back({ (int)(i - 1),h[i] });
            }
            else
            {
                continue;
            }
        }
        return ret;
    }
};
int main()
{
    vector<vector<int>>input = { {0, 2147483647, 2147483647} };
    Solution().getSkyline(input);
    return 0;
}