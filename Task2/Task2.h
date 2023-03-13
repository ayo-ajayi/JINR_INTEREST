#ifndef TASK1_H
#define TASK1_H

#include <vector>
#include <map>
#include "TH1D.h"
#include "TFile.h"
#include "Riostream.h"
#include <memory>
#include "TH2D.h"

using namespace std;

class Task2
{
public:
    typedef vector<vector<string>> File;
    File file, tfile;
    typedef ULong64_t eventid_type;
    eventid_type mEventId;
    vector<vector<Double_t>> the2_file;
    vector<Double_t> the_file;
    TH1D *mH1;
    TH2D *mH2;

    Task2();
    Task2(const Task2 &) = delete;
    Task2 &operator=(const Task2 &) = delete;
    virtual ~Task2();
    void Run();

    void InitHist();
    void FindVertexFiles();
    void ReadVertexFile(const string &DataFilePath);
    void Init2DHist();
    void FindTrackFiles();
    void ReadTrackFile(const string &DataFilePath);
    void CreateHist();
    void ClearDataStructures();
};
#endif
