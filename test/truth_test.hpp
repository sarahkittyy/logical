#pragma once

#include <catch2/catch.hpp>
#include <logical.hpp>

/**
 * @brief compare two truth tables
 *
 * @param a a truth table returned from util::gen_truth_table
 * @param expected the expected truth table
 * @return true if they are equal
 */
bool truth_test(const util::truth_table& a, util::truth_table expected);
