//
// Created by Brayhan De Aza on 12/12/25.
//

#include <utils/helpers/Helpers.h>
#include <cmath>
#include "includes/cromio/cromio.h"
#include "libs/catch2/catch_amalgamated.hpp"

using namespace cromio::visitor::nodes;

TEST_CASE("Float evaluation", "[FLOAT_LITERAL]") {
    const auto float_cases = GENERATE(std::make_tuple("1.0", 1.0), std::make_tuple("3.14", 3.14), std::make_tuple("-3.14", -3.14));

    const auto [c, expected_value] = float_cases;
    std::string text = c;

    const auto ast = cromio::Cromio::testAST(text);
    const auto& node = std::any_cast<FloatLiteralNode>(ast.body[0].children.at(0));

    INFO("Float kind");
    REQUIRE(node.kind == Kind::FLOAT_LITERAL);

    const auto parsed = std::stod(node.value);
    const auto rounded = std::round(parsed * 100.0) / 100.0;

    INFO("Float value (rounded to 2 decimals)");
    REQUIRE(rounded == Catch::Approx(expected_value).epsilon(0.01));
}
