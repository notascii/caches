#include <iostream>
#include <sstream>
#include <algorithm> // std::transform
#include "lru_cache.hpp"


int main(int argc, const char *argv[]) {
    // lru_cache command line arguments
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <cache_capacity>" << std::endl;
        return EXIT_FAILURE;
    }

    // Parse capacity from command line
    int capacity = std::stoi(argv[1]);
    if (capacity < 2) {
        std::cerr << "Error: Capacity must be at least 2" << std::endl;
        return EXIT_FAILURE;
    }

    LRUCache lru_cache(capacity);

    // Main loop
    while (true) {
        std::string input;
        std::cout << "\033[1mLRU(\033[0m" << capacity << "\033[1m)> \033[0m"; // Prompt with capacity
        std::getline(std::cin, input);

        std::istringstream iss(input);

        // lowercase the input command
        std::string command;
        iss >> command;
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);

        if (command == "quit" || command == "q") {
            break;
        }
        else if (command == "list" || command == "l") {
            lru_cache.print();
        }
        else {
            // Parse the input
            std::string key_str;
            std::string value_str;

            if (command == "get" || command == "g") {
                if (iss >> key_str) {
                    try {
                        int key = std::stoi(key_str);
                        int result = lru_cache.get(key);
                        if (result != -1) {
                            std::cout << result << std::endl;
                        } else {
                            std::cerr << "Error: Key not found" << std::endl;
                        }
                    } catch (const std::invalid_argument&) {
                        std::cerr << "Error: Invalid key format" << std::endl;
                    }
                } else {
                    std::cerr << "Error: Missing key" << std::endl;
                }
            }
            else if (command == "put" || command == "p") {
                if (iss >> key_str >> value_str) {
                    try {
                        int key = std::stoi(key_str);
                        int value = std::stoi(value_str);
                        lru_cache.put(key, value);
                        std::cout << "OK" << std::endl;
                    } catch (const std::invalid_argument&) {
                        std::cerr << "Error: Invalid number format" << std::endl;
                    }
                } else {
                    std::cerr << "Error: Missing key or value" << std::endl;
                }
            }
            else if (!command.empty()) {
                std::cerr << "Error: Unrecognized command" << std::endl;
            }
        }
    }

    return EXIT_SUCCESS;
}
