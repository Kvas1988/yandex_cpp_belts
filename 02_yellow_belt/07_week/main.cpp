#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
	Person(const string& name, const string vocation) : name_(name), vocation_(vocation) {};

	virtual void Walk(const string& destination) const {
		cout << vocation_ << ": " << name_ << " walks to: " << destination << endl;
	};

	ostream& Log() const {
		cout << vocation_ << ": " << name_;
		return cout;
	};

	string GetVocation() const { return vocation_; };
	string GetName() const { return name_; };

private:
	const string name_;
	const string vocation_;
};

class Student : public Person {
public:

	Student(const string& name, const string& favouriteSong) : Person(name, "Student"), f_song_(favouriteSong) {}

	void Learn() const {
		Log() << " learns" << endl;
	}

	void Walk(const string& destination) const {
		Log() << " walks to: " << destination << endl;
		SingSong();
	}

	void SingSong() const {
		Log() << " sings a song: " << f_song_ << endl;
	}

	string GetFavSong() const { return f_song_; }
private:
	const string f_song_;
};


class Teacher : public Person {
public:

	Teacher(const string& name, const string& subject) : Person(name, "Teacher"), subject_(subject) {};

	string GetSubject() const { return subject_; };

	void Teach() const {
		Log() << " teaches: " << subject_ << endl;
	}

private:
	const string subject_;
};


class Policeman : public Person {
public:
	Policeman(const string& name) : Person(name, "Policeman") {};

	void Check(const Person& p) const {
		cout << "Policeman: " << GetName() << " checks " << p.GetVocation() << ". " << p.GetVocation() << "'s name is: " << p.GetName() << endl;
	}
};


void VisitPlaces(Person& p, vector<string> places) {
	for (auto pl : places) {
		p.Walk(pl);
	}
}


int main() {
	Teacher t("Jim", "Math");
	Student s("Ann", "We will rock you");
	Policeman p("Bob");

	VisitPlaces(t, { "Moscow", "London" });
	p.Check(s);
	VisitPlaces(s, { "Moscow", "London" });
	return 0;
}