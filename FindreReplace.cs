using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;

namespace CX900
{
    public class FindreReplace
    {

        /// <summary>
        /// 
        /// </summary>
        /// <param name="srt"></param>
        /// <param name="path"></param>
        /// <returns></returns>
        public int SearchText(string srt,string path)
        {
            int count;
            string search = srt;
            if (!string.IsNullOrEmpty(search))
            {
                string fileName = path;
                using (TextReader tr = File.OpenText(fileName))
                {
                    string content = tr.ReadToEnd();
                    count = CountNumber(content, search);
                    return count;
                }
            }
            return 0;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="father"></param>
        /// <param name="son"></param>
        /// <returns></returns>
        private int CountNumber(string father, string son)
        {
            //判断是否有相同字符串
            if (father.Contains(son))
            {
                //用一个字符串储存被替换后的整个字符串
                string strReplaced = father.Replace(son, "");
                //两个字符串的长度差值 / 被替换掉的字符串单位长度
                return (father.Length - strReplaced.Length) / son.Length;
            }
            //没有返回0个
            return 0;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="searchstr"></param>
        /// <param name="replacestr"></param>
        /// <param name="path"></param>
        /// <returns></returns>
        public int  Replace(string searchstr,string replacestr,string path)
        {
            string search = searchstr;
            string replace = replacestr;
            if (!string.IsNullOrEmpty(search))
            {
                string fileName = path;
                string content, result;
                using (TextReader tr = File.OpenText(fileName))
                {
                    content = tr.ReadToEnd();
                    result = content.Replace(search, replace);

                }
                //写入文件
                using (FileStream fs = File.Open(fileName, FileMode.Create, FileAccess.Write, FileShare.None))
                {
                    Byte[] info = new UTF8Encoding(true).GetBytes(result);
                    fs.Write(info, 0, info.Length);
                }
                int count = CountNumber(content, search);
                return count;
            }
            return 0;

        }
    }
}
