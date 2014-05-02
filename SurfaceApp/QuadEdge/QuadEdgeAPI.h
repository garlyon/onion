#pragma once

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the QUADEDGE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// QUADEDGE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef QUADEDGE_EXPORTS
#define QUADEDGE_API __declspec(dllexport)
#else
#define QUADEDGE_API __declspec(dllimport)
#endif

//// This class is exported from the QuadEdge.dll
//class QUADEDGE_API CQuadEdge {
//public:
//	CQuadEdge(void);
//	// TODO: add your methods here.
//};
//
//extern QUADEDGE_API int nQuadEdge;
//
//QUADEDGE_API int fnQuadEdge(void);
