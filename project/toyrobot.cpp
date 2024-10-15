#include "toyrobot.hpp"

int main(int argc, char * argv[])
{
    //if no input, select test_input.txt in current folder
    auto cwd = std::filesystem::current_path().string();
    string input = cwd + "/test_input.txt";

    if (argc > 1) {
        input = argv[1];
    }

    // command pre processing
    string line;
    fstream file(input);
    vector<string> raw_commands;
    while(getline(file, line)) {
        raw_commands.push_back(line);
    }

    //execute commands from textfile
    Robot g;
    g.processInput(raw_commands);
}
