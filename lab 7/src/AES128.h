//
// Created by Alexander Andreev on 07.01.2023.
//

#include <vector>
#include <unordered_map>

#ifndef LAB_7_AES128_H
#define LAB_7_AES128_H

#endif //LAB_7_AES128_H

class AES128 {

    const std::vector<std::vector<std::string>> SBOX = {
            {"63", "7c", "77", "7b", "f2", "6b", "6f", "c5", "30", "01", "67", "2b", "fe", "d7", "ab", "76"},
            {"ca", "82", "c9", "7d", "fa", "59", "47", "f0", "ad", "d4", "a2", "af", "9c", "a4", "72", "c0"},
            {"b7", "fd", "93", "26", "36", "3f", "f7", "cc", "34", "a5", "e5", "f1", "71", "d8", "31", "15"},
            {"04", "c7", "23", "c3", "18", "96", "05", "9a", "07", "12", "80", "e2", "eb", "27", "b2", "75"},
            {"09", "83", "2c", "1a", "1b", "6e", "5a", "a0", "52", "3b", "d6", "b3", "29", "e3", "2f", "84"},
            {"53", "d1", "00", "ed", "20", "fc", "b1", "5b", "6a", "cb", "be", "39", "4a", "4c", "58", "cf"},
            {"d0", "ef", "aa", "fb", "43", "4d", "33", "85", "45", "f9", "02", "7f", "50", "3c", "9f", "a8"},
            {"51", "a3", "40", "8f", "92", "9d", "38", "f5", "bc", "b6", "da", "21", "10", "ff", "f3", "d2"},
            {"cd", "0c", "13", "ec", "5f", "97", "44", "17", "c4", "a7", "7e", "3d", "64", "5d", "19", "73"},
            {"60", "81", "4f", "dc", "22", "2a", "90", "88", "46", "ee", "b8", "14", "de", "5e", "0b", "db"},
            {"e0", "32", "3a", "0a", "49", "06", "24", "5c", "c2", "d3", "ac", "62", "91", "95", "e4", "79"},
            {"e7", "c8", "37", "6d", "8d", "d5", "4e", "a9", "6c", "56", "f4", "ea", "65", "7a", "ae", "08"},
            {"ba", "78", "25", "2e", "1c", "a6", "b4", "c6", "e8", "dd", "74", "1f", "4b", "bd", "8b", "8a"},
            {"70", "3e", "b5", "66", "48", "03", "f6", "0e", "61", "35", "57", "b9", "86", "c1", "1d", "9e"},
            {"e1", "f8", "98", "11", "69", "d9", "8e", "94", "9b", "1e", "87", "e9", "ce", "55", "28", "df"},
            {"8c", "a1", "89", "0d", "bf", "e6", "42", "68", "41", "99", "2d", "0f", "b0", "54", "bb", "16"}};

    const std::vector<std::byte> RCON = {std::byte{0}, std::byte{1}, std::byte{2}, std::byte{4},
                                         std::byte{8}, std::byte{16}, std::byte{32}, std::byte{64},
                                         std::byte{128}, std::byte{27}, std::byte{54}};
    // for more info see:https://ru.wikipedia.org/wiki/AES_(%D1%81%D1%82%D0%B0%D0%BD%D0%B4%D0%B0%D1%80%D1%82_%D1%88%D0%B8%D1%84%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D1%8F)

    const std::vector<std::vector<std::string>> INV_SBOX = {
            {"52", "09", "6a", "d5", "30", "36", "a5", "38", "bf", "40", "a3", "9e", "81", "f3", "d7", "fb"},
            {"7c", "e3", "39", "82", "9b", "2f", "ff", "87", "34", "8e", "43", "44", "c4", "de", "e9", "cb"},
            {"54", "7b", "94", "32", "a6", "c2", "23", "3d", "ee", "4c", "95", "0b", "42", "fa", "c3", "4e"},
            {"08", "2e", "a1", "66", "28", "d9", "24", "b2", "76", "5b", "a2", "49", "6d", "8b", "d1", "25"},
            {"72", "f8", "f6", "64", "86", "68", "98", "16", "d4", "a4", "5c", "cc", "5d", "65", "b6", "92"},
            {"6c", "70", "48", "50", "fd", "ed", "b9", "da", "5e", "15", "46", "57", "a7", "8d", "9d", "84"},
            {"90", "d8", "ab", "00", "8c", "bc", "d3", "0a", "f7", "e4", "58", "05", "b8", "b3", "45", "06"},
            {"d0", "2c", "1e", "8f", "ca", "3f", "0f", "02", "c1", "af", "bd", "03", "01", "13", "8a", "6b"},
            {"3a", "91", "11", "41", "4f", "67", "dc", "ea", "97", "f2", "cf", "ce", "f0", "b4", "e6", "73"},
            {"96", "ac", "74", "22", "e7", "ad", "35", "85", "e2", "f9", "37", "e8", "1c", "75", "df", "6e"},
            {"47", "f1", "1a", "71", "1d", "29", "c5", "89", "6f", "b7", "62", "0e", "aa", "18", "be", "1b"},
            {"fc", "56", "3e", "4b", "c6", "d2", "79", "20", "9a", "db", "c0", "fe", "78", "cd", "5a", "f4"},
            {"1f", "dd", "a8", "33", "88", "07", "c7", "31", "b1", "12", "10", "59", "27", "80", "ec", "5f"},
            {"60", "51", "7f", "a9", "19", "b5", "4a", "0d", "2d", "e5", "7a", "9f", "93", "c9", "9c", "ef"},
            {"a0", "e0", "3b", "4d", "ae", "2a", "f5", "b0", "c8", "eb", "bb", "3c", "83", "53", "99", "61"},
            {"17", "2b", "04", "7e", "ba", "77", "d6", "26", "e1", "69", "14", "63", "55", "21", "0c", "7d"}};

    const int Nk = 4, Nb = 4, Nr = 10;

public:
    std::vector<std::byte> state;
    std::vector<std::vector<std::byte>> keys;
    bool decrypt;

    explicit AES128(const std::string& text, const std::string& key, bool decrypt_ = false) {
        decrypt = decrypt_;

        assert(text.size() == 16); // work only with 128 bytes
        assert(key.size() == 16); // work only with 128 bytes

        state.reserve(text.size());
        std::transform(std::begin(text), std::end(text), std::back_inserter(state), [](char c){
            return std::byte(c);
        });

        std::vector<std::byte> key_;
        std::transform(std::begin(key), std::end(key), std::back_inserter(key_), [](char c){
            return std::byte(c);
        });

        keys.emplace_back(key_);
    }

    std::byte sbox(std::byte x, bool decrypt_ = false) {
        int x_ = std::to_integer<int>(x);
        std::string s = (decrypt_ ? INV_SBOX : SBOX)[x_ >> 4][x_ & 15];
        std::size_t pos{};
        return static_cast<std::byte>(std::stoi(s, &pos, 16));
    }

    void key_expansion() {
        for (int j = 1; j != 11; j++) {
            std::vector<std::byte> key = keys[j-1];
            std::vector<std::byte> column = {key[13], key[14], key[15], key[12]};
            for (auto& x: column) x = sbox(x);
            column[0] ^= RCON[j];

            std::transform(begin(column), end(column), begin(key), begin(key), std::bit_xor<>());
            std::transform(begin(key)+4, end(key), begin(key), begin(key)+4, std::bit_xor<>());
            keys.emplace_back(std::move(key));
        }
    }

    void shift_rows() {
        int k = decrypt ? 3 : 1; // coef for rotation point
        for (int i = 1; i != 4; ++i)
            shift_row({state[i], state[4+i], state[8+i], state[12+i]}, (k*i) % 4, i);
    }

    void shift_row(std::vector<std::byte>&& row, int k, int j) {
        std::rotate(begin(row), begin(row)+k, end(row)); // shift
        for (int i = 0; i != 4; ++i) { state[i*4+j] = row[i]; }
    }

    void mix_columns() {
        for (int i = 0; i != 4; i++) {
            const std::vector<std::byte> column = {state[i*4], state[i*4+1], state[i*4+2], state[i*4+3]};
            if (!decrypt) {
                state[i*4] = vector_mult(column, { std::byte(0x2), std::byte(0x3), std::byte(0x1), std::byte(0x1) });
                state[i*4+1] = vector_mult(column, { std::byte(0x1), std::byte(0x2), std::byte(0x3), std::byte(0x1) });
                state[i*4+2] = vector_mult(column, { std::byte(0x1), std::byte(0x1), std::byte(0x2), std::byte(0x3) });
                state[i*4+3] = vector_mult(column, { std::byte(0x3), std::byte(0x1), std::byte(0x1), std::byte(0x2) });
            } else {
                state[i*4] = vector_mult(column, { std::byte(0xe), std::byte(0xb), std::byte(0xd), std::byte(0x9) });
                state[i*4+1] = vector_mult(column, { std::byte(0x9), std::byte(0xe), std::byte(0xb), std::byte(0xd) });
                state[i*4+2] = vector_mult(column, { std::byte(0xd), std::byte(0x9), std::byte(0xe), std::byte(0xb) });
                state[i*4+3] = vector_mult(column, { std::byte(0xb), std::byte(0xd), std::byte(0x9), std::byte(0xe) });
            }
        }
    }

    static std::byte mult_by_2(std::byte x) { return (x < std::byte{128}) ? x << 1 : (x << 1 & std::byte(255)) ^ std::byte(27); }
    static std::byte mult_by_8(std::byte x) { return mult_by_2(mult_by_2(mult_by_2(x))); }

    const std::unordered_map<std::byte, std::function<std::byte(std::byte)>> mapper = {
            {std::byte{0x1}, [](std::byte x) { return x; }},
            {std::byte{0x2}, mult_by_2},
            {std::byte{0x3}, [](std::byte x) { return mult_by_2(x) ^ x; }},
            {std::byte{0x9}, [](std::byte x) { return mult_by_8(x) ^ x; }},
            {std::byte{0xb}, [](std::byte x) { return mult_by_8(x) ^ mult_by_2(x) ^ x; }},
            {std::byte{0xd}, [](std::byte x) { return mult_by_8(x) ^ mult_by_2(mult_by_2(x)) ^ x; }},
            {std::byte{0xe}, [](std::byte x) { return mult_by_8(x) ^ mult_by_2(mult_by_2(x)) ^ mult_by_2(x); }},
    };

    std::byte vector_mult(const std::vector<std::byte>& v1, std::vector<std::byte>&& v2) {
        std::transform(begin(v1), end(v1), begin(v2), begin(v2),
                       [this](std::byte x, std::byte y) { return mapper.at(y)(x); });
//        return std::accumulate(begin(v2), end(v2), std::byte{0}, std::bit_xor<>());
        auto res = std::byte(0);
        for (auto& v2_el: v2) {
            res ^= v2_el;
        }
        return res;
    }

    void add_round_key(int r) {
        std::transform(begin(keys[r]), end(keys[r]), begin(state), begin(state), std::bit_xor<>());
    }
    void substitute_bytes() {
        std::transform(begin(state), end(state), begin(state), [&](std::byte x) { return sbox(x, decrypt); });
    }
};

namespace AES {

    std::vector<std::byte> encrypt(const std::string &text, const std::string &cipher) {
        AES128 aes(text, cipher);
        aes.key_expansion();
        aes.add_round_key(0);
        for (int i = 1; i != 10; i++) {
            aes.substitute_bytes();
            aes.shift_rows();
            aes.mix_columns();
            aes.add_round_key(i);
        }
        aes.substitute_bytes();
        aes.shift_rows();
        aes.add_round_key(10);
        return aes.state;
    }

    std::vector<std::byte> decrypt(const std::string &text, const std::string &cipher) {
        AES128 aes(text, cipher, true);
        aes.key_expansion();
        aes.add_round_key(10);
        aes.shift_rows();
        aes.substitute_bytes();
        for (int i = 9; i != 0; --i) {
            aes.add_round_key(i);
            aes.mix_columns();
            aes.shift_rows();
            aes.substitute_bytes();
        }
        aes.add_round_key(0);
        return aes.state;
    }
}
