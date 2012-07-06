
#include "main.h"

int Iteration_number;


void printclusters(map<int, vector<int> > clusters)
{
	for(map<int, vector<int> >::iterator it=clusters.begin();it!=clusters.end();it++)
	{
		cout<<"Cluster ";
		cout<<(*it).first;
		cout<<":";
		for(int i=0;i<(*it).second.size();i++)
			cout<<(*it).second[i]<<" ";
		cout<<"\n";
	}
}




int main()
{
	string file_name;
	string line;
	vector<string> dataset_string_format;
	cout<<"Enter the Dataset file name:";
	cin>>file_name;
	ifstream input_file;
	input_file.open((char *)file_name.c_str(),ifstream::in);
/* Read the dataset*/
	if(input_file.is_open())
	{
		while ( input_file.good())
    		{
      			getline(input_file,line);
     			dataset_string_format.push_back(line);
   		}
   		input_file.close();
	}
/////////////////////////////////////////


/* Convert the dataset from string format to float*/
	vector< vector<float> > dataset_final;
	char* temp;
	vector<float> line_float;
	temp=(char*)malloc(20*sizeof(char));
//	cout<<dataset_string_format.size()<<"\n";
//	cout<<dataset_string_format[50]<<"\n";
	for(vector<string>::iterator it=dataset_string_format.begin();it!=dataset_string_format.end();it++)
	{
		temp=strtok((char *)(*it).c_str(),", ");
		if(temp!=NULL)
		{	line_float.push_back(atof(temp));
			while((temp=strtok(NULL,", "))!=NULL)
				line_float.push_back(atof(temp));
			dataset_final.push_back(line_float);
		}
		line_float.clear();
	}
/////////////////////////////////////////

/*Choose K-Centers*/
int k;
cout<<"Enter the Number of Clusters:";
cin>>k;

while(1)
{
	vector<int> cluster_indexes;
	vector< vector<float> > cluster_centers;
	vector<double> probabilities_of_clusters;
	vector< vector<float> > covariance_matrix; // Covariance matrix only stores the diagonal of the covariance matrix ... the variance on each dimension ... as we use
					  //bayes principle and each dimension
					  //is independent of the other
	cluster_indexes=Initial_cluster_centers(dataset_final,k);
	for(int i=0;i<k;i++)
	{
		cluster_centers.push_back(dataset_final[cluster_indexes[i]]);
	}
	int num_dimensions=dataset_final[0].size();
	covariance_matrix=initial_covariance_matrix(num_dimensions,k);
	probabilities_of_clusters.assign(k,1.0/k);
///////////////////////////////////////


/* The Actual Clustering Phase*/
float threshold;
//cout<<"Enter the termination Threshold(0 to 1):";
cin>>threshold;

int retval=-1;
retval=EM(cluster_centers,covariance_matrix,probabilities_of_clusters,dataset_final,1121212123213.0,threshold);	

if(retval==1)
	break;
}
/////////////////////////////
}
