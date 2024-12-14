#include <bits/stdc++.h>

using namespace std;

vector<long long> getCoordinates(string line) {
  size_t x_pos{line.find("X")}, y_pos{line.find("Y")},
      comma_pos{line.find(",")};

  long long x = stoll(line.substr(x_pos + 2, comma_pos - x_pos - 2));
  long long y = stoll(line.substr(y_pos + 2));

  return {x, y};
}

vector<long long> getTokens(vector<vector<long long>> machine_info) {
  long long a1{0}, b1{0}, c1{0};
  long long a2{0}, b2{0}, c2{0};

  a1 = machine_info[0][0];
  b1 = machine_info[1][0];
  c1 = machine_info[2][0];

  a2 = machine_info[0][1];
  b2 = machine_info[1][1];
  c2 = machine_info[2][1];

  long long determinant = a1 * b2 - a2 * b1;

  long long determinant_x = c1 * b2 - c2 * b1;
  long long determinant_y = c2 * a1 - c1 * a2;

  if (determinant_x % determinant != 0 || determinant_y % determinant != 0) {
    return {-1};
  }

  long long x = determinant_x / determinant;
  long long y = determinant_y / determinant;

  return {x, y};
}

long long getTotalTokens(vector<vector<vector<long long>>> &all_machine_info,
                         bool is_adjusted = false) {
  long long total_tokens{0};

  for (vector<vector<long long>> machine_info : all_machine_info) {
    if (is_adjusted) {
      machine_info[2][0] += 10000000000000;
      machine_info[2][1] += 10000000000000;
    }

    vector<long long> tokens = getTokens(machine_info);

    if (tokens[0] == -1) {
      continue;
    }

    long long total = tokens[0] * 3 + tokens[1] * 1;
    total_tokens += total;
  }

  return total_tokens;
}

int main() {
  freopen("input/day-13.txt", "r", stdin);

  ios::sync_with_stdio(0);
  cin.tie(0);

  string line{""};
  vector<vector<vector<long long>>> all_machine_info{};
  vector<vector<long long>> machine_info{};

  while (getline(cin, line)) {
    if (line != "") {
      machine_info.push_back(getCoordinates(line));
      continue;
    }

    all_machine_info.push_back(machine_info);
    machine_info = {};
  }

  if (machine_info.size() != 0) {
    all_machine_info.push_back(machine_info);
  }

  cout << getTotalTokens(all_machine_info) << "\n";
  cout << getTotalTokens(all_machine_info, true) << "\n";

  return 0;
}
