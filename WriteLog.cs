using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CX900
{


public static class LogWriter
    {
        // 日志文件路径，默认在程序运行目录下
        private static string _logFilePath = "LOG.TXT";

        /// <summary>
        /// 设置日志文件路径
        /// </summary>
        /// <param name="path">自定义日志文件路径</param>
        public static void SetLogPath(string path)
        {
            _logFilePath = path;
        }

        /// <summary>
        /// 将字符串追加写入日志文件
        /// </summary>
        /// <param name="content">要写入的内容</param>
        /// <param name="includeTimestamp">是否包含时间戳</param>
        /// <returns>是否写入成功</returns>
        public static bool WriteToLog(string content, bool includeTimestamp = true)
        {
            try
            {
                // 准备要写入的内容，可选添加时间戳
                string logContent = includeTimestamp
                    ? $"[{DateTime.Now:yyyy-MM-dd HH:mm:ss}] {content}{Environment.NewLine}"
                    : $"{content}{Environment.NewLine}";

                // 追加写入文件，若文件不存在则自动创建
                // 使用UTF8编码避免中文乱码
                File.AppendAllText(_logFilePath, logContent, Encoding.UTF8);
                return true;
            }
            catch (Exception ex)
            {
                // 处理可能的异常（如权限不足、路径错误等）
                Console.WriteLine($"写入日志失败: {ex.Message}");
                return false;
            }
        }
    }
}

