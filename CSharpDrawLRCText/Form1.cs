using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace CSharpDrawLRCText
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        LrcAnalysis lrcanalysis = null;
        dld lrc_fun = null;
        private void btoOpenMusic_Click(object sender, EventArgs e)
        {
            OpenFileDialog opendia = new OpenFileDialog();
            opendia.Filter="MP3文件(*.mp3)|*.mp3|所有文件(*.*)|*.*";
            DialogResult res = opendia.ShowDialog();
            if (res == System.Windows.Forms.DialogResult.Yes || res == System.Windows.Forms.DialogResult.OK)
            {
                wmpPlay.URL = opendia.FileName;
            }
        }

        private void btoOpenLrc_Click(object sender, EventArgs e)
        {
            OpenFileDialog opendia = new OpenFileDialog();
            opendia.Filter = "LRC文件(*.lrc)|*.lrc|所有文件(*.*)|*.*";
            DialogResult res = opendia.ShowDialog();
            if (res == System.Windows.Forms.DialogResult.Yes || res == System.Windows.Forms.DialogResult.OK)
            {
                FileStream file = File.Open(opendia.FileName, FileMode.Open);
                lrcanalysis = new LrcAnalysis(file);
                file.Close();
            }
        }
        int tmp_i = 0;
        String lrc_temp = "";
        private void timeLrcTime_Tick(object sender, EventArgs e)
        {
            if (lrcanalysis != null) {
                //lblLrcText.Text=lrcanalysis.getLrcInfo(wmpPlay.currentMedia.
                //lblLrcText.Text = "ss:" + wmpPlay.currentMedia.duration.ToString();获取总时间秒
                //lblLrcText.Text=wmpPlay.Ctlcontrols.currentPosition.ToString();获取当前进度
                long temp = 0;
                LrcInfo info = lrcanalysis.getLrcInfo((long)(wmpPlay.Ctlcontrols.currentPosition * 1000), out temp);
                if (info != null) {
                    lblLrcText.Text = info.Lrcstr;
                    lbl_trim.Text = (temp / 1000).ToString();
                    if (!lrc_temp.Equals(info.Lrcstr))
                    {
                        lrc_temp = info.Lrcstr;
                        tmp_i = 0;
                        //dll动态链接库歌词程序
                        byte[] tempStr = Encoding.Default.GetBytes(info.Lrcstr);
                        byte[] tempDef = Encoding.Convert(Encoding.Default, Encoding.Unicode, tempStr);
                        //String lrcstr = Encoding.Unicode.GetString(tempDef);

                        lrc_fun.LoadFun("DrawLRC_SHOW_TEXT");
                        object[] Parameters = new object[] { (byte[])tempDef };
                        Type[] ParameterTypes = new Type[] { typeof(byte[]) };
                        ModePass[] themode = new ModePass[] { ModePass.ByValue };
                        Type Type_Return = typeof(void);
                        lrc_fun.Invoke(Parameters, ParameterTypes, themode, Type_Return);
                        lrc_fun.LoadFun("SetDrawLRCTime");
                        Parameters = new object[] { (long)(temp / 1000) };
                        ParameterTypes = new Type[] { typeof(long) };
                        themode = new ModePass[] { ModePass.ByValue };
                        lrc_fun.Invoke(Parameters, ParameterTypes, themode, Type_Return);
                    }
                }
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            lbltime_tmp.Text = (++tmp_i).ToString();
        }

        private void btoTextTimer_Click(object sender, EventArgs e)
        {
            tmp_i = 0;
        }

        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            DialogResult result = MessageBox.Show("确定要退出？", "提示", MessageBoxButtons.YesNo, MessageBoxIcon.Information);
            if (result == System.Windows.Forms.DialogResult.Yes)
            {
                e.Cancel = false;
            }
            else {
                e.Cancel = true;
            }
        }

        protected override void OnLoad(EventArgs e)
        {
            lrc_fun = new dld();
            lrc_fun.LoadDll("DrawLRC_DLL.dll");
            lrc_fun.LoadFun("InitGDI");

            object[] Parameters = new object[] { };
            Type[] ParameterTypes = new Type[] { };
            ModePass[] themode = new ModePass[] { };
            Type Type_Return = typeof(void);
            lrc_fun.Invoke(Parameters, ParameterTypes, themode, Type_Return);
            lrc_fun.LoadFun("CreateLRC");
            lrc_fun.Invoke(Parameters, ParameterTypes, themode, Type_Return);

            base.OnLoad(e);
        }

        private void btoLockingLrc_Click(object sender, EventArgs e)
        {
            object[] Parameters = new object[] { };
            Type[] ParameterTypes = new Type[] { };
            ModePass[] themode = new ModePass[] { };
            Type Type_Return = typeof(void);
            lrc_fun.LoadFun("LockingLRC");
            lrc_fun.Invoke(Parameters, ParameterTypes, themode, Type_Return);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            cboLrcColor.SelectedIndex = 3;
        }
        bool iscboColor = false;
        private void cboLrcColor_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (!iscboColor) {
                iscboColor = true;
                return;
            }
            String colorstr = cboLrcColor.Text;
            if (colorstr.Equals("")) {
                return;
            }
            int index = 1;
            if (colorstr.Equals("蓝色"))
            {
                index = 1;
            }
            else if (colorstr.Equals("绿色"))
            { index = 2; }
            else if (colorstr.Equals("红色"))
            { index = 3; }
            else if (colorstr.Equals("白色"))
            { index = 4; }
            else if (colorstr.Equals("黄色"))
            { index = 5; }
            object[] Parameters = new object[] { (int)index };
            Type[] ParameterTypes = new Type[] { typeof(int) };
            ModePass[] themode = new ModePass[] { ModePass.ByValue };
            Type Type_Return = typeof(void);
            lrc_fun.LoadFun("SetLRCColor");
            lrc_fun.Invoke(Parameters, ParameterTypes, themode, Type_Return);
        }
    }
}
