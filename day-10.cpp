#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> dir{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

void getHighestPoints(vector<vector<char>> &matrix, vector<int> curr_point,
                      set<vector<int>> &seen, set<vector<int>> &path,
                      char prev_char = '.') {
  if (curr_point[0] < 0 || curr_point[0] >= matrix.size() ||
      curr_point[1] < 0 || curr_point[1] >= matrix[0].size()) {
    return;
  }

  auto it{seen.find(curr_point)};

  if (it != seen.end()) {
    return;
  }

  if (matrix[curr_point[0]][curr_point[1]] == '.') {
    return;
  }

  char curr_char{matrix[curr_point[0]][curr_point[1]]};

  if (prev_char != '.' && ((curr_char - '0') - (prev_char - '0') != 1)) {
    return;
  }

  if (matrix[curr_point[0]][curr_point[1]] == '9') {
    path.insert(curr_point);
    return;
  }

  seen.insert(curr_point);

  for (vector<int> x : dir) {
    int row{curr_point[0]};
    int col{curr_point[1]};

    getHighestPoints(matrix, {row + x[0], col + x[1]}, seen, path,
                     matrix[row][col]);
  }

  return;
}

void getDistinctPaths(vector<vector<char>> &matrix, vector<int> curr_point,
                      set<vector<int>> &seen, vector<vector<int>> &path,
                      set<vector<vector<int>>> &paths, char prev_char = '.') {
  if (curr_point[0] < 0 || curr_point[0] >= matrix.size() ||
      curr_point[1] < 0 || curr_point[1] >= matrix[0].size()) {
    return;
  }

  if (matrix[curr_point[0]][curr_point[1]] == '.') {
    return;
  }

  char curr_char{matrix[curr_point[0]][curr_point[1]]};

  if (prev_char == curr_char) {
    return;
  }

  if (prev_char != '.' && (curr_char - '0') - (prev_char - '0') != 1) {
    return;
  }

  if (matrix[curr_point[0]][curr_point[1]] == '9') {
    path.push_back(curr_point);
    paths.insert(path);
    return;
  }

  for (vector<int> x : dir) {
    int row{curr_point[0]};
    int col{curr_point[1]};

    path.push_back(curr_point);

    getDistinctPaths(matrix, {row + x[0], col + x[1]}, seen, path, paths,
                     matrix[row][col]);

    path.pop_back();
  }

  return;
}

int main() {
  freopen("input/day-10.txt", "r", stdin);

  ios::sync_with_stdio(0);
  cin.tie(0);

  vector<vector<char>> matrix;
  string line;

  while (getline(cin, line)) {
    vector<char> row;

    for (char ch : line) {
      row.push_back(ch);
    }

    matrix.push_back(row);
  }

  set<vector<int>> seen{};
  set<vector<int>> path{};
  int sum_of_scores{0};

  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      if (matrix[i][j] == '0') {
        getHighestPoints(matrix, {i, j}, seen, path);
        sum_of_scores += path.size();
        path = {};
        seen = {};
      }
    }
  }

  cout << sum_of_scores << endl;

  set<vector<vector<int>>> paths{};
  vector<vector<int>> path_for_distinct_paths{};
  int sum_of_scores_for_distinct_paths{0};

  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      if (matrix[i][j] == '0') {
        getDistinctPaths(matrix, {i, j}, seen, path_for_distinct_paths, paths);

        sum_of_scores_for_distinct_paths += paths.size();
        path_for_distinct_paths = {};
        paths = {};
      }
    }
  }

  cout << sum_of_scores_for_distinct_paths << endl;

  return 0;
}
