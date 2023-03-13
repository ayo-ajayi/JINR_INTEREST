#ifndef TASK1_H
#define TASK1_H

#include <vector>
#include <map>
#include "TH1D.h"
#include "TFile.h"
#include "Riostream.h"
#include <memory>


using namespace std;

class Task1
{
public:
	typedef ULong64_t eventid_type;
	typedef map<eventid_type, vector<Double_t>> map_type;
	typedef vector<Double_t> event_vector_type;


	eventid_type mEventId;
	size_t mNbOfEvents;
	map_type mPrimaryVertices, mSecondaryVertices, mTrackLines;
	TH1D *mH1;


	Task1();
	Task1(const Task1 &) = delete;
	Task1 &operator=(const Task1 &) = delete;
	~Task1();
	void Run();


	void InitHist();
	void SaveAndDeleteHist();
	void ClearDataStructures();
	void FindVertexFiles();
	void ReadVertexFile(const string &DataFilePath);
	void FillHist();
};
#endif