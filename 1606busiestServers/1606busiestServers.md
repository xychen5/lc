
## 1606busiestServers 找到处理最多请求的服务器

### 1 题目：
[https://leetcode-cn.com/problems/find-servers-that-handled-most-number-of-requests/](https://leetcode-cn.com/problems/find-servers-that-handled-most-number-of-requests/)

### 2 解题思路：
- 1 自然的思路：对于每一个到来的请求，我们将服务器分为两部分，一部分是空闲服务器，一部分是繁忙服务器
  - 1.1 如何快速找到空闲服务器？我们用set记录空闲服务器即可，两次使用lower_bound完成cycle查询
  - 1.2 如何记录繁忙服务器？在每一个请求到来以及处理完成，都可能出现繁忙服务器的改动和空闲服务器的改动，于是采用map<到期时间，相应服务器列表>来存储繁忙服务器
  - 1.3 如何处理请求处理完成时的服务器从繁忙变为空闲？
    - 1.3.1 采用小根堆存储当前所有繁忙服务器的到期时间，那么只需要在请求到来的时候，将所有比当前请求小的到期时间的繁忙服务器变为空闲即可

```cpp
class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        // using small root heap to store the smallest avaliable server
        // auto cmp = [](const int& a, const int b) 
        set<int, std::less<int>> spareServers;
        map<int, vector<int>> busyServers;
        priority_queue<int, vector<int>, std::greater<int>> dues;
        vector<pair<int, int>> serverSumLoad;

        for(int i = 0; i < k; ++i) {
            spareServers.insert(i);
            serverSumLoad.push_back(make_pair(i,0));
        }

        // deal request
        int reqNum = arrival.size();
        int arrivalIdx = 0;
        for(int arrival : arrival) {
            // cout << "req: " << arrival << "load: " << load[arrivalIdx] << endl;
            // release servers
            while(!dues.empty() && dues.top() <= arrival) {
                int due = dues.top();
                dues.pop();
                vector<int>& toRelease = busyServers[due];
                for(auto i : toRelease) {
                    spareServers.insert(i);
                    // cout << "releasing " << i << endl;
                }
                // busyServers.erase(due);
            }

            // abandon the request
            if(spareServers.empty()) {
                ++ arrivalIdx;
                // cout << "abandon!" << endl;
                continue;
            }

            // request distribute, find the server
            int tarServer = -1;
            auto itr = spareServers.lower_bound(arrivalIdx % k);
            // cout << "trying to find: " << arrivalIdx % k << endl;
            if(itr != spareServers.end()) {
                tarServer = *itr;
                // cout << "find tar1: " << tarServer << endl;
            } else { // search from the start just like search like a cycle
                tarServer = *spareServers.lower_bound(0);
                // cout << "find tar2: " << tarServer << endl;
            }
            spareServers.erase(tarServer);
            
            // set the server to busy
            int due = arrival + load[arrivalIdx];
            if(busyServers.find(due) == busyServers.end()) {
                vector<int> tmpVec = {tarServer};
                busyServers[due] = tmpVec;
                dues.push(due);
                // cout << "init busy due : " << tarServer << " to " << due << endl;
            } else {
                busyServers[due].push_back(tarServer);
                // cout << "add busy due : " << tarServer << " to " << due << endl;
            }
            serverSumLoad[tarServer].second ++;

            ++ arrivalIdx;
        }

        sort(serverSumLoad.begin(), serverSumLoad.end(),[](
            const pair<int, int>& p1, const pair<int, int>& p2
        ) {
            return p1.second > p2.second;
        });
        
        // for(int ed = 0; ed < serverSumLoad.size(); ++ed) {
        //     cout << "server: " << serverSumLoad[ed].first << " > " << serverSumLoad[ed].second << endl;
        // }
        int ed = 1;
        vector<int> res = {serverSumLoad[0].first};
         
        
        for(; ed < serverSumLoad.size(); ++ed) {
            if(serverSumLoad[ed].second != serverSumLoad[0].second) {
                break;
            }
            res.emplace_back(serverSumLoad[ed].first);
        }
        
        return res;
    }
};
```