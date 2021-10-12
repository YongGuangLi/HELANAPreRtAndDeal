#include "waspcn.h"
#include "wasp67.h"
#include "wasp97.h"

bool g_bBLIF97 = true;             // IF97算法标识变量

namespace waspcn
{
    void SETSTD_WASP(int nStdID)
    {
        if (97 == nStdID)
        {
            g_bBLIF97 = true;
        }
        else
        {
            g_bBLIF97 = false;
        }
    }

    void GETSTD_WASP(int &nStdID)
    {
        if (true == g_bBLIF97)
        {
            nStdID = 97;
        }
        else
        {
            nStdID = 67;
        }
    }

    void P2T(double P, double &T, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            P2T97(P, &T, &nRange);
        }
        else
        {
            P2T67(P, &T, &nRange);
        }
    }

    void P2HL(double P, double &H, int &nRange)
    {
        if  (true == g_bBLIF97)
        {
            P2HL97(P, &H, &nRange);
        }
        else
        {
            P2HL67(P, &H, &nRange);
        }
    }

    void P2HG(double P, double &H, int &nRange)
    {
        if  (true == g_bBLIF97)
        {
            P2HG97(P, &H, &nRange);
        }
        else
        {
            P2HG67(P, &H, &nRange);
        }
    }

    void P2SL(double P, double &S, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            P2SL97(P, &S, &nRange);
        }
        else
        {
            P2SL67(P, &S, &nRange);
        }
    }

    void P2SG(double P, double &S, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            P2SG97(P, &S, &nRange);
        }
        else
        {
            P2SG67(P, &S, &nRange);
        }
    }

    void P2VL(double P, double &V, int &nRange)
    {
        if (true == g_bBLIF97) 
        {
            P2VL97(P, &V, &nRange);
        }
        else
        {
            P2VL67(P, &V, &nRange);
        }
    }

    void P2VG(double P, double &V, int &nRange)
    {
        if (true == g_bBLIF97) 
        {
            P2VG97(P, &V, &nRange);
        }
        else
        {
            P2VG67(P, &V, &nRange);
        }
    }

    void P2CPL(double P, double &CP, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            P2CPL97(P, &CP, &nRange);
        }
        else
        {
            P2CPL67(P, &CP, &nRange);
        }
    }

    void P2CPG(double P, double &CP, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            P2CPG97(P, &CP, &nRange);
        }
        else
        {
            P2CPG67(P, &CP, &nRange);
        }
    }

    void P2CVL(double P, double &CV, int & nRange)
    {
        if (true == g_bBLIF97)
        {
            P2CVL97(P, &CV, &nRange);
        }
        else
        {
            P2CVL67(P, &CV, &nRange);
        }
    }

    void P2CVG(double P, double &CV, int& nRange)
    {
        if (true == g_bBLIF97)
        {
            P2CVG97(P, &CV, &nRange);
        }
        else
        {
            P2CVG67(P, &CV, &nRange);
        }
    }

    void P2EL(double P, double &E, int &nRange)
    {
        if (true == g_bBLIF97) 
        {
            P2EL97(P, &E, &nRange);
        }
        else
        {
            P2EL67(P, &E, &nRange);
        }
    }

    void P2EG(double P, double &E, int &nRange)
    {
        if (true == g_bBLIF97) 
        {
            P2EG97(P, &E, &nRange);
        }
        else
        {
            P2EG67(P, &E, &nRange);
        }
    }

    void P2SSPL(double P, double &SSP, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            P2SSPL97(P, &SSP, &nRange);
        }
        else
        {
            P2SSPL67(P, &SSP, &nRange);
        }
    }

    void P2SSPG(double P, double &SSP, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            P2SSPG97(P, &SSP, &nRange);
        }
        else
        {
            P2SSPG67(P, &SSP, &nRange);
        }
    }

    void P2KSL(double P, double &KS, int &nRange)
    {
        if (true == g_bBLIF97) 
        {
            P2KSL97(P, &KS, &nRange);
        }
        else
        {
            P2KSL67(P, &KS, &nRange);
        }
    }

    void P2KSG(double P, double &KS, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            P2KSG97(P, &KS, &nRange);
        }
        else
        {
            P2KSG67(P, &KS, &nRange);
        }
    }

    void P2ETAL(double P, double &ETA, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            P2ETAL97(P, &ETA, &nRange);
        }
        else
        {
            P2ETAL67(P, &ETA, &nRange);
        }
    }

    void P2ETAG(double P, double &ETA, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            P2ETAG97(P, &ETA, &nRange);
        }
        else
        {
            P2ETAG67(P, &ETA, &nRange);
        }
    }

    void P2UL(double P, double &U, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            P2UL97(P, &U, &nRange);
        }
        else
        {
            P2UL67(P, &U, &nRange);
        }
    }

    void P2UG(double P, double &U, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            P2UG97(P, &U, &nRange);
        }
        else
        {
            P2UG67(P, &U, &nRange);
        }
    }

    void P2RAMDL(double P, double &RAMD, int &nRange)
    {
        if (true == g_bBLIF97) 
        {
            P2RAMDL97(P, &RAMD, &nRange);
        }
        else
        {
            P2RAMDL67(P, &RAMD, &nRange);
        }
    }

    void P2RAMDG(double P, double &RAMD, int & nRange)
    {
        if (true == g_bBLIF97) 
        {
            P2RAMDG97(P, &RAMD, &nRange);
        }
        else
        {
            P2RAMDG67(P, &RAMD, &nRange);
        }
    }

    void P2PRNL(double P, double &PRN, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            P2PRNL97(P, &PRN, &nRange);
        }
        else
        {
            P2PRNL67(P, &PRN, &nRange);
        }
    }

    void  P2PRNG(double P, double &PRN, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            P2PRNG97(P, &PRN, &nRange);
        }
        else
        {
            P2PRNG67(P, &PRN, &nRange);
        }
    }

    void P2EPSL(double P,double &EPS, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            P2EPSL97(P, &EPS, &nRange);
        }
        else
        {
            P2EPSL67(P, &EPS, &nRange);
        }
    }

    void P2EPSG(double P, double &EPS, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            P2EPSG97(P, &EPS, &nRange);
        }
        else
        {
            P2EPSG67(P, &EPS, &nRange);
        }
    }

    void P2NL(double P, double LAMD, double &N, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            P2NL97(P, LAMD, &N, &nRange);
        }
        else
        {
            P2NL67(P, LAMD, &N, &nRange);
        }
    }

    void P2NG(double P, double LAMD, double &N, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            P2NG97(P, LAMD, &N, &nRange);
        }
        else
        {
            P2NG67(P, LAMD, &N, &nRange);
        }
    }

    void P2L(double P, 
        double & T, double & H, double &S, double &V, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            P2L97(P, &T, &H, &S, &V, &X, &nRange);
        }
        else
        {
            P2L67(P, &T, &H, &S, &V, &X, &nRange);
        }
    }

    void P2G(double P, 
        double &T, double &H, double &S, double &V, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            P2G97(P, &T, &H, &S, &V, &X, &nRange);
        }
        else
        {
            P2G67(P, &T, &H, &S, &V, &X, &nRange);
        }
    }

    void PT2H(double P, double T, double &H, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PT2H97(P, T, &H, &nRange);
        }
        else
        {
            PT2H67(P, T, &H, &nRange);
        }
    }

    void PT2S(double P, double T, double &S, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PT2S97(P, T, &S, &nRange);
        }
        else
        {
            PT2S67(P, T, &S, &nRange);
        }
    }

    void PT2V(double P, double T, double &V, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PT2V97(P, T, &V, &nRange);
        }
        else
        {
            PT2V67(P, T, &V, &nRange);
        }
    }

    void PT2X(double P, double T, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PT2X97(P, T, &X, &nRange);
        }
        else
        {
            PT2X67(P, T, &X, &nRange);
        }
    }


    void PT2CP(double P, double T, double &CP, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PT2CP97(P, T, &CP, &nRange);
        }
        else
        {
            PT2CP67(P, T, &CP, &nRange);
        }
    }

    void PT2CV(double P, double T, double &CV, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PT2CV97(P, T, &CV, &nRange);
        }
        else
        {
            PT2CV67(P, T, &CV, &nRange);
        }
    }

    void PT2E(double P, double T, double &E, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PT2E97(P, T, &E, &nRange);
        }
        else
        {
            PT2E67(P, T, &E, &nRange);
        }
    }

    void PT2SSP(double P, double T, double &SSP, int &nRange)
    {
        if (true == g_bBLIF97) 
        {
            PT2SSP97(P, T, &SSP, &nRange);
        }
        else
        {
            PT2SSP67(P, T, &SSP, &nRange);
        }
    }


    void PT2KS(double P, double T, double &KS, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PT2KS97(P, T, &KS, &nRange);
        }
        else
        {
            PT2KS67(P, T, &KS, &nRange);
        }
    }

    void PT2ETA(double P, double T, double &ETA, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PT2ETA97(P, T, &ETA, &nRange);
        }
        else
        {
            PT2ETA67(P, T, &ETA, &nRange);
        }
    }

    void PT2U(double P, double T, double &U, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PT2U97(P, T, &U, &nRange);
        }
        else
        {
            PT2U67(P, T, &U, &nRange);
        }
    }

    void PT2RAMD(double P, double T, double &RAMD, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PT2RAMD97(P, T, &RAMD, &nRange);
        }
        else
        {
            PT2RAMD67(P, T, &RAMD, &nRange);
        }
    }


    void PT2PRN(double P, double T, double &PRN, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PT2PRN97(P, T, &PRN, &nRange);
        }
        else
        {
            PT2PRN67(P, T, &PRN, &nRange);
        }
    }

    void PT2EPS(double P, double T, double &EPS, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PT2EPS97(P, T, &EPS, &nRange);
        }
        else
        {
            PT2EPS67(P, T, &EPS, &nRange);
        }
    }

    void PT2N(double P, double T, double LAMD, double &N, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PT2N97(P, T, LAMD, &N, &nRange);
        }
        else
        {
            PT2N67(P, T, LAMD, &N, &nRange);
        }
    }

    void PT(double P, double T, 
        double &H, double &S, double &V, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PT97(P, T, &H, &S, &V, &X, &nRange);
        }
        else
        {
            PT67(P, T, &H, &S, &V, &X, &nRange);
        }
    }

    void PT2MV(double P,double T, 
        double &H, double &S, double &V, 
        double &E,double &CP, double &CV, double &SSP, int &nRange)
    {
        PX2H(P, 0.95, H, nRange);
        double H1 = H;
        double T1;
        P2T(P, T1, nRange);
        H=PT2HReg2MV(P,T);
        if(P<=10.0 && H>=H1 && T1>=T)
        {
            nRange=128;     //存在亚稳态参数
        }
        else
        {
            nRange=0;       //不存在亚稳态参数
        }
        return;
    }

    void  PT2HMV(double P, double T, double &H)
    {
        H=PT2HReg2MV(P, T);
    }

    void  PT2VMV(double P, double T, double &V)
    {
        V=PT2VReg2MV(P, T);
    }

    void  PT2EMV(double P, double T, double &E)
    {
        E=PT2EReg2MV(P, T);
    }

    void  PT2SMV(double P, double T, double &S)
    {
        S=PT2SReg2MV(P, T);
    }

    void  PT2CPMV(double P, double T, double &CP)
    {
        CP=PT2CPReg2MV(P, T);
    }

    void  PT2SSPMV(double P, double T, double &SSP)
    {
        SSP=PT2SSPReg2MV(P, T);
    }

    void  PT2CVMV(double P, double T, double &CV)
    {
        CV=PT2CVReg2MV(P, T);
    }

    void PH2T(double P, double H, double &T, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PH2T97(P, H, &T, &nRange);
        }
        else
        {
            PH2T67(P, H, &T, &nRange);
        }
    }

    void PH2S(double P, double H, double &S, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PH2S97(P, H, &S, &nRange);
        }
        else
        {
            PH2S67(P, H, &S, &nRange);
        }
    }

    void PH2V(double P, double H, double &V, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PH2V97(P, H, &V, &nRange);
        }
        else
        {
            PH2V67(P, H, &V, &nRange);
        }
    }

    void PH2X(double P, double H, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PH2X97(P, H, &X, &nRange);
        }
        else
        {
            PH2X67(P, H, &X, &nRange);
        }
    }

    void PH2SSP(double P, double H, double &SSP, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PH2SSP97(P, H, &SSP, &nRange);
        }
        else
        {
            PH2SSP67(P, H, &SSP, &nRange);
        }
    }

    void PH2CP(double P, double H,double &CP,int & nRange)
    {
        double T;
        PH2T(P, H, T, nRange);
        PT2CP(P, T, CP, nRange);
    }

    void PH2CV(double P, double H,double &CV,int & nRange)
    {
        double T;
        PH2T(P, H, T, nRange);
        PT2CV(P, T, CV, nRange);
    }

    void PH2E(double P, double H,double &E,int & nRange)
    {
        double T;
        PH2T(P, H, T, nRange);
        PT2E(P, T, E, nRange);
    }

    void  PH2KS(double P, double H,double &KS,int & nRange)
    {
        double T;
        PH2T(P, H, T, nRange);
        PT2KS(P, T, KS, nRange);
    }

    void  PH2ETA(double P, double H,double &ETA,int & nRange)
    {
        double T;
        PH2T(P, H, T, nRange);
        PT2ETA(P, T, ETA, nRange);
    }

    void  PH2U(double P, double H, double &U, int &nRange)
    {
        double T;
       PH2T(P, H, T, nRange);
        PT2U(P, T, U, nRange);
    }

    void PH2RAMD(double P, double H,double &RAMD,int & nRange)
    {
        double T;
        PH2T(P, H, T, nRange);
        PT2RAMD(P, T, RAMD, nRange);
    }

    void PH2PRN(double P, double H,double &PRN,int & nRange)
    {
        double T;
        PH2T(P, H, T, nRange);
        PT2PRN(P, T, PRN, nRange);
    }

    void PH2EPS(double P, double H,double &EPS,int & nRange)
    {
        double T;
        PH2T(P, H, T, nRange);
        PT2EPS(P, T, EPS, nRange);
    }

    void PH2N(double P, double H, double LAMD, double &N, int &nRange)
    {
        double T;
        PH2T(P, H, T, nRange);
        PT2N(P, T, 2.265E-7, N, nRange);
    }

    void PH(double P, double &T, 
        double H, double &S, double &V, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PH97(P, &T, H, &S, &V, &X, &nRange);
        }
        else
        {
            PH67(P, &T, H, &S, &V, &X, &nRange);
        }
    }

    void PS2T(double P, double S, double &T, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PS2T97(P, S, &T, &nRange);
        }
        else
        {
            PS2T67(P, S, &T, &nRange);
        }
    }

    void PS2H(double P, double S, double &H, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PS2H97(P, S, &H, &nRange);
        }
        else
        {
            PS2H67(P, S, &H, &nRange);
        }
    }

    void PS2V(double P, double S, double &V, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PS2V97(P, S, &V, &nRange);
        }
        else
        {
            PS2V67(P, S, &V, &nRange);
        }
    }

    void PS2X(double P, double S, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PS2X97(P, S, &X, &nRange);
        }
        else
        {
            PS2X67(P, S, &X, &nRange);
        }
    }

    void PS(double P, double &T, double &H, double S, double &V, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PS97(P, &T, &H, S, &V, &X, &nRange);
        }
        else
        {
            PS67(P, &T, &H, S, &V, &X, &nRange);
        }
    }

    void PV2T(double P, double V, double &T, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PV2T97(P, V, &T, &nRange);
        }
        else
        {
            PV2T67(P, V, &T, &nRange);
        }
    }

    void PV2H(double P, double V, double &H, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PV2H97(P, V, &H, &nRange);
        }
        else
        {
            PV2H67(P, V, &H, &nRange);
        }
    }

    void PV2S(double P, double V, double &S,int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PV2S97(P, V, &S, &nRange);
        }
        else
        {
            PV2S67(P, V, &S, &nRange);
        }
    }

    void PV2X(double P, double V, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PV2X97(P, V, &X, &nRange);
        }
        else
        {
            PV2X67(P, V, &X, &nRange);
        }
    }

    void PV(double P,double &T, double &H, double &S, double V, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PV97(P, &T, &H, &S, V, &X, &nRange);
        }
        else
        {
            PV67(P, &T, &H, &S, V, &X, &nRange);
        }
    }

    void PX2T(double P, double X, double &T, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PX2T97(P, X, &T, &nRange);
        }
        else
        {
            PX2T67(P, X, &T, &nRange);
        }
    }

    void PX2H(double P, double X, double &H, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PX2H97(P, X, &H, &nRange);
        }
        else
        {
            PX2H67(P, X, &H, &nRange);
        }
    }

    void PX2S(double P, double X, double &S, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PX2S97(P, X, &S, &nRange);
        }
        else
        {
            PX2S67(P, X, &S, &nRange);
        }
    }

    void PX2V(double P, double X, double &V, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PX2V97(P, X, &V, &nRange);
        }
        else
        {
            PX2V67(P, X, &V, &nRange);
        }
    }

    void PX(double P, double &T, double &H, double &S, double &V, 
        double X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            PX97(P, &T, &H, &S, &V, X, &nRange);
        }
        else
        {
            PX67(P, &T, &H, &S, &V, X, &nRange);
        }
    }

    void T2P(double T,double &P, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2P97(T, &P, &nRange);
        }
        else
        {
            T2P67(T, &P, &nRange);
        }
    }

    void T2HL(double T, double &H, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2HL97(T, &H, &nRange);
        }
        else
        {
            T2HL67(T, &H, &nRange);
        }
    }

    void T2HG(double T, double &H, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2HG97(T, &H, &nRange);
        }
        else
        {
            T2HG67(T, &H, &nRange);
        }
    }

    void T2SL(double T, double &S, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2SL97(T, &S, &nRange);
        }
        else
        {
            T2SL67(T, &S, &nRange);
        }
    }

    void T2SG(double T, double &S, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2SG97(T, &S, &nRange);
        }
        else
        {
            T2SG67(T, &S, &nRange);
        }
    }

    void T2VL(double T, double &V, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2VL97(T, &V, &nRange);
        }
        else
        {
            T2VL67(T, &V, &nRange);
        }
    }

    void T2VG(double T,double &V, int & nRange)
    {
        if (true == g_bBLIF97)
        {
            T2VG97(T, &V, &nRange);
        }
        else
        {
            T2VG67(T, &V, &nRange);
        }
    }

    void T2CPL(double T, double &CP, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2CPL97(T, &CP, &nRange);
        }
        else
        {
            T2CPL67(T, &CP, &nRange);
        }
    }

    void T2CPG(double T, double &CP, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2CPG97(T, &CP, &nRange);
        }
        else
        {
            T2CPG67(T, &CP, &nRange);
        }
    }

    void T2CVL(double T, double &CV, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2CVL97(T, &CV, &nRange);
        }
        else
        {
            T2CVL67(T, &CV, &nRange);
        }
    }

    void T2CVG(double T, double &CV, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2CVG97(T, &CV, &nRange);
        }
        else
        {
            T2CVG67(T, &CV, &nRange);
        }
    }

    void T2EL(double T, double &E, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2EL97(T, &E, &nRange);
        }
        else
        {
            T2EL67(T, &E, &nRange);
        }
    }

    void T2EG(double T, double &E, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2EG97(T, &E, &nRange);
        }
        else
        {
            T2EG67(T, &E, &nRange);
        }
    }

    void T2SSPL(double T, double &SSP, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2SSPL97(T, &SSP, &nRange);
        }
        else
        {
            T2SSPL67(T, &SSP, &nRange);
        }
    }

    void T2SSPG(double T, double &SSP, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2SSPG97(T, &SSP, &nRange);
        }
        else
        {
            T2SSPG67(T, &SSP, &nRange);
        }
    }

    void T2KSL(double T, double &KS, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2KSL97(T, &KS, &nRange);
        }
        else
        {
            T2KSL67(T, &KS, &nRange);
        }
    }

    void T2KSG(double T, double &KS, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2KSG97(T, &KS, &nRange);
        }
        else
        {
            T2KSG67(T, &KS, &nRange);
        }
    }

    void T2ETAL(double T, double &ETA, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2ETAL97(T, &ETA, &nRange);
        }
        else
        {
            T2ETAL67(T, &ETA, &nRange);
        }
    }

    void T2ETAG(double T, double &ETA, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2ETAG97(T, &ETA, &nRange);
        }
        else
        {
            T2ETAG67(T, &ETA, &nRange);
        }
    }

    void T2UL(double T, double &U, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2UL97(T, &U, &nRange);
        }
        else
        {
            T2UL67(T, &U, &nRange);
        }
    }

    void T2UG(double T, double &U, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2UG97(T, &U, &nRange);
        }
        else
        {
            T2UG67(T, &U, &nRange);
        }
    }

    void T2RAMDL(double T, double &RAMD, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2RAMDL97(T, &RAMD, &nRange);
        }
        else
        {
            T2RAMDL67(T, &RAMD, &nRange);
        }
    }

    void T2RAMDG(double T, double &RAMD, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2RAMDG97(T, &RAMD, &nRange);
        }
        else
        {
            T2RAMDG67(T, &RAMD, &nRange);
        }
    }

    void T2PRNL(double T, double &PRN, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2PRNL97(T, &PRN, &nRange);
        }
        else
        {
            T2PRNL67(T, &PRN, &nRange);
        }
    }

    void T2PRNG(double T, double &PRN, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2PRNG97(T, &PRN, &nRange);
        }
        else
        {
            T2PRNG67(T, &PRN, &nRange);
        }
    }

    void T2EPSL(double T, double &EPS, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2EPSL97(T, &EPS, &nRange);
        }
        else
        {
            T2EPSL67(T, &EPS, &nRange);
        }
    }

    void T2EPSG(double T, double &EPS, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2EPSG97(T, &EPS, &nRange);
        }
        else
        {
            T2EPSG67(T, &EPS, &nRange);
        }
    }

    void T2NL(double T, double LAMD, double &N, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2NL97(T, LAMD, &N, &nRange);
        }
        else
        {
            T2NL67(T, LAMD, &N, &nRange);
        }
    }

    void T2NG(double T, double LAMD, double &N, int &nRange)
    {
        if (true == g_bBLIF97) 
        {
            T2NG97(T, LAMD, &N, &nRange);
        }
        else
        {
            T2NG67(T, LAMD, &N, &nRange);
        }
    }

    void T2SURFT(double T, double &SURFT, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2SURFT97(T, &SURFT, &nRange);
        }
        else
        {
            T2SURFT67(T, &SURFT, &nRange);
        }
    }

    void T2L(double &P, 
        double T, double &H, double &S, double &V, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2L97(&P, T, &H, &S, &V, &X, &nRange);
        }
        else
        {
            T2L67(&P, T, &H, &S, &V, &X, &nRange);
        }
    }

    void T2G(double &P, 
        double T, double &H, double &S, double &V, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            T2G97(&P, T, &H, &S, &V, &X, &nRange);
        }
        else
        {
            T2G67(&P, T, &H, &S, &V, &X, &nRange);
        }
    }

    void TH2PHP(double T, double H, double &P, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TH2PHP97(T, H, &P, &nRange);
        }
        else
        {
            TH2PHP67(T, H, &P, &nRange);
        }
    }

    void TH2PLP(double T, double H, double &P, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TH2PLP97(T, H, &P, &nRange);
        }
        else
        {
            TH2PLP67(T, H, &P, &nRange);
        }
    }

    void TH2P(double T, double H, double &P, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TH2P97(T, H, &P, &nRange);
        }
        else
        {
            TH2P67(T, H, &P, &nRange);
        }
    }

    void TH2SHP(double T, double H, double &S, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TH2SHP97(T, H, &S, &nRange);
        }
        else
        {
            TH2SHP67(T, H, &S, &nRange);
        }
    }

    void TH2SLP(double T, double H, double &S, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TH2SLP97(T, H, &S, &nRange);
        }
        else
        {
            TH2SLP67(T, H, &S, &nRange);
        }
    }

    void TH2S(double T, double H, double &S, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TH2S97(T, H, &S, &nRange);
        }
        else
        {
            TH2S67(T, H, &S, &nRange);
        }
    }

    void TH2VHP(double T, double H, double &V,int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TH2VHP97(T, H, &V, &nRange);
        }
        else
        {
            TH2VHP67(T, H, &V, &nRange);
        }
    }

    void TH2VLP(double T, double H, double &V, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TH2VLP97(T, H, &V, &nRange);
        }
        else
        {
            TH2VLP67(T, H, &V, &nRange);
        }
    }

    void TH2V(double T, double H, double &V, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TH2V97(T, H, &V, &nRange);
        }
        else
        {
            TH2V67(T, H, &V, &nRange);
        }
    }

    void TH2XHP(double T, double H, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TH2XHP97(T, H, &X, &nRange);
        }
        else
        {
            TH2XHP67(T, H, &X, &nRange);
        }
    }

    void TH2XLP(double T, double H, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TH2XLP97(T, H, &X, &nRange);
        }
        else
        {
            TH2XLP67(T, H, &X, &nRange);
        }
    }

    void TH2X(double T, double H, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TH2X97(T, H, &X, &nRange);
        }
        else
        {
            TH2X67(T, H, &X, &nRange);
        }
    }

    void TH(double &P, 
        double T, double H, double &S, double &V, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TH97(&P, T, H, &S, &V, &X, &nRange);
        }
        else
        {
            TH67(&P, T, H, &S, &V, &X, &nRange);
        }
    }

    void THHP(double &P, 
        double T, double H, double &S, double &V, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            THHP97(&P, T, H, &S, &V, &X, &nRange);
        }
        else
        {
            THHP67(&P, T, H, &S, &V, &X, &nRange);
        }
    }

    void THLP(double &P, 
        double T, double H, double &S, double &V, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            THLP97(&P, T, H, &S, &V, &X, &nRange);
        }
        else
        {
            THLP67(&P, T, H, &S, &V, &X, &nRange);
        }
    }


    void TS2PHP(double T, double S, double &P, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TS2PHP97(T, S, &P, &nRange);
        }
        else
        {
            TS2PHP67(T, S, &P, &nRange);
        }
    }

    void TS2PLP(double T, double S, double &P, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TS2PLP97(T, S, &P, &nRange);
        }
        else
        {
            TS2PLP67(T, S, &P, &nRange);
        }
    }

    void TS2P(double T, double S, double &P, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TS2P97(T, S, &P, &nRange);
        }
        else
        {
            TS2P67(T, S, &P, &nRange);
        }
    }

    void TS2HHP(double T, double S, double &H, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TS2HHP97(T, S, &H, &nRange);
        }
        else
        {
            TS2HHP67(T, S, &H, &nRange);
        }
    }

    void TS2HLP(double T, double S, double &H, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TS2HLP97(T, S, &H, &nRange);
        }
        else
        {
            TS2HLP67(T, S, &H, &nRange);
        }
    }



    void TS2H(double T, double S, double &H, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TS2H97(T, S, &H, &nRange);
        }
        else
        {
            TS2H67(T, S, &H, &nRange);
        }
    }

    void TS2VHP(double T, double S, double &V, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TS2VHP97(T, S, &V, &nRange);
        }
        else
        {
            TS2VHP67(T, S, &V, &nRange);
        }
    }

    void TS2VLP(double T, double S, double &V, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TS2VLP97(T, S, &V, &nRange);
        }
        else
        {
            TS2VLP67(T, S, &V, &nRange);
        }
    }

    void TS2V(double T, double S, double &V, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TS2V97(T, S, &V, &nRange);
        }
        else
        {
            TS2V67(T, S, &V, &nRange);
        }
    }

    void TS2X(double T, double S, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TS2X97(T, S, &X, &nRange);
        }
        else
        {
            TS2X67(T, S, &X, &nRange);
        }
    }

    void TS(double &P, 
        double T, double &H, 
        double S, double &V, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TS97(&P, T, &H, S, &V, &X, &nRange);
        }
        else
        {
            TS67(&P, T, &H, S, &V, &X, &nRange);
        }
    }

    void TSHP(double &P, 
        double T, double &H, double S, double &V, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TSHP97(&P, T, &H, S, &V, &X, &nRange);
        }
        else
        {
            TSHP67(&P, T, &H, S, &V, &X, &nRange);
        }
    }

    void TSLP(double &P, 
        double T, double &H, double S, double &V, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TSLP97(&P, T, &H, S, &V, &X, &nRange);
        }
        else
        {
            TSLP67(&P, T, &H, S, &V, &X, &nRange);
        }
    }

    void TV2P(double T, double V, double &P, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TV2P97(T, V, &P, &nRange);
        }
        else
        {
            TV2P67(T, V, &P, &nRange);
        }
    }

    void TV2H(double T, double V, double &H, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TV2H97(T, V, &H, &nRange);
        }
        else
        {
            TV2H67(T, V, &H, &nRange);
        }
    }

    void TV2S(double T, double V, double &S, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TV2S97(T, V, &S, &nRange);
        }
        else
        {
            TV2S67(T, V, &S, &nRange);
        }
    }

    void TV2X(double T, double V, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TV2X97(T, V, &X, &nRange);
        }
        else
        {
            TV2X67(T, V, &X, &nRange);
        }
    }

    void TV(double &P, 
        double T, double &H, double &S, 
        double V, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TV97(&P, T, &H, &S, V, &X, &nRange);
        }
        else
        {
            TV67(&P, T, &H, &S, V, &X, &nRange);
        }
    }

    void TX2P(double T, double X, double &P, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TX2P97(T, X, &P, &nRange);
        }
        else
        {
            TX2P67(T, X, &P, &nRange);
        }
    }

    void TX2H(double T, double X, double &H, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TX2H97(T, X, &H, &nRange);
        }
        else
        {
            TX2H67(T, X, &H, &nRange);
        }
    }

    void TX2S(double T, double X, double &S, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TX2S97(T, X, &S, &nRange);
        }
        else
        {
            TX2S67(T, X, &S, &nRange);
        }
    }

    void TX2V(double T, double X, double &V, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TX2V97(T, X, &V, &nRange);
        }
        else
        {
            TX2V67(T, X, &V, &nRange);
        }
    }

    void TX(double &P, 
        double T, double &H, double &S, double &V, double X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            TX97(&P, T, &H, &S, &V, X, &nRange);
        }
        else
        {
            TX67(&P, T, &H, &S, &V, X, &nRange);
        }
    }

    void H2TL(double H, double &T, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            H2TL97(H, &T, &nRange);
        }
        else
        {
            H2TL67(H, &T, &nRange);
        }
    }

    void HS2P(double H, double S, double &P, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            HS2P97(H, S, &P, &nRange);
        }
        else
        {
            HS2P67(H, S, &P, &nRange);
        }
    }

    void HS2T(double H, double S, double &T, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            HS2T97(H, S, &T, &nRange);
        }
        else
        {
            HS2T67(H, S, &T, &nRange);
        }
    }

    void HS2V(double H, double S, double &V, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            HS2V97(H, S, &V, &nRange);
        }
        else
        {
            HS2V67(H, S, &V, &nRange);
        }
    }

    void HS2X(double H, double S, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            HS2X97(H, S, &X, &nRange);
        }
        else
        {
            HS2X67(H, S, &X, &nRange);
        }
    }

    void HS(double &P, double &T, 
        double H, double S, double &V, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            HS97(&P, &T, H, S, &V, &X, &nRange);
        }
        else
        {
            HS67(&P, &T, H, S, &V, &X, &nRange);
        }
    }

    void HV2P(double H, double V, double &P, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            HV2P97(H, V, &P, &nRange);
        }
        else
        {
            HV2P67(H, V, &P, &nRange);
        }
    }

    void HV2T(double H, double V, double &T, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            HV2T97(H, V, &T, &nRange);
        }
        else
        {
            HV2T67(H, V, &T, &nRange);
        }
    }

    void HV2S(double H, double V, double &S, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            HV2S97(H, V, &S, &nRange);
        }
        else
        {
            HV2S67(H, V, &S, &nRange);
        }
    }

    void HV2X(double H, double V, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            HV2X97(H, V, &X, &nRange);
        }
        else
        {
            HV2X67(H, V, &X, &nRange);
        }
    }

    void HV(double &P, double &T, 
        double H, double &S, 
        double V, double &X, int& nRange)
    {
        if (true == g_bBLIF97)
        {
            HV97(&P, &T, H, &S, V, &X, &nRange);
        }
        else
        {
            HV67(&P, &T, H, &S, V, &X, &nRange);
        }
    }

    void HX2T(double H, double X, double &T, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            HX2T97(H, X, &T, &nRange);
        }
        else
        {
            HX2T67(H, X, &T, &nRange);
        }
    }

    void HX2P(double H, double X, double &P, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            HX2P97(H, X, &P, &nRange);
        }
        else
        {
            HX2P67(H, X, &P, &nRange);
        }
    }

    void HX2S(double H, double X, double &S, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            HX2S97(H, X, &S, &nRange);
        }
        else
        {
            HX2S67(H, X, &S, &nRange);
        }
    }

    void HX2V(double H, double X, double &V, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            HX2V97(H, X, &V, &nRange);
        }
        else
        {
            HX2V67(H, X, &V, &nRange);
        }
    }

    void HX(double &P, double &T, 
        double H, double &S, double &V, 
        double X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            HX97(&P, &T, H, &S, &V, X, &nRange);
        }
        else
        {
            HX67(&P, &T, H, &S, &V, X, &nRange);
        }
    }

    void HX2THP(double H, double X, double &T, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            HX2THP97(H, X, &T, &nRange);
        }
        else
        {
            HX2THP67(H, X, &T, &nRange);
        }
    }

    void HX2PHP(double H, double X, double &P, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            HX2PHP97(H, X, &P, &nRange);
        }
        else
        {
            HX2PHP67(H, X, &P, &nRange);
        }
    }


    void HX2SHP(double H, double X, double &S, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            HX2SHP97(H, X, &S, &nRange);
        }
        else
        {
            HX2SHP67(H, X, &S, &nRange);
        }
    }

    void  HX2VHP(double H, double X, double &V, int & nRange)
    {
        if (true == g_bBLIF97) 
        {
            HX2VHP97(H, X, &V, &nRange);
        }
        else
        {
            HX2VHP67(H, X, &V, &nRange);
        }
    }

    void  HXHP(double &P, double &T, 
        double H, double &S, double &V, 
        double X, int &nRange)
    {
        if (true == g_bBLIF97) 
        {
            HXHP97(&P, &T, H, &S, &V, X, &nRange);
        }
        else
        {
            HXHP67(&P, &T, H, &S, &V, X, &nRange);
        }
    }

    void HX2TLP(double H, double X, double &T, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            HX2TLP97(H, X, &T, &nRange);
        }
        else
        {
            HX2TLP67(H, X, &T, &nRange);
        }
    }

    void HX2PLP(double H, double X, double &P, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            HX2PLP97(H, X, &P, &nRange);
        }
        else
        {
            HX2PLP67(H, X, &P, &nRange);
        }
    }

    void HX2SLP(double H, double X, double &S, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            HX2SLP97(H, X, &S, &nRange);
        }
        else
        {
            HX2SLP67(H, X, &S, &nRange);
        }
    }

    void HX2VLP(double H, double X, double &V, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            HX2VLP97(H, X, &V, &nRange);
        }
        else
        {
            HX2VLP67(H, X, &V, &nRange);
        }
    }

    void HXLP(double &P, double &T, 
        double H, double &S, double &V, 
        double X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            HXLP97(&P, &T, H, &S, &V, X, &nRange);
        }
        else
        {
            HXLP67(&P, &T, H, &S, &V, X, &nRange);
        }
    }

    void S2TG(double S, double &T, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            S2TG97(S, &T, &nRange);
        }
        else
        {
            S2TG67(S, &T, &nRange);
        }
    }


    void SV2P(double S, double V, double &P, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            SV2P97(S, V, &P, &nRange);
        }
        else
        {
            SV2P67(S, V, &P, &nRange);
        }
    }

    void SV2T(double S, double V, double &T, int &nRange)
    {
        if (true == g_bBLIF97) 
        {
            SV2T97(S, V, &T, &nRange);
        }
        else
        {
            SV2T67(S, V, &T, &nRange);
        }
    }

    void SV2H(double S, double V, double &H, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            SV2H97(S, V, &H, &nRange);
        }
        else
        {
            SV2H67(S, V, &H, &nRange);
        }
    }

    void SV2X(double S, double V, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            SV2X97(S, V, &X, &nRange);
        }
        else
        {
            SV2X67(S, V, &X, &nRange);
        }
    }

    void SV(double &P, double &T, double &H, 
        double S, double V, double &X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            SV97(&P, &T, &H, S, V, &X, &nRange);
        }
        else
        {
            SV67(&P, &T, &H, S, V, &X, &nRange);
        }
    }

    void SX2T(double S, double X, double &T, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            SX2T97(S, X, &T, &nRange);
        }
        else
        {
            SX2T67(S, X, &T, &nRange);
        }
    }

    void SX2P(double S, double X, double &P, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            SX2P97(S, X, &P, &nRange);
        }
        else
        {
            SX2P67(S, X, &P, &nRange);
        }
    }

    void SX2H(double S, double X, double &H, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            SX2H97(S, X, &H, &nRange);
        }
        else
        {
            SX2H67(S, X, &H, &nRange);
        }
    }

    void SX2V(double S, double X, double &V, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            SX2V97(S, X, &V, &nRange);
        }
        else
        {
            SX2V67(S, X, &V, &nRange);
        }
    }

    void SX(double &P, double &T, double &H, 
        double S, double &V, double X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            SX97(&P, &T, &H, S, &V, X, &nRange);
        }
        else
        {
            SX67(&P, &T, &H, S, &V, X, &nRange);
        }
    }

    void SX2THP(double S, double X, double &T, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            SX2THP97(S, X, &T, &nRange);
        }
        else
        {
            SX2THP67(S, X, &T, &nRange);
        }
    }

    void SX2PHP(double S, double X, double &P, int & nRange)
    {
        if (true == g_bBLIF97)
        {
            SX2PHP97(S, X, &P, &nRange);
        }
        else
        {
            SX2PHP67(S, X, &P, &nRange);
        }
    }

    void SX2HHP(double S, double X, double &H, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            SX2HHP97(S, X, &H, &nRange);
        }
        else
        {
            SX2HHP67(S, X, &H, &nRange);
        }
    }

    void SX2VHP(double S, double X, double &V, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            SX2VHP97(S, X, &V, &nRange);
        }
        else
        {
            SX2VHP67(S, X, &V, &nRange);
        }
    }

    void SXHP(double &P, double &T, double &H, 
        double S, double &V, 
        double X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            SXHP97(&P, &T, &H, S, &V, X, &nRange);
        }
        else
        {
            SXHP67(&P, &T, &H, S, &V, X, &nRange);
        }
    }


    void SX2TMP(double S, double X, double &T, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            SX2TMP97(S, X, &T, &nRange);
        }
        else
        {
            SX2TMP67(S, X, &T, &nRange);
        }
    }

    void SX2PMP(double S, double X, double &P, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            SX2PMP97(S, X, &P, &nRange);
        }
        else
        {
            SX2PMP67(S, X, &P, &nRange);
        }
    }

    void SX2HMP(double S, double X, double &H, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            SX2HMP97(S, X, &H, &nRange);
        }
        else
        {
            SX2HMP67(S, X, &H, &nRange);
        }
    }

    void SX2VMP(double S, double X, double &V, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            SX2VMP97(S, X, &V, &nRange);
        }
        else
        {
            SX2VMP67(S, X, &V, &nRange);
        }
    }

    void SXMP(double &P, double &T, double &H, 
        double S, double &V, 
        double X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            SXMP97(&P, &T, &H, S, &V, X, &nRange);
        }
        else
        {
            SXMP67(&P, &T, &H, S, &V, X, &nRange);
        }
    }


    void SX2TLP(double S, double X, double &T, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            SX2TLP97(S, X, &T, &nRange);
        }
        else
        {
            SX2TLP67(S, X, &T, &nRange);
        }
    }

    void SX2PLP(double S, double X, double &P, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            SX2PLP97(S, X, &P, &nRange);
        }
        else
        {
            SX2PLP67(S, X, &P, &nRange);
        }
    }

    void SX2HLP(double S, double X, double &H, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            SX2HLP97(S, X, &H, &nRange);
        }
        else
        {
            SX2HLP67(S, X, &H, &nRange);
        }
    }

    void SX2VLP(double S, double X, double &V, int & nRange)
    {
        if (true == g_bBLIF97)
        {
            SX2VLP97(S, X, &V, &nRange);
        }
        else
        {
            SX2VLP67(S, X, &V, &nRange);
        }
    }

    void SXLP(double &P, double &T, double &H, 
        double S, double &V, double X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            SXLP97(&P, &T, &H, S, &V, X, &nRange);
        }
        else
        {
            SXLP67(&P, &T, &H, S, &V, X, &nRange);
        }
    }

    void V2TG(double V, double &T, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            V2TG97(V, &T, &nRange);
        }
        else
        {
            V2TG67(V, &T, &nRange);
        }
    }

    void VX2T(double V, double X, double &T, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            VX2T97(V, X, &T, &nRange);
        }
        else
        {
            VX2T67(V, X, &T, &nRange);
        }
    }

    void VX2P(double V, double X, double &P, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            VX2P97(V, X, &P, &nRange);
        }
        else
        {
            VX2P67(V, X, &P, &nRange);
        }
    }

    void VX2H(double V, double X, double &H, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            VX2H97(V, X, &H, &nRange);
        }
        else
        {
            VX2H67(V, X, &H, &nRange);
        }
    }

    void VX2S(double V, double X, double &S, int & nRange)
    {
        if (true == g_bBLIF97)
        {
            VX2S97(V, X, &S, &nRange);
        }
        else
        {
            VX2S67(V, X, &S, &nRange);
        }
    }

    void VX(double &P, double &T, double &H, double &S, 
        double V, double X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            VX97(&P, &T, &H, &S, V, X, &nRange);
        }
        else
        {
            VX67(&P, &T, &H, &S, V, X, &nRange);
        }
    }

    void VX2THP(double V, double X, double &T,int &nRange)
    {
        if (true == g_bBLIF97)
        {
            VX2THP97(V, X, &T, &nRange);
        }
        else
        {
            VX2THP67(V, X, &T, &nRange);
        }
    }

    void VX2PHP(double V, double X, double &P, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            VX2PHP97(V, X, &P, &nRange);
        }
        else
        {
            VX2PHP67(V, X, &P, &nRange);
        }
    }

    void VX2HHP(double V, double X, double &H, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            VX2HHP97(V, X, &H, &nRange);
        }
        else
        {
            VX2HHP67(V, X, &H, &nRange);
        }
    }

    void VX2SHP(double V, double X, double &S, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            VX2SHP97(V, X, &S, &nRange);
        }
        else
        {
            VX2SHP67(V, X, &S, &nRange);
        }
    }

    void VXHP(double &P, double &T, double &H, double &S, 
        double V, double X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            VXHP97(&P, &T, &H, &S, V, X, &nRange);
        }
        else
        {
            VXHP67(&P, &T, &H, &S, V, X, &nRange);
        }
    }

    void VX2TLP(double V, double X, double &T, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            VX2TLP97(V, X, &T, &nRange);
        }
        else
        {
            VX2TLP67(V, X, &T, &nRange);
        }
    }

    void VX2PLP(double V, double X, double &P, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            VX2PLP97(V, X, &P, &nRange);
        }
        else
        {
            VX2PLP67(V, X, &P, &nRange);
        }
    }

    void VX2HLP(double V, double X, double &H, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            VX2HLP97(V, X, &H, &nRange);
        }
        else
        {
            VX2HLP67(V, X, &H, &nRange);
        }
    }

    void VX2SLP(double V, double X, double &S, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            VX2SLP97(V, X, &S, &nRange);
        }
        else
        {
            VX2SLP67(V, X, &S, &nRange);
        }
    }

    void VXLP(double &P, double &T, double &H, double &S, 
        double V, double X, int &nRange)
    {
        if (true == g_bBLIF97)
        {
            VXLP97(&P, &T, &H, &S, V, X, &nRange);
        }
        else
        {
            VXLP67(&P, &T, &H, &S, V, X, &nRange);
        }
    }

}
