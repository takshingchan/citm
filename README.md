A Cognitive Information Theory of Music (CITM)
----------------------------------------------

This project contains the code and data for Chan (2008). Portions
of the project are based on Yang and Speidel (2005), Eerola et
al. (2007, 2001), and Cilibrasi et al. (2004); see the `AUTHORS`
file for details.

## Introduction

CITM is a novel information model which quantifies human music
cognition in bits. It models musical complexity, similarity, and
preference using tools from algorithmic information theory,
statistical distances, and complex systems. This project is
organized as follows. The `information`, `similarity`, and
`fitness` directories contain the code and data from Chapters 3,
4, and 5, respectively. The `information` directory consists of
the following:

| Directory    | Description                                |
| ------------ | ------------------------------------------ |
| `chan`       | My proposed and reduced measures           |
| `cilibrasi`  | Baseline measure from Cilibrasi (2004)     |
| `conley`     | Complexity for Conley (1981)               |
| `shmulevich` | Complexity for Shmulevich and Povel (2000) |
| `heyduk`     | Complexity for Heyduk (1975)               |

while the `similarity` directory includes the following:

| File           | Description                               |
| -------------- | ----------------------------------------- |
| `experiment-1` | Similarity for Cambouropoulos (2001)      |
| `experiment-2` | Similarity for Eerola et al. (2007, 2001) |
| `experiment-3` | My similarity experiment                  |

and the `fitness` directory includes the following:

| File           | Description                            |
| -------------- | -------------------------------------- |
| `experiment-1` | Replication of Chan and Wiggins (2005) |
| `experiment-2` | My fitness experiment                  |
| `experiment-3` | Fitness for Jeong et al. (1998)        |
| `experiment-4` | Fitness for Heyduk (1975)              |
| `experiment-5` | Fitness for Vitz (1966)                |

Additional tools are placed under the `utilities` directory:

| File          | Description                                   |
| ------------- | --------------------------------------------- |
| `asymmetry.m` | Calculates departure from symmetry            |
| `esac.y`      | Parses EsAC                                   |
| `mutate.c`    | Mutates OPM files                             |
| `nb2opm.c`    | Converts NB to OPM                            |
| `opm2mid.c`   | Converts OPM to MIDI                          |
| `opmcat.c`    | Concatenates OPM files                        |
| `printcor.m`  | Prints correlation with gMDL+                 |
| `random.c`    | Generates random music (Jeong et al., 1998)   |
| `shares.pl`   | Converts EsAC files into a shell archive      |
| `triangle.m`  | Calculates departure from triangle inequality |
| `trilmat.m`   | Row-major version of squareform('tovector')   |
| `trilvec.m`   | Row-major version of squareform('tomatrix')   |
| `vitz.c`      | Generates tone sequences (Vitz, 1966)         |

The non-M-files are only used if you regenerate the stimuli for
Chapter 5 (see below). The EsAC format is described in Schaffrath
(1997). A note-beat (NB) file consists of note statements of the
form `Note [ontime] [offtime] [pitch]` plus beat statements of
the form `Beat [time] [level]`, as defined by Temperley and
Sleator (1999). An OPM or onset-pitch-metrical level file
consists of the number of notes on the first line, followed by
OPM statements of the form `[time] [pitch] [level]` on subsequent
lines. Symmetricity and triangle inequality violations are
calculated as per Johnson et al. (2002).

### Requirements

In additional to the GNU development environment (bash, g++, gcc,
make, and yacc), we require the following.

- A recent version of MATLAB (or Octave), Perl 5, Ruby 2, and
  mftext from abcmidi.
- To regenerate the stimuli, we need the sources for Melisma and
  Dynamic Creator under the `utilities` directory:

    ```shell
    cd citm/utilities
    curl http://www.link.cs.cmu.edu/melisma/melisma2003.tar.gz | tar zxvf -
    curl http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/DC/dcmt0.1.tgz | tar zxvf -
    cd ../..
    ```

- To replicate the psychological experiments, we need Objective-C
  and Xcode on Mac OS X 10.3 (unsupported).

### Compilation and Execution

Perform the following steps under the `citm` directory.

1. Type `make` to compile the code.
2. Type `make regenerate` if you wish to regenerate the musical
   fitness stimuli using current time as seed (results will 
   differ).
3. Type `make reproduce`, then run `analysis.m` under each of the
   `results` subdirectories (see Appendix for a transcript).
4. The `similarity/Experiment` and `fitness/Experiment`
   directories contain Xcode projects for the validation
   experiments. They could be useful if you wish to extend the
   psychological experiments herein (unsupported).

### Erratum

The baseline results in Chapter 3 are wrong because part of the
workflow was done in text mode. To simulate this error, insert
`exit(0) if n == mn` into `cilibrasi.rb`, right before `na.each`.

Tak-Shing Chan

20 December 2017

### References

Cambouropoulos, E. (2001). Melodic cue abstraction, similarity,
and category formation: A formal model. *Music Perception*,
18(3), 347-370.

Chan, T.-S. T. and Wiggins, G. A. (2005, July). *A computational
memetics approach to music information and aesthetic fitness*.
Paper presented at the IJCAI Workshop on Computational
Creativity.

Chan, T.-S. T. (2008). *A cognitive information theory of music:
A computational memetics approach* (Unpublished doctoral
dissertation). University of London, London, UK.

Cilibrasi, R., Vitanyi, P., & de Wolf, R. (2004). Algorithmic
clustering of music based on string compression. *Computer Music
Journal*, 28(4), 49-67.

Conley, J. K. (1981). Physical correlates of the judged
complexity of music by subjects differing in musical background.
*British Journal of Psychology*, 72, 451-464.

Eerola, T., & Bregman, M. (2007). Melodic and contextual
similarity of folk song phrases. *Musicae Scientiae*, Discussion
Forum 4A, 211-233.

Eerola, T., Jarvinen, T., Louhivuori, J., & Toiviainen, P.
(2001). Statistical features and perceived similarity of folk
melodies. *Music Perception*, 18(3), 275-296.

Heyduk, R. G. (1975). Rated preference for musical compositions
as it relates to complexity and exposure frequency. *Perception
and Psychophysics*, 17(1), 84-91.

Jeong, J., Joung, M. K., & Kim, S. Y. (1998). Quantification of
emotion by nonlinear analysis of the chaotic dynamics of
electroencephalograms during perception of *1/f* music.
*Biological Cybernetics*, 78(3), 217-225.

Johnson, D. S., Gutin, G., McGeoch, L. A., Zhang, W., &
Zverovitch, A. (2002). Experimental analysis of heuristics for
the ATSP. In G. Gutin & A. Punnen (Eds.), *The Traveling Salesman
Problem and Its Variations* (pp. 445-487). Dordrecht: Kluwer
Academic Publishers.

Schaffrath, H. (1997). The Essen Associative Code: A code for
folksong analysis. In E. Selfridge-Field (Ed.), *Beyond MIDI: The
Handbook of Musical Codes* (pp. 343-361). Cambridge, MA: MIT
Press.

Shmulevich, I., & Povel, D.-J. (2000). Measures of temporal
pattern complexity. *Journal of New Music Research*, 29(1),
61-69.

Temperley, D., & Sleator, D. (1999). Modeling meter and harmony:
A preference-rule approach. Computer Music Journal, 23(1), 10-27.

Vitz, P. C. (1966). Affect as a function of stimulus variation.
*Journal of Experimental Psychology*, 71(1), 74-79.

Yang, J., & Speidel, U. (2005, September). *A T-decomposition
algorithm with O(n log n) time and space complexity*. Paper
presented at the International Symposium on Information Theory.
https://doi.org/10.1109/ISIT.2005.1523285

### Appendix. Transcript of Results

A MATLAB diary is appended below (after `make reproduce`):

```
>> addpath /home/takshingchan/citm/utilities
>> % 3.8.1 Experiment 1
>> cd information/shmulevich/results
>> analysis
ncf-ftd         r(33) = 0.44174 (p = 0.0039457), gMDL+ = 0.81111
plain-ftd       r(33) = -0.44841 (p = 0.99655), gMDL+ = 1.2704
cilibrasi       r(33) = 0.10458 (p = 0.27496), gMDL+ = 1.2704
>> % 3.8.2 Experiment 2
>> cd ../../conley/results/1
>> analysis
ncf-ftd
- Graduate  r(14) = 0.41527 (p = 0.054848), gMDL+ = 1.8282
- Sophomore r(14) = 0.66564 (p = 0.0024427), gMDL+ = -0.67028
- Non-major r(14) = 0.59758 (p = 0.0072504), gMDL+ = 0.29844
plain-ftd
- Graduate  r(14) = 0.48901 (p = 0.027287), gMDL+ = 1.3615
- Sophomore r(14) = 0.72824 (p = 0.00068984), gMDL+ = -1.8584
- Non-major r(14) = 0.65668 (p = 0.0028605), gMDL+ = -0.52605
cilibrasi
- Graduate  r(14) = 0.57495 (p = 0.0099071), gMDL+ = 0.56324
- Sophomore r(14) = 0.78453 (p = 0.00016001), gMDL+ = -3.2844
- Non-major r(14) = 0.8041 (p = 8.6895e-05), gMDL+ = -3.8921
>> % 3.8.3 Experiment 3
>> cd ../2
>> analysis
ncf-ftd
- Graduate  r(14) = 0.48571 (p = 0.028238), gMDL+ = 1.3864
- Sophomore r(14) = 0.68993 (p = 0.0015497), gMDL+ = -1.0916
- Non-major r(14) = 0.62716 (p = 0.0046565), gMDL+ = -0.088188
plain-ftd
- Graduate  r(14) = 0.54564 (p = 0.014398), gMDL+ = 0.8701
- Sophomore r(14) = 0.73447 (p = 0.00059722), gMDL+ = -1.997
- Non-major r(14) = 0.66793 (p = 0.0023442), gMDL+ = -0.70808
cilibrasi
- Graduate  r(14) = 0.64777 (p = 0.003331), gMDL+ = -0.38797
- Sophomore r(14) = 0.81385 (p = 6.2481e-05), gMDL+ = -4.2227
- Non-major r(14) = 0.81005 (p = 7.1206e-05), gMDL+ = -4.0915
>> % 3.8.4 Experiment 4
>> cd ../../../heyduk/results
>> analysis
ncf-ftd         r(2) = 0.98768 (p = 0.0061589), gMDL+ = -3.6414
plain-ftd       r(2) = 0.87465 (p = 0.062673), gMDL+ = -0.37071
cilibrasi       r(2) = 0.83806 (p = 0.080972), gMDL+ = -0.058764
>> % 4.4.1 Model Selection with Three Experiments (p. 69)
>> % - Correlation with Deliege's (1996) Experiment
>> cd ../../../similarity/results/cambouropoulos
>> analysis
bach-dist1      r(24) = 0.2987 (p = 0.069134), gMDL+ = 2.491
bach-dist2      r(24) = 0.38291 (p = 0.026757), gMDL+ = 1.9257
bach-dist3      r(24) = 0.42199 (p = 0.015882), gMDL+ = 1.5534
>> % - Correlation with Eerola et al.'s (2001) Experiment
>> % - Correlation with Eerola and Bregman's (2007) Experiment
>> cd ../eerola
>> analysis
eerola01-dist1  r(103) = 0.42047 (p = 3.9895e-06), gMDL+ = -4.0067
eerola01-dist2  r(103) = 0.45405 (p = 5.726e-07), gMDL+ = -5.8189
eerola01-dist3  r(103) = 0.4178 (p = 4.6141e-06), gMDL+ = -3.872
eerola07-dist1  r(188) = 0.51983 (p = 7.6054e-15), gMDL+ = -22.556
eerola07-dist2  r(188) = 0.45283 (p = 2.6947e-11), gMDL+ = -14.611
eerola07-dist3  r(188) = 0.49928 (p = 1.1309e-13), gMDL+ = -19.922
eerola01        asymmetry = 0, triangle = 0.0034313
eerola07        asymmetry = 0, triangle = 0.0035215
eerola01-dist1  asymmetry = 0.0025063, triangle = 0
eerola01-dist2  asymmetry = 0, triangle = 0
eerola01-dist3  asymmetry = 0.0058994, triangle = 0
eerola07-dist1  asymmetry = 0.0061873, triangle = 0
eerola07-dist2  asymmetry = 2.8793e-05, triangle = 0
eerola07-dist3  asymmetry = 0.016385, triangle = 0
>> % 4.4.2 Validation of H1
>> cd ../chan
>> analysis
chopin-dist1    r(76) = 0.61654 (p = 9.2944e-10), gMDL+ = -12.367
chopin-dist1    asymmetry = 0.0015351, triangle = 0
chopin          asymmetry = 0, triangle = 0
chopina         asymmetry = 0.078926, triangle = 0.00018017
>> % 5.3.3 Model Selection with Three Experiments
>> % - Correlation with Vitz's (1966) Experiment
>> cd ../../../fitness/results/vitz
>> analysis
vitz-uid1       r(4) = 0.84667 (p = 0.01673), gMDL+ = -0.72447
vitz-uid2       r(4) = 0.94361 (p = 0.00234), gMDL+ = -2.9889
vitz-uid3       r(4) = 0.86956 (p = 0.012205), gMDL+ = -1.0712
>> % - Correlation with Heyduk's (1975) Experiment
>> cd ../heyduk
>> analysis
heyduk_uid1     r(2) = 0.74572 (p = 0.12714), gMDL+ = 0.42395
heyduk-uid2     r(2) = 0.74938 (p = 0.12531), gMDL+ = 0.41026
heyduk-uid3     r(2) = 0.93187 (p = 0.034063), gMDL+ = -1.1768
>> % - Correlation with Jeong et al.'s (1998) Experiment
>> cd ../jeong/2
>> analysis
jeong-uid1      r(1) = 0.8459 (p = 0.17906), gMDL+ = 0.020653
jeong-uid2      r(1) = 0.99657 (p = 0.026362), gMDL+ = -3.5428
jeong-uid3      r(1) = -0.99235 (p = 0.96061), gMDL+ = -0.058892
>> % 5.3.4 Validation of H2 and H3
>> cd ../../chan
>> analysis
essen-uid1      r(176) = 0.18205 (p = 0.0075047), gMDL+ = 3.0835
essen-uid2      r(176) = 0.66223 (p = 3.9205e-24), gMDL+ = -43.726
essen-uid3      r(176) = 0.66943 (p = 8.5045e-25), gMDL+ = -45.242
```

