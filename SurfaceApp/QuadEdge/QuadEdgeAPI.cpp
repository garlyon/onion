// QuadEdge.cpp : Defines the exported functions for the DLL application.
//

#include "QuadEdgeAPI.h"


// This is an example of an exported variable
QUADEDGE_API int nQuadEdge=0;

// This is an example of an exported function.
QUADEDGE_API int fnQuadEdge(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see QuadEdge.h for the class definition
CQuadEdge::CQuadEdge()
{
	return;
}
