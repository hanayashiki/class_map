#pragma once
#ifndef __CLASS_MAP__
#define __CLASS_MAP__

#include <cstring>
#include <unordered_map>
#include <typeinfo>

namespace class_map
{
	typedef void* Ptr;

	class indicator
	{
		const Ptr ptr;
	public:
		indicator(const Ptr ptr) : ptr(ptr) {}
		const Ptr GetPtr() const { return ptr; }
	};

	template <class _Tp>
	struct __StrEqual
	{
		bool operator()(const _Tp& __x, const _Tp& __y) const
		{
			return strcmp(__x, __y) == 0;
		}
	};

	struct __StrHash
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
	struct __StrMap
	{
		typedef std::unordered_map<const char*,
			Val,
			__StrHash,
			__StrEqual<const char*>>
			value;
	};

	class __ClassMapWrapper
	{
	public:
		static __StrMap<Ptr>::value * mapper;
	};

	template<class _Type>
	_Type* get()
	{
		return reinterpret_cast<_Type*>(__ClassMapWrapper::mapper->at(typeid(_Type).name()));
	}

	template<class _Type>
	_Type* get(const indicator & indicator)
	{
		return reinterpret_cast<_Type*>(indicator.GetPtr());
	}

	template<class _Type>
	const indicator make_indicator()
	{
		return indicator(__ClassMapWrapper::mapper->at(typeid(_Type).name()));
	}

}

#endif

#define CLASS_MAP(_CLASS, ...) \
	namespace class_map \
	{ \
		const auto __dummy__##_CLASS = [=]() { \
			if (!__ClassMapWrapper::mapper) \
			{ \
				__ClassMapWrapper::mapper = new __StrMap<class_map::Ptr>::value(); \
			} \
			__ClassMapWrapper::mapper->emplace(typeid(_CLASS).name(), new _CLASS(__VA_ARGS__)); \
			return 0; \
		}(); \
	}
