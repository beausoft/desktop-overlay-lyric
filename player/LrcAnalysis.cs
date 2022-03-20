using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Text.RegularExpressions;

namespace player
{
    public class LrcAnalysis
    {
        private string lrcstr;
        private readonly List<LrcInfo> list;

        /// <summary>
        /// 通过文件流打开文件，使用完FileStream记得要释放哦；
        /// </summary>
        /// <param name="lrc_file">文件流</param>
        public LrcAnalysis(FileStream lrc_file)
        {
            list = new List<LrcInfo>(); //创建list
            ReadFileToStr(lrc_file);
            ResolveLrc();       //解析
        }
        /// <summary>
        /// 通过时间返回歌词信息，如果没有时间段没有歌词就返回null
        /// </summary>
        /// <param name="time">歌词时间</param>
        /// <param name="nextTime">返回下一句歌词的开始时间</param>
        /// <returns>歌词信息</returns>
        public LrcInfo getLrcInfo(long time, out long nextTime)
        {
            if (list.Count <= 0) {
                nextTime = -1;
                return null;
            }
            int index = list.FindLastIndex(delegate (LrcInfo lrc) {
                return time > lrc.Time;
            });
            if (index == -1) {
                nextTime = list[0].Time;
                return null;
            }
            LrcInfo info = list[index];
            if (index + 1 < list.Count)
            {
                nextTime = list[index + 1].Time;
            }
            else {
                nextTime = long.MaxValue;
            }
            return info;
        }

        /// <summary>
        /// 读取文件流到字符串
        /// </summary>
        /// <param name="lrc_file">文件流</param>
        private void ReadFileToStr(FileStream lrc_file)
        {
            FileStream fs = null;
            StreamReader read = null;
            try
            {
                fs = lrc_file;
                read = new StreamReader(fs, Encoding.Default);
                StringBuilder sb = new StringBuilder();
                string line;
                while ((line = read.ReadLine()) != null)
                {
                    if ((line = line.Trim()).Equals(""))
                    {
                        continue;
                    }
                    sb.Append(line + "\r\n");
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
        private void ResolveLrc()
        {
            string[] lrc_list;  //歌词数组
            lrc_list = this.lrcstr.Split(new char[] { '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries);
            Regex rex = new Regex(@"^((\[\d+:\d+\.\d+\])+)(.*?)$");
            for (int i = 0; i < lrc_list.Length; i++)
            {
                string a = lrc_list[i].Trim();
                MatchCollection SearchResults = rex.Matches(a);

                for (int j = 0; j < SearchResults.Count; j++)
                {
                    string lrc_str_line = SearchResults[j].Value.Replace("[", "");
                    string[] lrc_list_line = lrc_str_line.Split(']');
                    string lrc_str = lrc_list_line[lrc_list_line.Length - 1];
                    if (lrc_str.Equals(""))
                    {
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
        private long TimeToDigital(string time)
        {
            Regex rex = new Regex(@"^(\d+):(\d+)(\.(\d+))?$");
            string[] time_list = rex.Split(time);
            long digital = int.Parse(time_list[1]) * 60 * 1000 + int.Parse(time_list[2]) * 1000 + int.Parse(time_list[4]);
            return digital;
        }

    }
    /// <summary>
    /// 歌曲歌词信息
    /// </summary>
    public class LrcInfo : IComparable<LrcInfo>
    {
        /// <summary>
        /// 时间
        /// </summary>
        public long Time { get; set; } = 0;

        /// <summary>
        /// 歌词内容
        /// </summary>
        public string Lrcstr { get; set; } = "";
        public LrcInfo()
        {
            Time = 0;
            Lrcstr = "";
        }
        /// <summary>
        /// 创建歌词信息
        /// </summary>
        /// <param name="time">歌词时间</param>
        /// <param name="lrcstr">歌词字符串</param>
        public LrcInfo(long time, string lrcstr)
        {
            Time = time;
            Lrcstr = lrcstr;
        }
        /// <summary>
        /// 用于排序
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public int CompareTo(LrcInfo other)
        {
            if (Time > other.Time)
            {
                return 1;
            }
            else if (Time < other.Time)
            {
                return -1;
            }
            else
            {
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
            if (lrcinfo.Time <= Time)
            {
                return true;
            }
            else
            {
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
            return Lrcstr;
        }
    }
}
