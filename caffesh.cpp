#include <iostream>
#include <string>
#include <cstdlib>
#include <array>
#include <memory>
#include <unistd.h>
#include <limits.h>
using namespace std;

/* TODO List;
> Add settings interface with a TUI - Unsure
*/

string getUser() {
    array<char, 128> buffer;
    string user = "";
    shared_ptr<FILE> pipe(popen("echo $USER", "r"), pclose);
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        user += buffer.data();
    }
    if (!user.empty() && user.back() == '\n') {
        user.pop_back();
    }
    return user;
}

string getDir() {
    array<char, 128> buffer;
    string cdir = "";
    shared_ptr<FILE> pipe(popen("echo $PWD", "r"), pclose);
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        cdir += buffer.data();
    }
    if (!cdir.empty() && cdir.back() == '\n') {
        cdir.pop_back();
    }
    return cdir;
}

int main() {
    system("clear");
    system("figlet CAFFE sh");
    cout << "\nRun \"c.help\" to list available commands\n\n";

prompt:
    string user = getUser();
    string cdir = getDir();
    string promptRes;
    // Checks if user is in /home (for aesthetics only)
    if (cdir.find("/home/") != string::npos) {
        cout << user << " at " << "~" << " :: ";
        getline(cin, promptRes);
    }
    else {
        cout << user << " at " << cdir << " :: ";
        getline(cin, promptRes);
    }


promptHandling:
    // Note: You are NOT ready for what you are going to see (a.k.a. the worst way to handle a prompt)
    if (promptRes == "c.help") {
        cout << "List of available commands:\n\n";

        cout << "c.help : Lists available commands\n";
        cout << "c.settings / c.opts : *not implemented yet* Opens CAFFEsh's settings menu\n";
        cout << "c.quit / c.exit / c.qx : Quits CAFFEsh\n";
        cout << "lsd : Basically `ls -lah` :)\n";

        cout << "Note: CAFFEsh still does NOT support error handling\n";
        goto prompt;
    }
    else if (promptRes == "lsd") {
        string lswdir = "ls -lah " + cdir;
        system(lswdir.c_str());
        goto prompt;
    }

    else if (promptRes == "exit") {
        cout << "[!] Use \'c.quit\', \'c.exit\' or \'c.qx\' to quit CAFFEsh\n";
        goto prompt;
    }
    else if (promptRes == "c.quit" || promptRes == "c.exit" || promptRes == "c.qx") {
        cout << "Thanks for using CAFFEsh!\n";
        return 0;
    }
    else if (promptRes.substr(0, 3) == "cd ") {
        string newDir = promptRes.substr(3);
        if (chdir(newDir.c_str()) != 0) {
            perror("cd failed");
        }
        goto prompt;
    }
    else {
        string promptElseRes = promptRes;
        system(promptElseRes.c_str());
        goto prompt;
    }
}
