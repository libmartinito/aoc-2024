#include <bits/stdc++.h>

using namespace std;

bool isXmas(int start, int end, vector<char> line) {
  string result(line.begin() + start, line.begin() + end + 1);

  if (result == "XMAS" || result == "SAMX") {
    return true;
  }

  return false;
}

bool isMas(int start, int end, vector<char> line) {
  string result(line.begin() + start, line.begin() + end + 1);

  if (result == "MAS" || result == "SAM") {
    return true;
  }

  return false;
}

int getDiaCount(vector<vector<char>> matrix) {
  int start = 0, end = 3, col = 0, xmas_count = 0;

  while (end < matrix.size()) {
    while (col + 3 < matrix[0].size()) {
      int i = start, j = col;

      vector<char> bottom_right_line;

      while (i <= end) {
        bottom_right_line.push_back(matrix[i][j]);
        i++;
        j++;
      }

      if (isXmas(0, 3, bottom_right_line)) {
        xmas_count++;
      }

      int k = end, l = col;

      vector<char> top_right_line;

      while (k >= start) {
        top_right_line.push_back(matrix[k][l]);
        k--;
        l++;
      }

      if (isXmas(0, 3, top_right_line)) {
        xmas_count++;
      }

      col++;
    }

    col = 0;
    start++;
    end++;
  }

  return xmas_count;
}

int getHorCount(vector<vector<char>> matrix) {
  int start = 0, end = 3, xmas_count = 0;

  for (vector<char> row : matrix) {
    while (end < row.size()) {
      if (isXmas(start, end, row)) {
        xmas_count++;
      }

      start++;
      end++;
    }

    start = 0;
    end = 3;
  }

  return xmas_count;
}

int getVerCount(vector<vector<char>> matrix) {
  int row_start = 0, row_end = 3, col = 0, xmas_count = 0;

  while (row_end < matrix.size()) {
    while (col < matrix[0].size()) {
      vector<char> line;

      for (int i = row_start; i <= row_end; i++) {
        line.push_back(matrix[i][col]);
      }

      if (isXmas(0, 3, line)) {
        xmas_count++;
      }

      col++;
    }
    col = 0;
    row_start++;
    row_end++;
  }

  return xmas_count;
}

int getXMasCount(vector<vector<char>> matrix) {
  int start = 0, end = 2, col = 0, xmas_count = 0;

  while (end < matrix.size()) {
    while (col + 2 < matrix[0].size()) {
      int i = start, j = col;

      vector<char> bottom_right_line;

      while (i <= end) {
        bottom_right_line.push_back(matrix[i][j]);
        i++;
        j++;
      }

      int k = end, l = col;

      vector<char> top_right_line;

      while (k >= start) {
        top_right_line.push_back(matrix[k][l]);
        k--;
        l++;
      }

      if (isMas(0, 2, bottom_right_line) && isMas(0, 2, top_right_line)) {
        xmas_count++;
      }

      col++;
    }

    col = 0;
    start++;
    end++;
  }

  return xmas_count;
}

int main() {
  freopen("input/day-4.txt", "r", stdin);

  ios::sync_with_stdio(0);
  cin.tie(0);

  vector<vector<char>> word_matrix;
  string line;

  while (getline(cin, line)) {
    vector<char> row;

    for (char ch : line) {
      row.push_back(ch);
    }

    word_matrix.push_back(row);
  }

  int sum = getHorCount(word_matrix) + getVerCount(word_matrix) +
            getDiaCount(word_matrix);

  cout << sum << "\n";
  cout << getXMasCount(word_matrix) << "\n";

  return 0;
}
