# MiRCA
Hybrid Error Correction Tool for NGS Long Reads


We present MiRCA a new hybrid approach that detects and corrects errors using preassembled Illumina short reads. It uses an alignment-based approach, supports substitution, insertion and deletion errors, using pre-assembled short reads as a reference to correct MinIon long reads.

#####Requirements

- A Linux based operating system.
- Spades assembler v3.6 (at least) available in http://bioinf.spbau.ru/en
- BLAST+ v2.2.30plus (at least) available in https://blast.ncbi.nlm.nih.gov/Blast.cgi?PAGE_TYPE=BlastDocs&DOC_TYPE=Download
- Celera Assembler v8.3 (at least) this step is optionnal. if you want to assemble the corrected Long reads.

#####Download MiRCA
MiRCA can be downloaded at : 
- https://github.com/Mkchouk/MiRCA

#####Install MiRCA
To install the tool, the user must download the file **MiRCA-master.zip** and extract it.
```
tar -xzf MiRCA-master.zip
```
#####Running MiRCA
This section describes the different steps required to use MiRCA. 
The package contains one main script MiRCA.sh that coordinates the execution of the whole process.

You must modify the MiRCA.sh file by adding the paths of short reads  (.fastq or fq) and long reads reads (.FASTA) and the path of resulting file to the current directory.

There are Two Mode in MiRCA: the Default Mode and Trim Mode.
- For `Default Mode`: You must modify the input and the output files in main.c by the result of alignment file from alignment with Blast+ and the Long reads file (.FASTA).
- For `Trim Mode`: You must modify the input and the output files in main_trim.c by the result of alignment file from alignment with Blast+ and the Long reads file (.FASTA).




