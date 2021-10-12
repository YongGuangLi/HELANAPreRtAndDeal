#ifndef __TOOL_SRC_H__
#define __TOOL_SRC_H__

namespace ToolSrc
{
    // 功能描述：显示系统帮助菜单
    int OnHelp(void);
    // 功能描述：执行指定的服务类型
    void OnWaspcn(int &nType);
    // 功能描述：已知温度、求其它服务类型处理函数
    void OnCaseWaspcn1(void);
    // 功能描述：已知压力、求其它服务类型处理函数
    void OnCaseWaspcn2(void);
    // 功能描述：已知温度、压力求其它服务类型处理函数
    void OnCaseWaspcn3(void);
    // 功能描述：已知温度、比容求其它服务类型处理函数
    void OnCaseWaspcn4(void);
    // 功能描述：已知温度、比焓求其它服务类型处理函数
    void OnCaseWaspcn5(void);
    // 功能描述：已知温度、比熵求其它服务类型处理函数
    void OnCaseWaspcn6(void);
    // 功能描述：已知压力、干度求其它服务类型处理函数
    void OnCaseWaspcn7(void);
    // 功能描述：已知压力、比焓求其它服务类型处理函数
    void OnCaseWaspcn8(void);
    // 功能描述：已和压力、比熵求其它服务类型处理函数
    void OnCaseWaspcn9(void);
    // 功能描述：已知比焓、比熵求其它服务类型处理函数
    void OnCaseWaspcn10(void);
}

#endif//__TOOL_SRC_H__
