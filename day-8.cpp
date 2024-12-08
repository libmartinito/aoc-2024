#include <bits/stdc++.h>

using namespace std;

set<vector<int>>
getAntinodeLocations(vector<vector<char>> &matrix,
                     map<char, vector<vector<int>>> &node_locations) {
  set<vector<int>> antinode_locations{};

  for (auto node_location : node_locations) {
    for (int i = 0; i < node_location.second.size() - 1; i++) {
      for (int j = i + 1; j < node_location.second.size(); j++) {
        vector<int> first_node{node_location.second[i]};
        vector<int> second_node{node_location.second[j]};

        int row_diff = second_node[1] - first_node[1];
        int col_diff = second_node[0] - first_node[0];

        vector<int> first_antinode{};
        vector<int> second_antinode{};

        if (col_diff > 0) {
          first_antinode = {first_node[0] - col_diff, first_node[1] - row_diff};
          second_antinode = {second_node[0] + col_diff,
                             second_node[1] + row_diff};
        } else {
          first_antinode = {first_node[0] + col_diff, first_node[1] + row_diff};
          second_antinode = {second_node[0] - col_diff,
                             second_node[1] - row_diff};
        }

        if (first_antinode[0] >= 0 && first_antinode[0] < matrix.size() &&
            first_antinode[1] >= 0 && first_antinode[1] < matrix[0].size()) {
          antinode_locations.insert(first_antinode);
        }

        if (second_antinode[0] >= 0 && second_antinode[0] < matrix.size() &&
            second_antinode[1] >= 0 && second_antinode[1] < matrix[0].size()) {
          antinode_locations.insert(second_antinode);
        }
      }
    }
  }

  return antinode_locations;
}

set<vector<int>>
getAllAntinodeLocations(vector<vector<char>> &matrix,
                        map<char, vector<vector<int>>> &node_locations) {
  set<vector<int>> antinode_locations{};

  for (auto node_location : node_locations) {
    for (int i = 0; i < node_location.second.size() - 1; i++) {
      for (int j = i + 1; j < node_location.second.size(); j++) {
        vector<int> first_node{node_location.second[i]};
        vector<int> second_node{node_location.second[j]};

        int row_diff = second_node[1] - first_node[1];
        int col_diff = second_node[0] - first_node[0];

        vector<int> first_antinode{};
        vector<int> second_antinode{};

        if (col_diff > 0) {
          first_antinode = {first_node[0] - col_diff, first_node[1] - row_diff};
          second_antinode = {second_node[0] + col_diff,
                             second_node[1] + row_diff};
        } else {
          first_antinode = {first_node[0] + col_diff, first_node[1] + row_diff};
          second_antinode = {second_node[0] - col_diff,
                             second_node[1] - row_diff};
        }

        while (first_antinode[0] >= 0 && first_antinode[0] < matrix.size() &&
               first_antinode[1] >= 0 && first_antinode[1] < matrix[0].size()) {
          antinode_locations.insert(first_antinode);

          if (col_diff > 0) {
            first_antinode = {first_antinode[0] - col_diff,
                              first_antinode[1] - row_diff};
          } else {
            first_antinode = {first_antinode[0] + col_diff,
                              first_antinode[1] + row_diff};
          }
        }

        while (second_antinode[0] >= 0 && second_antinode[0] < matrix.size() &&
               second_antinode[1] >= 0 &&
               second_antinode[1] < matrix[0].size()) {
          antinode_locations.insert(second_antinode);

          if (col_diff > 0) {
            second_antinode = {second_antinode[0] + col_diff,
                               second_antinode[1] + row_diff};
          } else {
            second_antinode = {second_antinode[0] - col_diff,
                               second_antinode[1] - row_diff};
          }
        }

        antinode_locations.insert(first_node);
        antinode_locations.insert(second_node);
      }
    }
  }

  return antinode_locations;
}

int main() {
  freopen("input/day-8.txt", "r", stdin);

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

  map<char, vector<vector<int>>> node_locations{};

  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[0].size(); j++) {
      if (matrix[i][j] != '.') {
        node_locations[matrix[i][j]].push_back({i, j});
      }
    }
  }

  cout << getAntinodeLocations(matrix, node_locations).size() << endl;
  cout << getAllAntinodeLocations(matrix, node_locations).size() << endl;

  return 0;
}
