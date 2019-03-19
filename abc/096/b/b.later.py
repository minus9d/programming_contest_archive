nums = list(map(int, input().split()))
K = int(input())
nums.sort()
print(sum(nums[:2]) + nums[2] * 2 ** K)
