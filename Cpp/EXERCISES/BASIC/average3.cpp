#include <iostream>
#include <utility>

using Note = float; using Weight = float;
using StudantNote = std::pair<Note, Weight>;
static StudantNote notes[4] =
{
	StudantNote(0,2.0), StudantNote(0,3.0),
	StudantNote(0,4.0), StudantNote(0,1.0)
};

template<std::size_t size>
float getAverage(StudantNote(&notes)[size]);


int main()
{
	using namespace std;
	cin >> notes[0].first >> notes[1].first >> notes[2].first >> notes[3].first;
	float average = getAverage(notes);

	cout.precision(1);
	cout.setf(cout.fixed);
	cout << "Media: " << average << endl;
	
	if (average >= 7.0)
		cout << "Aluno aprovado." << endl;

	else if (average >= 5.0)
	{
		cout << "Aluno em exame." << endl;
		float examNote, finalAvr;
		cin >> examNote;
		finalAvr = (examNote + average) / 2.0;
		cout << "Nota do exame: " << examNote << endl;
		if (finalAvr >= 5.0)
			cout << "Aluno aprovado." << endl;
		else
			cout << "Aluno reprovado." << endl;

		cout << "Media final: " << finalAvr << endl;
	}

	else
		cout << "Aluno reprovado." << endl;
	




	return 0;
}


template<std::size_t size>
float getAverage(StudantNote(&notes)[size])
{
	float notesTotal = 0;
	float weightTotal = 0;

	for (int i = 0; i < 4; ++i) {
		notesTotal += notes[i].first * notes[i].second;
		weightTotal += notes[i].second;
	}

	return notesTotal / weightTotal;
}