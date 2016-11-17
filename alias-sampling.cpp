/*************************************************************************
	> File Name: alias-sampling.cpp
	> Author: chenshaoyi
	> Mail: chshaoyi7@gmail.com
	> Created Time: 三 11/16 16:27:21 2016
 ************************************************************************/

#include<iostream>
#include<deque>
#include<vector>
#include<cstdlib>
using namespace std;

double GetUniform(){
    return (double)(rand()%10000)/10000.0;
}

class AliasSampler{
    public:
    AliasSampler();
    AliasSampler(vector<double> probs_distribution);
    void SetDistribution(vector<double> probs_distribution);
    void SetDistribution(double probs_distribution[], int length);
    void GenerateAliasTable();
    int  GetASample(); 
    void Print();

    private:
        vector<double> probs_distribution_;
        vector<int>    alias_ids_;
        vector<double> alias_vals_;
        double threshold;
};

void AliasSampler::Print(){
    vector<double> probs_dis(probs_distribution_.size(), 0.0);
    for(int i=0; i<probs_distribution_.size(); i++){
        if(alias_vals_[i]*probs_distribution_.size()<1.0){
            probs_dis[i] += alias_vals_[i];
            probs_dis[alias_ids_[i]] += (threshold-alias_vals_[i]);
        }else{
            probs_dis[alias_ids_[i]] += threshold;
        }
    }

    for(int i=0; i< probs_distribution_.size(); i++){
        cout << alias_ids_[i] << " " << alias_vals_[i] << endl;;
    }
    cout << endl;
    for(int i=0; i< probs_distribution_.size(); i++){
        cout << probs_dis[i] << " " ;
    }
    cout << endl;
}

AliasSampler::AliasSampler(){
    probs_distribution_.clear();
    probs_distribution_.push_back(1.0);
}

AliasSampler::AliasSampler(vector<double> probs_distribution){
    this->probs_distribution_ = probs_distribution;
}

void AliasSampler::SetDistribution(vector<double> probs_distribution){
    this->probs_distribution_ = probs_distribution;
}

void AliasSampler::SetDistribution(double probs_distribution[], int length){
    probs_distribution_.clear();
    double total=0.0;
    for(int i=0; i<length; i++){
        probs_distribution_.push_back(probs_distribution[i]);
        total += probs_distribution[i];
    }
    for(int i=0; i<length; i++){
        probs_distribution_[i] /= total;
    }
}

void AliasSampler::GenerateAliasTable(){
    alias_ids_.clear();    
    alias_vals_.clear(); 
    
    deque<int> lower;
    deque<int> higher;

    //Initialize
    threshold = 1.0/static_cast<double>(probs_distribution_.size());
    vector<double> probs_temp = probs_distribution_;
    for(int i=0; i<probs_distribution_.size(); i++){
        alias_ids_.push_back(i);
        alias_vals_.push_back(1.0);
        if(probs_distribution_[i]<threshold){
            lower.push_back(i);
        }else{
            higher.push_back(i);
        }
    }

    while(!lower.empty()&&!higher.empty()){
        int l = lower.front(); 
        int h = higher.front();
        lower.pop_front();
        higher.pop_front();
        alias_ids_[l] = h;
        alias_vals_[l] = probs_temp[l];
        probs_temp[h] -= (threshold-probs_temp[l]);
        if(probs_temp[h]>threshold){
            higher.push_back(h); 
        }else{
            lower.push_back(h);
        }
    }

}

int AliasSampler::GetASample(){
    int bin = rand()%probs_distribution_.size();

    if(GetUniform()<alias_vals_[bin]*probs_distribution_.size()) return bin;

    return alias_ids_[bin];
}

int main(){
    
    double distribution[] = {1.0, 2.0, 3.0, 4.0};
    int length = 4;

    srand(time(NULL));
    vector<int> counter(length, 0);
    AliasSampler sampler;
    sampler.SetDistribution(distribution, length);
    sampler.GenerateAliasTable();
    sampler.Print();
    int t = 20;
    while(t--){
        cout << GetUniform() << endl;
    }
    for(int i=0; i<10000; i++){
        counter[sampler.GetASample()] += 1;
    } 

    for(int i=0; i<length; i++){
        cout << counter[i] << " ";
    }
    cout << endl;

    return 0;
}


