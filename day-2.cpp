#include <bits/stdc++.h>

using namespace std;

bool isAllIncreasing(vector<int> nums) {
  bool is_all_increasing = true;

  for (int i = 1; i < nums.size(); i++) {
    if (nums[i] < nums[i - 1]) {
      is_all_increasing = false;
    }
  }

  return is_all_increasing;
}

bool isAllDecreasing(vector<int> nums) {
  bool is_all_decreasing = true;

  for (int i = 1; i < nums.size(); i++) {
    if (nums[i] > nums[i - 1]) {
      is_all_decreasing = false;
    }
  }

  return is_all_decreasing;
}

bool isLevelSafe(vector<int> nums, string line) {
  bool is_diff_in_range = true;

  for (int i = 1; i < nums.size(); i++) {
    int diff = abs(nums[i] - nums[i - 1]);

    if (diff == 0 || diff > 3) {
      is_diff_in_range = false;
    }
  }

  bool is_all_increasing = isAllIncreasing(nums);
  bool is_all_decreasing = isAllDecreasing(nums);

  return is_diff_in_range && (is_all_increasing || is_all_decreasing);
}

int main() {
  freopen("input/day-2.txt", "r", stdin);

  ios::sync_with_stdio(0);
  cin.tie(0);

  string line;
  int safe_levels_count = 0;
  int safe_levels_count_with_problem_dampener = 0;

  while (getline(cin, line)) {
    stringstream ss(line);
    vector<int> nums;
    int num;

    while (ss >> num) {
      nums.push_back(num);
    }

    if (isLevelSafe(nums, line)) {
      safe_levels_count++;
    }

    for (int i = 0; i < nums.size(); i++) {
      vector<int> sub_nums = nums;
      sub_nums.erase(sub_nums.begin() + i);

      if (isLevelSafe(sub_nums, line)) {
        safe_levels_count_with_problem_dampener++;
        break;
      }
    }
  }

  cout << safe_levels_count << "\n";
  cout << safe_levels_count_with_problem_dampener << "\n";

  return 0;
}
