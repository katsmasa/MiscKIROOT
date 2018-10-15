//
// GetAGraphNCol.C  by Katsumasa Ikematsu
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "TGraph.h"

#define DEBUG

TGraph* GetAGraphNCol(const string filepath, const int x_column, const int y_column, const int n_column) {

  using namespace std;

  ifstream ifs(filepath);
  if ( ifs.fail() ) {
    cerr << "Error! Failed to open the file: ./" << filepath << endl;
    exit(1);
  }
#ifdef DEBUG
  cout << filepath << " has been opened" << endl;
#endif

  const int ndata = n_column;  // the number of data in each line
  vector<double> x;
  vector<double> y;
  double temp_data[ndata];

  for (int i = 0; i < ndata; i++) ifs >> temp_data[i];
  while ( !ifs.eof() ) {
    x.push_back(temp_data[x_column - 1]);
    y.push_back(temp_data[y_column - 1]);
    for (int i = 0; i < ndata; i++) ifs >> temp_data[i];
  }
  ifs.close();

  if (x.size() != y.size()) {
    cerr << "Error! The size of two data arrays are different..." << endl;
    exit(1);
  }

#ifdef DEBUG
  for (int i = 0; i < x.size(); i++) {
    cout << "(i, x, y) = (" << i << ", " << x.at(i) << ", " << y.at(i) << ")" << endl;
  }
#endif

  double* xpointer = &(x.at(0));
  double* ypointer = &(y.at(0));

  auto graph = new TGraph(x.size(), xpointer, ypointer);

  graph->SetTitle(filepath.c_str());

  return graph;
}
