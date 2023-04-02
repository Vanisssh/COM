#include "wrapper.h"
#include <iostream>

using namespace std;

int main() {    		
	cout << "Client start" << endl;			

	try{
	 	cout<<"default class factory"<<endl;
		BServer b;

		b.set_matrix();
	 }catch(AServer& a){
		cout<<a.GetMessage()<<endl;
	 }
	
	return 0;
}