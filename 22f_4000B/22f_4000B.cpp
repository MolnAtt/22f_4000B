
#include <iostream>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;



vector<string> feldarabol(string& sor, char elvalasztojel)
{
    istringstream stream(sor);
    vector<string> result;
    string darab;
    while (getline(stream, darab, elvalasztojel))
    {
        result.push_back(darab);
    }
    return result;
}

class Tanulo
{
public:

    int sorszam;
    string nev;
    string matcsop;
    string ancsop;
    string nyelv2;
    string nem;
    int egyuttlakok;
    int testverek;

    Tanulo(int sorszam, string nev, string matcsop, string ancsop, string nyelv2, string nem, int egyuttlakok, int testverek)
    {
        this->sorszam = sorszam;
        this->nev = nev;
        this->matcsop = matcsop;
        this->ancsop = ancsop;
        this->nyelv2 = nyelv2;
        this->nem = nem;
        this->egyuttlakok = egyuttlakok;
        this->testverek = testverek;
    }

    ~Tanulo()
    {
    }

private:

};


vector<Tanulo> Beolvas_tanulok_fajlbol(string fajlnev)
{
    ifstream file(fajlnev);
    vector<Tanulo> tanulok;

    string sor;
    getline(file, sor); // az elsõ sort kidobjuk
    while (getline(file, sor))
    {
        vector<string> sortomb = feldarabol(sor, '\t');
        tanulok.push_back(Tanulo(stoi(sortomb[0]), sortomb[1], sortomb[2], sortomb[3], sortomb[4], sortomb[5], stoi(sortomb[6]), stoi(sortomb[7])));
    }
    file.close();
    return tanulok;
}


vector<vector<int>> Beolvas_kapcsolatok_fajlbol(string fajlnev, int N)
{
    vector<vector<int>> m = vector<vector<int>>(N,vector<int>(N,0));
    ifstream file(fajlnev);

    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            file >> m[i][j];
        }
    }


    return m;
}


string to_graphviz(vector<Tanulo> tanulok, vector<vector<int>> matrix) 
{
    string s = "";
    
    for (size_t i = 0; i < tanulok.size(); i++)
    {
        for (size_t j = i; j < tanulok.size(); j++)
        {
            if (matrix[i][j]==1)
            {
                s += "\""+tanulok[i].nev + "\" -- \"" + tanulok[j].nev + "\";\n";
            }
        }
    }
    
    return "graph G {\n"+s+"\n}";
}

int hanyadik(vector<Tanulo> tanulok, string nev) {
    for (size_t i = 0; i < tanulok.size(); i++)
    {
        if (tanulok[i].nev == nev)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    vector<Tanulo> tanulok = Beolvas_tanulok_fajlbol("4000B_tanulok.tsv");
    cout << tanulok.size();
    vector<vector<int>> szomszedsagi_matrix = Beolvas_kapcsolatok_fajlbol("4000B_kapcsolatok.tsv", tanulok.size());

    cout << endl;

    //for (size_t i = 0; i < tanulok.size(); i++)
    //{
    //    for (size_t j = 0; j < tanulok.size(); j++)
    //    {
    //        cout << szomszedsagi_matrix[i][j];
    //    }
    //    cout << endl;
    //}

    cout << to_graphviz(tanulok, szomszedsagi_matrix);

    if (szomszedsagi_matrix[hanyadik(tanulok, "Parady Csoma")][hanyadik(tanulok, "Vagd Alma")] == 1)
    {
        cout << "Parady Csoma es Vagd Alma baratok\n";
    }
    else {
        cout << "Parady Csoma es Vagd Alma nem baratok\n";
    }
}
