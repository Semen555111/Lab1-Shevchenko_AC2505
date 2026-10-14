#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cstdlib>
using namespace std;
struct PIPE {
	string name;
	double length;
	double diameter;
	bool isWorking;
};
struct KS {
	string name;
	int works;
	int worksA;
	double efficiency;

};




void create_pipe(PIPE& p) {
	cout << "Name -> ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, p.name);

	cout << "Length -> ";
	cin >> p.length;
	while (cin.fail() || p.length <= 0 || cin.peek() != '\n') {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cout << "Error, length must be a positive number -> ";
		cin >> p.length;
	}

	cout << "Diameter -> ";
	cin >> p.diameter;
	while (cin.fail() || p.diameter <= 0 || cin.peek() != '\n') {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cout << "Error, diameter must be a positive number -> ";
		cin >> p.diameter;
	}

	int working;
	cout << "Is Working (0 - Not Working, 1 - Working) -> ";
	cin >> working;
	while (cin.fail() || (working != 0 && working != 1)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cout << "Error, enter ONLY 0 or 1 -> ";
		cin >> working;
	}
	p.isWorking = working;
}
void edit_pipe(PIPE& p) {
	cout << "Choose what you want to edit: 1 - Is Working, 0 - Main menu" << "\n";
	int c;
	cin >> c;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cout << "Error, choose the right option" << "\n";
		return;
	}
	switch (c) {
	case 1: {
		cout << "Enter new isWorking (0 - Not Working, 1 - Working): ";
		cin >> p.isWorking;
		while (cin.fail() || (p.isWorking != 0 && p.isWorking != 1)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout << "Error, enter ONLY 0 or 1 -> ";
			cin >> p.isWorking;
		}
		break;
	}
	case 0: {
		break;
	}
	default: {
		cout << "Error, choose the right option" << "\n";
		break;
	}
	}
}

void create_ks(KS& s) {
	cout << "Name -> ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, s.name);

	cout << "Works -> ";
	cin >> s.works;

	while (cin.fail() || s.works <= 0 || cin.peek() != '\n') {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Error, works must be a positive integer -> ";
		cin >> s.works;
	}

	cout << "Active Works -> ";
	cin >> s.worksA;

	while (cin.fail() || s.worksA < 0 || s.worksA > s.works || cin.peek() != '\n') {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Error, active works must be from 0 to "
			 << s.works << " -> ";

		cin >> s.worksA;
	}

	cout << "Efficiency -> ";
	cin >> s.efficiency;

	while (cin.fail() || s.efficiency < 0 || s.efficiency > 100 || cin.peek() != '\n') {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Error, efficiency must be a number from 0 to 100 -> ";
		cin >> s.efficiency;
	}
}

void edit_ks(KS& s) {
	cout << "Choose what you want to edit: 1 - Active Works, 0 - Main menu" << "\n";
	int d;
	cin >> d;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cout << "Error, choose the right option" << "\n";
		return;
	}
	switch (d) {
	case 1: {
		cout << "Enter new active works (0 to " << s.works << "): ";
		cin >> s.worksA;
		while (cin.fail() || s.worksA < 0 || s.worksA > s.works) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout << "Error, active works must be from 0 to " << s.works << " -> ";
			cin >> s.worksA;
		}
		break;
	}
	case 0: {
		break;
	}
	default: {
		cout << "Error, choose the right option" << "\n";
		break;
	}
	}
}


void show_pipe(const PIPE& p) {
	cout << "PIPE" << "\n";
	if (p.length <= 0)
		cout << "Pipe is not created yet" << "\n";
	else {
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
	PIPE p = PIPE();
    KS s = KS();
    int d;

do {
    cout << "1. Create pipe" << endl;
    cout << "2. Edit pipe" << endl;
    cout << "3. Create KS" << endl;
    cout << "4. Edit KS" << endl;
    cout << "5. Show all" << endl;
    cout << "6. Save to file" << endl;
    cout << "7. Load from file" << endl;
    cout << "0. Exit" << endl;

    cout << "Choose an option: ";
	cin >> d;

	while (cin.fail() || d < 0 || d > 7) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Error, choose a number from 0 to 7 -> ";
    cin >> d;
}

        switch (d) {

        case 1: {
            create_pipe(p);
            break;

        }

        case 2: {
            if (p.length <= 0)
                cout << "Pipe is not created yet" << endl;
            else
                edit_pipe(p);
            break;
        }

        case 3: {
            create_ks(s);
            break;
        }

        case 4: {
            if (s.works <= 0)
                cout << "KS is not created yet" << endl;
            else
                edit_ks(s);
            break;
        }

        case 5: {
            show_pipe(p);
            show_ks(s);
            break;
        }

        case 6: {

            if (p.length <= 0 && s.works <= 0) {
                cout << "Nothing to save, create a pipe or KS" << endl;
                break;
            }
            ofstream fout("data.txt");
            if (!fout) {
                cout << "Error opening data.txt for writing" << endl;
                break;
            }
            save_pipe(fout, p);
            save_ks(fout, s);
            fout.close();
            cout << "Data was saved to data.txt" << endl;
            break;
        }

        case 7: {

            ifstream fin("data.txt");
            if (!fin) {
                cout << "Error opening data.txt for reading" << endl;
                break;
            }
            string mark;
            getline(fin, mark);
            if (mark != "PIPE" && mark != "KS")
                cout << "No mark PIPE or KS in data.txt" << endl;
				break;
            if (mark == "PIPE") {
                load_pipe(fin, p);
                getline(fin, mark);
            }
            if (mark == "KS")
                load_ks(fin, s);
            fin.close();
            break;
        }

        case 0: {
            cout << "Exiting..." << endl;
            break;
        }

        default: {
            cout << "Error, choose the right option" << endl;
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