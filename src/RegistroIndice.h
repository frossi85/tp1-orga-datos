#ifndef REGISTROINDICE_H_
#define REGISTROINDICE_H_

#include <iostream>

using namespace std;

class RegistroIndice{
private:
	string clave;
	unsigned int offset;

public:
	RegistroIndice(string clave, unsigned int offset);
	string getClave();
	unsigned int getOffset();
	void setOffset(unsigned int offset);
};

#endif /* REGISTROINDICE_H_ */
