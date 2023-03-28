#include "../catch_amalgamated.hpp"
#include <iostream>
#include "model/Unit.h"

TEST_CASE("Units should work", "[Unit]") {
    Unit unit;
    unit.pram->text = R"(
    #include <stdio.h>
    int main() {
        // printf() displays the string inside quotation
        printf("Hello, World!");
        return 0;
    }
    )";

    unit.makeWork();

//    REQUIRE(unit.lram->text == "Hello, World!");
    REQUIRE(strcmp(unit.lram->text.c_str(), "Hello, World!") == 0);
}
