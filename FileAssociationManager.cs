using System;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;
using Microsoft.Win32;

namespace CX900
{
    /// <summary>
    /// 文件关联管理器 - 用于注册.CXKJ扩展名与程序图标的关联
    /// </summary>
    public class FileAssociationManager
    {
        private const string Extension = ".cxkj";
        private const string ProgId = "CX900.File";
        private const string FileTypeName = "CX900 Project File";

        [System.Runtime.InteropServices.DllImport("shell32.dll", CallingConvention = System.Runtime.InteropServices.CallingConvention.StdCall)]
        private static extern void SHChangeNotify(uint wEventId, uint uFlags, IntPtr dwItem1, IntPtr dwItem2);

        private const uint SHCNE_ASSOCCHANGED = 0x08000000;
        private const uint SHCNF_IDLIST = 0x0000;

        /// <summary>
        /// 注册文件关联
        /// </summary>
        public static void RegisterFileAssociation()
        {
            try
            {
                // 获取程序路径和图标路径
                string appPath = Application.ExecutablePath;
                string appDirectory = Path.GetDirectoryName(appPath);
                string iconPath = Path.Combine(appDirectory, "Construction_(159).ico");

                // 如果图标文件不存在，使用程序本身的图标
                if (!File.Exists(iconPath))
                {
                    iconPath = appPath + ",0"; // 使用程序的第0个图标
                }

                // 创建注册表项 (当前用户级别)
                using (RegistryKey rootKey = Registry.CurrentUser.CreateSubKey(@"Software\Classes"))
                {
                    // 1. 创建扩展名到ProgId的映射
                    using (RegistryKey extensionKey = rootKey.CreateSubKey(Extension))
                    {
                        extensionKey.SetValue("", ProgId);
                    }

                    // 2. 创建ProgId项
                    using (RegistryKey progIdKey = rootKey.CreateSubKey(ProgId))
                    {
                        progIdKey.SetValue("", FileTypeName);

                        // 设置图标
                        using (RegistryKey iconKey = progIdKey.CreateSubKey("DefaultIcon"))
                        {
                            iconKey.SetValue("", iconPath);
                        }

                        // 设置打开命令
                        using (RegistryKey commandKey = progIdKey.CreateSubKey(@"shell\open\command"))
                        {
                            commandKey.SetValue("", $"\"{appPath}\" \"%1\"");
                        }
                    }
                }

                // 通知系统图标缓存更新
                SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, IntPtr.Zero, IntPtr.Zero);
                
                Debug.WriteLine("文件关联注册成功");
            }
            catch (Exception ex)
            {
                // 注册失败时不影响程序运行
                Debug.WriteLine($"注册文件关联失败: {ex.Message}");
            }
        }

        /// <summary>
        /// 注销文件关联
        /// </summary>
        public static void UnregisterFileAssociation()
        {
            try
            {
                using (RegistryKey rootKey = Registry.CurrentUser.OpenSubKey(@"Software\Classes", true))
                {
                    if (rootKey != null)
                    {
                        // 删除扩展名映射
                        rootKey.DeleteSubKey(Extension, false);
                        // 删除ProgId
                        rootKey.DeleteSubKeyTree(ProgId);
                    }
                }

                // 通知系统图标缓存更新
                SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, IntPtr.Zero, IntPtr.Zero);
                
                Debug.WriteLine("文件关联注销成功");
            }
            catch (Exception ex)
            {
                Debug.WriteLine($"注销文件关联失败: {ex.Message}");
            }
        }

        /// <summary>
        /// 检查文件关联是否已注册
        /// </summary>
        public static bool IsFileAssociationRegistered()
        {
            try
            {
                using (RegistryKey key = Registry.CurrentUser.OpenSubKey($@"Software\Classes\{Extension}"))
                {
                    return key != null && key.GetValue("") != null && key.GetValue("").ToString() == ProgId;
                }
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// 以管理员权限重新注册文件关联
        /// </summary>
        public static void RegisterFileAssociationWithAdmin()
        {
            try
            {
                ProcessStartInfo startInfo = new ProcessStartInfo
                {
                    FileName = Application.ExecutablePath,
                    Verb = "runas",
                    Arguments = "--register-association",
                    UseShellExecute = true
                };
                Process.Start(startInfo);
            }
            catch (Exception ex)
            {
                Debug.WriteLine($"以管理员权限注册失败: {ex.Message}");
            }
        }
    }
}
