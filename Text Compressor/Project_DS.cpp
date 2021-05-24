/*

	THE DATA STRUCTURES USED IN OUR PROJECT ARE-
	1. Arrays
	2. Linked LIst
	3. Vector
	4. Map
	5. Set
	6. Tree
	7. Queue

*/


#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<set>
#include<fstream>
#include<cmath>
#include<sstream>
using namespace std;

long int siz=0;
map<int, string> finVals;
string preorder = "";


// Huffman Start--------------------------------------------------------------------

class leaf{
public:
    int data;
    int freq;
    leaf* left;
    leaf* right;

    leaf(){
        data=freq=-1;
        left=right=NULL;
    }

    leaf(int data, int freq){
        this->data=data;
        this->freq=freq;
        left=right=NULL;
    }

    leaf(const leaf &l){
        data = l.data;
        freq = l.freq;
        left = l.left;
        right = l.right;
    }
};



void getPreorder(leaf* node){ 
    if (node == NULL){
		preorder += "-2 "; 
        return; 
	}
  
    
    preorder += (to_string(node->data) + " "); 
    
    getPreorder(node->left); 
  
    getPreorder(node->right); 
} 



class compare{
public:
    bool operator()(leaf* l, leaf* r){
        return ((l->freq)>(r->freq));
    }
};



void printRepres(leaf* root, string s){
    
    if (root->data != -1){ 
        cout << root->data << ": " << s << endl;
        finVals[root->data]=s;
        siz+=s.length()*root->freq;
        return;
    }
  
    printRepres(root->left, s + "0"); 
    printRepres(root->right, s + "1"); 
}



leaf* huffman_coding(map<unsigned short int,int> huff_map, int n){

    priority_queue<leaf*, vector<leaf*>, compare> tree_elem;

    for(auto i=huff_map.begin(); i!=huff_map.end(); i++){
        tree_elem.push(new leaf(i->first,i->second));
    }

    while(tree_elem.size()!=1){
        leaf* left = tree_elem.top();
        tree_elem.pop();
        leaf* right = tree_elem.top();
        tree_elem.pop();

        leaf* combine = new leaf(-1, left->freq + right->freq);

        combine->left = left;
        combine->right = right;

        tree_elem.push(combine);
    }

    return tree_elem.top();
}

// Huffman End----------------------------------------------------------------------









// Move to Front Transform Start--------------------------------------------------

vector<unsigned short int> mtf_vec;


class node{
public:
    unsigned char data;
    node* next;

    node(unsigned char data){
        this->data = data;
        this->next = NULL;
    }
};



void addNode(node* head, unsigned char data){
    node* temp = head;
	
    while(temp->next!=NULL){
        temp=temp->next;
    }

    node* n=new node(data);
    temp->next=n;
	
    return;
}



node* initializeLinkedList(set<unsigned char> elem){
	
    node* head = new node(*elem.begin());
    auto i=elem.begin();
    i++;
    for(i; i!=elem.end(); i++){
        addNode(head, (*i));
    }
    return head;

}



node* mtf_node(node* head, unsigned char x){
    node* temp = head; 

    int ind=0;
    while(true){
        if(temp->data==x){
            mtf_vec.push_back(ind);
            if(ind==0){
            	return head;
			}else{
				node* temp_prev = head;
        		while(temp_prev->next!=temp){
            		temp_prev=temp_prev->next;
        		}
        		temp_prev->next=temp->next;
        		temp->next=head;
        		head=temp;
        		return head;
			}
        }else{
            ind++;
            temp=temp->next;
        }
    }
}



void mtf(string s, set<unsigned char> elem){
    node* head=initializeLinkedList(elem);
	
    for(int i=0; i<s.length(); i++){
        head = mtf_node(head,s[i]);
    }
    return;
}

// Move to Front Transform End------------------------------------------------------









//  BWT START ----------------------------------------------------------------------


void rotate(string &s, int l){
	char x=s[l-1];
	for(int i=l-1; i>0; i--){
		s[i]=s[i-1];
	}
	s[0]=x;
	return;
}



string bwt(string s, int &ind){
	vector<string> v;
	v.push_back(s);
	int l=s.length();
    bool flag;
	for(int i=1; i<l; i++){
		rotate(s,l);
        flag=false;
		for(auto i=v.begin(); i!=v.end(); ++i){
			if(s<(*i)){
				v.insert(i,s);
                flag=true;
                break;
			}
		}
        if(!flag){
            v.push_back(s);
        }
	}
	rotate(s,l);
	string burr="";
	long int j=0;
	for(auto i=v.begin(); i!=v.end(); ++i,++j){
		burr+=(*i)[l-1];
//		cout<<(*i)[0];
		if(s==*i){
			ind = j;
		}
	}
	cout<<endl;
	return burr;
}
// BWT END--------------------------------------------------------------------------








int main(){
	
	cout<<"Enter file name: "<<endl;
	string nameOfFile;
	cin>>nameOfFile;
	
	ifstream InputFile(nameOfFile);
	
	stringstream strStream;
	strStream << InputFile.rdbuf();
	string s = strStream.str();
	
	
	
	// Burrows Wheeler Transform 
	int invIndex;
	string t=bwt(s, invIndex);
    cout<<"After BWT transform:\n"<<t<<endl; // This prints BWT Transform string!!
    cout<<invIndex<<endl;

	
	
	
	
	
	// Move to Front Transform
	set<unsigned char> uniq_ch(begin(t),end(t));
//	for(auto i=uniq_ch.begin(); i!=uniq_ch.end(); ++i){  
//        cout<<int(*i)<<" ";
//    }
//    cout<<endl;


	mtf(t,uniq_ch);
	
	
	// This loop prints MTF Tranform vector
	cout<<"MTF transform output:\n{";
    for(auto i=mtf_vec.begin(); i!=mtf_vec.end(); ++i){  
        cout<<(*i)<<", ";
    }
	cout<<'}'<<endl;
//	cout<<mtf_vec.size()<<endl;
	
	
	
	
	
	
	// Huffman Encoding
	map<short unsigned int,int> huff_map;
	for(auto i=mtf_vec.begin(); i!=mtf_vec.end(); ++i){
        huff_map[*i]++;
    }
    
    // This prints Frequency Map used to generate Huffman tree!!
//    for(auto i=huff_map.begin(); i!=huff_map.end(); ++i){
//    	cout<<i->first<<"-->"<<i->second<<endl;
//	}




    leaf* root = huffman_coding(huff_map, huff_map.size());
    printRepres(root,""); // This prints representation of each number of MTF Vector in binary
    int avg_len=0;
    for(auto i = finVals.begin(); i!=finVals.end(); i++){
    	avg_len += ((*i).second).length();
	}
    avg_len/=finVals.size();
    cout<<"Average length of binary representation: "<<avg_len<<endl;
    cout<<"Percentage Space Saved = "<<(8*s.length()-siz)*100/(8*s.length())<<"%"<<endl;
	cout<<"END!!!!"<<endl;
	
	
	
	
	
	
	
	// Making output file
	ofstream myFile(nameOfFile+"-Info.txt");
	if(myFile.is_open()){
		
		myFile<<invIndex<<endl;
		
		for(auto i=uniq_ch.begin(); i!=uniq_ch.end(); ++i){
			myFile<<int(*i)<<" ";
		}
		myFile<<endl;
		
    	getPreorder(root);

		myFile<<preorder;
		
	}else{
		cout<<"error"<<endl;
	}
	
	myFile.close();





	ofstream strFile(nameOfFile+"-HuffmanString.txt");
	string op = "";
	for(auto i=mtf_vec.begin(); i!=mtf_vec.end(); ++i){
       	op+=finVals[*i];
    }
    strFile<<op<<endl;
   	strFile.close();
	
	
	
	system("PAUSE");
	
	
	
	return 0;
}
