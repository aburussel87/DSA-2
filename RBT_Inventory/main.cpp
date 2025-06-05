#include "inventory.h"
#include <bits/stdc++.h>

vector<string> splitter(const string &s, char delimiter)
{
    vector<string> tokens;
    istringstream ss(s);
    string token;
    while (getline(ss, token, delimiter))
    {
        if (!token.empty())
        {
            if (token.front() == '"')
            {
                token = token.substr(1, token.length() - 2);
            }
            tokens.push_back(token);
        }
    }
    return tokens;
}

int main()
{
    ifstream infile("input.txt");
    INVENTORY myInventory;
    if (!infile.is_open())
    {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    vector<string> orders;
    while (getline(infile, line))
    {
        orders = splitter(line, ' ');
        if (orders[0] == "AI")
        {
            myInventory.AddItem(orders[1], orders[2], orders[3]);
        }
        else if (orders[0] == "BI")
        {
            if (!myInventory.BuyItem(orders[1], orders[2]))
            {
                cout << "Not Available\n";
            }
        }
        else if (orders[0] == "CI")
        {
            int total = myInventory.CheckItem(orders[1]);
            if (total == -1)
            {
                cout << "Not Available\n";
                continue;
            }
            cout << "Stock Left: " << total << endl;
        }
        else if (orders[0] == "Clr")
        {
            if (myInventory.ClearInventory())
            {
                cout << "Successful\n";
                continue;
            }
            cout << "Unsuccessful\n";
        }
        else if (orders[0] == "S")
        {
            cout << myInventory.InventorySize() << endl;
        }
        else if (orders[0] == "Em")
        {
            if (myInventory.Empty())
            {
                cout << "Yes\n";
            }
            else
            {
                cout << "No\n";
            }
        }
        else if (orders[0] == "Itr")
        {
            myInventory.ListInventory();
        }
        else
        {
            cout << "Enter valid command\n";
        }
    }

    infile.close();
    return 0;
}
