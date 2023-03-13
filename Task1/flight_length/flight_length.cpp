#include "TFile.h"
#include "Riostream.h"
#include "TSystemDirectory.h"
#include "TSystem.h"
#include <memory>
#include <iostream>
#include "TMath.h"
#include "Task1.h"

using namespace std;

Task1::Task1() { InitHist(); }
Task1::~Task1()
{
	SaveAndDeleteHist();
	ClearDataStructures();
}
void Task1::Run()
{
	FindVertexFiles();
	FillHist();
}

void Task1::InitHist()
{
	mH1 = new TH1D("Histogram", "Flight Length Distribution", 9, 0, 5300);
	mH1->SetFillColor(kGreen);
	mH1->SetXTitle("Flight Length(\xB5m)");
	mH1->SetYTitle("No of Events");
}
void Task1::SaveAndDeleteHist()
{
	TFile *HistFile = new TFile("HistFile.root", "recreate");
	mH1->Write();
	SafeDelete(mH1);
	SafeDelete(HistFile);
}
void Task1::ClearDataStructures()
{
	for (auto &PVertices : mPrimaryVertices)
		PVertices.second.clear();
	mPrimaryVertices.clear();
	for (auto &SVertices : mSecondaryVertices)
		SVertices.second.clear();
	mSecondaryVertices.clear();
}
void Task1::FindVertexFiles()
{
	
	const string DataDirName = "../emulsion-data-for-charm-studies";
	
	
	TSystemDirectory DataDir(DataDirName.data(), DataDirName.data());
	TList *DataDirFileList = DataDir.GetListOfFiles();

	if (!DataDirFileList || (DataDirFileList->GetSize() < 3))
	{
		cerr << "Error in " << __func__ << "()" << endl;
		exit(0);
	}
	TIter nextFile(DataDirFileList);
	
	for (TSystemFile *DataFile; (DataFile = (TSystemFile *)nextFile());)
	{
		if (DataFile->IsDirectory())
			continue;
		string DataFileName = DataFile->GetName();
		size_t StrPos = DataFileName.find("_Vertices.csv");
		if (StrPos == string::npos)
			continue;
		mEventId = stoull(DataFileName.substr(0, StrPos));
		string DataFilePath = DataDirName + "/" + DataFileName;
		ReadVertexFile(DataFilePath);
		
	}
}

void Task1::ReadVertexFile(const string &DataFilePath)
{
	ifstream ifs(DataFilePath);
	if (!ifs)
	{
		cerr << "Error in " << __func__ << "()" << endl;
		exit(0);
	}

	string fstring;
	getline(ifs, fstring);
	getline(ifs, fstring);

	istringstream istr1(fstring);
	event_vector_type &V1 = mPrimaryVertices[mEventId];
	V1.resize(3);
	istr1 >> V1[0];
	istr1.ignore();

	for (auto i = 0; i < 3; i++)
	{
		istr1 >> V1[i];
		istr1.ignore();
	}

	getline(ifs, fstring);
	istringstream istr2(fstring);
	event_vector_type &V2 = mSecondaryVertices[mEventId];
	V2.resize(3);
	istr2 >> V2[0];
	istr2.ignore();

	for (auto i = 0; i < 3; i++)
	{
		istr2 >> V2[i];
		istr2.ignore();
	}

	ifs.close();
}





void Task1::FillHist()
{
	for (const auto &PVertices : mPrimaryVertices)
	{
		const eventid_type EventId = PVertices.first;
		const event_vector_type &V1 = PVertices.second;
		const event_vector_type &V2 = mSecondaryVertices[EventId];

		Double_t dx = V1[0] - V2[0], dy = V1[1] - V2[1], dz = V1[2] - V2[2];

		auto Dist = TMath::Sqrt(dx * dx + dy * dy + dz * dz);
		mH1->Fill(Dist);
	}
}

void flight_length()
{
	cerr << endl
		 << "This program has started..." << endl
		 << endl;
	unique_ptr<Task1> TTask1(new Task1());
	TTask1->Run();
	cerr << endl
		 << "This program has finished successfully" << endl
		 << endl;
}