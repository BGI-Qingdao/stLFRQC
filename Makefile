all: lfr_per_barcode_53 lfr_length_53 lfr_readpair_53


lfr_per_barcode_53: lfr_per_barcode_53.cpp
	g++ -std=c++11 -g lfr_per_barcode_53.cpp -o lfr_per_barcode_53

lfr_length_53: lfr_length_53.cpp
	g++ -std=c++11 -g lfr_length_53.cpp -o lfr_length_53

lfr_readpair_53: lfr_readpair_53.cpp
	g++ -std=c++11 -g lfr_readpair_53.cpp -o lfr_readpair_53

clean:
	rm -rf lfr_per_barcode_53 lfr_length_53 lfr_readpair_53
