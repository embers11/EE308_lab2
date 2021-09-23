#include <string>
#include <iostream>
#include <fstream>


using namespace std;
string keyword[]={"auto","break","case","char","const","continue","default","do",
				  "double","else","enum","extern","float","for","goto","if",
				  "int","long","register","return","short","signed","sizeof","stastic",
				  "struct","switch","typedef","union","unsigned","void","volatile","while"};

int main(){
	int level=0;//input output level 
	string filename; //the file name 
	cout<<"please,input the .cpp file name you wanna open in the same folder"<<endl;
	cin>>filename;
	cout<<"what level of output you want(from 1 to 4)"<<endl;
	cin>> level;
	ifstream stream_read,sp;
	stream_read.open(filename.c_str(),ios::in);//stream for read and count keyword number 
	sp.open(filename.c_str(),ios::in);// stream for process detial about else if case, the reason of new stream is the read stream will delate when getline 
	if(!stream_read){
        cout <<"Error,please check the path of file and try again!" << endl;
        exit(0); 
    }
	string str;
	int kwnum=32,numt=0; ;
	int count[kwnum] = {0}; //creat a array to store each keyword number 
	while (getline (stream_read, str)){
		for(int i=0;i<kwnum;i++)
		{
			int pos;//the position of keyword number 
			while(true)//the loop will break automatically while read to the end of stream,where return-1; 
			{
				if(str.find(keyword[i]) != -1)
				{
					pos = str.find(keyword[i]);//save the positon of current keyword avoid read mistake 
					count[i]++;
					str = str.substr(pos + keyword[i].length(),str.length() - pos - keyword[i].length());//get substring and deleat 
				} 
				else
					break;
			}
		}
	}
	for (int j;j<kwnum;j++)
	{
		if(count[j]!=0)
		{
			numt+=count[j];	
		}
	}
	int index[5]={25,2,6,15,9},x[3]={0,0,0};// index:the index in keyword appendix£»x:the array to store the number of switch,if and if else if  
	int struc[count[index[0]]]={0};//creat a array according previous switch number to store case number within each switch function 
	string pick[3]={"else if", "if","else"};
	int divide[1],ely=0,eln=0;//the divide here is used to mark string with if to divided srting for better sort if else and else if,
	                                //the statement here is to avoid compile error, the length of array will extend after count if number
									//ely:else if yes ; eln:else if no=if else 
	while (getline (sp, str)){
		int pos;
		while(true){
			if(str.find(keyword[index[1]]) != -1){//switch 
				struc[x[0]]++;
				break;
			}
			if(str.find(keyword[index[2]]) != -1){//case
				x[0]++;
				break;
			}
			if(str.find(pick[1]) != -1&& str.find(pick[0]) == -1){//filter the else if case avoding mistake 
				x[1]++;//if number 
				break;
			}
			else break;
		}
		int Copy_array[x[1]];
		for (int i=0;i<x[1]-1;i++){
			Copy_array[i]=divide[i];
		}
		*divide=*Copy_array;
		while(true){
			if(str.find(keyword[index[3]]) != -1){
				x[2]++;
				break;
			}
			else break;			
			if(str.find(pick[0]) != -1){
				pos = str.find(pick[0]);
				divide[x[2]]++;
			}else break;	
		}	
	}
	
switch(level){//the display part 
	case 1:
		cout<<"total num is: "<<numt<<endl;
		for(int j=0;j<kwnum;j++){	
			if(count[j]!=0){
			cout<<keyword[j]<<" "<<count[j]<<endl;
			}
		}
		break;
	case 2:
		cout<<"total num is: "<<numt<<endl;
		for(int j=0;j<kwnum;j++){	
			if(count[j]!=0){
			cout<<keyword[j]<<" "<<count[j]<<endl;
			}
		}
		cout<<"The number of switch structure is:"<<count[index[0]]<<endl;
		for(int k=0;k<count[index[0]];k++){
		cout<<"switch "<<k+1<<" number of case is: "<<struc[k]<<endl;
		}
		break;
	case 3:
		cout<<"total num is: "<<numt<<endl;
		for(int j=0;j<kwnum;j++){ 	
			if(count[j]!=0){
			cout<<keyword[j]<<" "<<count[j]<<endl;
			}
		}
		cout<<"The number of switch structure is:"<<count[index[0]]<<endl;
		for(int k=0;k<count[index[0]];k++){
		cout<<"switch "<<k+1<<" number of case is: "<<struc[k]<<endl;
		}
		for(int m=0;m<x[1];m++){
		if(divide[m]==0){
			eln++;
			}
		else{
			ely++;				
			}	
		}
		cout<<"the number of if-else: "<<eln<<endl;
		break;
	case 4:
		cout<<"total num is: "<<numt<<endl;
		for(int j=0;j<kwnum;j++){	
			if(count[j]!=0){
			cout<<keyword[j]<<" "<<count[j]<<endl;
			}
		}
		cout<<"The number of switch structure is:"<<count[index[0]]<<endl;
		for(int k=0;k<count[index[0]];k++){
		cout<<"switch "<<k+1<<" number of case is: "<<struc[k]<<endl;
		}
		for(int m=0;m<x[1];m++){
		if(divide[m]==0){
			eln++;
			}
		else{
			ely++;				
			}	
		}
		cout<<"the number of if-else: "<<eln<<endl;
		cout<<"the number of if-else if-else: "<<ely<<endl;
		break;
	}
return 0;
}
