using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace CX900
{
    public static class varclass
    {
        private static byte ask=0;
        private static int prosbar = 0;

        public static byte Ask { get => ask; set => ask = value; }
        public static int Prosbar { get => prosbar; set => prosbar = value; }
    }
}
