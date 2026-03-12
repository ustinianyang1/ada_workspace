#include<iostream>
#include<vector>
#include<queue>
#include<string>
using namespace std;

void test(vector<string>&, vector<string>&, vector<vector<int>>&, vector<vector<int>>&);

vector<string> men, women;
vector<vector<int>> m_preferences, w_preferences;
vector<vector<int>> w_rank;
vector<int> m_partner, w_partner;
queue<int> m_free;
vector<int> m_next;

void init(int n)
{
    men.resize(n), women.resize(n);
    m_preferences.assign(n, vector<int>(n));
    w_preferences.assign(n, vector<int>(n));
    test(men, women, m_preferences, w_preferences);
    w_rank.assign(n, vector<int>(n));
    m_partner.assign(n, -1), w_partner.assign(n, -1);
    while(!m_free.empty()) m_free.pop();
    for(int i = 0; i < n; i++)
        m_free.push(i);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            w_rank[i][w_preferences[i][j]] = j;
    m_next.resize(n, 0);
}

void gale_shapley(int n)
{
    init(n);
    while(!m_free.empty())
    {
        int m = m_free.front();
        m_free.pop();
        if (m_next[m] < n) {
            int w = m_preferences[m][m_next[m]];
            m_next[m]++;

            if (w_partner[w] == -1) {
                m_partner[m] = w;
                w_partner[w] = m;
            } else {
                int m_current = w_partner[w];
                if (w_rank[w][m] < w_rank[w][m_current]) {
                    m_partner[m] = w;
                    w_partner[w] = m;
                    m_partner[m_current] = -1;
                    m_free.push(m_current);
                } else {
                    m_free.push(m);
                }
            }
        }
    }
}

void test(vector<string>& men, vector<string>& women, vector<vector<int>>& m_preferences, vector<vector<int>>& w_preferences)
{
    men = {"zhangsan", "lisi", "wangwu", "zhaoliu"};
    women = {"bomei", "taidi", "songshi", "dubin"};
    m_preferences = {
        {0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3}
    };
    w_preferences = {
        {0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3}
    };
}

int main()
{
    int n = 4;
    gale_shapley(n);
    cout << "Stable Matching Results:" << endl;
    for (int i = 0; i < n; i++)
        cout << men[i] << " is matched with " << women[m_partner[i]] << endl;
    return 0;
}