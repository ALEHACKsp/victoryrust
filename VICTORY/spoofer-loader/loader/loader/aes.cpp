#include "aes.hpp"
#include <regex>

using namespace CryptoPP;

std::string space2underscore(std::string text)
{
    std::replace(text.begin(), text.end(), ' ', '+');
    return text;
}

std::string Encryption::encrypt(std::string cipher_key, std::string iv_key, std::string text) {
    std::string cipher;

    AutoSeededRandomPool prng;

    SecByteBlock key((const byte*)cipher_key.data(), cipher_key.size());
    SecByteBlock iv((const byte*)iv_key.data(), iv_key.size());

    try
    {
        CBC_Mode< AES >::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);

        StringSource s(text, true,
            new StreamTransformationFilter(e,
                new Base64Encoder(
                    new StringSink(cipher)
                )
            )
        );
    }
    catch (const Exception& e)
    {
        exit(1);
    }

    cipher = std::regex_replace(cipher, std::regex("\n"), "");

    return cipher;
}

std::string Encryption::decrypt(std::string cipher_key, std::string iv_key, std::string text) {
    std::string recovered;

    AutoSeededRandomPool prng;

    SecByteBlock key((const byte*)cipher_key.data(), cipher_key.size());
    SecByteBlock iv((const byte*)iv_key.data(), iv_key.size());

    try
    {
        CBC_Mode< AES >::Decryption d;
        d.SetKeyWithIV(key, key.size(), iv);

        StringSource s(text, true,
            new Base64Decoder(
                new StreamTransformationFilter(d,
                    new StringSink(recovered)
                ) // StreamTransformationFilter
            )
        ); // StringSource
    }
    catch (const Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    return recovered;
}