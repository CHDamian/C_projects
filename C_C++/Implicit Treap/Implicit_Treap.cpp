#include <iostream>
#include<algorithm>
using namespace std;

const long long int mod=1000000007;
int n,m,p,q;
int army[100005];
char c;
string S;

class Dynam {
public:
  long long int val[2][2];

  Dynam() {
    val[0][0] = 0;
    val[0][1] = 0;
    val[1][0] = 0;
    val[1][1] = 0;
  }

  Dynam(int x) {
    val[0][0] = 0;
    val[0][1] = 0;
    val[1][0] = 0;
    val[1][1] = 0;
    val[x][x]++;
  }

  Dynam(const Dynam &other) {
    val[0][0] = other.val[0][0];
    val[1][0] = other.val[1][0];
    val[0][1] = other.val[0][1];
    val[1][1] = other.val[1][1];
  }

  Dynam(Dynam d1, Dynam d2) {
    val[0][0]= d1.val[0][0] + d2.val[0][0] + d1.val[0][1]*(d2.val[0][0]+d2.val[1][0]) + d1.val[0][0]*d2.val[1][0];
    val[1][1]= d1.val[1][1] + d2.val[1][1] + d1.val[1][1]*(d2.val[1][1]+d2.val[0][1]) + d1.val[1][0]*d2.val[1][1];
    val[0][1]= d1.val[0][1] + d2.val[0][1] + d1.val[0][1]*(d2.val[0][1]+d2.val[1][1]) + d1.val[0][0]*d2.val[1][1];
    val[1][0]= d1.val[1][0] + d2.val[1][0] + d1.val[1][1]*(d2.val[1][0]+d2.val[0][0]) + d1.val[1][0]*d2.val[1][0];
    if(val[0][0]>=mod)val[0][0]%=mod;
    if(val[1][1]>=mod)val[1][1]%=mod;
    if(val[0][1]>=mod)val[0][1]%=mod;
    if(val[1][0]>=mod)val[1][0]%=mod;
  }
  Dynam rev() {
    swap(val[1][0], val[0][1]);
    return *this;
  }
};

typedef class Tree *Node;

class Tree {
public:
  int counter;
  int priority;
  bool flag;
  Dynam dp;
  Dynam me;
  Node left;
  Node right;

  Tree(int val, Node l, Node r){
    counter = 1;
    dp = Dynam(val);
    me = Dynam(val);
    left = l;
    right = r;
    flag = false;
    priority = (rand() << 16) | rand();
  }

  void toRev() {
    if (flag) {
      flag = false;
      if (left!=NULL){
        if(left->flag)left->flag=false;
        else left->flag=true;
      }
      if (right!=NULL){
        if(right->flag)right->flag=false;
        else right->flag=true;
      }
      swap(left, right);
    }
  }
  void changeDP(Dynam d){
      this->dp = d;
  }
};


void update(Node node) {
    Dynam d1;
    Dynam d2;
    node->counter=1;
    if(node->left!=NULL){
        node->counter+=node->left->counter;
        d1=Dynam(node->left->dp);
        if(node->left->flag)d1.rev();

    }
    if(node->right!=NULL){
        node->counter+=node->right->counter;
        d2=Dynam(node->right->dp);
        if(node->right->flag)d2.rev();
    }
    Dynam temp(d1,node->me);

    node->changeDP(Dynam(temp,d2));
}

void merge(Node &tree, Node left, Node right) {
  if(left!=NULL)left->toRev();
  if(right!=NULL)right->toRev();
  if (left==NULL)tree = right;
  else if (right==NULL)tree = left;
  else if (left->priority <= right->priority) {
    merge(right->left, left, right->left);
    tree = right;
  }
  else {
    merge(left->right, left->right, right);
    tree = left;
  }
  if(tree!=NULL)update(tree);
}

void split(Node tree, Node &left, Node &right, int k, int pom = 0) {
  left = NULL;
  right = NULL;
  if (tree!=NULL) {
    tree->toRev();
    int toIf=pom;
    if(tree->left!=NULL)toIf+=tree->left->counter;
    if (k <= toIf) {
      split(tree->left, left, tree->left, k, pom);
      right = tree;
    }
    else {
      split(tree->right, tree->right, right, k, toIf + 1);
      left = tree;
    }
    update(tree);
  }
}

bool cmp(Node node1, Node node2) {
  return node1->priority > node2->priority; }

void balance(Node node) {
  if (node!=NULL) {
    Node pom = node;
    if (node->left!=NULL && cmp(node->left,node))pom = node->left;
    if (node->right && cmp(node->right,pom))pom = node->right;
    if (pom != node) {
      swap(node->priority, pom->priority);
      balance(pom);
    }
  }
}

Node build(int *tab, int n) {
    if (n <= 0) return NULL;
    Node nod = new Tree(tab[n/2], build(tab, n/2), build(tab+1+(n/2) , n-1-(n/2)));
    balance(nod);
    update(nod);
    return nod;
}


int main() {
  ios_base::sync_with_stdio(0);
  cin>>n>>m;
  cin>>S;
  for (int i = 0; i < n; i++)if(S[i]=='R')army[i] = 1;
  Node treap = build(army, n);
  for (int i = 0; i < m; i++) {
        cin>>c>>p>>q;
        p--;
        q--;
        Node lef,mid,rig,helper;
        helper = treap;
        split(helper, lef, mid, p);
        split(mid, mid, rig, q-p+1);
        if(c=='?'){
            cout<<(mid->dp.val[0][0] + mid->dp.val[1][0] + mid->dp.val[0][1] + mid->dp.val[1][1])%mod<<endl;
        }
        else if(mid->flag)mid->flag=false;
        else mid->flag=true;
        merge(helper, lef, mid);
        merge(helper, helper, rig);
  }

  return 0;
}

