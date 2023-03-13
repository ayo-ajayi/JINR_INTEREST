#include "Task2.h"
#include "TSystemDirectory.h"
#include "TSystem.h"
#include <memory>
#include "TFile.h"
#include <vector>
#include "Riostream.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TCanvas.h"

using namespace std;
Task2::Task2()
{
    InitHist();
    Init2DHist();
}
Task2::~Task2()
{
    ClearDataStructures();
}
void Task2::ClearDataStructures()
{
    vector<vector<Double_t>>().swap(the2_file);
    vector<Double_t>().swap(the_file);
    File().swap(file);
    File().swap(tfile);
}
void Task2::Run()
{
    FindVertexFiles();
    FindTrackFiles();
    CreateHist();
}
void Task2::InitHist()
{
    mH1 = new TH1D("Hist", "track multiplicity", 10, 0, 10);
    mH1->SetFillColor(kRed);
    mH1->SetXTitle("multiplicity");
    mH1->SetYTitle("No of Events");
}
void Task2::Init2DHist()
{
    mH2 = new TH2D("Hist2", "muon tracks angle distr.", 30, -0.5, 0.5, 50, -0.5, 0.5);
    mH2->SetFillColor(kYellow);
    mH2->SetXTitle("AngXZ");
    mH2->SetYTitle("AngYZ");
    mH2->SetZTitle("Counts");
    mH2->GetXaxis()->SetTitleOffset(1.5);
    mH2->GetYaxis()->SetTitleOffset(1.6);
    mH2->GetZaxis()->SetTitleOffset(1.5);
}
void Task2::FindVertexFiles()
{
    const string DataDirName = "emulsion-data-for-track-multiplicity";

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
        size_t StrPos = DataFileName.find("_Vertex.csv");
        if (StrPos == string::npos)
            continue;
        mEventId = stoull(DataFileName.substr(0, StrPos));
        string DataFilePath = DataDirName + "/" + DataFileName;
        ReadVertexFile(DataFilePath);
    }
}

void Task2::ReadVertexFile(const string &DataFilePath)
{
    ifstream csv_stream(DataFilePath);
    if (!csv_stream)
    {
        cerr << "Error in " << __func__ << "()" << endl;
        exit(0);
    }

    string row_str;
    while (getline(csv_stream, row_str))
    {
        istringstream row_strem(row_str);
        string cell;
        vector<string> row;
        bool is_valid = true;
        while (getline(row_strem, cell, ','))
        {
            if (cell.empty())
            {
                is_valid = false;
                break;
            }
            row.push_back(cell);
        }
        if (row[0] != "evID")
            file.push_back(row);
    }

    csv_stream.close();
}

void Task2::FindTrackFiles()
{
    const string DataDirName = "emulsion-data-for-track-multiplicity";

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
        size_t StrPos = DataFileName.find("_Tracks.csv");
        if (StrPos == string::npos)
            continue;
        mEventId = stoull(DataFileName.substr(0, StrPos));
        string DataFilePath = DataDirName + "/" + DataFileName;
        ReadTrackFile(DataFilePath);
    }
}
void Task2::ReadTrackFile(const string &DataFilePath)
{

    ifstream csv_stream(DataFilePath);
    if (!csv_stream)
    {
        cerr << "Error in " << __func__ << "()" << endl;
        exit(0);
    }

    string row_str;
    while (getline(csv_stream, row_str))
    {
        istringstream row_strem(row_str);
        string cell;
        vector<string> row;
        bool is_valid = true;
        while (getline(row_strem, cell, ','))
        {
            if (cell.empty())
            {
                is_valid = false;
                break;
            }
            row.push_back(cell);
        }
        if (is_valid && !row.empty() && row[0] == "1")
        {
            row.erase(row.begin());
            tfile.push_back(row);
        }
    }

    csv_stream.close();
}

void Task2::CreateHist()
{
    for (const auto &f : file)
    {
        double m;
        for (auto i = 0; i < f.size(); i++)
            m = stod(f[8]);
        the_file.push_back(m);
    }

    for (const auto &f : tfile)
        the2_file.push_back({atan(stod(f[3])), atan(stod(f[4]))});

    auto *c1 = new TCanvas("cs", "cs", 1500, 900);
    for (auto &xeach : the_file)
        mH1->Fill(xeach);
    c1->Divide(2, 2);
    c1->cd(1);
    mH1->Draw();

    for (const auto &zeach : the2_file)
        mH2->Fill(zeach[0], zeach[1]);
    c1->cd(2);
    mH2->Draw("lego2");
    c1->cd(3);
    mH2->Draw("colz");
    c1->Print("file.png");
}

void mult()
{
    cerr << endl
         << "This program has started..." << endl
         << endl;
    unique_ptr<Task2> TTask2(new Task2());
    TTask2->Run();
    cerr << endl
         << "This program has finished successfully" << endl
         << endl;
}