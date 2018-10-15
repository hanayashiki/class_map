#pragma once
#include <iostream>

#include <cstring>
#include <unordered_map>

template <class _Tp>
struct StrEqual
{
	bool operator()(const _Tp& __x, const _Tp& __y) const
	{
		return strcmp(__x, __y) == 0;
	}
};

struct StrHash
{
	size_t operator() (const char * str) const {
		const static size_t base = 19260817;
		size_t ans = 0;

		while (*str != '\0')
		{
			ans = ans * base + *str;
			str++;
		}
		return ans;
	}
};

template <class Val>
struct StrMap
{
	typedef std::unordered_map<const char*,
		Val,
		StrHash,
		StrEqual<const char*>>
		value;
};