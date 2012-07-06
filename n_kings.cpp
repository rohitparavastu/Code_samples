#include<iostream>

using namespace std;

int chess();
int play_chess(int **,int,int,int,int);

/*void printboard(int **board,int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			cout<<board[i][j]<<" ";
		cout<<"\n";
	}
	cout<<"--------------------------\n";
}*/

int main()
{
	int t;
	cin>>t;
	for(int i=0;i<t;i++)
	{
		cout<<chess()<<"\n";
	}	
}

int chess()
{
	int n;
	cin>>n;
	int **board;
	board=new int* [n];
	for(int i=0;i<n;i++)
		board[i]=new int[n];

	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			board[i][j]=0;



	int k;
	cin>>k;
	for(int i=0;i<k;i++)
		for(int j=0;j<n;j++)
			board[i][j]=1;

	int columns_filled[k];
	if(k!=0)
	{
		for(int i=0;i<k;i++)
		{
			cin>>columns_filled[i];
		}

		if(n==k)
			return 1;
		for(int i=0;i<k;i++)
		{
			int row_number=i;
			int column_number=columns_filled[i];
			for(int j=0;j<n;j++)
				board[j][column_number]=1;
			for(int j=-1;j<2;j++)
			for(int l=-1;l<2;l++)
			{	
				if(row_number+j>=0 && row_number+j<n && column_number+l>=0 && column_number+l<n)
					board[row_number+j][column_number+l]=1;
			}	
		}
	}
//	printboard(board,n);	
	int total=0;
	int initial_row=k;
	if(initial_row==n-1)
	{	
		for(int j=0;j<n;j++)
		{
			if(board[initial_row][j]==0)
				total+=1;
		}
	}
	else
	{	
		for(int j=0;j<n;j++)
		{
			if(board[initial_row][j]==0)
				total+=play_chess(board,initial_row,j,n,2);
		}
	}
	delete[] board;
	return total;	
}

int play_chess(int **board,int row_number,int column_number,int n,int level)
{
	
		for(int i=0;i<n;i++)
		{
			if(board[row_number][i]==0)	
				board[row_number][i]=level;
			if(board[i][column_number]==0)
				board[i][column_number]=level;
		}
		for(int j=-1;j<2;j++)
		for(int l=-1;l<2;l++)
		{	
			if(row_number+j>=0 && row_number+j<n && column_number+l>=0 && column_number+l<n)
			{
				if(board[row_number+j][column_number+l]==0)
					board[row_number+j][column_number+l]=level;
			}
		}
		//printboard(board,n);
		int total=0;
		if(row_number+1==n-1)
		{
			
			for(int i=0;i<n;i++)
			{
				if(board[row_number+1][i]==0)	
					total+=1;
			}
		}
		else{
			for(int i=0;i<n;i++)
			{
				if(board[row_number+1][i]==0)	
					total+=play_chess(board,row_number+1,i,n,level+1);
			}
		}
		// Restoring the board to the original state
		for(int i=0;i<n;i++)
		{	
			if(board[row_number][i]==level)
			board[row_number][i]=0;
			if(board[i][column_number]==level)
			board[i][column_number]=0;
		}
		for(int j=-1;j<2;j++)
		for(int l=-1;l<2;l++)
		{	
			if(row_number+j>=0 && row_number+j<n && column_number+l>=0 && column_number+l<n)
			{
				if(board[row_number+j][column_number+l]==level)
					board[row_number+j][column_number+l]=0;
			}

		}
		return total;
}
