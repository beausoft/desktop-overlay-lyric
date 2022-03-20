using System;
using System.IO;
using System.Windows.Forms;

namespace player
{
    public partial class WinMainForm : Form
    {

        private LrcAnalysis lrcAnalysis = null;
        private Lyric lyric;

        public WinMainForm()
        {
            InitializeComponent();
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            wmpPlay.enableContextMenu = false;
            wmpPlay.settings.autoStart = false;
            lyric = new Lyric();
            lyric.SetText("桌面歌词C#测试程序");
            lyric.Show();
            lyric.Update();
        }

        protected override void OnClosed(EventArgs e)
        {
            base.OnClosed(e);
            lyric.Close();
        }

        private void btnOpenMusic_Click(object sender, EventArgs e)
        {
            OpenFileDialog opendia = new OpenFileDialog();
            opendia.Filter = "MP3文件(*.mp3)|*.mp3|所有文件(*.*)|*.*";
            DialogResult res = opendia.ShowDialog();
            if (res == System.Windows.Forms.DialogResult.Yes || res == System.Windows.Forms.DialogResult.OK)
            {
                wmpPlay.URL = opendia.FileName;
            }
        }

        private void btnOpenLrc_Click(object sender, EventArgs e)
        {
            OpenFileDialog opendia = new OpenFileDialog();
            opendia.Filter = "LRC文件(*.lrc)|*.lrc|所有文件(*.*)|*.*";
            DialogResult res = opendia.ShowDialog();
            if (res == System.Windows.Forms.DialogResult.Yes || res == System.Windows.Forms.DialogResult.OK)
            {
                FileStream file = File.Open(opendia.FileName, FileMode.Open);
                lrcAnalysis = new LrcAnalysis(file);
                file.Close();
            }
        }

        private void btnShowLRC_Click(object sender, EventArgs e)
        {
            lyric.Show();
        }

        private void btnHideLRC_Click(object sender, EventArgs e)
        {
            lyric.Hide();
        }

        private void rBtnStyles_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rBtn = (RadioButton)sender;
            int style = int.Parse(rBtn.Tag.ToString());
            lyric.SetColorStyle(style);
            lyric.Update();
        }

        private void timerLRC_Tick(object sender, EventArgs e)
        {
            if (lrcAnalysis != null) {
                long currentTime = (long)(wmpPlay.Ctlcontrols.currentPosition * 1000);
                LrcInfo info = lrcAnalysis.getLrcInfo(currentTime, out long nextTime);
                if (info != null)
                {
                    lyric.SetText(info.Lrcstr);
                    if (nextTime != -1)
                    {
                        float scale = (currentTime - (float)info.Time) / (nextTime - (float)info.Time);
                        lyric.SetScale(scale);
                    }
                    lyric.Update();
                }
                else {
                    lyric.SetText("");
                    lyric.Update();
                }
            }
        }

        private void wmpPlay_PlayStateChange(object sender, AxWMPLib._WMPOCXEvents_PlayStateChangeEvent e)
        {
            // wmppsUndefined = 0, wmppsStopped = 1, wmppsPaused = 2, wmppsPlaying = 3, wmppsScanForward = 4, wmppsScanReverse = 5, wmppsBuffering = 6, wmppsWaiting = 7, wmppsMediaEnded = 8, wmppsTransitioning = 9, wmppsReady = 10, wmppsReconnecting = 11, wmppsLast = 12
            if (e.newState == 3)
            {
                timerLRC.Enabled = true;
            }
            else if (e.newState == 1 || e.newState == 2) {
                timerLRC.Enabled = false;
            }
        }

        private void btnLock_Click(object sender, EventArgs e)
        {
            Button btn = (Button)sender;
            if (btn.Text.Equals("锁定歌词"))
            {
                btn.Text = "解锁歌词";
                lyric.SetLock(true);
            }
            else {
                btn.Text = "锁定歌词";
                lyric.SetLock(false);
            }
        }

        private void btnFont_Click(object sender, EventArgs e)
        {
            DialogResult result =  dlgFont.ShowDialog();
            if (result == DialogResult.OK || result == DialogResult.Yes) {
                lyric.SetFont(dlgFont.Font.Name, dlgFont.Font.Size);
                lyric.Update();
            }
        }
    }
}
