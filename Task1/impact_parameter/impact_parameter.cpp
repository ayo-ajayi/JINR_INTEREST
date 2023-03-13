#include <vector>
#include "TFile.h"
#include "Riostream.h"
#include "TSystemDirectory.h"
#include "TSystem.h"
#include <memory>
#include "TMath.h"
#include "TCanvas.h"
#include "Task1.h"

using namespace std;

Task1::Task1() { InitHist(); }

Task1::~Task1()
{
	SaveHist();
	ClearDataStructures();
}
void Task1::Run()
{
	FindVertexFiles();
	FindTrackFIles();
	CreateVectors();
	CalcImpactParameter();
	CreateHist();
};
void Task1::CreateVectors()
{
	CreateBC();
	CreateB();
	CreateA();
	CreateC();
	CreateAB();
}
void Task1::InitHist()
{
	mH1 = new TH1D("h1", "impact parameter; impact parameter; Tracks", 9, 0, 520);
	mH1->SetFillColor(kBlue);
}
void Task1::ClearDataStructures()
{
	for (auto &PVertices : mPrimaryVertices)
		PVertices.second.clear();
	mPrimaryVertices.clear();
	vector<vector<vector<Double_t>>>().swap(vecB);
	vector<vector<vector<Double_t>>>().swap(vecC);
	vector<vector<vector<Double_t>>>().swap(vecAB);
	vector<vector<vector<Double_t>>>().swap(vecBC);
	vector<vector<Double_t>>().swap(vecA);
	vector<vector<Double_t>>().swap(parent_vector);
}
void Task1::SaveHist()
{
	TFile *HistFile = new TFile("HistFile_.root", "recreate");
	mH1->Write();
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

	vector<string> fileNames;
	TIter nextFile(DataDirFileList);
	for (TSystemFile *DataFile; (DataFile = (TSystemFile *)nextFile());)
	{
		if (DataFile->IsDirectory())
			continue;
		string DataFileName = DataFile->GetName();
		size_t StrPos = DataFileName.find("_Vertices.csv");
		if (StrPos == string::npos)
			continue;
		fileNames.push_back(DataFileName);
	}

	sort(fileNames.begin(), fileNames.end());

	for (const string &DataFileName : fileNames)
	{
		mEventId = stoull(DataFileName.substr(0, DataFileName.find("_Vertices.csv")));
		string DataFilePath = DataDirName + "/" + DataFileName;
		ReadVertexFile(DataFilePath);
	}
}

void Task1::FindTrackFIles()
{
	const string DataDirName = "../emulsion-data-for-charm-studies";
	TSystemDirectory DataDir(DataDirName.data(), DataDirName.data());
	TList *DataDirFileList = DataDir.GetListOfFiles();

	if (!DataDirFileList || (DataDirFileList->GetSize() < 3))
	{
		cerr << "Error in " << __func__ << "()" << endl;
		exit(0);
	}

	vector<string> fileNames;
	TIter nextFile(DataDirFileList);
	for (TSystemFile *DataFile; (DataFile = (TSystemFile *)nextFile());)
	{
		if (DataFile->IsDirectory())
			continue;
		string DataFileName = DataFile->GetName();
		size_t StrPos = DataFileName.find("_TrackLines.csv");
		if (StrPos == string::npos)
			continue;
		fileNames.push_back(DataFileName);
	}
	sort(fileNames.begin(), fileNames.end());
	for (const string &DataFileName : fileNames)
	{
		mEventId = stoull(DataFileName.substr(0, DataFileName.find("_TrackLines.csv")));
		string DataFilePath = DataDirName + "/" + DataFileName;
		ReadTrackFile(DataFilePath);
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
	parent_vector.push_back(V1);
	ifs.close();
}

void Task1::ReadTrackFile(const string &DataFilePath)
{
	ifstream csv_stream(DataFilePath);
	if (!csv_stream)
	{
		cerr << "Error in " << __func__ << "()" << endl;
		exit(0);
	}

	vector<vector<vector<string>>> file;
	vector<vector<string>> rows;
	string row_str;
	while (getline(csv_stream, row_str))
	{
		istringstream row_stream(row_str);
		string cell;
		vector<string> row;
		bool is_valid = true;
		while (getline(row_stream, cell, ','))
		{
			if (cell.empty())
			{
				is_valid = false;
				break;
			}
			row.push_back(cell);
		}
		if (is_valid && !row.empty() && row[0] == "10")
		{
			row.erase(row.begin());
			rows.push_back(row);
		}
	}
	ip_vector.push_back(rows);
}

void Task1::CreateBC()
{
	for (const auto &file_vector : ip_vector)
	{
		vector<vector<Double_t>> one_file;
		for (const auto &row : file_vector)
		{
			vector<Double_t> one_row;
			one_row = {stod(row[3]) - stod(row[0]), stod(row[4]) - stod(row[1]), stod(row[5]) - stod(row[2])};
			one_file.push_back(one_row);
		}
		vecBC.push_back(one_file);
	}
}
void Task1::CreateB()
{
	for (const auto &file_vector : ip_vector)
	{
		vector<vector<Double_t>> one_file;
		for (const auto &row : file_vector)
		{
			vector<Double_t> one_row;
			one_row = {stod(row[0]), stod(row[1]), stod(row[2])};
			one_file.push_back(one_row);
		}
		vecB.push_back(one_file);
	}
}
void Task1::CreateC()
{
	for (const auto &file_vector : ip_vector)
	{
		vector<vector<Double_t>> one_file;
		for (const auto &row : file_vector)
		{
			vector<Double_t> one_line;
			one_line = {stod(row[3]), stod(row[4]), stod(row[5])};
			one_file.push_back(one_line);
		}
		vecC.push_back(one_file);
	}
}
void Task1::CreateA()
{

	vector<Double_t> one_row;
	for (const auto &row : parent_vector)
	{
		one_row = {row[0], row[1], row[2]};
		vecA.push_back(one_row);
	}
}
void Task1::CreateAB()
{

	for (int i = 0; i < vecA.size(); i++)
	{
		vector<vector<Double_t>> vector_d;

		for (vector<Double_t> &vectorB : vecB[i])
		{
			vector<Double_t> vector_AB;

			for (int k = 0; k < vecA[i].size(); k++)
			{
				vector_AB.push_back(vecA[i][k] - vectorB[k]);
			}

			vector_d.push_back(vector_AB);
		}

		vecAB.push_back(vector_d);
	}
}

void Task1::CalcImpactParameter()
{
	vector<vector<Double_t>> cp;

	for (int i = 0; i < vecBC.size(); i++)
	{
		for (int j = 0; j < vecBC[i].size(); j++)
		{
			vector<Double_t> x(3);

			x[0] = vecAB[i][j][1] * vecBC[i][j][2] - vecAB[i][j][2] * vecBC[i][j][1];
			x[1] = vecAB[i][j][2] * vecBC[i][j][0] - vecAB[i][j][0] * vecBC[i][j][2];
			x[2] = vecAB[i][j][0] * vecBC[i][j][1] - vecAB[i][j][1] * vecBC[i][j][0];

			cp.push_back(x);
		}
	}
	vector<Double_t> cr;

	for (int i = 0; i < cp.size(); i++)
	{
		Double_t z = sqrt(pow(cp[i][0], 2) + pow(cp[i][1], 2) + pow(cp[i][2], 2));
		cr.push_back(z);
	}

	vector<Double_t> cr1;

	for (int i = 0; i < vecBC.size(); i++)
	{
		for (int j = 0; j < vecBC[i].size(); j++)
		{
			Double_t z = sqrt(pow(vecBC[i][j][0], 2) + pow(vecBC[i][j][1], 2) + pow(vecBC[i][j][2], 2));
			cr1.push_back(z);
		}
	}

	for (int i = 0; i < cr.size(); i++)
	{
		Double_t z = cr[i] / cr1[i];
		impact_parameter.push_back(z);
	}
}
void Task1::CreateHist()
{

	for (auto &xeach : impact_parameter)
		mH1->Fill(xeach);

	c1 = new TCanvas();
	mH1->Draw();
	c1->Print("impact_parameter.pdf");
	c1->Print("impact_parameter.png");
}

void impact_parameter()
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