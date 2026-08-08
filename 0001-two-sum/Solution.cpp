class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        unordered_map<int,int> freq;
        for(int i=0;i<n;i++){
            int rem =target-nums[i];
            if(freq.find(rem)!=freq.end()){
                return {freq[rem],i};
            }
            freq[nums[i]] = i;
        }
        return {};
    }
};