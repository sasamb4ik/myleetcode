#include <iostream>
#include <vector>

std::vector<int> SortCyclicShifts(std::string& string) {
  const size_t kAlphabet = 256;
  std::vector<int> p_array(string.size());
  std::vector<int> c_array(string.size());
  std::vector<int> cnt(std::max(kAlphabet, string.size()), 0);
  for (char letter : string) {
    ++cnt[letter];
  }
  for (size_t i = 1; i < kAlphabet; i++) {
    cnt[i] += cnt[i - 1];
  }
  for (size_t i = 0; i < string.size(); i++) {
    p_array[--cnt[string[i]]] = i;
  }
  c_array[p_array[0]] = 0;
  int classes = 1;
  for (size_t i = 1; i < string.size(); i++) {
    if (string[p_array[i]] != string[p_array[i - 1]]) {
      classes++;
    }
    c_array[p_array[i]] = classes - 1;
  }
  std::vector<int> pn(string.size());
  std::vector<int> cn(string.size());
  for (size_t deg = 0; (1 << deg) < string.size(); ++deg) {
    for (size_t i = 0; i < string.size(); i++) {
      pn[i] = p_array[i] - (1 << deg);
      if (pn[i] < 0) {
        pn[i] += string.size();
      }
    }
    fill(cnt.begin(), cnt.begin() + classes, 0);
    for (size_t i = 0; i < string.size(); i++) {
      ++cnt[c_array[pn[i]]];
    }
    for (int i = 1; i < classes; i++) {
      cnt[i] += cnt[i - 1];
    }
    for (int i = static_cast<int>(string.size()) - 1; i >= 0; i--) {
      p_array[--cnt[c_array[pn[i]]]] = pn[i];
    }
    cn[p_array[0]] = 0;
    classes = 1;
    for (size_t i = 1; i < string.size(); i++) {
      std::pair<int, int> cur = {
          c_array[p_array[i]],
          c_array[(p_array[i] + (1 << deg)) % string.size()]};
      std::pair<int, int> prev = {
          c_array[p_array[i - 1]],
          c_array[(p_array[i - 1] + (1 << deg)) % string.size()]};
      if (cur != prev) {
        ++classes;
      }
      cn[p_array[i]] = classes - 1;
    }
    c_array.swap(cn);
  }
  return p_array;
}

std::vector<int> SuffixArrayConstruction(std::string string) {
  std::vector<int> sorted_shifts = SortCyclicShifts(string);
  return sorted_shifts;
}

void GetBwt(std::vector<int>& suffix_array, std::string& string) {
  for (size_t i = 0; i < string.size(); ++i) {
    std::cout << string[(suffix_array[i] + string.size() - 1) % string.size()];
  }
  std::cout << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::string string;
  std::cin >> string;

  auto suffix_array = SuffixArrayConstruction(string);
  GetBwt(suffix_array, string);

  return 0;
}
