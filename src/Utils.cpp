#include "Utils.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdarg>
#include <fstream>
#include <sstream>
using namespace std;

float Utils::RandRange(float from, float to) {
	return ((float)rand() / RAND_MAX) * (to - from) + from;
}
float Utils::RandRange(float to) {
	return RandRange(0, to);
}

float Utils::RoundTo(float val, int k) {
	val *= pow(10, k);
	val = round(val);
	val /= pow(10, k);

	if (fabs(val) == 0)
		val = 0;

	return val;
}

string Utils::WrappedInBrackets(int count...) {
	va_list args;
	va_start(args, count);

	stringstream ss;
	ss << "(";
	for (int i = 0; i < count; i++) {
		ss << (float)va_arg(args, double);
		if (i != count - 1)
			ss << ", ";
	}
	ss << ")";

	va_end(args);
	return string(istreambuf_iterator<char>(ss), {});
}
list<string> Utils::ReadAllFile(string name) {
	auto result = list<string>();
	ifstream input;
	input.open(name);
	for (string line = ""; getline(input, line);)
		result.push_back(line);
	return result;
}

string Utils::String::AlignedLeft(string s, size_t maxLength) {
	s = Trimmed(s);
	while (s.length() < maxLength)
		s.insert(s.rbegin().base(), ' ');
	return s;
}
string Utils::String::AlignedRight(string s, size_t maxLength) {
	s = Trimmed(s);
	while (s.length() < maxLength)
		s.insert(s.begin(), ' ');
	return s;
}
string Utils::String::AlignedCenter(string s, size_t maxLength) {
	s = Trimmed(s);
	while (s.length() < maxLength) {
		s.insert(s.begin(), ' ');
		s.insert(s.rbegin().base(), ' ');
	}
	if (s.length() > maxLength)
		s.erase(s.rend().base());
	return s;
}

string Utils::String::TrimmedLeft(string s) {
	int spos = 0;
	for (int i = 0; i < s.length() && s[i] == ' '; i++, spos++);
	return s.substr(spos);
}
string Utils::String::TrimmedRight(string s) {
	int spos = 0;
	for (int i = s.length() - 1; i >= 0 && s[i] == ' '; i--, spos++);
	return s.substr(0, s.length() - spos);
}
string Utils::String::Trimmed(string s) {
	return TrimmedRight(TrimmedLeft(s));
}

string Utils::String::ReplaceAll(string s, string what, string with) {
	size_t pos;
	do {
		pos = s.find(what);
		if (pos >= 0)
			s = s.replace(pos, what.length(), with);
	}
	while (pos >= 0);
	return s;
}
list<string> Utils::String::Split(string s, string delimiter) {
	list<string> result = list<string>();
	size_t pos;
	while ((pos = s.find(delimiter)) != string::npos) {
		string found = s.substr(0, pos);
		if (found.length() > 0)
			result.push_back(s.substr(0, pos));
		s = s.substr(pos + 1);
	}
	if (s.length() > 0)
		result.push_back(s);
	return result;
}
string Utils::String::ToLower(string s) {
	transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return tolower(c); });
	return s;
}