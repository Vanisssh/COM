#pragma once

#include "ICF.h"
#include "server.h"
#include "IDMF.h"

#include <iostream>

class ClassFactory : public ICF, public IDefaultMatrixFactory{
    private:
        int refCount;
    public:
        ClassFactory();

        virtual HRESULT_ __stdcall (QueryInterface(const IID_& iid, void** object));
        virtual HRESULT_ __stdcall AddRef();
        virtual HRESULT_ __stdcall Release();

        virtual HRESULT_ __stdcall CreateInstance(const IID_& iid, void** object);

        virtual HRESULT_ __stdcall CreateInstance(const IID_& iid, void** object, int license[]);

        ~ClassFactory();
};