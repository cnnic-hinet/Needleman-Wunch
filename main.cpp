#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define N 1000
const char* G1 = "Gene1_Seq.txt";
const char* G2 = "Gene2_Seq.txt";

int OPT[N][N] = {0};
int MARK[N][N] = {0};

using namespace std;
int Weight(int,int);
int Max(int,int,int);
void Find(string &a1,string &a2)
{
    int m = a1.length();
    int n = a2.length();
    for(int i=0;i<=m;i++)
    {
        OPT[i][0] = -3 * i;
    }
    for(int j=0;j<=n;j++)
    {
        OPT[0][j] = -3 * j;
    }
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            int max = Max(OPT[i-1][j-1]+Weight(a1[i-1],a2[j-1]),OPT[i][j-1]-3,OPT[i-1][j]-3);
            if(max == OPT[i-1][j-1]+Weight(a1[i-1],a2[j-1]))
            {
                OPT[i][j] = OPT[i-1][j-1]+Weight(a1[i-1],a2[j-1]);
                MARK[i][j] = -2;
            }
            else if(max == OPT[i][j-1]-3)
            {
                OPT[i][j] = OPT[i][j-1]-3;
                MARK[i][j] = -3;
            }
            else
            {
                OPT[i][j] = OPT[i-1][j]-3;
                MARK[i][j] = -1;
            }
        }
    }
}

int Max(int a,int b,int c)
{
    if(a>=b && a >=c)
        return a;
    else if(b>=a && b>=c)
        return b;
    else
        return c;
}
int Weight(int a,int b)
{
    if (a == b)
        return 1;
    else
        return (-1);
}
void Change(int MARK[][N],string &a1,string &a2,int i,int j)
{
    if (i == 0 || j == 0)
    {
        return;
    }
    if (MARK[i][j] == -2)
    {
        Change(MARK,a1,a2,i-1,j-1);
    }
    else if (MARK[i][j] == -1)
    {
        a2.insert(j-1,"_");
        Change(MARK,a1,a2,i-1,j);
    }
    else
    {
        a1.insert(i-1,"_");
        Change(MARK,a1,a2,i,j-1);
    }
}

int main()
{
    ifstream fin;
    string a1,a2;
    fin.open(G1);
    static char line[1024];
    FILE *fp;
    fp = fopen(G1, "r");
    assert(fp != NULL);
    while (!feof(fp)) {
        fscanf(fp, "%s", line);
        a1.append(line);
    }

    fclose(fp);
    fp = fopen(G2,"r");
    assert(fp != NULL);
    while (!feof(fp)){
        fscanf(fp,"%s", line);
        a2.append(line);
    }
    fclose(fp);
    Find(a1,a2);
    cout << OPT[a1.length()][a2.length()]<<endl;
    Change(MARK,a1,a2,a1.length(),a2.length());
    cout << a1<< endl << a2<<endl;
    return 0;
}

