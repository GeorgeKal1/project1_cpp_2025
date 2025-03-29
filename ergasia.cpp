#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class participant {
    friend class participantList;

private:
    string fullname;
    int ID;
    int ranking;
    string origin;
    int timestamp;
    int position; // A variable that shows the position in the list
    

public:

    participant* next; // Pointer to the next node (participant)
    participant(const string& str) : next(nullptr) { // Constructor
        parseData(str);
    }

    // Getter functions
    string getName() { return fullname; }
    string getOrigin() { return origin; }
    int getID() { return ID; }
    int getRanking() { return ranking; }
    int getTimestamp() { return timestamp; }

    // Constructor helper function
    void parseData(const string& str);
};

class participantList {
    
public:
    participant* head; // Pointer to the first node of the list

    participantList() : head(nullptr) {}; // Constructor

    ~participantList() { // Destructor
        participant* temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }  


    void readfile(string filename); // Method for the 1st option
    void readfileOrdered(string filename);// Method for the 2nd option
    void findPlayer(string name1,string lname1);//method for the 6th option
    void printAll(); // Method for the 7th option
};

// This method gets a string of the elements of a participant and separates them into variables
void participant::parseData(const string &str) {
    size_t start = 0, end;

    // Extract full name (everything before the first comma)
    end = str.find(',');
    if (end == string::npos) {
        cerr << "Error: Missing comma after full name!" << endl;
        return;
    }
    fullname = str.substr(start, end - start);
    start = end + 1;

    // Extract ID
    end = str.find(',', start);
    if (end == string::npos) {
        cerr << "Error: Missing data fields!" << endl;
        return;
    }
    ID = stoi(str.substr(start, end - start));
    start = end + 1;

    // Extract ranking
    end = str.find(',', start);
    if (end == string::npos) {
        cerr << "Error: Missing data fields!" << endl;
        return;
    }
    ranking = stoi(str.substr(start, end - start));
    start = end + 1;

    // Extract origin
    end = str.find(',', start);
    if (end == string::npos) {
        cerr << "Error: Missing data fields!" << endl;
        return;
    }
    origin = str.substr(start, end - start);
    start = end + 1;

    // Extract timestamp (last value, no more commas expected)
    timestamp = stoi(str.substr(start));
}

// Function that implements the 1st function (reading from file)
void participantList::readfile(string filename) {
    // If the list is not empty, exit early
    if (head != nullptr) {
        cout << "Participants already loaded. File reading skipped." << endl;
        return;
    }

    fstream file{filename, ios::in}; 
    string str;

    if (!file) {
        cout << "No such file" << endl;
        return;
    }

    participant* temp = nullptr;

    
    //here the list is filled
    if (getline(file, str)) {
        head = new participant(str);
        temp = head;
    }
    while (getline(file, str)) {
        participant* newparticipant = new participant(str);
        temp->next = newparticipant;
        temp = newparticipant;
    }

    cout << "Participants loaded successfully!" << endl;
}

// this method implements the 2nd option (reading from file ordered by ID)
void participantList::readfileOrdered(string filename){
    // If the list is not empty, exit early
    if (head != nullptr) {
        cout << "Participants already loaded. File reading skipped." << endl;
        return;
    }

    fstream file{filename, ios::in}; 
    string str;

    if (!file) {
        cout << "No such file" << endl;
        return;
    }

    participant * temp;
    participant * temp2; 
    participant *newparticipant;

    if (getline(file, str)) {
        head = new participant(str);
        temp = head;
    }
    while (getline(file, str)) {
        participant* newparticipant = new participant(str);

        // Case 1: Insert at the beginning if it has the smallest ID
        if (newparticipant->getID() < head->getID()) {
            newparticipant->next = head;
            head = newparticipant;
            continue;
        }

        // Case 2: Find the correct position in the sorted list
        participant* temp = head;
        while (temp->next != nullptr && temp->next->getID() < newparticipant->getID()) {
            temp = temp->next;
        }

        // Insert in the list
        newparticipant->next = temp->next;
        temp->next = newparticipant;
    }

        

    
    cout<<"participants loaded sucessfully";

}

//function that implements the 6th option(finding player by name)
void participantList::findPlayer(string name1, string lname1){
    participant *temp= head;

    string full1= name1 + " " + lname1;
    string full2= lname1 + " " + name1;

    while(temp->getName()!=full1 || temp->getName()!=full1){
        
        if (temp->next==nullptr){
            cout<<"Player not Found"<<endl;
            return;
        }

        temp= temp->next;
    }
    
    cout << "Name: " << temp->getName() <<
                "\nID: " << temp->getID() <<
                "\nRanking: " << temp->getRanking() <<
                "\nOrigin: " << temp->getOrigin() <<
                "\nTimestamp: " << temp->getTimestamp() << endl;
    cout << "-----------------------------" << endl;

}

// Function that prints all participants
void participantList::printAll() {
    participant* temp = head;
    if (temp == nullptr) {
        cout << "No participants to display." << endl;
        return;
    }

    while (temp != nullptr) { // Loop through all nodes
        cout << "Name: " << temp->getName() <<
                "\nID: " << temp->getID() <<
                "\nRanking: " << temp->getRanking() <<
                "\nOrigin: " << temp->getOrigin() <<
                "\nTimestamp: " << temp->getTimestamp() << endl;
        cout << "-----------------------------" << endl;
        
        temp = temp->next;
    }
}



int main() {
    participantList list;
    string file = "contest_participants.txt";

    list.readfileOrdered(file); 
    
    list.printAll(); 

    list.findPlayer("Joseph","Nelson");
    return 0;
}


int menu(){
    int answ;
    cout << "1. Read Players \n" <<
            "2. Read Players sorted by ID \n"<<
            "3. Sort list by ranking of players \n"<<
            "4. Delete layer by ID \n" <<
            "5. Delete complete list \n" <<
            "6. Search player by name \n" <<
            "7. Print list of players by current order \n"<<
            "8. Print list of Players by sign-up timestamp \n"<<
            "9. Exit\n"<<endl;
    cout << "Give your answer: ";
    cin >> answ;
    return answ;
}