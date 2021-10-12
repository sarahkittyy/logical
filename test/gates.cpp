#include <catch2/catch.hpp>
#include <logical.hpp>

#include "truth_test.hpp"

using namespace lg;

TEST_CASE("basic logic gates", "[node]") {
	SECTION("const") {
		gates::CONST o(true);
		REQUIRE(truth_test(util::gen_truth_table(o),
						   { { {}, { 1 } } }));
	}

	SECTION("or") {
		gates::OR o;
		REQUIRE(truth_test(util::gen_truth_table(o),
						   { { { 0, 0 }, { 0 } },
							 { { 0, 1 }, { 1 } },
							 { { 1, 0 }, { 1 } },
							 { { 1, 1 }, { 1 } } }));
	}

	SECTION("nor") {
		gates::NOR o;
		REQUIRE(truth_test(util::gen_truth_table(o),
						   { { { 0, 0 }, { 1 } },
							 { { 0, 1 }, { 0 } },
							 { { 1, 0 }, { 0 } },
							 { { 1, 1 }, { 0 } } }));
	}

	SECTION("not") {
		gates::NOT o;
		REQUIRE(truth_test(util::gen_truth_table(o),
						   { { { 0 }, { 1 } },
							 { { 1 }, { 0 } } }));
	}

	SECTION("and") {
		gates::AND o;
		REQUIRE(truth_test(util::gen_truth_table(o),
						   { { { 0, 0 }, { 0 } },
							 { { 0, 1 }, { 0 } },
							 { { 1, 0 }, { 0 } },
							 { { 1, 1 }, { 1 } } }));
	}

	SECTION("nand") {
		gates::NAND o;
		REQUIRE(truth_test(util::gen_truth_table(o),
						   { { { 0, 0 }, { 1 } },
							 { { 0, 1 }, { 1 } },
							 { { 1, 0 }, { 1 } },
							 { { 1, 1 }, { 0 } } }));
	}

	SECTION("xor") {
		gates::XOR o;
		REQUIRE(truth_test(util::gen_truth_table(o),
						   { { { 0, 0 }, { 0 } },
							 { { 0, 1 }, { 1 } },
							 { { 1, 0 }, { 1 } },
							 { { 1, 1 }, { 0 } } }));
	}

	SECTION("xnor") {
		gates::XNOR o;
		REQUIRE(truth_test(util::gen_truth_table(o),
						   { { { 0, 0 }, { 1 } },
							 { { 0, 1 }, { 0 } },
							 { { 1, 0 }, { 0 } },
							 { { 1, 1 }, { 1 } } }));
	}
}
