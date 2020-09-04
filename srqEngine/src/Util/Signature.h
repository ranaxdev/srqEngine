#ifndef _H_SIGNATURE
#define _H_SIGNATURE
#include<queue>

class Signature {
public:
	Signature();
	static int generateSig();
	static void destroySig(int signature);
private:
	static const unsigned int MAX_ENTITIES;
	static std::queue<int> entitySignatures;
};

#endif