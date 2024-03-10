#include <catch2/catch_test_macros.hpp>

#include "cracker.hpp"

TEST_CASE("Basic score", "[cracker]")
{
  CodeBreaker c(R"(C:\Users\Ming\code\codebreaker\tetragraphs.csv)");
  c.SetCipherText("AAAA");
  REQUIRE(c.CalculateScore() == 711880);

  c.SetCipherText("AAAAR");
  REQUIRE(c.CalculateScore() == 711880 + 1405030);
}
