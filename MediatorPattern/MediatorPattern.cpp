#include <iostream>
#include <string>
using namespace std;
class Person;

//�����н���
class Mediator {
public:
    virtual void Send(const string& msg, Person* person) = 0;

    virtual ~Mediator() { }

    void BuildRelation(Person *a, Person *b) {
        m_a = a;
        m_b = b;
    }

protected:
    Person *m_a;
    Person *m_b;
};

//ʵ���н�
class ConcreteMediator :public Mediator {
public:
    void Send(const string& msg, Person* person) {
        if (person == m_a) {
            cout << msg << "--Mediator--PersonB" << endl;
        }
        else if (person == m_b) {
            cout << msg << "--Mediator--PersonA" << endl;
        }
    }
};

//�����û�
class Person {
public:
    Person(Mediator*md):_md(md) { }
    virtual void SendMessage(const string& msg) = 0;
    virtual ~Person() { }
protected:
    Mediator* _md;
};

//�û�A
class ConcretePersonA :public Person {
public:
    ConcretePersonA(Mediator* md):Person(md) { }

    void SendMessage(const string& msg) {
        _md->Send(msg, this);
    }

};

//�û�B
class ConcretePersonB :public Person {
public:
    ConcretePersonB(Mediator* md):Person(md) { }

    void SendMessage(const string& msg) {
        _md->Send(msg, this);
    }
};

//�û�C
class ConcretePersonC :public Person {
public:
	ConcretePersonC(Mediator* md) :Person(md) { }

	void SendMessage(const string& msg) {
		_md->Send(msg, this);
	}
};


int main() {
    Mediator *mediator = new ConcreteMediator();
    Person *personA = new ConcretePersonA(mediator);
    Person *personB = new ConcretePersonB(mediator);
	Person *personC = new ConcretePersonC(mediator);

    mediator->BuildRelation(personA, personB);
    personA->SendMessage("PersonA");
    personB->SendMessage("PersonB");

	mediator->BuildRelation(personA, personC);
	personC->SendMessage("PersonC");

    delete personA;
    delete personB;
    delete mediator;

    return 0;
}
