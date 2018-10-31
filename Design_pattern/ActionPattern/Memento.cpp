/*Originator（发起人）：负责创建一个 Memento，以记录当前时刻自身的内部状态，并可以使用 Memento 恢复内部状态。Originator 可以根据需要决定 Memento 储存自己的哪些内部状态。
Memento（备忘录）：负责存储 Originator 对象的内部状态，并可以防止 Originator 以外的其他对象访问备忘录。
Caretaker（管理者）：负责管理 Memento，但不能对 Memento 的内容进行访问或者操作。
--------------------- 
作者：一去丶二三里 
来源：CSDN 
原文：https://blog.csdn.net/liang19890820/article/details/79292435 
版权声明：本文为博主原创文章，转载请附上博文链接！
*/

// 以《大话西游》 时间穿越为背景
// Datatime: Memento 
// Lift : Originator
// PandoraBox: Caretaker

// Memento
#include <iostream>
#include <string>
#include <vector>

class DateTime
{
	public:
	DateTime(std::string dt):m_dateTime(dt){}
	
	void SetDateTime(std::string dt) {
		m_dateTime = dt;
	}
	
	std::string GetDateTime() {
		return m_dateTime;
	}
private:
	std::string m_dateTime;
};

// originator
class OneLife 
{
public:
	void SetDateTime(std::string dt) {
		std::cout << "set date time to:" << dt << std::endl;
		m_dateTime = dt;
	}
	std::string GetDateTime() {
		return m_dateTime;
	}
	
	void RestorMemento(DateTime* dt) {
		m_dateTime = dt->GetDateTime();
	}
	
	// create datetime
	DateTime* CreateDateTime() {
		return new DateTime(m_dateTime);
	}
private:
	std::string m_dateTime;
};

// PandoraBox :CareTacker

class PandoraBox
{
public:
	PandoraBox(OneLife* life):m_life(life){}
	~PandoraBox()
	{
		for(int i = 0; i < m_history.size(); ++i)
		{
			delete m_history.at(i);
		}
		m_history.clear();
	}
	
	void Save() {
		std::cout << "Saving.." << std::endl;
		m_history.push_back(m_life->CreateDateTime());
	}
	
	void UnDo() {
		std::cout << "Undo.." <<std::endl;
		m_life->SetDateTime(m_history.back()->GetDateTime());
		m_history.pop_back();
	}
	
private:
	std::vector<DateTime*> m_history;
	OneLife* m_life;
	
};


int main()
{
	OneLife* life = new OneLife();
	PandoraBox* box = new PandoraBox(life);
	
	life->SetDateTime("2018/10/30:00:00:11");
	box->Save();
	
	life->SetDateTime("2010/10/01:00:00:12");
	box->Save();
	
	life->SetDateTime("1987/2/10:15:30:30");
	
	// 穿越
	 box->UnDo();
	 std::cout << "current life time:" << life->GetDateTime() << std::endl;
	 
	 // 穿越
	box->UnDo();
	 std::cout << "current life time:" << life->GetDateTime() << std::endl;
	 
	delete life;
	delete box;

	return 0;
}

// #include <iostream>
// #include <string>

// class Memento { // 备忘录类，用于记录状态
// public:
	// friend class Originator;
	// Memento(const std::string& st) {
		// _st = st;
	// }
	
	// void SetState(const std::string& st) {
		// _st = st;
	// }
	
	// std::string GetState() {
		// return _st;
	// }
// private:
	// std::string _st;
// };

// class Originator { // 状态负责人
// public:
	// Originator() {
		// _mt = nullptr;
	// }
	
	// Originator(const std::string& st) {
		// _st = st;
		// _mt = nullptr;
	// }
	
	 // Memento* CreateMemento() {
        // return new Memento(_st);
    // }
	
	// void SetMemento(Memento* mt) {
		// _mt = mt;
	// }
	
	// Memento* GetMemento() { 
		// return _mt;
	// }
	
	// void RestoreToMemento(Memento* mt) {
		// _st = mt->GetState();
	// }
	
	// std::string GetState() {
		// return _st;
	// }
	
	// void SetState(std::string st) {
		// _st = st;
	// }
	
	 // void PrintState() {
        // std::cout << _st << "..." << std::endl;
    // }

	
// private:
	// std::string _st;
	// Memento* _mt;
// };

 // int main()
 // {
	 // Originator *o = new Originator();
	 // o->SetState("old");
	 // o->PrintState();
	 // Memento* m = o->CreateMemento();
	 // o->SetState("new");
	 // o->PrintState();
	 // o->RestoreToMemento(m);
	 // o->PrintState();
	 
	 // delete m;
	 // delete o;
	 
	 // return 0;
 // }
