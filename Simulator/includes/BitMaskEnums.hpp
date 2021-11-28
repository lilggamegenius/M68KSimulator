//
// Created by ggonz on 11/22/2021.
//

#pragma once

namespace M68K::Opcodes{

	template<typename Enum>
	struct EnableBitMaskOperators {
		static const bool enable = false;
	};

	template<typename Enum>
	typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
	operator|(Enum lhs, Enum rhs) {
		using underlying = typename std::underlying_type<Enum>::type;
		return static_cast<Enum> (
				static_cast<underlying>(lhs) |
				static_cast<underlying>(rhs)
		);
	}

	template<typename Enum>
	typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
	operator&(Enum lhs, Enum rhs) {
		using underlying = typename std::underlying_type<Enum>::type;
		return static_cast<Enum> (
				static_cast<underlying>(lhs) &
				static_cast<underlying>(rhs)
		);
	}

	template<typename Enum>
	typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
	operator^(Enum lhs, Enum rhs) {
		using underlying = typename std::underlying_type<Enum>::type;
		return static_cast<Enum> (
				static_cast<underlying>(lhs) ^
				static_cast<underlying>(rhs)
		);
	}

	template<typename Enum>
	typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
	operator~(Enum rhs) {
		using underlying = typename std::underlying_type<Enum>::type;
		return static_cast<Enum> (
				~static_cast<underlying>(rhs)
		);
	}

	template<typename Enum>
	typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type &
	operator|=(Enum &lhs, Enum rhs) {
		using underlying = typename std::underlying_type<Enum>::type;
		lhs = static_cast<Enum> (
				static_cast<underlying>(lhs) |
				static_cast<underlying>(rhs)
		);

		return lhs;
	}

	template<typename Enum>
	typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type &
	operator&=(Enum &lhs, Enum rhs) {
		using underlying = typename std::underlying_type<Enum>::type;
		lhs = static_cast<Enum> (
				static_cast<underlying>(lhs) &
				static_cast<underlying>(rhs)
		);

		return lhs;
	}

	template<typename Enum>
	typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type &
	operator^=(Enum &lhs, Enum rhs) {
		using underlying = typename std::underlying_type<Enum>::type;
		lhs = static_cast<Enum> (
				static_cast<underlying>(lhs) ^
				static_cast<underlying>(rhs)
		);

		return lhs;
	}

	constexpr int bit(int index) {
		if (index == 0) return 0;
		return 1 << (index - 1);
	}

#define ENABLE_BITMASK_OPERATORS(x)  \
template<>                           \
struct EnableBitMaskOperators<x>     \
{                                    \
    static const bool enable = true; \
};
}