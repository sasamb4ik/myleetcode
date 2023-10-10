#include <iostream>
#include <vector>

struct SuffixArray {
  std::string s;
  std::vector<int> suffix_array;
  const size_t kAlphabet = 256;

  SuffixArray(const std::string& str) : s(str), suffix_array(str.size()) {
    s.push_back('$');
    std::vector<int> c_array(s.size());
    std::vector<int> p_array(s.size());
    std::vector<int> count(std::max(s.size(), kAlphabet));
    for (size_t i = 0; i < s.size();
         ++i) {  // разбор k = 0, сортировка 1-ых букв
      ++count[s[i]];
    }
    for (size_t i = 1; i < kAlphabet; ++i) {
      count[i] += count[i - 1];
    }
    for (size_t i = 0; i < s.size(); ++i) {
      p_array[--count[s[i]]] = i;
    }
    c_array[p_array[0]] = 0;
    size_t number_cl = 1;
    for (size_t i = 1; i < s.size(); i++) {
      if (s[p_array[i]] != s[p_array[i - 1]]) {
        number_cl++;
      }
      c_array[p_array[i]] = number_cl - 1;
    }  // конец случая k = 0, переход 2^k -> 2^(k+1)
    std::vector<int> pn(s.size());
    std::vector<int> cn(s.size());
    for (size_t j = 0; (1 << j) < s.size(); ++j) {
      int len = 1 << j;
      for (size_t i = 0; i < s.size(); ++i) {
        pn[i] = p_array[i] - len;
        if (pn[i] < 0) {
          pn[i] += static_cast<int>(s.size());
        }
      }
      fill(count.begin(), count.begin() + number_cl, 0);
      for (size_t i = 0; i < s.size(); ++i) {
        ++count[c_array[pn[i]]];
      }
      for (size_t i = 1; i < number_cl; ++i) {
        count[i] += count[i - 1];
      }
      for (int i = static_cast<int>(s.size() - 1); i >= 0; i--) {
        p_array[--count[c_array[pn[i]]]] = pn[i];
      }
      cn[p_array[0]] = 0;
      number_cl = 1;
      for (size_t i = 1; i < s.size(); ++i) {
        std::pair<int, int> current = {
            c_array[p_array[i]], c_array[(p_array[i] + (1 << j)) % s.size()]};
        std::pair<int, int> prev = {
            c_array[p_array[i - 1]],
            c_array[(p_array[i - 1] + (1 << j)) % s.size()]};
        if (current != prev) {
          number_cl++;
        }
        cn[p_array[i]] = number_cl - 1;
      }
      c_array.swap(cn);
    }
    Fix(suffix_array, p_array, s);
  }

  static void Fix(std::vector<int>& suff_array, std::vector<int>& p_array,
                  std::string& string) {
    for (size_t i = 0; i < p_array.size() - 1; ++i) {
      suff_array[i] = p_array[i + 1];
    }
    string.pop_back();  // удалим $, т.е. возвращаем строку в исходное состояние
                        // (правило хорошего тона)
  }

  void Print() {
    for (int item : suffix_array) {
      std::cout << item + 1 << " ";
    }
    std::cout << "\n";
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::string string;
  std::cin >> string;

  SuffixArray suffix_array(string);

  suffix_array.Print();

  return 0;
}
