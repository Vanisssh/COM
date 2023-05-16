#pragma once

#include <string>
#include <vector>
#include <windows.h>
#include <iostream>
#include <objbase.h>


class Constants{
    public:
     static IID IID_IUnknown;
     static IID IID_IClassFactory;

     static IID IID_IDefaultMatrix;
     static IID IID_IProMatrix;
     static IID IID_IMatrixClassFactory;

     static CLSID CLSID_Server;
     static CLSID CLSID_MatrixClassFactory;
};

class IDefaultMatrix : public IUnknown{
    public:
        virtual HRESULT __stdcall set_matrix() = 0;
        virtual HRESULT __stdcall mult_num() = 0;
        virtual HRESULT __stdcall addition() = 0;
        virtual HRESULT __stdcall subtraction() = 0;
        virtual HRESULT __stdcall exponentiation() = 0;
};

class IProMatrix : public IUnknown{
    public:
        virtual HRESULT __stdcall set_matrix() = 0;
        virtual HRESULT __stdcall find_determinant() = 0;
        virtual HRESULT __stdcall transposition() = 0;
        virtual HRESULT __stdcall rank() = 0;
        virtual HRESULT __stdcall reverse() = 0;
        virtual HRESULT __stdcall minor() = 0;
};

class IMatrixClassFactory : public IUnknown{
    public:
        virtual HRESULT __stdcall CreateInstance(const IID& iid, void** object, int license[]) = 0;
};

extern "C" HRESULT __stdcall __declspec(dllexport) DllGetClassObject(const CLSID& clsid, const IID& iid, void** object);
