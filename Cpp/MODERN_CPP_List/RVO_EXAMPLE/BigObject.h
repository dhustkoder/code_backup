#ifndef BIGOBJECT_H
#define BIGOBJECT_H

class BigObject
{
public:
	BigObject();
	BigObject(char y);
	BigObject(const BigObject& other);
	BigObject(BigObject&& other);
	~BigObject();

	const BigObject& operator=(const BigObject& other);
	const BigObject& operator=(BigObject&& other);


	void setData(char y);
private:
	char *m_data;
};


BigObject create_rvo(char y);  // RVO
BigObject create_nrvo(char y); // NRVO
BigObject create_move(char y); // MOVE







#endif