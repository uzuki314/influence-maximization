#ifndef ASIM_ALGORITHM_H
#define ASIM_ALGORITHM_H
#include<unordered_set>
#include<unordered_map>
#include"graph.h"
#include"LT.h"

typedef std::unordered_set<int> uset;

double assignScore(DirectedGraph &G, size_t u, uset &C, int d){
    if(d==0)return 0;
    auto out = G.getNodeOutNeighbors(u);
    double sum = 0;
    for (size_t j = 0; j < out.size(); j++)
    {
        if(C.find(out[j]) != C.end())continue;
        double influence = G.getEdgeInfluence(u,out[j]);
        double threshold = G.getNodeThreshold(out[j]);
        auto inn = G.getNodeInNeighbors(out[j]);
        vector<int> active_in;
        for (size_t i = 0; i < inn.size(); i++)
        {
            if(C.find(inn[i]) != C.end()) active_in.push_back(inn[i]);
        }
        sum += (1.0 + influence - threshold + influence_sum(&G,out[j],active_in)) + assignScore(G,out[j],C,d-1);
        // sum += (1.0 + influence - threshold) * assignScore(G,out[j],C,d-1);
        // sum+= influence + assignScore(G,out[j],C,d-1);
        G.getNodeThreshold(u);
    }
    return sum;
}

/**
 * @brief 
 * @param S seedSet
 * 
 * @param G Graph
 * @param k seedNumber
 * @return std::unordered_set<int> 
 */
uset seedSelection(DirectedGraph &G, int k){
    uset S, C;
    for (int i = 0; i < k; i++)
    {
        double max = 0;
        int maxID = 0;
        size_t vSize = G.getNodeNumber();
        for (size_t u = 1; u <= vSize; u++)
        {
            if(S.find(u)!=S.end()) continue;
            double sum = assignScore(G,u,C,2);
            if(sum>max){
                max = sum;
                maxID = u;
            }
        }
        S.insert(maxID);
        auto cc = diffuse_all(&G,S);
        C.insert(cc.begin(),cc.end());
    }
    return S;
}
#endif