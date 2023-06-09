// Following set of scripts were used to load data: https://github.com/Kotbenek/TSP Implemented by KotBenek.
// Source: https://github.com/Kotbenek/TSP
#pragma once
#include <string>

using namespace std;

class StringFunctions
{
public:
	static bool starts_with(string s, string pattern);
	static string trim(string s);
	static string get_substring_after_char(string s, char c);
	static bool to_int(string input, int* output);
	static bool to_int64(string input, int64_t* output);
	static bool to_double(string input, double* output);

private:
	StringFunctions() { }

	template <typename T>
	static bool convert(string input, T* output);
};