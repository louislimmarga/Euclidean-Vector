#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <cmath>
#include <sstream>

TEST_CASE("basic test") {
	// Please note - this test may not function, it's just here for stubbing purposes
	auto const a1 = comp6771::euclidean_vector(3, 3.0);
	auto const a2 = comp6771::euclidean_vector(3, 3.0);
	auto const a3 = comp6771::euclidean_vector(3, 3.0);

	auto oss = std::ostringstream{};
	oss << (a1 + a2 + a3);
	CHECK(oss.str() == "[9 9 9]");
}

TEST_CASE("constructors") {
	auto const a1 = comp6771::euclidean_vector();
	auto oss1 = std::ostringstream{};
	oss1 << a1;
	CHECK(oss1.str() == "[0]");

	auto const a2 = comp6771::euclidean_vector(2);
	auto oss2 = std::ostringstream{};
	oss2 << a2;
	CHECK(oss2.str() == "[0 0]");

	auto const a3 = comp6771::euclidean_vector(2, 3.4);
	auto oss3 = std::ostringstream{};
	oss3 << a3;
	CHECK(oss3.str() == "[3.4 3.4]");

	std::vector<double> v = {1, 2, 3.3, 4.4};
	auto const a4 = comp6771::euclidean_vector(v.begin(), v.end());
	auto oss4 = std::ostringstream{};
	oss4 << a4;
	CHECK(oss4.str() == "[1 2 3.3 4.4]");

	auto const a5 = comp6771::euclidean_vector{1, 2, 3.3, 4.4};
	auto oss5 = std::ostringstream{};
	oss5 << a5;
	CHECK(oss5.str() == "[1 2 3.3 4.4]");

	auto const a6 = comp6771::euclidean_vector(a5);
	auto oss6 = std::ostringstream{};
	oss6 << a6;
	CHECK(oss6.str() == "[1 2 3.3 4.4]");

	auto const a7 = comp6771::euclidean_vector(std::move(a6));
	auto oss7 = std::ostringstream{};
	oss7 << a7;
	CHECK(oss7.str() == "[1 2 3.3 4.4]");
}

TEST_CASE("Operations") {
	auto const a = comp6771::euclidean_vector{1, 2, 3.3, 4.4};
	auto oss = std::ostringstream{};
	oss << a;
	CHECK(oss.str() == "[1 2 3.3 4.4]");

	auto a1 = a;
	auto oss1 = std::ostringstream{};
	oss1 << a1;
	CHECK(oss.str() == oss1.str());

	auto a2 = a;
	a2[2] = 3.0;
	auto oss2 = std::ostringstream{};
	oss2 << a2 << " " << a2[2];
	CHECK(oss2.str() == "[1 2 3 4.4] 3");

	auto oss3 = std::ostringstream{};
	oss3 << +a;
	CHECK(oss3.str() == "[1 2 3.3 4.4]");

	auto const a4 = -a;
	CHECK(a == -a4);

	a1 += a;
	auto oss4 = std::ostringstream{};
	oss4 << a1;
	CHECK(oss4.str() == "[2 4 6.6 8.8]");

	a1 -= a;
	auto oss5 = std::ostringstream{};
	oss5 << a1;
	CHECK(oss5.str() == "[1 2 3.3 4.4]");

	a1 *= 2;
	auto oss6 = std::ostringstream{};
	oss6 << a1;
	CHECK(oss6.str() == "[2 4 6.6 8.8]");

	a1 /= 2;
	auto oss7 = std::ostringstream{};
	oss7 << a1;
	CHECK(oss7.str() == "[1 2 3.3 4.4]");
}

TEST_CASE("Member functions") {
	auto a = comp6771::euclidean_vector{1, 2, 3.3, 4.4};
	a.at(2) = 5.5;
	auto oss = std::ostringstream{};
	oss << a.at(1) << " " << a << " " << a.dimensions();
	CHECK(oss.str() == "2 [1 2 5.5 4.4] 4");
}

TEST_CASE("Friends") {
	auto a = comp6771::euclidean_vector{1, 2, 3.3, 4.4};
	auto b = comp6771::euclidean_vector{1, 2, 3.3, 4.4};
	CHECK((a == b) == true);
	CHECK((a != b) == false);

	auto c = a + b;
	auto oss1 = std::ostringstream{};
	oss1 << c;
	CHECK(oss1.str() == "[2 4 6.6 8.8]");

	auto d = a - b;
	auto oss2 = std::ostringstream{};
	oss2 << d;
	CHECK(oss2.str() == "[0 0 0 0]");

	auto e1 = a * 2; 
	auto oss3 = std::ostringstream{};
	oss3 << e1;
	CHECK(oss3.str() == "[2 4 6.6 8.8]");
	auto e2 = 2 * a;
	CHECK(e1 == e2);

	auto f = a / 2;
	auto oss4 = std::ostringstream{};
	oss4 << f;
	CHECK(oss4.str() == "[0.5 1 1.65 2.2]");
}

TEST_CASE("Utility") {
	auto a = comp6771::euclidean_vector{1, 2, 3};
	auto norm = sqrt(1 + 4 + 9);
	CHECK(comp6771::euclidean_norm(a) == norm);

	auto b = comp6771::euclidean_vector{(1 / norm), (2 / norm), (3 / norm)};
	CHECK(comp6771::unit(a) == b);

	auto c1 = comp6771::euclidean_vector{1, 2, 3};
	auto c2 = comp6771::euclidean_vector{4, 5, 6};

	CHECK(comp6771::dot(c1, c2) == (1 * 4 + 2 * 5 + 3 * 6));
}

TEST_CASE("Exception") {
	auto a = comp6771::euclidean_vector{1, 2, 3};
	auto b = comp6771::euclidean_vector{1, 2, 3, 4};

	try {
		a += b;
	} catch (comp6771::euclidean_vector_error const& e) {
		CHECK(std::string(e.what()) == "Dimensions of LHS(3) and RHS(4) do not match\n");
	}

	try {
		a -= b;
	} catch (comp6771::euclidean_vector_error const& e) {
		CHECK(std::string(e.what()) == "Dimensions of LHS(3) and RHS(4) do not match\n");
	}

	try {
		a /= 0;
	} catch (comp6771::euclidean_vector_error const& e) {
		CHECK(std::string(e.what()) == "Invalid vector division by 0\n");
	}

	try {
		a.at(-1);
	} catch (comp6771::euclidean_vector_error const& e) {
		CHECK(std::string(e.what()) == "Index -1 is not valid for this euclidean_vector object\n");
	}

	try {
		a.at(90);
	} catch (comp6771::euclidean_vector_error const& e) {
		CHECK(std::string(e.what()) == "Index 90 is not valid for this euclidean_vector object\n");
	}

	try {
		a.at(-1) = 1;
	} catch (comp6771::euclidean_vector_error const& e) {
		CHECK(std::string(e.what()) == "Index -1 is not valid for this euclidean_vector object\n");
	}

	try {
		a.at(90) = 1;
	} catch (comp6771::euclidean_vector_error const& e) {
		CHECK(std::string(e.what()) == "Index 90 is not valid for this euclidean_vector object\n");
	}

	try {
		auto c = a + b;
	} catch (comp6771::euclidean_vector_error const& e) {
		CHECK(std::string(e.what()) == "Dimensions of LHS(3) and RHS(4) do not match\n");
	}

	try {
		auto c = a - b;
	} catch (comp6771::euclidean_vector_error const& e) {
		CHECK(std::string(e.what()) == "Dimensions of LHS(3) and RHS(4) do not match\n");
	}

	try {
		auto c = a / 0;
	} catch (comp6771::euclidean_vector_error const& e) {
		CHECK(std::string(e.what()) == "Invalid vector division by 0\n");
	}

	try {
		comp6771::dot(a, b);
	} catch (comp6771::euclidean_vector_error const& e) {
		CHECK(std::string(e.what()) == "Dimensions of LHS(3) and RHS(4) do not match\n");
	}

	auto c = comp6771::euclidean_vector(0);
	try {
		comp6771::unit(c);
	} catch (comp6771::euclidean_vector_error const& e) {
		CHECK(std::string(e.what())
		      == "euclidean_vector with no dimensions does not have a unit vector");
	}

	auto d = comp6771::euclidean_vector(1);
	try {
		comp6771::unit(d);
	} catch (comp6771::euclidean_vector_error const& e) {
		CHECK(std::string(e.what())
		      == "euclidean_vector with zero euclidean normal does not have a unit vector");
	}
}