#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
typedef tuple<int,int,int> T;
typedef tree<T,null_type,less<T>, rb_tree_tag,tree_order_statistics_node_update> ordered_set;

