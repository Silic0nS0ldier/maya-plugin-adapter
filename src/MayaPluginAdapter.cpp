// MayaPluginAdapter.cpp : Defines the entry point for the application.
//

#include "MayaPluginAdapter.h"

DeclareSimpleCommand(helloWorld, "Autodesk", "2015");
MStatus helloWorld::doIt(const MArgList&)
{
    cout << "Hello World\n" << endl;
    return MS::kSuccess;
}
