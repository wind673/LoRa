/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_Run.c
* @Description : 系统运行
* @Date        : 2017/10/16
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32L151CB)
* @Explain     : None
-------------------------------------------------------------------------------
版本号：		WindOS3.2.01
修订记录：	
 @Date		@Version			@Revise					@Author
2017/10/16 	WindOS3.2.01		修正运行时间				Wind（谢玉伸）
2017/10/16 	WindOS3.2.02		修复Free				Wind（谢玉伸）

最后修订：
修复Free线程只能走一个App的BUG。 
*=============================================================================*/     

/* 头文件包含 ----------------------------------------------------------------*/
#include "OS_Run.h"
#include "OS_StartFile.h"
#include "OS_Manage.h"
#include "OS_Tools.h"

/* 私有宏定义 ----------------------------------------------------------------*/
											
/* 私有（静态）函数声明 ------------------------------------------------------*/
										
/* 全局变量定义 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/	
 
/**----------------------------------------------------------------------------
* @FunctionName  : OSThread_Free()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : 空闲线程
------------------------------------------------------------------------------*/
inline void OSThread_Free(void)
{ 
	static u32 time_us = 0;
 	Type_AppList *AppRun = &AppHead;    
	
	if(!OStimer_usTimeOver_Is(time_us,1000)) return;
	time_us = OStimer_us_Get(); //更新时间
	
	if(OS_Msg & OS_BREAK) return;   
	
	while(1)
	{    
		if(AppRun ->next == NULL) return;  
		
		AppRun = AppRun ->next;   	 
		if(AppRun ->thread != OS_THREAD_FREE) continue; 
		if(AppRun ->loading != 0 )  AppRun ->loading --;
		if(AppRun ->loading == 0 ) 
		{ 
		 
			if(AppRun ->state == OS_STATE_SUSPEND) //挂起
			{ 
				if(AppRun ->AppEnd != NULL) AppRun ->AppEnd();  
				AppRun ->state = OS_STATE_SUSPEND_FINISH; 	
				AppRun ->loading = AppRun ->reload;	
			}
			else if(AppRun ->state == OS_STATE_SUSPEND_FINISH)//运行已经挂起的后台程序
			{
				if(AppRun ->AppBack != NULL) AppRun ->AppBack();//运行后台程序
				AppRun ->loading = AppRun ->reload;	
			}	
			else if(AppRun ->state == OS_STATE_ACTIVE) //激活   
			{ 
				if(AppRun ->AppStart != NULL) AppRun ->AppStart(); //运行启动程序  
				AppRun ->state = OS_STATE_ACTIVE_FINISH; 	
				AppRun ->loading = AppRun ->reload;	
			}					
			else if(AppRun ->state == OS_STATE_ONE_OFF) //一次性的程序  
			{ 				
				if(AppRun ->AppMain != NULL) AppRun ->AppMain(); //运行一次主程序  
				AppRun ->state = OS_STATE_CLOSE_FINISH;  
				AppRun ->loading = AppRun ->reload;	 
			} 
			else if(AppRun ->state == OS_STATE_CLOSE)
			{ 
				if(AppRun ->AppEnd != NULL) AppRun ->AppEnd(); 	//运行结束程序
				AppRun ->state = OS_STATE_CLOSE_FINISH;
				AppRun ->loading = AppRun ->reload;	
			}
			else if(AppRun ->state == OS_STATE_ACTIVE_FINISH)//运行已经激活的主程序
			{
				if(AppRun ->AppMain != NULL) AppRun ->AppMain(); 
				AppRun ->loading = AppRun ->reload;	
			}	
			 
		}  
		
	} 
}

 
 
/**----------------------------------------------------------------------------
* @FunctionName  : OSThread_5()     
* @Description   : None 
* @Data          : 2016/4/19
* @Explain       : 线程5
------------------------------------------------------------------------------*/
inline void OSThread_5(void)
{
	Type_AppList *AppRun = &AppHead;   
	if(OS_Msg & OS_BREAK) return;
	
	while(1)
	{	
		if(AppRun ->next == NULL) return; 
		
		AppRun = AppRun ->next; 
		
		if(AppRun ->thread != OS_THREAD_5) continue; 
		
		if(AppRun ->loading != 0) AppRun ->loading --;   
		if(AppRun ->loading == 0 )  
		{  	
			if(AppRun ->state == OS_STATE_ACTIVE_FINISH)//运行已经激活的主程序		
			{
				if(AppRun ->AppMain != NULL) AppRun ->AppMain(); 	
				AppRun ->loading = AppRun ->reload;					
			} 
			else if(AppRun ->state == OS_STATE_SUSPEND_FINISH)//运行已经挂起的后台程序
			{
				if(AppRun ->AppBack != NULL) AppRun ->AppBack();//运行后台程序
				AppRun ->loading = AppRun ->reload;	
			}	
			else if(AppRun ->state == OS_STATE_SUSPEND) //挂起
			{ 
				if(AppRun ->AppEnd != NULL) AppRun ->AppEnd(); 
				AppRun ->state = OS_STATE_SUSPEND_FINISH; 	
				AppRun ->loading = AppRun ->reload;	
			} 
			else if(AppRun ->state == OS_STATE_ACTIVE) //激活   
			{ 
				if(AppRun ->AppStart != NULL) AppRun ->AppStart(); //运行启动程序  
				AppRun ->state = OS_STATE_ACTIVE_FINISH; 	
				AppRun ->loading = AppRun ->reload;	
			}		 
			else if(AppRun ->state == OS_STATE_ONE_OFF) //一次性的程序  
			{ 				
				if(AppRun ->AppMain != NULL) AppRun ->AppMain(); //运行一次主程序程序   	
				AppRun ->state = OS_STATE_ONE_OFF_FINISH;  	
				AppRun ->loading = AppRun ->reload;	
			} 
			else if(AppRun ->state == OS_STATE_ONE_OFF_FINISH) //一次性的程序  
			{ 				
				if(AppRun ->AppMain != NULL) AppRun ->AppMain(); //运行一次主程序程序   	
				AppRun ->state = OS_STATE_CLOSE_FINISH;  	
				AppRun ->loading = AppRun ->reload;	
			} 
			else if(AppRun ->state == OS_STATE_CLOSE)	
			{ 
				if(AppRun ->AppEnd != NULL) AppRun ->AppEnd(); 	//运行结束程序	
				AppRun ->state = OS_STATE_CLOSE_FINISH;	
				AppRun ->loading = AppRun ->reload;	
			}	 
			 							
		}
			   
	} 
	
}








/**----------------------------------------------------------------------------
* @FunctionName  : OSThread_8()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : 线程8
------------------------------------------------------------------------------*/
inline void OSThread_8(void)
{   
	Type_AppList *AppRun = &AppHead;   
	if(OS_Msg & OS_BREAK) return;
	
	while(1)
	{	
		if(AppRun ->next == NULL) return; 
		
		AppRun = AppRun ->next; 
		
		if(AppRun ->thread != OS_THREAD_8) continue; 
		
		if(AppRun ->loading != 0) AppRun ->loading --;   
		if(AppRun ->loading == 0 )  
		{  	
			if(AppRun ->state == OS_STATE_ACTIVE_FINISH)//运行已经激活的主程序		
			{
				if(AppRun ->AppMain != NULL) AppRun ->AppMain(); 	
				AppRun ->loading = AppRun ->reload;					
			} 
			else if(AppRun ->state == OS_STATE_SUSPEND_FINISH)//运行已经挂起的后台程序
			{
				if(AppRun ->AppBack != NULL) AppRun ->AppBack();//运行后台程序
				AppRun ->loading = AppRun ->reload;	
			}	
			else if(AppRun ->state == OS_STATE_SUSPEND) //挂起
			{ 
				if(AppRun ->AppEnd != NULL) AppRun ->AppEnd(); 
				AppRun ->state = OS_STATE_SUSPEND_FINISH; 	
				AppRun ->loading = AppRun ->reload;	
			} 
			else if(AppRun ->state == OS_STATE_ACTIVE) //激活   
			{ 
				if(AppRun ->AppStart != NULL) AppRun ->AppStart(); //运行启动程序  
				AppRun ->state = OS_STATE_ACTIVE_FINISH; 	
				AppRun ->loading = AppRun ->reload;	
			}		 
			else if(AppRun ->state == OS_STATE_ONE_OFF) //一次性的程序  
			{ 				
				if(AppRun ->AppMain != NULL) AppRun ->AppMain(); //运行一次主程序程序   	
				AppRun ->state = OS_STATE_ONE_OFF_FINISH;  	
				AppRun ->loading = AppRun ->reload;	
			} 
			else if(AppRun ->state == OS_STATE_ONE_OFF_FINISH) //一次性的程序  
			{ 				
				if(AppRun ->AppMain != NULL) AppRun ->AppMain(); //运行一次主程序程序   	
				AppRun ->state = OS_STATE_CLOSE_FINISH;  	
				AppRun ->loading = AppRun ->reload;	
			} 
			else if(AppRun ->state == OS_STATE_CLOSE)	
			{ 
				if(AppRun ->AppEnd != NULL) AppRun ->AppEnd(); 	//运行结束程序	
				AppRun ->state = OS_STATE_CLOSE_FINISH;	
				AppRun ->loading = AppRun ->reload;	
			}	 
			 							
		}
			   
	} 
	
} 






/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/





