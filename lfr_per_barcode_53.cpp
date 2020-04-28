#include <vector>
#include <iostream>


int main()
{
    int lfr_freq[20];
    for( int i = 0 ; i < 20 ; i++ ) { lfr_freq[i] = 0 ;}
    int prev_barcode = -1 ;
    std::string line ;
    std::getline(std::cin,line); // remove header
    std::vector<std::vector<int> > cache ;
    while( ! std::cin.eof() ) {
        int tmp , barcode , rp ;
        std::cin>>barcode>>tmp>>rp>>tmp>>tmp;
        if(barcode != prev_barcode ) {
            prev_barcode = barcode ;
            cache.push_back(std::vector<int>());
        }
        cache[cache.size()-1].push_back(rp);
    }
    for ( int i = 1 ; i < 6 ; i++ ){
        std::cerr<<"##############\t################"<<std::endl;
        std::cerr<<"LFR-filter\tread-pair<"<<i<<std::endl;
        int b = 0 ;int bm = 0; int l = 0;
        int b5 = 0 ;int bm5 = 0; int l5 = 0;
        int bi = 0 ;int bi5 = 0; int li = 0;
        int bib = 0 ; int biv=0 ; int bil=0;
        for(const auto & d : cache ) {
            int br = 0 ; // read-pair in barcode
            int v = 0; // valid barcode or not
            int lc = 0 ;
            if( d.size() == 1 ) {
                lc =1 ; ;
                v =1;
                br=d[0];
            }else {
                for( int r : d ) {
                    br += r ;
                    if (r >=i) { lc ++; v=1; }
                }
            }
            l += lc;
            b += v ;
            if ( br >5 ) {
                b5 ++ ;
                bm5 +=v ;
                l5 +=lc;
            }
            if ( br >i ) {
                bi ++ ;
                bi5 +=v ;
                li +=lc;
            }
            if( br > 1 )
                bm +=v ;
            if( i == 1 ){
                if( br > 1 &&br <= 5 ){
                    biv += v ;
                    bib += 1;
                    bil +=lc;
                }
            }
            if( i == 3 && br >=5 ) { 
                if( lc > 0 && lc < 20 ) lfr_freq[lc-1]++;
                if( lc > 20 ) lfr_freq[19]++;
            }
        }
        std::cerr<<"Totoal-data\t---------"<<std::endl;

        std::cerr<<"total_barcode\t"<<cache.size()<<std::endl;
        std::cerr<<"uncertain_barcode\t"<<cache.size()-b<<std::endl;
        std::cerr<<"valid_barcode\t"<<b<<std::endl;
        std::cerr<<"valid_lfr\t"<<l<<std::endl;
        std::cerr<<"valid_lfr/valid_barcode\t"<<float(l)/float(b)<<std::endl;

        std::cerr<<"barcode-read-pair>1\t---------"<<std::endl;
        std::cerr<<"total_barcode\t"<<cache.size()-(b-bm)<<std::endl;
        std::cerr<<"uncertain_barcode\t"<<cache.size()-b<<std::endl;
        std::cerr<<"valid_barcode\t"<<bm<<std::endl;
        std::cerr<<"valid_lfr\t"<<l-(b-bm)<<std::endl;
        std::cerr<<"(valid_lfr/valid_barcode)\t"
                                     <<float(l-(b-bm))/float(bm)<<std::endl;

        std::cerr<<"barcode-read-pair>"<<i<<"\t---------"<<std::endl;
        std::cerr<<"total_barcode\t"<<bi<<std::endl;
        std::cerr<<"uncertain_barcode\t"<<bi-bi5<<std::endl;
        std::cerr<<"valid_barcode\t"<<bi5<<std::endl;
        std::cerr<<"valid_lfr\t"<<li<<std::endl;
        std::cerr<<"(valid_lfr/valid_barcode)\t"
                                     <<float(li)/float(bi5)<<std::endl;
        std::cerr<<"barcode-read-pair>5\t---------"<<std::endl;
        std::cerr<<"total_barcode\t"<<b5<<std::endl;
        std::cerr<<"uncertain_barcode\t"<<b5-bm5<<std::endl;
        std::cerr<<"valid_barcode\t"<<bm5<<std::endl;
        std::cerr<<"valid_lfr\t"<<l5<<std::endl;
        std::cerr<<"(valid_lfr/valid_barcode)\t"
                                     <<float(l5)/float(bm5)<<std::endl;
        if( i == 1 ){
            std::cerr<<"total_barcode(if-1<barcode-read-pair<=5)\t"<<bib<<std::endl;
            //std::cerr<<"uncertain_barcode(if-1<barcode-read-pair<=5))\t"<<bib-biv<<std::endl;
            std::cerr<<"valid_barcode(if-1<barcode-read-pair<=5)\t"<<biv<<std::endl;
            std::cerr<<"valid_lfr(if-1<barcode-read-pair<=5)\t"<<bil<<std::endl;
            std::cerr<<"valid_lfr/valid_barcode(if-1<barcode-read-pair<=5)\t"<<float(bil)/float(biv)<<std::endl;
        }
    }
    std::cerr<<"\nvalid-lfr-per-barcode-count:\n";
    for( int i = 0 ; i < 20 ; i++ ){
        std::cerr<<i+1<<'\t'<<lfr_freq[i]<<'\n';
    }
    std::cerr<<"notice : >20 count in 20!\n";
}
