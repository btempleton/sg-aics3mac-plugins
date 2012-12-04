#include "IllustratorSDK.h" 
// Tell Xcode to export the following symbols 
#if defined(__GNUC__) 
#pragma GCC visibility push(default) 
#endif 
// Plug-in entry point 
extern "C" ASAPI ASErr PluginMain(char* caller, char* selector, void* message); 
// Tell Xcode to return to default visibility for symbols 
#if defined(__GNUC__) 
#pragma GCC visibility pop 
#endif 
extern "C" ASAPI ASErr PluginMain(char* caller, char* selector, void* message) 
{ 
ASErr error = kNoErr; 
SPBasicSuite* sSPBasic = ((SPMessageData*)message)->basic; 
if(sSPBasic->IsEqual(caller,kSPInterfaceCaller)) 
{ 
ADMBasicSuite10 *sADMBasic = nil; 
error = sSPBasic->AcquireSuite(kADMBasicSuite, 
kADMBasicSuiteVersion10,(const void**)&sADMBasic); 
if(sSPBasic->IsEqual(selector,kSPInterfaceStartupSelector)) 
sADMBasic->MessageAlert("Hello World!"); 
else if(sSPBasic->IsEqual(selector,kSPInterfaceShutdownSelector)) 
sADMBasic->MessageAlert("Goodbye World!"); 
error = sSPBasic->ReleaseSuite(kADMBasicSuite,kADMBasicSuiteVersion10); 
} 
return error; 
}