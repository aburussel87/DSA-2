#include "table.h"
using namespace std;

int main()
{
    int N, Q;
    cin >> N >> Q;

    OuterHashTable outer_table(N);

    for (int _ = 0; _ < Q; _++)
    {
        string cmd;
        cin >> cmd;

        if (cmd == "INSERT")
        {
            int group_id, user_id;
            string permission;
            cin >> group_id >> user_id >> permission;
            outer_table.insert(group_id, user_id, permission);
        }
        else if (cmd == "SEARCH")
        {
            string line;
            getline(cin, line);
            stringstream ss(line);

            int group_id;
            ss >> group_id;

            int user_id;
            if (ss >> user_id)
            {
                string result = outer_table.search_user(group_id, user_id);
                cout << result << "\n";
            }
            else
            {
                bool found = false;
                vector<pair<int, string>> results = outer_table.search_group(group_id, found);
                if (!found)
                {
                    cout << "Group " << group_id << " not found\n";
                }
                else
                {
                    for (auto &p : results)
                    {
                        cout << "(" << p.first << ", " << p.second << ")";
                    }
                    if (!results.empty())
                        cout << "\n";
                }
            }
        }

        else if (cmd == "DELETE")
        {
            int group_id, user_id;
            cin >> group_id >> user_id;
            bool found;
            pair<int, string> res = outer_table.remove(group_id, user_id, found);
            if (!found)
            {
                cout << "User " << user_id << " not found in group " << group_id << "\n";
            }
            else
            {
                cout << "(" << res.first << ", " << res.second << ") deleted\n";
            }
        }
    }

    return 0;
}
