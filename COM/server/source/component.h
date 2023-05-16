#pragma once

#include "interface.h"

class Server : public IDefaultMatrix, public IProMatrix{
    private:
        IDefaultMatrix* dm;
        IProMatrix* pm;
        int refCount;
        int N;
        int M;
        int M1;
        int M2;
        int num;
    public:
        Server();
        
        virtual HRESULT __stdcall QueryInterface(const IID& iid, void** object);
        virtual ULONG __stdcall AddRef();
        virtual ULONG __stdcall Release();

        virtual HRESULT __stdcall set_matrix();
        virtual HRESULT __stdcall mult_num();
        virtual HRESULT __stdcall addition();
        virtual HRESULT __stdcall subtraction();
        virtual HRESULT __stdcall exponentiation();

        virtual HRESULT __stdcall find_determinant();
        virtual HRESULT __stdcall transposition();
        virtual HRESULT __stdcall rank();
        virtual HRESULT __stdcall reverse();
        virtual HRESULT __stdcall minor();
        
        ~Server();
};

class DefaultMatrixClassFactory : public IClassFactory, public IMatrixClassFactory{
    private:
        int refCount;
    public:
        DefaultMatrixClassFactory();

        virtual HRESULT __stdcall QueryInterface(const IID& iid, void** object);
        virtual ULONG __stdcall AddRef();
        virtual ULONG __stdcall Release();

        virtual HRESULT __stdcall CreateInstance(IUnknown* pUnknownOuter, const IID& iid, void** object);
        virtual HRESULT __stdcall CreateInstance(const IID& iid, void** object, int license[]);

        virtual HRESULT __stdcall LockServer(BOOL bLock);

        ~DefaultMatrixClassFactory();
};