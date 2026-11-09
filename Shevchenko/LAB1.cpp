#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <map>
#include <vector>

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
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return x;
}

string read_line()
{
	string text;
	getline(cin >> ws, text);
	return text;
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
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return x;
}

void create_pipe(PIPE& p) {
	p.id = next_pipe_id++;
	cout << "Name -> ";
	p.name = read_line();

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
	s.name = read_line();

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

vector<int> find_pipes_by_name(const map<int, PIPE>& pipes, const string& part) {
	vector<int> found;
	for (auto& [id, p] : pipes) {
		if (p.name.find(part) != string::npos)
			found.push_back(id);
	}
	return found;
}

vector<int> find_pipes_by_status(const map<int, PIPE>& pipes, bool working) {
	vector<int> found;
	for (auto& [id, p] : pipes) {
		if (p.isWorking == working)
			found.push_back(id);
	}
	return found;
}

vector<int> find_ks_by_name(const map<int, KS>& stations, const string& part) {
	vector<int> found;
	for (auto& [id, s] : stations) {
		if (s.name.find(part) != string::npos)
			found.push_back(id);
	}
	return found;
}

double idle_percent(const KS& s) {
	return (s.works - s.worksA) * 100.0 / s.works;
}

vector<int> find_ks_by_idle(const map<int, KS>& stations, double min_percent) {
	vector<int> found;
	for (auto& [id, s] : stations) {
		if (idle_percent(s) >= min_percent)
			found.push_back(id);
	}
	return found;
}

void show_found_pipes(const map<int, PIPE>& pipes, const vector<int>& ids) {
	cout << "Found: " << ids.size() << endl;
	for (int id : ids)
		show_pipe(pipes.at(id));
}

void show_found_ks(const map<int, KS>& stations, const vector<int>& ids) {
	cout << "Found: " << ids.size() << endl;
	for (int id : ids) {
		show_ks(stations.at(id));
		cout << "Idle works -> " << idle_percent(stations.at(id)) << "%" << endl;
	}
}

vector<int> search_pipes(const map<int, PIPE>& pipes) {
	cout << "Search by: 1 - name, 2 - status -> ";
	int filter = read_int(1, 2);
	if (filter == 1) {
		cout << "Name (or part of it) -> ";
		string part = read_line();
		return find_pipes_by_name(pipes, part);
	}
	cout << "Status (0 - Not Working, 1 - Working) -> ";
	bool working = read_int(0, 1);
	return find_pipes_by_status(pipes, working);
}

vector<int> search_ks(const map<int, KS>& stations) {
	cout << "Search by: 1 - name, 2 - idle works percent -> ";
	int filter = read_int(1, 2);
	if (filter == 1) {
		cout << "Name (or part of it) -> ";
		string part = read_line();
		return find_ks_by_name(stations, part);
	}
	cout << "Minimum idle works percent (0 to 100) -> ";
	double percent = read_double(0, 100);
	return find_ks_by_idle(stations, percent);
}

bool contains(const vector<int>& ids, int id) {
	for (int x : ids) {
		if (x == id)
			return true;
	}
	return false;
}

vector<int> pick_ids(const vector<int>& found) {
	vector<int> chosen;
	while (true) {
		cout << "ID from the found list (0 - finish) -> ";
		int id = read_int(0, 1000000);
		if (id == 0)
			break;
		if (!contains(found, id))
			cout << "ID " << id << " is not in the found list" << endl;
		else if (contains(chosen, id))
			cout << "ID " << id << " is already chosen" << endl;
		else
			chosen.push_back(id);
	}
	return chosen;
}

void batch_edit_pipes(map<int, PIPE>& pipes) {
	vector<int> found = search_pipes(pipes);
	show_found_pipes(pipes, found);
	if (found.empty())
		return;

	cout << "Apply to: 1 - all found, 2 - chosen IDs -> ";
	vector<int> targets;
	if (read_int(1, 2) == 1)
		targets = found;
	else
		targets = pick_ids(found);

	if (targets.empty()) {
		cout << "Nothing chosen" << endl;
		return;
	}

	cout << "Action: 1 - set Working, 2 - set Not Working, 3 - delete -> ";
	int action = read_int(1, 3);
	for (int id : targets) {
		if (action == 3)
			pipes.erase(id);
		else
			pipes[id].isWorking = (action == 1);
	}
	cout << "Done for " << targets.size() << " pipe(s)" << endl;
}

int main()
{
	map<int, PIPE> pipes;
	map<int, KS> stations;
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
		cout << "10. Search pipes" << endl;
		cout << "11. Search KS" << endl;
		cout << "12. Batch edit pipes" << endl;
		cout << "0. Exit" << endl;

		cout << "Choose an option: ";
		d = read_int(0, 12);

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

		case 10: {
			if (pipes.empty()) {
				cout << "No pipes yet" << endl;
				break;
			}
			vector<int> found = search_pipes(pipes);
			show_found_pipes(pipes, found);
			break;
		}

		case 11: {
			if (stations.empty()) {
				cout << "No KS yet" << endl;
				break;
			}
			vector<int> found = search_ks(stations);
			show_found_ks(stations, found);
			break;
		}

		case 12: {
			if (pipes.empty()) {
				cout << "No pipes yet" << endl;
				break;
			}
			batch_edit_pipes(pipes);
			break;
		}

		case 0: {
			cout << "Exiting..." << endl;
			break;
		}
		}

		if (d != 0) {
			cout << "\nPress Enter to continue...";
			cin.get();
		}

	} while (d != 0);

	return 0;
}