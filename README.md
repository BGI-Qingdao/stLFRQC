

```
Usage :
     ./stLFRQC [OPTION]

quality control of stLFR reads.

Options  :
        -h/--help     print usage
        --bwa         bwa
        --samtools    samtools
        --python3     python3 from anaconda
        --ref         reference
        --read1       read1
        --read2       read2
        --cpu         thread for bwa & samtools

Example  :

 ./stLFRQC --ref ref.fa --read1 r1.fq.gz --read2 r2.fq.gz \
           --bwa /path/to/bwa --samtools /path/to/samtools \
           --python3 /path/to/python3

```
