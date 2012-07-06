#include "main.h"
#include<cmath>

vector<int> Initial_cluster_centers(vector< vector <float> > dataset_final,int k)
{
	int dataset_size=dataset_final.size();
	vector<int> cluster_centers;
	srand( time(NULL) );
	for(int i=0;i<k;i++)
	{
		cluster_centers.push_back(rand()% dataset_size + 1);
	}
	
	return cluster_centers;
}

vector< vector<float> > initial_covariance_matrix(int num_dimensions,int k) 
{
	vector<vector<float> > covariance_matrix;
	for(int i=0;i<k;i++)
	{
		vector<float> temp;
		for(int j=0;j<num_dimensions;j++)
			temp.push_back((rand()%100)/10);
		covariance_matrix.push_back(temp);
	}
	return covariance_matrix;
}

vector< vector<float> > Recompute_cluster_centers(vector< vector<float> > dataset_final,map<int, vector<double> > conditional_probabilities)
{
	vector< vector<float> > centers_new;
	for(map<int, vector<double> >::iterator it=conditional_probabilities.begin();it!=conditional_probabilities.end();it++)
	{
		vector<float> mean;
		float denominator=0.0;
		mean.assign(dataset_final[0].size(),0);
		for(int it1=0;it1 <(*it).second.size();it1++)
		{
			mean[0]+=((*it).second[it1])*dataset_final[it1][0];
			mean[1]+=((*it).second[it1])*dataset_final[it1][1];
			denominator+=(*it).second[it1];
		}
		mean[0]/=denominator;
		mean[1]/=denominator;
		centers_new.push_back(mean);
		
	}
	return centers_new;
}

vector< vector<float> > Recompute_covariance(vector< vector<float> > cluster_centers, vector< vector<float> > dataset_final,map<int, vector<double> >
conditional_probabilities)
{
	vector< vector<float> > covariances_new;
	for(map<int, vector<double> >::iterator it=conditional_probabilities.begin();it!=conditional_probabilities.end();it++)
	{
		vector<float> covariance;
		float denominator=0.0;
		covariance.assign(dataset_final[0].size(),0);
		for(int it1=0;it1 <(*it).second.size();it1++)
		{
			covariance[0]+=((*it).second[it1])*pow(dataset_final[it1][0]-cluster_centers[(*it).first][0],2);
			covariance[1]+=((*it).second[it1])*pow(dataset_final[it1][1]-cluster_centers[(*it).first][1],2);
			denominator+=(*it).second[it1];
		}
		covariance[0]/=denominator;
		covariance[1]/=denominator;
		covariances_new.push_back(covariance);
		
	}	
	return covariances_new;

}


vector<double> recompute_probabilities(map<int, vector<double> > conditional_probabilities)
{
	vector<double> probabilities_new_cluster;
	for(map<int, vector<double> >::iterator it=conditional_probabilities.begin();it!=conditional_probabilities.end();it++)
	{	double prob;
		for(int it1=0;it1 <(*it).second.size();it1++)
			prob+=(*it).second[it1];
		prob/=(*it).second.size();
		probabilities_new_cluster.push_back(prob);
	}
	return probabilities_new_cluster;
}



double compute_probability(vector<float> center,vector<float> covariance,double probability_cluster,vector<float> datapoint)
{
	double probability=probability_cluster;
	for(int i=0;i<covariance.size();i++)
	{
		probability*=(1/sqrt(2*M_PI*covariance[i]))*pow(M_E,-0.5*pow(abs(datapoint[i]-center[i])/sqrt(covariance[i]),2));
		
	}
	if(probability==0.0)
	{
		probability=0.000001;
	}
	return probability;	
}
	

float distance1(vector<float> point1,vector<float> point2)
{
	float sum_of_squares;
	for(int i=0;i<point1.size();i++)
	{
		sum_of_squares+=pow(point1[i]-point2[i],2);
	}
	return sqrt(sum_of_squares);
}

int EM(vector< vector<float> > cluster_centers,vector< vector<float> > covariance_matrix,vector<double> probabilities_of_clusters,vector< vector<float> > dataset_final,float sum_old,float threshold)
{
	map<int, vector<int> > clusters;
	map<int, vector<double> > conditional_probability_points_cluster;
	float sum_distances=0;
	for(int i=0;i<dataset_final.size();i++)
	{
		double probability_highest=-1;
		vector<double> probability;
		double probability_denominator=0.0;
		int cluster_center_closest;
		for(int j=0;j<cluster_centers.size();j++)
		{	
			double prob;
			prob=compute_probability(cluster_centers[j],covariance_matrix[j],probabilities_of_clusters[j],dataset_final[i]);
			probability.push_back(prob);
			probability_denominator+=prob;
			if(isnan(prob))
			{
				return 0;
			}
			if(prob>probability_highest)
			{
				probability_highest=prob;
				cluster_center_closest=j;
			}
		}
		for(int j=0;j<cluster_centers.size();j++)
		{
			probability[j]/=probability_denominator;
			conditional_probability_points_cluster[j].push_back(probability[j]);
		}	
		
		if(clusters.find(cluster_center_closest)==clusters.end())
		{
			vector<int> temp;
			temp.push_back(i);
			clusters[cluster_center_closest]=temp;
			sum_distances+=distance1(dataset_final[i],cluster_centers[cluster_center_closest]);
		}
		else
		{
			sum_distances+=distance1(dataset_final[i],cluster_centers[cluster_center_closest]);
			clusters[cluster_center_closest].push_back(i);
		}
		probability.clear();
	}
	if(sum_distances>=(1-threshold)*sum_old)
	{
		printclusters(clusters);
		return 1;
	}
	else
	{
		vector< vector<float> > cluster_centers_new;
		vector< vector<float> > covariance_matrix_new;
		vector<double> probabilities_new;
		cluster_centers_new=Recompute_cluster_centers(dataset_final,conditional_probability_points_cluster);
		covariance_matrix_new=Recompute_covariance(cluster_centers_new,dataset_final,conditional_probability_points_cluster);
		probabilities_new=recompute_probabilities(conditional_probability_points_cluster);
		return EM(cluster_centers_new,covariance_matrix_new,probabilities_new,dataset_final,sum_distances,threshold);
	}
}	
