#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> // for sort()

using namespace std;


bool sort_descend_lastcolumn(const vector<int>& v1, const vector<int>& v2)
{
    int n = v1.size();
    return v1[n-1] > v2[n-1];
}

bool sort_firstcolumn(const vector<int>& v1, const vector<int>& v2)
{
    return v1[0] < v2[0];
}

int main()
{
    string buf;
    int i,j,k, color;

    cout << "Graph color problem!" << endl;


    ifstream file("data_graph/gc_1000_9");
    getline(file, buf);
    int i_space = buf.find(' ');
    int nV = stoi(buf.substr(0, i_space));
    int nE = stoi(buf.substr(i_space+1));

    cout << "nV=" << nV << ", nE=" << nE << endl;

    // ������� ���������
    vector < vector<int> > Adj_matrix(nV, vector<int>(nV+1,0));

    for (k=0; k < nE; k++)
    {
        getline(file, buf);
        i_space = buf.find(' ');
        i = stoi(buf.substr(0, i_space));
        j = stoi(buf.substr(i_space+1));
        Adj_matrix[i][j+1] = 1;
        Adj_matrix[j][i+1] = 1;
    }

    file.close();


    // ������� ������
    vector<int> Deg(nV,0);
    for (i=0; i<nV; i++)
    {
        Adj_matrix[i][0] = i; //������ ������
        int s = 0;
        for (j=1; j<nV+1; j++)
            s += Adj_matrix[i][j];
        Deg[i] = s;
    }

    // ������� ��������� + �������
    vector < vector<int> > Adj_Deg(nV, vector<int>(nV+2,0));
    for (i=0; i<nV; i++)
    {
        for (j=0; j<nV+1; j++)
            Adj_Deg[i][j] = Adj_matrix[i][j];
        Adj_Deg[i][nV+1] = Deg[i];
    }


    /* ����� �� �����
    cout << "adj_deg matrix before sort:\n";
    for (i=0; i<nV; i++)
    {
        for ( j=0; j<nV+2; j++)
            cout << Adj_Deg[i][j] << " ";
        cout << endl;
    }
    */

    //���������� ������� �� ������������� �������� ������ (���������� �������)
    sort(Adj_Deg.begin(), Adj_Deg.end(), sort_descend_lastcolumn);

    /* ����� �� �����
    cout << "adj_deg matrix after sort:\n";
    for (i=0; i<nV; i++)
    {
        for ( j=0; j<nV+2; j++)
            cout << Adj_Deg[i][j] << " ";
        cout << endl;
    }
    */


    // ������� ��������� ������� - �����. ������� ������������� ������� G.
    vector < vector<int> > G(nV, vector<int>(nV+3,-1));
    for (i=0; i<nV; i++)
        for (j=0; j<nV+2; j++)
            G[i][j] = Adj_Deg[i][j];

    G[0][nV+2] = 0;


    //���������
    for (i=1; i<nV; i++)
    {
        //����� ��������� ������� �� ��������� � ������������ ���������
        color = 0;
        for (j=1; j<nV+1; j++)
            if (G[i][j] == 1) //������� ������ � i-�
            {
                //j - ����� ������� (������ � ����� �������), � ������� ������� i ������
                //������ ��������� j-� ������� � ������� G:
                k = -1;
                for (int ii=0; ii<nV; ii++)
                    if (G[ii][0] == j-1)
                    {
                        k = ii; // ��� ����� ������ � ������� G, ��������������� ������� j
                        break;
                    }

                if (G[k][nV+2] != -1)
                    color += 1;
            }

        G[i][nV+2] = color;
    }


    // ���������
    vector < vector<int> > Colors(nV, vector<int>(2,0));
    for (i=0; i<nV; i++)
    {
        Colors[i][0] = G[i][0];
        Colors[i][1] = G[i][nV+2];
    }
    sort(Colors.begin(), Colors.end(), sort_firstcolumn);

    cout << "Result. Vertice and their colors:" << endl;
    for (i=0; i<nV; i++)
        cout << Colors[i][0] << " ";
    cout << endl;
    for (i=0; i<nV; i++)
        cout << Colors[i][1] << " ";
    cout << endl;



    return 0;
}
