#include <iomanip>
#include <iostream>
#include <string>

#include "cracker.hpp"

int main() {
  Cracker c(R"(C:\Users\Ming\code\codebreaker\tetragraphs.csv)");
  c.SetCipherText(
      "DSDRO XFIJV DIYSB ANQAL TAIMX VBDMB GASSA QRTRT CGGXJ MMTQC IPJSB AQPDR "
      "SDIMS DUAMB CQCMS AQDRS"
      "DMRJN SBAGC IYTCY ASBCS MQXKS CICGX RSRCQ ACOGA SJPAS AQHDI ASBAK GCDIS "
      "AWSJN CMDKB AQHAR RCYAE");

  c.Crack();

  // std::cout << "best_plain_text=" << c.GetBestPlainText() << std::endl;
  // std::cout << "best_key=" << c.GetBestKey() << std::endl;
  // std::cout << "best_score=" << c.GetBestScore() << std::endl;

  return 0;
}
