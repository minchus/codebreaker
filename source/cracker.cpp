#include "cracker.hpp"
#include <fmt/core.h>

void CodeBreaker::SetCipherText(const std::string& cipher_text) {
  cipher_text_ = cipher_text;

  // Uppercase
  std::transform(cipher_text_.begin(), cipher_text_.end(), cipher_text_.begin(),
                 ::toupper);

  // Keep only A-Z characters
  std::erase_if(cipher_text_,
                [](auto const& c) -> bool { return c < 'A' || c > 'Z'; });

  // Initialise key
  for (int i = 0; i < 26; i++) {
    key_[i] = 'A' + i;
  }

  // Initialise plain_text_ string and string view
  plain_text_ = cipher_text_;
  plain_text_sv_ = plain_text_;
}

void CodeBreaker::LoadScores(const std::string& path) {
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

void CodeBreaker::Decrypt() {
  for (int i = 0; i < cipher_text_.size(); i++) {
    plain_text_[i] = key_[cipher_text_[i] - 'A'];
  }
}

double CodeBreaker::CalculateScore() {
  double result = 0.0;
  for (int i = 0; i <= plain_text_sv_.length() - 4; i++) {
    auto sub_str = plain_text_sv_.substr(i, 4);
    if (auto it{scores_.find(sub_str)}; it != scores_.end()) {
      result += it->second;
    }
  }
  return result;
}
