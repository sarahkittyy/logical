#include <catch2/catch.hpp>
#include <logical.hpp>

#include "truth_test.hpp"

using namespace lg;

TEST_CASE("testing schematics and ticking", "[schematic]") {
	schematic ss;

	REQUIRE(ss.count() == 0);

	gates::CONST i1(true);
	gates::CONST i2(false);

	ss.add(&i1);
	ss.add(&i2);

	REQUIRE(ss.count() == 2);

	gates::AND a;
	gates::OR b;

	a.link_in(&i1, 0, 0);
	a.link_in(&i2, 0, 1);

	b.link_in(&i1, 0, 0);
	b.link_in(&i2, 0, 1);

	ss.add(&a);
	ss.add(&b);

	ss.tick();
	REQUIRE(a.result(0) == false);
	REQUIRE(b.result(0) == true);

	i1.toggle();
	ss.tick();
	REQUIRE(a.result(0) == false);
	REQUIRE(b.result(0) == false);

	i1.toggle();
	i2.toggle();
	ss.tick();
	REQUIRE(a.result(0) == true);
	REQUIRE(b.result(0) == true);
}

TEST_CASE("testing schematic factories", "[schematic_factory]") {
	util::schematic_factory fa;

	REQUIRE(fa.schem().count() == 0);

	fa.add<gates::CONST>("a", true);
	fa.add<gates::CONST>("b", false);
	fa.add<gates::CONST>("cin", true);
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

	schematic& ss = fa.schem();

	ss.tick();

	std::shared_ptr<gates::OUT> s = std::dynamic_pointer_cast<gates::OUT>(fa.get("s"));
	std::shared_ptr<gates::OUT> c = std::dynamic_pointer_cast<gates::OUT>(fa.get("c"));

	REQUIRE(s->result(0) == false);
	REQUIRE(c->result(0) == true);
}
