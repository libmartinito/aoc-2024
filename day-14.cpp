#include <bits/stdc++.h>

using namespace std;

struct Robot {
  vector<int> position;
  vector<int> velocity;

  Robot(vector<int> position, vector<int> velocity)
      : position(position), velocity(velocity) {};

  void move(int width, int height, int number_of_times) {
    int row{position[0]}, col{position[1]}, row_v{velocity[0]},
        col_v{velocity[1]};

    int new_row{row + row_v * number_of_times},
        new_col{col + col_v * number_of_times};

    while (new_row < 0 || new_row >= height) {
      if (new_row < 0) {
        new_row = new_row + height;
      } else if (new_row >= height) {
        new_row = new_row - height;
      }
    }

    while (new_col < 0 || new_col >= width) {
      if (new_col < 0) {
        new_col = new_col + width;
      } else if (new_col >= width) {
        new_col = new_col - width;
      }
    }

    position = {new_row, new_col};
  }

  void move_back(int width, int height, int number_of_times) {
    int row{position[0]}, col{position[1]}, row_v{velocity[0]},
        col_v{velocity[1]};

    int new_row{row - row_v * number_of_times},
        new_col{col - col_v * number_of_times};

    while (new_row < 0 || new_row >= height) {
      if (new_row < 0) {
        new_row = new_row + height;
      } else if (new_row >= height) {
        new_row = new_row - height;
      }
    }

    while (new_col < 0 || new_col >= width) {
      if (new_col < 0) {
        new_col = new_col + width;
      } else if (new_col >= width) {
        new_col = new_col - width;
      }
    }

    position = {new_row, new_col};
  }
};

Robot *getRobot(string line) {
  size_t space_pos = line.find(" ");
  string position = line.substr(0, space_pos);
  string velocity = line.substr(space_pos + 1);

  size_t p_comma_pos = position.find(",");
  size_t v_comma_pos = velocity.find(",");

  int col = stoi(position.substr(2, p_comma_pos - 2));
  int row = stoi(position.substr(p_comma_pos + 1));

  int col_v = stoi(velocity.substr(2, v_comma_pos - 2));
  int row_v = stoi(velocity.substr(v_comma_pos + 1));

  return new Robot({row, col}, {row_v, col_v});
}

int getSafetyScore(int width, int height, vector<Robot *> robots) {
  int first_q_count{0}, second_q_count{0}, third_q_count{0}, fourth_q_count{0};

  for (Robot *robot : robots) {
    int row{robot->position[0]}, col{robot->position[1]};
    int vertical_divider{(int)floor(width / 2)};
    int horizontal_divider{(int)floor(height / 2)};

    if (row >= 0 && row < horizontal_divider && col >= 0 &&
        col < vertical_divider) {
      first_q_count++;
    }

    if (row >= 0 && row < horizontal_divider && col > vertical_divider &&
        col < width) {
      second_q_count++;
    }

    if (row > horizontal_divider && row < height && col >= 0 &&
        col < vertical_divider) {
      third_q_count++;
    }

    if (row > horizontal_divider && row < height && col > vertical_divider &&
        col < width) {
      fourth_q_count++;
    }
  }

  return first_q_count * second_q_count * third_q_count * fourth_q_count;
}

bool isClumpPresent(vector<vector<char>> &matrix) {
  for (size_t i = 0; i < matrix.size() - 4; i++) {
    for (size_t j = 0; j < matrix[0].size() - 4; j++) {
      bool clump_present = true;

      for (size_t k = i; k < i + 4; k++) {
        for (size_t l = j; l < j + 4; l++) {
          if (matrix[k][l] != 'a') {
            clump_present = false;
          }
        }
      }

      if (clump_present) {
        return true;
      }
    }
  }

  return false;
}

void drawOnMatrix(vector<vector<char>> &matrix, vector<Robot *> &robots) {
  for (size_t i = 0; i < matrix.size(); i++) {
    for (size_t j = 0; j < matrix[0].size(); j++) {
      matrix[i][j] = '.';
    }
  }

  for (Robot *robot : robots) {
    matrix[robot->position[0]][robot->position[1]] = 'a';
  }
}

int main() {
  freopen("input/day-14.txt", "r", stdin);

  ios::sync_with_stdio(0);
  cin.tie(0);

  string line{""};
  vector<Robot *> robots{};

  while (getline(cin, line)) {
    robots.push_back(getRobot(line));
  }

  for (Robot *robot : robots) {
    robot->move(101, 103, 100);
  }

  cout << getSafetyScore(101, 103, robots) << "\n";

  vector<vector<char>> matrix{};

  for (int i = 0; i < 103; i++) {
    vector<char> row{};

    for (int j = 0; j < 101; j++) {
      row.push_back('.');
    }

    matrix.push_back(row);
  }

  drawOnMatrix(matrix, robots);

  int total_seconds{0};

  while (!isClumpPresent(matrix)) {
    total_seconds++;

    for (Robot *robot : robots) {
      robot->move(101, 103, 1);
    }

    drawOnMatrix(matrix, robots);
  }

  cout << total_seconds << "\n";

  return 0;
}
