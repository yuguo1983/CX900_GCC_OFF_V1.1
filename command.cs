using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace CX900
{
    public  enum command
    {
        OPWER_ON    =   0x01,
        OPWER_OFF           ,
        TURN_UP             ,
        TURN_DOWN           ,
        AUTO                ,
        CLEAR_PARAM         ,
        SET_VCC1            ,
        SET_VCC2            ,
        SET_VCC3            ,
        SET_VCC4            ,
        SET_VCC5            ,
        SET_VCC6            ,
        SET_VSP             ,
        SET_VSN             ,
        SET_FLLE_LEN        ,
        SET_APP_ADDR        ,
        SET_IAP_FLAG        ,
        SET_APP_FLAG        ,
    }

}
