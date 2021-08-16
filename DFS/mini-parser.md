# Mini Parser
## Problem
Given a string s represents the serialization of a nested list, implement a parser to deserialize it and return the deserialized NestedInteger.
Each element is either an integer or a list whose elements may also be integers or other lists.  
  
Example:
```
[123,456,[788,799,833],[[]],10,[]]
324
[123,[456,[789,-829],283,90],22,[12,90]]
```
## Solution
Let's do this recursively.
```
case 1: If 1st character of string is numeric or '-', then string is simply a number. Thus, return stoi(s) directly.
case 2: If 1st character of string is '[', then begin new list. Tokenize the whole string (excluding [ and ]) and recurse for each component.
```
While tokenizing, keep in mind, the current substring under consideration. While tokenizing using string::find direclty won't benefit as:
```
[12,[567,[123]]]
We should get tokens 12 and [567,[123]]. But if we use simple s.find(',', previous) for tokenizing, we will get 12 and [567 and 123]] which is incorrect.
```
Thus, we should implement our own version of find which linearly traverse and return index of ',' only when
```
number of '[' = number of ']'
```
Thus, function looks like this:
```c++
int helper(string s, int ind) {
    int open = 0, close = 0;
    for(int i=ind ; i<s.size() ; i++) {
        if(open == close && s[i]==',')
            return i;
        if(s[i]=='[')   open++;
        if(s[i]==']')   close++;
    }
    return -1;
}

NestedInteger deserialize(string s) {
    int n = s.size();
    if(isdigit(s[0]) || s[0]=='-') {
        return NestedInteger(stoi(s));
    }
    else if(s[0]=='[') {
        if(s[1]==']')   return NestedInteger();
        int prev = 0, next = 0;
        NestedInteger container;
        while(true) {
            next = helper(s, prev+1);
            if(next == -1) {
                next = n-prev-1;
                break;
            }
            string maal = s.substr(prev+1, next-prev-1);
            container.add(deserialize(maal));
            prev = next;
        }
        string maal = s.substr(prev+1, next-1);
        container.add(deserialize(maal));
        return container;
    }
    return NestedInteger();
}
```
However, this is not optimal due to various reasons. It is not single pass due to helper(). Also, memory usage is not optimal due to recursion and string
substr().  
Thus, we could mimin the above recusrion using stack and make it a single pass-iterative solution.
```c++
NestedInteger deserialize(const string s) 
{
    if(s[0]!='[') return NestedInteger(stoi(s));
    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    // const vector<NestedInteger> &getList() const;
    stack<NestedInteger *> st({new NestedInteger()});
    for(int i=1, x=0, sign=1; i+1<size(s); ++i)
        switch(s[i])
      {
          case '+' : break;                         
            case '-' : sign = -1;
                   break;                   
            case '[' : st.top()->add(NestedInteger());
                       st.push(&st.top()->getList().back());
                       break;
            case ']' : st.pop();
                       break;  
            case ',' : break;  
            default  : x = 10*x+s[i]-'0';  
                       if(!isdigit(s[i+1]))
                       {
                           st.top()->add(NestedInteger(sign*x));
                           sign=1;
                           x=0;
                       }
                       break;
        }
    return *st.top();
}
```
When '[' is encountered, a new NestedInteger object is appended to the list at stack top. After this, pointer to the newly created NestedInteger object is
pushed on top of the stack so that further modifications are directly done in that.
