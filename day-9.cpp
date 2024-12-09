#include <bits/stdc++.h>

using namespace std;

vector<map<string, long>>
getUpdatedExpandedVec(vector<map<string, long>> expanded_vec) {
  int lo = 0;
  int hi = expanded_vec.size() - 1;

  while (lo < hi) {
    if (expanded_vec[lo]["id"] != -1) {
      lo++;
      continue;
    }

    if (expanded_vec[hi]["id"] == -1) {
      hi--;
      continue;
    }

    map<string, long> temp_hi = expanded_vec[hi];
    expanded_vec[hi] = expanded_vec[lo];
    expanded_vec[lo] = temp_hi;

    lo++;
    hi--;
  }

  return expanded_vec;
}

vector<vector<int>> getLocAndSize(vector<map<string, long>> &expanded_vec,
                                  string type) {
  vector<vector<int>> loc_and_sizes{};
  vector<int> loc_and_size{};

  for (size_t i = 0; i < expanded_vec.size(); i++) {
    if (type == "spaces") {
      if (expanded_vec[i]["id"] != -1) {
        continue;
      }
    } else {
      if (expanded_vec[i]["id"] == -1) {
        continue;
      }
    }

    size_t end{i};

    while (end < expanded_vec.size()) {
      if (expanded_vec[i]["id"] != expanded_vec[end]["id"]) {
        end--;
        break;
      }

      end++;
    }

    if (end == expanded_vec.size()) {
      end--;
    }

    loc_and_size.push_back(i);
    loc_and_size.push_back(end - i + 1);
    loc_and_sizes.push_back(loc_and_size);
    loc_and_size = {};
    i = end;
  }

  return loc_and_sizes;
}

int getSpaceIndexForFile(vector<vector<int>> space_loc_and_sizes,
                         vector<int> file) {
  int file_index{file[0]};
  int file_size{file[1]};

  for (size_t i = 0; i < space_loc_and_sizes.size(); i++) {
    vector<int> space{space_loc_and_sizes[i]};
    int space_index{space[0]};
    int space_size{space[1]};

    if (space_index < file_index && space_size >= file_size) {
      return space_index;
    }
  }

  return -1;
}

vector<map<string, long>> getUpdatedExpandedVecWithEntireFilesMoved(
    vector<map<string, long>> expanded_vec) {
  vector<vector<int>> file_loc_and_sizes{getLocAndSize(expanded_vec, "files")};

  vector<vector<int>> space_loc_and_sizes{
      getLocAndSize(expanded_vec, "spaces")};

  for (int i = file_loc_and_sizes.size() - 1; i >= 0; i--) {
    vector<int> file{file_loc_and_sizes[i]};
    int space_index_for_file = getSpaceIndexForFile(space_loc_and_sizes, file);

    if (space_index_for_file == -1) {
      continue;
    }

    int file_index{file[0]};
    int file_size{file[1]};

    for (int j = space_index_for_file; j < space_index_for_file + file_size;
         j++) {
      expanded_vec[j] = expanded_vec[file_index];
    }

    for (int k = file_index; k < file_index + file_size; k++) {
      expanded_vec[k] = {{"id", -1}};
    }

    space_loc_and_sizes = getLocAndSize(expanded_vec, "spaces");
  }

  return expanded_vec;
}

long getSumOfProduct(vector<map<string, long>> &expanded_vec) {
  long sum_of_product{0};

  for (size_t i = 0; i < expanded_vec.size(); i++) {
    if (expanded_vec[i]["id"] == -1) {
      continue;
    }

    sum_of_product += expanded_vec[i]["id"] * i;
  }

  return sum_of_product;
}

int main() {
  freopen("input/day-9.txt", "r", stdin);

  ios::sync_with_stdio(0);
  cin.tie(0);

  string line{""};
  getline(cin, line);

  vector<map<string, long>> expanded_vec{};
  long id{0};

  for (size_t i = 0; i < line.size(); i++) {
    for (int j = 0; j < line[i] - '0'; j++) {
      if (i % 2 == 0) {
        expanded_vec.push_back({{"id", id}});
      } else {
        expanded_vec.push_back({{"id", -1}});
      }
    }

    if (i % 2 == 0) {
      id++;
    }
  }

  vector<map<string, long>> updated_expanded_vec =
      getUpdatedExpandedVec(expanded_vec);

  cout << getSumOfProduct(updated_expanded_vec) << "\n";

  vector<map<string, long>> updated_expanded_vec_with_entire_files_moved =
      getUpdatedExpandedVecWithEntireFilesMoved(expanded_vec);

  cout << getSumOfProduct(updated_expanded_vec_with_entire_files_moved) << "\n";

  return 0;
}
