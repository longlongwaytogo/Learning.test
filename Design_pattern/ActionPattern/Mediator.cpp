// Mediator.cpp
#include <iostream>
#include <string>
#include <list>

class IPerson;
class IMediator // 抽象中介
{
	public:
	// 注册参与者
	 void registerParticipator(IPerson* person) {
		m_persons.push_back(person);
	}
	const std::list<IPerson*>& GetPersons() const { return m_persons;}

	virtual void distributeMessage(const IPerson* sender, const std::string& msg) const = 0;
protected:
	std::list<IPerson*> m_persons;
};

class IPerson
{
public:
	IPerson(const std::string& name): m_strName(name){}
	std::string GetName() const {return m_strName;}
	virtual void SendMessage(const IMediator* mediator, const std::string& msg) const = 0;
	virtual void ReciveMessage(const IPerson* sender, const std::string& msg) const = 0;
protected:
	std::string m_strName;
};

// 具体中介者
class ConcreateMediator :public IMediator {
public:
	ConcreateMediator() {}

 void distributeMessage(const IPerson* sender, const std::string& msg) const 
 {
	 for(auto listener : m_persons)
	 {
		 if(listener != sender)
			 listener->ReciveMessage(sender,msg);
	 }
 }
};

class ConcreatePerson: public IPerson
{
public:
	ConcreatePerson(const std::string name) :IPerson(name){}
	virtual void SendMessage(const IMediator* mediator, const std::string& msg) const
	{
		mediator->distributeMessage(this,msg);
	}
	virtual void ReciveMessage(const IPerson* sender, const std::string& msg) const{
		std::cout << this->GetName() << ":received the message from:"  << sender->GetName() << ":"
		<< msg << std::endl;
	}
};

int main()
{
	ConcreateMediator* mediator = new ConcreateMediator();
	ConcreatePerson* person1 = new ConcreatePerson("jhon");
	ConcreatePerson* person2 = new ConcreatePerson("jim");
	ConcreatePerson* person3 = new ConcreatePerson("fangdong");
	
	mediator->registerParticipator(person1);
	mediator->registerParticipator(person2);
	mediator->registerParticipator(person3);
	
	std::string info = "I have on room";
	person1->SendMessage(mediator,info);	
	
	delete person1;
	delete person2;
	delete person3;
	delete mediator;
	
	return 0;
}