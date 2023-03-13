#ifndef TASK1_H
#define TASK1_H

#include <string>
#include "Rtypes.h"
#include <vector>
#include <map>
#include "TH1D.h"
#include "TCanvas.h"
using namespace std;

class Task1
{
public:
    typedef ULong64_t eventid_type;
    typedef map<eventid_type, vector<Double_t>> map_type;
    typedef vector<Double_t> event_vector_type;
    typedef vector<vector<string>> ttrtype;
    vector<ttrtype> ip_vector;
    vector<vector<vector<Double_t>>> vecB, vecC, vecBC, vecAB;
    vector<vector<Double_t>> parent_vector;
    vector<vector<Double_t>> vecA;
    vector<Double_t> impact_parameter;

private:
    eventid_type mEventId;
    map_type mPrimaryVertices;
    TH1D *mH1;
    TCanvas *c1;

public:
    Task1();
    Task1(const Task1 &) = delete;
    Task1 &operator=(const Task1 &) = delete;

    virtual  ~Task1();
    void Run();

    void InitHist();
    void SaveHist();
	void ClearDataStructures();
    void FindVertexFiles();
    void ReadVertexFile(const string &DataFilePath);
    void FindTrackFIles();
    void ReadTrackFile(const string &DataFilePath);
    void CreateBC();
    void CreateB();
    void CreateA();
    void CreateC();
    void CreateAB();
    void CalcImpactParameter();
    void CreateVectors();
    void CreateHist();
};
#endif