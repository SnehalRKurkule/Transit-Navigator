#include "utils.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <limits>

std::string readline_trim() {
    std::string input;
    std::getline(std::cin, input);

    // trim left
    input.erase(input.begin(), std::find_if(input.begin(), input.end(),
                                            [](unsigned char ch) { return !std::isspace(ch); }));
    // trim right
    input.erase(std::find_if(input.rbegin(), input.rend(),
                             [](unsigned char ch) { return !std::isspace(ch); }).base(),
                input.end());

    return input;
}

void pauseScreen() {
    std::cout << "\nPress ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
