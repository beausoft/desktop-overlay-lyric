namespace player
{
    partial class WinMainForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(WinMainForm));
            this.timerLRC = new System.Windows.Forms.Timer(this.components);
            this.btnHideLRC = new System.Windows.Forms.Button();
            this.btnShowLRC = new System.Windows.Forms.Button();
            this.btnOpenMusic = new System.Windows.Forms.Button();
            this.btnOpenLrc = new System.Windows.Forms.Button();
            this.rBtnBlue = new System.Windows.Forms.RadioButton();
            this.rBtnGreen = new System.Windows.Forms.RadioButton();
            this.gboxStyles = new System.Windows.Forms.GroupBox();
            this.rBtnYellow = new System.Windows.Forms.RadioButton();
            this.rBtnWhite = new System.Windows.Forms.RadioButton();
            this.rBtnRed = new System.Windows.Forms.RadioButton();
            this.wmpPlay = new AxWMPLib.AxWindowsMediaPlayer();
            this.btnLock = new System.Windows.Forms.Button();
            this.btnFont = new System.Windows.Forms.Button();
            this.dlgFont = new System.Windows.Forms.FontDialog();
            this.gboxStyles.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.wmpPlay)).BeginInit();
            this.SuspendLayout();
            // 
            // timerLRC
            // 
            this.timerLRC.Interval = 30;
            this.timerLRC.Tick += new System.EventHandler(this.timerLRC_Tick);
            // 
            // btnHideLRC
            // 
            this.btnHideLRC.Location = new System.Drawing.Point(127, 217);
            this.btnHideLRC.Name = "btnHideLRC";
            this.btnHideLRC.Size = new System.Drawing.Size(109, 36);
            this.btnHideLRC.TabIndex = 1;
            this.btnHideLRC.Text = "隐藏桌面歌词";
            this.btnHideLRC.UseVisualStyleBackColor = true;
            this.btnHideLRC.Click += new System.EventHandler(this.btnHideLRC_Click);
            // 
            // btnShowLRC
            // 
            this.btnShowLRC.Location = new System.Drawing.Point(12, 217);
            this.btnShowLRC.Name = "btnShowLRC";
            this.btnShowLRC.Size = new System.Drawing.Size(109, 36);
            this.btnShowLRC.TabIndex = 2;
            this.btnShowLRC.Text = "显示桌面歌词";
            this.btnShowLRC.UseVisualStyleBackColor = true;
            this.btnShowLRC.Click += new System.EventHandler(this.btnShowLRC_Click);
            // 
            // btnOpenMusic
            // 
            this.btnOpenMusic.Location = new System.Drawing.Point(12, 12);
            this.btnOpenMusic.Name = "btnOpenMusic";
            this.btnOpenMusic.Size = new System.Drawing.Size(75, 29);
            this.btnOpenMusic.TabIndex = 3;
            this.btnOpenMusic.Text = "打开音乐";
            this.btnOpenMusic.UseVisualStyleBackColor = true;
            this.btnOpenMusic.Click += new System.EventHandler(this.btnOpenMusic_Click);
            // 
            // btnOpenLrc
            // 
            this.btnOpenLrc.Location = new System.Drawing.Point(104, 12);
            this.btnOpenLrc.Name = "btnOpenLrc";
            this.btnOpenLrc.Size = new System.Drawing.Size(75, 29);
            this.btnOpenLrc.TabIndex = 4;
            this.btnOpenLrc.Text = "打开歌词";
            this.btnOpenLrc.UseVisualStyleBackColor = true;
            this.btnOpenLrc.Click += new System.EventHandler(this.btnOpenLrc_Click);
            // 
            // rBtnBlue
            // 
            this.rBtnBlue.AutoSize = true;
            this.rBtnBlue.Checked = true;
            this.rBtnBlue.Location = new System.Drawing.Point(35, 33);
            this.rBtnBlue.Name = "rBtnBlue";
            this.rBtnBlue.Size = new System.Drawing.Size(58, 19);
            this.rBtnBlue.TabIndex = 7;
            this.rBtnBlue.TabStop = true;
            this.rBtnBlue.Tag = "1";
            this.rBtnBlue.Text = "蓝色";
            this.rBtnBlue.UseVisualStyleBackColor = true;
            this.rBtnBlue.CheckedChanged += new System.EventHandler(this.rBtnStyles_CheckedChanged);
            // 
            // rBtnGreen
            // 
            this.rBtnGreen.AutoSize = true;
            this.rBtnGreen.Location = new System.Drawing.Point(122, 33);
            this.rBtnGreen.Name = "rBtnGreen";
            this.rBtnGreen.Size = new System.Drawing.Size(58, 19);
            this.rBtnGreen.TabIndex = 8;
            this.rBtnGreen.Tag = "2";
            this.rBtnGreen.Text = "绿色";
            this.rBtnGreen.UseVisualStyleBackColor = true;
            this.rBtnGreen.CheckedChanged += new System.EventHandler(this.rBtnStyles_CheckedChanged);
            // 
            // gboxStyles
            // 
            this.gboxStyles.Controls.Add(this.rBtnYellow);
            this.gboxStyles.Controls.Add(this.rBtnWhite);
            this.gboxStyles.Controls.Add(this.rBtnRed);
            this.gboxStyles.Controls.Add(this.rBtnBlue);
            this.gboxStyles.Controls.Add(this.rBtnGreen);
            this.gboxStyles.Location = new System.Drawing.Point(12, 272);
            this.gboxStyles.Name = "gboxStyles";
            this.gboxStyles.Size = new System.Drawing.Size(504, 73);
            this.gboxStyles.TabIndex = 9;
            this.gboxStyles.TabStop = false;
            this.gboxStyles.Text = "颜色风格";
            // 
            // rBtnYellow
            // 
            this.rBtnYellow.AutoSize = true;
            this.rBtnYellow.Location = new System.Drawing.Point(383, 33);
            this.rBtnYellow.Name = "rBtnYellow";
            this.rBtnYellow.Size = new System.Drawing.Size(58, 19);
            this.rBtnYellow.TabIndex = 11;
            this.rBtnYellow.Tag = "5";
            this.rBtnYellow.Text = "黄色";
            this.rBtnYellow.UseVisualStyleBackColor = true;
            this.rBtnYellow.CheckedChanged += new System.EventHandler(this.rBtnStyles_CheckedChanged);
            // 
            // rBtnWhite
            // 
            this.rBtnWhite.AutoSize = true;
            this.rBtnWhite.Location = new System.Drawing.Point(296, 33);
            this.rBtnWhite.Name = "rBtnWhite";
            this.rBtnWhite.Size = new System.Drawing.Size(58, 19);
            this.rBtnWhite.TabIndex = 10;
            this.rBtnWhite.Tag = "4";
            this.rBtnWhite.Text = "白色";
            this.rBtnWhite.UseVisualStyleBackColor = true;
            this.rBtnWhite.CheckedChanged += new System.EventHandler(this.rBtnStyles_CheckedChanged);
            // 
            // rBtnRed
            // 
            this.rBtnRed.AutoSize = true;
            this.rBtnRed.Location = new System.Drawing.Point(209, 33);
            this.rBtnRed.Name = "rBtnRed";
            this.rBtnRed.Size = new System.Drawing.Size(58, 19);
            this.rBtnRed.TabIndex = 9;
            this.rBtnRed.Tag = "3";
            this.rBtnRed.Text = "红色";
            this.rBtnRed.UseVisualStyleBackColor = true;
            this.rBtnRed.CheckedChanged += new System.EventHandler(this.rBtnStyles_CheckedChanged);
            // 
            // wmpPlay
            // 
            this.wmpPlay.Enabled = true;
            this.wmpPlay.Location = new System.Drawing.Point(12, 58);
            this.wmpPlay.Name = "wmpPlay";
            this.wmpPlay.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("wmpPlay.OcxState")));
            this.wmpPlay.Size = new System.Drawing.Size(504, 138);
            this.wmpPlay.TabIndex = 0;
            this.wmpPlay.PlayStateChange += new AxWMPLib._WMPOCXEvents_PlayStateChangeEventHandler(this.wmpPlay_PlayStateChange);
            // 
            // btnLock
            // 
            this.btnLock.Location = new System.Drawing.Point(242, 217);
            this.btnLock.Name = "btnLock";
            this.btnLock.Size = new System.Drawing.Size(109, 36);
            this.btnLock.TabIndex = 10;
            this.btnLock.Text = "锁定歌词";
            this.btnLock.UseVisualStyleBackColor = true;
            this.btnLock.Click += new System.EventHandler(this.btnLock_Click);
            // 
            // btnFont
            // 
            this.btnFont.Location = new System.Drawing.Point(357, 217);
            this.btnFont.Name = "btnFont";
            this.btnFont.Size = new System.Drawing.Size(109, 36);
            this.btnFont.TabIndex = 11;
            this.btnFont.Text = "设置字体";
            this.btnFont.UseVisualStyleBackColor = true;
            this.btnFont.Click += new System.EventHandler(this.btnFont_Click);
            // 
            // dlgFont
            // 
            this.dlgFont.AllowScriptChange = false;
            this.dlgFont.AllowSimulations = false;
            this.dlgFont.AllowVectorFonts = false;
            this.dlgFont.AllowVerticalFonts = false;
            this.dlgFont.Font = new System.Drawing.Font("黑体", 42F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.dlgFont.ScriptsOnly = true;
            this.dlgFont.ShowEffects = false;
            // 
            // WinMainForm
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Inherit;
            this.ClientSize = new System.Drawing.Size(533, 372);
            this.Controls.Add(this.btnFont);
            this.Controls.Add(this.btnLock);
            this.Controls.Add(this.gboxStyles);
            this.Controls.Add(this.btnOpenLrc);
            this.Controls.Add(this.btnOpenMusic);
            this.Controls.Add(this.btnShowLRC);
            this.Controls.Add(this.btnHideLRC);
            this.Controls.Add(this.wmpPlay);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "WinMainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "播放器";
            this.gboxStyles.ResumeLayout(false);
            this.gboxStyles.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.wmpPlay)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Timer timerLRC;
        private AxWMPLib.AxWindowsMediaPlayer wmpPlay;
        private System.Windows.Forms.Button btnHideLRC;
        private System.Windows.Forms.Button btnShowLRC;
        private System.Windows.Forms.Button btnOpenMusic;
        private System.Windows.Forms.Button btnOpenLrc;
        private System.Windows.Forms.RadioButton rBtnBlue;
        private System.Windows.Forms.RadioButton rBtnGreen;
        private System.Windows.Forms.GroupBox gboxStyles;
        private System.Windows.Forms.RadioButton rBtnRed;
        private System.Windows.Forms.RadioButton rBtnWhite;
        private System.Windows.Forms.RadioButton rBtnYellow;
        private System.Windows.Forms.Button btnLock;
        private System.Windows.Forms.Button btnFont;
        private System.Windows.Forms.FontDialog dlgFont;
    }
}

