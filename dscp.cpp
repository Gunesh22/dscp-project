#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Read {
public:
    string name;
    string topic;
    string date;
    string key;

    Read(string _name, string _topic, string _date, string _key) {
        name = _name;
        topic = _topic;
        date = _date;
        key = _key;
    }

    void display_Read() const {
        cout << "Student Name: " << name << endl;
        cout << "Topic: " << topic << endl;
        cout << "Date: " << date << endl;
        cout << "Key: " << key << endl;
    }
};

class Student {
public:
    string name;
    string topic;
    string date;
    string key;

    // Constructor to initialize 
    Student(string _name, string _topic, string _date, string _key) : name(_name), topic(_topic), date(_date), key(_key) {}

    // Default constructor
    Student() {}

    // Method to display student details
    void display_Student() const {
        cout << "Student Name: " << name << endl;
        cout << "Topic: " << topic << endl;
        cout << "Date: " << date << endl;
        cout<< "key: "<<key<<endl;
    }

    string getName() const { return name; }
    string getTopic() const { return topic; }
    string getDate() const { return date; }
};

string last_key_fun(const string& filename) {
    ifstream inputFile(filename, ios::app);
    string line, lastKey;

    if (inputFile.is_open()) {
        // Seek to the end of the file
        inputFile.seekg(0, ios::end);

        // Start reading backward until a newline is encountered
        bool foundNewLine = false;
        long long pos = inputFile.tellg();
        while (pos >= 0 && !foundNewLine) {
            inputFile.seekg(pos, ios::beg);
            char ch;
            inputFile.get(ch);
            if (ch == '\n') {
                foundNewLine = true;
            }
            pos--;
        }

        // Read the last line and extract the last key
        getline(inputFile, line);
        if (!line.empty()) {
            size_t lastCommaPos = line.find_last_of(',');
            if (lastCommaPos != string::npos && lastCommaPos < line.size() - 1) {
                lastKey = line.substr(lastCommaPos + 1);
            }
        }

        inputFile.close();
    } else {
        cerr << "Unable to open file." << std::endl;
    }

    return lastKey;
}


vector<Read> reads;

void read_function() {
    string searchvalue;
    cout << "Search: ";
    cin >> searchvalue;

    ifstream inputfile;
    inputfile.open("F:\\dsa\\array\\data.csv" , ios::app) ; // Use double backslashes in the file path

    if (!inputfile) {
        cerr << "Error opening the file." << endl;
        return;
    }

    string line;
    while (getline(inputfile, line)) {
        stringstream inputstring(line);

        string name, topic, date, key;
        getline(inputstring, name, ',');
        getline(inputstring, topic, ',');
        getline(inputstring, date, ',');
        getline(inputstring, key, ',');

        // Check if any field matches the search value
        if (name == searchvalue || topic == searchvalue || date == searchvalue || key == searchvalue) {
            Read record(name, topic, date, key);
            reads.push_back(record);
        }
    }

    inputfile.close();

    // Display the search results
    for (const auto &read : reads) {
        read.display_Read();
    }
}

void write() {
    int numStudents;

    cout << "Enter the number of students: ";
    cin >> numStudents;

    vector<Student> students;

    for (int i = 0; i < numStudents; i++) {
        string name, topic, date;

        cout << "Enter student " << i + 1 << "'s name: ";
        cin >> name;
        cout << "Enter student " << i + 1 << "'s topic: ";
        cin >> topic;
        cout << "Enter student " << i + 1 << "'s date: ";
        cin >> date;

        std::string filename = "F:\\dsa\\array\\data.csv";
        std::string lastkey = last_key_fun(filename); // get the key

        string str = lastkey;
        
        int num;
        std::istringstream(str) >> num; // string to int
        num = num +1;
        
        std::ostringstream oss; // int to string12
        oss << num;
        std::string newStr = oss.str();
        



        students.push_back(Student(name, topic, date, newStr));
    }

    // Open the CSV file in append mode
    ofstream file("F:\\dsa\\array\\data.csv", ios::app);

    




    if (file.is_open()) {
        for (const auto &student : students) {
            file << student.getName() << "," << student.getTopic() << "," << student.getDate() << "\n";
        }
        file.close();
        cout << "Data added to data.csv successfully." << endl;
    } else {
        cout << "Error opening file data.csv." << endl;
    }

}

void Admin() {
    int r;
    int pin;
    cout << "Enter Pin: " << endl;
    cin >> pin;

    if (pin == 123) {
        cout << "Enter 1 for Read or 2 for write" << endl;
        cin >> r;

        if (r == 1) {
            read_function();
        } else if (r == 2) {
            write();
        } else {
            cout << "Invalid input." << endl;
        }
    } else {
        cout << "Pin is invalid." << endl;
        cout << "Enter pin again: " << endl;
        cin >> pin;
    }
}

void User() {
    read_function();
}

int main() {
    Admin(); // You can change this to User() if you want to directly enter the read mode without pin verification
    return 0;
}