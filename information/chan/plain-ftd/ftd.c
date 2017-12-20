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

#include "ftd.h"

void func_PrintResult(const char *pc_DatatoPrint, UINT32_TANALYZE US32_Length, UINT32_TANALYZE U32_TexpansionParameter); /*Print out the result (T-expansion parameters and T-prefixes).*/
double func_Tinformation (double d_Tcomplexity, double d_Offset);
double ei (double);


INT32_TANALYZE func_StringUnpack (char **ppc_StringUnpacked, char *pc_StringToUnpack, UINT32_TANALYZE *pU32_LengthOfString)
{
    UINT32_TANALYZE U32_Length_UnpackedString = (*pU32_LengthOfString) * 8;
    *ppc_StringUnpacked = (char*)malloc (U32_Length_UnpackedString);

    UINT32_TANALYZE U32_Loop;
    for (U32_Loop = 0; U32_Loop < *pU32_LengthOfString; U32_Loop++)
    {
        UINT32_TANALYZE U32_Temp = U32_Loop * 8;
        if ((pc_StringToUnpack[U32_Loop] & 128) == 128)
            (*ppc_StringUnpacked)[U32_Temp] = '1';
	    else
            (*ppc_StringUnpacked)[U32_Temp] = '0';

	    if ((pc_StringToUnpack[U32_Loop] & 64) == 64)
            (*ppc_StringUnpacked)[U32_Temp + 1] = '1';
	    else
            (*ppc_StringUnpacked)[U32_Temp + 1] = '0';

	    if ((pc_StringToUnpack[U32_Loop] & 32) == 32)
            (*ppc_StringUnpacked)[U32_Temp + 2] = '1';
	    else
            (*ppc_StringUnpacked)[U32_Temp + 2] = '0';

	    if ((pc_StringToUnpack[U32_Loop] & 16) == 16)
            (*ppc_StringUnpacked)[U32_Temp + 3] = '1';
	    else
            (*ppc_StringUnpacked)[U32_Temp + 3] = '0';

	    if ((pc_StringToUnpack[U32_Loop] & 8) == 8)
            (*ppc_StringUnpacked)[U32_Temp + 4] = '1';
	    else
            (*ppc_StringUnpacked)[U32_Temp + 4] = '0';

	    if ((pc_StringToUnpack[U32_Loop] & 4) == 4)
            (*ppc_StringUnpacked)[U32_Temp + 5] = '1';
	    else
            (*ppc_StringUnpacked)[U32_Temp + 5] = '0';

	    if ((pc_StringToUnpack[U32_Loop] & 2) == 2)
            (*ppc_StringUnpacked)[U32_Temp + 6] = '1';
	    else
            (*ppc_StringUnpacked)[U32_Temp + 6] = '0';

	    if ((pc_StringToUnpack[U32_Loop] & 1) == 1)
            (*ppc_StringUnpacked)[U32_Temp + 7] = '1';
	    else
            (*ppc_StringUnpacked)[U32_Temp + 7] = '0';
    }
    *pU32_LengthOfString = U32_Length_UnpackedString;
    return OK_TANALYZE;
}

void func_PrintResult (const char * pc_DatatoPrint, UINT32_TANALYZE u32_Length, UINT32_TANALYZE U32_TexpansionParameter)
{   /*Print out the T-prefix and T-augmentation.*/
    printf ("%lu\t", U32_TexpansionParameter);
    UINT32_TANALYZE U32_Loop;
    for (U32_Loop = 0; U32_Loop < u32_Length; U32_Loop++)
    {
        printf ("%c", pc_DatatoPrint[U32_Loop]);
    }
    printf ("\n");
}

double ei(double x)  /*This function is to convert T-complexity to T-information. The code of this function is from Mark Titchener's tcalc. tcalc is Mark's*/
                                         /*implementation of T-decomposition. This function is to be rewritten at some stage.*/
{
    void nrerror(char error_text[]);
    int k;
    double fact,prev,sum,term;
                
    if (x <= 0.0) 
        printf ("Bad argument in ei\n");
    if (x < FPMIN) return log(x)+EULER;
    if (x <= -log(EPS)) 
    {
        sum=0.0;
        fact=1.0;
        for (k=1;k<=MAXIT;k++) 
        {
            fact *= x/k;
            term=fact/k;
            sum += term;
            if (term < EPS*sum) break;
        }
        if (k > MAXIT)
            printf ("series failed in ei/n");
        return sum+log(x)+EULER;
    } 
    else 
    {
        sum=0.0;
        term=1.0;
        for (k=1;k<=MAXIT;k++) 
        {
            prev=term;
            term *= k/x;
            if (term < EPS) break;
            if (term < prev) sum += term;
            else 
            {
                sum -= prev;
                break;
            }
        }
            return exp(x)*(1.0+sum)/x;
    }
}


double func_Tinformation (double d_Tcomplexity, double d_Offset)/*This function is to convert T-complexity to T-information. The code of this function is from Mark Titchener's tcalc. tcalc is Mark's*/
                                                                                                       /*implementation of T-decomposition. This function is to be rewritten at some stage.*/
{
    double lb, ub, tmp1, tmp2, g1;
    lb = 1.0+EPS;   
    if (d_Tcomplexity < ei(log(lb))) 
    {   
        printf ("The argument is too small!\n");
        return 0;
    }
    ub = 2.0;
    while (ei(log(ub)) < d_Tcomplexity) 
    {
        lb = ub;
        ub *= 2;
    }
    tmp1 = ei(log(lb));
    tmp2 = ei(log(ub));
    g1 = 1/log(lb);
    /* x is now between logint(lb) and logint(ub) */
    /* printf("lb:%g ub:%g tmp1:%g tmp2:%g g1:%g\n",lb,ub,tmp1,tmp2,g1); */
    while (tmp2-tmp1 > EPS) 
    {       
        /* printf("lb:%g ub:%g tmp1:%g tmp2:%g g1:%g\n",lb,ub,tmp1,tmp2,g1);
        printf("Iteration\n"); */
        ub = (d_Tcomplexity - tmp1) * (ub - lb)/(tmp2 - tmp1) + lb;
        tmp2 = ei(log(ub));
        lb += (d_Tcomplexity - tmp1)/g1;
        tmp1 = ei(log(lb));
        g1 = 1/log(lb);
    }
    return (ub + d_Offset);
}

INT32_TANALYZE func_Calculate (const char *pc_String, UINT32_TANALYZE U32_LengthOfString, double *pd_Tcomplexity, double *pd_Tinformation, 
        double *pd_Tentropy, INT32_TANALYZE I32_Opt)
{  /*This is the main function to calculate the T-complexity, T-information and T-entropy.*/
    if (pc_String == NULL)
    {
        printf ("ERROR: The first parameter of func_Calculate can not be NULL!\n");
        return (ERROR_TANALYZE);
    }

    INT32_TANALYZE I32_OptPrintOut = I32_Opt & 0xf3;     /*Retrieve the lower 3 bits, the value of which is used to determine what information to print out.*/
    INT32_TANALYZE I32_OptLog2Based= I32_Opt & OPT_LOG2BASED;

    UINT32_TANALYZE U32_StepInfoDisplayInterval =  I32_Opt >> 16;
    if (U32_StepInfoDisplayInterval == 0)
        U32_StepInfoDisplayInterval = 1;

    if (U32_StepInfoDisplayInterval > MAX_STEPSAMPLE_INTERVAL)
    {
        printf ("ERROR! The maximal sample interval is: %d\n", MAX_STEPSAMPLE_INTERVAL);
        return ERROR_TANALYZE;
    }

    double d_OffsetTinfo = 0;
    
    if ((I32_Opt & OPT_OFFSET_TINFO) == OPT_OFFSET_TINFO)
    {
        d_OffsetTinfo = OFFSET_TINFO;
    }


    *pd_Tcomplexity = 0;

    if (U32_LengthOfString == 0)    /*To deal with a zero-length string.*/
    {
        *pd_Tinformation = func_Tinformation (*pd_Tcomplexity, d_OffsetTinfo);

        if (I32_OptLog2Based == OPT_LOG2BASED)   /*If use log2 for the T-information.*/
            *pd_Tinformation = *pd_Tinformation / log(2.0);	

        *pd_Tentropy = (*pd_Tinformation);  /*The length is 1, as there is only one character in the string.*/
        if (I32_OptPrintOut == OPT_STEPINFO_PRINTOUT)
        {
            double d_Tentropy_Rate = 0;
            printf ("%-15s%-15.2f%-15.2f%-15.5f%-15.5f\n", "1", *pd_Tcomplexity, *pd_Tinformation, *pd_Tentropy, d_Tentropy_Rate);
        }
    return OK_TANALYZE;
    }
    
	double d_TinfoLastparsing;    /*To record the T-information of the last parsing. This helps to compute the entropy rate.*/
    
	if (I32_OptPrintOut == OPT_STEPINFO_PRINTOUT) 
    {
        *pd_Tinformation = func_Tinformation (*pd_Tcomplexity, d_OffsetTinfo);

        if (I32_OptLog2Based == OPT_LOG2BASED)   /*If use log2 for the T-information.*/
            *pd_Tinformation = *pd_Tinformation / log(2.0);	

        *pd_Tentropy = *pd_Tinformation;  /*The length is 1, as there is only one character in the string.*/
        double d_Tentropy_Rate = 0;
        d_TinfoLastparsing = *pd_Tinformation;
		printf ("%-15s%-15.2f%-15.2f%-15.5f%-15.5f\n", "1", *pd_Tcomplexity, *pd_Tinformation, *pd_Tentropy, d_Tentropy_Rate);

    }
    
    UINT32_TANALYZE U32_HashTableSize = U32_LengthOfString + 256;  /*Approximate the maximun number of different codewords that might occur during the whole process.*/

    STRU_CODEWORD *p_CODEWORD_PrimeListEnd = NULL;    /*Pointer to the last node in the string list (which is a dummy node).*/ 
     ///////////////////////////////////////////////
     //Initialize the head and end node of the entry list.
     //////////////////////////////////////////////
    STRU_MATCHLISTENTRY *p_buff_MATCHLISTENTRY_EntryList = (STRU_MATCHLISTENTRY*)malloc(sizeof (STRU_MATCHLISTENTRY) * U32_HashTableSize);
    if (p_buff_MATCHLISTENTRY_EntryList == NULL)
    {
        printf ("Memory allocate failed (malloc)!\n");
        return ERROR_TANALYZE;
    }

    const UINT32_TANALYZE U32_Tprefix_N_Indicate = 256;  /*It is the entry reserved for p^k_n.*/
    p_buff_MATCHLISTENTRY_EntryList[U32_Tprefix_N_Indicate].U32_CodeWordID = 0;
    UINT32_TANALYZE U32_NextAvailableEntry = 257; /*Point to the next available entry.*/
    UINT32_TANALYZE U32_FirstNewEntry_PerPass = U32_NextAvailableEntry;   /*The entry for the first new codeword during each pass.*/

    STRU_CODEWORD * p_buff_CODEWORD_PrimeList = (STRU_CODEWORD *)malloc ((U32_LengthOfString + 2) * sizeof (STRU_CODEWORD)); /*There are too additional nodes, head and end nodes in the string list.*/
    if (p_buff_CODEWORD_PrimeList == NULL)
    {
        printf ("Memory allocate failed (malloc)!\n");
        return ERROR_TANALYZE;
    }

/*Initialize the head node.*/
    p_buff_CODEWORD_PrimeList[0].p_CODEWORD_NextCodeWordInStringList = p_buff_CODEWORD_PrimeList + 1;   /*The heand node.*/
    p_buff_CODEWORD_PrimeList[0].p_CODEWORD_PreviousCodeWordInStringList = NULL;
/*Initialize the end node.*/    
    p_buff_CODEWORD_PrimeList[U32_LengthOfString + 1].p_CODEWORD_NextCodeWordInStringList = NULL;
    p_buff_CODEWORD_PrimeList[U32_LengthOfString + 1].p_CODEWORD_PreviousCodeWordInStringList = p_buff_CODEWORD_PrimeList + U32_LengthOfString; /*The end node.*/
    
    UINT32_TANALYZE U32_Loop;
    for (U32_Loop = 0; U32_Loop < 256; U32_Loop++)  /*Initialize the first 256 entries (0--255).*/
    {
        p_buff_MATCHLISTENTRY_EntryList[U32_Loop].p_CODEWORD_PreviousCodeWordInMatchList = (STRU_CODEWORD*)(p_buff_MATCHLISTENTRY_EntryList + U32_Loop);  /*Note that in the heads of the hash lists, this is used to indicate the lattest inserted node.*/
        p_buff_MATCHLISTENTRY_EntryList[U32_Loop].U32_CodeWordID = 0; /*In the head nodes, it is to store the new allocated index for a new codeword.*/
    }
    
    for (U32_Loop= 1; U32_Loop < U32_LengthOfString + 1; U32_Loop++)   /*Create the lists. The pointers p_CODEWORD_NextCodeWordInMatchList and*/
                                                                                        /*p_CODEWORD_NextCodeWordInStringList should have the same value.*/
    {
        p_buff_CODEWORD_PrimeList[U32_Loop].p_CODEWORD_NextCodeWordInStringList = p_buff_CODEWORD_PrimeList + U32_Loop + 1;
        p_buff_CODEWORD_PrimeList[U32_Loop].p_CODEWORD_PreviousCodeWordInStringList = p_buff_CODEWORD_PrimeList + U32_Loop - 1;
    }
    p_CODEWORD_PrimeListEnd = p_buff_CODEWORD_PrimeList + U32_LengthOfString + 1;

    UINT32_TANALYZE U32_StepCount = 1;   /*It includes the litera character (the rightmost character).*/

    STRU_CODEWORD *p_CODEWORD_PrimeListTemp = p_buff_CODEWORD_PrimeList;
    for (U32_Loop= 0; U32_Loop < U32_LengthOfString; U32_Loop++)   /*Create the lists. The pointers p_CODEWORD_NextCodeWordInMatchList and*/
    {
        UINT32_TANALYZE U32_HashCodeTemp = (unsigned char)(pc_String[U32_Loop]);  
        p_CODEWORD_PrimeListTemp->p_CODEWORD_NextCodeWordInStringList->U32_CodeWordID = U32_HashCodeTemp;
/*///////////////Add to the list///////////////////////*/
        p_CODEWORD_PrimeListTemp->p_CODEWORD_NextCodeWordInStringList->p_CODEWORD_PreviousCodeWordInMatchList =p_buff_MATCHLISTENTRY_EntryList[U32_HashCodeTemp].p_CODEWORD_PreviousCodeWordInMatchList;
        p_CODEWORD_PrimeListTemp->p_CODEWORD_NextCodeWordInStringList->p_CODEWORD_NextCodeWordInMatchList = (STRU_CODEWORD*)&(p_buff_MATCHLISTENTRY_EntryList[U32_HashCodeTemp]);
        p_buff_MATCHLISTENTRY_EntryList[U32_HashCodeTemp].p_CODEWORD_PreviousCodeWordInMatchList->p_CODEWORD_NextCodeWordInMatchList = p_CODEWORD_PrimeListTemp->p_CODEWORD_NextCodeWordInStringList;
        p_buff_MATCHLISTENTRY_EntryList[U32_HashCodeTemp].p_CODEWORD_PreviousCodeWordInMatchList = p_CODEWORD_PrimeListTemp->p_CODEWORD_NextCodeWordInStringList;
/*///////////////////////////////////////////////////*/

        p_CODEWORD_PrimeListTemp++;
    }
    p_CODEWORD_PrimeListTemp = p_buff_CODEWORD_PrimeList;

    UINT32_TANALYZE U32_Length_SuffixString_ParsedIntoOneCodeword = 0;   /*To compute the length of a substring (in fact it is a suffix of the string)that has been parsed into one*/ 
                                                                               /*codeword after each run. Thus we can get step information with the corresponding substring length.*/
    STRU_CODEWORD *p_CODEWORD_RealEndOfPrimeList = p_CODEWORD_PrimeListEnd;

    UINT32_TANALYZE U32_StepInfoPrintCount = 0;   /*To work with U32_StepInfoDisplayInterval*/

    /*////////////////////////////
     /////////////////////////////
     ////Now start T-decomposition!
     ////////////////////////////
     ////////////////////////////*/

    for (;;)  
    {
        if (p_buff_CODEWORD_PrimeList->p_CODEWORD_NextCodeWordInStringList->p_CODEWORD_NextCodeWordInStringList == NULL) /*Check if the process should finished (if these is only one codeword in the string).*/
            break;

        UINT32_TANALYZE U32_TexpansionParameter = 1;   /*Count the number of the adjacent codewords that match the T-prerix.*/
        U32_StepCount++;   /*Step count.*/
         /*//////////////////
        //(1)Get the T-prefix.
        ///////////////////*/
        STRU_CODEWORD *p_CODEWORD_Node_Tprefix = p_CODEWORD_PrimeListEnd->p_CODEWORD_PreviousCodeWordInStringList;
        const char *pc_TprefixAddress = pc_String + (p_CODEWORD_Node_Tprefix - p_buff_CODEWORD_PrimeList) - 1;  
        UINT32_TANALYZE U32_TprefixLength = p_CODEWORD_RealEndOfPrimeList - p_CODEWORD_Node_Tprefix;
        UINT32_TANALYZE U32_HashCode_Tprefix = (p_CODEWORD_Node_Tprefix->U32_CodeWordID);
        STRU_CODEWORD *p_CODEWORD_HeadOfCurrentMatchList = p_CODEWORD_Node_Tprefix->p_CODEWORD_NextCodeWordInMatchList;  /*Point to the dummy head of the hash list.*/
        /*/////////////////////////////////////////////////////////////////////////////////////////////////////////
        //(2)Find how many adjacent copies preceding the T-prefix at the end of the string. So we can got the T-expansion parameter.
        ////////////////////////////////////////////////////////////////////////////////////////////////////////*/
        while (p_CODEWORD_Node_Tprefix->p_CODEWORD_PreviousCodeWordInStringList->p_CODEWORD_PreviousCodeWordInStringList != NULL)
        {
            if (p_CODEWORD_Node_Tprefix->p_CODEWORD_PreviousCodeWordInMatchList == p_CODEWORD_Node_Tprefix->p_CODEWORD_PreviousCodeWordInStringList)
            {  
                p_CODEWORD_Node_Tprefix = p_CODEWORD_Node_Tprefix->p_CODEWORD_PreviousCodeWordInStringList;
                U32_TexpansionParameter++;
            }
            else
                break;
        }
        p_CODEWORD_RealEndOfPrimeList = p_CODEWORD_Node_Tprefix; 
  
        p_CODEWORD_Node_Tprefix->p_CODEWORD_PreviousCodeWordInMatchList->p_CODEWORD_NextCodeWordInMatchList = p_CODEWORD_HeadOfCurrentMatchList;
        p_CODEWORD_HeadOfCurrentMatchList->p_CODEWORD_PreviousCodeWordInMatchList = p_CODEWORD_Node_Tprefix->p_CODEWORD_PreviousCodeWordInMatchList;
        p_CODEWORD_Node_Tprefix->p_CODEWORD_PreviousCodeWordInStringList->p_CODEWORD_NextCodeWordInStringList = p_CODEWORD_PrimeListEnd;
        p_CODEWORD_PrimeListEnd->p_CODEWORD_PreviousCodeWordInStringList = p_CODEWORD_Node_Tprefix->p_CODEWORD_PreviousCodeWordInStringList;

        *pd_Tcomplexity = *pd_Tcomplexity + log((double)(U32_TexpansionParameter + 1));  /*Compute the T-complexity.*/
        
		if (I32_OptPrintOut == OPT_TDECOMPOSITION_PRINTOUT)  /*If need to print out the T-prefix and T-expansion parameters.*/
            func_PrintResult (pc_TprefixAddress, U32_TprefixLength, U32_TexpansionParameter); /*Print out T-prefix and T-augmentation parameters.*/
        else if (I32_OptPrintOut == OPT_STEPINFO_PRINTOUT) /*Print out the T-information, T-entropy and T-complexity for each step.*/
        {
            double  d_Tcomplexity_Step = *pd_Tcomplexity / log (2.0);

            *pd_Tinformation = func_Tinformation (d_Tcomplexity_Step, d_OffsetTinfo);
            if (I32_OptLog2Based == OPT_LOG2BASED)   /*Use log2 for the T-information.*/
                *pd_Tinformation = *pd_Tinformation / log(2.0);	
            U32_Length_SuffixString_ParsedIntoOneCodeword = U32_Length_SuffixString_ParsedIntoOneCodeword + U32_TprefixLength * U32_TexpansionParameter;  //Length of substring for each run.
            if ( (U32_StepInfoPrintCount++  % U32_StepInfoDisplayInterval) == 0)
            {
                UINT32_TANALYZE U32_Length_SuffixString_ParsedIncluLastCharacter = U32_Length_SuffixString_ParsedIntoOneCodeword + 1;  /*To include the last character.*/
                *pd_Tentropy = (*pd_Tinformation)/(U32_Length_SuffixString_ParsedIncluLastCharacter);
                /*Now compute the T-entropy rate.*/
            /*    double d_Tentropy_Rate = ((log ((double)(U32_TexpansionParameter + 1)) / log (2.0)) /(U32_TexpansionParameter * U32_TprefixLength)) * log (*pd_Tinformation);
            */
			    double d_Tentropy_Rate = (*pd_Tinformation - d_TinfoLastparsing) / (U32_TprefixLength * U32_TexpansionParameter);
			    d_TinfoLastparsing = *pd_Tinformation;
				printf ("%-15lu%-15.2f%-15.2f%-15.5f%-15.5f\n", U32_Length_SuffixString_ParsedIncluLastCharacter, d_Tcomplexity_Step, *pd_Tinformation, *pd_Tentropy, d_Tentropy_Rate);
            }
        }
        /*///////////////////////////////////////////////////////////////////////////
        //(3)Search from the beginning of the match list to find the codeword that matches the T-prefix.
        ////////////////////////////////////////////////////////////////////////////*/
        STRU_CODEWORD *p_CODEWORD_CodeWordInMatchList = p_CODEWORD_HeadOfCurrentMatchList;  /*The head of the match list.*/

        if (p_CODEWORD_CodeWordInMatchList ->p_CODEWORD_NextCodeWordInMatchList == p_CODEWORD_HeadOfCurrentMatchList)   /*If the list does not exist.*/
          	continue;
        p_CODEWORD_CodeWordInMatchList = p_CODEWORD_CodeWordInMatchList->p_CODEWORD_NextCodeWordInMatchList;
        UINT32_TANALYZE U32_Count_TprefixMatch = 0;  /*The number of the adjacent copies of T-prefix found. It will be set to 0 again*/
                                                                             /*once the new codeword does not mathc the T-prefix.*/
        /*Now the search really begins from the beginnin of the corresponding match list. The match list helps to locate the codeword in the string list.*/
        while (p_CODEWORD_CodeWordInMatchList != p_CODEWORD_HeadOfCurrentMatchList)  
        {
            p_CODEWORD_PrimeListTemp = p_CODEWORD_CodeWordInMatchList;
            U32_Count_TprefixMatch = 1;  /*The number of the adjacent codewords that match the T-prefix.*/
            STRU_CODEWORD *p_CODEWORD_CodeWordBegin = p_CODEWORD_PrimeListTemp; /*The node that pointing to the possible beginning of a new codeword.*/
            p_CODEWORD_PrimeListTemp = p_CODEWORD_PrimeListTemp->p_CODEWORD_NextCodeWordInStringList;

            for (;;)  /*We have found the matched codeword. Here we need remove some codewords from the match list and string list.*/
                        /*And the new merged codeword will be added to the corresponding match list.Check in the string list.*/
            {    
                if (U32_HashCode_Tprefix == p_CODEWORD_PrimeListTemp->U32_CodeWordID)
                { /*The current codeword DOES match the T-prefix.*/
                    U32_Count_TprefixMatch++;  
                    if (U32_Count_TprefixMatch <= U32_TexpansionParameter)
                    {
                        p_CODEWORD_PrimeListTemp = p_CODEWORD_PrimeListTemp->p_CODEWORD_NextCodeWordInStringList;
                    }
                    else  /*If the number of the adjacent matching codewords exceeds the T-expansion parameter.*/
                    {
                        /*To move the pointer to the next code in the match list.*/
                        p_CODEWORD_CodeWordInMatchList = p_CODEWORD_PrimeListTemp->p_CODEWORD_NextCodeWordInMatchList;
                        /*To delete the node in the string list.*/
                        p_CODEWORD_CodeWordBegin->p_CODEWORD_NextCodeWordInStringList = p_CODEWORD_PrimeListTemp->p_CODEWORD_NextCodeWordInStringList;
                        p_CODEWORD_PrimeListTemp->p_CODEWORD_NextCodeWordInStringList->p_CODEWORD_PreviousCodeWordInStringList = p_CODEWORD_CodeWordBegin;
                        UINT32_TANALYZE U32_TempID;
                        if ( p_buff_MATCHLISTENTRY_EntryList[U32_Tprefix_N_Indicate].U32_CodeWordID < U32_FirstNewEntry_PerPass) /*There is no entry for this new codeword.*/
                        {
                            p_buff_MATCHLISTENTRY_EntryList[U32_Tprefix_N_Indicate].U32_CodeWordID = U32_NextAvailableEntry;
                            U32_TempID = U32_NextAvailableEntry;
                            p_buff_MATCHLISTENTRY_EntryList[U32_NextAvailableEntry].p_CODEWORD_PreviousCodeWordInMatchList = (STRU_CODEWORD*)(p_buff_MATCHLISTENTRY_EntryList + U32_NextAvailableEntry);
                            p_buff_MATCHLISTENTRY_EntryList[U32_NextAvailableEntry].U32_CodeWordID= 0;
                            U32_NextAvailableEntry++;
                        }
                        else
                        {
                            U32_TempID = p_buff_MATCHLISTENTRY_EntryList[U32_Tprefix_N_Indicate].U32_CodeWordID;
                        }
                        p_CODEWORD_CodeWordBegin->U32_CodeWordID = U32_TempID;

/*/////////////////////////Add to the lists///////////////////////*/
                        p_CODEWORD_CodeWordBegin->p_CODEWORD_PreviousCodeWordInMatchList =p_buff_MATCHLISTENTRY_EntryList[U32_TempID].p_CODEWORD_PreviousCodeWordInMatchList;
                        p_CODEWORD_CodeWordBegin->p_CODEWORD_NextCodeWordInMatchList = (STRU_CODEWORD*)(&(p_buff_MATCHLISTENTRY_EntryList[U32_TempID]));
                        p_buff_MATCHLISTENTRY_EntryList[U32_TempID].p_CODEWORD_PreviousCodeWordInMatchList->p_CODEWORD_NextCodeWordInMatchList = p_CODEWORD_CodeWordBegin;
                        p_buff_MATCHLISTENTRY_EntryList[U32_TempID].p_CODEWORD_PreviousCodeWordInMatchList = p_CODEWORD_CodeWordBegin;

                        break;
                    }
                }
                else   /*The current codeword does not match the T-prefix.*/
                {
                    UINT32_TANALYZE U32_TempEntry = p_CODEWORD_PrimeListTemp->U32_CodeWordID;
                    p_CODEWORD_CodeWordInMatchList = p_CODEWORD_PrimeListTemp->p_CODEWORD_PreviousCodeWordInStringList->p_CODEWORD_NextCodeWordInMatchList;
                    UINT32_TANALYZE U32_Loop;
                    for (U32_Loop = 0; U32_Loop < U32_Count_TprefixMatch; U32_Loop++)  /*Remove these codewords from the string list. Notice that the first matched codeword should remain.*/
                    {
                        if (p_buff_MATCHLISTENTRY_EntryList[U32_TempEntry].U32_CodeWordID < U32_FirstNewEntry_PerPass) /*There has been an entry for the new codeword.*/
                        {
                            p_buff_MATCHLISTENTRY_EntryList[U32_TempEntry].U32_CodeWordID = U32_NextAvailableEntry;
                            U32_TempEntry = U32_NextAvailableEntry;
                            p_buff_MATCHLISTENTRY_EntryList[U32_TempEntry].p_CODEWORD_PreviousCodeWordInMatchList = (STRU_CODEWORD*)(p_buff_MATCHLISTENTRY_EntryList + U32_TempEntry);
                            p_buff_MATCHLISTENTRY_EntryList[U32_TempEntry].U32_CodeWordID= 0;
                                
                            U32_NextAvailableEntry++;
                        }
                        else
                        {
                            U32_TempEntry = p_buff_MATCHLISTENTRY_EntryList[U32_TempEntry].U32_CodeWordID;
                        }
                    }
                    p_CODEWORD_CodeWordBegin->U32_CodeWordID = U32_TempEntry;  /*New UID.*/
                    { /*If this is not the last node in the match list.*/
                        p_CODEWORD_PrimeListTemp->p_CODEWORD_PreviousCodeWordInMatchList->p_CODEWORD_NextCodeWordInMatchList = p_CODEWORD_PrimeListTemp->p_CODEWORD_NextCodeWordInMatchList; 
                        p_CODEWORD_PrimeListTemp->p_CODEWORD_NextCodeWordInMatchList->p_CODEWORD_PreviousCodeWordInMatchList = p_CODEWORD_PrimeListTemp->p_CODEWORD_PreviousCodeWordInMatchList;
                    }
                    
/*//////////////////////////Add to the lists/////////////////////*/
                    p_CODEWORD_CodeWordBegin->p_CODEWORD_PreviousCodeWordInMatchList =p_buff_MATCHLISTENTRY_EntryList[U32_TempEntry].p_CODEWORD_PreviousCodeWordInMatchList;
                    p_CODEWORD_CodeWordBegin->p_CODEWORD_NextCodeWordInMatchList = (STRU_CODEWORD*)(&(p_buff_MATCHLISTENTRY_EntryList[U32_TempEntry]));
                    p_buff_MATCHLISTENTRY_EntryList[U32_TempEntry].p_CODEWORD_PreviousCodeWordInMatchList->p_CODEWORD_NextCodeWordInMatchList = p_CODEWORD_CodeWordBegin;
                    p_buff_MATCHLISTENTRY_EntryList[U32_TempEntry].p_CODEWORD_PreviousCodeWordInMatchList = p_CODEWORD_CodeWordBegin;
/*////////////////////////////////////////////////////////////*/
                    p_CODEWORD_CodeWordBegin->p_CODEWORD_NextCodeWordInStringList = p_CODEWORD_PrimeListTemp->p_CODEWORD_NextCodeWordInStringList;
                    p_CODEWORD_PrimeListTemp->p_CODEWORD_NextCodeWordInStringList->p_CODEWORD_PreviousCodeWordInStringList = p_CODEWORD_CodeWordBegin;
                
                    break;
                }
            }/*end of for (;;)*/
        }
        U32_FirstNewEntry_PerPass = U32_NextAvailableEntry;
    }
    /*/////////////////////////////////////////////////////////////////////////////
    ///Near the end of the process. We can now get T-complexity, T-information and T-entropy.
    /////////////////////////////////////////////////////////////////////////////*/
     free (p_buff_MATCHLISTENTRY_EntryList);
     free (p_buff_CODEWORD_PrimeList);

    *pd_Tcomplexity = *pd_Tcomplexity/log(2.0);
    *pd_Tinformation = func_Tinformation (*pd_Tcomplexity, d_OffsetTinfo);
     if (I32_OptLog2Based == OPT_LOG2BASED)   /*If use log2 for the T-information.*/
        *pd_Tinformation = *pd_Tinformation / log(2.0);	

    *pd_Tentropy = (*pd_Tinformation)/(U32_LengthOfString + 1);  /*To take into account the last character, which has been deliberately ignored in the main() program.*/
    return OK_TANALYZE;
}



