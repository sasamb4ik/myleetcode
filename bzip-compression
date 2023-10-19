#include <iostream>
#include <vector>

const static std::string kAlphabet = "abcdefghijklmnopqrstuvwxyz";
const static int kTEN = 10;

std::vector<int> SortCyclicShifts(std::string& string) {
  const size_t kAlphabetSize = 256;
  std::vector<int> p_array(string.size());
  std::vector<int> c_array(string.size());
  std::vector<int> cnt(std::max(kAlphabetSize, string.size()), 0);
  for (char letter : string) {
    ++cnt[letter];
  }
  for (size_t i = 1; i < kAlphabetSize; i++) {
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

std::string GetBwt(std::vector<int>& suffix_array, std::string& string) {
  std::string bwt;
  for (size_t i = 0; i < string.size(); ++i) {
    bwt.push_back(
        string[(suffix_array[i] + string.size() - 1) % string.size()]);
  }
  return bwt;
}

void MoveStringForward(std::string& alphabet, size_t index) {
  std::string movement_letter(1, alphabet[index]);
  std::string buffer = movement_letter;
  for (size_t i = 0; i < index; ++i) {
    buffer.push_back(alphabet[i]);
  }
  for (size_t i = index + 1; i < alphabet.size(); ++i) {
    buffer.push_back(alphabet[i]);
  }
  alphabet = buffer;
}

std::vector<size_t> GetMTF(std::string& bwt_string) {
  std::vector<size_t> mtf;
  std::string alphabet = kAlphabet;
  for (char letter : bwt_string) {
    auto index = alphabet.find(letter);
    mtf.push_back(index);
    MoveStringForward(alphabet, index);
  }
  return mtf;
}

void GetRLE(std::string& mtf_encoding) {
  for (size_t i = 0; i < mtf_encoding.length(); i++) {
    size_t count = 1;
    while (i < mtf_encoding.length() - 1 &&
           mtf_encoding[i] == mtf_encoding[i + 1]) {
      ++count;
      ++i;
    }
    std::cout << mtf_encoding[i] << count;
  }
}

void Encrypt(std::string& string) {
  auto suffix = SuffixArrayConstruction(string);
  auto bwt = GetBwt(suffix, string);
  std::string alphabet = kAlphabet;
  auto mtf = GetMTF(bwt);
  std::string mtf_result;
  for (auto item : mtf) {
    mtf_result.push_back(alphabet[item]);
  }
  GetRLE(mtf_result);
}

std::string DecodeRLE(const std::string& encoded) {
  std::string rle_result;
  size_t ind = 0;

  while (ind < encoded.size()) {
    char character = encoded[ind];
    int count = 0;
    ++ind;

    while (ind < encoded.size() && (isdigit(encoded[ind]) != 0)) {
      count = count * kTEN + (encoded[ind] - '0');
      ind++;
    }

    for (int j = 0; j < count; j++) {
      rle_result += character;
    }
  }

  return rle_result;
}

void MoveToFront(size_t index, std::string& list) {
  std::vector<char> record(kAlphabet.size());
  for (size_t i = 0; i < list.size(); i++) {
    record[i] = list[i];
  }

  for (size_t i = 1; i <= index; i++) {
    list[i] = record[i - 1];
  }

  list[0] = record[index];
}

std::string DecodeMTF(std::vector<size_t>& digits_array) {
  std::string list = kAlphabet;
  std::string decoded_mtf;

  for (size_t item : digits_array) {
    decoded_mtf.push_back(list[item]);

    MoveToFront(item, list);
  }
  return decoded_mtf;
}

std::string DecodeBWT(const std::string& bwt_encoded, int index) {
  std::vector<std::pair<char, int>> last_column;

  // Populate last_column with characters and their corresponding indices
  for (size_t i = 0; i < bwt_encoded.size(); ++i) {
    last_column.emplace_back(bwt_encoded[i], i);
  }

  // Sort last_column lexicographically
  std::sort(last_column.begin(), last_column.end());

  std::string original;

  // Traverse to find the original string
  for (int i = 0; i < static_cast<int>(bwt_encoded.size()); ++i) {
    original += last_column[index].first;
    index = last_column[index].second;
  }

  return original;
}

void Decode(std::string& string, int bwt_helper) {
  std::string list = kAlphabet;
  auto decoded_rle = DecodeRLE(string);
  std::vector<size_t> mtf_result;
  for (char letter : decoded_rle) {
    mtf_result.push_back(list.find(letter));
  }
  auto decoded_mtf = DecodeMTF(mtf_result);
  // сейчас остался последний шаг - декодировать BWT зная bwt_helper
  auto decoded_bwt = DecodeBWT(decoded_mtf, bwt_helper);
  std::cout << decoded_bwt;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  short mode;
  std::cin >> mode;
  std::string input;
  std::cin >> input;

  if (mode == 1) {
    Encrypt(input);
  }

  if (mode == 2) {
    int decode_help;
    std::cin >> decode_help;
    Decode(input, decode_help);
  }

  return 0;
}
