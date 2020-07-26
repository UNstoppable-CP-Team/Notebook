  /*
  oo =  infinite distance
  n = number of nodes
  adj = graph saved in an adjacency list
  processed[i] = if node i has already been processed
*/
for (int i=1;i<=n;i++){ 
  distance[i] = oo; 
} 
distance[x] = 0; 
q.push({0,x}); 
while (!q.empty()) { 
  int a = q.top().second; q.pop(); 
  if (processed[a]) continue; 
    processed[a] = true; 
    for (auto u : adj[a]) { 
      int b = u.first, w = u.second; 
      if (distance[a]+w < distance[b]) { 
        distance[b] = distance[a]+w; 
        q.push({-distance[b],b}); 
      } 
    } 
}
