/*
    ftd 0.96 (30 March 2005)

   This program (ftd), coded by Jia Yang and Ulrich Speidel, is an implementation of an
   efficient T-decomposition algorithm proposed by Jia Yang and Ulrich Speidel. 
   
   ftd provides T-decomposition-based information measures for finite strings. The 
   principle of T-decomposition and the concepts of T-decomposition-based information measures 
   were initially proposed by Mark R. Titchener.
   
   Copyright (C) 2005, Jia Yang and Ulrich Speidel, The University of Auckland.
   All rights reserved.                          
   
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote 
        products derived from this software without specific prior written 
        permission.

     4. Modification is permitted for research purposes only and any
        code resulting from modification of the code provided herein
        must be made available to the public under the same license 
        provisions. 

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER
   OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

   Contact information:

   Jia Yang: jyan055@cs.auckland.ac.nz
   Ulrich Speidel: ulrich@cs.auckland.ac.nz
*/

#ifndef _TANALYZE_H
#define _TANALYZE_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK_TANALYZE 0
#define ERROR_TANALYZE -1
#define TRUE_TANALYZE 1
#define FALSE_TANALYZE 0

#define UINT32_TANALYZE unsigned long
#define INT32_TANALYZE int     
#define UINT16_TANALYZE unsigned short

#define BUFF_PIPE 5000000

#define MAXIT 100          
#define EULER 0.5772156649
#define FPMIN 5.0e-308
#define EPS 5.0e-16

#define OFFSET_TINFO -0.7582198

/*The following three values for I32_Opt decide what the function func_Calculate () will print out. The lowest two bits corresponding to these three options. */
#define OPT_NO_PRINTOUT 0                             /*No print out at all. */
#define OPT_TDECOMPOSITION_PRINTOUT 1   /*Display the T-decomposition process. All the T-prefixes and T-expansion parameters will be shown.*/
#define OPT_STEPINFO_PRINTOUT 2                /*If true the T-information, T-complexity and T-entropy will be displayed for eash run. In other words,*/
                                                                       /*the T-information, T-complexity and T-entropy values of the suffix string that has been parsed into onle codeword*/ 
                                                                       /*during each run will be displayed.*/
#define OPT_LOG2BASED 4                             /*Determine whether the base of log is 2 or e. This option will affect the T-information and T-entropy. The third lowest bit corresponding to  this option.*/                                                     

#define OPT_OFFSET_TINFO 8                       /*Let the constant offset value "OFFSET_TINFO"  be the second parameter of the function func_Tinformation(). Oftherwise*/
                                                                      /*this parameter will be set "0". This second parameter is to make sure the T-information of a string with length 1*/
                                                                      /*is 1 (assume that it is based on log_2).*/
#define MAX_STEPSAMPLE_INTERVAL 65536  /*The maximun interval (2^16) for step information sample.*/

typedef struct STRU_CODEWORDLIST  /*Struct type for the match lists (which link the same codewords together based on their IDs, and the string list (which links all the codewords together).*/
{  
    UINT32_TANALYZE U32_CodeWordID;
    struct STRU_CODEWORDLIST *p_CODEWORD_NextCodeWordInMatchList;  /*Pointer to the next codeword in the corresponding match list.*/
    struct STRU_CODEWORDLIST *p_CODEWORD_PreviousCodeWordInMatchList;    /*Pointer to the previous codeword in the corresponding match list.*/
    struct STRU_CODEWORDLIST *p_CODEWORD_NextCodeWordInStringList;    /*Pointer to the next codeword in the string list.*/
    struct STRU_CODEWORDLIST *p_CODEWORD_PreviousCodeWordInStringList;  /*Pointer to the previous codeword in the string.*/
    
}STRU_CODEWORD; 

typedef struct STRU_MATCHLISTENTRY_DEF  /*Struct type for the entry list which store the heads of all the match lists. These heads are dummy heads, in other words, no real data will be stored there.*/
{  
    UINT32_TANALYZE U32_CodeWordID;
    struct STRU_CODEWORDLIST *p_CODEWORD_NextCodeWordInMatchList;    /*Pointer to the first codeword in the the match list.*/
    struct STRU_CODEWORDLIST *p_CODEWORD_PreviousCodeWordInMatchList;    /*Pointer to the end node that is also the last inserted node in the match list.*/
    
}STRU_MATCHLISTENTRY;

INT32_TANALYZE func_Calculate(const char *pc_String, UINT32_TANALYZE U32_LengthOfString, double *pd_Tcomplexity, double *pd_Tentropy, 
    	    double *pd_Tinformation, INT32_TANALYZE I32_Opt);  /*About I32_Opt, look at OPT_NO_PRINTOUT, OPT_TDECOMPOSITION_PRINTOUT etc.*/
INT32_TANALYZE func_StringUnpack (char **ppc_StringUnpacked, char *pc_StringToUnpack, UINT32_TANALYZE *pU32_LengthOfString);  /*Unpack a string (1 bit => 1 byte. For example 1=> '1', 0=>'0').*/

#endif
