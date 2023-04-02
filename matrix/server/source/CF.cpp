#include "CF.h"

using namespace std;

ClassFactory::ClassFactory(){
    cout<<"ClassFactory::ClassFactory"<<endl;
    this->refCount = 0;                                                                       
}

ClassFactory::~ClassFactory(){
    cout<<"ClassFactory::~ClassFactory"<<endl;
}


HRESULT_ ClassFactory::QueryInterface(const IID_& iid, void** object){
    cout<<"ClassFactory::QueryInterface"<<endl;
        if (iid == IID_IClassFactory_){
            *object = (IUnknown_*) (ICF*) this;
        }
        else if (iid == IID_IDefaultMatrixClassFactory){
            *object = (IUnknown_*) (IDefaultMatrixFactory*) this;
        }
        else{
            *object = NULL;
            return E_NOINTERFACE_;
        }

        this->AddRef();
        return refCount;
}

HRESULT_ ClassFactory::AddRef(){
    refCount++;
    return refCount;
}

HRESULT_ ClassFactory::Release(){
    refCount--;
    if (refCount == 0){
        delete this;
    }
    return refCount;
}

HRESULT_ ClassFactory::CreateInstance(const IID_& iid, void** object){
    cout<<"ClassFactory::CreateInstance"<<endl;
    IUnknown_* s = (IUnknown_*)(IDefaultMatrix*) new Server();

    s->AddRef();
    HRESULT_ res = s->QueryInterface(iid, object);
    s->Release();

    return res;
}

HRESULT_ ClassFactory::CreateInstance(const IID_& iid, void** object, int license[]){
    cout<<"ClassFactory::CreateInstance with license"<<endl;
    HRESULT_ res = E_NOCOMPONENT_;

    if (license != NULL){
        IUnknown_*s = (IUnknown_*)(IDefaultMatrix*) new Server();

        s->AddRef();
        res = s->QueryInterface(iid, object);
        s->Release();
    }
    return res;
}
//global
HRESULT_ __stdcall CreateInstance(const CLSID_& clsid, const IID_& iid, void** object){
    cout<<"CreateIsntance"<<endl;

    ICF* s = NULL;
    HRESULT_ res = GetClassObject(clsid, IID_IClassFactory_, (void**) &s);

    if (res == S_OK_){
        if (iid == IID_IDefaultMatrix){
            IDefaultMatrix* dm = NULL;
            res = s->CreateInstance(iid, (void**) &dm);
            *object = (IUnknown_*)(IDefaultMatrix*) dm;
        }
        else if (iid == IID_IProMatrix){
            IProMatrix* pm = NULL;
            res = s->CreateInstance(iid, (void**) &pm);
            *object = (IUnknown_*)(IProMatrix*) pm;
        }
    }else{
        cout<<"CreateIsntance ERROR"<<endl;
    }

    return res;
}

HRESULT_ __stdcall GetClassObject(const CLSID_& clsid, const IID_& iid, void** object){
    cout<<"GetClassObject"<<endl;
    IUnknown_* s = NULL;
    if (clsid == CLSID_DefaultMatrixClassFactory){
        s = (IUnknown_*)(ICF*) new ClassFactory();
    }else{
        *object = NULL;
        return E_NOCOMPONENT_;
    }
    s->AddRef();
    HRESULT_ res = s->QueryInterface(iid, object);
    s->Release();

    return S_OK_;
}