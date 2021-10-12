#include "except.h"
#include "waspcn.h"
using namespace waspcn;

#include <math.h>
#include <vector>
#include <stdlib.h>
using namespace std;

typedef vector<double>    VDOUBLE;
typedef VDOUBLE::iterator VDOUBLEInt;
typedef double (*EXTFUNCTION)(VDOUBLE& t);

#define RANG                0

#ifdef __cplusplus
extern "C" {
#endif
    double pst(double ta)
    {
         double P;
         int nRange;
         int nType;
         GETSTD_WASP(nType);
         SETSTD_WASP(67);
         T2P(ta, P, nRange);
         SETSTD_WASP(nType);
         return P;
    };
    double tsp(double pa)
    {
        double T;
        int nRange;
        int nType;
        GETSTD_WASP(nType);
        SETSTD_WASP(67);
        P2T(pa/10, T, nRange);
        SETSTD_WASP(nType);
        return T;
    }
    void ptparam(double pa,double ta,double *ha,double *sa,double *va)
    {
        int nRange;
        int nType;
        GETSTD_WASP(nType);
        SETSTD_WASP(67);
        PT2H(pa/10, ta, *ha, nRange);
        PT2S(pa/10, ta, *sa, nRange);
        PT2V(pa/10, ta, *va, nRange);
        SETSTD_WASP(nType);
    }
    void waterparam(double pa,double ta,double *hf,double *sf,double *vf)
    {
        ptparam(pa, ta, hf, sf, vf);
    }
    void vaporparam(double pa,double ta,double *hg,double *sg,double *vg)
    {
        ptparam(pa, ta, hg, sg, vg);
    }
    void psparam(double pa,double sa,double *ta,double *ha,double *va)
    {
        int nRange;
        int nType;
        GETSTD_WASP(nType);
        SETSTD_WASP(67);
        PS2T(pa/10, sa, *ta, nRange);
        PS2H(pa/10, sa, *ha, nRange);
        PS2V(pa/10, sa, *va, nRange);
        SETSTD_WASP(nType);
    }
    void phparam(double pa,double ha,double *ta,double *sa,double *va)
    {
        int nRange;
        int nType;
        GETSTD_WASP(nType);
        SETSTD_WASP(67);
        PH2T(pa/10, ha, *ta, nRange);
        PH2S(pa/10, ha, *sa, nRange);
        PH2V(pa/10, ha, *va, nRange);
        SETSTD_WASP(nType);
    }
    void hsparam(double ha,double sa,double *pa,double *ta,double *va)
    {
        int nRange;
        int nType;
        GETSTD_WASP(nType);
        SETSTD_WASP(67);
        HS2P(ha, sa, *pa, nRange);
        HS2T(ha, sa, *ta, nRange);
        HS2V(ha, sa, *va, nRange);
        SETSTD_WASP(nType);
    }

#ifdef __cplusplus
}
#endif

//处理数学异常
//static int _matherr(exception *except );

//通过温度求压力
static double PST(VDOUBLE& t);
//通过压力求温度
static double TSP(VDOUBLE& t);

//平方函数
static double SQRT(VDOUBLE& t);
//绝对值函数
static double ABS(VDOUBLE& t);
//ln函数
static double LN(VDOUBLE& t);
//幂函数
static double POW(VDOUBLE& t);
//log10函数
static double LOG(VDOUBLE& t);
//指数函数
static double EXP(VDOUBLE& t);
//正弦
static double SIN(VDOUBLE& t);
//双曲正弦
static double SINH(VDOUBLE& t);
//反正弦
static double ASIN(VDOUBLE& t);
//余弦
static double COS(VDOUBLE& t);
//双曲余弦
static double COSH(VDOUBLE& t);
//反余弦
static double ACOS(VDOUBLE& t);
//正切
static double TAN(VDOUBLE& t);
//反正切
static double ATON(VDOUBLE& t);
//双曲正切
static double TANH(VDOUBLE& t);
//求阶乘
static double FACTORIAL(VDOUBLE& t);
//求最大值
static double MAX(VDOUBLE& t);
//求最小值
static double MIN(VDOUBLE& t);

//通过压力和温度求气体的焓
static double AHPT(VDOUBLE& t);
//通过压力和温度求气体的熵
static double ASPT(VDOUBLE& t);
//通过压力和温度求气体的比容
static double AVPT(VDOUBLE& t);

//通过压力和熵求气体的温度
static double ATPS(VDOUBLE& t);
//通过压力和熵求气体的焓
static double AHPS(VDOUBLE& t);
//通过压力和熵求气体的比容
static double AVPS(VDOUBLE& t);

//通过压力和焓求气体的温度
static double ATPH(VDOUBLE& t);
//通过压力和焓求气体的熵
static double ASPH(VDOUBLE& t);
//通过压力和焓求气体的比容
static double AVPH(VDOUBLE& t);

//通过熵和焓求气体的压力
static double APHS(VDOUBLE& t);
//通过熵和焓求气体的温度
static double ATHS(VDOUBLE& t);
//通过熵和焓求气体的比容
static double AVHS(VDOUBLE& t);

//通过温度和压力求水的焓
static double WHPT(VDOUBLE& t);
//通过温度和压力求水的熵
static double WSPT(VDOUBLE& t);
//通过温度和压力求水的比容
static double WVPT(VDOUBLE& t);

//通过温度和压力求气水的焓
static double GHPT(VDOUBLE& t);
//通过温度和压力求气水的熵
static double GSPT(VDOUBLE& t);
//通过温度和压力求气水的比容
static double GVPT(VDOUBLE& t);


//已知压力(MPa)，求对应饱和温度(℃)
static double F_P2T(VDOUBLE& t);
//已知压力(MPa)，求对应饱和水比焓(kJ/kg)
static double F_P2HL(VDOUBLE& t);
//已知压力(MPa)，求对应饱和汽比焓(kJ/kg)
static double F_P2HG(VDOUBLE& t);
//已知压力(MPa)，求对应饱和水比熵(kJ/(kg.℃))
static double F_P2SL(VDOUBLE& t);
//已知压力(MPa)，求对应饱和汽比熵(kJ/(kg.℃))
static double F_P2SG(VDOUBLE& t);
//已知压力(MPa)，求对应饱和水比容(m^3/kg)
static double F_P2VL(VDOUBLE& t);
//已知压力(MPa)，求对应饱和汽比容(m^3/kg)
static double F_P2VG(VDOUBLE& t);
//已知压力(MPa)，求对应饱和水定压比热(kJ/(kg.℃))
static double F_P2CPL(VDOUBLE& t);
//已知压力(MPa)，求对应饱和汽定压比热(kJ/(kg.℃))
static double F_P2CPG(VDOUBLE& t);
//已知压力(MPa)，求对应饱和水定容比热(kJ/(kg.℃))
static double F_P2CVL(VDOUBLE& t);
//已知压力(MPa)，求对应饱和汽定容比热(kJ/(kg.℃))
static double F_P2CVG(VDOUBLE& t);
//已知压力(MPa)，求对应饱和水内能(kJ/kg)
static double F_P2EL(VDOUBLE& t);
//已知压力(MPa)，求对应饱和汽内能(kJ/kg)
static double F_P2EG(VDOUBLE& t);
//已知压力(MPa)，求对应饱和水音速(m/s)
static double F_P2SSPL(VDOUBLE& t);
//已知压力(MPa)，求对应饱和汽音速(m/s)
static double F_P2SSPG(VDOUBLE& t);
//已知压力(MPa)，求对应饱和水定熵指数
static double F_P2KSL(VDOUBLE& t);
//已知压力(MPa)，求对应饱和汽定熵指数
static double F_P2KSG(VDOUBLE& t);
//已知压力(MPa)，求对应饱和水动力粘度(Pa.s)
static double F_P2ETAL(VDOUBLE& t);
//已知压力(MPa)，求对应饱和汽动力粘度(Pa.s)
static double F_P2ETAG(VDOUBLE& t);
//已知压力(MPa)，求对应饱和水运动粘度(m^2/s)
static double F_P2UL(VDOUBLE& t);
//已知压力(MPa)，求对应饱和汽运动粘度(m^2/s)
static double F_P2UG(VDOUBLE& t);
//已知压力(MPa)，求对应饱和水导热系数(W/(m.℃))
static double F_P2RAMDL(VDOUBLE& t);
//已知压力(MPa)，求对应饱和汽导热系数(W/(m.℃))
static double F_P2RAMDG(VDOUBLE& t);
//已知压力(MPa)，求对应饱和水普朗特数
static double F_P2PRNL(VDOUBLE& t);
//已知压力(MPa)，求对应饱和汽普朗特数
static double F_P2PRNG(VDOUBLE& t);
//已知压力(MPa)，求对应饱和水介电常数
static double F_P2EPSL(VDOUBLE& t);
//已知压力(MPa)，求对应饱和汽介电常数
static double F_P2EPSG(VDOUBLE& t);
//已知压力(MPa)，求对应饱和水折射率
static double F_P2NL(VDOUBLE& t);
//已知压力(MPa)，求对应饱和汽折射率
static double F_P2NG(VDOUBLE& t);

//已知压力(MPa)和温度(℃)，求比焓(kJ/kg)
static double F_PT2H(VDOUBLE& t);
//已知压力(MPa)和温度(℃)，求比熵(kJ/(kg.℃))
static double F_PT2S(VDOUBLE& t);
//已知压力(MPa)和温度(℃)，求比容(m^3/kg)
static double F_PT2V(VDOUBLE& t);
//已知压力(MPa)和温度(℃)，求干度(100%)
static double F_PT2X(VDOUBLE& t);
//已知压力(MPa)和温度(℃)，求定压比热(kJ/(kg.℃))
static double F_PT2CP(VDOUBLE& t);
//已知压力(MPa)和温度(℃)，求定容比热(kJ/(kg.℃))
static double F_PT2CV(VDOUBLE& te);
//已知压力(MPa)和温度(℃)，求内能(kJ/kg)
static double F_PT2E(VDOUBLE& t);
//已知压力(MPa)和温度(℃)，求音速(m/s)
static double F_PT2SSP(VDOUBLE& t);
//已知压力(MPa)和温度(℃)，求定熵指数
static double F_PT2KS(VDOUBLE& t);
//已知压力(MPa)和温度(℃)，求动力粘度(Pa.s)
static double F_PT2ETA(VDOUBLE& t);
//已知压力(MPa)和温度(℃)，求运动粘度(m^2/s)
static double F_PT2U(VDOUBLE& t);
//已知压力(MPa)和温度(℃)，求热传导系数 (W/(m.℃))
static double F_PT2RAMD(VDOUBLE& t);
//已知压力(MPa)和温度(℃)，求普朗特数
static double F_PT2PRN(VDOUBLE& t);
//已知压力(MPa)和温度(℃)，求介电常数
static double F_PT2EPS(VDOUBLE& t);
//已知压力(MPa)和温度(℃)，求折射率
static double F_PT2N(VDOUBLE& t);

//已知压力(MPa)和比焓(kJ/kg)，求温度(℃)
static double F_PH2T(VDOUBLE& t);
//已知压力(MPa)和比焓(kJ/kg)，求比熵(kJ/(kg.℃))
static double F_PH2S(VDOUBLE& t);
//已知压力(MPa)和比焓(kJ/kg)，求比容(m^3/kg)
static double F_PH2V(VDOUBLE& t);
//已知压力(MPa)和比焓(kJ/kg)，求干度(100%)
static double F_PH2X(VDOUBLE& t);

//已知压力(MPa)和比熵(kJ/(kg.℃))，求温度(℃)
static double F_PS2T(VDOUBLE& t);
//已知压力(MPa)和比熵(kJ/(kg.℃))，求比焓(kJ/kg)
static double F_PS2H(VDOUBLE& t);
//已知压力(MPa)和比熵(kJ/(kg.℃))，求比容(m^3/kg)
static double F_PS2V(VDOUBLE& t);
//已知压力(MPa)和比熵(kJ/(kg.℃))，求干度(100%)
static double F_PS2X(VDOUBLE& t);

//已知压力(MPa)和比容(m^3/kg)，求温度(℃)
static double F_PV2T(VDOUBLE& t);
//已知压力(MPa)和比容(m^3/kg)，求比焓(kJ/kg)
static double F_PV2H(VDOUBLE& t);
//已知压力(MPa)和比容(m^3/kg)，求比容(m^3/kg)
static double F_PV2S(VDOUBLE& t);
//已知压力(MPa)和比容(m^3/kg)，求干度(100%)
static double F_PV2X(VDOUBLE& t);

//已知压力(MPa)和干度(100%)，求温度(℃)
static double F_PX2T(VDOUBLE& t);
//已知压力(MPa)和干度(100%)，求比焓(kJ/kg)
static double F_PX2H(VDOUBLE& t);
//已知压力(MPa)和干度(100%)，求比熵(kJ/(kg.℃))
static double F_PX2S(VDOUBLE& t);
//已知压力(MPa)和干度(100%)，求比容(m^3/kg)
static double F_PX2V(VDOUBLE& t);

//已知温度(℃)，求饱和压力(MPa)？
static double F_T2P(VDOUBLE& t);
//已知温度(℃)，求饱和水比焓(kJ/kg)
static double F_T2HL(VDOUBLE& t);
//已知温度(℃)，求饱和汽比焓(kJ/kg)
static double F_T2HG(VDOUBLE& t);
//已知温度(℃)，求饱和水比熵(kJ/(kg.℃))
static double F_T2SL(VDOUBLE& t);
//已知温度(℃)，求饱和汽比熵(kJ/(kg.℃))
static double F_T2SG(VDOUBLE& t);
//已知温度(℃)，求饱和水比容(m^3/kg)
static double F_T2VL(VDOUBLE& t);
//已知温度(℃)，求饱和汽比容(m^3/kg)
static double F_T2VG(VDOUBLE& t);
//已知温度(℃)，求饱和水定压比热(kJ/(kg.℃))
static double F_T2CPL(VDOUBLE& t);
//已知温度(℃)，求饱和汽定压比热(kJ/(kg.℃))
static double F_T2CPG(VDOUBLE& t);
//已知温度(℃)，求饱和水定容比热(kJ/(kg.℃))
static double F_T2CVL(VDOUBLE& t);
//已知温度(℃)，求饱和汽定容比热(kJ/(kg.℃))
static double F_T2CVG(VDOUBLE& t);
//已知温度(℃)，求饱和水内能(kJ/kg)
static double F_T2EL(VDOUBLE& t);
//已知温度(℃)，求饱和汽内能(kJ/kg)
static double F_T2EG(VDOUBLE& t);
//已知温度(℃)，求饱和水音速(m/s)
static double F_T2SSPL(VDOUBLE& t);
//已知温度(℃)，求饱和汽音速(m/s)
static double F_T2SSPG(VDOUBLE& t);
//已知温度(℃)，求饱和水定熵指数
static double F_T2KSL(VDOUBLE& t);
//已知温度(℃)，求饱和汽定熵指数
static double F_T2KSG(VDOUBLE& t);
//已知温度(℃)，求饱和水动力粘度(Pa.s)
static double F_T2ETAL(VDOUBLE& t);
//已知温度(℃)，求饱和汽动力粘度(Pa.s)
static double F_T2ETAG(VDOUBLE& t);
//已知温度(℃)，求饱和水运动粘度(m^2/s)
static double F_T2UL(VDOUBLE& t);
//已知温度(℃)，求饱和汽运动粘度(m^2/s)
static double F_T2UG(VDOUBLE& t);
//已知温度(℃)，求饱和水导热系数(W/(m.℃))
static double F_T2RAMDL(VDOUBLE& t);
//已知温度(℃)，求饱和汽导热系数(W/(m.℃))
static double F_T2RAMDG(VDOUBLE& t);
//已知温度(℃)，求饱和水普朗特数
static double F_T2PRNL(VDOUBLE& t);
//已知温度(℃)，求饱和汽普朗特数
static double F_T2PRNG(VDOUBLE& t);
//已知温度(℃)，求饱和水介电常数
static double F_T2EPSL(VDOUBLE& t);
//已知温度(℃)，求饱和汽介电常数
static double F_T2EPSG(VDOUBLE& t);
//已知温度(℃)，求饱和水折射率
static double F_T2NL(VDOUBLE& t);
//已知温度(℃)，求饱和汽折射率
static double F_T2NG(VDOUBLE& t);
//已知温度(℃)，求饱和水表面张力(N/m)
static double F_T2SURFT(VDOUBLE& t);

//已知温度(℃)和比焓(kJ/kg)，求压力(MPa)(低压的一个值)
static double F_TH2PLP(VDOUBLE& t);
//已知温度(℃)和比焓(kJ/kg)，求比熵(kJ/(kg.℃))(低压的一个值)
static double F_TH2SLP(VDOUBLE& t);
//已知温度(℃)和比焓(kJ/kg)，求比容(m^3/kg)(低压的一个值)
static double F_TH2VLP(VDOUBLE& t);
//已知温度(℃)和比焓(kJ/kg)，求压力(MPa)(高压的一个值)
static double F_TH2PHP(VDOUBLE& t);
//已知温度(℃)和比焓(kJ/kg)，求比熵(kJ/(kg.℃))(高压的一个值)
static double F_TH2SHP(VDOUBLE& t);
//已知温度(℃)和比焓(kJ/kg)，求比容(m^3/kg)(高压的一个值)
static double F_TH2VHP(VDOUBLE& t);
//已知温度(℃)和比焓(kJ/kg)，求压力(MPa)(缺省为低压的一个值)
static double F_TH2P(VDOUBLE& t);
//已知温度(℃)和比焓(kJ/kg)，求比熵(kJ/(kg.℃))(缺省为低压的一个值)
static double F_TH2S(VDOUBLE& t);
//已知温度(℃)和比焓(kJ/kg)，求比容(m^3/kg)(缺省为低压的一个值)
static double F_TH2V(VDOUBLE& t);
//已知温度(℃)和比焓(kJ/kg)，求干度(100%)
static double F_TH2X(VDOUBLE& t);

//已知温度(℃)和比熵(kJ/(kg.℃))，求压力(MPa)(低压的一个值)
static double F_TS2PLP(VDOUBLE& t);
//已知温度(℃)和比熵(kJ/(kg.℃))，求比焓(kJ/kg)(低压的一个值)
static double F_TS2HLP(VDOUBLE& t);
//已知温度(℃)和比熵(kJ/(kg.℃))，求比容(m^3/kg)(低压的一个值)
static double F_TS2VLP(VDOUBLE& t);
//已知温度(℃)和比熵(kJ/(kg.℃))，求压力(MPa)(高压的一个值)
static double F_TS2PHP(VDOUBLE& t);
//已知温度(℃)和比熵(kJ/(kg.℃))，求比焓(kJ/kg)(高压的一个值)
static double F_TS2HHP(VDOUBLE& t);
//已知温度(℃)和比熵(kJ/(kg.℃))，求比容(m^3/kg)(高压的一个值)
static double F_TS2VHP(VDOUBLE& t);
//已知温度(℃)和比熵(kJ/(kg.℃))，求压力(MPa)(缺省为低压的一个值)
static double F_TS2P(VDOUBLE& t);
//已知温度(℃)和比熵(kJ/(kg.℃))，求比焓(kJ/kg)(缺省为低压的一个值)
static double F_TS2H(VDOUBLE& t);
//已知温度(℃)和比熵(kJ/(kg.℃))，求比容(m^3/kg)(缺省为低压的一个值)
static double F_TS2V(VDOUBLE& t);
//已知温度(℃)和比熵(kJ/(kg.℃))，求干度(100%)
static double F_TS2X(VDOUBLE& t);

//已知温度(℃)和比容(m^3/kg)，求压力(MPa)
static double F_TV2P(VDOUBLE& t);
//已知温度(℃)和比容(m^3/kg)，求比焓(kJ/kg)
static double F_TV2H(VDOUBLE& t);
//已知温度(℃)和比容(m^3/kg)，求比熵(kJ/(kg.℃))
static double F_TV2S(VDOUBLE& t);
//已知温度(℃)和比容(m^3/kg)，求干度(100%)
static double F_TV2X(VDOUBLE& t);

//已知温度(℃)和干度(100%)，求压力(MPa)
static double F_TX2P(VDOUBLE& t);
//已知温度(℃)和干度(100%)，求比焓(kJ/kg)
static double F_TX2H(VDOUBLE& t);
//已知温度(℃)和干度(100%)，求比熵(kJ/(kg.℃))
static double F_TX2S(VDOUBLE& t);
//已知温度(℃)和干度(100%)，求比容(m^3/kg)
static double F_TX2V(VDOUBLE& t);

//已知比焓(kJ/kg)和比熵(kJ/(kg.℃))，求压力(MPa)
static double F_HS2P(VDOUBLE& t);
//已知比焓(kJ/kg)和比熵(kJ/(kg.℃))，求温度(℃)
static double F_HS2T(VDOUBLE& t);
//已知比焓(kJ/kg)和比熵(kJ/(kg.℃))，求比容(m^3/kg)
static double F_HS2V(VDOUBLE& t);
//已知比焓(kJ/kg)和比熵(kJ/(kg.℃))，求干度(100%)
static double F_HS2X(VDOUBLE& t);

//已知比焓(kJ/kg)和比容(m^3/kg)，求压力(MPa)
static double F_HV2P(VDOUBLE& t);
//已知比焓(kJ/kg)和比容(m^3/kg)，求温度(℃)
static double F_HV2T(VDOUBLE& t);
//已知比焓(kJ/kg)和比容(m^3/kg)，求比熵(kJ/(kg.℃))
static double F_HV2S(VDOUBLE& t);
//已知比焓(kJ/kg)和比容(m^3/kg)，求干度(100%)
static double F_HV2X(VDOUBLE& t);

//已知比焓(kJ/kg)和干度(100%)，求压力(MPa)(低压的一个值)
static double F_HX2PLP(VDOUBLE& t);
//已知比焓(kJ/kg)和干度(100%)，求温度(℃)(低压的一个值)
static double F_HX2TLP(VDOUBLE& t);
//已知比焓(kJ/kg)和干度(100%)，求比熵(kJ/(kg.℃))(低压的一个值)
static double F_HX2SLP(VDOUBLE& t);
//已知比焓(kJ/kg)和干度(100%)，求比容(m^3/kg)(低压的一个值)
static double F_HX2VLP(VDOUBLE& t);
//已知比焓(kJ/kg)和干度(100%)，求压力(MPa)(高压的一个值)
static double F_HX2PHP(VDOUBLE& t);
//已知比焓(kJ/kg)和干度(100%)，求温度(℃)(高压的一个值)
static double F_HX2THP(VDOUBLE& t);
//已知比焓(kJ/kg)和干度(100%)，求比熵(kJ/(kg.℃))(高压的一个值)
static double F_HX2SHP(VDOUBLE& t);
//已知比焓(kJ/kg)和干度(100%)，求比容(m^3/kg)(高压的一个值)
static double F_HX2VHP(VDOUBLE& te);
//已知比焓(kJ/kg)和干度(100%)，求压力(MPa)(缺省是低压的一个值)
static double F_HX2P(VDOUBLE& t);
//已知比焓(kJ/kg)和干度(100%)，求温度(℃)(缺省是低压的一个值)
static double F_HX2T(VDOUBLE& t);
//已知比焓(kJ/kg)和干度(100%)，求比熵(kJ/(kg.℃))(缺省是低压的一个值)
static double F_HX2S(VDOUBLE& t);
//已知比焓(kJ/kg)和干度(100%)，求比容(m^3/kg)(缺省是低压的一个值)
static double F_HX2V(VDOUBLE& t);

//已知比熵(kJ/(kg.℃))和比容(m^3/kg)，求压力(MPa)
static double F_SV2P(VDOUBLE& t);
//已知比熵(kJ/(kg.℃))和比容(m^3/kg)，求温度(℃)
static double F_SV2T(VDOUBLE& t);
//已知比熵(kJ/(kg.℃))和比容(m^3/kg)，求比焓(kJ/kg)
static double F_SV2H(VDOUBLE& t);
//已知比熵(kJ/(kg.℃))和比容(m^3/kg)，求干度(100%)
static double F_SV2X(VDOUBLE& t);


//已知比熵(kJ/(kg.℃))和干度(100%)，求压力(MPa)(低压的一个值)
static double F_SX2PLP(VDOUBLE& te);
//已知比熵(kJ/(kg.℃))和干度(100%)，求压力(MPa)(中压的一个值)
static double F_SX2PMP(VDOUBLE& t);
//已知比熵(kJ/(kg.℃))和干度(100%)，求压力(MPa)(高压的一个值)
static double F_SX2PHP(VDOUBLE& t);
//已知比熵(kJ/(kg.℃))和干度(100%)，求压力(MPa)(缺省是低压的一个值)
static double F_SX2P(VDOUBLE& t);
//已知比熵(kJ/(kg.℃))和干度(100%)，求温度(℃)(低压的一个值)
static double F_SX2TLP(VDOUBLE& t);
//已知比熵(kJ/(kg.℃))和干度(100%)，求温度(℃)(中压的一个值)
static double F_SX2TMP(VDOUBLE& t);
//已知比熵(kJ/(kg.℃))和干度(100%)，求温度(℃)(高压的一个值)
static double F_SX2THP(VDOUBLE& t);
//已知比熵(kJ/(kg.℃))和干度(100%)，求温度(℃)(缺省是低压的一个值)
static double F_SX2T(VDOUBLE& t);
//已知比熵(kJ/(kg.℃))和干度(100%)，求比焓(kJ/kg)(低压的一个值)
static double F_SX2HLP(VDOUBLE& t);
//已知比熵(kJ/(kg.℃))和干度(100%)，求比焓(kJ/kg)(中压的一个值)
static double F_SX2HMP(VDOUBLE& t);
//已知比熵(kJ/(kg.℃))和干度(100%)，求比焓(kJ/kg)(高压的一个值)
static double F_SX2HHP(VDOUBLE& t);
//已知比熵(kJ/(kg.℃))和干度(100%)，求比焓(kJ/kg)(缺省是低压的一个值)
static double F_SX2H(VDOUBLE& t);
//已知比熵(kJ/(kg.℃))和干度(100%)，求比容(m^3/kg)(低压的一个值)
static double F_SX2VLP(VDOUBLE& t);
//已知比熵(kJ/(kg.℃))和干度(100%)，求比容(m^3/kg)(中压的一个值)
static double F_SX2VMP(VDOUBLE& t);
//已知比熵(kJ/(kg.℃))和干度(100%)，求比容(m^3/kg)(高压的一个值)
static double F_SX2VHP(VDOUBLE& t);
//已知比熵(kJ/(kg.℃))和干度(100%)，求比容(m^3/kg)(缺省是低压的一个值)
static double F_SX2V(VDOUBLE& t);

//已知比容(m^3/kg)和干度(100%)，求压力(MPa)(低压的一个值)
static double F_VX2PLP(VDOUBLE& t);
//已知比容(m^3/kg)和干度(100%)，求压力(MPa)(低高压的一个值)
static double F_VX2PHP(VDOUBLE& t);
//已知比容(m^3/kg)和干度(100%)，求压力(MPa)(缺省是低压的一个值)
static double F_VX2P(VDOUBLE& t);
//已知比容(m^3/kg)和干度(100%)，求温度(℃)(低压的一个值)
static double F_VX2TLP(VDOUBLE& t);
//已知比容(m^3/kg)和干度(100%)，求温度(℃)(高压的一个值)
static double F_VX2THP(VDOUBLE& t);
//已知比容(m^3/kg)和干度(100%)，求温度(℃)(缺省是低压的一个值)
static double F_VX2T(VDOUBLE& t);
//已知比容(m^3/kg)和干度(100%)，求比焓(kJ/kg)(低压的一个值)
static double F_VX2HLP(VDOUBLE& t);
//已知比容(m^3/kg)和干度(100%)，求比焓(kJ/kg)(高压的一个值)
static double F_VX2HHP(VDOUBLE& t);
//已知比容(m^3/kg)和干度(100%)，求比焓(kJ/kg)(缺省是低压的一个值)
static double F_VX2H(VDOUBLE& t);
//已知比容(m^3/kg)和干度(100%)，求比熵(kJ/(kg.℃))(低压的一个值)
static double F_VX2SLP(VDOUBLE& t);
//已知比容(m^3/kg)和干度(100%)，求比熵(kJ/(kg.℃))(高压的一个值)
static double F_VX2SHP(VDOUBLE& t);
//已知比容(m^3/kg)和干度(100%)，求比熵(kJ/(kg.℃))(缺省是低压的一个值)
static double F_VX2S(VDOUBLE& t);
EXTFUNCTION extfun[]=
{
#define ff(a,b,c,d)
#define df(a,b,c,d) c,
#define sf(a,b,c,d) c,
#define vf(a,b,c,d) c,
#include "func.h"
};



///*******************************************************************************/
////数学函数
///*******************************************************************************/
//
//double pt2h97(VDOUBLE& t)
//{
//	double h;
//	int r;
//	PT2H97(t.front(),*(++t.begin()),h,r);
//	return h;
//}
//平方函数
double SQRT(VDOUBLE& t)
{
    return sqrt(t.front());
}

//绝对值函数
double ABS(VDOUBLE& t)
{
    return abs(t.front());
}

//ln函数
double LN(VDOUBLE& t)
{
    return log(t.front());
}

//幂函数
double POW(VDOUBLE& t)
{
    return pow(t.front(),*(++t.begin()));
}

//log10函数
double LOG(VDOUBLE& t)
{
    return log10(t.front());
}

//指数函数
double EXP(VDOUBLE& t)
{
    return exp(t.front());
}

//正弦
double SIN(VDOUBLE& t)
{
    return sin(t.front());
}

//双曲正弦
double SINH(VDOUBLE& t)
{
    return sinh(t.front());
}

//反正弦
double ASIN(VDOUBLE& t)
{
    return asin(t.front());
}

//余弦
double COS(VDOUBLE& t)
{
    return cos(t.front());
}

//双曲余弦
double COSH(VDOUBLE& t)
{
    return cosh(t.front());
}

//反余弦
double ACOS(VDOUBLE& t)
{
    return asin(t.front());
}

//正切
double TAN(VDOUBLE& t)
{
    return tan(t.front());
}

//反正切
double ATON(VDOUBLE& t)
{
    return atan(t.front());
}

//双曲正切
double TANH(VDOUBLE& t)
{
    return tanh(t.front());
}


//阶乘
double FACTORIAL(VDOUBLE& t)
{
    double value,index;

    index=t.front();
    value=1;

    for(int i=1;i<=index;i++)
        value*=i;

    return value;
}

//求最大值
double MAX(VDOUBLE& t)
{
    double value=t.front();
    VDOUBLEInt Int=t.begin();

    while(++Int!=t.end())
    {
        if(*Int>value)
            value=*Int;
    }

    return value;
}

//求最小值
double MIN(VDOUBLE& t)
{
    double value=t.front();
    VDOUBLEInt Int=t.begin();

    while(++Int!=t.end())
    {
        if(*Int<value)
            value=*Int;
    }

    return value;
}



//处理数学异常
//int _matherr(exception *except )
//{
//    throw CExcept(" math error ");
//    return 0;
//}



/*******************************************************************************/
//气体的温度和压力转换函数
/*******************************************************************************/

//由温度求压力
double PST(VDOUBLE& t)
{
    return pst(t.front());
}

//由压力求温度
double TSP(VDOUBLE& t)
{
    return tsp(t.front());
}

/*******************************************************************************/
//由温度和压力求气体的其他参数
/*******************************************************************************/

//由温度压力求气体焓
double AHPT(VDOUBLE& t)
{
    double ha,sa,va;
    ptparam(t.front(),*(++t.begin()),&ha,&sa,&va);
    return ha;
}

//由温度压力求气体熵
double ASPT(VDOUBLE& t)
{
    double ha,sa,va;
    ptparam(t.front(),*(++t.begin()),&ha,&sa,&va);
    return sa;
}

//由温度压力求气体比容
double AVPT(VDOUBLE& t)
{
    double ha,sa,va;
    ptparam(t.front(),*(++t.begin()),&ha,&sa,&va);
    return va;
}

/*******************************************************************************/
//由压力和熵求气体的其他参数
/*******************************************************************************/

//由压力熵求气体温度
double ATPS(VDOUBLE& t)
{
    double ta,ha,va;
    psparam(t.front(),*(++t.begin()),&ta,&ha,&va);
    return ta;
}

//由压力熵求气体焓
double AHPS(VDOUBLE& t)
{
    double ta,ha,va;
    psparam(t.front(),*(++t.begin()),&ta,&ha,&va);
    return ha;
}

//由压力熵求气体比容
double AVPS(VDOUBLE& t)
{
    double ta,ha,va;
    psparam(t.front(),*(++t.begin()),&ta,&ha,&va);
    return va;
}

/*******************************************************************************/
//由压力和焓求气体的其他参数
/*******************************************************************************/


//由压力焓求气体温度
double ATPH(VDOUBLE& t)
{
    double ta,sa,va;
    phparam(t.front(),*(++t.begin()),&ta,&sa,&va);
    return ta;
}

//由压力焓求气体熵
double ASPH(VDOUBLE& t)
{
    double ta,sa,va;
    phparam(t.front(),*(++t.begin()),&ta,&sa,&va);
    return sa;
}

//由压力焓求气体比容
double AVPH(VDOUBLE& t)
{
    double ta,sa,va;
    phparam(t.front(),*(++t.begin()),&ta,&sa,&va);
    return sa;
}


/*******************************************************************************/
//由熵和焓求气体的其他参数
/*******************************************************************************/

//由熵和焓求气体压力
double APHS(VDOUBLE& t)
{
    double pa,ta,va;
    hsparam(t.front(),*(++t.begin()),&pa,&ta,&va);
    return pa;
}

//由熵和焓求气体温度
double ATHS(VDOUBLE& t)
{
    double pa,ta,va;
    hsparam(t.front(),*(++t.begin()),&pa,&ta,&va);
    return ta;
}

//由熵和焓求气体比容
double AVHS(VDOUBLE& t)
{
    double pa,ta,va;
    hsparam(t.front(),*(++t.begin()),&pa,&ta,&va);
    return va;
}


/*******************************************************************************/
//由温度和压力求水的其他参数
/*******************************************************************************/

//由温度压力求水焓
double WHPT(VDOUBLE& t)
{
    double ha,sa,va;
    waterparam(t.front(),*(++t.begin()),&ha,&sa,&va);
    return ha;
}

//由温度压力求水熵
double WSPT(VDOUBLE& t)
{
    double ha,sa,va;
    waterparam(t.front(),*(++t.begin()),&ha,&sa,&va);
    return sa;
}

//由温度压力求水比容
double WVPT(VDOUBLE& t)
{
    double ha,sa,va;
    waterparam(t.front(),*(++t.begin()),&ha,&sa,&va);
    return va;
}

/*******************************************************************************/
//由温度和压力求水气的其他参数
/*******************************************************************************/
//由温度压力求水气焓
double GHPT(VDOUBLE& t)
{
    double ha,sa,va;
    vaporparam(t.front(),*(++t.begin()),&ha,&sa,&va);
    return ha;
}

//由温度压力求水气熵
double GSPT(VDOUBLE& t)
{
    double ha,sa,va;
    vaporparam(t.front(),*(++t.begin()),&ha,&sa,&va);
    return sa;
}

//由温度压力求水气比容
double GVPT(VDOUBLE& t)
{
    double ha,sa,va;
    vaporparam(t.front(),*(++t.begin()),&ha,&sa,&va);
    return va;
}

//已知压力(MPa)，求对应饱和温度(℃)
double F_P2T(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2T(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和水比焓(kJ/kg)
double F_P2HL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2HL(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和汽比焓(kJ/kg)
double F_P2HG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2HG(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和水比熵(kJ/(kg.℃))
double F_P2SL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2SL(t.front(),dRet,nRang);
    return dRet;	
}
//已知压力(MPa)，求对应饱和汽比熵(kJ/(kg.℃))
double F_P2SG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2SG(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和水比容(m^3/kg)
double F_P2VL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2VL(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和汽比容(m^3/kg)
double F_P2VG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2VG(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和水定压比热(kJ/(kg.℃))
double F_P2CPL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2CPL(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和汽定压比热(kJ/(kg.℃))
double F_P2CPG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2CPG(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和水定容比热(kJ/(kg.℃))
double F_P2CVL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2CVL(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和汽定容比热(kJ/(kg.℃))
double F_P2CVG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2CVG(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和水内能(kJ/kg)
double F_P2EL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2EL(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和汽内能(kJ/kg)
double F_P2EG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2EG(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和水音速(m/s)
double F_P2SSPL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2SSPL(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和汽音速(m/s)
double F_P2SSPG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2SSPG(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和水定熵指数
double F_P2KSL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2KSL(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和汽定熵指数
double F_P2KSG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2KSG(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和水动力粘度(Pa.s)
double F_P2ETAL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2ETAL(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和汽动力粘度(Pa.s)
double F_P2ETAG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2ETAG(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和水运动粘度(m^2/s)
double F_P2UL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2UL(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和汽运动粘度(m^2/s)
double F_P2UG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2UG(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和汽运动粘度(m^2/s)
double F_P2TP2UG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2UG(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和水导热系数(W/(m.℃))
double F_P2RAMDL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2RAMDL(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和汽导热系数(W/(m.℃))
double F_P2RAMDG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2RAMDG(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和水普朗特数
double F_P2PRNL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2PRNL(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和汽普朗特数
double F_P2PRNG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2PRNG(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和水介电常数
double F_P2EPSL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2EPSL(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和汽介电常数
double F_P2EPSG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2EPSG(t.front(),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和水折射率
double F_P2NL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2NL(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)，求对应饱和汽折射率
double F_P2NG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2NG(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和温度(℃)，求比焓(kJ/kg)
double F_PT2H(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2H(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和温度(℃)，求比熵(kJ/(kg.℃))
double F_PT2S(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2S(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和温度(℃)，求比容(m^3/kg)
double F_PT2V(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2V(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和温度(℃)，求干度(100%)
double F_PT2X(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2X(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和温度(℃)，求定压比热(kJ/(kg.℃))
double F_PT2CP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2CP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和温度(℃)，求定容比热(kJ/(kg.℃))
double F_PT2CV(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2CV(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和温度(℃)，求内能(kJ/kg)
double F_PT2E(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2E(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和温度(℃)，求音速(m/s)
double F_PT2SSP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2SSP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和温度(℃)，求定熵指数
double F_PT2KS(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2KS(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和温度(℃)，求动力粘度(Pa.s)
double F_PT2ETA(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2ETA(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和温度(℃)，求运动粘度(m^2/s)
double F_PT2U(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2U(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和温度(℃)，求热传导系数 (W/(m.℃))
double F_PT2RAMD(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2RAMD(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和温度(℃)，求普朗特数
double F_PT2PRN(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2PRN(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和温度(℃)，求介电常数
double F_PT2EPS(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2EPS(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和温度(℃)，求折射率
double F_PT2N(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2N(t.front(),*(++t.begin()),t[2],dRet,nRang);
    return dRet;
}

//已知压力(MPa)和比焓(kJ/kg)，求温度(℃)
double F_PH2T(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PH2T(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和比焓(kJ/kg)，求比熵(kJ/(kg.℃))
double F_PH2S(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PH2S(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和比焓(kJ/kg)，求比容(m^3/kg)
double F_PH2V(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PH2V(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和比焓(kJ/kg)，求干度(100%)
double F_PH2X(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PH2X(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}

//已知压力(MPa)和比熵(kJ/(kg.℃))，求温度(℃)
double F_PS2T(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PS2T(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和比熵(kJ/(kg.℃))，求比焓(kJ/kg)
double F_PS2H(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PS2H(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和比熵(kJ/(kg.℃))，求比容(m^3/kg)
double F_PS2V(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PS2V(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和比熵(kJ/(kg.℃))，求干度(100%)
double F_PS2X(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PS2X(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}

//已知压力(MPa)和比容(m^3/kg)，求温度(℃)
double F_PV2T(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PV2T(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和比容(m^3/kg)，求比焓(kJ/kg)
double F_PV2H(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PV2H(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和比容(m^3/kg)，求比容(m^3/kg)
double F_PV2S(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PV2S(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和比容(m^3/kg)，求干度(100%)
double F_PV2X(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PV2X(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}

//已知压力(MPa)和干度(100%)，求温度(℃)
double F_PX2T(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PX2T(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和干度(100%)，求比焓(kJ/kg)
double F_PX2H(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PX2H(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和干度(100%)，求比熵(kJ/(kg.℃))
double F_PX2S(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PX2S(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知压力(MPa)和干度(100%)，求比容(m^3/kg)
double F_PX2V(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PX2V(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}

//已知温度(℃)，求饱和压力(MPa)？
double F_T2P(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2P(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和水比焓(kJ/kg)
double F_T2HL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2HL(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和汽比焓(kJ/kg)
double F_T2HG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2HG(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和水比熵(kJ/(kg.℃))
double F_T2SL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2SL(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和汽比熵(kJ/(kg.℃))
double F_T2SG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2SG(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和水比容(m^3/kg)
double F_T2VL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2VL(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和汽比容(m^3/kg)
double F_T2VG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2VG(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和水定压比热(kJ/(kg.℃))
double F_T2CPL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2CPL(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和汽定压比热(kJ/(kg.℃))
double F_T2CPG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2CPG(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和水定容比热(kJ/(kg.℃))
double F_T2CVL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2CVL(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和汽定容比热(kJ/(kg.℃))
double F_T2CVG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2CVG(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和水内能(kJ/kg)
double F_T2EL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2EL(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和汽内能(kJ/kg)
double F_T2EG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2EG(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和水音速(m/s)
double F_T2SSPL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2SSPL(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和汽音速(m/s)
double F_T2SSPG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2SSPG(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和水定熵指数
double F_T2KSL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2KSL(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和汽定熵指数
double F_T2KSG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2KSG(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和水动力粘度(Pa.s)
double F_T2ETAL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2KSG(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和汽动力粘度(Pa.s)
double F_T2ETAG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2ETAG(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和水运动粘度(m^2/s)
double F_T2UL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2UL(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和汽运动粘度(m^2/s)
double F_T2UG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2UG(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和水导热系数(W/(m.℃))
double F_T2RAMDL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2RAMDL(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和汽导热系数(W/(m.℃))
double F_T2RAMDG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2RAMDG(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和水普朗特数
double F_T2PRNL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2PRNL(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和汽普朗特数
double F_T2PRNG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2PRNL(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和水介电常数
double F_T2EPSL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2EPSL(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和汽介电常数
double F_T2EPSG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2EPSG(t.front(),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和水折射率
double F_T2NL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2NL(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和汽折射率
double F_T2NG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2NG(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)，求饱和水表面张力(N/m)
double F_T2SURFT(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2SURFT(t.front(),dRet,nRang);
    return dRet;
}

//已知温度(℃)和比焓(kJ/kg)，求压力(MPa)(低压的一个值)
double F_TH2PLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TH2PLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)和比焓(kJ/kg)，求比熵(kJ/(kg.℃))(低压的一个值)
double F_TH2SLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TH2SLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)和比焓(kJ/kg)，求比容(m^3/kg)(低压的一个值)
double F_TH2VLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TH2VLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)和比焓(kJ/kg)，求压力(MPa)(高压的一个值)
double F_TH2PHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TH2PHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)和比焓(kJ/kg)，求比熵(kJ/(kg.℃))(高压的一个值)
double F_TH2SHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TH2SHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)和比焓(kJ/kg)，求比容(m^3/kg)(高压的一个值)
double F_TH2VHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TH2VHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)和比焓(kJ/kg)，求压力(MPa)(缺省为低压的一个值)
double F_TH2P(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TH2P(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)和比焓(kJ/kg)，求比熵(kJ/(kg.℃))(缺省为低压的一个值)
double F_TH2S(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TH2S(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)和比焓(kJ/kg)，求比容(m^3/kg)(缺省为低压的一个值)
double F_TH2V(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TH2V(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)和比焓(kJ/kg)，求干度(100%)
double F_TH2X(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TH2X(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}

//已知温度(℃)和比熵(kJ/(kg.℃))，求压力(MPa)(低压的一个值)
double F_TS2PLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TS2PLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)和比熵(kJ/(kg.℃))，求比焓(kJ/kg)(低压的一个值)
double F_TS2HLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TS2HLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)和比熵(kJ/(kg.℃))，求比容(m^3/kg)(低压的一个值)
double F_TS2VLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TS2VLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)和比熵(kJ/(kg.℃))，求压力(MPa)(高压的一个值)
double F_TS2PHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TS2PHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)和比熵(kJ/(kg.℃))，求比焓(kJ/kg)(高压的一个值)
double F_TS2HHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TS2HHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)和比熵(kJ/(kg.℃))，求比容(m^3/kg)(高压的一个值)
double F_TS2VHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TS2VHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)和比熵(kJ/(kg.℃))，求压力(MPa)(缺省为低压的一个值)
double F_TS2P(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TS2P(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)和比熵(kJ/(kg.℃))，求比焓(kJ/kg)(缺省为低压的一个值)
double F_TS2H(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TS2H(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)和比熵(kJ/(kg.℃))，求比容(m^3/kg)(缺省为低压的一个值)
double F_TS2V(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TS2V(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)和比熵(kJ/(kg.℃))，求干度(100%)
double F_TS2X(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TS2X(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}

//已知温度(℃)和比容(m^3/kg)，求压力(MPa)
double F_TV2P(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TV2P(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)和比容(m^3/kg)，求比焓(kJ/kg)
double F_TV2H(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TV2H(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)和比容(m^3/kg)，求比熵(kJ/(kg.℃))
double F_TV2S(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TV2S(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)和比容(m^3/kg)，求干度(100%)
double F_TV2X(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TV2X(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}

//已知温度(℃)和干度(100%)，求压力(MPa)
double F_TX2P(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TX2P(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)和干度(100%)，求比焓(kJ/kg)
double F_TX2H(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TX2H(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)和干度(100%)，求比熵(kJ/(kg.℃))
double F_TX2S(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TX2S(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知温度(℃)和干度(100%)，求比容(m^3/kg)
double F_TX2V(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TX2V(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}

//已知比焓(kJ/kg)和比熵(kJ/(kg.℃))，求压力(MPa)
double F_HS2P(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HS2P(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比焓(kJ/kg)和比熵(kJ/(kg.℃))，求温度(℃)
double F_HS2T(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HS2T(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比焓(kJ/kg)和比熵(kJ/(kg.℃))，求比容(m^3/kg)
double F_HS2V(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HS2V(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比焓(kJ/kg)和比熵(kJ/(kg.℃))，求干度(100%)
double F_HS2X(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HS2X(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}

//已知比焓(kJ/kg)和比容(m^3/kg)，求压力(MPa)
double F_HV2P(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HV2P(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比焓(kJ/kg)和比容(m^3/kg)，求温度(℃)
double F_HV2T(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HV2T(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比焓(kJ/kg)和比容(m^3/kg)，求比熵(kJ/(kg.℃))
double F_HV2S(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HV2S(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比焓(kJ/kg)和比容(m^3/kg)，求干度(100%)
double F_HV2X(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HV2X(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}

//已知比焓(kJ/kg)和干度(100%)，求压力(MPa)(低压的一个值)
double F_HX2PLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HX2PLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比焓(kJ/kg)和干度(100%)，求温度(℃)(低压的一个值)
double F_HX2TLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HX2TLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比焓(kJ/kg)和干度(100%)，求比熵(kJ/(kg.℃))(低压的一个值)
double F_HX2SLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HX2SLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比焓(kJ/kg)和干度(100%)，求比容(m^3/kg)(低压的一个值)
double F_HX2VLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HX2VLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比焓(kJ/kg)和干度(100%)，求压力(MPa)(高压的一个值)
double F_HX2PHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HX2PHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比焓(kJ/kg)和干度(100%)，求温度(℃)(高压的一个值)
double F_HX2THP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HX2THP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比焓(kJ/kg)和干度(100%)，求比熵(kJ/(kg.℃))(高压的一个值)
double F_HX2SHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HX2SHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比焓(kJ/kg)和干度(100%)，求比容(m^3/kg)(高压的一个值)
double F_HX2VHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HX2VHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比焓(kJ/kg)和干度(100%)，求压力(MPa)(缺省是低压的一个值)
double F_HX2P(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HX2P(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比焓(kJ/kg)和干度(100%)，求温度(℃)(缺省是低压的一个值)
double F_HX2T(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HX2T(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比焓(kJ/kg)和干度(100%)，求比熵(kJ/(kg.℃))(缺省是低压的一个值)
double F_HX2S(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HX2S(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比焓(kJ/kg)和干度(100%)，求比容(m^3/kg)(缺省是低压的一个值)
double F_HX2V(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HX2V(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}

//已知比熵(kJ/(kg.℃))和比容(m^3/kg)，求压力(MPa)
double F_SV2P(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SV2P(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比熵(kJ/(kg.℃))和比容(m^3/kg)，求温度(℃)
double F_SV2T(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SV2T(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比熵(kJ/(kg.℃))和比容(m^3/kg)，求比焓(kJ/kg)
double F_SV2H(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SV2H(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比熵(kJ/(kg.℃))和比容(m^3/kg)，求干度(100%)
double F_SV2X(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SV2X(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}


//已知比熵(kJ/(kg.℃))和干度(100%)，求压力(MPa)(低压的一个值)
double F_SX2PLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2PLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比熵(kJ/(kg.℃))和干度(100%)，求压力(MPa)(中压的一个值)
double F_SX2PMP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2PMP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比熵(kJ/(kg.℃))和干度(100%)，求压力(MPa)(高压的一个值)
double F_SX2PHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2PHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比熵(kJ/(kg.℃))和干度(100%)，求压力(MPa)(缺省是低压的一个值)
double F_SX2P(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2P(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比熵(kJ/(kg.℃))和干度(100%)，求温度(℃)(低压的一个值)
double F_SX2TLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2TLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比熵(kJ/(kg.℃))和干度(100%)，求温度(℃)(中压的一个值)
double F_SX2TMP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2TMP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比熵(kJ/(kg.℃))和干度(100%)，求温度(℃)(高压的一个值)
double F_SX2THP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2THP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比熵(kJ/(kg.℃))和干度(100%)，求温度(℃)(缺省是低压的一个值)
double F_SX2T(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2T(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比熵(kJ/(kg.℃))和干度(100%)，求比焓(kJ/kg)(低压的一个值)
double F_SX2HLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2HLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比熵(kJ/(kg.℃))和干度(100%)，求比焓(kJ/kg)(中压的一个值)
double F_SX2HMP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2HMP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比熵(kJ/(kg.℃))和干度(100%)，求比焓(kJ/kg)(高压的一个值)
double F_SX2HHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2HHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比熵(kJ/(kg.℃))和干度(100%)，求比焓(kJ/kg)(缺省是低压的一个值)
double F_SX2H(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2H(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比熵(kJ/(kg.℃))和干度(100%)，求比容(m^3/kg)(低压的一个值)
double F_SX2VLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2VLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比熵(kJ/(kg.℃))和干度(100%)，求比容(m^3/kg)(中压的一个值)
double F_SX2VMP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2VMP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比熵(kJ/(kg.℃))和干度(100%)，求比容(m^3/kg)(高压的一个值)
double F_SX2VHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2VHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比熵(kJ/(kg.℃))和干度(100%)，求比容(m^3/kg)(缺省是低压的一个值)
double F_SX2V(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2V(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}

//已知比容(m^3/kg)和干度(100%)，求压力(MPa)(低压的一个值)
double F_VX2PLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    VX2PLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比容(m^3/kg)和干度(100%)，求压力(MPa)(低高压的一个值)
double F_VX2PHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    VX2PHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比容(m^3/kg)和干度(100%)，求压力(MPa)(缺省是低压的一个值)
double F_VX2P(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    VX2P(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比容(m^3/kg)和干度(100%)，求温度(℃)(低压的一个值)
double F_VX2TLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    VX2TLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比容(m^3/kg)和干度(100%)，求温度(℃)(高压的一个值)
double F_VX2THP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    VX2THP(t.front(), *(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比容(m^3/kg)和干度(100%)，求温度(℃)(缺省是低压的一个值)
double F_VX2T(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    VX2T(t.front(), *(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比容(m^3/kg)和干度(100%)，求比焓(kJ/kg)(低压的一个值)
double F_VX2HLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    VX2HLP(t.front(), *(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比容(m^3/kg)和干度(100%)，求比焓(kJ/kg)(高压的一个值)
double F_VX2HHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    VX2HHP(t.front(), *(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比容(m^3/kg)和干度(100%)，求比焓(kJ/kg)(缺省是低压的一个值)
double F_VX2H(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    VX2H(t.front(), *(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比容(m^3/kg)和干度(100%)，求比熵(kJ/(kg.℃))(低压的一个值)
double F_VX2SLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    VX2SLP(t.front(), *(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比容(m^3/kg)和干度(100%)，求比熵(kJ/(kg.℃))(高压的一个值)
double F_VX2SHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    VX2SHP(t.front(), *(++t.begin()),dRet,nRang);
    return dRet;
}
//已知比容(m^3/kg)和干度(100%)，求比熵(kJ/(kg.℃))(缺省是低压的一个值)
double F_VX2S(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    VX2S(t.front(), *(++t.begin()),dRet,nRang);
    return dRet;
}
