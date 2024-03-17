/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 void sort(ListNode* const head ,const int N){

     if(N==1)return;

     ListNode* ptr1,*ptr2;
     ptr2=ptr1=head;
     for(int i=0;i<N/2;i++)ptr2=ptr2->next;

     int N1=N/2;
     int N2=N-N/2;
     sort(ptr1,N1);
     sort(ptr2,N2);

     ListNode* head2, *ptr=NULL;
     int i=0,j=0;
     while(i<N1 || j<N2){
         int val;
         if(j==N2)val=ptr1->val,ptr1=ptr1->next,i++;
         else if(i==N1)val=ptr2->val,ptr2=ptr2->next,j++;
         else if(ptr1->val <= ptr2->val)val=ptr1->val,ptr1=ptr1->next,i++;
         else val=ptr2->val,ptr2=ptr2->next,j++;

         if(ptr==NULL)ptr=new ListNode(val),head2=ptr;
         else ptr->next=new ListNode(val),ptr=ptr->next;
     }


     ptr1=head,ptr2=head2;
     for(int i=0;i<N;i++){
         ptr1->val=ptr2->val;
         ptr1=ptr1->next;
         ptr2=ptr2->next;
     }

     ptr2=head2;
     while(ptr2!=NULL){
         ptr=ptr2;
         ptr2=ptr2->next;
         delete ptr;
     }

 }
ListNode* Solution::sortList(ListNode* A) {

    ListNode*ptr=A;
    int len=0;
    while(ptr!=NULL){
        ptr=ptr->next;
        len++;
    }
    sort(A,len);
    return A;
}

