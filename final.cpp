#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

struct Node {
    int rating;
    string name;
    long long hp;
    Node* left;
    Node* right;
    Node(int r, string n, long long h) {
        rating = r; name = n; hp = h; left = right = nullptr;
    }
};

Node* root = nullptr;

/* BST insert */
Node* insert(Node* node, int r, string n, long long h, bool &dup) {
    if (!node) return new Node(r, n, h);
    if (r == node->rating) { dup = true; return node; }
    if (r < node->rating) node->left = insert(node->left, r, n, h, dup);
    else node->right = insert(node->right, r, n, h, dup);
    return node;
}

/* BST search */
Node* search(Node* node, int r) {
    if (!node) return nullptr;
    if (node->rating == r) return node;
    if (r < node->rating) return search(node->left, r);
    return search(node->right, r);
}

/* Find min node */
Node* findMin(Node* node) {
    while (node && node->left) node = node->left;
    return node;
}

/* BST remove */
Node* remove(Node* node, int r, bool &found) {
    if (!node) return nullptr;
    if (r < node->rating) node->left = remove(node->left, r, found);
    else if (r > node->rating) node->right = remove(node->right, r, found);
    else {
        found = true;
        if (!node->left && !node->right) { delete node; return nullptr; }
        if (!node->left) { Node* t = node->right; delete node; return t; }
        if (!node->right) { Node* t = node->left; delete node; return t; }
        Node* succ = findMin(node->right);
        node->rating = succ->rating;
        node->name = succ->name;
        node->hp = succ->hp;
        node->right = remove(node->right, succ->rating, found);
    }
    return node;
}

/* NEXT (successor) */
Node* nextNode(Node* node, int x) {
    Node* ans = nullptr;
    while (node) {
        if (node->rating > x) { ans = node; node = node->left; }
        else node = node->right;
    }
    return ans;
}

/* PREV (predecessor) */
Node* prevNode(Node* node, int x) {
    Node* ans = nullptr;
    while (node) {
        if (node->rating < x) { ans = node; node = node->right; }
        else node = node->left;
    }
    return ans;
}

/* RANGE PRINT */
void rangePrint(Node* node, int L, int R, bool &any) {
    if (!node) return;
    if (node->rating > L) rangePrint(node->left, L, R, any);
    if (node->rating >= L && node->rating <= R) { cout << node->rating << " " << node->name << " " << node->hp << "\n"; any=true; }
    if (node->rating < R) rangePrint(node->right, L, R, any);
}

/* RANK COUNT */
int rankCount(Node* node, int x) {
    if (!node) return 0;
    if (node->rating >= x) return rankCount(node->left, x);
    return 1 + rankCount(node->left, x) + rankCount(node->right, x);
}

/* KTH smallest */
void kth(Node* node, int &k, bool &done) {
    if (!node || done) return;
    kth(node->left, k, done);
    if (--k == 0 && !done) { cout << node->rating << " " << node->name << " " << node->hp << "\n"; done = true; return; }
    kth(node->right, k, done);
}

/* TREE HEIGHT */
int height(Node* node) {
    if (!node) return -1;
    return 1 + max(height(node->left), height(node->right));
}

/* LEAF COUNT */
int leaves(Node* node) {
    if (!node) return 0;
    if (!node->left && !node->right) return 1;
    return leaves(node->left) + leaves(node->right);
}

/* DISTANCE BETWEEN TWO NODES */
int distance(Node* node, int a, int b) {
    if (!node) return -1;
    if (node->rating > a && node->rating > b) return distance(node->left, a, b);
    if (node->rating < a && node->rating < b) return distance(node->right, a, b);
    Node* cur = node; int d1=0,d2=0;
    while (cur->rating != a) { d1++; cur = (a < cur->rating)? cur->left : cur->right; }
    cur = node;
    while (cur->rating != b) { d2++; cur = (b < cur->rating)? cur->left : cur->right; }
    return d1 + d2;
}

/* MATCH */
Node* match(Node* node, int x) {
    Node* p = prevNode(node, x);
    Node* s = nextNode(node, x);
    if (!p && !s) return nullptr;
    if (!p) return s;
    if (!s) return p;
    return (x - p->rating <= s->rating - x)? p : s;
}

/* ---------- MAIN ---------- */

int main() {
    freopen("input.txt","r",stdin);   // read input from file
    freopen("output.txt","w",stdout); // write output to file

    int Q; cin >> Q;
    while(Q--) {
        string cmd; cin >> cmd;

        if(cmd=="JOIN") {
            int r; string n; long long h; cin>>r>>n>>h;
            bool dup=false; root=insert(root,r,n,h,dup);
            cout << (dup?"DUPLICATE\n":"JOINED\n");
        }
        else if(cmd=="LEAVE") {
            int r; cin>>r; bool found=false; root=remove(root,r,found);
            cout << (found?"LEFT\n":"NOT FOUND\n");
        }
        else if(cmd=="STATUS") {
            int r; cin>>r; Node* n=search(root,r);
            if(!n) cout<<"NOT FOUND\n";
            else cout<<n->rating<<" "<<n->name<<" "<<n->hp<<"\n";
        }
        else if(cmd=="DAMAGE") {
            int r; long long a; cin>>r>>a; Node* n=search(root,r);
            if(!n) cout<<"NOT FOUND\n";
            else { n->hp=max(0LL,n->hp-a); cout<<"DAMAGED "<<n->hp<<"\n"; }
        }
        else if(cmd=="HEAL") {
            int r; long long a; cin>>r>>a; Node* n=search(root,r);
            if(!n) cout<<"NOT FOUND\n";
            else { n->hp+=a; cout<<"HEALED "<<n->hp<<"\n"; }
        }
        else if(cmd=="NEXT") {
            int x; cin>>x; Node* n=nextNode(root,x);
            if(!n) cout<<"NONE\n"; else cout<<n->rating<<" "<<n->name<<" "<<n->hp<<"\n";
        }
        else if(cmd=="PREV") {
            int x; cin>>x; Node* n=prevNode(root,x);
            if(!n) cout<<"NONE\n"; else cout<<n->rating<<" "<<n->name<<" "<<n->hp<<"\n";
        }
        else if(cmd=="MATCH") {
            int x; cin>>x; Node* n=match(root,x);
            if(!n) cout<<"EMPTY\n"; else cout<<n->rating<<" "<<n->name<<" "<<n->hp<<"\n";
        }
        else if(cmd=="RANGE") {
            int L,R; cin>>L>>R; bool any=false; rangePrint(root,L,R,any);
            if(!any) cout<<"EMPTY\n";
        }
        else if(cmd=="RANK") {
            int x; cin>>x; cout<<rankCount(root,x)<<"\n";
        }
        else if(cmd=="KTH") {
            int k; cin>>k; bool done=false; kth(root,k,done);
            if(!done) cout<<"OUT OF RANGE\n";
        }
        else if(cmd=="DUEL") {
            int a,b; cin>>a>>b;
            if(!search(root,a) || !search(root,b)) cout<<"NOT FOUND\n";
            else cout<<"DIST "<<distance(root,a,b)<<"\n";
        }
        else if(cmd=="STATS") {
            int total=rankCount(root,1e9+7);
            cout<<"PLAYERS "<<total<<"\n";
            if(!root) cout<<"MIN NONE\nMAX NONE\nHEIGHT -1\nLEAVES 0\n";
            else {
                cout<<"MIN "<<findMin(root)->rating<<"\n";
                Node* t=root; while(t->right) t=t->right;
                cout<<"MAX "<<t->rating<<"\n";
                cout<<"HEIGHT "<<height(root)<<"\n";
                cout<<"LEAVES "<<leaves(root)<<"\n";
            }
        }
    }
    return 0;
}
