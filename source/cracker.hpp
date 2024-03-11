#pragma once

#include <algorithm>
#include <cstdint>
#include <random>
#include <unordered_map>
#include <vector>

/**
 * @brief The core implementation of the executable
 *
 */

template <typename... Bases>
struct Overload : Bases... {
  using is_transparent = void;
  using Bases::operator()...;
};

struct CharPointerHash {
  auto operator()(const char* ptr) const noexcept {
    return std::hash<std::string_view>{}(ptr);
  }
};

using transparent_string_hash =
    Overload<std::hash<std::string>, std::hash<std::string_view>,
             CharPointerHash>;

class Cracker {
 public:
  explicit Cracker(const std::string& path) {
    // Initialise key
    for (int i = 0; i < kKeySize; i++) {
      key_[i] = 'A' + i;
    }

    rng_ = std::default_random_engine{std::random_device{}()};
    LoadScores(path);
  }

  void SetCipherText(const std::string& cipher_text);

  void LoadScores(const std::string& path);

  void SetKey(const std::string& key_string) {
    for (int i = 0; i < key_.size(); i++) {
      key_[i] = key_string[i];
    }
  }

  std::string GetKey() const { return std::string(key_.begin(), key_.end()); }

  std::string GetCipherText() const { return cipher_text_; }
  std::string GetPlainText() const { return plain_text_; }

  void Decrypt();

  void ShuffleKey() {
    std::shuffle(std::begin(key_), std::end(key_), rng_);
  };

  bool CurrentKeyIsBetter();

  bool ImproveKeyWithExchanges();

  uint64_t CalculateScore() const;

  void Crack();

  static std::string InvertKey(const std::string& key);

  std::string GetBestKey() const { return best_key_; }
  std::string GetBestPlainText() const { return best_plain_text_; }
  uint64_t GetBestScore() const { return best_score_; }

  void PrintBest() const;

 private:
  static constexpr size_t kKeySize = 26;
  std::vector<char> key_ = std::vector<char>(kKeySize);
  std::string cipher_text_;
  std::string plain_text_;
  std::string_view plain_text_sv_;
  std::unordered_map<std::string, uint64_t, transparent_string_hash,
                     std::equal_to<>>
      scores_;
  std::default_random_engine rng_;

  std::string best_key_;
  std::string best_plain_text_;
  uint64_t best_score_ = 0;
};
