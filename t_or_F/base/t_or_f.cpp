#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <exception>
#include <new>
#include <vector>
#include <string>
#include <cstdlib>
#include <iterator>
#include <fstream>
#include <chrono>
#include <sstream>
#include <tuple>
#include <memory>
#include <utility>

uint64_t index_univ = 0;

std::vector<std::string> vec(2,"");


struct
{
    std::vector<std::string> first;
    int second = 0;
} pvec;

std::vector<std::string> algo(int n)
{
    try
    {
        if(n<1 || n>25) throw std::out_of_range("n>20");
        if(n==1)
        {

            try
            {
                vec = {"F","T"};
                return vec;
            }
            catch(std::exception e)
            {
                std::cerr << "EXIT";
            }
        }
        else
        {
            try
            {
                auto vec = algo(n-1);
                assert(vec[0]!="");

                vec.reserve(2*vec.size());

                copy(vec.begin(),vec.end(),std::back_inserter(vec));

                uint64_t index = 0;
                for(auto &elem : vec)
                {
                    if(index < (vec.size()/2))
                        elem+="T";
                    else
                        elem += "F";
                    index++;
                    index_univ++;
                }
                //std::cout<<"Index: "<<index_univ<<"\n";
                return vec;
            }

            catch(const std::exception &e)
            {
                std::cerr << __func__ <<
                __LINE__ << e.what() << " Error!";
            }
        }
    }
    catch(std::out_of_range &e)
    {
        std::cerr << e.what() <<" Out_of_range!";
        exit(1);
    }
    catch(const std::exception &e)
    {
        std::cerr<<e.what()<<__func__<<":"<<__LINE__<<":"<<"error";
    }
    catch(...)
    {
        std::cerr<<__func__<<":"<<__LINE__<<":"<<"error";
        exit(1);
    }
}

void print_to_file(int i,std::vector<std::string> v)
{
    std::ofstream file;
    std::stringstream ss;
    ss << i;
    std::string st = ss.str();
    std::string filename = "out/out"+ st +".txt";
    file.open(filename);
    file << i << std::endl;

    for(const auto &elem : v)
    {
        file << elem << "\n";
        //std::cout << elem << "\n";
    }
    file << std::endl;

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
            print_to_file(i,v);
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
    catch(...)
    {
        std::cerr<< __func__ << " is exiting at"
            << __LINE__;
        exit(1);
    }
    return 0;
}

