#ifndef _H_SIGNATURE
#define _H_SIGNATURE
#include<queue>
#include "Globals.h"
extern const int MAX_ENTITIES;

class Signature {
public:
	Signature();
	static int generateSig();
	static void destroySig(int signature);
	
private:
	static std::queue<int> entitySignatures;
	static unsigned int inUse;
};

#endif