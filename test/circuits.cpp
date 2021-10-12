#include <catch2/catch.hpp>
#include <logical.hpp>

#include <bitset>
#include <sstream>

#include "truth_test.hpp"

util::schematic_factory mk_half_adder() {
	util::schematic_factory ha;

	ha.add_inputs({ "a", "b" });
	ha.add_outputs({ "s", "c" });
	ha.add<gates::AND>("and");
	ha.add<gates::XOR>("xor");

	ha.connect("a", "and", 0, 0);
	ha.connect("b", "and", 0, 1);

	ha.connect("a", "xor", 0, 0);
	ha.connect("b", "xor", 0, 1);

	ha.connect("xor", "s", 0, 0);
	ha.connect("and", "c", 0, 0);

	return ha;
}

util::schematic_factory mk_full_adder() {
	util::schematic_factory fa;

	fa.add_inputs({ "a", "b", "cin" });
	fa.add_outputs({ "s", "c" });
	fa.add<gates::XOR>("xor1");
	fa.add<gates::XOR>("xor2");
	fa.add<gates::AND>("and1");
	fa.add<gates::AND>("and2");
	fa.add<gates::OR>("or");

	fa.connect("a", "xor1", 0, 0);
	fa.connect("a", "and2", 0, 0);
	fa.connect("b", "xor1", 0, 1);
	fa.connect("b", "and2", 0, 1);

	fa.connect("xor1", "xor2", 0, 0);
	fa.connect("cin", "xor2", 0, 1);
	fa.connect("xor1", "and1", 0, 1);
	fa.connect("cin", "and1", 0, 0);

	fa.connect("and1", "or", 0, 0);
	fa.connect("and2", "or", 0, 1);

	fa.connect("or", "c", 0, 0);
	fa.connect("xor2", "s", 0, 0);

	return fa;
}

util::schematic_factory mk_byte_adder() {
	util::schematic_factory ba;

	ba.add_inputs({ "a8", "a7", "a6", "a5", "a4", "a3", "a2", "a1" });
	ba.add_inputs({ "b8", "b7", "b6", "b5", "b4", "b3", "b2", "b1" });
	ba.add_outputs({ "o9", "o8", "o7", "o6", "o5", "o4", "o3", "o2", "o1" });

	ba.add("ha", mk_half_adder());
	ba.add("fa1", mk_full_adder());
	ba.add("fa2", mk_full_adder());
	ba.add("fa3", mk_full_adder());
	ba.add("fa4", mk_full_adder());
	ba.add("fa5", mk_full_adder());
	ba.add("fa6", mk_full_adder());
	ba.add("fa7", mk_full_adder());

	ba.connect("a1", "ha", 0, 0);
	ba.connect("b1", "ha", 0, 1);
	ba.connect("ha", "o1", 0, 0);
	ba.connect("ha", "fa1", 1, 2);

	ba.connect("a2", "fa1", 0, 0);
	ba.connect("b2", "fa1", 0, 1);
	ba.connect("fa1", "o2", 0, 0);
	ba.connect("fa1", "fa2", 1, 2);

	ba.connect("a3", "fa2", 0, 0);
	ba.connect("b3", "fa2", 0, 1);
	ba.connect("fa2", "o3", 0, 0);
	ba.connect("fa2", "fa3", 1, 2);

	ba.connect("a4", "fa3", 0, 0);
	ba.connect("b4", "fa3", 0, 1);
	ba.connect("fa3", "o4", 0, 0);
	ba.connect("fa3", "fa4", 1, 2);

	ba.connect("a5", "fa4", 0, 0);
	ba.connect("b5", "fa4", 0, 1);
	ba.connect("fa4", "o5", 0, 0);
	ba.connect("fa4", "fa5", 1, 2);

	ba.connect("a6", "fa5", 0, 0);
	ba.connect("b6", "fa5", 0, 1);
	ba.connect("fa5", "o6", 0, 0);
	ba.connect("fa5", "fa6", 1, 2);

	ba.connect("a7", "fa6", 0, 0);
	ba.connect("b7", "fa6", 0, 1);
	ba.connect("fa6", "o7", 0, 0);
	ba.connect("fa6", "fa7", 1, 2);

	ba.connect("a8", "fa7", 0, 0);
	ba.connect("b8", "fa7", 0, 1);
	ba.connect("fa7", "o8", 0, 0);
	ba.connect("fa7", "o9", 1, 0);

	return ba;
}

static unsigned short add(unsigned char a, unsigned char b) {
	auto byte_adder = mk_byte_adder();
	circuit byte_adder_c(&byte_adder.schem());

	std::string input;
	{
		std::ostringstream ss;
		std::bitset<8> ba(a), bb(b);
		ss << ba << bb;
		input = ss.str();
	}

	util::truth_table t = util::gen_truth_table(byte_adder_c, input);

	unsigned short out;
	{
		std::string ss;
		for (const bool& b : t.begin()->second) {
			ss.push_back(b ? '1' : '0');
		}
		out = std::stoi(ss, nullptr, 2);
	}

	return out;
}

TEST_CASE("testing multi-gate circuits", "[circuit]") {
	auto a = GENERATE(take(10, random(0, 255)));
	auto b = GENERATE(take(10, random(0, 255)));
	REQUIRE(add(a, b) == (unsigned short)a + (unsigned short)b);
}
