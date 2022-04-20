#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <unistd.h>
using namespace std;
int main(){
    
    const size_t MAX_ARGC = 15; // 1 command + # of arguments
    char[32] command;
    char* argv[MAX_ARGC + 1]; // Needs +1 because of the null terminator at the end
    // c_str() converts string to const char*, strdup converts const char* to char*
    argv[0] = strdup(command.c_str());

    // start filling up the arguments after the first command
    size_t arg_i = 1;
    while (cin && arg_i < MAX_ARGC) {
        string arg;
        cin >> arg;
        if (arg.empty()) {
            argv[arg_i] = nullptr;
            break;
        } else {
            argv[arg_i] = strdup(arg.c_str());
        }
        ++arg_i;
    }

    // Run the command with arguments
    if (execvp(command.c_str(), argv) == -1) {
        // Print error if command not found
        cerr << "command '" << command << "' not found\n";
    }
}