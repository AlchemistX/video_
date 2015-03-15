# mv-hevc
```
ISSUE - 1

Project Member Reported by hick4321, Jan 16, 2011
JCTVC의 메일링리스트에 HM 1.0 Release 뉴스 참조.
작업 결과물의 base code로 HM 1.0을 사용하기로 결정함에 따라, HM 1.0을 기존 코드에 덮어 쓴다.


Jan 16, 2011 Delete comment Project Member #1 hick4321
This issue was closed by revision r6.

ISSUE - 2

Project Member Reported by hick4321, Jan 16, 2011
새로운 mv-hevc branch 생성.
기존에 /branch/mv-hevc 라고 branch를 생성했지만, 이름을 바꿔야 함.
/branch/mv-hevc_vXX 라고 할 예정.


Jan 16, 2011 Delete comment Project Member #1 hick4321
This issue was closed by revision r8.

ISSUE - 3

Project Member Reported by hick4321, Jan 16, 2011
JMVC이 사용하는 설정 항목을 Review 해 보면 다음과 같다.


# JMVM Configuration File in MVC mode

#====================== GENERAL ================================================
InputFile  .\ballroom 
OutputFile .\qp32\output
ReconFile  .\qp32\recon
SourceWidth             640        # input  frame width
SourceHeight            480        # input  frame height
FrameRate               25.0       # frame rate [Hz]
FramesToBeEncoded       250        # number of frames

#====================== CODING =================================================
SymbolMode              1          # 0=CAVLC, 1=CABAC
FRExt                   1          # 8x8 transform (0:off, 1:on)
BasisQP                 32         # Quantization parameters

#====================== STRUCTURE ==============================================
GOPSize                 12	   # GOP Size (at maximum frame rate) 
IntraPeriod             12	   # Anchor Period
NumberReferenceFrames   2          # Number of reference pictures
InterPredPicsFirst      1          # 1 Inter Pics; 0 Inter-view
DeltaLayer0Quant        0          # differential QP for layer 0
DeltaLayer1Quant        3          # differential QP for layer 1
DeltaLayer2Quant        4          # differential QP for layer 2
DeltaLayer3Quant        5          # differential QP for layer 3
DeltaLayer4Quant        6          # differential QP for layer 4
DeltaLayer5Quant        7          # differential QP for layer 5

#============================== MOTION SEARCH ==================================
SearchMode              4          # Search mode (0:BlockSearch, 4:FastSearch)
SearchFuncFullPel       3          # Search function full pel
                                   #   (0:SAD, 1:SSE, 2:HADAMARD, 3:SAD-YUV) 
SearchFuncSubPel        2          # Search function sub pel
                                   #   (0:SAD, 1:SSE, 2:HADAMARD) 
SearchRange             96         # Search range (Full Pel) 
BiPredIter              4          # Max iterations for bi-pred search
IterSearchRange         8          # Search range for iterations (0: normal)

#============================== LOOP FILTER ====================================
LoopFilterDisable       0          # Loop filter idc (0: on, 1: off, 2:
                                   #   on except for slice boundaries)
LoopFilterAlphaC0Offset 0          # AlphaOffset(-6..+6): valid range
LoopFilterBetaOffset    0          # BetaOffset (-6..+6): valid range

#============================== WEIGHTED PREDICTION ============================
WeightedPrediction      0          # Weighting IP Slice (0:disable, 1:enable)
WeightedBiprediction    0          # Weighting B  Slice (0:disable, 1:explicit,
                                                         2:implicit)

#=================== PARALLEL DECODING INFORMATION SEI Message ==================
PDISEIMessage           0          # PDI SEI message enable (0: disable, 1:enable)
PDIInitialDelayAnc      2          # PDI initial delay for anchor pictures
PDIInitialDelayNonAnc   2          # PDI initial delay for non-anchor pictures

#========================= sEQUENCE PARAMETER SET ==========================
NumViewsMinusOne	7          # (Number of view to be coded minus 1)
ViewOrder               0-2-1-4-3-6-5-7   # (Order in which view_ids are coded)

View_ID		        0          # (view_id of a view 0 - 1024)                       
Fwd_NumAnchorRefs	0          # (number of list_0 references for anchor) 
Bwd_NumAnchorRefs	0          # (number of list 1 references for anchor)
Fwd_NumNonAnchorRefs    0          # (number of list 1 references for non-anchor)
Bwd_NumNonAnchorRefs    0          # (number of list 1 references for non-anchor)

View_ID                  1                                                    
Fwd_NumAnchorRefs	 1
Bwd_NumAnchorRefs	 1
Fwd_NumNonAnchorRefs     1
Bwd_NumNonAnchorRefs     1
Fwd_AnchorRefs	     	 0 0
Bwd_AnchorRefs	         0 2
Fwd_NonAnchorRefs	 0 0
Bwd_NonAnchorRefs	 0 2

View_ID                  2          
Fwd_NumAnchorRefs	 1
Bwd_NumAnchorRefs	 0
Fwd_NumNonAnchorRefs     0
Bwd_NumNonAnchorRefs     0
Fwd_AnchorRefs	         0 0

View_ID                  3                          
Fwd_NumAnchorRefs	 1
Bwd_NumAnchorRefs	 1
Fwd_NumNonAnchorRefs     1
Bwd_NumNonAnchorRefs     1
Fwd_AnchorRefs	         0 2
Bwd_AnchorRefs	         0 4
Fwd_NonAnchorRefs	 0 2
Bwd_NonAnchorRefs	 0 4

View_ID                 4                         
Fwd_NumAnchorRefs	1
Bwd_NumAnchorRefs	0
Fwd_NumNonAnchorRefs    0
Bwd_NumNonAnchorRefs    0
Fwd_AnchorRefs	        0 2

View_ID                 5                          
Fwd_NumAnchorRefs	1
Bwd_NumAnchorRefs	1
Fwd_NumNonAnchorRefs    1
Bwd_NumNonAnchorRefs    1
Fwd_AnchorRefs	        0 4
Bwd_AnchorRefs	        0 6
Fwd_NonAnchorRefs	0 4
Bwd_NonAnchorRefs	0 6

View_ID                 6                          
Fwd_NumAnchorRefs       1
Bwd_NumAnchorRefs	0
Fwd_NumNonAnchorRefs    0
Bwd_NumNonAnchorRefs    0
Fwd_AnchorRefs	        0 4

View_ID                 7                       
Fwd_NumAnchorRefs       1
Bwd_NumAnchorRefs       0
Fwd_NumNonAnchorRefs    1
Bwd_NumNonAnchorRefs    0
Fwd_AnchorRefs	        0 6
Fwd_NonAnchorRefs       0 6

이 중 HMVC가 지원하지 않는 것이 있고, 지원하지 않는 것 중 Multiview와 관계 된 설정 항목들을 추가 하고 절절한 의미로 반영한다.
Jan 30, 2011 Delete comment Project Member #1 hick4321
추가 고려 사항.
만약 MVC 모드로 동작하는 것이면, InputFile, OutputFile, ReconFile의 이름을 prefix로 인식하여 prefix_[ViewID].yuv, prefix_[Vie-wID].bin, prefix_[ViewID].yuv 라고 내부적으로 처리 한다.

이 역시 JMVC와 동일한 처리 방식이다.
Jan 30, 2011 Delete comment Project Member #2 hick4321
(No comment was entered for this change.)
Status: Started 
Mar 9, 2011 Delete comment Project Member #3 hick4321
구현 완료 함.
Status: Done 

ISSUE - 4

Project Member Reported by hick4321, Jan 17, 2011
NAL Header, Sequence Parameter Set MVC Extension, Slice Header에 추가된 syntax element 추가.

Encoding/Decoding Process보다 Structure를 맞추는데 집중.



Jan 30, 2011 Delete comment Project Member #1 hick4321
NalUnitType 중 14,15,20,21 추가 해야 함.
14 : CODED_SLICE_PREFIX
15 : SUBSET_SPS
20 : CODED_SLICE_SCALABLE
21 : CODED_SLICE_IDR_SCALABLE

Jan 30, 2011 Delete comment Project Member #2 hick4321
(No comment was entered for this change.)
Status: Started 
Mar 9, 2011 Delete comment Project Member #3 hick4321
구현 완료 함.
Status: Done 


ISSUE - 5

Project Member Reported by hick4321, Jan 30, 2011
요구사항.
1. TEncCfg, TAppEncCfg를 통해 MVC 설정 접근.
2. 현재 VIEW ID의 설정에 따라 참조 VIEW의 RECON FILE을 열고 현재 Frame Number와 같은 Frame Pickup.
4. Slice Encoder에서 Reference Picture List를 구성할 때 Inter View Picture들을 보관하는 Pointer를 MVC 설정에 따라 지정한다.


Jan 30, 2011 Delete comment Project Member #1 hick4321
(No comment was entered for this change.)
Labels: -Type-Defect -Priority-Medium Type-Enhancement Priority-High 
Jan 30, 2011 Delete comment Project Member #2 hick4321
(No comment was entered for this change.)
Status: Started 
Mar 9, 2011 Delete comment Project Member #3 hick4321
구현 완료 함.
Status: Done 

ISSUE - 6

Project Member Reported by hick4321, Feb 21, 2011
Multiview Video Coding에 정의된 syntax에 따라 출력된 각 view component들을 보과하고 있는 파일들을 이용하여 하나의 Multiview stream을 만들어내는 Assembler가 필요하다.

JMVC의 내용을 참조하여 작업하면 된다.

출력물 포맷은 다음과 같다.

[SPS#1][SPS#2][PPS#1][PPS#2][Prefix][BaseView][View#3][View#2][Prefix][BaseView].....


Feb 22, 2011 Delete comment Project Member #1 hick4321
(No comment was entered for this change.)
Status: Started 
Mar 9, 2011 Delete comment Project Member #2 hick4321
구현 완료 함.
Status: Done 


ISSUE - 7

Project Member Reported by hick4321, Feb 22, 2011
Multiview Video Coding을 위해 추가한 syntax element의 올바른 parsing.
SPS, PPS, Prefix, Layer extension NAL 등이 있다.


Feb 22, 2011 Delete comment Project Member #1 hick4321
(No comment was entered for this change.)
Status: Started 
Mar 9, 2011 Delete comment Project Member #2 hick4321
구현 완료 함.
Mar 9, 2011 Delete comment Project Member #3 hick4321
구현 완료 함.
Status: Done 


ISSUE - 8

Project Member Reported by hick4321, Feb 22, 2011
Inter view prediction 및 view id관련 정보를 보관하는 자료구조 추가.
Feb 22, 2011 Delete comment Project Member #1 hick4321
(No comment was entered for this change.)
Status: Started 
Mar 9, 2011 Delete comment Project Member #2 hick4321
구현 완료 함.
Status: Done 

ISSUE - 9

Project Member Reported by hick4321, Feb 22, 2011
Inter-view prediction에 사용 할 Multiview Decoded Picture Buffer를 구성한다.


Mar 9, 2011 Delete comment Project Member #1 hick4321
구현 완료 함.
Status: Done 


ISSUE - 10

Project Member Reported by hick4321, Feb 22, 2011
syntax element의 정보를 바탕으로 multiview decoded picture buffer에서 선택한 picture를 이용한 inter view reference picture list구성 방법을 구현한다.


Mar 9, 2011 Delete comment Project Member #1 hick4321
구현 완료 함.
Status: Done 

ISSUE - 11

Project Member Reported by hick4321, Feb 22, 2011
decoding 결과물인 Multiview decoded picture buffer의 내용을 사용자가 지정한 파일에 dump할 방법을 구현한다.
Mar 9, 2011 Delete comment Project Member #1 hick4321
구현 완료 함
Status: Done 


ISSUE - 12

Project Member Reported by hick4321, Feb 22, 2011
reference list를 생성하기 위해 decoded picture list를 검색하는 함수에 버그가 있는 것으로 보임.
Encoder에서 사용한 reference picture의 POC와 Decoder가 사용한 reference picture의 POC가 다른 경우를 보임. 특이점으로는 B-Picture일 때 LO/L1의 POC가 같음.


Mar 9, 2011 Delete comment Project Member #1 hick4321
GOP 주기를 정상적으로 인식하도록 코드를 수정하여 해결 함.
Status: Fixed 


ISSUE - 13

Project Member Reported by hick4321, Mar 9, 2011
GOP가 15인 경우에 CODEC이 작동 되지 않음.


Mar 9, 2011 Delete comment Project Member #1 hick4321
HM은 짝수의 GOP만 지원함.
이는, 코딩 구조 설정과 관련된 자료구조를 이용하는 JMVC와 달리 수식에 따라 자동으로 계산된 코딩 구조를 이용하기 때문에 나타나는 현상임.
JMVC를 참조하여 코딩 구조를 표현할 수 있는 자료구조를 추가 해야 함.
Mar 15, 2011 Delete comment Project Member #2 hick4321
완료 함.
Status: Fixed 


ISSUE - 14

Project Member Reported by hick4321, Mar 13, 2011
실행 옵션으로 지정 한 view를 출력 해 주는 extractor 추가 요청.

Mar 13, 2011 Delete comment Project Member #1 hick4321
(No comment was entered for this change.)
Status: Started 
Mar 15, 2011 Delete comment Project Member #2 hick4321
mvc video stream에 포함된 모든 view components를 각각의 파일로 분리 해 주는 extractor로 구현 방향 수정
Mar 15, 2011 Delete comment Project Member #3 hick4321
완료 함.
Status: Done 

ISSUE - 15

Project Member Reported by hick4321, Mar 18, 2011
P-VIEW, B-VIEW의 RECON과 DECODED 영상의 PSNR을 측정한 결과 양쪽이 다른 것으로 나옴.

58 정도의 애매한 PSNR을 보임.

Deblocking, Border extension등을 의심 하는 중.
Mar 18, 2011 Delete comment Project Member #1 hick4321
원인은 bit depth increment으로 밝혀짐.

Encoder는 YUV file로 부터 RECON 영상을 read 하여 bit depth increment 하기 때문에 pixel의 value가 다음과 같게 됨.

RECON PIXEL @ ENCODER ==> 0x1200

Decoder는 Decoding 처리 결과인 RECON 영상을 직접 copy 하여 bit depth increment를 하지 않고  사용하기 때문에 pixel의 value가 다음과 같게 됨.

RECON PIXEL @ DECODER ==> 0x12xx

따라서, ENC/DEC에서 사용하는 reference picture의 하위 8bit에 오차가 발생 함.
Status: Started 
Mar 18, 2011 Delete comment Project Member #2 hick4321
(No comment was entered for this change.)
Status: Fixed 
```
