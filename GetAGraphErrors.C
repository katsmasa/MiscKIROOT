//
// GetAGraphErrors.C  by Katsumasa Ikematsu
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "TGraphErrors.h"

#define DEBUG

TGraph* GetAGraphErrors(const string filepath, const int x_column, const int y_column, const int ye_column) {

  using namespace std;

  ifstream ifs(filepath);
  if ( ifs.fail() ) {
    cerr << "Error! Failed to open the file: ./" << filepath << endl;
    exit(1);
  }
#ifdef DEBUG
  cout << filepath << " has been opened" << endl;
#endif

  string str;
  getline(ifs, str);

  vector<string> each_column;
  stringstream ss(str);
  string item;
#if 1
  while (getline(ss, item, '\t') && !item.empty()) {
#else
  while (getline(ss, item, ' ')  && !item.empty()) {
#endif
    each_column.push_back(item);
  }
  cout << "The number of column in each line is " << each_column.size() << endl;

  const int ndata = each_column.size();  // the number of data in each line
  vector<double> x;
  vector<double> y;
  vector<double> yerr;
  double temp_data[ndata];

  ifs.seekg(0);  // move to the beginning of the file
  for (int i = 0; i < ndata; i++) ifs >> temp_data[i];
  while ( !ifs.eof() ) {
    x.push_back(temp_data[x_column - 1]);
    y.push_back(temp_data[y_column - 1]);
    yerr.push_back(temp_data[ye_column - 1]);
    for (int i = 0; i < ndata; i++) ifs >> temp_data[i];
  }
  ifs.close();

  if (x.size() != y.size()) {
    cerr << "Error! The size of two data arrays are different..." << endl;
    exit(1);
  }

  if (y.size() != yerr.size()) {
    cerr << "Error! The size of two data arrays are different..." << endl;
    exit(1);
  }

#ifdef DEBUG
  for (int i = 0; i < x.size(); i++) {
    cout << "(i, x, y, y_err) = (" << i << ", " << x.at(i) << ", " << y.at(i) << ", " << yerr.at(i) << ")" << endl;
  }
#endif

  double* xpointer = &(x.at(0));
  double* ypointer = &(y.at(0));
  double* yerrpointer = &(yerr.at(0));

  auto graph = new TGraphErrors(x.size(), xpointer, ypointer, 0, yerrpointer);

  graph->SetTitle(filepath.c_str());

  return graph;
}
