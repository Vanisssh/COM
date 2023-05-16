#pragma once

#include "lib/interface.h"

#include <windows.h>
#include <iostream>

typedef HRESULT __stdcall (*FunctionType) (const CLSID&, const IID&, void**);

class AServer
{
    private:
        const char* msg;
    public:
        AServer(const char* msg);
        const char* GetMessage();
};

class BServer
{
    private:
        IDefaultMatrix* dm;
        IProMatrix* pm;
        BServer(const BServer&) {};
        BServer& operator=(const BServer&) {return *this;};
    public:
        BServer();
        BServer(int license[]);

        virtual HRESULT __stdcall set_matrix();
        virtual HRESULT __stdcall mult_num();
        virtual HRESULT __stdcall addition();
        virtual HRESULT __stdcall subtraction();
        virtual HRESULT __stdcall exponentiation();
        virtual HRESULT __stdcall transposition();
        virtual HRESULT __stdcall rank();
        virtual HRESULT __stdcall reverse();
        virtual HRESULT __stdcall minor();

        ~BServer();
};