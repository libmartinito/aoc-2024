#include <bits/stdc++.h>

using namespace std;

long blink(int curr_iter, int target_iter, long num,
           unordered_map<string, long> &cache) {
  string key = to_string(num) + "-" + to_string(target_iter - curr_iter);

  if (cache.find(key) != cache.end()) {
    return cache[key];
  }

  if (curr_iter == target_iter) {
    return 1;
  }

  long count = 0;
  curr_iter++;

  if (num == 0) {
    count += blink(curr_iter, target_iter, 1, cache);
  } else if (to_string(num).size() % 2 == 0) {
    string num_str = to_string(num);
    count += blink(curr_iter, target_iter,
                   stol(num_str.substr(0, num_str.size() / 2)), cache);
    count += blink(curr_iter, target_iter,
                   stol(num_str.substr(num_str.size() / 2)), cache);
  } else {
    count += blink(curr_iter, target_iter, num * 2024, cache);
  }

  cache[key] = count;

  return cache[key];
}

int main() {
  freopen("input/day-11.txt", "r", stdin);

  ios::sync_with_stdio(0);
  cin.tie(0);

  vector<long> stones;
  string line;

  getline(cin, line);

  size_t space_pos{line.find(" ")};

  while (space_pos != string::npos) {
    stones.push_back(stol(line.substr(0, space_pos)));
    line = line.substr(space_pos + 1);
    space_pos = line.find(" ");
  }

  if (line != "") {
    stones.push_back(stol(line));
  }

  int part_one_curr_iter{0};
  int part_one_target_iter{25};
  long part_one_total_count{0};
  unordered_map<string, long> cache{};

  for (long stone : stones) {
    part_one_total_count +=
        blink(part_one_curr_iter, part_one_target_iter, stone, cache);

    part_one_curr_iter = 0;
  }

  cout << part_one_total_count << "\n";

  int part_two_curr_iter{0};
  int part_two_target_iter{75};
  long part_two_total_count{0};
  unordered_map<string, long> part_two_cache{};

  for (long stone : stones) {
    part_two_total_count +=
        blink(part_two_curr_iter, part_two_target_iter, stone, part_two_cache);

    part_two_curr_iter = 0;
  }

  cout << part_two_total_count << "\n";

  return 0;
}
