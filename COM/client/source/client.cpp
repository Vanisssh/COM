#include "wrapper.h"
#include "lib/interface.h"
#include <iostream>

using namespace std;

IID Constants::IID_IUnknown = { 0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46} };
IID Constants::IID_IClassFactory = { 0x00000001,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46} };

IID Constants::IID_IDefaultMatrix = { 0x00000001,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00} };
IID Constants::IID_IProMatrix = { 0x00000002,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00} };
IID Constants::IID_IMatrixClassFactory = { 0x00000011,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00} };

CLSID Constants::CLSID_Server = {0x781dfe5a,0x0602,0x4a54,{0x8a,0xf6,0x19,0x07,0xf3,0xbd,0x7d,0x89}};


int main() {
	cout << "Client start" << std::endl;			
	
	try{
		BServer b;
		b.set_matrix();
	 }catch(AServer& a){
		cout << a.GetMessage() << std::endl;
	 }
	
	return 0;
}