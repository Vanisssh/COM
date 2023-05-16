#include "wrapper.h"

using namespace std;

AServer::AServer(const char* msg)
{
    this->msg = msg;
}

const char* AServer::GetMessage()
{
    return msg;
}

BServer::BServer()
{
    cout << "Bserver" << endl;
    CoInitialize(NULL);

    IClassFactory* MCF = NULL;

    HRESULT resFactory = CoGetClassObject(Constants::CLSID_Server, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IClassFactory, (void**) &MCF);


    if(!SUCCEEDED(resFactory)){
        throw AServer("No Factory");
    }
    
    HRESULT resInstance = MCF->CreateInstance(NULL, Constants::IID_IDefaultMatrix, (void**) &dm);

    if (!SUCCEEDED(resInstance))
    {
        throw AServer("No instance");
    }

    HRESULT resQuery = dm->QueryInterface(Constants::IID_IProMatrix, (void**) &pm);

    if (!SUCCEEDED(resQuery))
    {
        throw AServer("No QueryInterface");
    }

    MCF->Release();
}

BServer::BServer(int license[])
{
    cout << "Bserver::license" << endl;
    CoInitialize(NULL);

    IClassFactory* MCF = NULL;

    HRESULT resFactory = CoGetClassObject(Constants::CLSID_Server, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IClassFactory, (void**) &MCF);


    if(!SUCCEEDED(resFactory)){
        throw AServer("No Factory");
    }


    HRESULT resInstance = MCF->CreateInstance(NULL, Constants::IID_IDefaultMatrix, (void**) &dm);

    if (!SUCCEEDED(resInstance))
    {
        throw AServer("No license");
    }

    HRESULT resQuery = dm->QueryInterface(Constants::IID_IProMatrix, (void**) &pm);

    if (!SUCCEEDED(resQuery))
    {
        throw AServer("No QueryInterface");
    }

    MCF->Release();
}

HRESULT __stdcall BServer::set_matrix()
{
    return dm->set_matrix();
}

HRESULT __stdcall BServer::mult_num()
{
    return dm->mult_num();
}

HRESULT __stdcall BServer::addition(){
    return dm->addition();
}

HRESULT __stdcall BServer::subtraction(){
    return dm->subtraction();
}

HRESULT __stdcall BServer::exponentiation(){
    return dm->exponentiation();
}

HRESULT __stdcall BServer::transposition(){
    return pm->transposition();
}

HRESULT __stdcall BServer::rank(){
    return pm->rank();
}

HRESULT __stdcall BServer::reverse(){
    return pm->reverse();
}

HRESULT __stdcall BServer::minor(){
    return pm->minor();
}

BServer::~BServer()
{
    dm->Release();
    pm->Release();

    CoUninitialize();
}
