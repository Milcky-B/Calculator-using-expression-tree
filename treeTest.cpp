#include <iostream>
using namespace std;
#include "tree.cpp"
int main(){
    Tree<int> t, ct;
    t.insert(10);
    t.insert(0);
    t.insert(40);
    //t.copy(ct);


    cout << "isbst: "<<t.isTherePath(100)<<endl;
    
    t.display();
    /*
    p=t.search(40);
    cout<<t.findMin()<< endl;
    cout<<t.findMax()<< endl;
    cout << p->data<<endl;
    t.display();*/

}
