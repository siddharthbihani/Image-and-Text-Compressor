#include<bits/stdc++.h>
#include<bitset>
# define STB_IMAGE_IMPLEMENTATION
# define STB_IMAGE_WRITE_IMPLEMENTATION
#include "C:/Users/Rakesh/Desktop/HtmlProjects/DS Lab Work/stb_image/stb_image.h"
#include "C:/Users/Rakesh/Desktop/HtmlProjects/DS Lab Work/stb_image/stb_image_resize.h"
#include "C:/Users/Rakesh/Desktop/HtmlProjects/DS Lab Work/stb_image/stb_image_write.h"
using namespace std;   

long int siz=0;
map<int, string> finVals;
string preorder = "";

class leaf{
public:
    int data;
    long int freq;
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
        cout << int(root->data) << ": " << s << endl;
        finVals[root->data]=s;
        siz+=s.length()*root->freq;
        return;
    }
  
    printRepres(root->left, s + "0"); 
    printRepres(root->right, s + "1"); 
}

leaf* huffman_coding(map<uint8_t ,long int> huff_map, int n){

    priority_queue<leaf*, vector<leaf*>, compare> tree_elem;

    for(auto i=huff_map.begin(); i!=huff_map.end(); i++){
        tree_elem.push(new leaf(int(i->first),i->second));
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

int main(){
	int width, height, bpp;
	
	string s;
	cout<<"Enter file name: ";
	cin>>s;
	const char* x = s.c_str();
    uint8_t* rgb_image = stbi_load(x, &width, &height, &bpp, 0);
    
    if(rgb_image==NULL){
    	cout<<"Invalid Filename!!"<<endl;
    	return 0;
	}
	
	cout<<"Enter compression factor (0 for default): ";
	int comFac;
	cin>>comFac;
	
	if(comFac==0){
		comFac = 5;
	}
	
	cout<<width<<" "<<height<<" "<<bpp<<endl;
	
	uint8_t* temp = rgb_image;
	
//	for(int i=0; i<1000; i++){
//		cout<<int(*temp)<<endl;
//		temp++;
//	}

	map<uint8_t, long int> huff_map;
	
	for(uint8_t* temp = rgb_image; temp!=rgb_image+width*height*bpp; temp++){
		huff_map[*temp-((*temp)%comFac)]++;
	}
	
	cout<<huff_map.size()<<endl;

	leaf* root = huffman_coding(huff_map, huff_map.size());
    printRepres(root,""); // This prints representation of each number of MTF Vector in binary
    cout<<"************"<<endl;
//    int avg_len=siz/huff_map.size();
//    cout<<avg_len<<endl;
    cout<<"Percentage Space Saved = "<<(8*width*height*bpp-siz)*100/(8*width*height*bpp)<<"%"<<endl;
	cout<<"END!!!!"<<endl;

	ofstream createFile(s+"-Info.txt");
	if(createFile.is_open()){
		
    	getPreorder(root);

		createFile<<preorder;
		
	}else{
		cout<<"error"<<endl;
	}
	
	createFile.close();
	
	ofstream strFile(s+"-HuffmanString.txt");
	for(uint8_t* temp = rgb_image; temp!=rgb_image+width*height*bpp; temp++){
		strFile<<finVals[*temp-((*temp)%comFac)];
	}
    
   	strFile.close();

	ofstream actualFile(s+"-Raw.txt");
	for(uint8_t* temp = rgb_image; temp!=rgb_image+width*height*bpp; temp++){
		actualFile<<bitset<8>(*temp).to_string();
	}
    
   	actualFile.close();

	stbi_image_free(rgb_image);
	
	system("PAUSE");
	
    return 0;
}
