#include <bits/stdc++.h>
using namespace std;

struct Node{
    int value;
    Node* next;
};

struct LinkedList{
    Node *head,*tail;

    LinkedList(){
        head=NULL;
        tail=NULL;
    }

    void add(int value){

        if(head==NULL){

            head=new Node;
            tail=head;

            tail->next=NULL;
            tail->value=value;


        }
        else{
            tail->next=new Node;
            tail=tail->next;
            tail->value=value;
            tail->next=NULL;
        }
    }

    void dlt(Node*&ptr){
        Node* temp;
        while(ptr!=NULL){
            temp=ptr;
            ptr=ptr->next;
            delete temp;
        }
    }

    void sort(Node* ptr, int len){
           if(ptr==NULL)return ;

           if(len==1)return ;

           int len1=len/2;
           int len2=len/2+len%2;

           Node*ptr1=ptr;
           Node*ptr2=ptr;
           for(int i=0;i<len1;i++)ptr2=ptr2->next;

           sort(ptr1,len1);
           sort(ptr2,len2);


           LinkedList ll;
           int i=0,j=0;
           while(i<len1 && j<len2){
               if(ptr1->value <= ptr2->value){
                    ll.add(ptr1->value);
                    ptr1=ptr1->next;
                    i++;
               }
               else{
                    ll.add(ptr2->value);
                    ptr2=ptr2->next;
                    j++;
               }
           }
           while(i<len1){
                ll.add(ptr1->value);
                ptr1=ptr1->next;
                i++;
           }
           while(j<len2){
                ll.add(ptr2->value);
                ptr2=ptr2->next;
                j++;
           }
          cpy(ptr,ll.head);
          dlt(ll.head);
    }


     void cpy(Node* ptr1,Node* ptr2){
        while(ptr1!=NULL){
            ptr1->value=ptr2->value;
            ptr1=ptr1->next;
            ptr2=ptr2->next;
        }
     }
    void print(){
        Node*ptr=head;
        while(ptr!=NULL){
            cout<<ptr->value<<" ";
            ptr=ptr->next;
        }
    }


};

int main(){
   LinkedList ll;
   int n,x;
   cin>>n;
   for(int i=0;i<n;i++){
        cin>>x;
        ll.add(x);
   }
   ll.sort(ll.head,n);
   ll.print();
}
