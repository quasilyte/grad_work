#include <cstring>
#include <cstdio>
#include <algorithm>
#include "lexer.hpp"
#include "token.hpp"

using namespace std;
using compiler::Lexer;

int main(void) {
  long score = 0;
  
  const char *data = R"==(
+ ++ ( BF ++ - ( ++ - 7 2684 - 11051 8 ( ( + - 3358709 -- + 367 3 ( -- -- -- ( + ( 805884 77 ++ + ( 835280 + ++ 26674 ++ ( ( ) - -- ++ ++ ) ( ( + ) FGGEEeAeG aGBCgefbF ) + - ( ) 768668 ++ ++ ++ -- ( GCbfdGgdG eefdGG -- -- 7692137 609 -- 4 4376 ( ++ gAaBadfBGa - - + - ) ++ - -- ( ( 11 ( ( ) + 096 - + ( - ( 6 -- - -- ) + - eGA ( -- + ++ ++ ++ -- ( ( 47559 61 ) ++ ++ ( fgeADefdag eFBDgfcEf 60 982214 - ( + - ) 5 ++ ) ( ) - ++ ++ ( - -- ) ( + ( cBDAAfAGGc - ++ - ( ) - ( adAbfG ( GgF BDbeCfGeB - ++ -- - - ++ - -- + ) ( ) ) ( + + -- ++ 597 gBc - ( ) ( - 9851 -- 830130 ) ++ + + BabeCFff ++ FfddEcdf 29814 -- + -- -- ( -- -- ++ ++ -- -- DEEg ++ ( ( ( ba - ++ ++ ++ ( ++ + - ( -- + -- -- -- - 50 -- - 7760 ( - + g ++ -- ( ++ - 092657 b - ) ( ++ ++ + 097181 -- -- ++ ( ++ bEFeceCaga ( + ) - 529418 73 -- 095 - ) ) 31 ( ) -- + + 817061 + + + 2 + cbeDgBEG -- BFBE ++ cFde + + 078000 + - + ) 766 ) dEEcfE + -- + -- dDdEdg ) -- ) 6287 - ( 7061 ( -- + ) 17 cfaDB -- GEe ) ) ( -- -- - ( ( + -- -- ) ++ + dfd + + + - 11 ) ) gBAg 917 ) ( 6 451406 ) ) ++ ACgeeDGD -- AEDcEacB ++ + ++ ) bbcgDcBC 43 64 ( ++ fDDCceEgE + ( ++ ++ - ) ++ 4848 bBbAcbB FcD ++ ( b + -- -- 464112 ++ ) FDGGgcb 1088263 ++ ) gEfaCceEC + Da - ++ ( CfBbfdA - -- Dbfc ++ ( DdfAfgEFce -- ( ++ ( ++ ++ FdcAbbbgDE ++ 5 fa ++ ABgeDGG ++ 0273427 ( ) ++ 4958 ++ - ++ ++ dfCABb b + -- DaFgdCaGDG ADadGEBcf 6753698 ) + + 4 ++ ( ++ 84487 + ab 183098 ( ( -- - ++ bfDCa ) ( 467 ++ ) ++ + ) -- 3 ) - CcbADFbC ( ++ - ) ++ ) ++ ( ++ ) ++ ++ -- -- ++ ++ ) -- ++ 4795 58 ) ( - 7 564014 + + -- ( ++ ) 464 -- ) -- -- + 9 ) -- ++ -- -- 0 ) 554490 -- ++ + ++ ) -- ) ) ++ CFGecdfcB 56 + ) 37 -- - ( c + 38126 ( ) de 855 ++ 11611 -- ++ + ) 5968159 ( -- 6332873 -- ( ( -- ) -- + 13 ++ + - gCDbg + ++ - ( eBGdAA 3 EFebdCBDgG - 585027 + 819874 ) BAAFcag ( -- - DFCcEcCfb 3450296 ) - 94468 - ( 24100 -- 0309041 - 296 ++ ) eFAFeGaEB + 514928 + ( fcea DGgcdE - BBdCC -- ) -- 71915 ++ ++ - ( 51 + ++ + -- -- 1669 - faaaa 553720 - -- - BaFfe ( - 1076744 - ++ ++ ++ -- 2 GEEaaB ) - ( ) ++ -- ++ CfBdFcb + -- - ) bDBGDgGFF - G + fdDbGBCDC ++ ++ + ) + - Gefb ) + dGbc - - Ccbc ( ++ ++ 634379 340467 + + agEdCeGBag 39 ge - + - - + -- ( afaGdfE 38334 adEdDdbFg Ga ) bBeD ) GeFFCaFAB - -- - 9385 + ++ + ) 978 -- ) - ) + 126 - + f ) -- 9 cefdF -- ) 5 ++ + ++ - ( + ) FCaFcGFd ( + -- ++ ) + 9578 + 201 - ) ( ) ) ) ( CdFacfGEeF -- - + + ++ GFCCaAeDf 28639 -- EaaBc ++ FeCbEFEe ++ -- ++ ++ - - BadcFD ( -- - acaeBba + ( ) ( ++ + -- 42 ( FeAAB -- ( - geb - aEcdEaCFbb + ( ( ++ -- ++ -- ++ - ( + - -- -- ) ++ ( ( + ++ - ) - -- 7749316 -- ++ -- ( ( 495 -- -- + - -- + 1929 ( ) 126901 ) ( BDdE ( + + 4643927 ) ++ 18701 ) A 2311567 - + ++ ) 521 + + - ) - ) ) - -- ++ ) + ) ++ - - ( 6698207 + fCa ++ ( -- ( ( ++ 12 - ++ fCF + 1605241 - ( 6378733 - ++ ( Bab ) 89115 - Cc 87480 + BCACFFE ( ) ( BDCFgebDbE 5088117 ( ++ ) - ) ) 37 6 ( - ga ) G ( AcBDaca 0164448 ) ++ 9 gfBfcCFFg 8406468 + ) + ( ) 4 ++ -- ( + - -- 16 -- 23 + - 4 ++ 7 -- ++ ( -- ++ + -- 4798730 + - 36 9 - ++ - + + 7 - gGg ++ -- + ) + ) ) -- ( ) - + - ++ gbCEBGag + 2 CeGBcG + AbcDGDfg -- ) - ++ ) DGcGgb ++ feeGD ) 86 ) ++ ( ba -- ) ) - 3976317 bbgE -- ++ ( ) ) ( ( dBcE b -- + - 29 - 673 ) + ( 30 252800 fDBA + ( - ++ 74 - ) ( ) EdbG ( - + 697 - ++ dGFGb 2 -- ++ + + aDA ) -- + + EaggdgFDg - -- -- 181 ) ) Ga - + ( - ( + - ) cgE BcBc 363 ) ebabcc + + -- ) 58335 - ) ) -- -- ( + 533 1893269 301003 ) 22630 bBgAGCf -- - 8513667 -- ++ ( -- ( - ( - DDgBDgaCA -- 9 - 7158375 ) ++ -- ( - ) EBbdCcf CCGBgc + -- da D ( ++ ) 39 ( ++ + G 54646 - -- + - - + ) ) ) -- + ( AEgbADGd ( fBdB 3761 - + - ++ ( ) -- ( ( - ++ ) + ( ) 1119497 ( -- gFfdg ( ++ e ) ( E FG ) + BEgebEFee ++ 169 ( + 6144 ( ( 8 ++ ( Addafa ) 889 ( 446094 - -- 821 0140146 ) + ( gfgeEDFCa DcGBfea Fgddgccddd -- gdfggbBeGa aEcFd ) ) 9620 + ++ + FCBCdbDe ++ ++ ) ad -- cce -- -- - - + ( 35670 ( 82525 1 -- ++ 124 Abcgdc ) BCg 262389 ( ( + ( - -- -- - ) + ( ) ( ) ) -- ) - G 113 ) GecDdaEEg GabC + ) ++ - 39873 -- - ( ++ 778 ++ + ) -- ( + ( ( + ( ) ( gBf - 1689 -- ( ++ EfA + - ( + - ( - + -- - - ) + BFecDeEFeB ) 5 DCabcBDaf 79 FCDCBEEC ++ ) -- ( ) ) ++ - ) + - dbbcFc 8444 -- ) + -- + + -- -- ++ bGAbaCcG + ( -- CffgDeaCGF -- -- 4658 ) - ) + + -- ) -- 45 0558 - ++ - ( ( -- 54 ++ 329 -- ++ -- GfdDcaBg - fgEeF -- ++ -- -- ) -- -- -- + -- efBfBbac - ) cCaADAddCG - - ) + - - ++ ) - fBEABga + ++ 60479 ) 2728607 ++ -- - ++ + ) - 503460 + - ++ - ) + + - -- ++ ++ eFg ( - 0394 ) -- 9734322 ( 3824445 ) ( ( -- - + + ( - ++ - ++ - ( ( - + ( 3 - ( -- dEbeb 018 -- ) - ( ++ + ( fb + -- ) ) - + cGbBDe 084380 -- - ( ) ++ ++ + A ) - + AdCCg ) ++ a -- ++ 224948 ++ ABFb ( ++ ++ 04 ( ++ eeB + + + - BGEeaCG ( ++ ++ ++ -- ++ -- ( + -- ( ) ++ ( eb ( - -- + cECc - ++ d + 678 - - - ( ++ 487742 244878 ( -- ) EeegBf 4622 b ( -- ( ( - -- -- ) ( -- -- + ++ aagdFCdbeE ) ++ - - ++ Bdefge 8788370 + + -- GdacF ++ CeBbfaccD BA ( ( Caabb -- -- + ) ) ) ( -- ++ CAaBFEe ( ( ACCFGCAgFA bebFcb + ++ ) ( ( 1 cFBdF ++ 227330 5286 caCbBaAFDf ( ) ADgfDcG ) 71446 + ) -- ++ + - af ( - ) - - ( + ++ -- + ( - -- efegg b ( ) ++ + cEbgdeAgd -- ) 6282847 ++ + ++ -- ++ - -- -- ++ -- - ( EbbgE FFbFA - ) + ) - -- -- 50 + EADbdaC ( ++ ++ + + cGDdcF 882 ) ++ ( a f ( ++ FAEC bb -- - 37218 - ( -- -- 60127 -- ( - 610700 ( -- ) ++ ( -- ) ( ) 85 AdbeceAda BDd - -- 9030 ) - DEgeadA -- + caB ++ -- FcAbcgBfFA -- ++ + - ) ( ( - eggdaBF - ++ - 62772 GBdee -- Bace -- 32198 eAEfAeABbd FDdbe ++ DDcGbAC -- ) ( ++ + -- 0 -- -- - ae 162 + efFgaa ++ - FFBBDG ffDeEFfcBE -- ++ ) ++ - ( + ) + - -- + 46097 -- 02 - -- 7868 ++ 81711 ) ++ ) + 
)==";
    
  size_t len = strlen(data);
  char *input = new char[len + 1];
  
  for (int i = 0; i < 1000; ++i) {
    copy(data, data + len, input);
    Lexer lexer(input, len);

    while (lexer.has_next()) {
      Token token = lexer.next();;
     
      switch (token.tag) {
      case PLUS: score += 1; break;
      case PLUS2: score += 2; break;
      case MINUS: score -= 1; break;
      case MINUS2: score -= 2; break;
      case DECIMAL: score += 11; break;
      case WORD: score += strlen(token.val); break;
      case LPAREN: score += 3; break;
      case RPAREN: score += 5; break;
      default:
	printf("unknown token!%d\n", token.tag);
      }
    }
  }

  printf("%ld\n", score);
  
  return 0;
}
