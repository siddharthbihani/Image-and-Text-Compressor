#include<bits/stdc++.h>
#include<sstream>
#include<fstream>
using namespace std;
#define COUNT 10


// Inverse Huffman Transform

stringstream str;

class leaf{
public:
	int data;
	leaf* left;
	leaf* right;
	
	leaf(int data = -1){
		this->data = data;
		left = right= NULL;
	}
	
};

leaf* buildTree(leaf* root){
	
	int x;
    str>>x;
 
    if(x==-2){
        return NULL;
    }
 
    leaf* n = new leaf(x);
    root = n;
 
    root->left = buildTree(root->left);
    root->right = buildTree(root->right);
 
    return root;
}

vector<int> getInvHuff(leaf* root, string s){
	
	vector<int> v;
	leaf* temp = root;
	for(int i = 0; i<s.length(); i++){
		
		if(s[i]=='1'){
			temp = temp->right;
		}else{
			temp = temp->left;
		}
		
		if(temp->left == NULL && temp->right == NULL){
			v.push_back(temp->data);
			temp = root;
		}
	}
	
	return v;
}

//Inverse Huffman End----------------------------------------------------------------------






// Inverse MTF-------------------------------------------------------------------------------

class node{
public:
    unsigned char data;
    node* next;

    node(unsigned char data){
        this->data = data;
        this->next = NULL;
    }
};

void AddNode(node* head, int x){
	node* temp = head;
	while(temp->next!=NULL){
		temp = temp->next;
	}
	node* n = new node(x);
	temp->next = n;
	 
}


char mtf_node(int index, node* &head){
	
	if(index == 0){
		return head->data;
	}else{
		node* temp = head;
		node* temp1 = head->next;
		int i=1;
		
		while(i!=index){
			temp1 = temp1->next;
			temp = temp->next;
			i++;
		}	
		
		temp->next = temp1->next;
		temp1->next = head;
		head = temp1;
		return head->data;
	}
}



string getInvMTF(vector<int> mtfTransform, node* head){
	
//	string AllCharList = "";
	
	string inverse="";
	
//	for(int i=0; i<=127; i++){
//		AllCharList+=char(i);
//	}
	
	for(auto i=mtfTransform.begin(); i!=mtfTransform.end(); ++i){
		
		unsigned char x = mtf_node(*i, head);		
		inverse.push_back(x);
				
	}
	
	
//	cout<<inverse<<endl;
	return inverse;
}

// Inverse MTF end-----------------------------------------------------------------------------










// Inverse BWT---------------------------------------------------------------------------------

string getInvBWT(string bwtTransform, int OGindex){
	
	map<unsigned char, long int> freq;
	
	for(unsigned char x:bwtTransform){
		freq[x]++;
	}
	
	string sortBWT = "";
	string ans = "";	
	
	for(auto i=freq.begin(); i!=freq.end(); i++){
		for(int j=0; j<(i->second); j++){
			sortBWT+=(i->first);
		}
	}
	
//	cout<<sortBWT<<endl;
	
	int x = OGindex;
	
	char find = sortBWT[x];
//	cout<<"@@@@@"<<endl;
	long int brr = 0;
//	cout<<bwtTransform<<endl;
	for(int i=0; i<bwtTransform.length(); i++){
		int j, count = 0;
//		cout<<"1"<<endl;
		ans+=sortBWT[x];
//		cout<<"2"<<endl;
		for(j=0; j<x; j++){
			if(sortBWT[j]==find){
				count++;
			}
		}
//		cout<<"3"<<endl;
//		cout<<find<<endl;
		j=-1;
//		cout<<count<<endl;
		while(count>=0){
			++j;
			if(bwtTransform[j]==find){
				count--;
			}
		}
//		cout<<"4"<<endl;
		find = sortBWT[j];
		x = j;
//		cout<<"5"<<endl;
	}
//	cout<<"%%%%%"<<endl;
	return ans;
}

// Inverse BWT end-----------------------------------------------------------------------------

void printTREE(leaf *root, int space=0)  
{  
    // Base case  
    if (root == NULL)  
        return;  
  
    // Increase distance between levels  
    space += COUNT;  
  
    // Process right child first  
    printTREE(root->right, space);  
  
    // Print current node after space  
    // count  
    cout<<endl;  
    for (int i = COUNT; i < space; i++)  
        cout<<" ";  
    cout<<root->data<<"\n";  
  
    // Process left child  
    printTREE(root->left, space);  
}  

int main(){
	
	cout<<"Enter Binary String file name: ";
	string BinName;
	cin>>BinName;
	
	
	cout<<"Enter Info File name: ";
	string InfoName;
	cin>>InfoName;
	
	
	ifstream BinFile(BinName);
	ifstream InfoFile(InfoName);

	
	// ENSURE THAT FILES HAVE BEEN OPENED WITHOUT ANY ERROR
	if(!BinFile.is_open() or !InfoFile.is_open()){
		cout<<"Error!"<<endl;
		return 0;
	}

	
	
	// READING CONTENTS FROM THE FILES AS STRING
	stringstream strStream;
	strStream << BinFile.rdbuf();
	string BinString = strStream.str();
	
	
	
	string OGind;
	int OGindex; // BWT INVERSE INDEX NUMBER
	string CharListINT;  // LIST OF CHARACTERS PRESENT 
	string treePreorder;  // PREORDER OF HUFFMAN TREE
	
	getline(InfoFile, OGind);
	OGindex = stoi(OGind);
	getline(InfoFile, CharListINT);
	getline(InfoFile, treePreorder);
	
//	cout<<OGindex<<endl;
//	cout<<CharListINT<<endl;
//	cout<<treePreorder<<endl;
//	cout<<BinString<<endl;


	
	stringstream chars(CharListINT);
	
	int x;
	string AllCharList="";
	
	
	// MAKING LINKED LIST OF CHARACTERS
	chars>>x;
	node* head = new node(x);
	
	while(chars>>x){
		AddNode(head,x);
	}
	


	// MAKING HUFFMAN TREE FROM TREE PREORDER
	leaf* root = NULL;	
	str << treePreorder;
	root = buildTree(root);
	
//  	printTREE(root);	

	
	
	
	// GETTING MOVE TO TRANSFORM VECTOR FROM HUFFMAN TREE AND HUFFMAN STRING
	vector<int> mtfTransform = getInvHuff(root, BinString);

//	for(auto i=mtfTransform.begin(); i!=mtfTransform.end(); i++){
//		cout<<*i<<" ";
//	}
//	cout<<mtfTransform.size()<<endl;
	
	
	// GETTING BWT STRING FROM MTF VECTOR
	string bwtTransform = getInvMTF(mtfTransform, head);
//	cout<<bwtTransform<<endl;
	
	
	
	// GETTING THE ACTUAL TEXT BACK 
	string actual = getInvBWT(bwtTransform, OGindex);
//	cout<<actual;
	
	cout<<"File Successfully Decoded!"<<endl;
	
	ofstream OutputFile("Decoded.txt");
    OutputFile<<actual;
   	OutputFile.close();
	
	system("PAUSE");
	
	return 0;
}
