#ifndef __WASPCN_H__
#define __WASPCN_H__

#include <iostream>

#ifdef WIN32
#ifndef IMPORT_TYPE
#define IMPORT_TYPE extern "C" __declspec(dllexport)
#endif//IMPORT_TYPE
#else
#ifndef IMPORT_TYPE
#define IMPORT_TYPE extern "C"
#endif//IMPORT_TYPE
#endif

// 变量说明：P 压力，T 温度，H 比焓，S 比熵，V 比容，X 干度

namespace waspcn
{
    // 功能描述：设定将要使用的标准
    IMPORT_TYPE void SETSTD_WASP(int nStdID);
    // 功能描述：获知当前使用的标准
    IMPORT_TYPE void GETSTD_WASP(int &nStdID);

    // 功能描述：已知压力(MPa)，求对应饱和温度(℃)
    IMPORT_TYPE void P2T(double P, double &T, int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和水比焓(kJ/kg)
    IMPORT_TYPE void P2HL(double P, double &H, int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和汽比焓(kJ/kg)
    IMPORT_TYPE void P2HG(double P, double &H, int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和水比熵(kJ/(kg.℃))
    IMPORT_TYPE void P2SL(double P, double &S , int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和汽比熵(kJ/(kg.℃))
    IMPORT_TYPE void P2SG(double P, double &S, int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和水比容(m^3/kg)
    IMPORT_TYPE void P2VL(double P, double &V, int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和汽比容(m^3/kg)
    IMPORT_TYPE void P2VG(double P, double &V , int &nRange);
    IMPORT_TYPE void P2L(double P, 
        double &T,double &H, double &S, double &V, double &X, int &nRange);
    IMPORT_TYPE void P2G(double P, 
        double &T,double &H, double &S, double &V, double &X, int &nRange);

    // 功能描述：已知压力(MPa)，求对应饱和水定压比热(kJ/(kg.℃))
    IMPORT_TYPE void P2CPL(double P ,double &CP, int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和汽定压比热(kJ/(kg.℃))
    IMPORT_TYPE void P2CPG(double P, double &CP, int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和水定容比热(kJ/(kg.℃))
    IMPORT_TYPE void P2CVL(double P, double &CV, int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和汽定容比热(kJ/(kg.℃))
    IMPORT_TYPE void P2CVG(double P, double &CV, int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和水内能(kJ/kg)
    IMPORT_TYPE void P2EL(double P, double &E, int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和汽内能(kJ/kg)
    IMPORT_TYPE void P2EG(double P, double &E, int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和水音速(m/s)
    IMPORT_TYPE void P2SSPL(double P, double &SSP, int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和汽音速(m/s)
    IMPORT_TYPE void P2SSPG(double P, double &SSP, int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和水定熵指数
    IMPORT_TYPE void P2KSL(double P, double &KS , int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和汽定熵指数
    IMPORT_TYPE void P2KSG(double P, double &KS, int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和水动力粘度(Pa.s)
    IMPORT_TYPE void P2ETAL(double P,double &ETA, int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和汽动力粘度(Pa.s)
    IMPORT_TYPE void P2ETAG(double P, double &ETA, int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和水运动粘度(m^2/s)
    IMPORT_TYPE void P2UL(double P, double &U, int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和汽运动粘度(m^2/s)
    IMPORT_TYPE void P2UG(double P, double &U,int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和水导热系数(W/(m.℃))
    IMPORT_TYPE void P2RAMDL(double P, double &RAMD, int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和汽导热系数(W/(m.℃))
    IMPORT_TYPE void P2RAMDG(double P, double &RAMD, int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和水普朗特数
    IMPORT_TYPE void P2PRNL(double P, double &PRN, int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和汽普朗特数
    IMPORT_TYPE void P2PRNG(double P, double &PRN, int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和水介电常数
    IMPORT_TYPE void P2EPSL(double P, double &EPS, int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和汽介电常数
    IMPORT_TYPE void P2EPSG(double P, double &EPS, int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和水折射率
    IMPORT_TYPE void P2NL(double P, double LAMD, double &N, int &nRange);
    // 功能描述：已知压力(MPa)，求对应饱和汽折射率
    IMPORT_TYPE void P2NG(double P, double LAMD, double &N, int &nRange);

    // 功能描述：已知压力(MPa)和温度(℃)，求比焓(kJ/kg)
    IMPORT_TYPE void PT2H(double P, double T, double &H, int &nRange);
    // 功能描述：已知压力(MPa)和温度(℃)，求比熵(kJ/(kg.℃))
    IMPORT_TYPE void PT2S(double P, double T, double &S, int &nRange);
    // 功能描述：已知压力(MPa)和温度(℃)，求比容(m^3/kg)
    IMPORT_TYPE void PT2V(double P, double T, double &V, int &nRange);
    // 功能描述：已知压力(MPa)和温度(℃)，求干度(100%)
    IMPORT_TYPE void PT2X(double P, double T, double &X, int &nRange);
    IMPORT_TYPE void PT(double P, double T, 
        double &H, double &S, double &V, double &X, int &nRange);
    IMPORT_TYPE void PT2MV(double P, double T, 
        double &H, double &S, double &V, 
        double &E, double &CP, double &CV, double &SSP, int &nRange);

    // 功能描述：已知压力(MPa)和温度(℃)，求定压比热(kJ/(kg.℃))
    IMPORT_TYPE void PT2CP(double P, double T, double &CP, int &nRange);
    // 功能描述：已知压力(MPa)和温度(℃)，求定容比热(kJ/(kg.℃))
    IMPORT_TYPE void PT2CV(double P, double T, double &CV, int &nRange);
    // 功能描述：已知压力(MPa)和温度(℃)，求内能(kJ/kg)
    IMPORT_TYPE void PT2E(double P, double T, double &E, int &nRange);
    // 功能描述：已知压力(MPa)和温度(℃)，求音速(m/s)
    IMPORT_TYPE void PT2SSP(double P, double T, double &SSP, int &nRange);
    // 功能描述：已知压力(MPa)和温度(℃)，求定熵指数
    IMPORT_TYPE void PT2KS(double P, double T, double &KS, int &nRange);
    // 功能描述：已知压力(MPa)和温度(℃)，求动力粘度(Pa.s)
    IMPORT_TYPE void PT2ETA(double P, double T, double &ETA, int &nRange);
    // 功能描述：已知压力(MPa)和温度(℃)，求运动粘度(m^2/s)
    IMPORT_TYPE void PT2U(double P, double T, double &U, int &nRange);
    // 功能描述：已知压力(MPa)和温度(℃)，求热传导系数 (W/(m.℃))
    IMPORT_TYPE void PT2RAMD(double P, double T, double &RAMD, int &nRange);
    // 功能描述：已知压力(MPa)和温度(℃)，求普朗特数
    IMPORT_TYPE void PT2PRN(double P, double T, double &PRN, int &nRange);
    // 功能描述：已知压力(MPa)和温度(℃)，求介电常数
    IMPORT_TYPE void PT2EPS(double P, double T, double &EPS, int &nRange);
    // 功能描述：已知压力(MPa)和温度(℃)，求折射率
    IMPORT_TYPE void PT2N(double P, double T, double LAMD, double &N, int &nRange);

    IMPORT_TYPE void PT2HMV(double P, double T, double &H);
    IMPORT_TYPE void PT2VMV(double P, double T, double &V);
    IMPORT_TYPE void PT2SMV(double P, double T, double &S);
    IMPORT_TYPE void PT2EMV(double P, double T, double &E);
    IMPORT_TYPE void PT2CPMV(double P, double T, double &CP);
    IMPORT_TYPE void PT2CVMV(double P, double T, double &CV);
    IMPORT_TYPE void PT2SSPMV(double P, double T, double &SSP);

    // 功能描述：已知压力(MPa)和比焓(kJ/kg)，求温度(℃)
    IMPORT_TYPE void PH2T(double P, double H, double &T, int &nRange);
    // 功能描述：已知压力(MPa)和比焓(kJ/kg)，求比熵(kJ/(kg.℃))
    IMPORT_TYPE void PH2S(double P, double H, double &S, int &nRange);
    // 功能描述：已知压力(MPa)和比焓(kJ/kg)，求比容(m^3/kg)
    IMPORT_TYPE void PH2V(double P, double H, double &V, int &nRange);
    // 功能描述：已知压力(MPa)和比焓(kJ/kg)，求干度(100%)
    IMPORT_TYPE void PH2X(double P, double H, double &X, int &nRange);
    IMPORT_TYPE void PH2SSP(double P, double H, double &SSP, int &nRange);
    IMPORT_TYPE void PH2CP(double P, double H, double &CP, int &nRange);
    IMPORT_TYPE void PH2CV(double P, double H, double &CV, int &nRange);
    IMPORT_TYPE void PH2E(double P, double H, double &E, int &nRange);
    IMPORT_TYPE void PH2KS(double P, double H, double &KS, int &nRange);
    IMPORT_TYPE void PH2ETA(double P, double H, double &ETA, int &nRange);
    IMPORT_TYPE void PH2U(double P, double H, double &U, int &nRange);
    IMPORT_TYPE void PH2RAMD(double P, double H, double &RAMD, int &nRange);
    IMPORT_TYPE void PH2PRN(double P, double H, double &PRN, int &nRange);
    IMPORT_TYPE void PH2EPS(double P, double H, double &EPS, int &nRange);
    IMPORT_TYPE void PH2N(double P, double H, double LAMD, double &N, int &nRange);
    IMPORT_TYPE void PH(double P, double &T, 
        double H, double & S, double &V, double &X,int & nRange);

    // 功能描述：已知压力(MPa)和比熵(kJ/(kg.℃))，求温度(℃)
    IMPORT_TYPE void PS2T(double P, double S, double &T, int &nRange);
    // 功能描述：已知压力(MPa)和比熵(kJ/(kg.℃))，求比焓(kJ/kg)
    IMPORT_TYPE void PS2H(double P, double S, double &H, int &nRange);
    // 功能描述：已知压力(MPa)和比熵(kJ/(kg.℃))，求比容(m^3/kg)
    IMPORT_TYPE void PS2V(double P, double S, double &V, int &nRange);
    // 功能描述：已知压力(MPa)和比熵(kJ/(kg.℃))，求干度(100%)
    IMPORT_TYPE void PS2X(double P, double S, double &X, int &nRange);
    IMPORT_TYPE void PS(double P, double &T, double &H, 
        double S, double &V, double &X, int &nRange);

    // 功能描述：已知压力(MPa)和比容(m^3/kg)，求温度(℃)
    IMPORT_TYPE void PV2T(double P, double V, double &T, int &nRange);
    // 功能描述：已知压力(MPa)和比容(m^3/kg)，求比焓(kJ/kg)
    IMPORT_TYPE void PV2H(double P, double V, double &H, int &nRange);
    // 功能描述：已知压力(MPa)和比容(m^3/kg)，求比容(m^3/kg)
    IMPORT_TYPE void PV2S(double P, double V, double &S, int &nRange);
    // 功能描述：已知压力(MPa)和比容(m^3/kg)，求干度(100%)
    IMPORT_TYPE void PV2X(double P, double V, double &X, int &nRange);
    IMPORT_TYPE void PV(double P, double &T, double &H, double &S, 
        double V, double &X, int &nRange);

    // 功能描述：已知压力(MPa)和干度(100%)，求温度(℃)
    IMPORT_TYPE void PX2T(double P, double X, double &T, int &nRange);
    // 功能描述：已知压力(MPa)和干度(100%)，求比焓(kJ/kg)
    IMPORT_TYPE void PX2H(double P, double X, double &H, int &nRange);
    // 功能描述：已知压力(MPa)和干度(100%)，求比熵(kJ/(kg.℃))
    IMPORT_TYPE void PX2S(double P, double X, double &S, int &nRange);
    // 功能描述：已知压力(MPa)和干度(100%)，求比容(m^3/kg)
    IMPORT_TYPE void PX2V(double P, double X, double &V, int &nRange);
    IMPORT_TYPE void PX(double P, double &T, double &H, double &S, double &V, 
        double X, int &nRange);

    // 功能描述：已知温度(℃)，求饱和压力(MPa)？
    IMPORT_TYPE void T2P(double T, double &P, int &nRange);
    // 功能描述：已知温度(℃)，求饱和水比焓(kJ/kg)
    IMPORT_TYPE void T2HL(double T, double &H, int &nRange);
    // 功能描述：已知温度(℃)，求饱和汽比焓(kJ/kg)
    IMPORT_TYPE void T2HG(double T, double &H, int &nRange);
    // 功能描述：已知温度(℃)，求饱和水比熵(kJ/(kg.℃))
    IMPORT_TYPE void T2SL(double T, double &S, int &nRange);
    // 功能描述：已知温度(℃)，求饱和汽比熵(kJ/(kg.℃))
    IMPORT_TYPE void T2SG(double T, double &S, int &nRange);
    // 功能描述：已知温度(℃)，求饱和水比容(m^3/kg)
    IMPORT_TYPE void T2VL(double T, double &V, int &nRange);
    // 功能描述：已知温度(℃)，求饱和汽比容(m^3/kg)
    IMPORT_TYPE void T2VG(double T, double &V, int &nRange);
    IMPORT_TYPE void T2L(double &P, 
        double T, double &H, double &S, double &V, double &X, int &nRange);
    IMPORT_TYPE void T2G(double &P, 
        double T, double &H, double &S, double &V, double &X, int &nRange);

    // 功能描述：已知温度(℃)，求饱和水定压比热(kJ/(kg.℃))
    IMPORT_TYPE void T2CPL(double T, double &CP, int &nRange);
    // 功能描述：已知温度(℃)，求饱和汽定压比热(kJ/(kg.℃))
    IMPORT_TYPE void T2CPG(double T, double &CP, int &nRange);
    // 功能描述：已知温度(℃)，求饱和水定容比热(kJ/(kg.℃))
    IMPORT_TYPE void T2CVL(double T, double &CV, int &nRange);
    // 功能描述：已知温度(℃)，求饱和汽定容比热(kJ/(kg.℃))
    IMPORT_TYPE void T2CVG(double T, double &CV, int &nRange);
    // 功能描述：已知温度(℃)，求饱和水内能(kJ/kg)
    IMPORT_TYPE void T2EL(double T, double &E, int &nRange);
    // 功能描述：已知温度(℃)，求饱和汽内能(kJ/kg)
    IMPORT_TYPE void T2EG(double T, double &E, int &nRange);
    // 功能描述：已知温度(℃)，求饱和水音速(m/s)
    IMPORT_TYPE void T2SSPL(double T, double &SSP, int &nRange);
    // 功能描述：已知温度(℃)，求饱和汽音速(m/s)
    IMPORT_TYPE void T2SSPG(double T, double &SSP, int &nRange);
    // 功能描述：已知温度(℃)，求饱和水定熵指数
    IMPORT_TYPE void T2KSL(double T, double &KS, int &nRange);
    // 功能描述：已知温度(℃)，求饱和汽定熵指数
    IMPORT_TYPE void T2KSG(double T, double &KS, int &nRange);
    // 功能描述：已知温度(℃)，求饱和水动力粘度(Pa.s)
    IMPORT_TYPE void T2ETAL(double T, double &ETA, int &nRange);
    // 功能描述：已知温度(℃)，求饱和汽动力粘度(Pa.s)
    IMPORT_TYPE void T2ETAG(double T, double &ETA, int &nRange);
    // 功能描述：已知温度(℃)，求饱和水运动粘度(m^2/s)
    IMPORT_TYPE void T2UL(double T, double &U, int &nRange);
    // 功能描述：已知温度(℃)，求饱和汽运动粘度(m^2/s)
    IMPORT_TYPE void T2UG(double T, double &U, int &nRange);
    // 功能描述：已知温度(℃)，求饱和水导热系数(W/(m.℃))
    IMPORT_TYPE void T2RAMDL(double T, double &RAMD, int &nRange);
    // 功能描述：已知温度(℃)，求饱和汽导热系数(W/(m.℃))
    IMPORT_TYPE void T2RAMDG(double T, double &RAMD, int &nRange);
    // 功能描述：已知温度(℃)，求饱和水普朗特数
    IMPORT_TYPE void T2PRNL(double T, double &PRN, int &nRange);
    // 功能描述：已知温度(℃)，求饱和汽普朗特数
    IMPORT_TYPE void T2PRNG(double T, double &PRN, int &nRange);
    // 功能描述：已知温度(℃)，求饱和水介电常数
    IMPORT_TYPE void T2EPSL(double T, double &EPS, int &nRange);
    // 功能描述：已知温度(℃)，求饱和汽介电常数
    IMPORT_TYPE void T2EPSG(double T, double &EPS, int &nRange);
    // 功能描述：已知温度(℃)，求饱和水折射率
    IMPORT_TYPE void T2NL(double T, double LAMD, double &N, int &nRange);
    // 功能描述：已知温度(℃)，求饱和汽折射率
    IMPORT_TYPE void T2NG(double T, double LAMD, double &N, int &nRange);
    // 功能描述：已知温度(℃)，求饱和水表面张力(N/m)
    IMPORT_TYPE void T2SURFT(double T, double &SURFT, int &nRange);

    // 功能描述：已知温度(℃)和比焓(kJ/kg)，求压力(MPa)(缺省为低压的一个值)
    IMPORT_TYPE void TH2P(double T, double H, double &P, int &nRange);
    // 功能描述：已知温度(℃)和比焓(kJ/kg)，求压力(MPa)(低压的一个值)
    IMPORT_TYPE void TH2PLP(double T, double H, double &P, int &nRange);
    // 功能描述：已知温度(℃)和比焓(kJ/kg)，求压力(MPa)(高压的一个值)
    IMPORT_TYPE void TH2PHP(double T, double H, double &P, int &nRange);
    // 功能描述：已知温度(℃)和比焓(kJ/kg)，求比熵(kJ/(kg.℃))(缺省为低压的一个值)
    IMPORT_TYPE void TH2S(double T, double H, double &S, int &nRange);
    // 功能描述：已知温度(℃)和比焓(kJ/kg)，求比熵(kJ/(kg.℃))(低压的一个值)
    IMPORT_TYPE void TH2SLP(double T, double H, double &S, int &nRange);
    // 功能描述：已知温度(℃)和比焓(kJ/kg)，求比熵(kJ/(kg.℃))(高压的一个值)
    IMPORT_TYPE void TH2SHP(double T, double H, double &S, int &nRange);
    // 功能描述：已知温度(℃)和比焓(kJ/kg)，求比容(m^3/kg)(缺省为低压的一个值)
    IMPORT_TYPE void TH2V(double T, double H, double &V, int &nRange);
    // 功能描述：已知温度(℃)和比焓(kJ/kg)，求比容(m^3/kg)(低压的一个值)
    IMPORT_TYPE void TH2VLP(double T, double H,double &V,int &nRange);
    // 功能描述：已知温度(℃)和比焓(kJ/kg)，求比容(m^3/kg)(高压的一个值)
    IMPORT_TYPE void TH2VHP(double T, double H, double &V, int &nRange);
    // 功能描述：已知温度(℃)和比焓(kJ/kg)，求干度(100%)
    IMPORT_TYPE void TH2X(double T, double H, double &X, int &nRange);
    IMPORT_TYPE void TH2XLP(double T, double H, double &X, int &nRange);
    IMPORT_TYPE void TH2XHP(double T, double H, double &X, int &nRange);
    IMPORT_TYPE void TH(double &P, 
        double T, double H, double &S, double &V, double &X, int &nRange);
    IMPORT_TYPE void THLP(double &P, 
        double T, double H, double &S, double &V, double &X, int &nRange);
    IMPORT_TYPE void THHP(double &P, 
        double T, double H, double &S, double &V, double &X, int &nRange);

    // 功能描述：已知温度(℃)和比熵(kJ/(kg.℃))，求压力(MPa)(高压的一个值)
    IMPORT_TYPE void TS2PHP(double T, double S, double &P, int &nRange);
    // 功能描述：已知温度(℃)和比熵(kJ/(kg.℃))，求压力(MPa)(低压的一个值)
    IMPORT_TYPE void TS2PLP(double T, double S, double &P, int &nRange);
    // 功能描述：已知温度(℃)和比熵(kJ/(kg.℃))，求压力(MPa)(缺省为低压的一个值)
    IMPORT_TYPE void TS2P(double T, double S, double &P, int &nRange);
    // 功能描述：已知温度(℃)和比熵(kJ/(kg.℃))，求比焓(kJ/kg)(高压的一个值)
    IMPORT_TYPE void TS2HHP(double T, double S, double &H, int &nRange);
    // 功能描述：已知温度(℃)和比熵(kJ/(kg.℃))，求比焓(kJ/kg)(低压的一个值)
    IMPORT_TYPE void TS2HLP(double T, double S, double &H, int &nRange);
    // 功能描述：已知温度(℃)和比熵(kJ/(kg.℃))，求比焓(kJ/kg)(缺省为低压的一个值)
    IMPORT_TYPE void TS2H(double T, double S, double &H, int &nRange);
    // 功能描述：已知温度(℃)和比熵(kJ/(kg.℃))，求比容(m^3/kg)(高压的一个值)
    IMPORT_TYPE void TS2VHP(double T, double S, double &V, int &nRange);
    // 功能描述：已知温度(℃)和比熵(kJ/(kg.℃))，求比容(m^3/kg)(低压的一个值)
    IMPORT_TYPE void TS2VLP(double T, double S, double &V, int &nRange);
    // 功能描述：已知温度(℃)和比熵(kJ/(kg.℃))，求比容(m^3/kg)(缺省为低压的一个值)
    IMPORT_TYPE void TS2V(double T, double S, double &V, int &nRange);
    // 功能描述：已知温度(℃)和比熵(kJ/(kg.℃))，求干度(100%)
    IMPORT_TYPE void TS2X(double T, double S, double &X, int &nRange);
    IMPORT_TYPE void TSHP(double &P, 
        double T, double &H, 
        double S, double &V, double &X, int &nRange);
    IMPORT_TYPE void TSLP(double &P, 
        double T, double &H, 
        double S, double &V, double &X, int &nRange);
    IMPORT_TYPE void TS(double &P, 
        double T, double &H, 
        double S, double &V, double &X, int &nRange);

    // 功能描述：已知温度(℃)和比容(m^3/kg)，求压力(MPa)
    IMPORT_TYPE void TV2P(double T, double V, double &P, int &nRange);
    // 功能描述：已知温度(℃)和比容(m^3/kg)，求比焓(kJ/kg)
    IMPORT_TYPE void TV2H(double T, double V, double &H, int &nRange);
    // 功能描述：已知温度(℃)和比容(m^3/kg)，求比熵(kJ/(kg.℃))
    IMPORT_TYPE void TV2S(double T, double V, double &S, int &nRange);
    // 功能描述：已知温度(℃)和比容(m^3/kg)，求干度(100%)
    IMPORT_TYPE void TV2X(double T, double V, double &X, int &nRange);
    IMPORT_TYPE void TV(double &P, 
        double T, double &H, double &S, 
        double V, double &X, int &nRange);

    // 功能描述：已知温度(℃)和干度(100%)，求压力(MPa)
    IMPORT_TYPE void TX2P(double T, double X, double &P, int &nRange);
    // 功能描述：已知温度(℃)和干度(100%)，求比焓(kJ/kg)
    IMPORT_TYPE void TX2H(double T, double X, double &H, int &nRange);
    // 功能描述：已知温度(℃)和干度(100%)，求比熵(kJ/(kg.℃))
    IMPORT_TYPE void TX2S(double T, double X, double &S, int &nRange);
    // 功能描述：已知温度(℃)和干度(100%)，求比容(m^3/kg)
    IMPORT_TYPE void TX2V(double T, double X, double &V, int &nRange);
    IMPORT_TYPE void TX(double &P, 
        double T, double &H, double &S, double &V, 
        double X, int &nRange);

    IMPORT_TYPE void H2TL(double H, double &T, int &nRange);
    // 功能描述：已知比焓(kJ/kg)和比熵(kJ/(kg.℃))，求压力(MPa)
    IMPORT_TYPE void HS2P(double H, double S, double &P, int &nRange);
    // 功能描述：已知比焓(kJ/kg)和比熵(kJ/(kg.℃))，求温度(℃)
    IMPORT_TYPE void HS2T(double H, double S, double &T, int &nRange);
    // 功能描述：已知比焓(kJ/kg)和比熵(kJ/(kg.℃))，求比容(m^3/kg)
    IMPORT_TYPE void HS2V(double H, double S, double &V, int &nRange);
    // 功能描述：已知比焓(kJ/kg)和比熵(kJ/(kg.℃))，求干度(100%)
    IMPORT_TYPE void HS2X(double H, double S, double &X, int &nRange);
    IMPORT_TYPE void HS(double &P, double &T , 
        double H, double S, double &V, double &X, int &nRange);

    // 功能描述：已知比焓(kJ/kg)和比容(m^3/kg)，求压力(MPa)
    IMPORT_TYPE void HV2P(double H, double V, double &P, int & nRange);
    // 功能描述：已知比焓(kJ/kg)和比容(m^3/kg)，求温度(℃)
    IMPORT_TYPE void HV2T(double H, double V, double &T, int & nRange);
    // 功能描述：已知比焓(kJ/kg)和比容(m^3/kg)，求比熵(kJ/(kg.℃))
    IMPORT_TYPE void HV2S(double H, double V, double &S, int & nRange);
    // 功能描述：已知比焓(kJ/kg)和比容(m^3/kg)，求干度(100%)
    IMPORT_TYPE void HV2X(double H, double V, double &X, int & nRange);
    IMPORT_TYPE void HV(double &P, double &T, 
        double H, double &S, double V, double &X, int & nRange);

    // 功能描述：已知比焓(kJ/kg)和干度(100%)，求压力(MPa)(缺省是低压的一个值)
    IMPORT_TYPE void HX2P(double H, double X, double &P, int &nRange);
    // 功能描述：已知比焓(kJ/kg)和干度(100%)，求压力(MPa)(低压的一个值)
    IMPORT_TYPE void HX2PLP(double H, double X, double &P, int &nRange);
    // 功能描述：已知比焓(kJ/kg)和干度(100%)，求压力(MPa)(高压的一个值)
    IMPORT_TYPE void HX2PHP(double H, double X, double &P, int &nRange);
    // 功能描述：已知比焓(kJ/kg)和干度(100%)，求温度(℃)(缺省是低压的一个值)
    IMPORT_TYPE void HX2T(double H, double X, double &T, int &nRange);
    // 功能描述：已知比焓(kJ/kg)和干度(100%)，求温度(℃)(低压的一个值)
    IMPORT_TYPE void HX2TLP(double H, double X, double &T, int &nRange);
    // 功能描述：已知比焓(kJ/kg)和干度(100%)，求温度(℃)(高压的一个值)
    IMPORT_TYPE void HX2THP(double H, double X, double &T, int &nRange);
    // 功能描述：已知比焓(kJ/kg)和干度(100%)，求比熵(kJ/(kg.℃))(缺省是低压的一个值)
    IMPORT_TYPE void HX2S(double H, double X, double &S, int &nRange);
    // 功能描述：已知比焓(kJ/kg)和干度(100%)，求比熵(kJ/(kg.℃))(低压的一个值)
    IMPORT_TYPE void HX2SLP(double H, double X, double &S, int &nRange);
    // 功能描述：已知比焓(kJ/kg)和干度(100%)，求比熵(kJ/(kg.℃))(高压的一个值)
    IMPORT_TYPE void HX2SHP(double H, double X, double &S, int &nRange);
    // 功能描述：已知比焓(kJ/kg)和干度(100%)，求比容(m^3/kg)(缺省是低压的一个值)
    IMPORT_TYPE void HX2V(double H, double X, double &V, int &nRange);
    // 功能描述：已知比焓(kJ/kg)和干度(100%)，求比容(m^3/kg)(低压的一个值)
    IMPORT_TYPE void HX2VLP(double H, double X, double &V, int &nRange);
    // 功能描述：已知比焓(kJ/kg)和干度(100%)，求比容(m^3/kg)(高压的一个值)
    IMPORT_TYPE void HX2VHP(double H, double X, double &V, int &nRange);
    IMPORT_TYPE void HX(double &P, double &T, 
        double H, double &S, double &V, 
        double X, int &nRange);
    IMPORT_TYPE void HXLP(double &P, double &T, 
        double H, double &S, double &V, 
        double X, int &nRange);
    IMPORT_TYPE void HXHP(double &P, double &T, 
        double H, double &S, double &V, 
        double X, int &nRange);

    IMPORT_TYPE void S2TG(double S, double &T, int &nRange);
    // 功能描述：已知比熵(kJ/(kg.℃))和比容(m^3/kg)，求压力(MPa)
    IMPORT_TYPE void SV2P(double S, double V, double &P, int &nRange);
    // 功能描述：已知比熵(kJ/(kg.℃))和比容(m^3/kg)，求温度(℃)
    IMPORT_TYPE void SV2T(double S, double V, double &T, int &nRange);
    // 功能描述：已知比熵(kJ/(kg.℃))和比容(m^3/kg)，求比焓(kJ/kg)
    IMPORT_TYPE void SV2H(double S, double V, double &H, int &nRange);
    // 功能描述：已知比熵(kJ/(kg.℃))和比容(m^3/kg)，求干度(100%)
    IMPORT_TYPE void SV2X(double S, double V, double &X, int &nRange);
    IMPORT_TYPE void SV(double &P, double &T, double &H, 
        double S, double V, double &X, int &nRange);

    // 功能描述：已知比熵(kJ/(kg.℃))和干度(100%)，求压力(MPa)(缺省是低压的一个值)
    IMPORT_TYPE void SX2P(double S, double X, double &P, int &nRange);
    // 功能描述：已知比熵(kJ/(kg.℃))和干度(100%)，求压力(MPa)(低压的一个值)
    IMPORT_TYPE void SX2PLP(double S, double X, double &P, int &nRange);
    // 功能描述：已知比熵(kJ/(kg.℃))和干度(100%)，求压力(MPa)(中压的一个值)
    IMPORT_TYPE void SX2PMP(double S, double X, double &P, int &nRange);
    // 功能描述：已知比熵(kJ/(kg.℃))和干度(100%)，求压力(MPa)(高压的一个值)
    IMPORT_TYPE void SX2PHP(double S, double X, double &P, int &nRange);
    // 功能描述：已知比熵(kJ/(kg.℃))和干度(100%)，求温度(℃)(低压的一个值)
    IMPORT_TYPE void SX2TLP(double S, double X, double &T, int &nRange);
    // 功能描述：已知比熵(kJ/(kg.℃))和干度(100%)，求温度(℃)(中压的一个值)
    IMPORT_TYPE void SX2TMP(double S, double X, double &T, int &nRange);
    // 功能描述：已知比熵(kJ/(kg.℃))和干度(100%)，求温度(℃)(高压的一个值)
    IMPORT_TYPE void SX2THP(double S, double X, double &T, int &nRange);
    // 功能描述：已知比熵(kJ/(kg.℃))和干度(100%)，求温度(℃)(缺省是低压的一个值)
    IMPORT_TYPE void SX2T(double S, double X, double &T, int &nRange);
    // 功能描述：已知比熵(kJ/(kg.℃))和干度(100%)，求比焓(kJ/kg)(缺省是低压的一个值)
    IMPORT_TYPE void SX2H(double S, double X, double &H, int &nRange);
    // 功能描述：已知比熵(kJ/(kg.℃))和干度(100%)，求比焓(kJ/kg)(低压的一个值)
    IMPORT_TYPE void SX2HLP(double S, double X, double &H, int &nRange);
    // 功能描述：已知比熵(kJ/(kg.℃))和干度(100%)，求比焓(kJ/kg)(中压的一个值)
    IMPORT_TYPE void SX2HMP(double S, double X, double &H, int &nRange);
    // 功能描述：已知比熵(kJ/(kg.℃))和干度(100%)，求比焓(kJ/kg)(高压的一个值)
    IMPORT_TYPE void SX2HHP(double S, double X, double &H, int &nRange);
    // 功能描述：已知比熵(kJ/(kg.℃))和干度(100%)，求比容(m^3/kg)(缺省是低压的一个值)
    IMPORT_TYPE void SX2V(double S, double X, double &V, int &nRange);
    // 功能描述：已知比熵(kJ/(kg.℃))和干度(100%)，求比容(m^3/kg)(低压的一个值)
    IMPORT_TYPE void SX2VLP(double S, double X, double &V, int &nRange);
    // 功能描述：已知比熵(kJ/(kg.℃))和干度(100%)，求比容(m^3/kg)(中压的一个值)
    IMPORT_TYPE void SX2VMP(double S, double X, double &V, int &nRange);
    // 功能描述：已知比熵(kJ/(kg.℃))和干度(100%)，求比容(m^3/kg)(高压的一个值)
    IMPORT_TYPE void SX2VHP(double S, double X, double &V, int &nRange);
    IMPORT_TYPE void SX(double &P, double &T, double &H, 
        double S, double &V, 
        double X, int &nRange);
    IMPORT_TYPE void SXLP(double &P, double &T, double &H, 
        double S, double &V, 
        double X, int &nRange);
    IMPORT_TYPE void SXMP(double &P, double &T, double &H, 
        double S, double &V, 
        double X, int &nRange);
    IMPORT_TYPE void SXHP(double &P, double &T, double &H, 
        double S, double &V, 
        double X, int &nRange);

    IMPORT_TYPE void V2TG(double V, double &T, int &nRange);
    // 功能描述：已知比容(m^3/kg)和干度(100%)，求压力(MPa)(缺省是低压的一个值)
    IMPORT_TYPE void VX2P(double V, double X, double &P, int &nRange);
    // 功能描述：已知比容(m^3/kg)和干度(100%)，求压力(MPa)(低压的一个值)
    IMPORT_TYPE void VX2PLP(double V, double X, double &P, int &nRange);
    // 功能描述：已知比容(m^3/kg)和干度(100%)，求压力(MPa)(低高压的一个值)
    IMPORT_TYPE void VX2PHP(double V, double X, double &P, int &nRange);
    // 功能描述：已知比容(m^3/kg)和干度(100%)，求温度(℃)(缺省是低压的一个值)
    IMPORT_TYPE void VX2T(double V, double X, double &T, int &nRange);
    // 功能描述：已知比容(m^3/kg)和干度(100%)，求温度(℃)(低压的一个值)
    IMPORT_TYPE void VX2TLP(double V, double X, double &T, int &nRange);
    // 功能描述：已知比容(m^3/kg)和干度(100%)，求温度(℃)(高压的一个值)
    IMPORT_TYPE void VX2THP(double V, double X, double &T, int &nRange);
    // 功能描述：已知比容(m^3/kg)和干度(100%)，求比焓(kJ/kg)(缺省是低压的一个值)
    IMPORT_TYPE void VX2H(double V, double X, double &H, int &nRange);
    // 功能描述：已知比容(m^3/kg)和干度(100%)，求比焓(kJ/kg)(低压的一个值)
    IMPORT_TYPE void VX2HLP(double V, double X, double &H, int &nRange);
    // 功能描述：已知比容(m^3/kg)和干度(100%)，求比焓(kJ/kg)(高压的一个值)
    IMPORT_TYPE void VX2HHP(double V, double X, double &H, int &nRange);
    // 功能描述：已知比容(m^3/kg)和干度(100%)，求比熵(kJ/(kg.℃))(缺省是低压的一个值)
    IMPORT_TYPE void VX2S(double V, double X, double &S, int &nRange);
    // 功能描述：已知比容(m^3/kg)和干度(100%)，求比熵(kJ/(kg.℃))(低压的一个值)
    IMPORT_TYPE void VX2SLP(double V, double X, double &S, int &nRange);
    // 功能描述：已知比容(m^3/kg)和干度(100%)，求比熵(kJ/(kg.℃))(高压的一个值)
    IMPORT_TYPE void VX2SHP(double V, double X, double &S, int &nRange);
    IMPORT_TYPE void VX(double &P, double &T, double &H, double &S, 
        double V, double X, int &nRange);
    IMPORT_TYPE void VXLP(double &P, double &T, double &H, double &S, 
        double V, double X, int &nRange);
    IMPORT_TYPE void VXHP(double &P, double &T, double &H, double &S, 
        double V, double X, int &nRange);
}

#endif//__WASPCN_H__
