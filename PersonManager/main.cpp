#include <iostream>
#include <string>
#include <fstream>


using namespace std;



struct Person {
    string name;
    int age;
    Person* nextAge;
    Person* nextName;
};

class Data {
private:
    Person* headA;
    Person* headN;
    int size;
public:
    Data() {
        headA = NULL;
        headN = NULL;
        size = 0;
    }
    void add(string name, int age);
    bool remove(string name);
    void update(string name, int age);
    void printByAge();
    void printByName();
    void loadFile(string filename);
    void saveToFileByAge(string filename);
    void saveToFileByName(string filename);
};


void Data::add(string name, int age) {
    Person* newP = new Person;
    newP->name = name;
    newP->age = age;
    newP->nextAge = NULL;
    newP->nextName = NULL;

    if (headN == NULL) {
        headN = newP;
    }
    else {
        Person* temp = headN;
        Person* prev = NULL;
        while (temp != NULL && name > temp->name) {
            prev = temp;
            temp = temp->nextName;
        }
        if (prev == NULL) {
            newP->nextName = headN;
            headN = newP;
        }
        else {
            prev->nextName = newP;
            newP->nextName = temp;
        }
    }
    if (headA == NULL) {
        headA = newP;
    }
    else {
        Person* temp = headA;
        Person* prev = NULL;

        while (temp != NULL && age < temp->age) {
            prev = temp;
            temp = temp->nextAge;
        }
        if (prev == NULL) {
            newP->nextAge = headA;
            headA = newP;
        }
        else {
            prev->nextAge = newP;
            newP->nextAge = temp;
        }
    }
}


bool Data::remove(string name) {
    Person* temp = headN;
    Person* prev = NULL;
    while (temp != NULL && name != temp->name) {
        prev = temp;
        temp = temp->nextName;
    }
    if (temp == NULL) {
        return false;
    }
    else {
        prev->nextName = temp->nextName;
        temp->nextName = NULL;
    }

    Person* temp2 = headA;
    Person* prev2 = NULL;
    while (temp2 != NULL && name != temp->name) {
        prev = temp;
        temp = temp->nextName;
    }
    if (temp2 == NULL) {
        return false;
    }

    else {
        prev2->nextName = temp2->nextName;
        temp2->nextName = NULL;
    }
    delete temp;
    delete temp2;

    return true;
}


void Data::update(string name, int age) {
    Person* temp = headN;
    Person* prev = NULL;

    while (temp != NULL && name != temp->name) {
        prev = temp;
        temp = temp->nextName;
    }
    if (temp == NULL) {
        return;
    }
    else {
        temp->age = age;
    }
    Person* temp2 = headA;
    Person* prev2 = NULL;
    while (temp2 != NULL && name != temp->name) {
        prev2 = temp2;
        temp2 = temp2->nextName;
    }
    if (temp2 == NULL) {
        return;
    }
    else {
        temp2->age = age;
    }
}


void Data::printByAge() {
    Person* temp = headA;
    while (temp != NULL) {
        cout << temp->name << " " << temp->age << endl;
        temp = temp->nextAge;
    }
}


void Data::printByName() {
    Person* temp = headN;
    while (temp != NULL) {
        cout << temp->name << " " << temp->age << endl;
        temp = temp->nextName;
    }
}

void Data::loadFile(string filename) {
    ifstream file;
    file.open(filename.c_str());
    string name;
    int age;
    while (file >> name >> age) {
        add(name, age);
    }
    file.close();
}



void Data::saveToFileByAge(string filename) {
    ofstream file(filename);
    Person* temp = headA;
    while (temp != NULL) {
        file << temp->name << temp->age;
        temp = temp->nextAge;
    }
    file.close();
}



void Data::saveToFileByName(string filename) {
    ofstream file(filename);
    Person* temp = headN;
    while (temp != NULL) {
        file << temp->name << temp->age;
        temp = temp->nextName;
    }
    file.close();
}

int main() {
    Data data;
    data.loadFile("Persons.txt");
    cout << "People sorted by age:" << endl;
    data.printByAge();
    
    cout << endl << "People sorted by name:" << endl;
    data.printByName();
    data.saveToFileByAge("dataByAge.txt");
    data.saveToFileByName("dataByName.txt");
    return 0;
}
