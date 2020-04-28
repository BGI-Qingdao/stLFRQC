#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <numeric>
#include <cassert>
// lfr-length-distrubution , bined by 1000 bp
std::map<int , int > lfr_length_freq_1000;
// lfr-length-cache : for min ,max and median
std::vector<long long> length_cache;

void incr(int length) {
    assert(length > 0 );
    int b_index=length/1000;
    if( lfr_length_freq_1000.find(b_index) == lfr_length_freq_1000.end() )
        lfr_length_freq_1000[b_index]=1;
    else
        lfr_length_freq_1000[b_index]++;
    length_cache.push_back(length);
}

int main()
{
    // cache all lfr info
    std::vector<std::vector<std::pair<int,int>> > cache ;

    // 1. load long_fragment_detail.txt
    int prev_barcode = -1 ;
    std::string line ;
    std::getline(std::cin,line); // remove header
    while( ! std::cin.eof() ) {
        int tmp , barcode , rp , length;
        std::cin>>barcode>>tmp>>rp>>tmp>>length;
        if(barcode != prev_barcode ) {
            prev_barcode = barcode ;
            cache.push_back(std::vector<std::pair<int,int>>());
        }
        assert(length>0);
        cache[cache.size()-1].push_back(std::make_pair(rp,length));
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
            br=d.at(0).first;
        }else {
            for( const std::pair<int,int> & p : d ) {
                br += p.first ;
                if ( p.first >=min_lrp )
                    v=1; 
            }
        }
        if( v==1 && br >=min_brp ) {
            if( d.size() == 1 ) 
                incr(d.at(0).second);
            else {
                for( const std::pair<int,int> & p : d )
                    if ( p.first >=min_lrp ) 
                        incr(p.second);
            }
        }
    }
    std::sort(length_cache.begin(),length_cache.end());
    long long sum = 0 ;
    for( long x : length_cache) sum +=x ;
    std::cerr<<"Average-lfr-length\t"<<sum/length_cache.size()<<std::endl;
    std::cerr<<"Min-lfr-length\t"<<length_cache.at(0)<<std::endl;
    std::cerr<<"Max-lfr-length\t"<<length_cache.at(length_cache.size()-1)<<std::endl;
    std::cerr<<"Median-lfr-length\t"<<length_cache.at(length_cache.size()/2)<<std::endl;
    std::cerr<<"LFR-length/1000\tcount\n";
    for(const std::pair<long,long> & p : lfr_length_freq_1000 ){
        std::cerr<<p.first<<"\t"<<p.second<<"\n";
    }
}
