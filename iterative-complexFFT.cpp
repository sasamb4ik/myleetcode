#include <algorithm>
#include <complex>
#include <iostream>
#include <vector>

const double kPi = acos(-1);

struct Polynom {
  std::vector<std::complex<double>> polynom;
  int exponent;
  int degree;
  Polynom(std::vector<int>& coef) {
    exponent = ceil(log(static_cast<double>(coef.size())) / log(2));
    degree = (1 << exponent);
    coef.resize(degree, 0);
    for (int& item : coef) {
      polynom.emplace_back(item, 0);
    }
  }
};

void BitReverse(std::vector<std::complex<double>>& array, int exponenta) {
  const size_t kSize = array.size();

  for (size_t i = 0; i < kSize; ++i) {
    size_t j_ind = 0;
    for (size_t bit = 0; bit < static_cast<size_t>(exponenta); ++bit) {
      j_ind |= ((i >> bit) & 1) << (exponenta - 1 - bit);
    }

    if (i < j_ind) {
      std::swap(array[i], array[j_ind]);
    }
  }
}

void FFT(Polynom& polynom_object) {
  BitReverse(polynom_object.polynom, polynom_object.exponent);
  for (int j = 0; j < polynom_object.exponent; ++j) {
    for (int i = 0; i < polynom_object.degree; i += (1 << (j + 1))) {
      std::complex<double> omega(1, 0);
      double phi = 2 * (kPi / (1 << (j + 1)));
      std::complex<double> omega_temp(cos(phi), sin(phi));
      for (int iter = 0; iter < (1 << j); ++iter) {
        auto temp1 = polynom_object.polynom[i + iter];
        auto temp2 = polynom_object.polynom[i + iter + (1 << j)] * omega;
        polynom_object.polynom[i + iter] = temp1 + temp2;
        polynom_object.polynom[i + iter + (1 << j)] = temp1 - temp2;
        omega = omega * omega_temp;
      }
    }
  }
}

void IFFT(Polynom& polynom_object) {
  BitReverse(polynom_object.polynom, polynom_object.exponent);
  for (int j = 0; j < polynom_object.exponent; ++j) {
    for (int i = 0; i < polynom_object.degree; i += (1 << (j + 1))) {
      std::complex<double> omega(1, 0);
      double phi = -1 * 2 * kPi / (1 << (j + 1));
      std::complex<double> omega_temp(cos(phi), sin(phi));
      for (int iter = 0; iter < (1 << j); ++iter) {
        auto temp1 = polynom_object.polynom[i + iter];
        auto temp2 = polynom_object.polynom[i + iter + (1 << j)] * omega;
        polynom_object.polynom[i + iter] = temp1 + temp2;
        polynom_object.polynom[i + iter + (1 << j)] = temp1 - temp2;
        omega = omega * omega_temp;
      }
    }
  }
  for (auto& elem : polynom_object.polynom) {
    elem = std::complex<double>(round(elem.real() / polynom_object.degree), 0);
  }
}

std::vector<std::complex<double>> Multiple(std::vector<int>& coef1, int size1,
                                           std::vector<int>& coef2, int size2) {
  coef1.resize(size1 + size2 + 1);
  coef2.resize(size1 + size2 + 1);
  Polynom polynom1(coef1);
  Polynom polynom2(coef2);
  FFT(polynom1);
  FFT(polynom2);
  for (size_t i = 0; i < polynom1.polynom.size(); ++i) {
    polynom1.polynom[i] = polynom1.polynom[i] * polynom2.polynom[i];
  }
  IFFT(polynom1);
  return polynom1.polynom;
}

int main() {
  int number1;
  std::cin >> number1;
  std::vector<int> coef1(number1 + 1);
  for (int i = 0; i <= number1; ++i) {
    std::cin >> coef1[number1 - i];
  }
  int number2;
  std::cin >> number2;
  std::vector<int> coef2(number2 + 1);
  for (int i = 0; i <= number2; ++i) {
    std::cin >> coef2[number2 - i];
  }
  auto polynom = Multiple(coef1, number1, coef2, number2);
  std::cout << number1 + number2 << " ";
  for (int i = 0; i <= number1 + number2; ++i) {
    std::cout << static_cast<int>(floor(polynom[number1 + number2 - i].real()))
              << " ";
  }
}
