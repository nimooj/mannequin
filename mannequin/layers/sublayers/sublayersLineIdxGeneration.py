#nums = [8, 26, 27, 28, 29, 9]
nums = [9, 30, 31, 32, 33, 34, 35, 10]

outfile = open("subMeshLineIdx", "w")


for n in range(0, len(nums) - 1):
	for idx in range(1, 37): 
		if idx == 36 :
			outfile.write("%d %d %d %d %d %d\n" % (nums[n], idx, nums[n + 1], 1, nums[n + 1], idx ))
			outfile.write("%d %d %d %d %d %d\n" % (nums[n], idx, nums[n], 1, nums[n + 1], 1))
		elif idx > 18 :
			outfile.write("%d %d %d %d %d %d\n" % (nums[n], idx, nums[n + 1], idx + 1, nums[n + 1], idx ))
			outfile.write("%d %d %d %d %d %d\n" % (nums[n], idx, nums[n], idx + 1, nums[n + 1], idx + 1))
		else: 
			outfile.write("%d %d %d %d %d %d\n" % (nums[n], idx, nums[n], idx + 1, nums[n + 1], idx ))
			outfile.write("%d %d %d %d %d %d\n" % (nums[n], idx + 1, nums[n + 1], idx + 1, nums[n + 1], idx ))


outfile.close()