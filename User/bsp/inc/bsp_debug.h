#ifndef _DEBUG_H_
#define _DEBUG_H_
#include "bsp.h"

//µ÷ÊÔ¿ª¹Ø
#define DEBUG 1

#if DEBUG

#define DEBUG_Clear()                                   OLED_Clear()
#define DEBUG_Char(Line, Column, Char)                  OLED_ShowChar(Line, Column, Char)
#define DEBUG_String(Line, Column, String)              OLED_ShowString(Line, Column, String)
#define DEBUG_Num(Line, Column, Number, Length)         OLED_ShowNum(Line, Column, Number, Length)
#define DEBUG_SignedNum(Line, Column, Number, Length)   OLED_ShowSignedNum(Line, Column, Number, Length)
#define DEBUG_HexNum(Line, Column, Number, Length)      OLED_ShowHexNum(Line, Column, Number, Length)
#define DEBUG_BinNum(Line, Column, Number, Length)      OLED_ShowBinNum(Line, Column, Number, Length)
#define DEBUG_Memery(Line, addr, Length)                OLED_ShowMemery(Line, addr, Length)             

#else

#define DEBUG_Clear()                                
#define DEBUG_Char(Line, Column, Char)               
#define DEBUG_String(Line, Column, String)           
#define DEBUG_Num(Line, Column, Number, Length)      
#define DEBUG_SignedNum(Line, Column, Number, Length)
#define DEBUG_HexNum(Line, Column, Number, Length)   
#define DEBUG_BinNum(Line, Column, Number, Length)   

#endif

#endif

