#pragma once

#include <cstdint>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

/**
 * @brief The core implementation of the executable
 *
 */

template<typename ... Bases>
struct Overload : Bases ...
{
    using is_transparent = void;
    using Bases::operator() ... ;
};


struct CharPointerHash
{
    auto operator()( const char* ptr ) const noexcept
    {
        return std::hash<std::string_view>{}( ptr );
    }
};

using transparent_string_hash = Overload<
    std::hash<std::string>,
    std::hash<std::string_view>,
    CharPointerHash
>;


class CodeBreaker {
public:
	explicit CodeBreaker(const std::string& path) {
		LoadScores(path);
	}

	void SetCipherText(const std::string& cipher_text);

    void LoadScores(const std::string& path);

    void SetKey(const std::string& key_string) {
		for (int i = 0; i < key_.size(); i++) {
			key_[i] = key_string[i];
		}
	}

	std::string GetKey() const {
		return std::string(key_.begin(), key_.end());
	}

	void InvertKey() {
		std::vector<char> tmp = key_;
		for (int i = 0; i < key_.size(); i++) {
			tmp[key_[i] - 'A'] = 'A' + i;
		}
		key_ = tmp;
	}

	std::string GetPlainText() const {
		return plain_text_;
	}

	void Decrypt();

    void RandomizeKey();

	double CalculateScore();

   private:
	std::vector<char> key_ = std::vector<char>(26);
	std::string cipher_text_;
	std::string plain_text_;
	std::string_view plain_text_sv_;
	std::unordered_map<std::string, uint64_t, transparent_string_hash, std::equal_to<>> scores_;
};
