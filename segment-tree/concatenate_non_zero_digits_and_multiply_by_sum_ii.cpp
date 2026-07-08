#include<bits/stdc++.h>
using namespace std;

#define ll long long
constexpr int MOD = 1e9 + 7;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

namespace IO {
    namespace Input {
        // Basic types
        void read(bool& x) { cin >> x; }
        void read(char& x) { cin >> x; }
        void read(int& x) { cin >> x; }
        void read(unsigned int& x) { cin >> x; }
        void read(long int& x) { cin >> x; }
        void read(unsigned long& x) { cin >> x; }
        void read(long long int& x) { cin >> x; }
        void read(unsigned long long& x) { cin >> x; }
        void read(float& x) { cin >> x; }
        void read(double& x) { cin >> x; }
        void read(long double& x) { cin >> x; }
        
        // String with whitespace handling
        void read(string& x) { 
            cin >> ws; 
            getline(cin, x); 
        }
        
        // Linked list
        void read(ListNode*& head) {
            int n; 
            cin >> n;
            if (n == 0) { 
                head = nullptr; 
                return; 
            }
            vector<int> values(n);
            for (int i = 0; i < n; i++) { 
                cin >> values[i]; 
            }
            head = new ListNode(values[0]);
            ListNode* current = head;
            for (int i = 1; i < n; i++) {
                current->next = new ListNode(values[i]);
                current = current->next;
            }
        }
        
        // Binary tree (level-order traversal format)
        void read(TreeNode*& root) {
            int n; 
            cin >> n;
            if (n == 0) { 
                root = nullptr; 
                return;
            }
            vector<string> values(n);
            for (int i = 0; i < n; i++) {
                cin >> values[i]; 
            }
            if (values[0] == "null") {
                root = nullptr; 
                return;
            }
            root = new TreeNode(stoi(values[0]));
            queue<TreeNode*> q;
            q.push(root);
            int i = 1;
            while (!q.empty() && i < n) {
                TreeNode* node = q.front();
                q.pop();
                if (i < n) {
                    if (values[i] != "null") {
                        node->left = new TreeNode(stoi(values[i]));
                        q.push(node->left);
                    }
                    i++;
                }
                if (i < n) {
                    if (values[i] != "null") {
                        node->right = new TreeNode(stoi(values[i]));
                        q.push(node->right);
                    }
                    i++;
                }
            }
        }

        template <typename T> void read(vector<T>& x);
        
        // Vector
        template <typename T>
        void read(vector<T>& x) {
            int n;
            cin >> n;
            x.resize(n);
            for (int i = 0; i < n; i++) {
                read(x[i]);
            }
        }
    } // namespace Input
    
    namespace Output {
        // Basic types
        void write(bool x) { cout << (x ? "True" : "False"); }
        void write(char x) { cout << "\"" << x << "\""; }
        void write(int x) { cout << x; }
        void write(unsigned int x) { cout << x; }
        void write(long int x) { cout << x; }
        void write(unsigned long x) { cout << x; }
        void write(long long int x) { cout << x; }
        void write(unsigned long long x) { cout << x; }
        void write(float x) { cout << x; }
        void write(double x) { cout << x; }
        void write(long double x) { cout << x; }
        void write(string x) { cout << "\"" << x << "\""; }
        void write(const char* x) { cout << "\"" << x << "\""; }
        
        // Linked list
        void write(ListNode* head) {
            cout << "[";
            bool first = true;
            while (head) {
                if (!first) cout << ",";
                first = false;
                cout << head->val;
                head = head->next;
            }
            cout << "]";
        }
        
        // Binary tree (level-order output)
        void write(TreeNode* root) {
            if (!root) {
                cout << "[]";
                return;
            }
            cout << "[";
            queue<TreeNode*> q;
            q.push(root);
            bool first = true;
            while (!q.empty()) {
                int levelSize = q.size();
                bool hasNextLevel = false;
                for (int i = 0; i < levelSize; i++) {
                    TreeNode* node = q.front();
                    q.pop();
                    if (!first) cout << ",";
                    first = false;
                    if (node) {
                        cout << node->val;
                        q.push(node->left);
                        q.push(node->right);
                        if (node->left || node->right) hasNextLevel = true;
                    } else {
                        cout << "null";
                    }
                }
                if (!hasNextLevel) break;
            }
            cout << "]";
        }
        
        template <typename T> void write(const vector<T>& x);
        
        // Vector
        template <typename T>
        void write(const vector<T>& x) {
            cout << "[";
            int n = x.size();
            for (int i = 0; i < n; i++) {
                write(x[i]);
                if (i < n - 1) cout << ",";
            }
            cout << "]";
        }
    } // namespace Output
    
    template <typename T>
    void input(T& x) {
        Input::read(x);
    }
    
    template <typename T>
    void output(T x) {
        Output::write(x);
    }
} 

using namespace IO;

template<typename Node, typename Update>
struct SegTree {
    vector<Node> tree;
    int n;
    int s;

    SegTree(int n, vector<long long>& a) {
        this->n = n;
        s = 1;
        while (s < 2 * n) s <<= 1;
        tree.resize(2 * s - 1, Node());
        _build(a, 0, n - 1, 0);
    }

    void _build(vector<long long>& a, int l, int r, int idx) {
        if (l == r) { tree[idx] = Node(a[l]); return; }
        int m = (l + r) / 2;
        _build(a, l, m, 2 * idx + 1);
        _build(a, m + 1, r, 2 * idx + 2);
        tree[idx].merge(tree[2 * idx + 1], tree[2 * idx + 2]);
    }

    // void _update(int l, int r, int idx, int pos, Update& u) {
    //     if (l == r) { u.apply(tree[idx]); return; }
    //     int m = (l + r) / 2;
    //     if (pos <= m) _update(l, m, 2 * idx + 1, pos, u);
    //     else _update(m + 1, r, 2 * idx + 2, pos, u);
    //     tree[idx].merge(tree[2 * idx + 1], tree[2 * idx + 2]);
    // }

    Node _query(int l, int r, int idx, int ql, int qr) {
        if (l > qr || r < ql) return Node();
        if (l >= ql && r <= qr) return tree[idx];
        int m = (l + r) / 2;
        Node left = _query(l, m, 2 * idx + 1, ql, qr);
        Node right = _query(m + 1, r, 2 * idx + 2, ql, qr);
        Node ans;
        ans.merge(left, right);
        return ans;
    }

    // void make_update(int pos, long long val) {
    //     Update u(val);
    //     _update(0, n - 1, 0, pos, u);
    // }

    Node make_query(int l, int r) {
        return _query(0, n - 1, 0, l, r);
    }
};
vector<ll> pow10;

struct Node1 {
    ll x;    // concatenation of only the NON-ZERO digits, mod MOD
    ll sum;  // plain sum of digits (zeros contribute 0 either way)
    int len; // count of NON-ZERO digits contributed to x (the shift width)
    ll ans;

    Node1() { x = 0; sum = 0; len = 0; ans = 0; }

    Node1(ll v) {
        if (v == 0) {
            // zero digit: adds nothing to x, zero width, sum += 0
            x = 0; len = 0; sum = 0;
        } else {
            x = v; len = 1; sum = v;
        }
        ans = (x * sum) % MOD;
    }

    void merge(Node1& l, Node1& r) {
        len = l.len + r.len;
        x = (l.x * pow10[r.len] + r.x) % MOD;
        sum = l.sum + r.sum;          // fits comfortably, digits are 0-9
        ans = (x * (sum % MOD)) % MOD;
    }
};

struct Update1 {
    long long val;
    Update1(long long v) { val = v; }
    void apply(Node1& a) {  }
};

class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n = s.length();
        pow10.resize(n + 1);
        pow10[0] = 1;
        for (int i = 1; i <= n; i++)
            pow10[i] = (pow10[i - 1] * 10) % MOD;

        vector<ll> a;
        for (auto c : s) a.push_back(c - '0');

        vector<int> res;
        SegTree<Node1, Update1> st(n, a);
        for (auto v : queries) {
            int l = v[0];
            int r = v[1];

            int ans = st.make_query(l, r).ans % MOD;
            res.push_back(ans);
        }

        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    input(t);
    while (t--) {
        string s;
        input(s);
        vector<vector<int>> queries;
        input(queries);
        Solution obj;
        output(obj.sumAndMultiply(s,queries));
        cout << endl;
    }
    
    return 0;
}