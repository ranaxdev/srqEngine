#include "Signature.h"
#include<iostream>
/* Maximum amount of entities allowed in a scene */
const unsigned int Signature::MAX_ENTITIES = 100;

/* Declare empty queue */
std::queue<int> Signature::entitySignatures;

/* Blank for now - possibly wont create signature objects */
Signature::Signature() {}

/* Generates a new unique entity signature from the queue */
int Signature::generateSig() {
	/* initalize entity signature queue to be used in scenes*/
	if (Signature::entitySignatures.empty()) {
		for (int i = 0; i < MAX_ENTITIES; i++) {
			Signature::entitySignatures.push(i);
		}
	}
	int sig = Signature::entitySignatures.front();
	Signature::entitySignatures.pop();
	std::cout << "SIGNATURE GENERATED: " << sig << std::endl;
	return sig;
}


/* Recycle entity signature after it's destruction */
void Signature::destroySig(int signature) {}