#include "admin.h"
#include "user.h"
#include "number.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    Number::InitRandom();
    Admin * admin = new Admin();
    vector<string> names;
    names.push_back("Alice");
    names.push_back("Bob");
    names.push_back("Charly");
    names.push_back("Darek");
    names.push_back("Eemma");

    map<const string, User *> users; 
    for(auto name: names)
    {
        User * user = new User(name, admin);
        users[name] = user;
    }

    admin->PrintAllUsers();

    cout << "\n===> Alice send message to Bob using DSA\n";
    users["Alice"]->SendMessage("hello", "Bob", DSA);
    cout << "\n===> Bob send message to Alice using Schnorr\n";
    users["Bob"]->SendMessage("hi", "Alice", Schnorr);
    cout << "\n===> Alice send malicious message to Eemma using DSA\n";
    users["Alice"]->MaliciousSendMessage("What is up", "Eemma", DSA);
    cout << "\n===> Bob send message to Darek using Schnorr\n";
    users["Bob"]->SendMessage("11111`````Yeah   aaa", "Darek", Schnorr);
    cout << "\n===> Bob send message to Bob using Schnorr\n";
    users["Bob"]->SendMessage("11```Yeah   aaa", "Bob", DSA);
    cout << "\n===> Charly send message to Darek using Schnorr\n";
    users["Charly"]->SendMessage("What''''s up   aaa", "Darek", Schnorr);



    cout << "\n===> Alice send malicious message to Bob using DSA\n";
    users["Alice"]->MaliciousSendMessage("hello", "Bob", DSA);
    cout << "\n===> Bob send  message to Charly using Schnorr\n";
    users["Bob"]->SendMessage("hi yoyoyoyoyo", "Charly", Schnorr);
    cout << "\n===> Bob send malicious message to Eemma using Schnorr\n";
    users["Bob"]->MaliciousSendMessage("abchhhscr", "Eemma", Schnorr);

    cout << "\n===> Bob send malicious message to Alice using Schnorr\n";
    users["Bob"]->MaliciousSendMessage("hi", "Alice", Schnorr);
    cout << "\n===> Bob send malicious message to Eemma using DSA\n";
    users["Alice"]->MaliciousSendMessage("What is up", "Eemma", DSA);
    cout << "\n===> Bob send message to Darek using Schnorr\n";
    users["Bob"]->SendMessage("11111`````Yeah   aaa", "Darek", Schnorr);
    cout << "\n===> Bob send malicious message to Bob using Schnorr\n";
    users["Bob"]->MaliciousSendMessage("11```Yeah   aaa", "Bob", DSA);
    cout << "\n===> Charly send malicious message to Darek using Schnorr\n";
    users["Charly"]->MaliciousSendMessage("What''''s up   aaa", "Darek", Schnorr);

    cout << "\n===> Eemma send message to Charly using Schnorr\n";
    users["Eemma"]->SendMessage(",,,,....jjjjhhhggg", "Charly", Schnorr);
    cout << "\n===> Eemma send malicious message to Darek using Schnorr\n";
    users["Eemma"]->MaliciousSendMessage("...246r...", "Darek", DSA);

    cout <<endl<<"Destruction==="<<endl;
    delete admin;

    for(const auto&kv: users)
    {
        delete kv.second;
    }

    Number::Delete();
    return 0;
}