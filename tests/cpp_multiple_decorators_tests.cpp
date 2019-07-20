#include "cpp_decorators.h"
#include "catch.hpp"

// This fixture is around tests that verify the multiple decorators live in harmony - without disturbing each other
class TwoDecoratorsTestFixture
{

private:
	static std::size_t first_decorator_call_amount;
	static std::size_t second_decorator_call_amount;

public:
	TwoDecoratorsTestFixture()
	{
		first_decorator_call_amount = 0;
		second_decorator_call_amount = 0;
	}

	~TwoDecoratorsTestFixture()
	{
		first_decorator_call_amount = 0;
		second_decorator_call_amount = 0;
	}

	static void set_first_decorator_was_called()
	{
		++first_decorator_call_amount;
	}

	static void set_second_decorator_was_called()
	{
		++second_decorator_call_amount;
	}

protected:
	static std::size_t get_first_decorator_call_amount()
	{
		return first_decorator_call_amount;
	}

	static std::size_t get_second_decorator_call_amount()
	{
		return second_decorator_call_amount;
	}
};

std::size_t TwoDecoratorsTestFixture::first_decorator_call_amount;
std::size_t TwoDecoratorsTestFixture::second_decorator_call_amount;

static void func()
{
	return;
}

static void func2()
{
	return;
}

static void first_decorator_func()
{
	TwoDecoratorsTestFixture::set_first_decorator_was_called();
}

static void second_decorator_func()
{
	TwoDecoratorsTestFixture::set_second_decorator_was_called();
}

TEST_CASE_METHOD(TwoDecoratorsTestFixture,
	"make 2 decorations for 2 different functions - assert decorators are from different types so they won't interfere each other")
{
	auto func_holder = &func;

	auto func2_holder = &func2;

	const auto first_decorator = MAKE_DECORATOR(func_holder, first_decorator_func);

	const auto second_decorator = MAKE_DECORATOR(func2_holder, second_decorator_func);

	REQUIRE(std::is_same_v<decltype(first_decorator), decltype(second_decorator)> == false);

}


// These tests will cause an access violation - for now ;)

TEST_CASE_METHOD(TwoDecoratorsTestFixture,
	"make 2 decorations for 2 different functions - assert both decoration functions are called once")
{
	auto func_holder = &func;

	auto func2_holder = &func2;

	const auto first_decorator = MAKE_DECORATOR(func_holder, first_decorator_func);

	const auto second_decorator = MAKE_DECORATOR(func2_holder, second_decorator_func);

	func_holder();

	func2_holder();

	REQUIRE(get_first_decorator_call_amount() == 1);

	REQUIRE(get_second_decorator_call_amount() == 1);
}

TEST_CASE_METHOD(TwoDecoratorsTestFixture,
	"make 2 decorations for same function - assert both decoration functions are called once")
{
	auto func_holder = &func;

	const auto first_decorator = MAKE_DECORATOR(func_holder, first_decorator_func);

	const auto second_decorator = MAKE_DECORATOR(func_holder, second_decorator_func);

	func_holder();

	REQUIRE(get_first_decorator_call_amount() == 1);

	REQUIRE(get_second_decorator_call_amount() == 1);
}