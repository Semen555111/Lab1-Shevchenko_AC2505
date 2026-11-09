#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <map>

using namespace std;

struct PIPE {
	int id;
	string name;
	double length;
	double diameter;
	bool isWorking;
};
struct KS {
	int id;
	string name;
	int works;
	int worksA;
	double efficiency;
};

int next_pipe_id = 1;
int next_ks_id = 1;

int read_int(int low, int high)
{
	int x;
	cin >> x;
	while (cin.fail() || cin.peek() != '\n' || x < low || x > high) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Error, enter an integer from " << low << " to " << high << " -> ";
		cin >> x;
	}
	return x;
}

double read_double(double low, double high)
{
	double x;
	cin >> x;
	while (cin.fail() || cin.peek() != '\n' || x < low || x > high) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Error, enter a number from " << low << " to " << high << " -> ";
		cin >> x;
	}
	return x;
}

void create_pipe(PIPE& p) {
	p.id = next_pipe_id++;
	cout << "Name -> ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, p.name);

	cout << "Length -> ";
	p.length = read_double(0.001, 100000);

	cout << "Diameter -> ";
	p.diameter = read_double(0.001, 100000);

	cout << "Is Working (0 - Not Working, 1 - Working) -> ";
	p.isWorking = read_int(0, 1);
}
void edit_pipe(PIPE& p) {
	cout << "Choose what you want to edit: 1 - Is Working, 0 - Main menu" << "\n";
	int c = read_int(0, 1);
	switch (c) {
	case 1: {
		cout << "Enter new isWorking (0 - Not Working, 1 - Working): ";
		p.isWorking = read_int(0, 1);
		break;
	}
	case 0: {
		break;
	}
	}
}

void create_ks(KS& s) {
	s.id = next_ks_id++;
	cout << "Name -> ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, s.name);

	cout << "Works -> ";
	s.works = read_int(1, 1000);

	cout << "Active Works -> ";
	s.worksA = read_int(0, s.works);

	cout << "Efficiency -> ";
	s.efficiency = read_double(0, 100);
}

void edit_ks(KS& s) {
	cout << "Choose what you want to edit: 1 - Active Works, 0 - Main menu" << "\n";
	int d = read_int(0, 1);
	switch (d) {
	case 1: {
		cout << "Enter new active works (0 to " << s.works << "): ";
		s.worksA = read_int(0, s.works);
		break;
	}
	case 0: {
		break;
	}
	}
}


void show_pipe(const PIPE& p) {
	cout << "PIPE" << "\n";
	if (p.length <= 0)
		cout << "Pipe is not created yet" << "\n";
	else {
		cout << "ID -> " << p.id << "\n";
		cout << "Name -> " << p.name << "\n";
		cout << "Length -> " << p.length << "\n";
		cout << "Diameter -> " << p.diameter << "\n";
		cout << "Is Working(0 - Not Working, 1 - Working) -> " << p.isWorking << "\n";
	}
}
void show_ks(const KS&s){
	cout << "\n" << "KS" << "\n";
	if (s.works <= 0)
		cout << "KS is not created yet" << "\n";
	else {
		cout << "ID -> " << s.id << "\n";
		cout << "Name -> " << s.name << "\n";
		cout << "Works -> " << s.works << "\n";
		cout << "Works Active -> " << s.worksA << "\n";
		cout << "Efficiency -> " << s.efficiency << "\n";
	}
}


void save_pipe(ofstream& fout, const PIPE& p) {
	if (p.length > 0)
		fout << "PIPE" << "\n" << p.name << "\n" << p.length << "\n" << p.diameter << "\n" << p.isWorking << "\n";
}

void save_ks(ofstream& fout, const KS& s) {
	if (s.works > 0)
		fout << "KS" << "\n" << s.name << "\n" << s.works << "\n" << s.worksA << "\n" << s.efficiency << "\n";
}

void load_pipe(ifstream& fin, PIPE& p) {
	PIPE tmp = PIPE();
	getline(fin, tmp.name);
	fin >> tmp.length >> tmp.diameter >> tmp.isWorking;
	if (!fin.fail() && tmp.length > 0 && tmp.diameter > 0) {
		p = tmp;
		cout << "Pipe was loaded" << "\n";
	}
	else
		cout << "Error: wrong pipe data in file" << "\n";
	fin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void load_ks(ifstream& fin, KS& s) {
	KS tmp = KS();
	getline(fin, tmp.name);
	fin >> tmp.works >> tmp.worksA >> tmp.efficiency;
	if (!fin.fail() && tmp.works > 0 && tmp.worksA >= 0
		&& tmp.worksA <= tmp.works && tmp.efficiency >= 0 && tmp.efficiency <= 100) {
		s = tmp;
		cout << "KS was loaded" << "\n";
	}
	else
		cout << "Error: wrong KS data in file" << "\n";
	fin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main()
{
	map<int, PIPE> pipes;     // key = pipe id, value = pipe
	map<int, KS> stations;    // key = KS id, value = KS
	int d;

	do {
		cout << "1. Create pipe" << endl;
		cout << "2. Edit pipe" << endl;
		cout << "3. Create KS" << endl;
		cout << "4. Edit KS" << endl;
		cout << "5. Show all" << endl;
		cout << "6. Save to file (later)" << endl;
		cout << "7. Load from file (later)" << endl;
		cout << "8. Delete pipe" << endl;
		cout << "9. Delete KS" << endl;
		cout << "0. Exit" << endl;

		cout << "Choose an option: ";
		d = read_int(0, 9);

		switch (d) {

		case 1: {
			PIPE p = PIPE();
			create_pipe(p);
			pipes[p.id] = p;
			break;
		}

		case 2: {
			if (pipes.empty()) {
				cout << "No pipes yet" << endl;
				break;
			}
			cout << "Pipe ID -> ";
			int id = read_int(1, 1000000);
			if (pipes.count(id) == 0)
				cout << "Pipe with ID " << id << " not found" << endl;
			else
				edit_pipe(pipes[id]);
			break;
		}

		case 3: {
			KS s = KS();
			create_ks(s);
			stations[s.id] = s;
			break;
		}

		case 4: {
			if (stations.empty()) {
				cout << "No KS yet" << endl;
				break;
			}
			cout << "KS ID -> ";
			int id = read_int(1, 1000000);
			if (stations.count(id) == 0)
				cout << "KS with ID " << id << " not found" << endl;
			else
				edit_ks(stations[id]);
			break;
		}

		case 5: {
			if (pipes.empty())
				cout << "No pipes yet" << endl;
			for (auto& [id, p] : pipes)
				show_pipe(p);

			if (stations.empty())
				cout << "No KS yet" << endl;
			for (auto& [id, s] : stations)
				show_ks(s);
			break;
		}

		case 6:
		case 7: {
			cout << "Files will be done in step 7" << endl;
			break;
		}

		case 8: {
			if (pipes.empty()) {
				cout << "No pipes yet" << endl;
				break;
			}
			cout << "Pipe ID -> ";
			int id = read_int(1, 1000000);
			if (pipes.count(id) == 0)
				cout << "Pipe with ID " << id << " not found" << endl;
			else {
				pipes.erase(id);
				cout << "Pipe " << id << " deleted" << endl;
			}
			break;
		}

		case 9: {
			if (stations.empty()) {
				cout << "No KS yet" << endl;
				break;
			}
			cout << "KS ID -> ";
			int id = read_int(1, 1000000);
			if (stations.count(id) == 0)
				cout << "KS with ID " << id << " not found" << endl;
			else {
				stations.erase(id);
				cout << "KS " << id << " deleted" << endl;
			}
			break;
		}

		case 0: {
			cout << "Exiting..." << endl;
			break;
		}
		}

		if (d != 0) {
			cout << "\nPress Enter to continue...";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get();
		}

	} while (d != 0);

	return 0;
}