/*******************************************************************************
* Copyright（C）,2016-2020,DTXY Tech .Co.Ltd;
* 文 件 名: RDbHead.h
* 文件描述: 数据结构公共头文件
*  作  者 : wangkai
* 创建日期: 2016-11-12 20:46:02
*******************************************************************************/

#ifndef __RDBHEAD_H__
#define __RDBHEAD_H__

//更新服务版本信息
const std::string g_strUpdateServiceVersionSQL = 
	"begin P_SYS_Update_VersionNumber(:v_service_name, :v_version_no, :v_logfile_path,:v_result); end;";
const std::string g_strAlarmScoreSQL = 
		"select id,convert(varchar(10),alarm_level),convert(varchar(10),alarm_score),\
		convert(varchar(10),upper_limit),convert(varchar(10),lower_limit) from tb_eids_model_alarm_score\
		order by alarm_level";

const std::string g_strOrcAlarmScoreSQL = 
		"select id,Fun_Pub_Num_To_Char(alarm_level) alarm_level,Fun_Pub_Num_To_Char(alarm_score) alarm_score,\
		Fun_Pub_Num_To_Char(upper_limit) upper_limit,Fun_Pub_Num_To_Char(lower_limit) lower_limit \
		from tb_eids_model_alarm_score \
		order by alarm_level";

const std::string g_strAlarmSetSQL = 
		"select m.set_code,m.sys_id,m.sys_weight,m.model_id,m.model_weight,n.category_id,\
		n.category_weight,n.monit_point_id,n.alarm_band,n.interval_id,n.alarm_level,n.alarm_type,\
		convert(varchar,n.lower_limit_value),convert(varchar,n.upper_limit_value) \
		from v_eids_set_model_alarm m left join  v_eids_model_point_zone n \
		on m.model_id = n.model_id ";

const std::string g_strOrcAlarmSetSQL = 
		"select m.set_code,m.sys_id,m.sys_weight,m.model_id,m.model_weight,n.category_id,\
		n.category_weight,n.monit_point_id,n.alarm_band,n.interval_id,n.alarm_level,n.alarm_type,\
		Fun_Pub_Num_To_Char(n.lower_limit_value) lower_limit_value,\
		Fun_Pub_Num_To_Char(n.upper_limit_value) upper_limit_value\
		from v_eids_set_model_alarm m left join  v_eids_model_point_zone n \
		on m.model_id = n.model_id  where n.category_id is not null";
// 机组到系统配置信息加载 where n.category_id is not null
//const std::string g_strAlarmSetSQL = 
//		"select t.parent_id,t.id,t.model_weight,t.model_category from  TB_EIDS_MODEL t where t.id in \
//		(select t.parent_id from  TB_EIDS_MODEL t where t.model_category=2)\
//		order by t.parent_id"; 

//
const std::string g_strAlarmCosineSQL = 
		"select p.set_code,p.sys_id,p.model_id,p.sn,t.id,t.fault_name,t.related_param_value,\
		t.fault_causes,t.fault_analyse,t.fault_guide from TB_EIDS_FAULT_RULE t left join  \
		v_eids_set_model_alarm p on t.model_id=p.model_id where t.enabled=1 \
		order by p.set_code,p.sys_id,p.model_id";

//模型到测点配置信息加载
const std::string g_strAlarmSQL ="select model_id,category_id,monit_point_id,interval_id,alarm_level,\
		alarm_type,upper_limit_value,lower_limit_value \
		from v_eids_model_point_zone \
		order by model_id,category_id,monit_point_id,alarm_level desc";

//replace(source_id_original,'ZZ.SIS.','DDM.ZZS.') 
//const std::string g_strAllPointSQL=
//	  "select id,replace(source_id_original, 'ZZ.SIS.', 'DDM.ZZS.') AS source_id_original from tb_pub_point";
static std::string g_strAllPointSQL=
	 "select point_code,source_id_original,set_code,full_point_code  from tb_pub_point where factory_code = '%s'";
const std::string g_strModeSQL=
	"select id,condtion_id,local_var,out_var,out_var_func,expression,\
	monit_point_id,mode_source,point_id,source_id_original,source_id,\
	source_id_predicted,similar_id from v_eids_model_pointandcon_pre order by id,condtion_id";

const std::string g_strSetToPointSQL=
	"select t.set_id,set_code,t.set_jkd_id,t.sys_id,t.sys_jkd_id,t.sys_weight,t.model_id,\
	t.model_jkd_id,t.model_weight,t.equip_status_code,t.equip_status_source_id,t.condition_source_id,\
	t.model_condition_id,t.condition_value,t.local_var,t.out_var,t.out_var_func,t.expression,\
	t.monit_category_id,t.category_jkd_id,t.category_weight,t.get_value_type,t.get_value,t.point_code,\
	t.monit_point_id,t.source_id_original,\
	t.source_id,t.qwz_id,t.monit_point_jkd_id,p.id,Fun_Pub_Num_To_Char(p.upper_limit_value),\
	Fun_Pub_Num_To_Char(p.lower_limit_value),Fun_Pub_Num_To_Char(p.alarm_cap),Fun_Pub_Num_To_Char(p.param_source),\
	Fun_Pub_Num_To_Char(p.param_value),\
	Fun_Pub_Num_To_Char(SET_JKD_VALUE),Fun_Pub_Num_To_Char(SYS_JKD_VALUE),Fun_Pub_Num_To_Char(MODEL_JKD_VALUE),\
	Fun_Pub_Num_To_Char(CATEGORY_JKD_VALUE),Fun_Pub_Num_To_Char(MONIT_POINT_JKD_VALUE) \
	from v_eids_model_monit_point_all t left join tb_eids_model_alarm_interval p\
	on t.monit_point_id = p.monit_point_id\
	where t.factory_code= '%s'";

static std::string g_strDfhSQL=
	"select set_id,set_code,set_dfhnl_id,capacity,system_id,sys_dfhnl_id,jdk_short_code,object_id,source_id,\
	interval_id,Fun_Pub_Num_To_Char(upper_limit_value),Fun_Pub_Num_To_Char(lower_limit_value),\
	Fun_Pub_Num_To_Char(dfhnl_value),Fun_Pub_Num_To_Char(dfhnl_source),object_category \
	from v_eids_dfhnl_cfg_all where factory_code= '%s'";

static std::string g_strIndexSQL=
	"select index_code,set_code,index_type,source_id,out_var||out_var_func out_var,local_var,\
	expression,to_char(is_write_back) is_write_back,full_index_code ,to_char(is_clear_zero) stop_clear,\
	to_char(is_steady_cal) is_steady_cal,fun_pub_num_to_char(min_value) min_value, \
	fun_pub_num_to_char(max_value) max_value,fun_pub_num_to_char(default_value) default_value \
	from v_pub_index t where factory_code='%s' order by full_index_code asc";

const std::string g_strModeMuConfSQL =
	"select t.model_id,t.model_condition_id,t.similar_limit,t.monit_point_id,\
	t.ma_value,t.model_value,t.model_value_relation \
	from  tb_eids_model_method_avg t left join  v_eids_model_all p\
	on t.model_id=p.model_id \
	where p.factory_code ='%s'\
	order by model_id,model_condition_id";

//查询指标与点的全点名
const std::string g_strPubPointSQL = 
		"select point_code, source_id, set_id from tb_pub_point";

//查询手工点值
const std::string g_strMaunalPointSQL = 
		"select  point_id, Fun_Pub_Num_To_Char(current_value) current_value  from \
		(select t.*,rank() over(partition by t.point_id order by t.begin_time desc,t.approve_time desc) ord	 \
		from tb_pub_maunal_point t where t.approve_flag = 1 ) where ord = 1";
		//"select point_id, Fun_Pub_Num_To_Char(current_value) current_value from tb_pub_maunal_point where approve_flag = 1";

//查询模型配置更改标识
const std::string g_strSysStatusSQL = 
"select param_status from TB_PUB_PARAM where param_code='MODEL_IS_MODIFY' and factory_code = '%s'";


//查询计算到什么时间
const std::string g_strSysCalTimeSQL = 
"select param_value from TB_PUB_PARAM where param_code='MODEL_IS_MODIFY' and factory_code = '%s'";

//更新系统计算时间
const std::string g_strUpdateSysCalTimeSQL = 
"update TB_PUB_PARAM set param_value = '%s',compute_type=%d where param_code='MODEL_IS_MODIFY' and factory_code = '%s'";

//查询模型配置更改标识
const std::string g_strFactoryNoSQL = 
"select factory_tag from TB_PUB_MODULE_FACTORY  where factory_code ='%s'";
		
/*const std::string g_strSysStatusSQL = 
"select to_char(status_value) status_value from tb_pub_sys_status where status_name='MODEL_IS_MODIFY'";*/		

//更新指标配置更改标识
const std::string g_strUpdateStatusSQL = 
		"update TB_PUB_PARAM  set param_status =%d where param_code='MODEL_IS_MODIFY' and factory_code ='%s'";


//更新模型测点实时值表里面的模型健康度测点实时值
const std::string g_strSavePointValueSQL =  
        "update tb_eids_model_monit_point  set \
        update_time = to_date(:update_time,'yyyy-mm-dd hh24:mi:ss'), \
        similar_value = :sim_value \
        where point_id = :point_id";

//插入测点新的告警记录前将最后一条告警记录状态置为历史
const std::string g_strRsltPointUpFrontInsSQL = 
		"update tb_eids_model_alarm_data_point  set is_history=1 where is_history=0 and \
		model_id=:1  and category_id=:2 and monit_point_id=:3 ";

//插入测点新的告警记录
const std::string g_strRsltPointInSQL = 
		"insert into tb_eids_model_alarm_data_point(id,model_id,category_id,condition_id,monit_point_id,\
		begin_time,end_time,max_value,min_value,avg_value,max_value_predicted,min_value_predicted,\
		avg_value_predicted,alarm_level,is_history,avg_similar_value,alarm_type) \
		values(:1,:2,:3,:4,:5,convert(datetime,:6),convert(datetime,:7),\
		:8,:9,:10,:11,:12,:13,:14,:15,:16,:17)";

const std::string g_strOrcRsltPointInSQL = 
		"insert into tb_eids_model_alarm_data_point(id,model_id,category_id,condition_id,monit_point_id,\
		begin_time,end_time,max_value,min_value,avg_value,max_value_predicted,min_value_predicted,\
		avg_value_predicted,alarm_level,is_history,avg_similar_value,alarm_type) \
		values(:1,:2,:3,:4,:5, to_date(:6,'yyyy-mm-dd hh24:mi:ss'), to_date(:7,'yyyy-mm-dd hh24:mi:ss'),\
		:8,:9,:10,:11,:12,:13,:14,:15,:16,:17)";


//更新当前测点告警记录
const std::string g_strRsltPointUpBackInSQL = 
		"update tb_eids_model_alarm_data_point set \
		end_time=convert(datetime,:1),max_value=:2,min_value=:3,avg_value=:4,\
		max_value_predicted=:5,min_value_predicted=:6,avg_value_predicted=:7, \
		is_history=0,avg_similar_value=:8\
		where  id=:9 ";

const std::string g_strOrcRsltPointUpBackInSQL = 
		"update tb_eids_model_alarm_data_point set \
		end_time=to_date(:1,'yyyy-mm-dd hh24:mi:ss'),max_value=:2,min_value=:3,avg_value=:4,\
		max_value_predicted=:5,min_value_predicted=:6,avg_value_predicted=:7, \
		is_history=0,avg_similar_value=:8\
		where  id=:9 ";
//const std::string g_strRsltPointUpBackInSQL = 
//	"update tb_eids_model_alarm_data_point set \
//	end_time=convert(datetime,'%1'),max_value=%2,min_value=%3,avg_value=%4,\
//	max_value_predicted=%5,min_value_predicted=%6,avg_value_predicted=%7, \
//	is_history=0,avg_similar_value=%8\
//	where  id='%9' ";
const std::string g_strRsltIndexRtValuesSQL =
	"update tb_pub_index_value t set t.current_value=:1,t.update_time=to_date(:2,'yyyy-mm-dd hh24:mi:ss'), \
	t.update_time_c=to_date(:3,'yyyy-mm-dd hh24:mi:ss') where t.full_index_code=:4";

const std::string g_strRsltDpointRtValuesSQL =
	"update tb_pub_point_value t set t.update_time=to_date(:1,'yyyy-mm-dd hh24:mi:ss') , \
	t.current_value=:2 where t.full_point_code=:3";

const std::string g_strRsltPointRtValuesSQL =
	"update tb_eids_model_monit_point t set t.current_value=:1,t.predicted_value=:2,\
	t.jkd_value=:3 ,update_time=to_date(:4,'yyyy-mm-dd hh24:mi:ss') where t.id=:5";

const std::string g_strRsltModleRtValuesSQL =
"update tb_eids_model t set update_time=to_date(:1,'yyyy-mm-dd hh24:mi:ss') ,jkd_value=:2,dfhnl_value=:3,\
	condition_value=:4 where t.id=:5";

const std::string g_strRsltGroupRtValuesSQL = 
	"update tb_eids_model_monit_category t set t.jkd_value=:1,update_time=to_date(:2,'yyyy-mm-dd hh24:mi:ss') \
	where t.id=:3";


const std::string g_strRsltPointUpValuesSQL = 
	"update tb_eids_model_monit_point  set alarm_level=:1,update_time=convert(datetime,:2),\
	current_value=:3,predicted_value=:4,similar_value=:5 where category_id=:6 and point_id=:7";

const std::string g_strOrcRsltPointUpValuesSQL = 
	"update tb_eids_model_monit_point  set alarm_level=:1,update_time=to_date(:2,'yyyy-mm-dd hh24:mi:ss'),\
	current_value=:3,predicted_value=:4,similar_value=:5 where category_id=:6 and point_id=:7";

//插入分类新的告警记录前将最后一条告警记录状态置为历史
const std::string g_strRsltGroupUpFrontInsSQL = 
	"update tb_eids_model_category_alarm  set is_history=1 where is_history=0 and \
	category_id=:1 ";

//插入测点新的告警记录
const std::string g_strRsltGroupInSQL = 
	"insert into tb_eids_model_category_alarm(id,category_id,\
	begin_time,end_time,alarm_level,alarm_value,is_history) \
	values(:id,:category_id,convert(datetime,:start_t),convert(datetime,:end_t),\
	:alarm_level,:alarm_value,:is_history)";

const std::string g_strOrcRsltGroupInSQL = 
	"insert into tb_eids_model_category_alarm(id,category_id,\
	begin_time,end_time,alarm_level,alarm_value,is_history) \
	values(:id,:category_id,to_date(:start_t,'yyyy-mm-dd hh24:mi:ss'),\
	to_date(:end_t,'yyyy-mm-dd hh24:mi:ss'),\
	:alarm_level,:alarm_value,:is_history)";
//更新分类告警记录
const std::string g_strRsltGroupUpBackInSQL = 
	"update tb_eids_model_category_alarm set end_time=convert(datetime,:end_time)\
		where  id=:id and  is_history=0 ";

const std::string g_strOrcRsltGroupUpBackInSQL = 
	"update tb_eids_model_category_alarm set end_time=to_date(:end_time,'yyyy-mm-dd hh24:mi:ss')\
	where  id=:id and  is_history=0 ";

//插入模型新的告警记录前将最后一条告警记录状态置为历史
const std::string g_strRsltModelUpFrontInsSQL = 
	"update tb_eids_model_alarm_data  set is_history=1 where is_history=0 and \
	 model_id=:1";

//插入模型新的告警记录
const std::string g_strRsltModelInSQL = 
	"insert into tb_eids_model_alarm_data(id,model_id,\
	begin_time,end_time,alarm_level,alarm_value,is_history) \
	values(:id,:model_id,convert(datetime,:start_t),\
	convert(datetime,:end_t),\
	:alarm_level,:alarm_value,:is_history)";

const std::string g_strOrcRsltModelInSQL = 
	"insert into tb_eids_model_alarm_data(id,model_id,\
	begin_time,end_time,alarm_level,alarm_value,is_history) \
	values(:id,:model_id,to_date(:start_t,'yyyy-mm-dd hh24:mi:ss'),\
	to_date(:end_t,'yyyy-mm-dd hh24:mi:ss'),\
	:alarm_level,:alarm_value,:is_history)";
//更新模型告警记录
const std::string g_strRsltModelUpBackInSQL = 
	"update tb_eids_model_alarm_data set end_time=convert(datetime,:end_time)\
	 where  id=:id and  is_history=0 ";

const std::string g_strOrcRsltModelUpBackInSQL = 
	"update tb_eids_model_alarm_data set end_time=to_date(:end_time,'yyyy-mm-dd hh24:mi:ss')\
	where  id=:id and  is_history=0 ";
//插入模型模式新的记录前将最后一条告警记录状态置为历史
const std::string g_strRsltConditionUpFrontInsSQL = 
	"update tb_eids_model_period  set is_history=1 where is_history=0 and \
	 condition_id=:1";

const std::string g_strRsltConditionUpFrontInsSQLfirst = 
"update tb_eids_model_period  set is_history=1 where is_history=0";

//插入模式新的记录
const std::string g_strRsltConditionInSQL = 
	"insert into tb_eids_model_period(id,condition_id,begin_time,end_time,duration,is_history) \
	values(:id,:condition_id,convert(datetime,:begin_time),convert(datetime,:end_time),\
	:duration,:is_history)";

const std::string g_strOrcRsltConditionInSQL = 
	"insert into tb_eids_model_period(id,condition_id,begin_time,end_time,duration,is_history) \
	 values(:id,:condition_id,to_date(:begin_time,'yyyy-mm-dd hh24:mi:ss'),to_date(:end_time,'yyyy-mm-dd hh24:mi:ss'),\
	:duration,:is_history)";
//更新模式告警记录
const std::string g_strRsltConditionUpBackInSQL = 
	"update tb_eids_model_period set end_time=convert(datetime,:end_time),duration=:duration\
	where  id=:id and  is_history=0 ";

const std::string g_strOrcRsltConditionUpBackInSQL = 
	"update tb_eids_model_period set end_time=to_date(:end_time,'yyyy-mm-dd hh24:mi:ss'),duration=:duration\
	where  id=:id and  is_history=0 ";
//插入故障定位新的记录
const std::string g_strRsltCosineInSQL = 
	"insert into tb_eids_fault_event(id,fault_id,model_id,fault_name,start_time,end_time,\
	duration,fault_causes,fault_analyse,fault_guide,event_state,fault_code, match_rate,fault_type) \
	values(:id,:fault_id,:model_id,:fault_name,convert(datetime,:start_t),\
	convert(datetime,:end_t),:duration,:fault_causes,:fault_analyse,\
	:fault_guide,:event_state,:fault_code,:match_rate,:fault_type)";

const std::string g_strOrcRsltCosineInSQL = 
	"insert into tb_eids_fault_event(id,fault_id,model_id,fault_name,start_time,end_time,\
	duration,fault_causes,fault_analyse,fault_guide,event_state,fault_code, match_rate,fault_type) \
	values(:id,:fault_id,:model_id,:fault_name,to_date(:start_t,'yyyy-mm-dd hh24:mi:ss'),\
	to_date(:end_t,'yyyy-mm-dd hh24:mi:ss'),:duration,:fault_causes,:fault_analyse,\
	:fault_guide,:event_state,:fault_code,:match_rate,:fault_type)";

//更新故障定位记录
const std::string g_strRslCosineUpBackInSQL = 
"update tb_eids_fault_event  set end_time=convert(datetime,:end_time),duration=:duration\
	where id=:id";

const std::string g_strOrcRslCosineUpBackInSQL = 
	"update tb_eids_fault_event  set end_time=to_date(:end_time,'yyyy-mm-dd hh24:mi:ss'),duration=:duration\
	where id=:id";
#endif
