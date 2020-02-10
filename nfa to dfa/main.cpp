#include<iostream>
#include<vector>
using namespace std;
int member(vector<int> s, int val)
{
    for(int i=0; i<s.size();i++)
    {
        if(s[i]==val)
            return 1;
    }
    return 0;
}
void display_nfa(vector<vector<vector<int> > > nfa,int f)
{
    cout<<"\nStates \t0\t1\n";
    for (int i = 0; i < nfa.size(); i++)
    {
        for (int j = 0; j < nfa[i].size(); j++)
        {
            if(member(nfa[i][0],f) && j==0)
                cout<<"*";
            cout<<"{ ";
            for(int k=0;k<nfa[i][j].size();k++)
            {
                if(nfa[i][j][k]==-1)
                    cout<<"-";
                else if(k==nfa[i][j].size()-1)
                    cout<<nfa[i][j][k];
                else
                    cout << nfa[i][j][k] << ",";
            }
            cout<<" }\t";
        }
        cout << endl;
    }
}
void display_dfa(vector<vector<vector<int> > > dfa,int f)
{
    cout<<"\nStates \t0\t1\n";
    for (int i = 0; i < dfa.size(); i++)
    {
        for (int j = 0; j < dfa[i].size(); j++)
        {
            if(member(dfa[i][0],f) && j==0)
                cout<<"*";
            for(int k=0;k<dfa[i][j].size();k++)
            {
                cout<<dfa[i][j][k];
            }
            cout<<"\t";
        }
        cout << endl;
    }
}
int member_state(vector<vector<vector<int> > > dfa, vector<int> val)
{
    for(int i=0; i<dfa.size();i++)
    {
        if(dfa[i][0]==val)
            return 1;
    }
    return 0;
}
vector<int> union_set(vector<int> s1,vector<int> s2)
{
    vector<int> s3;
    s3=s1;
    for(int i=0; i<s2.size();i++)
    {
        if(!member(s3,s2[i]) && !(s2[i]==-1))
        {
            s3.resize(s3.size()+1);
            s3[s3.size()-1]=s2[i];
        }
    }
    return s3;
}
vector<int> set_resolution(vector<vector<vector<int> > > nfa, vector<int> state, int pos)
{
    vector<int> result;
    if(state.size()==1 && state[0]==-1)
    {
        result.resize(1);
        result[0]=-1;
        return result;
    }
    for(int i=0; i<state.size();i++)
    {
        result=union_set(result,nfa[state[i]][pos]);
    }
    return result;
}
int main()
{
    int n,f;
    cout<<"Enter the total number of states: ";
    cin>>n;
    vector<vector< vector<int> > > nfa,dfa;
    nfa.resize(n);
    for(int i=0;i<n;i++)
    {
        nfa[i].resize(3);
        for(int j=0;j<nfa[i].size();j++)
        {
            nfa[i][j].resize(1);
        }
        nfa[i][0][0]=i;
    }
    cout<<"State 0 is considered as initial state\n";
    cout<<"Enter the final state: ";
    cin>>f;
    for(int i=0;i<n;i++)
    {
        int m,n;
        cout<<"For state "<<i<<":\n";
        cout<<"Enter the number of possible transitions for 0: ";
        cin>>m;
        if(m!=0)
        {
            nfa[i][1].resize(m);
            cout<<"Enter states that can be traversed at occurrence of 0: ";
            for(int j=0;j<m;j++)
            {
                int t;
                cin>>t;
                nfa[i][1][j]=t;
            }
        }
        else
        {
            nfa[i][1].resize(1);
            nfa[i][1][0]=-1;
        }
        cout<<"Enter the number of possible transitions for 1: ";
        cin>>n;
        if(n!=0)
        {
            nfa[i][2].resize(n);
            cout<<"Enter states that can be traversed at occurrence of 1: ";
            for(int j=0;j<n;j++)
            {
                int t;
                cin>>t;
                nfa[i][2][j]=t;
            }
        }
        else
        {
            nfa[i][2].resize(1);
            nfa[i][2][0]=-1;
        }
    }
    //cout<<nfa[0][2][0]<<"\n";
    cout<<"Entered nfa is as follows:";
    display_nfa(nfa,f);
    dfa.resize(1);
    dfa[0].resize(3);
    dfa[0]=nfa[0];
    for(int i=0;i<dfa.size();i++)
    {
        if(!member_state(dfa, dfa[i][1]))
        {
            dfa.resize(dfa.size()+1);
            dfa[dfa.size()-1].resize(3);
            dfa[dfa.size()-1][0]=dfa[i][1];
        }
        if(!member_state(dfa, dfa[i][2]))
        {
            dfa.resize(dfa.size()+1);
            dfa[dfa.size()-1].resize(3);
            dfa[dfa.size()-1][0]=dfa[i][2];
        }
        if(i>0)
        {
            dfa[i][1]=set_resolution(nfa, dfa[i][0],1);
            dfa[i][2]=set_resolution(nfa, dfa[i][0],2);
        }
    }
    cout<<"\nThe corresponding dfa is as follows(-1 represents rejections state):";
    display_dfa(dfa,f);
    return 0;
}
