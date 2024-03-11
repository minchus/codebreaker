#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "cracker.hpp"

TEST_CASE("Invert key", "[cracker]") {
  REQUIRE(Cracker::InvertKey("DCAB") == "CDBA");
}

// TEST_CASE("Swap key", "[cracker]") {
//   Cracker c(R"(C:\Users\Ming\code\codebreaker\tetragraphs.csv)");
//   std::cout << c.GetKey() << std::endl;
//   c.SwapKey();
//   std::cout << c.GetKey() << std::endl;
//   REQUIRE(true);
// }

TEST_CASE("Shuffle key", "[cracker]") {
  Cracker c(R"(C:\Users\Ming\code\codebreaker\tetragraphs.csv)");
  std::cout << c.GetKey() << std::endl;
  for (int i = 0; i < 10; i++) {
    c.ShuffleKey();
    std::cout << c.GetKey() << std::endl;
  }
  REQUIRE(true);
}

TEST_CASE("Basic score", "[cracker]") {
  Cracker c(R"(C:\Users\Ming\code\codebreaker\tetragraphs.csv)");
  c.SetCipherText("AAAA");
  REQUIRE(c.CalculateScore() == 711880);

  c.SetCipherText("AAAAR");
  REQUIRE(c.CalculateScore() == 711880 + 1405030);

  c.SetCipherText(
      "DSDRO XFIJV DIYSB ANQAL TAIMX VBDMB GASSA QRTRT CGGXJ MMTQC IPJSB AQPDR "
      "SDIMS DUAMB CQCMS AQDRS"
      "DMRJN SBAGC IYTCY ASBCS MQXKS CICGX RSRCQ ACOGA SJPAS AQHDI ASBAK GCDIS "
      "AWSJN CMDKB AQHAR RCYAE");
  uint64_t encrypted_score = c.CalculateScore();

  c.SetKey(Cracker::InvertKey("COMPANYBDEFGHIJKLQRSTUVWXZ"));
  c.Decrypt();
  uint64_t decrypted_score = c.CalculateScore();

  std::cout << "encrpyted_score=" << encrypted_score << std::endl;
  std::cout << "decrpyted_score=" << decrypted_score << std::endl;
  REQUIRE(decrypted_score > encrypted_score);
}
