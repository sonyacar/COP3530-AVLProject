/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/
#include <iostream>
#include <iomanip> 
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <regex>
#include "BinaryTree.h"
using namespace std;


	int main(){

	int num_lines;
    string line, command;
	string quotes, name, UFid;
	BinaryTree student;
    getline(cin, line);
    num_lines = stoi(line);

    while (num_lines--) {
        getline(cin, line);
        stringstream ss(line);
        ss >> command;

	  if(command=="insert"){

		string quotes, name, UFid;
            getline(ss, quotes, '"');
            getline(ss, name, '"');
            ss >> UFid;

		regex obj= regex("^[a-zA-Z\\s]*$");
    	regex obj2=regex("^[0-9]{8}$");
    	if (regex_match(name,obj)==true && regex_match(UFid,obj2)==true ){
			//use stoi to change the id to integer to use a value/data
			int UFidINT=stoi(UFid);
			student.Insert(UFidINT,name);
		
	  	}
		else{
			cout<<"unsuccessful"<<endl;
		}
	  }
	  else if(command=="printInorder")
	  {
		vector <string> res;
		student.inorder(student.GetHead(),res);
		for (int i = 0; i < res.size(); i++) {
			cout << res[i];
			if (i < res.size() - 1) {
				cout << ", ";
			}
    	}
		cout<<endl;
	  }
	  else if(command=="printPreorder"){
		vector <string> res;
		student.preorder(student.GetHead(),res);
		for (int i = 0; i < res.size(); i++) {
			cout << res[i];
			if (i < res.size() - 1) {
				cout << ", ";
				}
    	}
		cout<<endl;
	  }
	  else if(command=="printPostorder"){
		vector <string> res;
		student.postorder(student.GetHead(),res);
		for (int i = 0; i < res.size(); i++) {
			cout << res[i];
			if (i < res.size() - 1) {
				cout << ", ";
				}
    	}
		cout<<endl;
	  }
	  else if(command=="printLevelCount"){
		int treeHeight= student.levelCount(student.GetHead());
		cout<<treeHeight<<endl;

	  }
	  else if (command == "search"){
		getline(ss, quotes, '"');
    	getline(ss, name, '"');

		if(quotes==" ")
		{
		vector <int> result;
		student.searchName(student.GetHead(),name,result);
		
		if(result.size()>0){
		for (int i = 0; i < result.size(); i++) { 
        cout << setw(8) << std::setfill('0')<<result[i]<<endl;
        if (i < result.size() - 1) {
        	}
    	}
		}
		else{
			cout<<"unsuccessful"<<endl;
		}
		}
		else{
			//this is to search the ID and return the corresponding name

			int quoteINT=stoi(quotes);
			vector <string> res;
			student.searchID(student.GetHead(),quoteINT,res);
			if(res.size()>0)
			{
			for (int i = 0; i < res.size(); i++) {
        	cout << res[i]<<endl;;
			if (i < res.size() - 1) {
				cout <<endl;
				}
    		}
			}
			else{
				cout<<"unsuccessful"<<endl;
			}
		}
	  }
	  else if(command=="remove"){
		getline(ss, quotes, '"');
    	getline(ss, name, '"');

		int quoteINT=stoi(quotes);
		student.removeID(student.GetHead(),quoteINT);
	  }
	  else if(command=="removeInorder"){
    	ss >> quotes;

		int quoteINT=stoi(quotes); 
		vector <int> res;
		student.removeInorder(student.GetHead(),quoteINT,res);
		if (res.size() > quoteINT) {
			int deleteID = res[quoteINT];
			student.removeID(student.GetHead(),deleteID);
		}
		else {
		cout << "unsuccessful" << endl;
		}
	  }
	  else{

	  }
    }
  return 0;
}
  
