#pragma once

#include <iostream>
#include <map>
#include <vector>

#include <node.hpp>

namespace util {

/// a table mapping all possible inputs to a node, to each output
typedef std::map<std::vector<bool>, std::vector<bool>> truth_table;

/**
 * @brief generate a truth table for the given node
 *
 * @param n the node
 * @return the truth table corresponding to that node
 */
truth_table gen_truth_table(const node& n);

/**
 * @brief generate a truth table for the given node
 *
 * @param n the node
 * @param input the specific input to test
 * @return the truth table
 */
truth_table gen_truth_table(const node& n, std::vector<bool> input);

/**
 * @brief generate a truth table for the given node
 *
 * @param n the node
 * @param input the specific input to test
 * @return the truth table
 */
truth_table gen_truth_table(const node& n, std::string input);

}

/**
 * @brief outputs a truth table in a human-readable format
 */
std::ostream& operator<<(std::ostream& os, const util::truth_table& table);
