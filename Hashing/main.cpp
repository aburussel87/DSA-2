#include "hash_table.h"

struct data
{
    int collisions;
    double avg_stime1;
    double avg_probes1;
    double avg_stime2;
    double avg_probes2;
    data()
    {
        this->collisions = 0;
        this->avg_probes1 = 0;
        this->avg_probes2 = 0;
        this->avg_stime1 = 0;
        this->avg_stime2 = 0;
    }
};

#define MAX_WORDS 10000
string generate_words(mt19937 &gen)
{
    uniform_int_distribution<> word_len(5, 10);
    uniform_int_distribution<> chars('a', 'z');
    int len = word_len(gen);
    string word;
    for (int i = 0; i < len; i++)
    {
        word += static_cast<char>(chars(gen));
    }
    return word;
}

void printData(data &RBT1, data &RBT2, data &LP1, data &LP2, data &DH1, data &DH2, int N, ofstream &csv)
{
    cout << fixed << setprecision(2);
    csv << fixed << setprecision(2);

    cout << setw(60) << "Function 1" << setw(50) << "Function 2\n";
    cout << setw(41) << "Time" << setw(11) << "Probes"
         << setw(8) << "Time" << setw(9) << "Probes"
         << setw(23) << "Time" << setw(10) << "Probes"
         << setw(8) << "Time" << setw(11) << "Probes\n";
    cout << string(120, '-') << "\n";

    csv << "Method,Collisions (F1),Time1 (F1),Probes1 (F1),Time2 (F1),Probes2 (F1),"
        << "Collisions (F2),Time1 (F2),Probes1 (F2),Time2 (F2),Probes2 (F2)\n";

    auto writeRow = [&](string name, data &d1, data &d2)
    {
        string probes1_F1 = (name == "Separate Chaining") ? "N/A" : to_string(d1.avg_probes1 / N);
        string probes2_F1 = (name == "Separate Chaining") ? "N/A" : to_string(d1.avg_probes2 / N);
        string probes1_F2 = (name == "Separate Chaining") ? "N/A" : to_string(d2.avg_probes1 / N);
        string probes2_F2 = (name == "Separate Chaining") ? "N/A" : to_string(d2.avg_probes2 / N);

        cout << setw(20) << name
             << setw(10) << d1.collisions
             << setw(10) << d1.avg_stime1 / N
             << setw(10) << probes1_F1
             << setw(10) << d1.avg_stime2 / N
             << setw(10) << probes2_F1
             << setw(10) << d2.collisions
             << setw(10) << d2.avg_stime1 / N
             << setw(10) << probes1_F2
             << setw(10) << d2.avg_stime2 / N
             << setw(10) << probes2_F2 << "\n";

        csv << name << ","
            << d1.collisions << ","
            << d1.avg_stime1 / N << ","
            << probes1_F1 << ","
            << d1.avg_stime2 / N << ","
            << probes2_F1 << ","
            << d2.collisions << ","
            << d2.avg_stime1 / N << ","
            << probes1_F2 << ","
            << d2.avg_stime2 / N << ","
            << probes2_F2 << "\n";
    };

    writeRow("Separate Chaining", RBT1, RBT2);
    writeRow("Linear Probing", LP1, LP2);
    writeRow("Double Hashing", DH1, DH2);

    cout << string(120, '-') << "\n";
}

void collectData(mt19937 &gen, int N, vector<string> &words, data &RBT, data &LP, data &DH, int total, bool useHash2)
{
    HashTable vaultx(N, 5);
    vector<string> insertedWords;
    for (int i = 0; i < total; i++)
    {
        uniform_int_distribution<> index(0, words.size() - 1);
        int x = index(gen);
        vaultx.insert(words[x], "RBT", useHash2, RBT.collisions);
        vaultx.insert(words[x], "LP", useHash2, LP.collisions);
        vaultx.insert(words[x], "DH", useHash2, DH.collisions);
        insertedWords.push_back(words[x]);
    }

    int toSearch = total / 10;
    for (int i = 0; i < toSearch; i++)
    {
        uniform_int_distribution<> index(0, insertedWords.size() - 1);
        int x = index(gen);
        int probes = 0;
        long long time_taken = 0;
        vaultx.find(insertedWords[x], "RBT", probes, time_taken, useHash2);
        RBT.avg_probes1 += probes;
        RBT.avg_stime1 += time_taken;
        vaultx.find(insertedWords[x], "LP", probes, time_taken, useHash2);
        LP.avg_probes1 += probes;
        LP.avg_stime1 += time_taken;
        vaultx.find(insertedWords[x], "DH", probes, time_taken, useHash2);
        DH.avg_probes1 += probes;
        DH.avg_stime1 += time_taken;
    }
    vector<string> toRemove;
    for (int i = 0; i < toSearch; i++)
    {
        uniform_int_distribution<> index(0, insertedWords.size() - 1);
        int x = index(gen);
        toRemove.push_back(insertedWords[x]);
        vaultx.remove(insertedWords[x], "RBT", useHash2);
        vaultx.remove(insertedWords[x], "LP", useHash2);
        vaultx.remove(insertedWords[x], "DH", useHash2);
    }
    for (int i = 0; i < toSearch; i++)
    {
        int x;
        string word;
        if (i <= toSearch / 2)
        {
            uniform_int_distribution<> index(0, toRemove.size() - 1);
            x = index(gen);
            word = toRemove[x];
        }
        else
        {
            uniform_int_distribution<> index(0, insertedWords.size() - 1);
            x = index(gen);
            word = toRemove[x];
        }
        int probes = 0;
        long long time_taken = 0;
        vaultx.find(word, "RBT", probes, time_taken, useHash2);
        RBT.avg_probes2 += probes;
        RBT.avg_stime2 += time_taken;
        vaultx.find(word, "LP", probes, time_taken, useHash2);
        LP.avg_probes2 += probes;
        LP.avg_stime2 += time_taken;
        vaultx.find(word, "DH", probes, time_taken, useHash2);
        DH.avg_probes2 += probes;
        DH.avg_stime2 += time_taken;
    }
}

int main()
{
    ofstream out("results.csv");

    ofstream outfile("words.txt");
    vector<string> words;
    if (!outfile.is_open())
    {
        cout << "Error opening file!" << endl;
        return 1;
    }
    mt19937 gen(random_device{}());
    for (int i = 0; i < MAX_WORDS; i++)
    {
        string word = generate_words(gen);
        if (!word.empty())
        {
            words.push_back(word);
            outfile << word << endl;
        }
    }
    outfile.close();
    cout << "Generated 10000 words successfully!\n";

    if (words.empty())
    {
        cerr << "No words found in the file" << endl;
        return 1;
    }
    else
    {

        int N;
        cout << "Enter Value for size of table: ";
        cin >> N;
        float a = 0.4;
        while (a <= 1)
        {
            int total = N * a;
            data RBT1, LP1, DH1, RBT2, LP2, DH2;
            collectData(gen, N, words, RBT1, LP1, DH1, total, false);
            collectData(gen, N, words, RBT2, LP2, DH2, total, true);
            cout << "For load Factor  " << a << ":\n";
            printData(RBT1, RBT2, LP1, LP2, DH1, DH2, total / 10, out);
            a += 0.1;
        }
    }
    return 0;
}