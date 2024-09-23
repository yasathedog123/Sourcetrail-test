// Copyright 2015 Peter Most, PERA Software Solutions GmbH
//
// This file is part of the CppAidKit library.
//
// CppAidKit is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CppAidKit is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with CppAidKit. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <algorithm>
#include <functional>
#include <string_view>
#include <vector>

namespace aidkit {

template<typename T, typename Char = char, typename Int = int>
	class enum_class {
		public:
			enum_class(const enum_class &other) = default;
			enum_class &operator = (const enum_class &other) = default;

			Int value() const noexcept
			{
				return value_;
			}

			std::basic_string_view<Char> name() const noexcept
			{
				return name_;
			}

			// We only define the equal and less-then operator because if the other ones are needed then do:
			// #include <utility>
			// using namespace rel_ops;

			bool operator == (const enum_class &other) const noexcept
			{
				return value() == other.value();
			}

			bool operator < (const enum_class other) const noexcept
			{
				return value() < other.value();
			}

			// Some find functions for searching via a name or a value:

			static std::vector<T> find(std::basic_string_view<Char> name)
			{
				std::vector<T> foundEnums;

				for_each([&](const T &other)
				{
					if (name == other.name())
						foundEnums.push_back(other);
				});
				return foundEnums;
			}

			static std::vector<T> find(Int value)
			{
				std::vector<T> foundEnums;

				for_each([&](const T &other)
				{
					if (value == other.value())
						foundEnums.push_back(other);
				});
				return foundEnums;
			}

			// Allow iterating through all enum values:

			static void for_each(const std::function<void (const T &)> &function)
			{
				std::for_each(get_container().cbegin(), get_container().cend(), [&](const T *t)
				{
					function(*t);
				});
			}

		protected:
			enum_class()
				: enum_class(get_next_value(), EMPTY_NAME)
			{
			}

			enum_class(Int value)
				: enum_class(value, EMPTY_NAME)
			{
			}

			template <std::size_t SIZE>
				constexpr enum_class(const Char (&name)[SIZE])
					: enum_class(get_next_value(), name)
				{
				}

			template <std::size_t SIZE>
				enum_class(Int value, const Char (&name)[SIZE])
					: value_(value), name_(name, SIZE - 1)
				{
					get_container().push_back(static_cast<const T *>(this));
				}

		private:
			static const Char EMPTY_NAME[];

			static Int get_next_value()
			{
				return get_container().empty() ? 0 : get_container().back()->value_ + 1;
			}

			static std::vector<const T *> &get_container()
			{
				// Use a function level static container so we don't run into the "static initialization order fiasco"
				static std::vector<const T *> s_values;

				return s_values;
			}

			Int value_;
			std::basic_string_view<Char> name_;
	};

template <typename T, typename Char, typename Int>
	const Char enum_class<T, Char, Int>::EMPTY_NAME[] = { 0 };

}
