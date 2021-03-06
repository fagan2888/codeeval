/*
  Copyright (C) 2015 Daniel Rodriguez

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Basic headers for template
#include <fstream>
#include <iostream>
#include <string>

// Extra headers
#include <utility>  // pair/make_pair


std::pair<size_t, size_t>
reverse_and_add(const size_t &input)
{
    // For 100% completeness in any scenario this should be elegantly done with
    // Binary Coded Decimals (the processing overload would be huge)

    // Declaring forward/backwards with "auto" had side effects, probably
    // because backwards was being given a smaller bit size than start
    for(size_t i=0, start=input; ;i++) {
        size_t forward = start;
        size_t backwards = 0;

        while(forward) {
            backwards = 10 * backwards + forward % 10;
            forward /= 10;
        }
        if(start == backwards)
            return std::make_pair(i, backwards);

        start += backwards;
    }
}


struct SeparatorReader: std::ctype<char>
{
    SeparatorReader(const std::string &seps):
        std::ctype<char>(get_table(seps), true) {}

    std::ctype_base::mask const *get_table(const std::string &seps) {
        auto rc = new std::ctype_base::mask[std::ctype<char>::table_size]();
        for(auto &sep: seps)
            rc[static_cast<unsigned char>(sep)] = std::ctype_base::space;
        return &rc[0];
    }
};


int main(int argc, char *argv[]) {
    std::ifstream stream(argv[1]);
    stream.imbue(std::locale(stream.getloc(), new SeparatorReader("\n")));

    for(auto i=0; stream >> i;) {
        auto result = reverse_and_add(i);
        std::cout << result.first << " " << result.second << std::endl;
    }
    return 0;
}
