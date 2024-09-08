#pragma once

#include "assert.hpp"
#include "memory.hpp"
#include "types.hpp"
#include "vector.hpp"

namespace brb
{
	constexpr mu64 strlen(const char* const str)
	{
		assert(str != nullptr);

		mu64 len{0};
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
			u64 size = strlen(str);
			_data.resize(size);

			for (mu64 i = 0; i < size; ++i)
				_data[i] = str[i];
		}

		string(const char c, u64 size)
		{
			_data.resize(size);

			fill<char>(_data.data(), size, c);
		}

		constexpr mu64 size() const { return _data.size(); }
		constexpr bool empty() const { return _data.empty(); }
		char* data() { return _data.data(); }
		constexpr void clear() { _data.clear(); }
		void push_back(const char c) { _data.push_back(c); }
		void pop_back() { _data.pop_back(); }

		char operator[](u64 index) const
		{
			assert(index < _data.size(), "out-of-bounds string access");
			return _data[index];
		}

		char& operator[](u64 index)
		{
			assert(index < _data.size(), "out-of-bounds string access");
			return _data[index];
		}

		string& operator+=(const char* const str)
		{
			u64 len = strlen(str);
			_data.reserve(_data.size() + len);

			for (mu64 i = 0; i < len; ++i)
				_data.push_back(str[i]);

			return *this;
		}

		void operator=(const char* const str)
		{
			u64 len = strlen(str);
			_data.resize(len);
			memcpy(str, _data.data(), len);
		}

		bool operator==(const string& other) const
		{
			if (_data.size() != other.size())
				return false;

			return _data == other._data;
		}

		bool operator!=(const string& other) const
		{
			if (_data.size() != other.size())
				return true;

			return _data != other._data;
		}

	private:
		brb::vector<char> _data;
	};
}
