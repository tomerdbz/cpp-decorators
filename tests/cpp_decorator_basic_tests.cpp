#include "cpp_decorators.h"
#include "catch.hpp"

// This fixture is around tests that verify the decorator function was called when you expect it (and vice versa)
class DecoratorWasCalledTestFixture 
{

private:
	static bool decorator_called;

public:
	DecoratorWasCalledTestFixture()
	{
		decorator_called = false;
	}

	~DecoratorWasCalledTestFixture()
	{
		decorator_called = false;
	}

	static void set_decorator_was_called()
	{
		decorator_called = true;
	}

protected:
	static bool was_decorator_called() 
	{
		return decorator_called;
	}
};

bool DecoratorWasCalledTestFixture::decorator_called = false;


static void func()
{
	return;
}

static void decorator_func()
{
	DecoratorWasCalledTestFixture::set_decorator_was_called();
}


TEST_CASE_METHOD(DecoratorWasCalledTestFixture, "make decoration - decoration function was called")
{
	auto func_holder = &func;

	const auto decorator = make_decorator(&func_holder, &decorator_func);

	func_holder();

	REQUIRE(was_decorator_called());
}

TEST_CASE_METHOD(DecoratorWasCalledTestFixture,
	"make decoration for function, destroy it and call the function - decoration was not called")
{
	auto func_holder = &func;

	{
		const auto decorator = make_decorator(&func_holder, &decorator_func);
	}

	func_holder();

	REQUIRE(was_decorator_called() == false);
}

void func_with_args_different_qualifiers(int value, const char & lvalue_ref, double && rvalue_ref)
{
	return;
}

void decorator_func_with_args_different_qualifiers(int value, const char & lvalue_ref, double && rvalue_ref)
{
	DecoratorWasCalledTestFixture::set_decorator_was_called();
}

TEST_CASE_METHOD(DecoratorWasCalledTestFixture,
	"make decoration for function with different qualifiers - decoration function was called")
{
	auto func_holder = &func_with_args_different_qualifiers;

	const auto decorator = make_decorator(&func_holder, &decorator_func_with_args_different_qualifiers);

	char to_be_lvalue_ref = 'a';

	double to_be_rvalue_ref = 1.2;

	func_holder(20, to_be_lvalue_ref, std::move(to_be_rvalue_ref));

	REQUIRE(was_decorator_called());
}

void func_with_arg_lvalue_qualifier(char & lvalue_ref)
{
	return;
}

void decorator_func_with_arg_lvalue_qualifier(char & lvalue_ref)
{
	lvalue_ref = lvalue_ref + 1;

	DecoratorWasCalledTestFixture::set_decorator_was_called();
}

TEST_CASE_METHOD(DecoratorWasCalledTestFixture,
	"make decoration for function with an arg with lvalue qualifier - prove decoration can change its value")
{
	auto func_holder = &func_with_arg_lvalue_qualifier;

	const auto decorator = make_decorator(&func_holder, &decorator_func_with_arg_lvalue_qualifier);

	char to_be_lvalue_ref = 'a';
	char value_before_func_call = to_be_lvalue_ref;

	func_holder(to_be_lvalue_ref);

	REQUIRE(value_before_func_call + 1 == to_be_lvalue_ref);
}
