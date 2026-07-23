using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.Xml;
using static CX900.FuncNameEnum;
using static CX900.StructClass;
//using static ScintillaNET.Style;

namespace CX900
{
    public delegate void upstring(string info);
    public class CodeCompile
    {
        //public List<subCode> InitCode = null;

        public upstring upstr { get; set; }
        public upstring upfail { get; set; }
        public string sucessfullstring { get; set; }
        public string failstring { get; set; }
        public string info;
        public void startcompile()
        {
            try
            {


            using (Process p = new Process())
            {
                info = null;
                p.StartInfo.FileName = "make";
                p.StartInfo.UseShellExecute = false;        //是否使用操作系统shell启动
                p.StartInfo.RedirectStandardInput = false;  //接受来自调用程序的输入信息
                p.StartInfo.RedirectStandardOutput = true;  //由调用程序获取输出信息
                p.StartInfo.RedirectStandardError = true;   //重定向标准错误输出
                p.StartInfo.Arguments = "V=1";
                p.ErrorDataReceived += new DataReceivedEventHandler((sender, e) =>
                {

                    if (e.Data != null)
                    {
                        //  upfail(e.Data);
                        info += e.Data+"\r\n";


                    Console.WriteLine(e.Data);
                    }
                });

                p.StartInfo.CreateNoWindow = true;          //不显示程序窗口
                p.StartInfo.Arguments = "";
                if (!p.Start()) //启动程序
                {
                    Console.WriteLine("未能启动程序：");
                    return;
                }

                // To avoid deadlocks, use an asynchronous read operation on at least one of the streams.  
                p.BeginErrorReadLine();
                string oneLine;
                //获取cmd窗口的输出信息
                while (!p.StandardOutput.EndOfStream)
                {
                    oneLine = p.StandardOutput.ReadLine();
                    upstr(oneLine);

                }
                p.StandardOutput.Close();

                if (info != null)
                {
                    if (info.Contains("Error"))
                        upfail(info);
                }

                p.WaitForExit();//等待程序执行完退出进程
                p.Close();
             }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
            }

        }


        private void outputstr(string str)
        {

        }

        //同步方式
        public void RunExe(string exePath, string arguments, out string output, out string error)
        {
            using (Process process = new System.Diagnostics.Process())
            {
                process.StartInfo.FileName = exePath;
                process.StartInfo.Arguments = arguments;
                // 必须禁用操作系统外壳程序  
                process.StartInfo.UseShellExecute = false;
                process.StartInfo.CreateNoWindow = true;
                process.StartInfo.RedirectStandardOutput = true;
                process.StartInfo.RedirectStandardError = true;

                process.Start();

                output = process.StandardOutput.ReadToEnd();
                error = process.StandardError.ReadToEnd();

                process.WaitForExit();
                process.Close();
            }
        }

            public void cleancompile()
        {
            ProcessStartInfo startInfo = new ProcessStartInfo
            {
                FileName = "make", // 假设make命令在系统PATH中
                 Arguments = "clean", // 替换为实际的make参数
                UseShellExecute = false, // 不使用操作系统外壳启动进程
                RedirectStandardOutput = true, // 重定向标准输出
                RedirectStandardError = true, // 重定向标准错误
                CreateNoWindow = true // 不创建新窗口
            };
            try
            {
                using (Process process = Process.Start(startInfo))
                {
                    using (System.IO.StreamReader reader = process.StandardOutput)
                    {
                        // textBox_disinfo.ForeColor = Color.Green;
                        string stdout = reader.ReadToEnd(); // 读取标准输出流
                        upstr(stdout);
                        Debug.WriteLine(stdout);
                    }

                    string stderr = process.StandardError.ReadToEnd(); // 读取标准错误流
                    if (!string.IsNullOrEmpty(stderr))
                    {
                        upfail(stderr);
                        Debug.WriteLine(stderr);
                    }

                    process.WaitForExit(); // 等待进程结束
                }
            }
            catch (Exception e)
            {

                MessageBox.Show(e.Message + "正在安装配置环境，请稍等.....");
                return;
            }

        }


        public static int strInString(string instr, string srcstr)
        {
            if (srcstr == null)
                return -1;
            int length1 = srcstr.Length;
            int length2 = instr.Length;
            if (length2 > length1)
                return 0;
            int length3 = srcstr.Replace(instr, "").Length;
            return (length1 - length3) / length2;
        }
        private List<string> removeSingularRemarks(List<string> lstr)
        {
            List<string> stringList = new List<string>();

            int count = lstr.Count;
            for (int index = 0; index < count; ++index)
            {


                string srcstr = lstr[index].Replace("\r\n", "");
                if (CodeCompile.strInString("//", srcstr) > 0)
                {
                    int startIndex = srcstr.IndexOf("//");
                    int length = srcstr.Length;
                    string str = srcstr.Remove(startIndex, length - startIndex);
                    stringList.Add(str);
                }
                else
                    stringList.Add(srcstr);
            }
            return stringList;
        }
        private List<string> RemoveMutiLineRemarks(List<string> lstr)
        {
            List<string> stringList = lstr;
            int count = lstr.Count;
            int[] numArray1 = new int[2] { -1, -1 };
            int[] numArray2 = new int[2] { -1, -1 };
            for (int index1 = 0; index1 < count; ++index1)
            {
                string str1 = lstr[index1].Replace("\t", "");
                char minValue;
                if (str1.Contains("/*"))
                {
                    string str2 = str1;
                    minValue = char.MinValue;
                    string newValue = minValue.ToString();
                    string str3 = str2.Replace("/*", newValue);
                    int num = str3.IndexOf(char.MinValue);
                    numArray1[0] = index1;
                    numArray1[1] = num;
                    string str4 = str3;
                    minValue = char.MinValue;
                    string oldValue = minValue.ToString();
                    str1 = str4.Replace(oldValue, "/*");
                }
                if (str1.Contains("*/"))
                {
                    string str5 = str1;
                    minValue = char.MinValue;
                    string newValue = minValue.ToString();
                    string str6 = str5.Replace("*/", newValue);
                    int num = str6.IndexOf(char.MinValue);
                    numArray2[0] = index1;
                    numArray2[1] = num;
                    string str7 = str6;
                    minValue = char.MinValue;
                    string oldValue = minValue.ToString();
                    str7.Replace(oldValue, "*/");
                }
                if (numArray2[0] >= 0 && numArray1[0] >= 0)
                {
                    if (numArray1[0] == numArray2[0])
                    {
                        stringList[numArray1[0]] = stringList[numArray1[0]].Remove(numArray1[1], numArray2[1] - numArray1[1] + 2);
                    }
                    else
                    {
                        for (int index2 = numArray1[0]; index2 <= numArray2[0]; ++index2)
                            stringList[index2] = index2 != numArray1[0] ? (index2 != numArray2[0] ? "" : stringList[index2].Remove(0, numArray2[1] + 2)) : stringList[index2].Remove(numArray1[1], lstr[index2].Length - numArray1[1]);
                    }
                    numArray1[0] = -1;
                    numArray1[1] = -1;
                    numArray2[0] = -1;
                    numArray2[1] = -1;
                }
            }
            if (numArray1[0] > 0 && numArray2[0] < 0)
                //CodeCompile.report.Add(new codeReport()
                //{
                //    lines = numArray1[0],
                //    reports = "第 " + numArray1[1].ToString() + " 列 '*/'没有结尾标志"
                //});
                if (numArray1[0] < 0 && numArray2[0] > 0)
                {

                }
            //CodeCompile.report.Add(new codeReport()
            //{
            //    lines = numArray1[0],
            //    reports = "第 " + numArray1[1].ToString() + " 列 '*/'没有没有开始标志"
            //});
            return stringList;
        }
        private List<subCode> linesToLine(List<string> lstr)
        {
            List<subCode> line = new List<subCode>();
            bool flag = false;
            int count = lstr.Count;
            for (int index1 = 0; index1 < count; ++index1)
            {
                //if (index1 != 170 && index1 != 364)
                //    ;
                int num = CodeCompile.strInString(";", lstr[index1]);
                string str = !flag ? lstr[index1] : line[line.Count - 1].codeStr + lstr[index1];
                if (num > 0)
                {
                    string[] strArray = str.Split(';');
                    int length = strArray.Length;
                    for (int index2 = 0; index2 < length; ++index2)
                    {
                        string oldValue = strArray[index2];
                        if (oldValue.Replace(" ", "").Replace("\t", "").Length > 0)
                        {
                            if (flag)
                            {
                                line[line.Count - 1].line = index1 + 1;
                                line[line.Count - 1].codeStr = oldValue;
                            }
                            else
                                line.Add(new subCode()
                                {
                                    line = index1 + 1,
                                    codeStr = oldValue
                                });
                            str = str.Replace(oldValue, "");
                        }
                    }
                    flag = false;
                }
                else
                {
                    if (index1 + 1 == count)
                    {
                        if (flag)
                        {
                            line[line.Count - 1].line = index1 + 1;
                            line[line.Count - 1].codeStr = str;
                        }
                        else
                            line.Add(new subCode()
                            {
                                line = index1 + 1,
                                codeStr = str
                            });
                        codeReport codeReport = new codeReport()
                        {
                            lines = index1 + 1,
                            reports = "行尾';'号缺失;"
                        };
                    }
                    else if (flag)
                    {
                        line[line.Count - 1].line = index1 + 1;
                        line[line.Count - 1].codeStr = str;
                    }
                    else
                        line.Add(new subCode()
                        {
                            line = index1 + 1,
                            codeStr = str
                        });
                    flag = true;
                }
            }
            return line;
        }




        //private bool cutCode(List<subCode> lsc)
        //{
        //    if (InitCode == null)
        //        InitCode = new List<subCode>();

        //    bool flag = true;
        //    int count = lsc.Count;
        //    int[] numArray1 = new int[2] { -1, -1 };
        //    int[] numArray2 = new int[2] { -1, -1 };
        //    for (int index1 = 0; index1 < count; ++index1)
        //    {
        //        string codeStr = lsc[index1].codeStr;
        //        int line1 = lsc[index1].line;
        //        if (codeStr.Contains("_sPublicPar spublicpar={"))
        //        {
        //            int num = codeStr.IndexOf('{');
        //            numArray1[0] = index1;
        //            numArray1[1] = num;
        //        }
        //        if (codeStr.Contains("}"))
        //        {
        //            int num = codeStr.IndexOf('}');
        //            numArray2[0] = index1;
        //            numArray2[1] = num;
        //        }
        //        if (numArray1[0] >= 0 && numArray2[0] >= 0)
        //        {
        //            int num = numArray2[0];
        //            if (numArray1[0] == numArray2[0])
        //            {
        //                this.InitCode.Add(new subCode()
        //                {
        //                    line = line1,
        //                    codeStr = codeStr.Substring(numArray1[1], numArray2[1] - numArray1[index1])
        //                });
        //            }
        //            else
        //            {
        //                for (int index2 = numArray1[0]; index2 <= num; ++index2)
        //                {
        //                    int line2 = lsc[index2].line;
        //                    if (index2 == numArray1[0])
        //                    {
        //                        subCode subCode = new subCode();
        //                        subCode.line = line2;
        //                        subCode.codeStr = lsc[index2].codeStr.Substring(numArray1[1] + 1, lsc[index2].codeStr.Length - numArray1[1] - 1).Replace(" ", "");
        //                        lsc[index2].codeStr = lsc[index2].codeStr.Remove(numArray1[1] + 1, lsc[index2].codeStr.Length - numArray1[1] - 1);
        //                        if (subCode.codeStr.Length > 0)
        //                            this.InitCode.Add(subCode);
        //                    }
        //                    else if (index2 == num)
        //                    {
        //                        subCode subCode = new subCode();
        //                        subCode.line = line2;
        //                        subCode.codeStr = lsc[index2].codeStr.Substring(0, numArray2[1]).Replace(" ", "");
        //                        lsc[index2].codeStr = lsc[index2].codeStr.Remove(0, numArray2[1]);
        //                        if (subCode.codeStr.Length > 0)
        //                            this.InitCode.Add(subCode);
        //                    }
        //                    else
        //                    {
        //                        subCode subCode = new subCode();
        //                        subCode.line = line2;
        //                        subCode.codeStr = lsc[index2].codeStr.Replace(" ", "");
        //                        lsc[index2].codeStr = "";
        //                        if (subCode.codeStr.Length > 0)
        //                            this.InitCode.Add(subCode);
        //                    }
        //                }
        //                try
        //                {
        //                    lsc[numArray2[0]].codeStr = lsc[numArray2[0]].codeStr.Remove(numArray2[1], 1);
        //                }
        //                catch
        //                {
        //                }
        //                numArray1[0] = -1;
        //                numArray1[1] = -1;
        //                numArray2[0] = -1;
        //                numArray2[1] = -1;
        //            }
        //        }
        //    }

        //    if (numArray1[0] >= 0 && numArray2[0] < 0)
        //    {
        //        //CodeCompile.report.Add(new codeReport()
        //        //{
        //        //    lines = numArray1[0],
        //        //    reports = "void main() 无结尾标志"
        //        //});
        //        MessageBox.Show("void main() 无结尾标志");
        //    }

        //    if (numArray1[0] < 0 && numArray2[0] >= 0)
        //    {
        //        codeReport codeReport1 = new codeReport()
        //        {
        //            lines = numArray1[0],
        //            reports = "无法确定的符号!"
        //        };
        //    }

        //    return true;
        //}

        public void readinfo(string path, pMIPI_Para_Table par)
        {

            try
            {


                FileStream fs = new FileStream(path, FileMode.Create);
                StreamWriter sw = new StreamWriter(fs);


                sw.WriteLine("#include \"user_config.h\"");
                sw.WriteLine("#include \"lcd_cfg.h\"");
                sw.WriteLine("#include \"systick.h\"");
                sw.WriteLine("const uint8_t SSD2828Init = 0;");
                sw.WriteLine("const uint8_t HWSSD2828 = 0; //");
                //sw.WriteLine("char * videopath=\"sd: video.avi\";");
                sw.WriteLine(" pMIPI_Para_Table PARA_MIPI_VedioMode ={");
                sw.WriteLine("\"" +par.bLCDName.Replace("\n","")  + "\""+ ",");
                sw.WriteLine("\"" +par.bICName.Replace("\n", "") + "\",  ");
                sw.WriteLine("\"" + par.CodeZip.Replace("\n", "") + "\",    ");
                sw.WriteLine(par.DUAL_MIPI_LCD + ",                ");
                sw.WriteLine(par.DUAL_MIPI_CHANNEL_SWAP + ",                ");
                sw.WriteLine(par.ODD_EVEN_nLEFT_RIGHT + ",                //");
                sw.WriteLine(par.PCLK_Freq + ",                 //   ");
                sw.WriteLine(par.LANE_CNT + ",                 //   ");
                sw.WriteLine(par.V_DE + ",                 //   	");
                sw.WriteLine(par.V_VS + ",                 // ");
                sw.WriteLine(par.V_HS + ",                 //   ");
                sw.WriteLine(par.V_CLK + ",                 // ");
                sw.WriteLine(par.Display_Mode + ",          //");
                sw.WriteLine(par.HACT_WIDTH + ",                 //  ");
                sw.WriteLine(par.VACT_WIDTH + ",                 //   ");
                sw.WriteLine(par.HFP_WIDTH + ",                 //  ");
                sw.WriteLine(par.HBP_WIDTH + ",                // ");
                sw.WriteLine(par.HSW_WIDTH + ",                //  ");
                sw.WriteLine(par.VFP_WIDTH + ",                //   ");
                sw.WriteLine(par.VBP_WIDTH + ",            //    ");
                sw.WriteLine(par.VSW_WIDTH + ",          //   ");
                sw.WriteLine(par.NomalVCC1SET + ",       //  	");
                sw.WriteLine(par.LowperVCC1VOL + ",         //  ");
                sw.WriteLine(par.UperVCC1VOL + ",       //  ");
                sw.WriteLine(par.LowperVCC1MA + ",         //  ");
                sw.WriteLine(par.UperVCC1MA + ",        //   ");
                sw.WriteLine(par.NomalVCC2SET + ",         //   ");
                sw.WriteLine(par.LowperVCC2VOL + ",        // 	");
                sw.WriteLine(par.UperVCC2VOL + ",          //   ");
                sw.WriteLine(par.LowperVCC2MA + ",     // ");
                sw.WriteLine(par.UperVCC2MA + ",       //  ");
                sw.WriteLine(par.NomalVCC3SET + ",      //   ");
                sw.WriteLine(par.LowperVCC3VOL + ",        //  ");
                sw.WriteLine(par.UperVCC3VOL + ",        //  ");
                sw.WriteLine(par.LowperVCC3MA + ",         //   	");
                sw.WriteLine(par.UperVCC3MA + ",       //   ");
                sw.WriteLine(par.NomalVCC4SET + ",         //  	");
                sw.WriteLine(par.LowperVCC4VOL + ",         //   ");

                sw.WriteLine(par.UperVCC4VOL + ",           // ");
                sw.WriteLine(par.LowperVCC4MA + ",          //   ");
                sw.WriteLine(par.UperVCC4MA + ",          //	 ");
                sw.WriteLine(par.NomalVCC5SET + ",           //  ");
                sw.WriteLine(par.LowperVCC5VOL + ",             //	 ");
                sw.WriteLine(par.UperVCC5VOL + ",             // ");
                sw.WriteLine(par.LowperVCC5MA + ",             // ");
                sw.WriteLine(par.UperVCC5MA + ",                //");
                sw.WriteLine(par.NomalVCC6SET + ",          //	");
                sw.WriteLine(par.LowperVCC6VOL + ",          //	");

                sw.WriteLine(par.UperVCC6VOL + ",          //	");
                sw.WriteLine(par.LowperVCC6MA + ",       // 	");
                sw.WriteLine(par.UperVCC6MA + ",           //");


                sw.WriteLine(par.NomalVSPSET + ",           //");
                sw.WriteLine(par.LowperVSPVOL + ",           //");
                sw.WriteLine(par.UperVSPVOL + ",           //");
                sw.WriteLine(par.LowperVSPMA + ",           //");
                sw.WriteLine(par.UperVSPMA + ",           //");

                sw.WriteLine(par.NomalVSNSET + ",           //");
                sw.WriteLine(par.LowperVSNVOL + ",           //");
                sw.WriteLine(par.UperVSNVOL + ",           //");
                sw.WriteLine(par.LowperVSNMA + ",           //");
                sw.WriteLine(par.UperVSNMA + ",           //");

                sw.WriteLine(par.NomalBLSET + ",           //");
                sw.WriteLine(par.LowperBLVOL + ",           //");
                sw.WriteLine(par.UperBLVOL + ",           //");
                sw.WriteLine(par.LowperBLMA + ",           //");
                sw.WriteLine(par.UperBLMA + ",           //");
                sw.WriteLine(par.BLMASET + ",           //");

                sw.WriteLine(par.VCC1Time + ",           //");
                sw.WriteLine(par.VCC2Time + ",           //");
                sw.WriteLine(par.VCC3Time + ",           //");
                sw.WriteLine(par.VCC4Time + ",           //");
                sw.WriteLine(par.VCC5Time + ",           //");
                sw.WriteLine(par.VCC6Time + ",           //");
                sw.WriteLine(par.VSPTime + ",           //");
                sw.WriteLine(par.VSNTime + ",           //");

                sw.WriteLine(par.Low_Delay + ",           //");
                sw.WriteLine(par.SIZE_OF_SHOW_MODE + ",           //");
                sw.WriteLine(par.AlarmFlag + ",           //");
                sw.WriteLine(par.TimeLock + ",           //");
                sw.WriteLine(par.Reserve1 + ",           //");
                sw.WriteLine(par.Reserve2 + ",           //");
                sw.WriteLine(par.Reserve3 + ",           //");
                sw.WriteLine(par.Reserve4 + ",           //");
                sw.WriteLine(par.Reserve5 + ",           //");
                sw.WriteLine(par.MIPI_MODE + ",           //");
                sw.WriteLine(par.DW1_EN + ",           //");
                sw.WriteLine(par.DW2_EN + ",           //");
                sw.WriteLine("};");
                sw.WriteLine("const pMIPI_Para_Table * ptr_MIPI_TABLE[] =");
                sw.WriteLine("{");
                sw.WriteLine("&PARA_MIPI_VedioMode,");
                sw.WriteLine("};");
                // sw.WriteLine("uint8_t  MIPI_TABLE_LAST_INDEX = ((sizeof(ptr_TABLE) / sizeof(const _sPublicPar *)) - 1); @//自动计算ptr_EDP_TABLE表中对应屏参配置的个数");


                sw.Flush();
                sw.Dispose();
                sw.Close();
                fs.Close();

            }
            catch (Exception e)
            {

                Debug.WriteLine(e.Message);
            }
        }


    }
}
