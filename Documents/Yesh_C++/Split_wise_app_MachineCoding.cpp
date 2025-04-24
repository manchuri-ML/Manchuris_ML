#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

class User
{
    public:
    string name;
    User (string n)
    {
        name =n;
    }
};

class Expense
{
    public:
    string paid;
    double amount;
    vector<string> people;
    string type;
    
    Expense (string pd, double amt, vector<string> p, string t)
    {
        paid =pd;
        amount =amt;
        people = p;
        type =t;
    }
};

class BalanceBook
{
    unordered_map<string, unordered_map<string, double>> balance;
    
    public:
    
    void addExpense( Expense& e)
    {
        double share = e.amount/e.people.size();
        
        for (string person : e.people)
        {
            if (person != e.paid)
            balance[person][e.paid]+= share;
        }
    }
    
    void showall()
    {
        bool found=false;
        for (auto& from: balance)
        {
            for(auto& to: from.second)
            {
                if (to.second >0)
                {
                    cout<<""<<from.first<<" ows"<<""<<to.first<<" "<<to.second<<endl;
                    found=true;
                }
            }
        }
        if (!found)
            cout<<"No balances"<<endl;
    }
    
    void showuser(string user)
    {
        for (auto& owe : balance[user])
        {
            if (owe.second>0)
                cout<<user<<" ows "<<owe.first<<" "<<owe.second<<endl;
        }
        
        for (auto& owed: balance)
        {
            if (owed.first != user && owed.second[user]>0)
                cout<<owed.first<<"ows "<< user<<" "<<owed.second[user]<<endl;
        }
        
    }
};
class Manager
{
    vector<User> users;
    BalanceBook book;
    public:
    Manager (vector<string> names)
    {
        for( string name:names)
            users.push_back(User(name));
    }
    
    void run()
    {
        string line;
        while(getline(cin, line))
        {
            if (line.empty()) continue;
            
            stringstream ss(line);
            string word;
            ss >> word;
            if (word == "SHOW")
            {
                string uname;
                ss >> uname;
                if (uname.empty())
                    book.showall();
                else
                    book.showuser(uname);
            }
            else if (word == "EXPENSE")
            {
                string paidby;
                double amount;
                int count;
                ss >> paidby >> amount >> count;
                
                vector<string> people;
                for (int i=0;i< count;i++)
                {
                    string person;
                    ss >> person;
                    people.push_back(person);
                }
                
                string type;
                ss >> type;
                Expense e(paidby, amount, people, type);
                book.addExpense(e);
            }
        }
    }
};
    
int main() {
    vector<string> names = {"u1", "u2", "u3", "u4"};
    Manager m(names);
    m.run();
    return 0;
}
