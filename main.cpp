/*
 Yanzhen Wang
 cis 306 program 1
 9/29/2016
 */

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<iomanip>
#include<algorithm>
#include<iterator>

using namespace std;
int const MAX =50;

void indentifierTable(vector<string> &id,vector<string> word,vector<string> number)
{
    string keywords[27] ={"else","if","int","return","void","while","+", "-","=", "*","/","<","<=",">",">=","==","!=",";",",","(",")", "[","]","{","}","/*","*/"};
    vector<string> temp;
    int i, j, isfound = 0;
    for(i = 0; i < word.size(); i++)
    {
        isfound = 0;
        for(j=0; j< 27;j++)
            if(word[i] == keywords[j])
            {
                isfound = 1;
                break;
            }
        if(!isfound)
            temp.push_back(word[i]);
    }
    for(i = 0; i < temp.size(); i++)
    {
        isfound = 0;
        for(j=0; j< number.size();j++)
            if(temp[i] == number[j])
            {
                isfound = 1;
                break;
            }
        if(!isfound)
            id.push_back(temp[i]);
    }
    sort(id.begin(), id.end());
    vector<string>::iterator it;
    it = std::unique (id.begin(), id.end());
    id.resize( std::distance(id.begin(),it) );
}
void numberTable(vector<string> & number,vector<string> word)
{
    for(int j =0 ; j<word.size(); j++)
    {
        if(word[j][0] >=48 && word[j][0] <=57)
            number.push_back(word[j]);
    }
    vector<string>::iterator it;
    it = std::unique (number.begin(), number.end());
    number.resize( std::distance(number.begin(),it) );
    
}

void tokenTable(vector<string> id,vector<string> number,vector<string> toKen,string sentence[MAX])
{
    ofstream out;
    out.open("output.txt");
    string keywords[27] ={"else","if","int","return","void","while","+", "-","=", "*","/","<","<=",">",">=","==","!=",";",",","(",")", "[","]","{","}","/*","*/"};
    vector<string> Class;
    vector<int> index;
    out<<"Table 1 - KEYWORD"<<endl;
    out<<"Keyword"<<"  "<<"Index"<<endl;
    out<<"--------------------------"<<endl;
    for(int i =0; i < 27; i++)
        out<<setw(7)<<left<<keywords[i]<<setw(4)<<left
        <<"|"<<i+1<<endl;
    out<<endl;
    out<<"Table 2 - INDENTIFIER"<<endl;
    out<<"ID"<<"      "<<"Index"<<endl;
    out<<"--------------------------"<<endl;
    for(int l =0; l < id.size(); l++)
        out<<setw(6)<<left<<id[l]<<setw(4)<<left
        <<"|"<<l+1<<endl;
    out<<endl;
    out<<"Table 3 - NUMBER"<<endl;
    out<<"Num"<<"     "<<"Index"<<endl;
    out<<"--------------------------"<<endl;
    for(int j =0; j < number.size(); j++)
        out<<setw(6)<<left<<number[j]<<setw(4)<<left
        <<"|"<<j+1<<endl;
    out<<endl;
    out<<"Table 4 - TOKEN"<<endl;
    out<<"Token    class  index"<<endl;
    out<<"--------------------------"<<endl;
    
    for(int n = 0; n< toKen.size(); n++)
    {
        for(int m =0; m < 27; m++)
        {
            if(toKen[n] == keywords[m])
            {
                Class.push_back("kw");
                index.push_back(m+1);
            }
        }
        for(int u =0; u < id.size(); u++)
        {
            if(toKen[n] == id[u])
            {
                Class.push_back("id");
                index.push_back(u+1);
            }
        }
        for(int t =0; t< number.size(); t++)
        {
            if(toKen[n] ==number[t])
            {
                Class.push_back("num");
                index.push_back(t+1);
            }
        }
    }
    for(int j=0; j<toKen.size(); j++)
        out<<setw(7)<<left<<toKen[j]<<setw(3)<<left
        <<"|"<<setw(4)<<left<<Class[j]<<setw(4)<<left
        <<"|"<<index[j]<<endl;
    out<<endl;
    out<<"Output without Comments"<<endl;
    for(int w =0; w<MAX; w++)
    {
        if(sentence[w][0] !='/')
            out<<sentence[w];
        out<<endl;
    }
}
void createtoken (vector<string>& word, string sentence[27])
{
    for(int i =0; i<MAX;i++)
    {
        if(sentence[i][0] !='/')
        {
            istringstream iss(sentence[i]);
            copy(istream_iterator<string>(iss),
                 istream_iterator<string>(),
                 back_inserter(word));	
        }
    }
}

int main()
{
    ifstream inf;
    string line[MAX];
    vector<string> token;
    vector<string> num;
    vector<string> identifier;
    inf.open("input.txt");
    while(inf.good())
    {
        for(int i =0; i < MAX; i++)  
            getline(inf,line[i]);	
    }
    inf.close();
    createtoken(token,line);
    numberTable(num,token);
    indentifierTable(identifier,token,num);
    tokenTable(identifier,num,token,line);
    system("pause");
    return 0;
}
