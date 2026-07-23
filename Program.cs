using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Windows.Forms;

namespace CX900
{
    internal static class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {

            // 处理命令行参数
            string filePathToOpen = null;
            bool registerAssociation = false;

            if (args != null && args.Length > 0)
            {
                foreach (string arg in args)
                {
                    if (arg.Equals("--register-association", StringComparison.OrdinalIgnoreCase))
                    {
                        registerAssociation = true;
                    }
                    else if (arg.EndsWith(".cxkj", StringComparison.OrdinalIgnoreCase) && System.IO.File.Exists(arg))
                    {
                        filePathToOpen = arg;
                    }
                }
            }

            // 如果只是注册文件关联
            if (registerAssociation)
            {
                FileAssociationManager.RegisterFileAssociation();
                MessageBox.Show("文件关联注册成功！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }

#if true

            bool instantiated;
                        string aa = "CX900ID";
                        Mutex mutex = new Mutex(true, aa, out instantiated);
                        if (!instantiated)
                        {
                            MessageBox.Show("程序已经在运行中","提示");
                            return;
                        }
                        Application.EnableVisualStyles();
                        Application.SetCompatibleTextRenderingDefault(false);

                        // 创建主窗体并传递文件路径
                        MainForm mainForm = new MainForm();
                        if (!string.IsNullOrEmpty(filePathToOpen))
                        {
                            mainForm.FileToOpen = filePathToOpen;
                        }
                        Application.Run(mainForm);
                        GC.KeepAlive(mutex);

#else           

            bool instantiated;
            string aa = "CX900";
            System.Security.Principal.WindowsIdentity identity = System.Security.Principal.WindowsIdentity.GetCurrent();
            Application.EnableVisualStyles();
            System.Security.Principal.WindowsPrincipal principal = new System.Security.Principal.WindowsPrincipal(identity);
            if (principal.IsInRole(System.Security.Principal.WindowsBuiltInRole.Administrator))
            {
                Application.EnableVisualStyles();
                try
                {
                    Mutex mutex = new Mutex(true, aa, out instantiated);
                    if (!instantiated)
                    {
                        MessageBox.Show("程序已经在运行中", "提示");
                        return;
                    }
                    Application.EnableVisualStyles();
                    Application.SetCompatibleTextRenderingDefault(false);
                    Application.Run(new MainForm());
                    GC.KeepAlive(mutex);
                }
                catch (Exception e)
                {

                    System.Diagnostics.Debug.WriteLine(e.Message);
                }
            }

            else
            {
                //创建启动对象 
                System.Diagnostics.ProcessStartInfo startInfo1 = new System.Diagnostics.ProcessStartInfo();
                //设置运行文件 
                startInfo1.FileName = System.Windows.Forms.Application.ExecutablePath;
                //设置启动参数 
                startInfo1.Arguments = String.Join(" ", "CX900");
                //设置启动动作,确保以管理员身份运行 
                startInfo1.Verb = "runas";
                //如果不是管理员，则启动UAC 
                System.Diagnostics.Process.Start(startInfo1);
                //退出 
                System.Windows.Forms.Application.Exit();
            }
#endif
        }
    }
}
