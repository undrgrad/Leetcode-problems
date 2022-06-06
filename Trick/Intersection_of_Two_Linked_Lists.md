# Intersection of Two Linked Lists
## Problem
Given the heads of two singly linked-lists headA and headB, return the node at which the two lists intersect. 
If the two linked lists have no intersection at all, return null.  

## Constraints
The number of nodes of listA is in the m.  
The number of nodes of listB is in the n.  
1 <= m, n <= 3 * 104  
1 <= Node.val <= 105  

## Test Cases
![Screenshot from 2022-06-06 18-18-49](https://user-images.githubusercontent.com/44015508/172163808-3bb432e9-2c39-415d-a940-0ddfd373201b.png)
![Screenshot from 2022-06-06 18-19-01](https://user-images.githubusercontent.com/44015508/172163828-a36575b5-9779-477c-8ff9-1e90caa54621.png)
![Screenshot from 2022-06-06 18-19-13](https://user-images.githubusercontent.com/44015508/172163837-721d7410-b588-461e-81db-f6e79a77d6ef.png)

## Solution
### Brute Force
For each node of list A, check each node of List B. Time complexity: O(N^2)

### 3-Traversal approach
We make first traversal to get the length of List A (say n) and the 2nd traveral to get the length of B (say m).  
Let n > m. After this, we move the iterator pointer of list A forward by n-m steps and then move both iterator pointers together.  

### 2-Traversal approach
In the first iteration, we will reset the pointer of one linkedlist to the head of another linkedlist after it reaches the tail node. 
In the second iteration, we will move two pointers until they points to the same node. Our operations in first iteration will help us counteract the difference. 
So if two linkedlist intersects, the meeting point in second iteration must be the intersection point. If the two linked lists have no 
intersection at all, then the meeting pointer in second iteration must be the tail node of both lists, which is null.  
Try this approach on pen paper.


```c++
ListNode* getIntersectionNode(ListNode *headA, ListNode *headB) {
    //boundary check
    if(headA == null || headB == null) return null;
    
    ListNode *a = headA;
    ListNode *b = headB;
    
    //if a & b have different len, then we will stop the loop after second iteration
    while( a != b){
    	//for the end of first iteration, we just reset the pointer to the head of another linkedlist
        a = a == null? headB : a->next;
        b = b == null? headA : b->next;    
    }
    
    return a;
}
```
