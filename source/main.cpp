#include <iostream>
#include <iomanip>
#include <string>

#include "cracker.hpp"

int main()
{
	std::string cipher_text =
		"DSDRO XFIJV DIYSB ANQAL TAIMX VBDMB GASSA QRTRT CGGXJ MMTQC IPJSB AQPDR SDIMS DUAMB CQCMS AQDRS"
		"DMRJN SBAGC IYTCY ASBCS MQXKS CICGX RSRCQ ACOGA SJPAS AQHDI ASBAK GCDIS AWSJN CMDKB AQHAR RCYAE";

	CodeBreaker c(R"(C:\Users\Ming\code\codebreaker\tetragraphs.csv)");
	c.SetCipherText(cipher_text);
	c.SetKey("COMPANYBDEFGHIJKLQRSTUVWXZ");
	c.InvertKey();

	c.Decrypt();

	std::string plain_text = c.GetPlainText();
	std::cout << plain_text << std::endl;

	double score = c.CalculateScore();
	std::cout <<std::fixed << std::setprecision(0) << "score=" << score << std::endl;

	c.InvertKey();
	std::string key = c.GetKey();
	std::cout << key << std::endl;


	return 0;
}
