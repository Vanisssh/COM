#include "component.h"
using namespace std;

IID Constants::IID_IUnknown = { 0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
IID Constants::IID_IClassFactory = { 0x00000001,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};

IID Constants::IID_IDefaultMatrix = { 0x00000001,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
IID Constants::IID_IProMatrix = { 0x00000002,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00} };
IID Constants::IID_IMatrixClassFactory = { 0x00000011,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};

CLSID Constants::CLSID_Server = {0x781dfe5a,0x0602,0x4a54,{0x8a,0xf6,0x19,0x07,0xf3,0xbd,0x7d,0x89}};



Server::Server() 
{
  cout << "Server::Constructor" << endl;

  refCount = 0;

  CoInitialize(NULL);

    IClassFactory* MCF = NULL;

    HRESULT resFactory = CoGetClassObject(Constants::CLSID_Server, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IClassFactory, (void**) &MCF);

    cout << "Server::Constructor::CoGetClassObject" << endl;

    if(!SUCCEEDED(resFactory)){
        cout << "No Factory" << endl;
    }
    cout << "Server::Constructor::CreateInstance" << endl;
    HRESULT resInstance = MCF->CreateInstance(NULL, Constants::IID_IDefaultMatrix, (void**) &dm);

    

    if (!SUCCEEDED(resInstance))
    {
        cout << "No instance" << endl;
    }

    HRESULT resQuery = dm->QueryInterface(Constants::IID_IProMatrix, (void**) &pm);

    cout << "Server::Constructor::QueryInterface" << endl;

    if (!SUCCEEDED(resQuery))
    {
        cout << "No QueryInterface" << endl;
    }

    MCF->Release();

  CoUninitialize();

}

HRESULT Server::QueryInterface(const IID& iid, void** object)
{
   cout << "Server QueryInterface" << endl;

   if (iid == Constants::IID_IUnknown)
   {
     *object = (IUnknown*)(IDefaultMatrix*) this;
   }
   else if (iid == Constants::IID_IDefaultMatrix)
   {
     *object = static_cast<IDefaultMatrix*>(this);
   }
   else if (iid == Constants::IID_IProMatrix)
   {
     *object = static_cast<IProMatrix*>(this);
   }
   else
   {
     *object = NULL;
     return E_NOINTERFACE;
   }

   this->AddRef();
   return S_OK;
}

ULONG Server::AddRef()
{
    refCount++;
    return refCount;
}

ULONG Server::Release()
{
    refCount--;
    if (refCount == 0)
    {
        delete this;
    }
    
    return refCount;
}

HRESULT Server::find_determinant() 
{	 	    		
  return S_OK;
}

HRESULT Server::set_matrix() 
{	 	    		
  cout << "Server set matrix" << endl;
  cin >> M;
  cin >> N;
	int matrix [M][N];
  for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			cin >> matrix[i][j];
	};
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++){
			cout << matrix[i][j];
			};
		cout << " " << endl;
	}; 	   
	return matrix[M][N];
  //return S_OK;
}

HRESULT Server::mult_num() 
{
  cout << "mult sum" << endl;
	cin >> num;
  int matrix[N][M];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			matrix[i][j] *= num;
	};
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++){
			cout << matrix[i][j];
			};
		cout << " " << endl;
	};
  return S_OK;
}

HRESULT Server::addition()
{	 	    		
  cout << "Server::addition" << endl;
  return S_OK;
}

HRESULT Server::subtraction()
{	 	    		
  return S_OK;
}

HRESULT Server::exponentiation()
{	 	    		
  return S_OK;
}

HRESULT Server::transposition()
{	 	    		
  return S_OK;
}

HRESULT Server::rank()
{	 	    		
  return S_OK;
}

HRESULT Server::reverse()
{	 	    		
  return S_OK;
}

HRESULT Server::minor()
{	 	    		
  return S_OK;
}

Server::~Server()
{
    cout<<"Server::~Server()"<<endl;
    dm->Release();
    pm->Release();
}

//DefaultMatrixClassFactory__________________________________________________________________________________

DefaultMatrixClassFactory::DefaultMatrixClassFactory(){
    cout<<"DefaultMatrixClassFactory::DefaultMatrixClassFactory"<<endl;
    this->refCount = 0;
}

DefaultMatrixClassFactory::~DefaultMatrixClassFactory(){
    cout<<"DefaultMatrixClassFactory::~DefaultMatrixClassFactory"<<endl;
}


HRESULT DefaultMatrixClassFactory::QueryInterface(const IID& iid, void** object){
    cout<<"DefaultMatrixClassFactory::QueryInterface"<<endl;
        if (iid == Constants::IID_IClassFactory){
            *object = (IUnknown*) (IClassFactory*) this;
        }
        else{
            *object = NULL;
            return E_NOINTERFACE;
        }

        this->AddRef();
        return S_OK;
}

ULONG DefaultMatrixClassFactory::AddRef(){
    refCount++;
    return refCount;
}

ULONG DefaultMatrixClassFactory::Release(){
    refCount--;
    if (refCount == 0){
        delete this;
    }
    return refCount;
}

HRESULT DefaultMatrixClassFactory::CreateInstance(IUnknown* pUnknownOuter,const IID& iid, void** object){
    cout<<"DefaultMatrixClassFactory::CreateInstance"<<endl;

    if (pUnknownOuter != NULL){
        return E_NOTIMPL;
    }
    IUnknown* s = (IUnknown*)(IDefaultMatrix*) new Server();

    HRESULT res = s->QueryInterface(iid, object);

    return res;
}

HRESULT DefaultMatrixClassFactory::CreateInstance(const IID& iid, void** object, int license[]){
    cout<<"DefaultMatrixClassFactory::CreateInstance with license"<<endl;
    HRESULT res = E_NOTIMPL;

    if (license != NULL){
        IUnknown*s = (IUnknown*)(IDefaultMatrix*) new Server();

        s->AddRef();
        res = s->QueryInterface(iid, object);
        s->Release();
    }
    return res;
}

HRESULT DefaultMatrixClassFactory::LockServer(BOOL bLock){
    return S_OK;
}