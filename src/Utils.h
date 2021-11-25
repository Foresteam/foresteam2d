#pragma once
#include <random>
#include <string>

#define sqr(x) ((x) * (x))

#define DEG2RAD M_PI / 180
#define dsin(arg)  sin((arg) * DEG2RAD)
#define dcos(arg)  cos((arg) * DEG2RAD)
#define dtan(arg)  tan((arg) * DEG2RAD)
#define dasin(arg) asin(arg) / DEG2RAD
#define dacos(arg) acos(arg) / DEG2RAD
#define datan(arg) atan(arg) / DEG2RAD

namespace Utils {
	/// @param from Random start
	/// @param to Random end
	/// @returns Random value in range [from, to]
	float RandRange(float from, float to);
	/// @param to Random end
	/// @returns Random value in range [0, to]
	float RandRange(float to);
	float RoundTo(float val, int k);
	/// @returns A string like (a, b, c)
	std::string WrappedInBrackets(int count...);
	/// @returns Lines
	template<template<typename> typename T>
	T<std::string> ReadAllFile(std::string name);

	namespace String {
		/// @brief Removes all leading spaces
		/// @param maxLength Max line length in text
		/// @returns Formatted string
		std::string AlignedLeft(std::string s, size_t maxLength);
		/// @brief Adds leading spaces to maxLength
		/// @param maxLength Max line length in text
		/// @returns Formatted string
		std::string AlignedRight(std::string s, size_t maxLength);
		/// @brief Adds spaces to both sides to maxLength
		/// @param maxLength Max line length in text
		/// @returns Formatted string
		std::string AlignedCenter(std::string s, size_t maxLength);

		std::string TrimmedLeft(std::string s);
		std::string TrimmedRight(std::string s);
		std::string Trimmed(std::string s);

		/// @brief Replaces all occurances of 'what' in 's' with 'with'
		/// @param s String to replace in
		/// @param what String to search for
		/// @param with String to replace with
		std::string ReplaceAll(std::string s, std::string what, std::string with);
		std::string ToLower(std::string s);

		/// @param delimiter Separator
		/// @param s String to split
		/// @returns List(?) of substrings
		template <template <typename> typename T>
		T<std::string> Split(std::string s, std::string delimiter);
		// Useless. VS Code labels literally anything as the thing i write the docs for,
		// except the actual function. Fuck it.
		template <template <typename> typename T, typename V>
		std::string Join(T<V> items, std::string glue);
		template<typename T>
		std::string Convert(T value);
		template<typename T>
		T Convert(std::string value);
	}
}