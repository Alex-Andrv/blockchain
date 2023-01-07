//
// Created by Alexander Andreev on 07.01.2023.
//

#ifndef LAB_7_RANDOM_H
#define LAB_7_RANDOM_H

#endif //LAB_7_RANDOM_H

#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <random>
#include "AES128.h"

class RandomState {

    std::string key_st;


public:
    explicit RandomState(int key) {
        key_st = std::to_string(key);
        for (int i = key_st.size(); i < 16; i++) {
            key_st.push_back('9');
            /*
             * Простое дополнение нулевыми битами не решает проблемы,
             * так как получатель не сможет найти конец полезных данных.
             * К тому же, такой вариант приводит к атакам Оракула дополнения.
             * Поэтому на практике применимо решение, стандартизованное как «Метод дополнения 2» в ISO/IEC 9797-1,
             * добавляющее единичный бит в конец сообщения и заполняющее оставшееся место нулями.
             * В этом случае была доказана стойкость к подобным атакам.
             * https://ru.wikipedia.org/wiki/%D0%91%D0%BB%D0%BE%D1%87%D0%BD%D1%8B%D0%B9_%D1%88%D0%B8%D1%84%D1%80#.D0.94.D0.BE.D0.BF.D0.BE.D0.BB.D0.BD.D0.B5.D0.BD.D0.B8.D0.B5_.D0.B4.D0.BE_.D1.86.D0.B5.D0.BB.D0.BE.D0.B3.D0.BE_.D0.B1.D0.BB.D0.BE.D0.BA.D0.B0
             */
        }
        assert(key_st.size() == 16);
    }

    //! random value in [0, upper-1]
    int randint(int upper, std::string name) {
        name = name.size() > 16 ? name.substr(0, 16): name; // only 16 len supported
        for (int i = name.size(); i < 16; i++) {
            name.push_back('9');
            /*
             * Простое дополнение нулевыми битами не решает проблемы,
             * так как получатель не сможет найти конец полезных данных.
             * К тому же, такой вариант приводит к атакам Оракула дополнения.
             * Поэтому на практике применимо решение, стандартизованное как «Метод дополнения 2» в ISO/IEC 9797-1,
             * добавляющее единичный бит в конец сообщения и заполняющее оставшееся место нулями.
             * В этом случае была доказана стойкость к подобным атакам.
             * https://ru.wikipedia.org/wiki/%D0%91%D0%BB%D0%BE%D1%87%D0%BD%D1%8B%D0%B9_%D1%88%D0%B8%D1%84%D1%80#.D0.94.D0.BE.D0.BF.D0.BE.D0.BB.D0.BD.D0.B5.D0.BD.D0.B8.D0.B5_.D0.B4.D0.BE_.D1.86.D0.B5.D0.BB.D0.BE.D0.B3.D0.BE_.D0.B1.D0.BB.D0.BE.D0.BA.D0.B0
             */
        }
        std::vector<std::byte> out_bytes = AES::encrypt(name, key_st);
        return _mod(out_bytes, upper);
//        return std::min<int>(uniform() * upper, upper - 1);
    }

private:
    int _mod(std::vector<std::byte> &out_bytes, int upper) {
        int ans = 0;
        for (int i = 0; i < out_bytes.size(); i++) {
            ans = (ans << 4) + std::to_integer<int>(out_bytes[i]);
            if (ans > upper) {
                return ans % upper;
            }
        }
        return ans;
    }

};
