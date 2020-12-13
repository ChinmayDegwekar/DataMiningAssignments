#include<bits/stdc++.h>
#include <spatialindex/capi/sidx_api.h>
#include <spatialindex/capi/sidx_impl.h>
#include <spatialindex/capi/sidx_config.h>
using namespace std;
using namespace SpatialIndex;
#include <chrono> 
using namespace std::chrono; 

#define mod 1000000
vector<int> ran;

bool checkIsThere(int num){
	for(int i=0;i<ran.size();i++){
		if(ran[i] == num)
			return true;
	}
	return false;
}

void generateRandom(){
	int i=0;
	while(i<100){
		int num = rand()%mod;
		if(!checkIsThere(num)){
			ran.push_back(num);
			i++;
		}
	}
	sort(ran.begin(), ran.end());
}


Index* createIndex()
{
	// create a property set with default values.
	// see utility.cc for all defaults  http://libspatialindex.github.io/doxygen/Utility_8cc_source.html#l00031
	Tools::PropertySet* ps = GetDefaults();
	Tools::Variant var;

	// set index type to R*-Tree
	var.m_varType = Tools::VT_ULONG;
	var.m_val.ulVal = RT_RTree;
	ps->setProperty("IndexType", var);

	// Set index to store in memory (default is disk)
	var.m_varType = Tools::VT_ULONG;
	var.m_val.ulVal = RT_Memory;
	ps->setProperty("IndexStorageType", var);

	// initalise index
	Index* idx = new Index(*ps);
	delete ps;

	// check index is ok
	if (!idx->index().isIndexValid())
		throw "Failed to create valid index";
	else
		cout << "created index" << endl;

	return idx;
}

void addPoint(Index* idx, vector<double> row, int64_t id)
{
	int d = row.size();
	double coords[d];
	for(int i=0;i<d;i++){
		coords[i] = row[i];
	}

	// shapes can also have anobject associated with them but we'll leave that for the moment.
	uint8_t* pData = 0;
	uint32_t nDataLength = 0;

	// create shape
	SpatialIndex::IShape* shape = 0;
	shape = new SpatialIndex::Point(coords, d);

	// insert into index along with the an object and an ID
	idx->index().insertData(nDataLength,pData,*shape,id);

	delete shape;

}


int getNearest(Index* idx,vector<double> row,double maxResults)
{
	int d = row.size();
	double coords[d];
	for(int i=0;i<d;i++){
		coords[i] = row[i];
	}

	// get a visitor object and a point from which to search
	ObjVisitor* visitor = new ObjVisitor;
	// make point from lat/lon with two dimentions
	SpatialIndex::Point* r = new SpatialIndex::Point(coords, d);

	// get nearest maxResults shapes form index
	idx->index().nearestNeighborQuery(maxResults,*r,*visitor);

	// get count of inspections
	int64_t nResultCount;
	nResultCount = visitor->GetResultCount();

	delete r;
	delete visitor;

	return nResultCount;
}


int main(){
	generateRandom();
	auto start = high_resolution_clock::now(); 

	Index* idx = createIndex();
	vector<vector<double>> query;
	
	ifstream infile("scaled_4.csv");
	vector<double> temp;

    string line, word; 
	int id = 0, q=ran[0], rid=0;
    while (getline(infile, line)) { 
	
        temp.clear(); 
        istringstream s(line); 
        while (getline(s, word, ',')) { 
				temp.push_back(stod(word));
        }
		
		if(id==q){
			query.push_back(temp);
			rid++;
			q = ran[rid];
		}
		else addPoint(idx, temp, id);
		
		id++;
    } 
	long long int inspections = 0;
	for(int i=0;i<100;i++){
		inspections += getNearest(idx, query[i], 1);
	}
	auto stop = high_resolution_clock::now(); 
	auto duration = duration_cast<milliseconds>(stop - start); 
	cout<<"Inspections: "<<inspections<<endl;
	cout<<"time(milliseconds): "<<duration.count()<<endl;
}