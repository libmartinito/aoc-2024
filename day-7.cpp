#include <bits/stdc++.h>

using namespace std;

void validateTestValue(long &target, vector<long> &nums, int nums_idx, long num,
                       string command, vector<string> &commands,
                       bool &is_valid_test_value) {
  if (nums.size() == nums_idx) {
    if (target == num) {
      is_valid_test_value = true;
    }

    return;
  }

  if (command == "add") {
    num += nums[nums_idx];
  }

  if (command == "mul") {
    num *= nums[nums_idx];
  }

  if (command == "concat") {
    num = stol(to_string(num) + to_string(nums[nums_idx]));
  }

  for (string command : commands) {
    validateTestValue(target, nums, nums_idx + 1, num, command, commands,
                      is_valid_test_value);
  }

  return;
}

int main() {
  freopen("input/day-7.txt", "r", stdin);

  ios::sync_with_stdio(0);
  cin.tie(0);

  map<long, vector<long>> values{};
  string line{""};

  while (getline(cin, line)) {
    size_t colon_pos{line.find(":")};
    long key{stol(line.substr(0, colon_pos))};

    line = line.substr(colon_pos + 2);

    size_t space_pos{line.find(" ")};

    while (space_pos != string::npos) {
      values[key].push_back(stol(line.substr(0, space_pos)));
      line = line.substr(space_pos + 1);
      space_pos = line.find(" ");
    }

    values[key].push_back(stol(line));
  }

  long sum_of_valid_test_values{0};
  long sum_of_valid_test_values_with_concat{0};

  for (auto value : values) {
    long target{value.first};
    vector<long> nums{value.second};
    long initial_num{nums[0]};
    bool is_valid_test_value{false};
    bool is_valid_test_value_with_concat{false};
    vector<string> commands{"add", "mul"};
    vector<string> commands_with_concat{"add", "mul", "concat"};

    validateTestValue(target, nums, 0, initial_num, "", commands,
                      is_valid_test_value);
    validateTestValue(target, nums, 0, initial_num, "", commands_with_concat,
                      is_valid_test_value_with_concat);

    if (is_valid_test_value) {
      sum_of_valid_test_values += target;
    }

    if (is_valid_test_value_with_concat) {
      sum_of_valid_test_values_with_concat += target;
    }
  }

  cout << sum_of_valid_test_values << "\n";
  cout << sum_of_valid_test_values_with_concat << "\n";

  return 0;
}
