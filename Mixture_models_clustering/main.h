
#ifndef MAIN_H
#define MAIN_H
#include<iostream>
#include<stdio.h>
#include<vector>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<map>
using namespace std;

extern int Iteration_number;

vector<int> Initial_cluster_centers(vector< vector<float> >,int);

float distance1(vector<float>,vector<float>);

void printclusters(map<int, vector<int> >);

vector< vector<float> > initial_covariance_matrix(int,int);

vector< vector<float> > Recompute_cluster_centers(vector< vector<float>
>,map<int, vector<float> >);

vector< vector<float> > Recompute_covariance(vector< vector<float> >,
vector< vector<float> >,map<int,vector<float> >);

vector<double> recompute_probabilities(map<int, vector<float> >);

double compute_probability(vector<float>,vector<float>,float,vector<float>);

int EM(vector< vector<float> >,vector< vector<float> >,vector<double>,vector< vector<float> >,float,float);
#endif
