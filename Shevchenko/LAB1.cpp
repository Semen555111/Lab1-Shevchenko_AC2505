#include <iostream>
#include <string>
#include <fstream>
#include <limits>   // numeric_limits
#include <cstdlib>  // system
using namespace std;

const char* FILE_NAME = "data.txt";   

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


// printf '\033[3J' дополнительно стирает историю прокрутки,
// чтобы при прокрутке вверх не было видно старого текста
void clear_screen() {

	system("clear && printf '\\033[3J'");
}

void create_pipe(PIPE& p) {
	cout << "Name -> ";
	cin.ignore();
	getline(cin, p.name);

	cout << "Length -> ";
	cin >> p.length;
	while (cin.fail() || p.length <= 0) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cout << "Error, length must be a positive number -> ";
		cin >> p.length;
	}

	cout << "Diameter -> ";
	cin >> p.diameter;
	while (cin.fail() || p.diameter <= 0) {
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
		int working;
		cout << "Enter new isWorking (0 - Not Working, 1 - Working): ";
		cin >> working;
		while (cin.fail() || (working != 0 && working != 1)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout << "Error, enter ONLY 0 or 1 -> ";
			cin >> working;
		}
		p.isWorking = working;
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
void show_pipe(const PIPE&p) {
	cout << "Name -> " << p.name << "\n";
	cout << "Length -> " << p.length << "\n";
	cout << "Diameter -> " << p.diameter << "\n";
	cout << "Is Working(0 - Not Working, 1 - Working) -> " << p.isWorking << "\n";

}

void create_ks(KS& s) {
	cout << "Name -> ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, s.name);

	cout << "Works -> ";
	cin >> s.works;

	while (cin.fail() || s.works <= 0) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Error, works must be a positive integer -> ";
		cin >> s.works;
	}

	cout << "Active Works -> ";
	cin >> s.worksA;

	while (cin.fail() || s.worksA < 0 || s.worksA > s.works) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Error, active works must be from 0 to "
			 << s.works << " -> ";

		cin >> s.worksA;
	}

	cout << "Efficiency -> ";
	cin >> s.efficiency;

	while (cin.fail() || s.efficiency < 0 || s.efficiency > 100) {
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
void show_ks(const KS&s) {
	cout << "Name -> " << s.name << "\n";
	cout << "Works -> " << s.works << "\n";
	cout << "Works Active -> " << s.worksA << "\n";
	cout << "Efficiency -> " << s.efficiency << "\n";
}

// Запись трубы в уже открытый файл: метка PIPE, затем данные по строкам
void save_pipe(ofstream& fout, const PIPE& p) {
	fout << "PIPE" << "\n" << p.name << "\n" << p.length << "\n" << p.diameter << "\n" << p.isWorking << "\n";
}

// Чтение трубы из файла (метка PIPE уже прочитана в main).
// Если данные правильные, они копируются в p, иначе p не меняется
void load_pipe(ifstream& fin, PIPE& p) {
	PIPE tmp = PIPE();
	getline(fin, tmp.name);
	fin >> tmp.length >> tmp.diameter >> tmp.isWorking;
	if (!fin.fail() && tmp.length > 0 && tmp.diameter > 0)
		p = tmp;
	fin.ignore(numeric_limits<streamsize>::max(), '\n');   // перейти на следующую строку
}

// Запись КС в уже открытый файл: метка KS, затем данные по строкам
void save_ks(ofstream& fout, const KS& s) {
	fout << "KS" << "\n" << s.name << "\n" << s.works << "\n" << s.worksA << "\n" << s.efficiency << "\n";
}

// Чтение КС из файла (метка KS уже прочитана в main).
// Если данные правильные, они копируются в s, иначе s не меняется
void load_ks(ifstream& fin, KS& s) {
	KS tmp = KS();
	getline(fin, tmp.name);
	fin >> tmp.works >> tmp.worksA >> tmp.efficiency;
	if (!fin.fail() && tmp.works > 0 && tmp.worksA >= 0
		&& tmp.worksA <= tmp.works && tmp.efficiency >= 0 && tmp.efficiency <= 100)
		s = tmp;
	fin.ignore(numeric_limits<streamsize>::max(), '\n');   // перейти на следующую строку
}

int main()
{
    PIPE p = PIPE();   // все поля обнулены: длина 0 = труба ещё не создана
    KS s = KS();       // все поля обнулены: 0 цехов = КС ещё не создана
    int d;

    clear_screen();   

    do {
        cout << "1. Create pipe" << endl;
        cout << "2. Edit pipe" << endl;
        cout << "3. Show pipe" << endl;
        cout << "4. Create KS" << endl;
        cout << "5. Edit KS" << endl;
        cout << "6. Show KS" << endl;
        cout << "7. Save pipe" << endl;
        cout << "8. Save KS" << endl;
        cout << "9. Load pipe" << endl;
        cout << "10. Load KS" << endl;
        cout << "0. Exit" << endl;

        cout << "Choose an option: ";
        cin >> d;
        if (cin.fail()) {          
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            d = -1;
            cout << "Error, choose the right option" << endl;
            cout << "\nPress Enter to continue...";
            cin.get();
            clear_screen();
            continue;
        }

        // Файл один на трубу и КС, поэтому для пунктов 7-10
        // сначала читаем, что в нём уже сохранено
        PIPE filePipe = PIPE();
        KS fileKs = KS();
        if (d >= 7 && d <= 10) {
            ifstream fin(FILE_NAME);
            string mark;
            while (getline(fin, mark)) {       // читаем метки PIPE / KS
                if (mark == "PIPE")
                    load_pipe(fin, filePipe);
                else if (mark == "KS")
                    load_ks(fin, fileKs);
            }
            fin.close();
        }

        switch (d) {

        case 1: {
            clear_screen();
            create_pipe(p);
            break;
        }

        case 2: {
            clear_screen();
            if (p.length <= 0)
                cout << "Pipe is not created yet" << endl;
            else
                edit_pipe(p);
            break;
        }

        case 3: {
            clear_screen();
            if (p.length <= 0)
                cout << "Pipe is not created yet" << endl;
            else
                show_pipe(p);
            break;
        }

        case 4: {
            clear_screen();
            create_ks(s);
            break;
        }

        case 5: {
            clear_screen();
            if (s.works <= 0)
                cout << "KS is not created yet" << endl;
            else
                edit_ks(s);
            break;
        }

        case 6: {
            clear_screen();
            if (s.works <= 0)
                cout << "KS is not created yet" << endl;
            else
                show_ks(s);
            break;
        }

        case 7: {   // сохранить трубу, КС из файла переписать обратно без изменений
            clear_screen();
            if (p.length <= 0) {
                cout << "Pipe is not created yet" << endl;
                break;
            }
            ofstream fout(FILE_NAME);
            if (!fout) {
                cout << "Error opening " << FILE_NAME << " for writing" << endl;
                break;
            }
            save_pipe(fout, p);
            if (fileKs.works > 0)
                save_ks(fout, fileKs);
            fout.close();
            cout << "Pipe was saved to " << FILE_NAME << endl;
            break;
        }

        case 8: {   // сохранить КС, трубу из файла переписать обратно без изменений
            clear_screen();
            if (s.works <= 0) {
                cout << "KS is not created yet" << endl;
                break;
            }
            ofstream fout(FILE_NAME);
            if (!fout) {
                cout << "Error opening " << FILE_NAME << " for writing" << endl;
                break;
            }
            if (filePipe.length > 0)
                save_pipe(fout, filePipe);
            save_ks(fout, s);
            fout.close();
            cout << "KS was saved to " << FILE_NAME << endl;
            break;
        }

        case 9: {   // загрузить трубу
            clear_screen();
            if (filePipe.length <= 0) {
                cout << "No correct pipe data in " << FILE_NAME << endl;
            }
            else {
                p = filePipe;
                cout << "Pipe was loaded" << endl;
            }
            break;
        }

        case 10: {  // загрузить КС
            clear_screen();
            if (fileKs.works <= 0) {
                cout << "No correct KS data in " << FILE_NAME << endl;
            }
            else {
                s = fileKs;
                cout << "KS was loaded" << endl;
            }
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
            clear_screen();    // очистка консоли после каждой функции
        }

    } while (d != 0);

    return 0;
}


