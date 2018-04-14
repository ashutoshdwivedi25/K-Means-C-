#include<bits/stdc++.h>
using namespace std;

#define INF                       		2147483647
#define INFLL                     		9023372036854775807LL
#define _                         		ios::sync_with_stdio(false); cin.tie(0);
#define T()                       		int t; cin>>t; while(t--)
#define f0(i,n)                   		for(int i=0;i<n;i++)
#define f1(i,n)                   		for(int i=1;i<=n;i++)
#define fk(i,k,n)                 		for(int i=k;i<=n;i++)
#define fr(i,r,n)                 		for(int i=r;i>=n;i--)
#define pb push_back

//Calculating euclidean distance b/w cluster center and a point
double dist(vector<double> x10, vector<double> c10, int n){
	double d = 0;
	/*f0(i,2) cout<<x10[i]<<" ";
	    cout<<endl;*/
	//f0(i,2) cout<<c10[i]<<" ";
	f0(i,n){
	    d += ((x10[i] - c10[i])*(x10[i] - c10[i]));
	}
	d = sqrt(d);
	return d;
}
int main(int argc, char** argv)
{
	_
	string file_name = argv[1];
	string no_of_cluster = argv[2];
	stringstream ss(no_of_cluster);
    int k = 0;
    ss >> k;
    vector<vector<double> > v;
	fstream file;
	file.open(file_name);
    string   line;
    // Read one line at a time into the variable line:
    while(getline(file, line))
    {
        vector<double>   Dline;
        stringstream  lineStream(line);

        double fig;
        // Read an integer at a time from the line
        while(lineStream >> fig)
        {
            // Add the integers from a line to a 1D array (vector)
            Dline.push_back(fig);
        }
        // When all the integers have been read, add the 1D array
        // into a 2D array (as one line in the 2D array)
        v.push_back(Dline);
    }
    //cout<<v.size()<<endl;
    //cout<<v[0].size()<<endl;
    for(int i=0; i<v.size(); i++)
    {
		for(int j=0; j<v[0].size(); j++)
			cout<<v[i][j]<<" ";
		cout<<endl;
    }
    int m = v.size();
    int n = v[0].size();
   
/*	f0(i, m)
		f0(j, n)
			cout<<v[i][j]<<" ";*/

	vector<double> x1; 
	vector<vector<double> > c1(k);//cluster centers
	
	//choosing cluster centres randomly
	vector<int> t1;
	f0(i,k)
	t1.pb(rand()%m);
	for(int i=0; i<k; i++)
		c1[i] = v[t1[i]];
	
	//c1 = v[t1];//cluster center 1
	
	/*f0(i,k)
	   f0(j,n)
	     cout<<c1[i][j]<<" ";*/
	
	vector<vector<double> > prev_cluster(k,vector<double>(n, 0.0)); //to check whether prev centres is equal to new
	vector<pair<double, double> > dist_vec(m); //stores min. dist and cluster id of a point
	//stopping the loop when previous centres is equal to new centres or when no. of iterations are 50
	for(int p2 = 0; p2<50; p2++){
	
	f0(i,m){
		f0(j,n){
			//cout<<v[i][j]<<" ";
			
			x1.pb(v[i][j]);//pushing a point in the new vector in order to evaluate its distance from center
			
			//cout<<x1[j]<<" ";
		}
		
		//Evaluating minimum distance of a point from cluster
		double min = INT_MAX; 
		int cluster_id = 0;
		for(int idx=0; idx<k; idx++){
				double x2 = dist(c1[idx], x1, n);
				if(x2 < min)
				{
					min = x2;         //min. dist of point from cluster center
					cluster_id = idx; //id to which point belongs
				}
		}
		//cout<<c4[0]<<endl;
		dist_vec[i] = (make_pair(min, cluster_id));
		x1.clear();//clearing point vector so a new point can be pushed in order to evaluate its distance
		//cout<<endl;
	}
	//f0(i,m) cout<<c4[i]<<" ";
	//cout<<endl;
	vector<vector<pair<double, int> > > cluster(k,vector<pair<double, int> >(n, make_pair(0.0, 0)));
	
	f0(i,m){
		f0(d,n){
			cluster[dist_vec[i].second][d].first += v[i][d]; // summing points for taking average
			cluster[dist_vec[i].second][d].second += 1;      // no. of points in a cluster
		}
	}
	f0(i,k){
	  f0(d,n){
				c1[i][d] = cluster[i][d].first/cluster[i][d].second;//taking average
			}
		}
    // Breaking the loop when new cluster centres are equal to old
	if(p2 >= 1)
		{
			bool flag = false;
			f0(d,n){
				f0(i,k){
					if(prev_cluster[i][d] != c1[i][d])
						flag = true;
				}
			}
			if(flag == false)
				break;
		}
		f0(d,n)
			f0(i,k)
				prev_cluster[i][d] = c1[i][d]; //updating old cluster center
	}
    ofstream fout("output.txt");
    
    //Printing the cluster centres
  	f0(i,k)
	{
		fout<<"Final Cluster Center "<<i+1<<" is\t";
		f0(d,n)
			fout<<c1[i][d]<<" ";
			
		fout<<endl;
	}
	fout.close();
	return 0;
}


