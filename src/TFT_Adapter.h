#ifdef TFT_Adapter_STM32F746_Discovery
   #include "TFT_Adapter_STM32F746_Discovery.h"
#elif defined TFT_Adapter_ILI9341_BluePill
   #include "TFT_Adapter_ILI9341_BluePill.h"
#elif defined TFT_Adapter_CYD_V1_2
   #include "TFT_Adapter_CYD_V1_2.h"   
#elif defined TFT_Adapter_SPFD5408_UNO
   #include "TFT_Adapter_SPFD5408_UNO.h"
#elif defined TFT_TEK
   #include "TFT_TEK_wrapper.h"
#elif defined TFT_Adapter_ILI9341_F407_Discovery
   #include "TFT_Adapter_ILI9341_F407_Discovery.h"
#else
   #pragma error
#endif
