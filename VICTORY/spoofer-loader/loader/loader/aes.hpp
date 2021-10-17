#pragma once

#include <windows.h>
#include <iostream>

#include <cryptopp/cryptlib.h>
#include <cryptopp/rijndael.h>
#include <cryptopp/modes.h>
#include <cryptopp/files.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>
#include <cryptopp/base64.h>
#pragma comment(lib, "cryptlib.lib")

class Encryption {
public:
	std::string encrypt(std::string cipher_key, std::string iv, std::string text);
	std::string decrypt(std::string cipher_key, std::string iv, std::string text);
};

inline std::unique_ptr<Encryption> aes_enc;