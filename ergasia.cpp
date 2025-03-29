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
    

    //helper function for node swapping
    void swapWith(participant* other) { 
        swap(fullname, other->fullname);
        swap(ID, other->ID);
        swap(ranking, other->ranking);
        swap(origin, other->origin);
        swap(timestamp, other->timestamp);
        
    }

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
    int length() const {// function that returns the length of the list
        participant* temp = head;
        int num = 0;
        while (temp != nullptr) {
            num++;
            temp = temp->next;
        }
    return num;
    }
    

    void readfile(string filename); // Method for the 1st option
    void readfileOrdered(string filename);// Method for the 2nd option
    void sortlist();//method for the 3rd option
    void deletebyid(int id);
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

    // extract timestamp
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

//this method implements the 3rd option(sort the list based on ranking descending)
void participantList::sortlist() {
    if (!head || !head->next) return;


    participant* max;
    participant* temp1 = head;
    participant* temp2;


    //the logic of selection sort is applied
    while (temp1->next != nullptr) {
        max= temp1;
        temp2 = temp1->next;

        while (temp2 != nullptr) { 
            if (temp2->ranking > max->ranking) {
                max = temp2;
            }
            temp2 = temp2->next;
        }

        // Swap participant data
        temp1->swapWith(max);

        temp1 = temp1->next;
    }
    cout<< "Successfully sorted"<<endl;
}

//this method implements the 4th option()
void participantList::deletebyid(int id){
    if (head==nullptr){
        cout<<"The list is empty"<<endl;
        return;
    }

    participant* temp;
    participant* prev;
    temp=head;
    
    if (temp->getID()==id){//case the right node is the first
        head=temp->next;
        delete temp;
        cout<<"Successfuly deleted participant"<<endl;
        return;
    }

    prev=temp;
    temp=temp->next;
    
    while(temp!=nullptr){//search of the right node
        if(temp->getID()==id){
            prev->next=temp->next;
            delete temp;
            cout<<"Successfuly deleted participant"<<endl;
            return;
        }
        prev=temp;
        temp=temp->next;
    }


    cout<<"No participant with this ID"<<endl;

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





int menu(){//this method shows the message and returns the answer of the user
    int answ;
    cout << "1. Read Players \n" <<
            "2. Read Players sorted by ID \n"<<
            "3. Sort list by ranking of players \n"<<
            "4. Delete player by ID \n" <<
            "5. Delete complete list \n" <<
            "6. Search player by name \n" <<
            "7. Print list of players by current order \n"<<
            "8. Print list of Players by sign-up timestamp \n"<<
            "9. Exit\n"<<endl;
    cout << "Give your answer: ";
    cin >> answ;
    cout << "-------------------------"<<endl;
    return answ;
}

void actions(int answ,participantList& list1){//this method does the functions
    string filename,name,lname;
    int id;

    switch (answ){
    case 1:
        
        cout<<"Give the name of the file: ";
        cin>> filename;
        list1.readfile(filename);
        break;
    case 2:
        cout<<"Give the name of the file: ";
        cin>> filename;
        list1.readfileOrdered(filename);
        break;
    case 3:
        list1.sortlist();
        break;
    case 4:
        cout<<"Give player Id: ";
        cin >> id;
        list1.deletebyid(id);
        break;
    case 5:
        list1.~participantList();
        cout<<"sucessfuly deleted list\n";
        break;
    case 6:
        cout<<"Give first name: ";
        cin>> name;
        cout<<"Give last name: ";
        cin>>lname;
        cout<<"\n";
        list1.findPlayer(name,lname);
        break;
    case 7:
        list1.printAll();
        break;
        
    case 8:
        break;
    case 9:
        cout<<"goodbye";
    default:
        break;
    }
}

int main() {
    participantList list;
    int answ=menu();
    while(answ!=9){
        actions(answ,list);
        answ=menu();
    }

    
    return 0;
}
