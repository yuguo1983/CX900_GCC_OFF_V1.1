using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CX900
{
    public class FuncNameEnum
    {
      public  enum FuncName
        {
            DELAY = 0x01,
            SSDPAKESIZE,
            SSDWRITEDAT,
            SPIWRITECMD,
            SPIWRITEDAT,
            SETVCCTIM,
            SETIOVCCTIM,
            SETVSPTIM,
            SETVSNTIM,
            SETVCCVOL,
            SETIOVCCVOL,
            SETVSPVOL,
            SETVSNVOL,
            ENIOVCC,
            ENVCC,
            ENVSP,
            ENVSN,
            ENSSDPOWER,
            LCDRST,
            SSDRST,
            BLSET,
            NEXT,
            PURECOLOR,
            GRADIentCol,
            GradientRow,
            CHECKerboard,
            BARROW,
            BARCOL,
            BLACKWIGHT,
            DISBMP,
            FLINKER,
            CROSS,
            SETVOLVCC1,
            SETVOLVCC2,
            SETVOLVCC3,
            SETVOLVCC4,
            SETVOLVCC5,
            SETVOLVCC6,
            SETTIMVCC1,
            SETTIMVCC2,
            SETTIMVCC3,
            SETTIMVCC4,
            SETTIMVCC5,
            SETTIMVCC6,
        }

    }
}
