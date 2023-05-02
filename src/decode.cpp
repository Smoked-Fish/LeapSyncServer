// LeapSyncServer - Copyright (c) 2023 Jacob Espy. See LICENSE.txt for more details. 

#include "decode.h"
#include "gamepad.h"
#include "defines.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <iomanip>
#include <sstream>

std::vector<uint8_t> decodeSlip(const std::vector<uint8_t> &slipData) {
    std::vector<uint8_t> decodedData;

    for (uint8_t byte : slipData) {
        bool escaped = false;
        if (escaped) {
            if (byte == SLIP_ESC_END) {
                decodedData.push_back(SLIP_END);
            }
            else if (byte == SLIP_ESC_ESC) {
                decodedData.push_back(SLIP_ESC);
            }
            escaped = false;
        }
        else if (byte == SLIP_ESC) {
            escaped = true;
        }
        else if (byte != SLIP_END) {
            decodedData.push_back(byte);
        }
    }
    return decodedData;
}

std::string uint8ArrayToStringHex(const uint8_t* data, size_t size) {
    std::stringstream ss;
    ss << std::hex << std::uppercase << std::setfill('0');
    for (size_t i = 0; i < size; i++) {
        ss << std::setw(2) << static_cast<unsigned>(data[i]);
    }
    return ss.str();
}

std::string decodedDataToHex(const std::vector<uint8_t>& decodedData) {
    std::string hexString;
    for (uint8_t byte : decodedData) {
        hexString += uint8ArrayToStringHex(&byte, sizeof(byte));
    }
    return hexString;
}

std::string hexToASCII(const std::string& hex) {
    std::string ascii;
    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byte = hex.substr(i, 2);
        char c = static_cast<char>(std::stoi(byte, nullptr, 16));
        ascii += c;
    }
    return ascii;
}

std::string applyMaps(const std::string& str, const std::unordered_map<uint8_t, std::string>& dsMap, const std::unordered_map<char, int>& slipMap) {
    std::stringstream ss;
    for (char c : str) {
        if (dsMap.count(c) > 0) {
            ss << dsMap.at(c);
        } else if (slipMap.count(c) > 0) {
            ss << slipMap.at(c);
        } else {
            ss << c;
        }
    }
    return ss.str();
}

std::vector<std::pair<std::string, int>> processData(const std::vector<uint8_t> &slipData) {
    std::string input = hexToASCII(decodedDataToHex(decodeSlip(slipData)));
    std::vector<std::pair<std::string, int>> result;
    std::unordered_map<uint8_t, std::string> dsMap = {
        {DS_CIRCLE, "CIRCLE"}, {DS_CROSS, "CROSS"}, {DS_SHARE, "SHARE"}, {DS_OPTIONS, "OPTIONS"},
        {DS_TRIGGER_RIGHT, "TRIGGER_RIGHT"}, {DS_TRIGGER_LEFT, "TRIGGER_LEFT"}, {DS_TRIANGLE, "TRIANGLE"},
        {DS_SQUARE, "SQUARE"}, {DS_SHOULDER_LEFT, "SHOULDER_LEFT"}, {DS_SHOULDER_RIGHT, "SHOULDER_RIGHT"},
        {DS_DPAD_EAST, "DPAD_EAST"}, {DS_DPAD_WEST, "DPAD_WEST"}, {DS_DPAD_NORTH, "DPAD_NORTH"},
        {DS_DPAD_SOUTH, "DPAD_SOUTH"}, {DS_TOUCHPAD, "TOUCHPAD"}
    };
    std::unordered_map<char, int> slipMap = {
        {SLIP_TRUE, 0}, {SLIP_FALSE, 1}, {SLIP_CIRCLE, 2},
        {SLIP_CSTICK, 3}, {SLIP_TOUCH, 4}, {SLIP_GYRO, 5}, {SLIP_ACCEL, 6}
    };

    std::string currentStr;
    for (char c : input) {
        if (slipMap.count(c) > 0) {
            if (!currentStr.empty()) {
                std::string mappedStr = applyMaps(currentStr, dsMap, slipMap);
                result.emplace_back(mappedStr, slipMap.at(c));
                currentStr.clear();
            }
        } else {
            currentStr += c;
        }
    }

    return result;
}

