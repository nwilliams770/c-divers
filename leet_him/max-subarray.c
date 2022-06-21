int maxSubArray(int* nums, int numsSize){
    int maxSum = INT_MIN;

    for (int i = 0, sum = 0; i < numsSize; i++) {
        sum = sum < 0 ? nums[i] : sum + nums[i];
        maxSum = sum > maxSum ? sum : maxSum;
    }

    return maxSum;
}