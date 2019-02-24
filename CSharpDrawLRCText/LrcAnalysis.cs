using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Text.RegularExpressions;
using System.Windows.Forms;

namespace CSharpDrawLRCText
{
    public class LrcAnalysis
    {
        private String lrcstr;
        private List<LrcInfo> list;

        /// <summary>
        /// 通过文件流打开文件，使用完FileStream记得要释放哦；
        /// </summary>
        /// <param name="lrc_file">文件流</param>
        public LrcAnalysis(FileStream lrc_file)
        {
            list = new List<LrcInfo>(); //创建list
            this.ReadFileToStr(lrc_file);
            ResolveLrc();       //解析
        }
        /// <summary>
        /// 通过时间返回歌词信息，如果没有时间段就返回null
        /// </summary>
        /// <param name="time">歌词时间</param>
        /// <param name="TotalTime">歌词长度时间，如果为-1就是最后一行歌词</param>
        /// <returns>歌词信息</returns>
        public LrcInfo getLrcInfo(long time,out long TotalTime) {
            LrcInfo tempinfo = new LrcInfo();
            tempinfo.Time = time;
            tempinfo.Lrcstr = "";
            int index = list.FindIndex(delegate(LrcInfo lrc) { return lrc.Equals(tempinfo); });
            //if (index == -1) {
            //    TotalTime = -1;
            //    return null;
            //}
            //LrcInfo info = list[index];
            //if (list.Count <= index + 1)
            //{
            //    TotalTime = -1;
            //}
            //else {
            //    TotalTime = list[index + 1].Time - info.Time;
            //}
            if (index - 1 < 0)
            {
                TotalTime = -1;
                return null;
            }
            LrcInfo info = list[index-1];
            if (index < 0)
            {
                TotalTime = -1;
            }
            else {
                TotalTime = list[index].Time - info.Time;
            }
            return info;
        }

        /// <summary>
        /// 读取文件流到字符串
        /// </summary>
        /// <param name="lrc_file">文件流</param>
        private void ReadFileToStr(FileStream lrc_file) {
            FileStream fs = null;
            StreamReader read = null;
            try
            {
                fs = lrc_file;
                read = new StreamReader(fs, Encoding.Default);
                StringBuilder sb = new StringBuilder();
                String line;
                while ((line = read.ReadLine()) != null) {
                    if ((line = line.Trim()).Equals("")) {
                        continue;
                    }
                    sb.Append(line+"\r\n");
                }
                this.lrcstr = sb.ToString();
            }
            catch (Exception ex)
            {
                throw ex;
            }
            finally
            {
                read.Close();
                fs.Close();
            }
        }

        /// <summary>
        /// 获取歌词字符串
        /// </summary>
        /// <returns>歌词字符串</returns>
        public override string ToString()
        {
            Regex ex = new Regex(@"\[.*?\]");
            return ex.Replace(this.lrcstr, "");
        }
        /// <summary>
        /// 解析歌词
        /// </summary>
        private void ResolveLrc() {
            String[] lrc_list;  //歌词数组
            lrc_list = this.lrcstr.Split(new char[] { '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries);
            Regex rex = new Regex(@"^((\[\d+:\d+\.\d+\])+)(.*?)$");
            for (int i = 0; i < lrc_list.Length; i++) {
                String a = lrc_list[i].Trim();
                MatchCollection SearchResults = rex.Matches(a);
                
                for (int j = 0; j < SearchResults.Count; j++) {
                    String lrc_str_line = SearchResults[j].Value.Replace("[", "");
                    String[] lrc_list_line = lrc_str_line.Split(']');
                    String lrc_str = lrc_list_line[lrc_list_line.Length - 1];
                    if (lrc_str.Equals("")) {
                        continue;
                    }
                    for (int t = 0; t < lrc_list_line.Length - 1; t++)
                    {
                        list.Add(new LrcInfo(TimeToDigital(lrc_list_line[t]), lrc_str));
                    }
                }
            }
            list.Sort();
        }
        /// <summary>
        /// 时间转毫秒
        /// </summary>
        /// <param name="time">时间</param>
        /// <returns>毫秒</returns>
        private long TimeToDigital(String time) {
            Regex rex = new Regex(@"^(\d+):(\d+)(\.(\d+))?$");
            String[] time_list = rex.Split(time);
            long digital = int.Parse(time_list[1]) * 60 * 1000 + int.Parse(time_list[2]) * 1000 + int.Parse(time_list[4]);
            return digital;
        }

    }
    /// <summary>
    /// 歌曲歌词信息
    /// </summary>
    public class LrcInfo : IComparable<LrcInfo>
    {
        private long time = 0;
        /// <summary>
        /// 时间
        /// </summary>
        public long Time
        {
            get { return time; }
            set { time = value; }
        }
        private String lrcstr = "";
        /// <summary>
        /// 歌词内容
        /// </summary>
        public String Lrcstr
        {
            get { return lrcstr; }
            set { lrcstr = value; }
        }
        public LrcInfo() {
            this.time = 0;
            this.lrcstr = "";
        }
        /// <summary>
        /// 创建歌词信息
        /// </summary>
        /// <param name="time">歌词时间</param>
        /// <param name="lrcstr">歌词字符串</param>
        public LrcInfo(long time, String lrcstr) {
            this.time = time;
            this.lrcstr = lrcstr;
        }
        /// <summary>
        /// 用于排序
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public int CompareTo(LrcInfo other)
        {
            if (this.Time > other.Time) {
                return 1;
            }
            else if (this.Time < other.Time)
            {
                return -1;
            }
            else {
                return 0;
            }
        }
        /// <summary>
        /// 如果时间相等就返回true
        /// </summary>
        /// <param name="obj"></param>
        /// <returns></returns>
        public override bool Equals(object obj)
        {
            LrcInfo lrcinfo = (LrcInfo)obj;
            if (lrcinfo.Time <= this.Time)
            {
                return true;
            }
            else {
                return false;
            }
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
        /// <summary>
        /// 获取歌词字符串
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return this.Lrcstr;
        }
    }
}
