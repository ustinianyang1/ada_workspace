#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;

class MinHeap
{
    public:
    vector<int> nodes;
    MinHeap() {nodes.push_back(0);}

    void bubble_up(int i)
    {
        if(nodes.size() == 1)
            return;
        while(i > 1 && nodes[i] < nodes[i>>1])
        {
            swap(nodes[i], nodes[i>>1]);
            i >>= 1;
        }
    }

    void bubble_down(int i)
    {
        if(nodes.size() == 1)
            return;
        while(true)
        {
            int smallest = i, left = i<<1, right = i<<1|1;
            if(left < nodes.size() && nodes[left] < nodes[smallest])
                smallest = left;
            if(right < nodes.size() && nodes[right] < nodes[smallest])
                smallest = right;
            if(smallest == i)
                return;
            swap(nodes[i], nodes[smallest]);
            i = smallest;
        }
    }

    void push(int x)
    {
        nodes.push_back(x);
        bubble_up(nodes.size() - 1);
    }

    void pop()
    {
        if(nodes.size() == 1)
            return;
        swap(nodes[1], nodes.back());
        nodes.pop_back();
        bubble_down(1);
    }
};

int main()
{
    MinHeap minheap;
    for(int i = 1; i <= 20; i++)
        minheap.push(i);
    for(int i = 20; i >= 1; i--)
    {
        cout << minheap.nodes[1] << " ";
        minheap.pop();
    }
    return 0;
}