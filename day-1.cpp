#include <bits/stdc++.h>

using namespace std;

int getSimilarityCount(vector<int> nums, int target) {
  int count = 0;

  for (int num : nums) {
    if (target == num) {
      count++;
    }
  }

  return count;
}

int main() {
  freopen("input/day-1.txt", "r", stdin);

  ios::sync_with_stdio(0);
  cin.tie(0);

  vector<int> first_list;
  vector<int> second_list;

  string line;

  while (getline(cin, line)) {
    size_t space_pos = line.find(" ");
    first_list.push_back(stoi(line.substr(0, space_pos)));
    second_list.push_back(stoi(line.substr(space_pos + 3)));
  }

  sort(first_list.begin(), first_list.end());
  sort(second_list.begin(), second_list.end());

  int sum = 0;

  for (int i = 0; i < first_list.size(); i++) {
    sum += abs(first_list[i] - second_list[i]);
  }

  cout << sum << "\n";

  int similarity_score = 0;

  for (int num : first_list) {
    similarity_score += num * getSimilarityCount(second_list, num);
  }

  cout << similarity_score << "\n";

  return 0;
}
