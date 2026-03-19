#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;
void test1(vector<string> &, vector<string> &, vector<vector<int>> &, vector<vector<int>> &);
void test2(vector<string> &, vector<string> &, vector<vector<int>> &, vector<vector<int>> &);

vector<string> men, women;
vector<vector<int>> m_preferences, w_preferences;
vector<vector<int>> w_rank;
vector<int> m_partner, w_partner;
queue<int> m_free;
vector<int> m_next;

bool is_perfect_matching(int n)
{
    if (m_partner.size() != n || w_partner.size() != n)
        return false;
    vector<int> seen_w(n, 0), seen_m(n, 0); // 检查每个女人和男人是否被匹配多次
    for (int m = 0; m < n; ++m)
    {
        int w = m_partner[m];
        if (w < 0 || w >= n)
            return false;
        if (w_partner[w] != m)
            return false;
        if (++seen_w[w] > 1)
            return false;
    }
    for (int w = 0; w < n; ++w)
    {
        int m = w_partner[w];
        if (m < 0 || m >= n)
            return false;
        if (m_partner[m] != w)
            return false;
        if (++seen_m[m] > 1)
            return false;
    }
    return true;
}

void init(int n, int test_case)
{
    men.resize(n), women.resize(n);
    m_preferences.assign(n, vector<int>(n));
    w_preferences.assign(n, vector<int>(n));
    test_case == 1 ? test1(men, women, m_preferences, w_preferences) : test2(men, women, m_preferences, w_preferences);
    w_rank.assign(n, vector<int>(n));
    m_partner.assign(n, -1), w_partner.assign(n, -1);
    while (!m_free.empty())
        m_free.pop();
    for (int i = 0; i < n; i++)
        m_free.push(i);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            w_rank[i][w_preferences[i][j]] = j;
    m_next.resize(n, 0);
}

void gale_shapley(int n, int test_case)
{
    init(n, test_case);
    while (!m_free.empty())
    {
        int m = m_free.front();
        m_free.pop();
        if (m_next[m] < n)
        {
            int w = m_preferences[m][m_next[m]];
            m_next[m]++;
            if (w_partner[w] == -1)
                m_partner[m] = w, w_partner[w] = m;
            else
            {
                int m_current = w_partner[w];
                if (w_rank[w][m] < w_rank[w][m_current])
                {
                    m_partner[m] = w, w_partner[w] = m;
                    m_partner[m_current] = -1, m_free.push(m_current);
                }
                else
                    m_free.push(m);
            }
        }
    }
}

void test1(vector<string> &men, vector<string> &women, vector<vector<int>> &m_preferences,
           vector<vector<int>> &w_preferences)
{
    men = {"zhangsan", "lisi", "wangwu", "zhaoliu"};
    women = {"bomei", "taidi", "songshi", "dubin"};
    m_preferences = {{0, 1, 2, 3}, {1, 0, 2, 3}, {2, 1, 0, 3}, {3, 2, 1, 0}};
    w_preferences = {{0, 1, 2, 3}, {1, 0, 2, 3}, {2, 1, 0, 3}, {3, 2, 1, 0}};
}

void test2(vector<string> &men, vector<string> &women, vector<vector<int>> &m_preferences,
           vector<vector<int>> &w_preferences)
{
    men = {"A", "B", "C", "D", "E"};
    women = {"1", "2", "3", "4", "5"};
    m_preferences = {
        {0, 1, 2, 4, 3}, // A: 1,2,3,5,4
        {2, 0, 1, 3, 4}, // B: 3,1,2,4,5
        {3, 2, 0, 4, 1}, // C: 4,3,1,5,2
        {1, 3, 4, 2, 0}, // D: 2,4,5,3,1
        {4, 1, 2, 0, 3}  // E: 5,2,3,1,4
    };
    w_preferences = {
        {1, 0, 3, 2, 4}, // 1: B,A,D,C,E
        {4, 1, 0, 3, 2}, // 2: E,B,A,D,C
        {0, 2, 4, 1, 3}, // 3: A,C,E,B,D
        {2, 1, 3, 4, 0}, // 4: C,B,D,E,A
        {3, 4, 0, 1, 2}  // 5: D,E,A,B,C
    };
}

int main()
{
    const int test_cases[] = {1, 2};
    const int sizes[] = {4, 5};

    for (int idx = 0; idx < 2; ++idx)
    {
        int test_case = test_cases[idx];
        int n = sizes[idx];

        cout << "------------------------------" << endl;
        cout << "Test Case " << test_case << " (n = " << n << ")" << endl;
        cout << "------------------------------" << endl;

        gale_shapley(n, test_case);

        cout << "Stable Matching Results:" << endl;
        for (int i = 0; i < n; i++)
            cout << men[i] << " is matched with " << women[m_partner[i]] << endl;
        cout << "Perfect matching: " << (is_perfect_matching(n) ? "Yes" : "No") << endl;
        cout << endl;
    }
    return 0;
}