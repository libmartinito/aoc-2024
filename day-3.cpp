#include <bits/stdc++.h>

using namespace std;

int getSum(string line) {
  int sum_of_product = 0;
  smatch matches;
  regex pattern(R"(mul\((\d+),(\d+)\))");

  while (regex_search(line, matches, pattern)) {
    sum_of_product += stoi(matches[1]) * stoi(matches[2]);
    line = matches.suffix().str();
  }

  return sum_of_product;
}

int getSumWithConditional(string line, bool &is_enabled) {
  int sum_of_product_with_conditional = 0;
  smatch matches;
  regex pattern(R"(mul\((\d+),(\d+)\)|don't\(\)|do\(\))");

  while (regex_search(line, matches, pattern)) {
    if (matches[0] == "don't()") {
      is_enabled = false;
    } else if (matches[0] == "do()") {
      is_enabled = true;
    } else {
      if (is_enabled) {
        sum_of_product_with_conditional += stoi(matches[1]) * stoi(matches[2]);
      }
    }

    line = matches.suffix().str();
  }

  return sum_of_product_with_conditional;
}

int main() {
  freopen("input/day-3.txt", "r", stdin);

  ios::sync_with_stdio(0);
  cin.tie(0);

  string line;
  int sum_of_product = 0;
  int sum_of_product_with_conditional = 0;

  bool is_enabled = true;
  bool is_first_mul_considered = false;

  while (getline(cin, line)) {
    sum_of_product += getSum(line);
    sum_of_product_with_conditional += getSumWithConditional(line, is_enabled);
  }

  cout << sum_of_product << "\n";
  cout << sum_of_product_with_conditional << "\n";

  return 0;
}
