#include <bits/stdc++.h >
using namespace std;

string get_last_n_bits(int x, int n)
{
    int cnt = 0;
    string res = "";
    while (cnt < n)
    {
        int w = x % 2;
        x /= 2;
        if (!w)
            res.push_back('0');
        else
            res.push_back('1');

        ++cnt;
    }
    reverse(res.begin(), res.end());
    return res;
}

int main()
{
    int global_depth, bucket_capacity;
    cin >> global_depth >> bucket_capacity;

    int cur_depth = global_depth;
    vector<set<int>> buckets((1ll << global_depth));
    map<string, int> directory;
    vector<int> local_depth(20, 1);

    // set<int> s;
    // s.clear();

    directory["0"] = 0;
    directory["1"] = 1;
    // buckets.push_back(s);
    // buckets.push_back(s);
    --global_depth;
    while (global_depth--)
    {
        map<string, int> temp_map;
        for (auto it : directory) // doubling the directory
        {
            string w = it.first;
            int y = it.second;
            w = "0" + w;
            string w1 = "1" + it.first;
            temp_map[w] = y;
            temp_map[w1] = y;
            //   cout << val << endl;
            // directory.erase(directory.find(it->first));
        }
        directory.clear();
        directory = temp_map;
        temp_map.clear();
    }
    // for(auto it : directory)
    // {
    //     cout<<it.first<<" "<<it.second<<endl;
    // }

    int cntr = 0; // increment this when a new entry is added in the bucket.
    // cout << "Enter operation to be performed"
    //      << "\n";
    for (auto it = directory.begin(); it != directory.end(); ++it)
    {
        it->second = cntr;
        ++cntr;
    }
    int p = 7;
    while (1)
    {
        int op;
        cin >> op;
        // insertion
        if (op == 2)
        {
            int val;
            cin >> val;

            string x = get_last_n_bits(val, cur_depth);

            // if ((directory.find(x)->second) == -1) // if the bucket is not there, make it
            // {

            //     set<int> temp;
            //     temp.insert(val);
            //     buckets.push_back(temp);
            //     directory[x] = buckets.size() - 1;
            //     ++cntr;
            // }

            if (buckets[directory[x]].size() >= bucket_capacity) // if bucket cap is full,double the directory
            {

                ++cur_depth;
                // map<string, int>::iterator it;
                map<string, int>::iterator it4 = directory.end();
                map<string, int> temp_map;

                for (auto it : directory) // doubling the directory
                {
                    string w = it.first;
                    int y = it.second;
                    w = "0" + w;
                    string w1 = "1" + it.first;
                    temp_map[w] = y;
                    temp_map[w1] = y;
                    //  cout << val << endl;
                    // directory.erase(directory.find(it->first));
                }
                directory.clear();
                directory = temp_map;
                temp_map.clear();
                x = get_last_n_bits(val, cur_depth);
                auto it2 = directory.find(x);
                int ind = it2->second;
                set<int> corresponding_element;
                string h;
                vector<int> temp;
                for (auto it : buckets[ind])
                {
                    if (x != get_last_n_bits(it, cur_depth))
                    {
                        h = get_last_n_bits(it, cur_depth);
                        corresponding_element.insert(it);
                        temp.push_back(it);
                    }
                }
                for (auto it : temp)
                {
                    buckets[ind].erase(buckets[ind].find(it));
                }

                buckets.push_back(corresponding_element);
                directory[h] = buckets.size() - 1;
                ++cntr; // increment cntr after insertion
                buckets[ind].insert(val);
            }
            else
            {

                buckets[directory[x]].insert(val);
                // else
                // {
                //     cout << directory[x] << " " << val << endl;
                // }

                //  cout << buckets[directory[x]].begin() << "* " << endl;
            }
        }
        // searching
        else if (op == 3)
        {
            int val;
            cin >> val;

            string y = get_last_n_bits(val, cur_depth);
            if (directory.find(y) == directory.end())
                cout << "DNE" << endl;
            int ind = directory[y];
            if (buckets[ind].find(val) == buckets[ind].end())
            {
                cout << "DNE" << endl;
            }
            else
            {
                cout << "FOUND" << endl;
            }
        }
        else if (op == 4)
        {

            int val;
            cin >> val;

            string y = get_last_n_bits(val, cur_depth);
            if (directory.find(y) == directory.end())
                cout << "DNE" << endl;
            int ind = directory[y];
            if (buckets[ind].find(val) == buckets[ind].end())
            {
                cout << "DNE" << endl;
            }
            else
            {
                buckets[ind].erase(buckets[ind].find(val));
            }
        }
        else if (op == 5)
        {
            for (auto x : directory)
            {
                cout << x.first << ": ";
                for (auto y : buckets[x.second])
                {
                    cout << y << " ";
                }
                cout << endl;
            }
        }
        else if (op == 6)
        {
            break;
        }
    }

    return 0;
}