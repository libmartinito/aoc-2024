#include <bits/stdc++.h>

using namespace std;

map<int, vector<int>> dir = {
    {0, {-1, 0}}, {90, {0, 1}}, {180, {1, 0}}, {270, {0, -1}}};

vector<int> getStartPos(vector<vector<char>> map) {
  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[0].size(); j++) {
      if (map[i][j] == '^') {
        return {i, j};
      }
    }
  }

  return {-1, -1};
}

void walk(vector<vector<char>> &map, vector<int> pos, int &degree,
          set<vector<int>> &path) {
  int row = pos[0], col = pos[1];

  if (row < 0 || row >= map.size() || col < 0 || col >= map[0].size()) {
    return;
  }

  if (map[row][col] == '#') {
    int new_degree;

    if (degree + 90 == 360) {
      new_degree = 0;
    } else {
      new_degree = degree + 90;
    }

    walk(map, {row - dir[degree][0], col - dir[degree][1]}, new_degree, path);

    return;
  }

  path.insert(pos);

  walk(map, {row + dir[degree][0], col + dir[degree][1]}, degree, path);

  return;
}

void walkToFindLoop(vector<vector<char>> &map, vector<int> pos, int &degree,
                    set<vector<int>> &path_with_degree, bool &is_loop) {
  int row = pos[0], col = pos[1];

  if (row < 0 || row >= map.size() || col < 0 || col >= map[0].size()) {
    return;
  }

  if (map[row][col] == '#') {
    int new_degree;

    if (degree + 90 == 360) {
      new_degree = 0;
    } else {
      new_degree = degree + 90;
    }

    walkToFindLoop(map, {row - dir[degree][0], col - dir[degree][1]},
                   new_degree, path_with_degree, is_loop);

    return;
  }

  int path_with_degree_size_before = path_with_degree.size();

  path_with_degree.insert({pos[0], pos[1], degree});

  int path_with_degree_size_after = path_with_degree.size();

  if (path_with_degree_size_before == path_with_degree_size_after) {
    is_loop = true;
    return;
  }

  walkToFindLoop(map, {row + dir[degree][0], col + dir[degree][1]}, degree,
                 path_with_degree, is_loop);

  return;
}

int getObstructionCount(vector<vector<char>> &map, vector<int> startPos) {
  int start_row = startPos[0], start_col = startPos[1], obstruction_count = 0;

  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[0].size(); j++) {
      if (i == start_row && j == start_col) {
        continue;
      }

      if (map[i][j] == '#') {
        continue;
      }

      map[i][j] = '#';
      bool is_loop = false;
      int degree = 0;
      set<vector<int>> path_with_degree;

      walkToFindLoop(map, startPos, degree, path_with_degree, is_loop);

      if (is_loop) {
        obstruction_count++;
      }

      map[i][j] = '.';
    }
  }

  return obstruction_count;
}

int main() {
  freopen("input/day-6.txt", "r", stdin);

  ios::sync_with_stdio(0);
  cin.tie(0);

  vector<vector<char>> map;
  string line;

  while (getline(cin, line)) {
    vector<char> row;

    for (char ch : line) {
      row.push_back(ch);
    }

    map.push_back(row);
  }

  vector<int> startPos = getStartPos(map);
  int degree = 0;
  set<vector<int>> path;

  walk(map, startPos, degree, path);

  cout << path.size() << "\n";
  cout << getObstructionCount(map, startPos) << "\n";

  return 0;
}
