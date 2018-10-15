//
// PlotMultiGraph.C  by Katsumasa Ikematsu
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "TCanvas.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TAxis.h"
#include "GetAGraph.C"
#include "GetAGraphNCol.C"
#include "GetAGraphErrors.C"

void PlotMultiGraph(const string file_datalist = "datalist.txt",
                    const int x_column  = 1,
                    const int y_column  = 2,
		    const int ye_column = 3,
                    const string x_axis = "X",
                    const string y_axis = "Y",
                    const string mg_title = "") {

  using namespace std;

  gStyle->SetOptLogy(1);
  gStyle->SetPadGridX(1);
  gStyle->SetPadGridY(1);
  //gStyle->SetLabelOffset(0.025, "X");
  //gStyle->SetEndErrorSize(0);
  //gStyle->SetErrorX(0);

  ifstream ifs(file_datalist);
  if ( ifs.fail() ) {
    cerr << "Error! Failed to open the file: ./" << file_datalist << endl;
    exit(1);
  }

  vector<string> datalist;
  string temp_filepath;
  int nfile = 0;
#if 0
  while ( !ifs.eof() ) {
#else
  while (ifs >> temp_filepath) {
#endif
    datalist.push_back(temp_filepath);
    nfile++;
  }
  ifs.close();
  cout << "the number of file in the data list is " << nfile << endl;

#if 0
  for (int i = 0; i < nfile; i++) {
    cout << "(i, file_path) = (" << i << ", " << datalist.at(i) << ")" << endl;
  }
#else
  for (auto itr = datalist.begin(); itr != datalist.end(); ++itr) {
    cout << "file_path = " << *itr << endl;
  }
#endif

  gStyle->SetPalette(1);

  auto c1 = new TCanvas("c1", "Multi graph", 0, 0, 1024, 768);

  auto mg = new TMultiGraph();

  vector<TGraph*> multi_gr;
  for (int i = 0; i < nfile; i++) {
#if 0
    multi_gr.push_back(GetAGraph(datalist.at(i), x_column, y_column));
  //multi_gr.push_back(GetAGraphErrors(datalist.at(i), x_column, y_column, ye_column));
#else
    multi_gr.push_back(GetAGraphNCol(datalist.at(i), x_column, y_column, 3));
#endif
    multi_gr.at(i)->SetMarkerStyle(20 + i);
    multi_gr.at(i)->SetMarkerSize(0.5);
    multi_gr.at(i)->SetLineWidth(2);
    multi_gr.at(i)->SetLineColor(2 + i);  // PLC (Palette Line Color) doesn't work

    mg->Add(multi_gr.at(i));
  //mg->Add(multi_gr.at(i), "PL");
  }

#if 0
//TGraph* gr1 = GetAGraph(datalist.at(1), 1, 2);  // this works
  auto    gr1 = GetAGraph(datalist.at(1), 1, 2);  // this also works
#endif

#if 0
  mg->Draw("A PLC PMC");  // PLC (Palette Line Color) doesn't work
#else
  mg->Draw("A P L");
#endif
  mg->SetTitle(mg_title.c_str());
  mg->GetXaxis()->SetTitle(x_axis.c_str());
  mg->GetYaxis()->SetTitle(y_axis.c_str());

#if 0
  const double xmin =  0.;
  const double xmax = 10.;
  const double ymin =  0.;
  const double ymax = 10.;
  mg->GetXaxis()->SetLimits(xmin, xmax);
  mg->SetMinimum(ymin);
  mg->SetMaximum(ymax);
#endif
  gPad->Modified();
  gPad->Update();

  c1->BuildLegend();
}
