#pragma once

#include "assert.hpp"
#include "memory.hpp"
#include "types.hpp"
#include "vector.hpp"

namespace brb
{
	constexpr u64 strlen(const char* const str)
	{
		assert(str != nullptr);

		u64 len{0};
		while (str[len] != '\0')
			++len;
		return len;
	}

	class string
	{
	public:
		string() {};
		string(const char* const str)
		{
			const u64 size = strlen(str);
			_data.resize(size);

			for (u64 i = 0; i < size; ++i)
				_data[i] = str[i];
		}

		string(const char c, const u64 size)
		{
			_data.resize(size);

			fill<char>(_data.data(), size, c);
		}

		constexpr u64 size() const { return _data.size(); }
		constexpr bool empty() const { return _data.empty(); }
		char* data() { return _data.data(); }
		constexpr void clear() { _data.clear(); }
		void push_back(const char c) { _data.push_back(c); }
		void pop_back() { _data.pop_back(); }

		u64 find(const char c);

		char operator[](const u64 index) const
		{
			assert(index < _data.size(), "out-of-bounds string access");
			return _data[index];
		}

		char& operator[](const u64 index)
		{
			assert(index < _data.size(), "out-of-bounds string access");
			return _data[index];
		}

		string& operator+=(const char* const str)
		{
			const u64 len = strlen(str);
			_data.reserve(_data.size() + len);

			for (u64 i = 0; i < len; ++i)
				_data.push_back(str[i]);

			return *this;
		}

		string& operator+=(const string& str)
		{
			_data.reserve(_data.size() + str.size());

			for (u64 i = 0; i < str.size(); ++i)
				_data.push_back(str[i]);

			return *this;
		}

		void operator=(const char* const str)
		{
			const u64 len = strlen(str);
			_data.resize(len);
			memcpy(str, _data.data(), len);
		}

		bool operator==(const string& other) const
		{
			if (_data.size() != other.size())
				return false;

			return _data == other._data;
		}

		bool operator==(const char* const str) const
		{
			const u64 len = strlen(str);
			if (_data.size() != len)
				return false;

			return memcmp(_data.data(), str, len);
		}

		bool operator!=(const string& other) const
		{
			if (_data.size() != other.size())
				return true;

			return _data != other._data;
		}

		static constexpr u64 npos = -1;

	private:
		brb::vector<char> _data;
	};
}
