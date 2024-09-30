#include <iostream>
#include <string>
using namespace std;

int main() {
menu:
	system("figlet get-Csh");
	cout << "\n[I]nstall CAFFEsh";
	cout << "\n[U]ninstall CAFFEsh";
	cout << "\n[Q]uit";

	cout << "\n\nSelect operation: ";

	string operation; cin >> operation;
	if (operation == "I" || operation == "i") {
		system("clear");
		cout << "[i] Work directory created at ~/csh-temp\n";
		system("mkdir ~/csh-temp");

		cout << "[i] Installing dependancies\n";
		system("sudo pacman -S figlet gcc wget git");

		cout << "[i] Building CAFFEsh\n";
		system("cd ~/csh-temp && wget https://raw.githubusercontent.com/MaxWasTakenYT/CAFFEsh/main/caffesh.cpp && g++ -o caffesh caffesh.cpp -lstdc++");

		cout << "[i] Adding CAFFEsh to PATH (using /usr/bin)\n";
		system("cd ~/csh-temp && chmod +x ./caffesh && sudo mv ./caffesh /usr/bin/caffesh");

		cout << "[i] Cleaning up (deleting work directory)\n";
		system("cd ~/csh-temp && sudo rm ~/csh-temp/caffesh.cpp");
		system("cd ~/ && sudo rmdir ~/csh-temp");

		cout << "[i] Installated successfully\n\n";
		goto menu;
	}
	else if (operation == "U" || operation == "u") {
		system("clear");
		cout << "[i] Removing CAFFEsh from PATH (using /usr/bin)\n";
		system("sudo rm /usr/bin/caffesh");
		cout << "\n [i] Uninstalled successfully\n\n";
		goto menu;
	}
	else if (operation == "Q" || operation == "q") {
		system("clear");
		return 0;
	}
}
