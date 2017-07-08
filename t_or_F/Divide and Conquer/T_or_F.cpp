#include <iostream>
#include <new>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <tuple>
#include <utility>
#include <chrono>
#include <sstream>
#include <fstream>
#include <iterator>
#include <string>
#include <cassert>
#include <algorithm>

uint64_t index_univ = 0;

std::vector<std::string> vec = {"T","F"};

std::vector<std::vector<std::string>> vecGrp(10,vec);
uint64_t index = 1;



template <typename T>
std::string toStr(T toChange)
{
    std::stringstream ss;
    ss << toChange;
    std::string retStr = ss.str();
    return retStr;
}

std::string create_binary(uint64_t n)
{
    std::string retStr;
    while(n!=0)
    {
        uint64_t bin = n%2;
        auto ins = toStr<uint64_t>(bin);
        retStr += ins;
        n/=2;
    }
    reverse(retStr.begin(),retStr.end());
    return retStr;
}

bool createBinIndex(uint64_t index)
{

    const auto &vecB = vecGrp[index-2];

    auto &vec = vecGrp[index-1];
    vec = vecB;
    uint64_t k_ = vec.size();
    try{
    vec.reserve(vec.size()^2);
    }
    catch(...)
        {
            std::cerr << "err1";
            throw std::bad_alloc();
        }

    uint64_t i=1;

    while(i<k_)
    {
        try
        {
        copy(vecB.begin(),vecB.end(),std::back_inserter(vec));
        }
        catch(...)
        {
            std::cerr << "err2";
            throw std::bad_alloc();
        }
        i++;
    }

    i=0;

    for(auto &elem : vecB)
        {
            //std::cout << i << " ";
            for(uint64_t k=0;k<k_;k++)
            {
                vec[i]+=elem;
                i++;
            }
        }

    return true;
}

bool updateIndex(uint64_t check)
{
    while(index<check)
    {
        ++index;

        try{
            createBinIndex(index);
        }
        catch(const std::exception& e)
        {
                std::cerr<<"\nCaught Exception in "<<__FILE__<<" \nat line "
                    << __LINE__ << " in " << __func__ << " as \n" << e.what();
        }
    }
    return true;
}

std::vector<std::string> transmutate(std::vector<std::string> v1,std::vector<std::string> v2)
{
    if(v2[0]=="") return v1;
    //v2.reserve(v1.size()*v2.size());

    uint64_t s = v1.size();
    //for(auto elem:v2)std::cout<<"\n"<<elem;
    //std::cout<<"s = "<<s<<"\n";
    auto v2c = v2;
    v2.reserve(v1.size()*v2.size());

    uint64_t i=1;
    uint64_t a = floor(log2(v2.size()));
    //std::cout<<a;
    while(i<s)
    {
     copy(v2c.begin(),v2c.end(),std::back_inserter(v2));
        i++;
    }
    i=0;
    for(auto &elem : v1)
    {
       //std::cout<<i<<" ";
        for(uint64_t k=0;k<s;k++)
        {
            //std::cout<<elem<<" "<<v2[i]<<"\n"<<i<<"\n";
            v2[i]+=elem;
            //v2c[i]+=elem;
         //std::cout<<elem<<" "<<v2[i]<<"\n"<<i<<"\n\n";
            i++;
        }
    }
    return v2;
}


std::vector<std::string> mutate(std::string bin)
{
    auto v =vec;
    v={"",""};
    auto k = toStr(1);
    for(uint64_t i=0; i<bin.size(); i++)
    {

        if(bin[i]==k[0]) //std::cout<<"1";
            v=transmutate(vecGrp[bin.size()-i-1],v);
           // for(auto elem : v)
             //   std::cout<<elem<<std::endl;
    }
    return v;
}

std::vector<std::string> algo(uint64_t n)
{
    assert(n>1 && n<25);
    if(n==1)
    {
        return vec;
    }
    else
    {
        const auto bin = create_binary(n);
        auto check = bin.size();

        if(check>index)
        {
            try
            {
                updateIndex(check);
            }
            catch(const std::exception& e)
            {
                std::cerr<<"Caught Exception in "<<__FILE__<<" at line "
                    << __LINE__ << " as " << e.what();
            }
        }
                //std::cout << index;
            if( (n & (n-1)) ==0)
                return vecGrp[index-1];
            auto v = mutate(bin);
            return v;
        }

        return vec;
}

int main()
{
    try
    {
         int n;
        std::cin >> n;


        std::ofstream file;
        std::ofstream file1;
        std::ofstream file2;

        file1.open("ans.txt");
        file2.open("time.txt",std::ios::app);
        file2 << "\n";
        std::vector<int> rng(n);
        std::iota(rng.begin(),rng.end(),1);

        for(auto &i : rng)
        {

            auto start = std::chrono::system_clock::now();
/*
            std::stringstream ss;
            ss << i;
            std::string st = ss.str();

            std::string filename = "out/out"+ st +".txt";
            file.open(filename);
*/
            std::vector<std::string> v = algo(i);
            sort(v.begin(),v.end());
            //file << i << std::endl;
            std::cout << i << std::endl;
            file1 << v.size() <<"\n";
            //print_to_file(i,v);
           /* for(const auto &elem : v)
                {
                    file << elem << "\n";
                    //std::cout << elem << "\n";
                }
            //file << std::endl;
            */
            auto endt = std::chrono::system_clock::now();
            //std::chrono::duration<long long uint64_t, std::nano> diff = endt-start;
            std::chrono::duration<long double> diff = endt-start;

            file2 << i << " " << diff.count() << "\n";
            std::cout << i << " " << diff.count() << "\n";
            file.close();
        }
        return 0;
    }
    catch(const std::exception &e)
    {
        std::cerr<<"Caught Exception in "<<__FILE__<<" at line "
            << __LINE__ << " as " << e.what();
    }
}
