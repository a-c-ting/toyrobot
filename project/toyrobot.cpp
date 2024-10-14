#include "toyrobot.hpp"

int main(int argc, char * argv[])
{
    //if no input, select test_input.txt in current folder
    string input = "./test_input.txt";
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

    Robot g;
    g.processInput(raw_commands);

    cout << "Hello, world!" << endl;
}

vector<string> parse_input(fstream) {
    vector<string> result;
    cout << "boom" << endl;
    return result;
}
