#include "Signature.h"
#include<iostream>

/* Queue initially empty */
std::queue<int> Signature::entitySignatures;

/* No signatures in use by default */
unsigned int Signature::inUse = 0;

Signature::Signature() {}


/* Generates a new unique entity signature from the queue */
int Signature::generateSig() {
	/* Disallow signature generation if ran out */
	if (Signature::inUse == MAX_ENTITIES) {
		std::cout << "[ERROR] No more entities can be generated" << std::endl;
		return -1;
	}

	/* initalize entity signature queue to be used in scenes*/
	if (Signature::entitySignatures.empty()) {
		for (int i = 0; i < MAX_ENTITIES; i++) {
			Signature::entitySignatures.push(i);
		}
	}
	
	int sig = Signature::entitySignatures.front();
	Signature::entitySignatures.pop();
	Signature::inUse++;

	/* DEBUG (Temporary until assertion system is up) */
	std::cout << "------------------------------------------------------" << std::endl;
	std::cout << "SIGNATURE GENERATED: " << sig << std::endl;
	std::cout << "Signatures left: " << Signature::entitySignatures.size() << std::endl;
	std::cout << "Curently in use: " << Signature::inUse << std::endl;
	std::cout << "------------------------------------------------------" << std::endl;

	return sig;
}


/* Recycle entity signature after it's destruction */
void Signature::destroySig(int signature) {}

