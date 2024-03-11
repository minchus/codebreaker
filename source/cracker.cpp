#include "cracker.hpp"
#include <fmt/core.h>
#include <fstream>
#include <iostream>

void Cracker::SetCipherText(const std::string& cipher_text) {
  cipher_text_ = cipher_text;

  // Uppercase
  std::transform(cipher_text_.begin(), cipher_text_.end(), cipher_text_.begin(),
                 ::toupper);

  // Keep only A-Z characters
  std::erase_if(cipher_text_,
                [](auto const& c) -> bool { return c < 'A' || c > 'Z'; });

  // Initialise plain_text_ string and string view
  plain_text_ = cipher_text_;
  plain_text_sv_ = plain_text_;
}

void Cracker::LoadScores(const std::string& path) {
  using Rows = std::vector<std::vector<std::string>>;
  Rows rows;

  std::ifstream score_file(path);
  if (!score_file.is_open()) {
    throw std::runtime_error(
        fmt::format("Error: Unable to open file {}", path));
  }

  for (std::string row; std::getline(score_file, row, '\n');) {
    size_t pos = row.find(',');
    std::string tetragraph = row.substr(0, pos);
    std::string score = row.substr(pos + 1);
    scores_[tetragraph] = static_cast<uint64_t>(std::stod(score) * 1e6);
  }
}

void Cracker::Decrypt() {
  for (int i = 0; i < cipher_text_.size(); i++) {
    plain_text_[i] = key_[cipher_text_[i] - 'A'];
  }
}

bool Cracker::CurrentKeyIsBetter() {
  Decrypt();
  uint64_t score = CalculateScore();
  if (score > best_score_) {
    best_score_ = score;
    best_key_ = GetKey();
    best_plain_text_ = GetPlainText();
    return true;
  }
  return false;
}

bool Cracker::ImproveKeyWithExchanges() {
  for (int i = 0; i < kKeySize - 1; i++) {
    for (int j = i + 1; j < kKeySize; j++) {
      std::swap(key_[i], key_[j]);
      if (!CurrentKeyIsBetter()) {
        std::swap(key_[i], key_[j]);
      } else {
        std::cout << fmt::format("{},{}", key_[j], key_[i]) << std::endl;
        PrintBest();
        return true;
      }
    }
  }
  return false;
}

uint64_t Cracker::CalculateScore() const {
  uint64_t result = 0.0;
  for (int i = 0; i <= plain_text_sv_.length() - 4; i++) {
    auto sub_str = plain_text_sv_.substr(i, 4);
    if (auto it{scores_.find(sub_str)}; it != scores_.end()) {
      result += it->second;
    }
  }
  return result;
}

void Cracker::Crack() {
  best_key_ = "";
  best_plain_text_ = "";
  best_score_ = 0;

  // SetKey(Cracker::InvertKey("COMPANYBDEFGHIJKLQRSTUVWXZ"));
  //SetKey(Cracker::InvertKey("OCMPANYBDEFGHIJKLQRSTUVWXZ"));
  if (CurrentKeyIsBetter()) {
    PrintBest();
  }

  for (int i = 0; i < 100000; i++) {
    // std::cout << "i=" << i << std::endl;
    ShuffleKey();
    if (CurrentKeyIsBetter()) {
      PrintBest();
    }
    while(ImproveKeyWithExchanges()) {
      // do nothing
    };
  }
}

std::string Cracker::InvertKey(const std::string& key) {
  // TODO: sanitize input

  std::string tmp = key;
  for (int i = 0; i < key.size(); i++) {
    tmp[key[i] - 'A'] = 'A' + i;
  }
  return tmp;
}

void Cracker::PrintBest() const {
  std::cout << GetCipherText() << std::endl;
  std::cout << GetBestPlainText() << std::endl;
  std::cout << "best_score=" << GetBestScore() << std::endl;
  std::cout << "ABCDEFGHIJKLMNOPQRSTUVWXYZ" << std::endl;
  std::cout << GetBestKey() << std::endl;
  std::cout << InvertKey(GetBestKey()) << std::endl;
}
