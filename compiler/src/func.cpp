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

//������ѧ�쳣
//static int _matherr(exception *except );

//ͨ���¶���ѹ��
static double PST(VDOUBLE& t);
//ͨ��ѹ�����¶�
static double TSP(VDOUBLE& t);

//ƽ������
static double SQRT(VDOUBLE& t);
//����ֵ����
static double ABS(VDOUBLE& t);
//ln����
static double LN(VDOUBLE& t);
//�ݺ���
static double POW(VDOUBLE& t);
//log10����
static double LOG(VDOUBLE& t);
//ָ������
static double EXP(VDOUBLE& t);
//����
static double SIN(VDOUBLE& t);
//˫������
static double SINH(VDOUBLE& t);
//������
static double ASIN(VDOUBLE& t);
//����
static double COS(VDOUBLE& t);
//˫������
static double COSH(VDOUBLE& t);
//������
static double ACOS(VDOUBLE& t);
//����
static double TAN(VDOUBLE& t);
//������
static double ATON(VDOUBLE& t);
//˫������
static double TANH(VDOUBLE& t);
//��׳�
static double FACTORIAL(VDOUBLE& t);
//�����ֵ
static double MAX(VDOUBLE& t);
//����Сֵ
static double MIN(VDOUBLE& t);

//ͨ��ѹ�����¶����������
static double AHPT(VDOUBLE& t);
//ͨ��ѹ�����¶����������
static double ASPT(VDOUBLE& t);
//ͨ��ѹ�����¶�������ı���
static double AVPT(VDOUBLE& t);

//ͨ��ѹ��������������¶�
static double ATPS(VDOUBLE& t);
//ͨ��ѹ���������������
static double AHPS(VDOUBLE& t);
//ͨ��ѹ������������ı���
static double AVPS(VDOUBLE& t);

//ͨ��ѹ��������������¶�
static double ATPH(VDOUBLE& t);
//ͨ��ѹ���������������
static double ASPH(VDOUBLE& t);
//ͨ��ѹ������������ı���
static double AVPH(VDOUBLE& t);

//ͨ���غ����������ѹ��
static double APHS(VDOUBLE& t);
//ͨ���غ�����������¶�
static double ATHS(VDOUBLE& t);
//ͨ���غ���������ı���
static double AVHS(VDOUBLE& t);

//ͨ���¶Ⱥ�ѹ����ˮ����
static double WHPT(VDOUBLE& t);
//ͨ���¶Ⱥ�ѹ����ˮ����
static double WSPT(VDOUBLE& t);
//ͨ���¶Ⱥ�ѹ����ˮ�ı���
static double WVPT(VDOUBLE& t);

//ͨ���¶Ⱥ�ѹ������ˮ����
static double GHPT(VDOUBLE& t);
//ͨ���¶Ⱥ�ѹ������ˮ����
static double GSPT(VDOUBLE& t);
//ͨ���¶Ⱥ�ѹ������ˮ�ı���
static double GVPT(VDOUBLE& t);


//��֪ѹ��(MPa)�����Ӧ�����¶�(��)
static double F_P2T(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ����ˮ����(kJ/kg)
static double F_P2HL(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ����������(kJ/kg)
static double F_P2HG(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ����ˮ����(kJ/(kg.��))
static double F_P2SL(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ����������(kJ/(kg.��))
static double F_P2SG(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ����ˮ����(m^3/kg)
static double F_P2VL(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ����������(m^3/kg)
static double F_P2VG(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ����ˮ��ѹ����(kJ/(kg.��))
static double F_P2CPL(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ��������ѹ����(kJ/(kg.��))
static double F_P2CPG(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ����ˮ���ݱ���(kJ/(kg.��))
static double F_P2CVL(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ���������ݱ���(kJ/(kg.��))
static double F_P2CVG(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ����ˮ����(kJ/kg)
static double F_P2EL(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ����������(kJ/kg)
static double F_P2EG(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ����ˮ����(m/s)
static double F_P2SSPL(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ����������(m/s)
static double F_P2SSPG(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ����ˮ����ָ��
static double F_P2KSL(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ����������ָ��
static double F_P2KSG(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ����ˮ����ճ��(Pa.s)
static double F_P2ETAL(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ����������ճ��(Pa.s)
static double F_P2ETAG(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ����ˮ�˶�ճ��(m^2/s)
static double F_P2UL(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ�������˶�ճ��(m^2/s)
static double F_P2UG(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ����ˮ����ϵ��(W/(m.��))
static double F_P2RAMDL(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ����������ϵ��(W/(m.��))
static double F_P2RAMDG(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ����ˮ��������
static double F_P2PRNL(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ��������������
static double F_P2PRNG(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ����ˮ��糣��
static double F_P2EPSL(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ��������糣��
static double F_P2EPSG(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ����ˮ������
static double F_P2NL(VDOUBLE& t);
//��֪ѹ��(MPa)�����Ӧ������������
static double F_P2NG(VDOUBLE& t);

//��֪ѹ��(MPa)���¶�(��)�������(kJ/kg)
static double F_PT2H(VDOUBLE& t);
//��֪ѹ��(MPa)���¶�(��)�������(kJ/(kg.��))
static double F_PT2S(VDOUBLE& t);
//��֪ѹ��(MPa)���¶�(��)�������(m^3/kg)
static double F_PT2V(VDOUBLE& t);
//��֪ѹ��(MPa)���¶�(��)����ɶ�(100%)
static double F_PT2X(VDOUBLE& t);
//��֪ѹ��(MPa)���¶�(��)����ѹ����(kJ/(kg.��))
static double F_PT2CP(VDOUBLE& t);
//��֪ѹ��(MPa)���¶�(��)�����ݱ���(kJ/(kg.��))
static double F_PT2CV(VDOUBLE& te);
//��֪ѹ��(MPa)���¶�(��)��������(kJ/kg)
static double F_PT2E(VDOUBLE& t);
//��֪ѹ��(MPa)���¶�(��)��������(m/s)
static double F_PT2SSP(VDOUBLE& t);
//��֪ѹ��(MPa)���¶�(��)������ָ��
static double F_PT2KS(VDOUBLE& t);
//��֪ѹ��(MPa)���¶�(��)������ճ��(Pa.s)
static double F_PT2ETA(VDOUBLE& t);
//��֪ѹ��(MPa)���¶�(��)�����˶�ճ��(m^2/s)
static double F_PT2U(VDOUBLE& t);
//��֪ѹ��(MPa)���¶�(��)�����ȴ���ϵ�� (W/(m.��))
static double F_PT2RAMD(VDOUBLE& t);
//��֪ѹ��(MPa)���¶�(��)������������
static double F_PT2PRN(VDOUBLE& t);
//��֪ѹ��(MPa)���¶�(��)�����糣��
static double F_PT2EPS(VDOUBLE& t);
//��֪ѹ��(MPa)���¶�(��)����������
static double F_PT2N(VDOUBLE& t);

//��֪ѹ��(MPa)�ͱ���(kJ/kg)�����¶�(��)
static double F_PH2T(VDOUBLE& t);
//��֪ѹ��(MPa)�ͱ���(kJ/kg)�������(kJ/(kg.��))
static double F_PH2S(VDOUBLE& t);
//��֪ѹ��(MPa)�ͱ���(kJ/kg)�������(m^3/kg)
static double F_PH2V(VDOUBLE& t);
//��֪ѹ��(MPa)�ͱ���(kJ/kg)����ɶ�(100%)
static double F_PH2X(VDOUBLE& t);

//��֪ѹ��(MPa)�ͱ���(kJ/(kg.��))�����¶�(��)
static double F_PS2T(VDOUBLE& t);
//��֪ѹ��(MPa)�ͱ���(kJ/(kg.��))�������(kJ/kg)
static double F_PS2H(VDOUBLE& t);
//��֪ѹ��(MPa)�ͱ���(kJ/(kg.��))�������(m^3/kg)
static double F_PS2V(VDOUBLE& t);
//��֪ѹ��(MPa)�ͱ���(kJ/(kg.��))����ɶ�(100%)
static double F_PS2X(VDOUBLE& t);

//��֪ѹ��(MPa)�ͱ���(m^3/kg)�����¶�(��)
static double F_PV2T(VDOUBLE& t);
//��֪ѹ��(MPa)�ͱ���(m^3/kg)�������(kJ/kg)
static double F_PV2H(VDOUBLE& t);
//��֪ѹ��(MPa)�ͱ���(m^3/kg)�������(m^3/kg)
static double F_PV2S(VDOUBLE& t);
//��֪ѹ��(MPa)�ͱ���(m^3/kg)����ɶ�(100%)
static double F_PV2X(VDOUBLE& t);

//��֪ѹ��(MPa)�͸ɶ�(100%)�����¶�(��)
static double F_PX2T(VDOUBLE& t);
//��֪ѹ��(MPa)�͸ɶ�(100%)�������(kJ/kg)
static double F_PX2H(VDOUBLE& t);
//��֪ѹ��(MPa)�͸ɶ�(100%)�������(kJ/(kg.��))
static double F_PX2S(VDOUBLE& t);
//��֪ѹ��(MPa)�͸ɶ�(100%)�������(m^3/kg)
static double F_PX2V(VDOUBLE& t);

//��֪�¶�(��)���󱥺�ѹ��(MPa)��
static double F_T2P(VDOUBLE& t);
//��֪�¶�(��)���󱥺�ˮ����(kJ/kg)
static double F_T2HL(VDOUBLE& t);
//��֪�¶�(��)���󱥺�������(kJ/kg)
static double F_T2HG(VDOUBLE& t);
//��֪�¶�(��)���󱥺�ˮ����(kJ/(kg.��))
static double F_T2SL(VDOUBLE& t);
//��֪�¶�(��)���󱥺�������(kJ/(kg.��))
static double F_T2SG(VDOUBLE& t);
//��֪�¶�(��)���󱥺�ˮ����(m^3/kg)
static double F_T2VL(VDOUBLE& t);
//��֪�¶�(��)���󱥺�������(m^3/kg)
static double F_T2VG(VDOUBLE& t);
//��֪�¶�(��)���󱥺�ˮ��ѹ����(kJ/(kg.��))
static double F_T2CPL(VDOUBLE& t);
//��֪�¶�(��)���󱥺�����ѹ����(kJ/(kg.��))
static double F_T2CPG(VDOUBLE& t);
//��֪�¶�(��)���󱥺�ˮ���ݱ���(kJ/(kg.��))
static double F_T2CVL(VDOUBLE& t);
//��֪�¶�(��)���󱥺������ݱ���(kJ/(kg.��))
static double F_T2CVG(VDOUBLE& t);
//��֪�¶�(��)���󱥺�ˮ����(kJ/kg)
static double F_T2EL(VDOUBLE& t);
//��֪�¶�(��)���󱥺�������(kJ/kg)
static double F_T2EG(VDOUBLE& t);
//��֪�¶�(��)���󱥺�ˮ����(m/s)
static double F_T2SSPL(VDOUBLE& t);
//��֪�¶�(��)���󱥺�������(m/s)
static double F_T2SSPG(VDOUBLE& t);
//��֪�¶�(��)���󱥺�ˮ����ָ��
static double F_T2KSL(VDOUBLE& t);
//��֪�¶�(��)���󱥺�������ָ��
static double F_T2KSG(VDOUBLE& t);
//��֪�¶�(��)���󱥺�ˮ����ճ��(Pa.s)
static double F_T2ETAL(VDOUBLE& t);
//��֪�¶�(��)���󱥺�������ճ��(Pa.s)
static double F_T2ETAG(VDOUBLE& t);
//��֪�¶�(��)���󱥺�ˮ�˶�ճ��(m^2/s)
static double F_T2UL(VDOUBLE& t);
//��֪�¶�(��)���󱥺����˶�ճ��(m^2/s)
static double F_T2UG(VDOUBLE& t);
//��֪�¶�(��)���󱥺�ˮ����ϵ��(W/(m.��))
static double F_T2RAMDL(VDOUBLE& t);
//��֪�¶�(��)���󱥺�������ϵ��(W/(m.��))
static double F_T2RAMDG(VDOUBLE& t);
//��֪�¶�(��)���󱥺�ˮ��������
static double F_T2PRNL(VDOUBLE& t);
//��֪�¶�(��)���󱥺�����������
static double F_T2PRNG(VDOUBLE& t);
//��֪�¶�(��)���󱥺�ˮ��糣��
static double F_T2EPSL(VDOUBLE& t);
//��֪�¶�(��)���󱥺�����糣��
static double F_T2EPSG(VDOUBLE& t);
//��֪�¶�(��)���󱥺�ˮ������
static double F_T2NL(VDOUBLE& t);
//��֪�¶�(��)���󱥺���������
static double F_T2NG(VDOUBLE& t);
//��֪�¶�(��)���󱥺�ˮ��������(N/m)
static double F_T2SURFT(VDOUBLE& t);

//��֪�¶�(��)�ͱ���(kJ/kg)����ѹ��(MPa)(��ѹ��һ��ֵ)
static double F_TH2PLP(VDOUBLE& t);
//��֪�¶�(��)�ͱ���(kJ/kg)�������(kJ/(kg.��))(��ѹ��һ��ֵ)
static double F_TH2SLP(VDOUBLE& t);
//��֪�¶�(��)�ͱ���(kJ/kg)�������(m^3/kg)(��ѹ��һ��ֵ)
static double F_TH2VLP(VDOUBLE& t);
//��֪�¶�(��)�ͱ���(kJ/kg)����ѹ��(MPa)(��ѹ��һ��ֵ)
static double F_TH2PHP(VDOUBLE& t);
//��֪�¶�(��)�ͱ���(kJ/kg)�������(kJ/(kg.��))(��ѹ��һ��ֵ)
static double F_TH2SHP(VDOUBLE& t);
//��֪�¶�(��)�ͱ���(kJ/kg)�������(m^3/kg)(��ѹ��һ��ֵ)
static double F_TH2VHP(VDOUBLE& t);
//��֪�¶�(��)�ͱ���(kJ/kg)����ѹ��(MPa)(ȱʡΪ��ѹ��һ��ֵ)
static double F_TH2P(VDOUBLE& t);
//��֪�¶�(��)�ͱ���(kJ/kg)�������(kJ/(kg.��))(ȱʡΪ��ѹ��һ��ֵ)
static double F_TH2S(VDOUBLE& t);
//��֪�¶�(��)�ͱ���(kJ/kg)�������(m^3/kg)(ȱʡΪ��ѹ��һ��ֵ)
static double F_TH2V(VDOUBLE& t);
//��֪�¶�(��)�ͱ���(kJ/kg)����ɶ�(100%)
static double F_TH2X(VDOUBLE& t);

//��֪�¶�(��)�ͱ���(kJ/(kg.��))����ѹ��(MPa)(��ѹ��һ��ֵ)
static double F_TS2PLP(VDOUBLE& t);
//��֪�¶�(��)�ͱ���(kJ/(kg.��))�������(kJ/kg)(��ѹ��һ��ֵ)
static double F_TS2HLP(VDOUBLE& t);
//��֪�¶�(��)�ͱ���(kJ/(kg.��))�������(m^3/kg)(��ѹ��һ��ֵ)
static double F_TS2VLP(VDOUBLE& t);
//��֪�¶�(��)�ͱ���(kJ/(kg.��))����ѹ��(MPa)(��ѹ��һ��ֵ)
static double F_TS2PHP(VDOUBLE& t);
//��֪�¶�(��)�ͱ���(kJ/(kg.��))�������(kJ/kg)(��ѹ��һ��ֵ)
static double F_TS2HHP(VDOUBLE& t);
//��֪�¶�(��)�ͱ���(kJ/(kg.��))�������(m^3/kg)(��ѹ��һ��ֵ)
static double F_TS2VHP(VDOUBLE& t);
//��֪�¶�(��)�ͱ���(kJ/(kg.��))����ѹ��(MPa)(ȱʡΪ��ѹ��һ��ֵ)
static double F_TS2P(VDOUBLE& t);
//��֪�¶�(��)�ͱ���(kJ/(kg.��))�������(kJ/kg)(ȱʡΪ��ѹ��һ��ֵ)
static double F_TS2H(VDOUBLE& t);
//��֪�¶�(��)�ͱ���(kJ/(kg.��))�������(m^3/kg)(ȱʡΪ��ѹ��һ��ֵ)
static double F_TS2V(VDOUBLE& t);
//��֪�¶�(��)�ͱ���(kJ/(kg.��))����ɶ�(100%)
static double F_TS2X(VDOUBLE& t);

//��֪�¶�(��)�ͱ���(m^3/kg)����ѹ��(MPa)
static double F_TV2P(VDOUBLE& t);
//��֪�¶�(��)�ͱ���(m^3/kg)�������(kJ/kg)
static double F_TV2H(VDOUBLE& t);
//��֪�¶�(��)�ͱ���(m^3/kg)�������(kJ/(kg.��))
static double F_TV2S(VDOUBLE& t);
//��֪�¶�(��)�ͱ���(m^3/kg)����ɶ�(100%)
static double F_TV2X(VDOUBLE& t);

//��֪�¶�(��)�͸ɶ�(100%)����ѹ��(MPa)
static double F_TX2P(VDOUBLE& t);
//��֪�¶�(��)�͸ɶ�(100%)�������(kJ/kg)
static double F_TX2H(VDOUBLE& t);
//��֪�¶�(��)�͸ɶ�(100%)�������(kJ/(kg.��))
static double F_TX2S(VDOUBLE& t);
//��֪�¶�(��)�͸ɶ�(100%)�������(m^3/kg)
static double F_TX2V(VDOUBLE& t);

//��֪����(kJ/kg)�ͱ���(kJ/(kg.��))����ѹ��(MPa)
static double F_HS2P(VDOUBLE& t);
//��֪����(kJ/kg)�ͱ���(kJ/(kg.��))�����¶�(��)
static double F_HS2T(VDOUBLE& t);
//��֪����(kJ/kg)�ͱ���(kJ/(kg.��))�������(m^3/kg)
static double F_HS2V(VDOUBLE& t);
//��֪����(kJ/kg)�ͱ���(kJ/(kg.��))����ɶ�(100%)
static double F_HS2X(VDOUBLE& t);

//��֪����(kJ/kg)�ͱ���(m^3/kg)����ѹ��(MPa)
static double F_HV2P(VDOUBLE& t);
//��֪����(kJ/kg)�ͱ���(m^3/kg)�����¶�(��)
static double F_HV2T(VDOUBLE& t);
//��֪����(kJ/kg)�ͱ���(m^3/kg)�������(kJ/(kg.��))
static double F_HV2S(VDOUBLE& t);
//��֪����(kJ/kg)�ͱ���(m^3/kg)����ɶ�(100%)
static double F_HV2X(VDOUBLE& t);

//��֪����(kJ/kg)�͸ɶ�(100%)����ѹ��(MPa)(��ѹ��һ��ֵ)
static double F_HX2PLP(VDOUBLE& t);
//��֪����(kJ/kg)�͸ɶ�(100%)�����¶�(��)(��ѹ��һ��ֵ)
static double F_HX2TLP(VDOUBLE& t);
//��֪����(kJ/kg)�͸ɶ�(100%)�������(kJ/(kg.��))(��ѹ��һ��ֵ)
static double F_HX2SLP(VDOUBLE& t);
//��֪����(kJ/kg)�͸ɶ�(100%)�������(m^3/kg)(��ѹ��һ��ֵ)
static double F_HX2VLP(VDOUBLE& t);
//��֪����(kJ/kg)�͸ɶ�(100%)����ѹ��(MPa)(��ѹ��һ��ֵ)
static double F_HX2PHP(VDOUBLE& t);
//��֪����(kJ/kg)�͸ɶ�(100%)�����¶�(��)(��ѹ��һ��ֵ)
static double F_HX2THP(VDOUBLE& t);
//��֪����(kJ/kg)�͸ɶ�(100%)�������(kJ/(kg.��))(��ѹ��һ��ֵ)
static double F_HX2SHP(VDOUBLE& t);
//��֪����(kJ/kg)�͸ɶ�(100%)�������(m^3/kg)(��ѹ��һ��ֵ)
static double F_HX2VHP(VDOUBLE& te);
//��֪����(kJ/kg)�͸ɶ�(100%)����ѹ��(MPa)(ȱʡ�ǵ�ѹ��һ��ֵ)
static double F_HX2P(VDOUBLE& t);
//��֪����(kJ/kg)�͸ɶ�(100%)�����¶�(��)(ȱʡ�ǵ�ѹ��һ��ֵ)
static double F_HX2T(VDOUBLE& t);
//��֪����(kJ/kg)�͸ɶ�(100%)�������(kJ/(kg.��))(ȱʡ�ǵ�ѹ��һ��ֵ)
static double F_HX2S(VDOUBLE& t);
//��֪����(kJ/kg)�͸ɶ�(100%)�������(m^3/kg)(ȱʡ�ǵ�ѹ��һ��ֵ)
static double F_HX2V(VDOUBLE& t);

//��֪����(kJ/(kg.��))�ͱ���(m^3/kg)����ѹ��(MPa)
static double F_SV2P(VDOUBLE& t);
//��֪����(kJ/(kg.��))�ͱ���(m^3/kg)�����¶�(��)
static double F_SV2T(VDOUBLE& t);
//��֪����(kJ/(kg.��))�ͱ���(m^3/kg)�������(kJ/kg)
static double F_SV2H(VDOUBLE& t);
//��֪����(kJ/(kg.��))�ͱ���(m^3/kg)����ɶ�(100%)
static double F_SV2X(VDOUBLE& t);


//��֪����(kJ/(kg.��))�͸ɶ�(100%)����ѹ��(MPa)(��ѹ��һ��ֵ)
static double F_SX2PLP(VDOUBLE& te);
//��֪����(kJ/(kg.��))�͸ɶ�(100%)����ѹ��(MPa)(��ѹ��һ��ֵ)
static double F_SX2PMP(VDOUBLE& t);
//��֪����(kJ/(kg.��))�͸ɶ�(100%)����ѹ��(MPa)(��ѹ��һ��ֵ)
static double F_SX2PHP(VDOUBLE& t);
//��֪����(kJ/(kg.��))�͸ɶ�(100%)����ѹ��(MPa)(ȱʡ�ǵ�ѹ��һ��ֵ)
static double F_SX2P(VDOUBLE& t);
//��֪����(kJ/(kg.��))�͸ɶ�(100%)�����¶�(��)(��ѹ��һ��ֵ)
static double F_SX2TLP(VDOUBLE& t);
//��֪����(kJ/(kg.��))�͸ɶ�(100%)�����¶�(��)(��ѹ��һ��ֵ)
static double F_SX2TMP(VDOUBLE& t);
//��֪����(kJ/(kg.��))�͸ɶ�(100%)�����¶�(��)(��ѹ��һ��ֵ)
static double F_SX2THP(VDOUBLE& t);
//��֪����(kJ/(kg.��))�͸ɶ�(100%)�����¶�(��)(ȱʡ�ǵ�ѹ��һ��ֵ)
static double F_SX2T(VDOUBLE& t);
//��֪����(kJ/(kg.��))�͸ɶ�(100%)�������(kJ/kg)(��ѹ��һ��ֵ)
static double F_SX2HLP(VDOUBLE& t);
//��֪����(kJ/(kg.��))�͸ɶ�(100%)�������(kJ/kg)(��ѹ��һ��ֵ)
static double F_SX2HMP(VDOUBLE& t);
//��֪����(kJ/(kg.��))�͸ɶ�(100%)�������(kJ/kg)(��ѹ��һ��ֵ)
static double F_SX2HHP(VDOUBLE& t);
//��֪����(kJ/(kg.��))�͸ɶ�(100%)�������(kJ/kg)(ȱʡ�ǵ�ѹ��һ��ֵ)
static double F_SX2H(VDOUBLE& t);
//��֪����(kJ/(kg.��))�͸ɶ�(100%)�������(m^3/kg)(��ѹ��һ��ֵ)
static double F_SX2VLP(VDOUBLE& t);
//��֪����(kJ/(kg.��))�͸ɶ�(100%)�������(m^3/kg)(��ѹ��һ��ֵ)
static double F_SX2VMP(VDOUBLE& t);
//��֪����(kJ/(kg.��))�͸ɶ�(100%)�������(m^3/kg)(��ѹ��һ��ֵ)
static double F_SX2VHP(VDOUBLE& t);
//��֪����(kJ/(kg.��))�͸ɶ�(100%)�������(m^3/kg)(ȱʡ�ǵ�ѹ��һ��ֵ)
static double F_SX2V(VDOUBLE& t);

//��֪����(m^3/kg)�͸ɶ�(100%)����ѹ��(MPa)(��ѹ��һ��ֵ)
static double F_VX2PLP(VDOUBLE& t);
//��֪����(m^3/kg)�͸ɶ�(100%)����ѹ��(MPa)(�͸�ѹ��һ��ֵ)
static double F_VX2PHP(VDOUBLE& t);
//��֪����(m^3/kg)�͸ɶ�(100%)����ѹ��(MPa)(ȱʡ�ǵ�ѹ��һ��ֵ)
static double F_VX2P(VDOUBLE& t);
//��֪����(m^3/kg)�͸ɶ�(100%)�����¶�(��)(��ѹ��һ��ֵ)
static double F_VX2TLP(VDOUBLE& t);
//��֪����(m^3/kg)�͸ɶ�(100%)�����¶�(��)(��ѹ��һ��ֵ)
static double F_VX2THP(VDOUBLE& t);
//��֪����(m^3/kg)�͸ɶ�(100%)�����¶�(��)(ȱʡ�ǵ�ѹ��һ��ֵ)
static double F_VX2T(VDOUBLE& t);
//��֪����(m^3/kg)�͸ɶ�(100%)�������(kJ/kg)(��ѹ��һ��ֵ)
static double F_VX2HLP(VDOUBLE& t);
//��֪����(m^3/kg)�͸ɶ�(100%)�������(kJ/kg)(��ѹ��һ��ֵ)
static double F_VX2HHP(VDOUBLE& t);
//��֪����(m^3/kg)�͸ɶ�(100%)�������(kJ/kg)(ȱʡ�ǵ�ѹ��һ��ֵ)
static double F_VX2H(VDOUBLE& t);
//��֪����(m^3/kg)�͸ɶ�(100%)�������(kJ/(kg.��))(��ѹ��һ��ֵ)
static double F_VX2SLP(VDOUBLE& t);
//��֪����(m^3/kg)�͸ɶ�(100%)�������(kJ/(kg.��))(��ѹ��һ��ֵ)
static double F_VX2SHP(VDOUBLE& t);
//��֪����(m^3/kg)�͸ɶ�(100%)�������(kJ/(kg.��))(ȱʡ�ǵ�ѹ��һ��ֵ)
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
////��ѧ����
///*******************************************************************************/
//
//double pt2h97(VDOUBLE& t)
//{
//	double h;
//	int r;
//	PT2H97(t.front(),*(++t.begin()),h,r);
//	return h;
//}
//ƽ������
double SQRT(VDOUBLE& t)
{
    return sqrt(t.front());
}

//����ֵ����
double ABS(VDOUBLE& t)
{
    return abs(t.front());
}

//ln����
double LN(VDOUBLE& t)
{
    return log(t.front());
}

//�ݺ���
double POW(VDOUBLE& t)
{
    return pow(t.front(),*(++t.begin()));
}

//log10����
double LOG(VDOUBLE& t)
{
    return log10(t.front());
}

//ָ������
double EXP(VDOUBLE& t)
{
    return exp(t.front());
}

//����
double SIN(VDOUBLE& t)
{
    return sin(t.front());
}

//˫������
double SINH(VDOUBLE& t)
{
    return sinh(t.front());
}

//������
double ASIN(VDOUBLE& t)
{
    return asin(t.front());
}

//����
double COS(VDOUBLE& t)
{
    return cos(t.front());
}

//˫������
double COSH(VDOUBLE& t)
{
    return cosh(t.front());
}

//������
double ACOS(VDOUBLE& t)
{
    return asin(t.front());
}

//����
double TAN(VDOUBLE& t)
{
    return tan(t.front());
}

//������
double ATON(VDOUBLE& t)
{
    return atan(t.front());
}

//˫������
double TANH(VDOUBLE& t)
{
    return tanh(t.front());
}


//�׳�
double FACTORIAL(VDOUBLE& t)
{
    double value,index;

    index=t.front();
    value=1;

    for(int i=1;i<=index;i++)
        value*=i;

    return value;
}

//�����ֵ
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

//����Сֵ
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



//������ѧ�쳣
//int _matherr(exception *except )
//{
//    throw CExcept(" math error ");
//    return 0;
//}



/*******************************************************************************/
//������¶Ⱥ�ѹ��ת������
/*******************************************************************************/

//���¶���ѹ��
double PST(VDOUBLE& t)
{
    return pst(t.front());
}

//��ѹ�����¶�
double TSP(VDOUBLE& t)
{
    return tsp(t.front());
}

/*******************************************************************************/
//���¶Ⱥ�ѹ�����������������
/*******************************************************************************/

//���¶�ѹ����������
double AHPT(VDOUBLE& t)
{
    double ha,sa,va;
    ptparam(t.front(),*(++t.begin()),&ha,&sa,&va);
    return ha;
}

//���¶�ѹ����������
double ASPT(VDOUBLE& t)
{
    double ha,sa,va;
    ptparam(t.front(),*(++t.begin()),&ha,&sa,&va);
    return sa;
}

//���¶�ѹ�����������
double AVPT(VDOUBLE& t)
{
    double ha,sa,va;
    ptparam(t.front(),*(++t.begin()),&ha,&sa,&va);
    return va;
}

/*******************************************************************************/
//��ѹ���������������������
/*******************************************************************************/

//��ѹ�����������¶�
double ATPS(VDOUBLE& t)
{
    double ta,ha,va;
    psparam(t.front(),*(++t.begin()),&ta,&ha,&va);
    return ta;
}

//��ѹ������������
double AHPS(VDOUBLE& t)
{
    double ta,ha,va;
    psparam(t.front(),*(++t.begin()),&ta,&ha,&va);
    return ha;
}

//��ѹ�������������
double AVPS(VDOUBLE& t)
{
    double ta,ha,va;
    psparam(t.front(),*(++t.begin()),&ta,&ha,&va);
    return va;
}

/*******************************************************************************/
//��ѹ���������������������
/*******************************************************************************/


//��ѹ�����������¶�
double ATPH(VDOUBLE& t)
{
    double ta,sa,va;
    phparam(t.front(),*(++t.begin()),&ta,&sa,&va);
    return ta;
}

//��ѹ������������
double ASPH(VDOUBLE& t)
{
    double ta,sa,va;
    phparam(t.front(),*(++t.begin()),&ta,&sa,&va);
    return sa;
}

//��ѹ�������������
double AVPH(VDOUBLE& t)
{
    double ta,sa,va;
    phparam(t.front(),*(++t.begin()),&ta,&sa,&va);
    return sa;
}


/*******************************************************************************/
//���غ������������������
/*******************************************************************************/

//���غ���������ѹ��
double APHS(VDOUBLE& t)
{
    double pa,ta,va;
    hsparam(t.front(),*(++t.begin()),&pa,&ta,&va);
    return pa;
}

//���غ����������¶�
double ATHS(VDOUBLE& t)
{
    double pa,ta,va;
    hsparam(t.front(),*(++t.begin()),&pa,&ta,&va);
    return ta;
}

//���غ������������
double AVHS(VDOUBLE& t)
{
    double pa,ta,va;
    hsparam(t.front(),*(++t.begin()),&pa,&ta,&va);
    return va;
}


/*******************************************************************************/
//���¶Ⱥ�ѹ����ˮ����������
/*******************************************************************************/

//���¶�ѹ����ˮ��
double WHPT(VDOUBLE& t)
{
    double ha,sa,va;
    waterparam(t.front(),*(++t.begin()),&ha,&sa,&va);
    return ha;
}

//���¶�ѹ����ˮ��
double WSPT(VDOUBLE& t)
{
    double ha,sa,va;
    waterparam(t.front(),*(++t.begin()),&ha,&sa,&va);
    return sa;
}

//���¶�ѹ����ˮ����
double WVPT(VDOUBLE& t)
{
    double ha,sa,va;
    waterparam(t.front(),*(++t.begin()),&ha,&sa,&va);
    return va;
}

/*******************************************************************************/
//���¶Ⱥ�ѹ����ˮ������������
/*******************************************************************************/
//���¶�ѹ����ˮ����
double GHPT(VDOUBLE& t)
{
    double ha,sa,va;
    vaporparam(t.front(),*(++t.begin()),&ha,&sa,&va);
    return ha;
}

//���¶�ѹ����ˮ����
double GSPT(VDOUBLE& t)
{
    double ha,sa,va;
    vaporparam(t.front(),*(++t.begin()),&ha,&sa,&va);
    return sa;
}

//���¶�ѹ����ˮ������
double GVPT(VDOUBLE& t)
{
    double ha,sa,va;
    vaporparam(t.front(),*(++t.begin()),&ha,&sa,&va);
    return va;
}

//��֪ѹ��(MPa)�����Ӧ�����¶�(��)
double F_P2T(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2T(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ����ˮ����(kJ/kg)
double F_P2HL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2HL(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ����������(kJ/kg)
double F_P2HG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2HG(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ����ˮ����(kJ/(kg.��))
double F_P2SL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2SL(t.front(),dRet,nRang);
    return dRet;	
}
//��֪ѹ��(MPa)�����Ӧ����������(kJ/(kg.��))
double F_P2SG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2SG(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ����ˮ����(m^3/kg)
double F_P2VL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2VL(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ����������(m^3/kg)
double F_P2VG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2VG(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ����ˮ��ѹ����(kJ/(kg.��))
double F_P2CPL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2CPL(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ��������ѹ����(kJ/(kg.��))
double F_P2CPG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2CPG(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ����ˮ���ݱ���(kJ/(kg.��))
double F_P2CVL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2CVL(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ���������ݱ���(kJ/(kg.��))
double F_P2CVG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2CVG(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ����ˮ����(kJ/kg)
double F_P2EL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2EL(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ����������(kJ/kg)
double F_P2EG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2EG(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ����ˮ����(m/s)
double F_P2SSPL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2SSPL(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ����������(m/s)
double F_P2SSPG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2SSPG(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ����ˮ����ָ��
double F_P2KSL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2KSL(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ����������ָ��
double F_P2KSG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2KSG(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ����ˮ����ճ��(Pa.s)
double F_P2ETAL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2ETAL(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ����������ճ��(Pa.s)
double F_P2ETAG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2ETAG(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ����ˮ�˶�ճ��(m^2/s)
double F_P2UL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2UL(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ�������˶�ճ��(m^2/s)
double F_P2UG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2UG(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ�������˶�ճ��(m^2/s)
double F_P2TP2UG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2UG(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ����ˮ����ϵ��(W/(m.��))
double F_P2RAMDL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2RAMDL(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ����������ϵ��(W/(m.��))
double F_P2RAMDG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2RAMDG(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ����ˮ��������
double F_P2PRNL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2PRNL(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ��������������
double F_P2PRNG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2PRNG(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ����ˮ��糣��
double F_P2EPSL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2EPSL(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ��������糣��
double F_P2EPSG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2EPSG(t.front(),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ����ˮ������
double F_P2NL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2NL(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�����Ӧ������������
double F_P2NG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    P2NG(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)���¶�(��)�������(kJ/kg)
double F_PT2H(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2H(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)���¶�(��)�������(kJ/(kg.��))
double F_PT2S(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2S(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)���¶�(��)�������(m^3/kg)
double F_PT2V(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2V(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)���¶�(��)����ɶ�(100%)
double F_PT2X(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2X(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)���¶�(��)����ѹ����(kJ/(kg.��))
double F_PT2CP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2CP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)���¶�(��)�����ݱ���(kJ/(kg.��))
double F_PT2CV(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2CV(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)���¶�(��)��������(kJ/kg)
double F_PT2E(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2E(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)���¶�(��)��������(m/s)
double F_PT2SSP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2SSP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)���¶�(��)������ָ��
double F_PT2KS(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2KS(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)���¶�(��)������ճ��(Pa.s)
double F_PT2ETA(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2ETA(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)���¶�(��)�����˶�ճ��(m^2/s)
double F_PT2U(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2U(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)���¶�(��)�����ȴ���ϵ�� (W/(m.��))
double F_PT2RAMD(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2RAMD(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)���¶�(��)������������
double F_PT2PRN(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2PRN(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)���¶�(��)�����糣��
double F_PT2EPS(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2EPS(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)���¶�(��)����������
double F_PT2N(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PT2N(t.front(),*(++t.begin()),t[2],dRet,nRang);
    return dRet;
}

//��֪ѹ��(MPa)�ͱ���(kJ/kg)�����¶�(��)
double F_PH2T(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PH2T(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�ͱ���(kJ/kg)�������(kJ/(kg.��))
double F_PH2S(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PH2S(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�ͱ���(kJ/kg)�������(m^3/kg)
double F_PH2V(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PH2V(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�ͱ���(kJ/kg)����ɶ�(100%)
double F_PH2X(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PH2X(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}

//��֪ѹ��(MPa)�ͱ���(kJ/(kg.��))�����¶�(��)
double F_PS2T(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PS2T(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�ͱ���(kJ/(kg.��))�������(kJ/kg)
double F_PS2H(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PS2H(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�ͱ���(kJ/(kg.��))�������(m^3/kg)
double F_PS2V(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PS2V(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�ͱ���(kJ/(kg.��))����ɶ�(100%)
double F_PS2X(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PS2X(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}

//��֪ѹ��(MPa)�ͱ���(m^3/kg)�����¶�(��)
double F_PV2T(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PV2T(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�ͱ���(m^3/kg)�������(kJ/kg)
double F_PV2H(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PV2H(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�ͱ���(m^3/kg)�������(m^3/kg)
double F_PV2S(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PV2S(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�ͱ���(m^3/kg)����ɶ�(100%)
double F_PV2X(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PV2X(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}

//��֪ѹ��(MPa)�͸ɶ�(100%)�����¶�(��)
double F_PX2T(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PX2T(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�͸ɶ�(100%)�������(kJ/kg)
double F_PX2H(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PX2H(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�͸ɶ�(100%)�������(kJ/(kg.��))
double F_PX2S(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PX2S(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪ѹ��(MPa)�͸ɶ�(100%)�������(m^3/kg)
double F_PX2V(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    PX2V(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}

//��֪�¶�(��)���󱥺�ѹ��(MPa)��
double F_T2P(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2P(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�ˮ����(kJ/kg)
double F_T2HL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2HL(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�������(kJ/kg)
double F_T2HG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2HG(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�ˮ����(kJ/(kg.��))
double F_T2SL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2SL(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�������(kJ/(kg.��))
double F_T2SG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2SG(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�ˮ����(m^3/kg)
double F_T2VL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2VL(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�������(m^3/kg)
double F_T2VG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2VG(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�ˮ��ѹ����(kJ/(kg.��))
double F_T2CPL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2CPL(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�����ѹ����(kJ/(kg.��))
double F_T2CPG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2CPG(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�ˮ���ݱ���(kJ/(kg.��))
double F_T2CVL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2CVL(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺������ݱ���(kJ/(kg.��))
double F_T2CVG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2CVG(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�ˮ����(kJ/kg)
double F_T2EL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2EL(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�������(kJ/kg)
double F_T2EG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2EG(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�ˮ����(m/s)
double F_T2SSPL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2SSPL(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�������(m/s)
double F_T2SSPG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2SSPG(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�ˮ����ָ��
double F_T2KSL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2KSL(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�������ָ��
double F_T2KSG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2KSG(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�ˮ����ճ��(Pa.s)
double F_T2ETAL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2KSG(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�������ճ��(Pa.s)
double F_T2ETAG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2ETAG(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�ˮ�˶�ճ��(m^2/s)
double F_T2UL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2UL(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺����˶�ճ��(m^2/s)
double F_T2UG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2UG(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�ˮ����ϵ��(W/(m.��))
double F_T2RAMDL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2RAMDL(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�������ϵ��(W/(m.��))
double F_T2RAMDG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2RAMDG(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�ˮ��������
double F_T2PRNL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2PRNL(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�����������
double F_T2PRNG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2PRNL(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�ˮ��糣��
double F_T2EPSL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2EPSL(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�����糣��
double F_T2EPSG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2EPSG(t.front(),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�ˮ������
double F_T2NL(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2NL(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺���������
double F_T2NG(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2NG(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)���󱥺�ˮ��������(N/m)
double F_T2SURFT(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    T2SURFT(t.front(),dRet,nRang);
    return dRet;
}

//��֪�¶�(��)�ͱ���(kJ/kg)����ѹ��(MPa)(��ѹ��һ��ֵ)
double F_TH2PLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TH2PLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)�ͱ���(kJ/kg)�������(kJ/(kg.��))(��ѹ��һ��ֵ)
double F_TH2SLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TH2SLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)�ͱ���(kJ/kg)�������(m^3/kg)(��ѹ��һ��ֵ)
double F_TH2VLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TH2VLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)�ͱ���(kJ/kg)����ѹ��(MPa)(��ѹ��һ��ֵ)
double F_TH2PHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TH2PHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)�ͱ���(kJ/kg)�������(kJ/(kg.��))(��ѹ��һ��ֵ)
double F_TH2SHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TH2SHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)�ͱ���(kJ/kg)�������(m^3/kg)(��ѹ��һ��ֵ)
double F_TH2VHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TH2VHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)�ͱ���(kJ/kg)����ѹ��(MPa)(ȱʡΪ��ѹ��һ��ֵ)
double F_TH2P(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TH2P(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)�ͱ���(kJ/kg)�������(kJ/(kg.��))(ȱʡΪ��ѹ��һ��ֵ)
double F_TH2S(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TH2S(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)�ͱ���(kJ/kg)�������(m^3/kg)(ȱʡΪ��ѹ��һ��ֵ)
double F_TH2V(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TH2V(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)�ͱ���(kJ/kg)����ɶ�(100%)
double F_TH2X(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TH2X(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}

//��֪�¶�(��)�ͱ���(kJ/(kg.��))����ѹ��(MPa)(��ѹ��һ��ֵ)
double F_TS2PLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TS2PLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)�ͱ���(kJ/(kg.��))�������(kJ/kg)(��ѹ��һ��ֵ)
double F_TS2HLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TS2HLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)�ͱ���(kJ/(kg.��))�������(m^3/kg)(��ѹ��һ��ֵ)
double F_TS2VLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TS2VLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)�ͱ���(kJ/(kg.��))����ѹ��(MPa)(��ѹ��һ��ֵ)
double F_TS2PHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TS2PHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)�ͱ���(kJ/(kg.��))�������(kJ/kg)(��ѹ��һ��ֵ)
double F_TS2HHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TS2HHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)�ͱ���(kJ/(kg.��))�������(m^3/kg)(��ѹ��һ��ֵ)
double F_TS2VHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TS2VHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)�ͱ���(kJ/(kg.��))����ѹ��(MPa)(ȱʡΪ��ѹ��һ��ֵ)
double F_TS2P(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TS2P(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)�ͱ���(kJ/(kg.��))�������(kJ/kg)(ȱʡΪ��ѹ��һ��ֵ)
double F_TS2H(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TS2H(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)�ͱ���(kJ/(kg.��))�������(m^3/kg)(ȱʡΪ��ѹ��һ��ֵ)
double F_TS2V(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TS2V(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)�ͱ���(kJ/(kg.��))����ɶ�(100%)
double F_TS2X(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TS2X(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}

//��֪�¶�(��)�ͱ���(m^3/kg)����ѹ��(MPa)
double F_TV2P(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TV2P(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)�ͱ���(m^3/kg)�������(kJ/kg)
double F_TV2H(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TV2H(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)�ͱ���(m^3/kg)�������(kJ/(kg.��))
double F_TV2S(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TV2S(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)�ͱ���(m^3/kg)����ɶ�(100%)
double F_TV2X(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TV2X(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}

//��֪�¶�(��)�͸ɶ�(100%)����ѹ��(MPa)
double F_TX2P(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TX2P(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)�͸ɶ�(100%)�������(kJ/kg)
double F_TX2H(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TX2H(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)�͸ɶ�(100%)�������(kJ/(kg.��))
double F_TX2S(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TX2S(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪�¶�(��)�͸ɶ�(100%)�������(m^3/kg)
double F_TX2V(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    TX2V(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}

//��֪����(kJ/kg)�ͱ���(kJ/(kg.��))����ѹ��(MPa)
double F_HS2P(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HS2P(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/kg)�ͱ���(kJ/(kg.��))�����¶�(��)
double F_HS2T(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HS2T(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/kg)�ͱ���(kJ/(kg.��))�������(m^3/kg)
double F_HS2V(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HS2V(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/kg)�ͱ���(kJ/(kg.��))����ɶ�(100%)
double F_HS2X(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HS2X(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}

//��֪����(kJ/kg)�ͱ���(m^3/kg)����ѹ��(MPa)
double F_HV2P(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HV2P(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/kg)�ͱ���(m^3/kg)�����¶�(��)
double F_HV2T(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HV2T(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/kg)�ͱ���(m^3/kg)�������(kJ/(kg.��))
double F_HV2S(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HV2S(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/kg)�ͱ���(m^3/kg)����ɶ�(100%)
double F_HV2X(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HV2X(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}

//��֪����(kJ/kg)�͸ɶ�(100%)����ѹ��(MPa)(��ѹ��һ��ֵ)
double F_HX2PLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HX2PLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/kg)�͸ɶ�(100%)�����¶�(��)(��ѹ��һ��ֵ)
double F_HX2TLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HX2TLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/kg)�͸ɶ�(100%)�������(kJ/(kg.��))(��ѹ��һ��ֵ)
double F_HX2SLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HX2SLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/kg)�͸ɶ�(100%)�������(m^3/kg)(��ѹ��һ��ֵ)
double F_HX2VLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HX2VLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/kg)�͸ɶ�(100%)����ѹ��(MPa)(��ѹ��һ��ֵ)
double F_HX2PHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HX2PHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/kg)�͸ɶ�(100%)�����¶�(��)(��ѹ��һ��ֵ)
double F_HX2THP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HX2THP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/kg)�͸ɶ�(100%)�������(kJ/(kg.��))(��ѹ��һ��ֵ)
double F_HX2SHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HX2SHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/kg)�͸ɶ�(100%)�������(m^3/kg)(��ѹ��һ��ֵ)
double F_HX2VHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HX2VHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/kg)�͸ɶ�(100%)����ѹ��(MPa)(ȱʡ�ǵ�ѹ��һ��ֵ)
double F_HX2P(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HX2P(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/kg)�͸ɶ�(100%)�����¶�(��)(ȱʡ�ǵ�ѹ��һ��ֵ)
double F_HX2T(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HX2T(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/kg)�͸ɶ�(100%)�������(kJ/(kg.��))(ȱʡ�ǵ�ѹ��һ��ֵ)
double F_HX2S(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HX2S(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/kg)�͸ɶ�(100%)�������(m^3/kg)(ȱʡ�ǵ�ѹ��һ��ֵ)
double F_HX2V(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    HX2V(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}

//��֪����(kJ/(kg.��))�ͱ���(m^3/kg)����ѹ��(MPa)
double F_SV2P(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SV2P(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/(kg.��))�ͱ���(m^3/kg)�����¶�(��)
double F_SV2T(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SV2T(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/(kg.��))�ͱ���(m^3/kg)�������(kJ/kg)
double F_SV2H(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SV2H(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/(kg.��))�ͱ���(m^3/kg)����ɶ�(100%)
double F_SV2X(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SV2X(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}


//��֪����(kJ/(kg.��))�͸ɶ�(100%)����ѹ��(MPa)(��ѹ��һ��ֵ)
double F_SX2PLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2PLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/(kg.��))�͸ɶ�(100%)����ѹ��(MPa)(��ѹ��һ��ֵ)
double F_SX2PMP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2PMP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/(kg.��))�͸ɶ�(100%)����ѹ��(MPa)(��ѹ��һ��ֵ)
double F_SX2PHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2PHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/(kg.��))�͸ɶ�(100%)����ѹ��(MPa)(ȱʡ�ǵ�ѹ��һ��ֵ)
double F_SX2P(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2P(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/(kg.��))�͸ɶ�(100%)�����¶�(��)(��ѹ��һ��ֵ)
double F_SX2TLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2TLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/(kg.��))�͸ɶ�(100%)�����¶�(��)(��ѹ��һ��ֵ)
double F_SX2TMP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2TMP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/(kg.��))�͸ɶ�(100%)�����¶�(��)(��ѹ��һ��ֵ)
double F_SX2THP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2THP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/(kg.��))�͸ɶ�(100%)�����¶�(��)(ȱʡ�ǵ�ѹ��һ��ֵ)
double F_SX2T(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2T(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/(kg.��))�͸ɶ�(100%)�������(kJ/kg)(��ѹ��һ��ֵ)
double F_SX2HLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2HLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/(kg.��))�͸ɶ�(100%)�������(kJ/kg)(��ѹ��һ��ֵ)
double F_SX2HMP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2HMP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/(kg.��))�͸ɶ�(100%)�������(kJ/kg)(��ѹ��һ��ֵ)
double F_SX2HHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2HHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/(kg.��))�͸ɶ�(100%)�������(kJ/kg)(ȱʡ�ǵ�ѹ��һ��ֵ)
double F_SX2H(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2H(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/(kg.��))�͸ɶ�(100%)�������(m^3/kg)(��ѹ��һ��ֵ)
double F_SX2VLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2VLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/(kg.��))�͸ɶ�(100%)�������(m^3/kg)(��ѹ��һ��ֵ)
double F_SX2VMP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2VMP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/(kg.��))�͸ɶ�(100%)�������(m^3/kg)(��ѹ��һ��ֵ)
double F_SX2VHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2VHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(kJ/(kg.��))�͸ɶ�(100%)�������(m^3/kg)(ȱʡ�ǵ�ѹ��һ��ֵ)
double F_SX2V(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    SX2V(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}

//��֪����(m^3/kg)�͸ɶ�(100%)����ѹ��(MPa)(��ѹ��һ��ֵ)
double F_VX2PLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    VX2PLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(m^3/kg)�͸ɶ�(100%)����ѹ��(MPa)(�͸�ѹ��һ��ֵ)
double F_VX2PHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    VX2PHP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(m^3/kg)�͸ɶ�(100%)����ѹ��(MPa)(ȱʡ�ǵ�ѹ��һ��ֵ)
double F_VX2P(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    VX2P(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(m^3/kg)�͸ɶ�(100%)�����¶�(��)(��ѹ��һ��ֵ)
double F_VX2TLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    VX2TLP(t.front(),*(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(m^3/kg)�͸ɶ�(100%)�����¶�(��)(��ѹ��һ��ֵ)
double F_VX2THP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    VX2THP(t.front(), *(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(m^3/kg)�͸ɶ�(100%)�����¶�(��)(ȱʡ�ǵ�ѹ��һ��ֵ)
double F_VX2T(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    VX2T(t.front(), *(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(m^3/kg)�͸ɶ�(100%)�������(kJ/kg)(��ѹ��һ��ֵ)
double F_VX2HLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    VX2HLP(t.front(), *(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(m^3/kg)�͸ɶ�(100%)�������(kJ/kg)(��ѹ��һ��ֵ)
double F_VX2HHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    VX2HHP(t.front(), *(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(m^3/kg)�͸ɶ�(100%)�������(kJ/kg)(ȱʡ�ǵ�ѹ��һ��ֵ)
double F_VX2H(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    VX2H(t.front(), *(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(m^3/kg)�͸ɶ�(100%)�������(kJ/(kg.��))(��ѹ��һ��ֵ)
double F_VX2SLP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    VX2SLP(t.front(), *(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(m^3/kg)�͸ɶ�(100%)�������(kJ/(kg.��))(��ѹ��һ��ֵ)
double F_VX2SHP(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    VX2SHP(t.front(), *(++t.begin()),dRet,nRang);
    return dRet;
}
//��֪����(m^3/kg)�͸ɶ�(100%)�������(kJ/(kg.��))(ȱʡ�ǵ�ѹ��һ��ֵ)
double F_VX2S(VDOUBLE& t)
{
    double dRet=0;
    int nRang=RANG;
    VX2S(t.front(), *(++t.begin()),dRet,nRang);
    return dRet;
}
