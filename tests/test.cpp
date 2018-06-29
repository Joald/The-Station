#include <cassert>
#include <functional>
#include <map>
#include <iostream>
#include "../src/Globals.h"

#define assert_throws(n, e) do { try { n; assert(false); } catch (e& x) {} } while (false)

namespace {

typedef std::function<void()> test_t;

std::map<std::string, test_t> tests;
std::map<std::string, test_t> interactive_tests;

std::string to_lower(const std::string& input) {
    std::string to_return = input;
    for (char c : to_return) {
        if ('A' <= c && c <= 'Z') {
            c -= 'A' - 'a';
        }
    }
    return to_return;
}

} // namespace

void globals_test() {
    using namespace Globals;
    //concat
    assert(concat({"abcd", "e", "fghijkl"}) == "abcdefghijkl");

    //scanData
    assert_throws(scanData("INSTALL", "PLAYER"), std::logic_error);
    assert(scanData("images", "PLAYER").empty());
    assert(scanData("folder_names", "DATA") == "data/");

    //getExtension
    assert(getExtension(IMAGES) == ".png");
    assert_throws(getExtension(INSTALL), std::logic_error);
    assert_throws(getExtension(DATA), std::logic_error);
    assert_throws(getExtension(FOLDER_NAMES), std::logic_error);

    //getFolder
    assert(getFolder(IMAGES) == "img/");
    assert_throws(getFolder("NOT_A_FOLDER"), std::logic_error);
    assert_throws(getFolder(FOLDER_NAMES), std::logic_error);

    std::string current_install = "/home/joald/gamedev/The-Station/";

    //absolutePath - installation dependent
    assert(absolutePath(DATA) == current_install + "data/");
    assert_throws(absolutePath(FOLDER_NAMES), std::logic_error);

    //pathToResource
    assert(pathToResource(IMAGES, "PLAYER") == current_install + "img/PLAYER.png");
    assert_throws(pathToResource(INSTALL, FOLDER_NAMES), std::logic_error);

    std::cout << "Globals test passed!\n";
}

void register_tests() {
    tests["globals"] = globals_test;
}

void print_usage(const std::string& program_name, bool long_list = false) {
    std::cout << "Welcome to The Station's test suite!\n" <<
              "There are " << tests.size() << " tests registered.\n";
    if (long_list) {
        for (auto& i : tests) {
            std::cout << "\t" << i.first << "\n";
        }
    } else {
        std::cout << "For a list of all of them, run \"" << program_name << " --help\".\n";
    }

    std::cout << "For all tests, run \"" << program_name << " --all\".\n";
    std::cout << "For only interactive tests, run \"" << program_name << " --interactive\".\n";
    std::cout << "For only non-interactive tests, run \"" << program_name << " --non-interactive\".\n";
}

int main(int argc, char** argv) {
    register_tests();

    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }
    if (argc == 2) {
        if (to_lower(argv[1]) == "--all" || to_lower(argv[1]) == "--non-interactive") {
            std::cout << "Running all non-interactive tests!\n";
            for (auto& p : tests) {
                p.second();
            }
        }
        if (to_lower(argv[1]) == "--all" || to_lower(argv[1]) == "--interactive") {
            std::cout << "Running all interactive tests!\n";
            for (auto& p : interactive_tests) {
                p.second();
            }
        }
        if (to_lower(argv[1]) == "--help") {
            print_usage(argv[0], true);
        }
        return 0;
    }
    for (int i = 1; i < argc; ++i) {
        auto arg = to_lower(argv[i]);
        auto it = tests.find(arg);
        if (it == tests.end()) {
            std::cout << "Test \"" << arg << "\" not found.\n";
            continue;
        }
        it->second();
    }
}