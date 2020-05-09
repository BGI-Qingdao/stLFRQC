#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <numeric>
// lfr-length-distrubution , bined by 1000 bp
std::map<int , int > lfr_readpair_freq;
std::vector<int> readpair_cache;
void incr(int rp) {
    if( lfr_readpair_freq.find(rp) == lfr_readpair_freq.end() )
        lfr_readpair_freq[rp]=1;
    else
        lfr_readpair_freq[rp]++;
    readpair_cache.push_back(rp);
}

int main()
{
    // cache all lfr info
    std::vector<std::vector<int>> cache ;
    // 1. load long_fragment_detail.txt
    int prev_barcode = -1 ;
    std::string line ;
    std::getline(std::cin,line); // remove header
    while( ! std::cin.eof() ) {
        int tmp , barcode , rp , length;
        std::cin>>barcode>>tmp>>rp>>tmp>>length;
        if(barcode != prev_barcode ) {
            prev_barcode = barcode ;
            cache.push_back(std::vector<int>());
        }
        cache[cache.size()-1].push_back(rp);
    }

    // 2. filter valid lfr information
    int min_brp = 5 ; // min read-pair-number of valid barcode
    int min_lrp = 3 ; // min read-pair-number of valid lfr
    std::cerr<<"##############\t################"<<std::endl;
    std::cerr<<"Barcode-filter\tread-pair<"<<min_brp<<std::endl;
    std::cerr<<"LFR-filter\tread-pair<"<<min_lrp<<std::endl;
    for(const auto & d : cache ) {
        int br = 0 ; // read-pair in barcode
        int v = 0  ; // valid barcode or not
        if( d.size() == 1 ) {
            v =1;
            br=d.at(0);
        }else {
            for( int p : d ) {
                br += p ;
                if ( p >=min_lrp )
                    v=1; 
            }
        }
        if( v==1 && br >=min_brp ) {
            if( d.size() == 1 ) 
                incr(d.at(0));
            else {
                for( int  p : d )
                    if ( p >=min_lrp ) 
                        incr(p);
            }
        }
    }

    std::sort(readpair_cache.begin(),readpair_cache.end());
    long long sum = 0;
    for( long long x : readpair_cache) sum += x ;
    std::cerr<<"Average-lfr-readpair\t"<<sum/readpair_cache.size()<<std::endl;
    std::cerr<<"Min-lfr-readpair\t"<<readpair_cache.at(0)<<std::endl;
    std::cerr<<"Max-lfr-readpair\t"<<readpair_cache.at(readpair_cache.size()-1)<<std::endl;
    std::cerr<<"Median-lfr-readpair\t"<<readpair_cache.at(readpair_cache.size()/2)<<std::endl;
    std::cerr<<"LFR-readpair\tcount\n";
    for(const std::pair<long,long> & p : lfr_readpair_freq){
        std::cerr<<p.first<<"\t"<<p.second<<"\n";
    }
}
