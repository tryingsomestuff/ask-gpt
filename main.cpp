#include <iostream>
#include <fmt/core.h>
#include "openai.hpp"

int main(int argc, char *argv[]) {

    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " \"<explain your goal>\" \"<language>\"" << std::endl;
        std::cout << "        language can be c++17, c++20, python, bash, ..." << std::endl;
        std::cout << "For instance : " << argv[0] << " \"rename all files starting with the letter M with the pattern totoXXXX where XXXX is an incremeting number\" \"bash\"" << std::endl;
        return 1;
    }

    const std::string description = argv[1];
    const std::string user_prompt = fmt::format("Convert this text to a {} snippet, answer must output only the snippet.\nText to convert: ", argv[2]);

    // check if OPENAI_API_KEY is set
    const char *apiKey = std::getenv("OPENAI_API_KEY");
    if (apiKey == nullptr) {
        std::cout << "OPENAI_API_KEY environment variable must be set" << std::endl;
        return 1;
    }

    openai::start(apiKey);

    try {
        const openai::Json completion = openai::completion().create({
                                                                        {"model", "text-davinci-003"},
                                                                        {"prompt", user_prompt + description},
                                                                        {"max_tokens", 600},
                                                                        {"temperature", 0.7}
                                                                    });
        std::cout << "Answer: " << completion["choices"][0]["text"].get<std::string>() << '\n';
    } catch (const std::exception &e) {
        std::cout << "Fail: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
