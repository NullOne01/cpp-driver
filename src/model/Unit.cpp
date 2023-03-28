#include "Unit.h"
#include <cstdio>
#include <iostream>


void Unit::makeWork() {
    {
        std::unique_ptr<FILE, decltype(&pclose)> gccCodeIO(popen("gcc -xc - -o /tmp/mycpu_tmp_bin", "w"), pclose);
        assert(gccCodeIO != nullptr);

        // Write input code to compiler
        auto res = fwrite(pram->text.c_str(), sizeof(char), pram->text.length(), gccCodeIO.get());
        assert(res == pram->text.length());
    }

    short string_length = 255;
    std::string output(string_length, '\0');
    {
        std::unique_ptr<FILE, decltype(&pclose)> gccIO(popen("/tmp/mycpu_tmp_bin", "r"), pclose);
        assert(gccIO != nullptr);

        // Write input text to compiler
        int res = fwrite(lram->text.c_str(), sizeof(char), lram->text.length(), gccIO.get());
        assert(res == lram->text.length());

        // Read output from compiler
        res = fread(&output[0], sizeof(char), (size_t) string_length, gccIO.get());
    }

    lram->text = output;
}

Unit::Unit() : lram(std::make_unique<LRam>()), pram(std::make_unique<PRam>()) {}
