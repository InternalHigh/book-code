/******************************************************************

   Richter_TimeServiceProvider.H -- WMI provider class definition

   Generated by Microsoft WBEM Code Generation Engine
 
   Description: 
   Programming Server-Side Applications for Microsoft Windows 
   TimeService WMI Provider

*******************************************************************/

// Property set identification
//============================

#ifndef _Richter_TimeServiceProvider_H_
#define _Richter_TimeServiceProvider_H_

#define PROVIDER_NAME_RICHTER_TIMESERVICEPROVIDER L"Richter_TimeServiceProvider"

// Property name externs -- defined in Richter_TimeServiceProvider.cpp
//=================================================

extern const WCHAR* pName ;
extern const WCHAR* pPipeName ;

class CRichter_TimeServiceProvider : public Provider 
{
    public:
        // Constructor/destructor
        //=======================

        CRichter_TimeServiceProvider(LPCWSTR lpwszClassName, LPCWSTR lpwszNameSpace);
        virtual ~CRichter_TimeServiceProvider();

    protected:
        // Reading Functions
        //============================
        virtual HRESULT EnumerateInstances(MethodContext*  pMethodContext, long lFlags = 0L);
        virtual HRESULT GetObject(CInstance* pInstance, long lFlags = 0L);
        virtual HRESULT ExecQuery(MethodContext *pMethodContext, CFrameworkQuery& Query, long lFlags = 0L);

        // Writing Functions
        //============================
        virtual HRESULT PutInstance(const CInstance& Instance, long lFlags = 0L);
        virtual HRESULT DeleteInstance(const CInstance& Instance, long lFlags = 0L);

        // Other Functions
        virtual HRESULT ExecMethod( const CInstance& Instance,
                        const BSTR bstrMethodName,
                        CInstance *pInParams,
                        CInstance *pOutParams,
                        long lFlags = 0L );

        // TO DO: Declare any additional functions and accessor
        // functions for private data used by this class
        //===========================================================

    private:
        // All data members for CRichter_TimeServiceProvider should be included here.   

} ;

#endif
