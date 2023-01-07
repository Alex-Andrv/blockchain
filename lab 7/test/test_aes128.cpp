//
// Created by Alexander Andreev on 07.01.2023.
//
#include <iostream>
#include "../src/AES128.h"

int main() {
    std::string in  = "Hell0w world9999";
    std::string key = "some key99999999";

    std::cout << "text: " << in << "\n";
    std::cout << "key: " << key << "\n";

    std::vector<std::byte> out_bytes = AES::encrypt(in, key);

    std::string out_string;

    std::transform(std::begin(out_bytes), std::end(out_bytes), std::back_inserter(out_string), [](std::byte b){
        return char(b);
    });

    std::cout << "encode: " << out_string << "\n";


    std::vector<std::byte> decode_bytes = AES::decrypt(out_string, key);

    std::string decode_string;

    std::transform(std::begin(decode_bytes), std::end(decode_bytes), std::back_inserter(decode_string), [](std::byte b){
        return char(b);
    });

    std::cout << "decode: " << decode_string << " ";
}