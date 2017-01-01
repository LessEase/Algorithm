/*************************************************************************
	> File Name: unrolled_linked_list.cpp
	> Author: chenshaoyi
	> Mail: chshaoyi7@gmail.com
	> Created Time: 六 12/ 3 20:56:50 2016
 ************************************************************************/

#include<iostream>
using namespace std;

#define N 4

struct LinkNode{
    int values[N];
    int length;
    LinkNode* next;
    LinkNode():length(0),next(NULL){}
};

class ArrayList{
    private:
        LinkNode* head;
        int total_values;
    public:
        ArrayList(){
            head = NULL;
            total_values = 0;
        }
        
        bool GetValueInPosition(int idx, int& value);
        bool InsertValueInPosition(int idx, int value);
        bool DeleteValueInPosition(int idx);
        void Print();
};

void ArrayList::Print(){
    LinkNode* ptr = head;
    cout << "Print: " << endl;
    while(ptr!=NULL){
        cout << "number of nodes: " << ptr->length << endl;
        cout << "values: ";
        for(int i=0; i<ptr->length; i++){
            cout << ptr->values[i] << " ";
        }
        cout << endl;
        ptr = ptr->next;
    }    
}

bool ArrayList::GetValueInPosition(int idx, int& value){
    if(idx<0||idx>=total_values) return false;
    int counter=0;
    LinkNode* ptr = head;
    while(ptr!=NULL){
        if(counter+ptr->length>idx){
            idx -= counter;
            value = ptr->values[idx];
            return true;
        }
        counter += ptr->length;
        ptr = ptr->next;
    }
    return false;
}

bool ArrayList::InsertValueInPosition(int idx, int value){
    if(idx<0||idx>total_values) return false;
    int counter = 0;
    
    if(head==NULL){
        head = new LinkNode();
        head->values[0] = value;
        head->length = 1;
        return true;
    }

    LinkNode* ptr = head;
    while(ptr!=NULL){
        if(counter+ptr->length>=idx){
            if(ptr->length==N){
                LinkNode* temp = ptr->next;
                ptr->next = new LinkNode();
                ptr->next->next = temp;
                // not quite sure
                int half = N/2;
                for(int i=half; i<ptr->length; i++)
                    ptr->next->values[i-half] = ptr->values[i];
                ptr->next->length = ptr->length-half;
                ptr->length = half;
                continue;
            }else{
                int i = ptr->length;
                idx -= counter;
                while(i>idx){
                    ptr->values[i] = ptr->values[i-1];
                    i --;
                }
                ptr->values[idx] = value; 
                ptr->length += 1;
                total_values += 1;
                return true;
            }
        }

        counter += ptr->length;
        ptr = ptr->next;
    }
    return false;
}



bool ArrayList::DeleteValueInPosition(int idx){
    if(idx<0||idx>=total_values) return false;
    int counter=0;
    LinkNode* ptr = head, *before=NULL;
    
    while(ptr!=NULL){
        if(counter+ptr->length>idx){
            if(ptr->length==1){
                if(before!=NULL){
                    before->next = ptr->next;
                }else{
                    head = ptr->next;
                }
                delete ptr;
            }else{
                idx -= counter;
                int i = idx;
                ptr->length -= 1;
                while(i<ptr->length){
                    ptr->values[i] = ptr->values[i+1];
                    i ++;
                }
                if(ptr->length<N/2&&ptr->next!=NULL){
                    LinkNode* next = ptr->next;
                    if(next->length+ptr->length<N){
                        for(i=0; i<next->length; i++){
                            ptr->values[i+ptr->length] = next->values[i];
                        } 
                        ptr->length += next->length;
                        ptr->next = next->next;
                        delete next;
                    }else{
                        ptr->values[ptr->length] = ptr->next->values[0]; 
                        ptr->length += 1; 
                        next->length -= 1;
                        i = 0;
                        while(i<next->length){
                            next->values[i] = next->values[i+1];
                            i ++;
                        }
                    }
                }

            }
            total_values -= 1;
            return true;
        }
        counter += ptr->length;
        before = ptr;
        ptr = ptr->next;
    }

    return false;
}

int main(){
    
    int op, idx, value;

    ArrayList al;
    while(cin >> op){
        if(op==0) {
            cin >> idx;
            if(!al.GetValueInPosition(idx, value)) cout << "idx error" << endl;
            else cout << value << endl;
        }else if(op==1){
            cin >> idx >> value;
            if(!al.InsertValueInPosition(idx, value)) cout << "idx error" << endl;
        }else{
            cin >> idx;
            if(!al.DeleteValueInPosition(idx)) cout << "idx error" << endl;
        }
        al.Print();
    }

    return 0;
}


