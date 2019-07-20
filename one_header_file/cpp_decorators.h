﻿#pragma once
#include <stdexcept>

template<std::size_t ID, typename Func>
class decorator;

template<typename Func>
constexpr auto make_decorator(
	Func * function_address,
	Func decoration)
{
	return decorator<__COUNTER__, Func>(function_address, decoration);
}

template<std::size_t ID, typename RetType, typename... Args>
class decorator<ID, RetType(*)(Args...)>
{
	using FuncType = RetType(*)(Args...);
	using FuncAddressType = RetType(**)(Args...);

public:
	decorator(FuncAddressType function_address, FuncType decoration)
	{
		if (function_address == nullptr)
		{
			throw std::invalid_argument("arg function_address can't be nullptr");
		}

		m_function_address = function_address;
		m_decoration = decoration;

		m_function = *function_address;

		*function_address = &applied_hook;
	}

	static RetType applied_hook(Args... args)
	{
		m_decoration(std::forward<Args>(args)...);

		return m_function(std::forward<Args>(args)...);
	}

	~decorator()
	{
		*m_function_address = m_function;

		m_function_address = nullptr;
	}

private:
	static FuncType * m_function_address;

	static FuncType m_function;

	static FuncType m_decoration;
};

template<std::size_t ID, typename RetType, typename... Args>
typename decorator<ID, RetType(*)(Args...)>::FuncType * decorator<ID, RetType(*)(Args...)>::m_function_address;

template<std::size_t ID, typename RetType, typename... Args>
typename decorator<ID, RetType(*)(Args...)>::FuncType decorator<ID, RetType(*)(Args...)>::m_function;

template<std::size_t ID, typename RetType, typename... Args>
typename decorator<ID, RetType(*)(Args...)>::FuncType decorator<ID, RetType(*)(Args...)>::m_decoration;