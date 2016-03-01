#!/bin/sh

#Copyright (c) 2016 by Mehdi Kchouk  (mehdi.kchouk@gmail.com) and Mourad Elloumi


#Create Contigs from Illumina Short Reads
#must fix the path of spades.py and you have to put the path of paired-end short reads

link_to/spades.py -k 125 --careful --only-assembler -1 Illumina_R1.fastq -2 Illumina_R2.fastq -o spades_output

#Create BlastDB

makeblastdb -in pathTo/spades_output/K125/final_contigs.fasta -dbtype nucl -out contigDB

#Alignment Long reads To Contigs using BLASTn

link_to/blastn -query /pathToLongReads.fa -db contigDB -out Alignresults -outfmt "10 qseqid sseqid qstart qend qseq sseq" -reward 5 -penalty -4 -gapopen 10 -gapextend 6 -dust no -evalue 10e-10

#Correcting Error in Long Reads and generating Corrected Long Reads
#gcc main6.c
gcc main_trim.c
./a.out

#Assembly Step (Optionnal)
#runCA -p directory -d directory Corrected_reads.frg
