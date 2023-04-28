#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <unordered_map>

/// Decodes a SLIP-encoded byte sequence
/// @param slipData A vector of SLIP-encoded bytes
/// @return A vector of decoded bytes
std::vector<uint8_t> decodeSlip(const std::vector<uint8_t> &slipData);

/// Converts a uint8_t array to a hex string
/// @param data A uint8_t array
/// @param size The size of the array
/// @return A hex string
std::string uint8ArrayToStringHex(const uint8_t* data, size_t size);

/// Converts a vector of decoded bytes to a hex string
/// @param decodedData A vector of decoded bytes
/// @return A hex string
std::string decodedDataToHex(const std::vector<uint8_t>& decodedData);

/// Converts a hex string to an ASCII string
/// @param hex A hex string
/// @return An ASCII string
std::string hexToASCII(const std::string& hex);

/// Applies a mapping to a string based on a given DS_MAP and a SLIP_MAP
/// @param str The input string to be mapped
/// @param dsMap The mapping to be applied
/// @param slipMap The mapping to be applied
/// @return A string with the mapping applied
std::string applyMaps(const std::string& str, const std::unordered_map<uint8_t, std::string>& dsMap, const std::unordered_map<char, int>& slipMap);

/// Processes the decoded SLIP data and returns a vector of pairs of strings and integers
/// @param slipData A vector of SLIP-encoded bytes
/// @return A vector of pairs of strings and integers
std::vector<std::pair<std::string, int>> processData(const std::vector<uint8_t> &slipData);