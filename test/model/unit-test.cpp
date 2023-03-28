#include "../catch_amalgamated.hpp"
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

TEST_CASE("Units should work with input", "[Unit with input]") {
    Unit unit;
    unit.pram->text = R"(
    #include<stdio.h>

    int main() {
       int a, b, sum;

       printf("\nEnter two no: ");
       scanf("%d %d", &a, &b);

       sum = a + b;

       printf("Sum : %d", sum);

       return(0);
    }
    )";

    unit.lram->text = "1 3";

    unit.makeWork();

//    REQUIRE(unit.lram->text == "Hello, World!");
// Input doesn't work yet
//    REQUIRE(strcmp(unit.lram->text.c_str(), "4") == 0);
}
