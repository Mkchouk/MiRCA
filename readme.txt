MiRCA
Hybrid Error Correction Tool for NGS Long Reads

v1.1

The new MinIon sequencer provided by the Oxford Nanopore Technologies is characterized by his small size and is powered from the USB 3.0 port of a laptop computer. This sequencer produces long reads with a low production costs and with high throughput. However, long reads generated by the MinIon sequencer have a high error rate which deteriorates the quality of results obtained by analyzing these long reads. A solution to correct long reads is to use the high coverage and the high quality of short reads generated by the second generation sequencing technology.

We present MiRCA a new hybrid approach that detects and corrects errors using preassembled Illumina short reads. It uses an alignment-based approach, supports substitution, insertion and deletion errors, using pre-assembled short reads as a reference to correct MinIon long reads.

Requirements

A Linux based operating system.
Spades assembler v3.6 (at least) available in http://bioinf.spbau.ru/en
BLAST+ v2.2.30plus (at least) available in https://blast.ncbi.nlm.nih.gov/Blast.cgi?PAGE_TYPE=BlastDocs&DOC_TYPE=Download
Celera Assembler v8.3 (at least) this step is optionnal. if you want to assemble the corrected Long reads.
Download MiRCA

MiRCA can be downloaded at :

https://github.com/Mkchouk/MiRCA
Install MiRCA

To install the tool, the user must download the file MiRCA-master.zip and extract it.

tar -xzf MiRCA-master.zip
Run MiRCA

The package contains one main script called MiRCA.sh that coordinates the execution of the whole process.

chmod +x MiRCA.sh
./MiRCA.sh
You must modify the MiRCA.sh file by adding the paths of short reads (.FASTA or .FQ) and long reads reads (.FASTA). In the MiRCA.sh, you must change the directories of files results of spades and Blast+ in the current directory.

There are Two Mode in MiRCA:

First Mode Default Mode (main.c): update the input and output files by changing the path of the alignment results file and the long file reads path.
First Mode Trim Mode (main_trim.c): update the input and output files by changing the path of the alignment result file and the long file reads path (further explanation in main_trim.c).
The ssembly consists of long corrected reads using Celera assembler but this step is optional for those who want the assembly.

DataSets Used

we used the Long reads gerated from MinIon sequencer and short reads generated by Illumina.

Copyright

Copyright (c) 2016
