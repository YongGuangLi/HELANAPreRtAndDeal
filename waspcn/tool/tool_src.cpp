#include "waspcn.h"
#include "tool_src.h"
using namespace waspcn;

#include <iostream>
using namespace std;

namespace ToolSrc
{
    int OnHelp(void)
    {
        std::cout <<"��ѡ��������:"<<std::endl;
        std::cout <<"    1. ��֪�¶ȡ�������"<<std::endl;
        std::cout <<"    2. ��֪ѹ����������"<<std::endl;
        std::cout <<"    3. ��֪�¶ȡ�ѹ��������"<<std::endl;
        std::cout <<"    4. ��֪�¶ȡ�����������"<<std::endl;
        std::cout <<"    5. ��֪�¶ȡ�����������"<<std::endl;
        std::cout <<"    6. ��֪�¶ȡ�����������"<<std::endl;
        std::cout <<"    7. ��֪ѹ�����ɶ�������"<<std::endl;
        std::cout <<"    8. ��֪ѹ��������������"<<std::endl;
        std::cout <<"    9. �Ѻ�ѹ��������������"<<std::endl;
        std::cout <<"    10.��֪���ʡ�����������"<<std::endl;
        std::cout <<"    0.�˳�"<<std::endl;

        std::cout <<"\n��ѡ��:"<<std::flush;
        int nInput;
        std::cin >>nInput;
        return nInput;
    }

    void OnWaspcn(int &nType)
    {
        switch(nType)
        {
        case 0:
            break;
        case 1:
            OnCaseWaspcn1();
            break;
        case 2:
            OnCaseWaspcn2();
            break;
        case 3:
            OnCaseWaspcn3();
            break;
        case 4:
            OnCaseWaspcn4();
            break;
        case 5:
            OnCaseWaspcn5();
            break;
        case 6:
            OnCaseWaspcn6();
            break;
        case 7:
            OnCaseWaspcn7();
            break;
        case 8:
            OnCaseWaspcn8();
            break;
        case 9:
            OnCaseWaspcn9();
            break;
        case 10:
            OnCaseWaspcn10();
            break;
        default:
            std::cout <<"ĩ֪����������ѡ��"<<std::endl;
        }
    }

    void OnCaseWaspcn1(void)        // 1. ��֪�¶ȡ�������
    {
        double T;
        double P;
        double VL;
        double VG;
        double HL;
        double HG;
        double SL;
        double SG;
        std::cout <<"������¶�:"<<std::flush;
        std::cin >>T;
        int nRange;
        T2P(T, P, nRange);
        std::cout <<"����"<<nRange<<std::endl;
        std::cout <<"����ѹ��:"<<P<<std::endl;
        T2VL(T, VL, nRange);
        T2VG(T, VG, nRange);
        T2HL(T, HL, nRange);
        T2HG(T, HG, nRange);
        T2SL(T, SL, nRange);
        T2SG(T, SG, nRange);
        std::cout <<"����ˮ����:"<<VL<<std::endl;
        std::cout <<"����������:"<<VG<<std::endl;
        std::cout <<"����ˮ����:"<<HL<<std::endl;
        std::cout <<"����������:"<<HG<<std::endl;
        std::cout <<"����ˮ����:"<<SL<<std::endl;
        std::cout <<"����������:"<<SG<<std::endl;
    }

    void OnCaseWaspcn2(void)        // 2. ��֪ѹ����������
    {
        double P;
        double T;
        double VL;
        double VG;
        double HL;
        double HG;
        double SL;
        double SG;
        int nRange;
        std::cout <<"������ѹ��:"<<std::flush;
        cin >>P;
        P2T(P, T, nRange);
        std::cout <<"����"<<nRange<<std::endl;
        std::cout <<"�����¶�Ϊ:"<<T<<std::endl;
        P2VL(P, VL, nRange);
        P2VG(P, VG, nRange);
        P2HL(P, HL, nRange);
        P2HG(P, HG, nRange);
        P2SL(P, SL, nRange);
        P2SG(P, SG, nRange);
        std::cout <<"����ˮ����:"<<VL<<std::endl;
        std::cout <<"����������:"<<VG<<std::endl;
        std::cout <<"����ˮ����:"<<HL<<std::endl;
        std::cout <<"����������:"<<HG<<std::endl;
        std::cout <<"����ˮ����:"<<SL<<std::endl;
        std::cout <<"����������:"<<SG<<std::endl;
    }

    void OnCaseWaspcn3(void)            // 3. ��֪�¶ȡ�ѹ��������
    {
        double T;
        double P;
        std::cout <<"�������¶�:"<<std::flush;
        cin >>T;
        std::cout <<"������ѹ��:"<<std::flush;
        cin >>P;
        double H;
        double S;
        double V;
        int nRange;
        PT2H(P, T, H, nRange);
        PT2S(P, T, S, nRange);
        PT2V(P, T, V, nRange);
        std::cout <<"����"<<nRange<<std::endl;
        std::cout <<"����:"<<V<<std::endl;
        std::cout <<"����:"<<H<<std::endl;
        std::cout <<"����:"<<S<<std::endl;
        double CP;
        double CV;
        PT2CP(P, T, CP, nRange);
        std::cout <<"���ݱ���:"<<CP<<std::endl;
        PT2CV(P, T, CV, nRange);
        std::cout <<"��ѹ����:"<<CV<<std::endl;

        double E, SSP;
        PT2MV(P, T, H, S, V, E, CP, CV, SSP, nRange);
        if (128 == nRange)
        {
            PT2HMV(P,T,H);
            PT2SMV(P,T,S);
            PT2VMV(P,T,V);
            std::cout <<std::endl<<"��Ӧ����̬��������:"<<std::endl;
            std::cout <<"����:"<<V<<std::endl;
            std::cout <<"����:"<<H<<std::endl;
            std::cout <<"����:"<<S<<std::endl;
        }
    }

    void OnCaseWaspcn4(void)            // 4. ��֪�¶ȡ�����������
    {
        double T;
        double V;
        std::cout <<"�������¶�:"<<std::flush;
        cin >>T;
        std::cout <<"���������:"<<std::flush;
        cin >>V;
        double P;
        double H;
        double S;
        int nRange;
        TV2P(T, V, P, nRange);
        TV2H(T, V, H, nRange);
        TV2S(T, V, S, nRange);
        std::cout <<"����"<<nRange<<std::endl;
        std::cout <<"ѹ��:"<<P<<std::endl;
        std::cout <<"����:"<<H<<std::endl;
        std::cout <<"����:"<<S<<std::endl;
        if (4 == nRange)
        {
            double X;
            TV2X(T, V, X, nRange);
            if (-1 == X)
            {
                if (4 == nRange)
                {
                    std::cout <<"�ɶȣ�δ֪"<<std::endl;
                }
            } else {
                std::cout <<"�ɶ�:"<<X<<std::endl;
            }
        }
    }

    void OnCaseWaspcn5(void)                // 5. ��֪�¶ȡ�����������
    {
        double T;
        double H;
        int nRange;
        std::cout <<"�������¶�:"<<std::flush;
        cin >>T;
        std::cout <<"���������:"<<std::flush;
        cin >>H;
        double P;
        TH2P(T, H, P, nRange);
        std::cout <<"����"<<nRange<<std::endl;
        std::cout <<"ѹ��:"<<P<<std::endl;
        double S;
        TH2S(T, H, S, nRange);
        std::cout <<"����:"<<S<<std::endl;
        double V;
        TH2V(T, H, V, nRange);
        std::cout <<"����:"<<V<<std::endl;
        double X;
        TH2X(T, H, X, nRange);
        if (-1 == X)
        {
            if (4 == nRange)
            {
                std::cout <<"�ɶȣ�δ֪"<<std::endl;
            }
        } else {
            std::cout <<"�ɶ�:"<<X<<std::endl;
        }
    }

    void OnCaseWaspcn6(void)            // 6. ��֪�¶ȡ�����������
    {
        double T;
        double S;
        int nRange;
        std::cout <<"�������¶�:"<<std::flush;
        cin >>T;
        std::cout <<"���������:"<<std::flush;
        cin >>S;
        double P;
        TS2P(T, S, P, nRange);
        std::cout <<"����"<<nRange<<std::endl;
        std::cout <<"ѹ��:"<<P<<std::endl;
        double H;
        TS2H(T, S, H, nRange);
        std::cout <<"����:"<<H<<std::endl;
        double V;
        TS2V(T, S, V, nRange);
        std::cout <<"����:"<<V<<std::endl;
        double X;
        TS2X(T, S, X, nRange);
        if (-1 == X)
        {
            if (4 == nRange)
            {
                std::cout <<"�ɶȣ�δ֪"<<std::endl;
            }
        } else {
            std::cout <<"�ɶ�:"<<X<<std::endl;
        }
    }

    void OnCaseWaspcn7(void)                // 7. ��֪ѹ�����ɶ�������
    {
        double P;
        double X;
        int nRange;
        std::cout <<"������ѹ��:"<<std::flush;
        cin >>P;
        std::cout <<"������ɶ�:"<<std::flush;
        cin >>X;
        double T;
        PX2T(P, X, T, nRange);
        std::cout <<"����"<<nRange<<std::endl;
        std::cout <<"�¶�:"<<T<<std::endl;
        double H;
        PX2H(P, X, H, nRange);
        std::cout <<"����:"<<H<<std::endl;
        double S;
        PX2S(P, X, S, nRange);
        std::cout <<"����:"<<S<<std::endl;
        double V;
        PX2V(P, X, V, nRange);
        std::cout <<"����:"<<V<<std::endl;
    }

    void OnCaseWaspcn8(void)            // 8. ��֪ѹ��������������
    {
        double P;
        double H;
        int nRange;
        std::cout <<"������ѹ��:"<<std::flush;
        cin >>P;
        std::cout <<"���������:"<<std::flush;
        cin >>H;
        double T;
        PH2T(P, H, T, nRange);
        std::cout <<"����"<<nRange<<std::endl;
        std::cout <<"�¶�:"<<T<<std::endl;
        double S;
        PH2S(P, H, S, nRange);
        std::cout <<"����:"<<S<<std::endl;
        double V;
        PH2V(P, H, V, nRange);
        std::cout <<"����:"<<V<<std::endl;
        double X;
        PH2X(P, H, X, nRange);
        if (-1 == X)
        {
            if (4 == nRange)
            {
                std::cout <<"�ɶȣ�δ֪"<<std::endl;
            }
        } else {
            std::cout <<"�ɶ�:"<<X<<std::endl;
        }
    }

    void OnCaseWaspcn9(void)            // 9. �Ѻ�ѹ��������������
    {
        double P;
        double S;
        int nRange;
        std::cout <<"������ѹ��:"<<std::flush;
        cin >>P;
        std::cout <<"���������:"<<std::flush;
        cin >>S;
        double T;
        PS2T(P, S, T, nRange);
        std::cout <<"����"<<nRange<<std::endl;
        std::cout <<"�¶�:"<<T<<std::endl;
        double H;
        PS2H(P, S, H, nRange);
        std::cout <<"����:"<<H<<std::endl;
        double V;
        PS2V(P, S, V, nRange);
        std::cout <<"����:"<<V<<std::endl;
        double X;
        PS2X(P, S, X, nRange);
        if (-1 == X)
        {
            if (4 == nRange)
            {
                std::cout <<"�ɶȣ�δ֪"<<std::endl;
            }
        } else {
            std::cout <<"�ɶ�:"<<X<<std::endl;
        }
    }

    void OnCaseWaspcn10(void)                // 10.��֪���ʡ�����������
    {
        double H;
        double S;
        int nRange;
        std::cout <<"���������:"<<std::flush;
        cin >>H;
        std::cout <<"���������:"<<std::flush;
        cin >>S;
        double P;
        HS2P(H, S, P, nRange);
        std::cout <<"����"<<nRange<<std::endl;
        std::cout <<"ѹ��:"<<P<<std::endl;
        double T;
        HS2T(H, S, T, nRange);
        std::cout <<"�¶�:"<<T<<std::endl;
        double V;
        HS2V(H, S, V, nRange);
        std::cout <<"����:"<<V<<std::endl;
        double X;
        HS2X(H, S, X, nRange);
        if (-1 == X)
        {
            if (4 == nRange)
            {
                std::cout <<"�ɶȣ�δ֪"<<std::endl;
            }
        } else {
            std::cout <<"�ɶ�:"<<X<<std::endl;
        }
    }
}
