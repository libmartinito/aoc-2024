#include <bits/stdc++.h>

using namespace std;

vector<int> getNumbersBeforeTarget(int target, map<int, vector<int>> &rules) {
  vector<int> numbers_before;

  for (auto rule : rules) {
    for (int num : rule.second) {
      if (num == target) {
        numbers_before.push_back(rule.first);
      }
    }
  }

  return numbers_before;
}

bool isTargetPresentInVec(int target, vector<int> vec) {
  for (int el : vec) {
    if (el == target) {
      return true;
    }
  }

  return false;
}

bool isValidUpdate(vector<int> update, map<int, vector<int>> &rules) {
  for (int i = 0; i < update.size(); i++) {
    vector<int> numbers_before_target =
        getNumbersBeforeTarget(update[i], rules);

    for (int j = i + 1; j < update.size(); j++) {
      if (isTargetPresentInVec(update[j], numbers_before_target)) {
        return false;
      }
    }

    vector<int> numbers_after_target = rules[update[i]];

    for (int k = 0; k < i; k++) {
      if (isTargetPresentInVec(update[k], numbers_after_target)) {
        return false;
      }
    }
  }

  return true;
}

vector<int> sortNumbersAfterTarget(vector<int> nums, int curr_idx,
                                   map<int, vector<int>> &rules) {
  vector<int> numbers_after_curr_idx;

  for (int i = curr_idx + 1; i < nums.size(); i++) {
    numbers_after_curr_idx.push_back(nums[i]);
  }

  vector<int> numbers_after_target = rules[nums[curr_idx]];

  vector<int> incorrectly_ordered;
  vector<int> correctly_ordered;

  for (int i = 0; i < curr_idx; i++) {
    if (isTargetPresentInVec(nums[i], numbers_after_target)) {
      incorrectly_ordered.push_back(nums[i]);
    } else {
      correctly_ordered.push_back(nums[i]);
    }
  }

  if (incorrectly_ordered.size() == 0) {
    return nums;
  }

  vector<int> new_nums;

  for (int before_target_num : correctly_ordered) {
    new_nums.push_back(before_target_num);
  }

  new_nums.push_back(nums[curr_idx]);

  for (int after_target_num : incorrectly_ordered) {
    new_nums.push_back(after_target_num);
  }

  for (int number_after_curr_idx : numbers_after_curr_idx) {
    new_nums.push_back(number_after_curr_idx);
  }

  return new_nums;
}

vector<int> sortNumbersBeforeTarget(vector<int> nums, int curr_idx,
                                    map<int, vector<int>> &rules) {
  vector<int> numbers_before_curr_idx;

  for (int i = 0; i < curr_idx; i++) {
    numbers_before_curr_idx.push_back(nums[i]);
  }

  vector<int> numbers_before_target =
      getNumbersBeforeTarget(nums[curr_idx], rules);

  vector<int> incorrectly_ordered;
  vector<int> correctly_ordered;

  for (int i = curr_idx + 1; i < nums.size(); i++) {
    if (isTargetPresentInVec(nums[i], numbers_before_target)) {
      incorrectly_ordered.push_back(nums[i]);
    } else {
      correctly_ordered.push_back(nums[i]);
    }
  }

  if (incorrectly_ordered.size() == 0) {
    return nums;
  }

  vector<int> new_nums;

  for (int number_before_curr_idx : numbers_before_curr_idx) {
    new_nums.push_back(number_before_curr_idx);
  }

  for (int before_target_num : incorrectly_ordered) {
    new_nums.push_back(before_target_num);
  }

  new_nums.push_back(nums[curr_idx]);

  for (int after_target_num : correctly_ordered) {
    new_nums.push_back(after_target_num);
  }

  return new_nums;
}

vector<int> sortInvalidUpdate(vector<int> update,
                              map<int, vector<int>> &rules) {
  while (!isValidUpdate(update, rules)) {
    for (int i = 0; i < update.size(); i++) {
      vector<int> sorted_numbers_before_target =
          sortNumbersBeforeTarget(update, i, rules);

      if (update != sorted_numbers_before_target) {
        update = sorted_numbers_before_target;
        break;
      }

      vector<int> sorted_numbers_after_target =
          sortNumbersBeforeTarget(update, i, rules);

      if (update != sorted_numbers_after_target) {
        update = sorted_numbers_after_target;
        break;
      }
    }
  }

  return update;
}

int main() {
  freopen("input/day-5.txt", "r", stdin);

  ios::sync_with_stdio(0);
  cin.tie(0);

  string line;
  map<int, vector<int>> rules;
  bool is_rule = true;
  vector<vector<int>> updates;

  while (getline(cin, line)) {
    if (line == "") {
      is_rule = false;
      continue;
    }

    if (is_rule) {
      size_t divider_pos = line.find("|");
      int first_num = stoi(line.substr(0, divider_pos));
      int second_num = stoi(line.substr(divider_pos + 1));
      rules[first_num].push_back(second_num);
    } else {
      size_t comma_pos = line.find(",");
      vector<int> row;

      while (comma_pos != string::npos) {
        row.push_back(stoi(line.substr(0, comma_pos)));
        line = line.substr(comma_pos + 1);
        comma_pos = line.find(",");
      }

      row.push_back(stoi(line));
      updates.push_back(row);
    }
  }

  vector<vector<int>> valid_updates;
  vector<vector<int>> invalid_updates;

  for (vector<int> update : updates) {
    if (isValidUpdate(update, rules)) {
      valid_updates.push_back(update);
    } else {
      invalid_updates.push_back(update);
    }
  }

  int sum_of_middle_nums = 0;

  for (vector<int> update : valid_updates) {
    sum_of_middle_nums += update[floor(update.size() / 2)];
  }

  cout << sum_of_middle_nums << "\n";

  int sum_of_corrected_middle_nums = 0;

  vector<vector<int>> corrected_invalid_updates;

  for (vector<int> update : invalid_updates) {
    corrected_invalid_updates.push_back(sortInvalidUpdate(update, rules));
  }

  for (vector<int> update : corrected_invalid_updates) {
    sum_of_corrected_middle_nums += update[floor(update.size() / 2)];
  }

  cout << sum_of_corrected_middle_nums << "\n";

  return 0;
}
