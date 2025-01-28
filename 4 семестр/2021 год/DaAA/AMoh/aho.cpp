//
// Created by Dmitriy on 02.06.2021.
//

#include <vector>
#include <map>
#include <queue>
#include <string>
#include <list>
#include <cstring>
#include <cstdio>
#include <iostream>

using namespace std;

struct AhoCorasick
{
    map<int, map <char, int> > go_to;
    vector<int> failure;
    map<int, vector <int> > output;
    vector<list<int> > positions;

    void create_goto(const vector<string> &patterns) {

        positions.resize(patterns.size());

        int new_state = 0;
        for (int i = 0; i < patterns.size(); i++)
        {
            int state = 0, j;
            for (j = 0; j < patterns[i].size() && go_to[state].count(patterns[i][j]) >= 1; j++)
                state = go_to[state][patterns[i][j]];

            for (int k = j; k < patterns[i].size(); k++)
            {
                go_to[state][patterns[i][k]] = ++new_state;
                state = new_state;
            }

            if (output.find(state) == output.end())
                output[state] = vector <int> (1, i);
            else
                output[state].push_back(i);
        }

        failure.resize(new_state + 1, 0);
        for (char i = ' '; i <= '~'; i++)
            if (go_to[0].count(i) == 0)
                go_to[0][i] = 0;

        create_failure();
    }

    void create_failure() {

        queue<int> q;
        int current, state;
        for(auto & itr : go_to[0])
        {
            if (itr.second != 0)
            {
                q.push (itr.second);
                failure[itr.second] = 0;
            }
        }

        while (!q.empty())
        {
            current = q.front();
            q.pop();
            state = failure[current];

            for (auto itr = go_to[current].begin(); itr != go_to[current].end(); itr++)
            {
                if (go_to[current].count((*itr).first) != 0)
                {
                    q.push((*itr).second);
                    state = failure[current];
                    while (go_to[state].count((*itr).first) == 0)
                        state = failure[state];
                    failure[(*itr).second] = go_to [state][(*itr).first];
                    output[(*itr).second].insert(output[(*itr).second].end(), output[failure[(*itr).second]].begin(),
                                                 output[failure[(*itr).second]].end());
                }
            }
        }
    }

    void find_matches(const string &T)
    {
        int state = 0, t;
        for (int i = 0; i < T.size(); i++)
        {
            while (go_to[state].count(T[i]) == 0)
                state = failure[state];

            state = go_to [state][T[i]];
            if (output.count(state) > 0)
            {
                t = output[state].size();
                vector <int> tmp = output[state];
                for (int j = 0; j < t; j++)
                    positions[tmp[j]].push_back(i);
            }
        }
    }
};

int main ()
{

    int n, i;
    char s[200005];
    char t[100005];
    while (scanf("%d", &n) == 1)
    {
        getchar();
        AhoCorasick AC;
        vector<string> queries(n);
        for (i = 0; i < n; i++)
        {
            gets(t);
            queries[i] = string(t);
        }

        gets(s);
        AC.create_goto(queries);
        AC.find_matches(string(s));

        for (i = 0; i < AC.positions.size(); i++)
        {
            for (auto itr = AC.positions[i].begin(); itr != AC.positions[i].end(); itr++)
                printf("%lu ", *itr-(queries[i].size()-1));
            printf("\n");
        }
    }
    return 0;

}