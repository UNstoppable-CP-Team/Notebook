/*
  oo =  infinite distance
  n = number of nodes
  edges = graph saved in an edge list
*/
for (int i=1;i<=n;i++){ 
  distance[i] = oo; 
} 
  distance[x] = 0; 
  for (int i = 1; i <= n-1; i++) { 
    for (auto e : edges) { 
    int a, b, w; tie(a,b,w)=e; 
    distance[b] = min(distance[b], distance[a]+w); 
    } 
}
