#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> dir{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

set<char> getUniqueChars(vector<vector<char>> &matrix) {
  set<char> unique_chars{};

  for (size_t i = 0; i < matrix.size(); i++) {
    for (size_t j = 0; j < matrix[0].size(); j++) {
      unique_chars.insert(matrix[i][j]);
    }
  }

  return unique_chars;
}

void updateRegionInfo(vector<vector<char>> &matrix, vector<int> curr_point,
                      char &target, set<vector<int>> &seen_points,
                      map<string, int> &region_info) {
  int row{curr_point[0]}, col{curr_point[1]};

  if (seen_points.find(curr_point) != seen_points.end()) {
    return;
  }

  if (row < 0 || row >= matrix.size() || col < 0 || col >= matrix[0].size()) {
    return;
  }

  if (matrix[row][col] != target) {
    return;
  }

  seen_points.insert(curr_point);
  region_info["area"]++;

  for (size_t i = 0; i < dir.size(); i++) {
    int new_row{row + dir[i][0]}, new_col{col + dir[i][1]};

    if (new_row < 0 || new_row >= matrix.size() || new_col < 0 ||
        new_col >= matrix[0].size() ||
        matrix[row][col] != matrix[new_row][new_col]) {
      region_info["perimeter"]++;
    }
  }

  for (size_t i = 0; i < dir.size(); i++) {
    int new_row{row + dir[i][0]}, new_col{col + dir[i][1]};
    updateRegionInfo(matrix, {new_row, new_col}, target, seen_points,
                     region_info);
  }

  return;
}

void updateAreaAndCorners(vector<vector<char>> &matrix, vector<int> curr_point,
                          char &target, set<vector<int>> &seen_points,
                          int &areas, int &corners) {
  int row{curr_point[0]}, col{curr_point[1]};

  if (seen_points.find(curr_point) != seen_points.end()) {
    return;
  }

  if (row < 0 || row >= matrix.size() || col < 0 || col >= matrix[0].size()) {
    return;
  }

  if (matrix[row][col] != target) {
    return;
  }

  seen_points.insert(curr_point);
  areas++;

  for (size_t i = 0; i < dir.size(); i++) {
    int first_row{row + dir[i][0]}, first_col{col + dir[i][1]}, second_row{},
        second_col{};

    if (i + 1 == dir.size()) {
      second_row = row + dir[0][0], second_col = col + dir[0][1];
    } else {
      second_row = row + dir[i + 1][0], second_col = col + dir[i + 1][1];
    }

    bool is_first_cell_invalid =
        first_row < 0 || first_row >= matrix.size() || first_col < 0 ||
        first_col >= matrix[0].size() ||
        matrix[row][col] != matrix[first_row][first_col];

    bool is_second_cell_invalid =
        second_row < 0 || second_row >= matrix.size() || second_col < 0 ||
        second_col >= matrix[0].size() ||
        matrix[row][col] != matrix[second_row][second_col];

    vector<int> corner{};

    if (i == 0) {
      corner = {first_row, first_col + 1};
    } else if (i == 1) {
      corner = {second_row, second_col + 1};
    } else if (i == 2) {
      corner = {first_row, first_col - 1};
    } else {
      corner = {second_row, second_col - 1};
    }

    if (is_first_cell_invalid && is_second_cell_invalid) {
      corners++;
    }

    if (!is_first_cell_invalid && !is_second_cell_invalid &&
        matrix[corner[0]][corner[1]] != target) {
      corners++;
    }

    updateAreaAndCorners(matrix, {first_row, first_col}, target, seen_points,
                         areas, corners);
  }

  return;
}

int main() {
  freopen("input/day-12.txt", "r", stdin);

  ios::sync_with_stdio(0);
  cin.tie(0);

  vector<vector<char>> matrix{};
  string line{""};

  while (getline(cin, line)) {
    vector<char> row{};

    for (char ch : line) {
      row.push_back(ch);
    }

    matrix.push_back(row);
  }

  int total{0};

  set<vector<int>> seen_points{};
  set<char> unique_chars = getUniqueChars(matrix);

  for (char ch : unique_chars) {
    for (size_t i = 0; i < matrix.size(); i++) {
      for (size_t j = 0; j < matrix[0].size(); j++) {
        int row = i, col = j;
        if (seen_points.find({row, col}) == seen_points.end()) {
          map<string, int> region_info{};
          updateRegionInfo(matrix, {row, col}, ch, seen_points, region_info);
          total += region_info["area"] * region_info["perimeter"];
        }
      }
    }
  }

  cout << total << "\n";

  seen_points = {};
  int total_for_info_with_shape_side{0};

  for (char ch : unique_chars) {
    for (size_t i = 0; i < matrix.size(); i++) {
      for (size_t j = 0; j < matrix[0].size(); j++) {
        int row = i, col = j;

        if (seen_points.find({row, col}) == seen_points.end()) {
          int areas{0};
          int corners{0};

          updateAreaAndCorners(matrix, {row, col}, ch, seen_points, areas,
                               corners);

          total_for_info_with_shape_side += areas * corners;
        }
      }
    }
  }

  cout << total_for_info_with_shape_side << "\n";

  return 0;
}
