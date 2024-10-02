#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>  
#include <unistd.h>    

using namespace std;

class User {
public:
    string _name;
    string _login;
    string _pass;

    User(const string& name = "", const string& login = "", const string& pass = "")
        : _name(name), _login(login), _pass(pass) {}

    static vector<User> loadUsers(const string& filename) {
        vector<User> users;
        ifstream infile(filename);
        if (infile.is_open()) {
            string name, login, pass;
            while (infile >> name >> login >> pass) {
                users.push_back(User(name, login, pass));
            }
            infile.close();
        }
        return users;
    }

    static void saveUsers(const vector<User>& users, const string& filename) {
        ofstream outfile(filename);
        if (outfile.is_open()) {
            for (const auto& user : users) {
                outfile << user._name << " " << user._login << " " << user._pass << endl;
            }
            outfile.close();
        }
        chmod(filename.c_str(), S_IRUSR | S_IWUSR); 
    }
};

class Message {
public:
    string _text;
    string _sender;
    string _receiver;

    Message(const string& text = "", const string& sender = "", const string& receiver = "")
        : _text(text), _sender(sender), _receiver(receiver) {}

    static vector<Message> loadMessages(const string& filename) {
        vector<Message> messages;
        ifstream infile(filename);
        if (infile.is_open()) {
            string text, sender, receiver;
            while (infile >> text >> sender >> receiver) {
                messages.push_back(Message(text, sender, receiver));
            }
            infile.close();
        }
        return messages;
    }

    static void saveMessages(const vector<Message>& messages, const string& filename) {
        ofstream outfile(filename);
        if (outfile.is_open()) {
            for (const auto& msg : messages) {
                outfile << msg._text << " " << msg._sender << " " << msg._receiver << endl;
            }
            outfile.close();
        }
        chmod(filename.c_str(), S_IRUSR | S_IWUSR); 
    }
};


int main() {
    const string userFile = "users.dat";
    const string messageFile = "messages.dat";

  
    vector<User> users = User::loadUsers(userFile);
    vector<Message> messages = Message::loadMessages(messageFile);

    users.push_back(User("SkillFac", "Sigma", "BillyBat"));
    messages.push_back(Message("Sup, Billy!", "bye bye", "09.11.2001"));

    User::saveUsers(users, userFile);
    Message::saveMessages(messages, messageFile);

    cout << "Данные сохранены. Файлы защищены правами доступа" << endl;

    return 0;
}
