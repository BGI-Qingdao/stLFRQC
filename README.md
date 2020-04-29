# stLFR QC

## Uasge

```
Usage :
     ./stLFRQC [OPTION]

quality control of stLFR reads.

Options  :
        -h/--help         print usage
        --bwa             bwa
        --samtools        samtools
        --python3         python3 from anaconda
        --ref             reference
        --read1           read1
        --read2           read2
        --gap_threshold   max gap distance to treat as same lfr
        --cpu             thread for bwa & samtools

Example  :

 ./stLFRQC --ref ref.fa --read1 r1.fq.gz --read2 r2.fq.gz \
           --bwa /path/to/bwa --samtools /path/to/samtools \
           --python3 /path/to/python3

```

## Output

**all in 10.report.tar.gz**

current it contains :
```
02.ngs.basic.txt
02.ngs.indel.txt
03.cumulative_depth_freq.png
03.depth_detail.txt
03.depth_freq.png
06.lfr_length.txt
06.lfr_per_barcode.txt
06.lfr_readpair.txt
```
