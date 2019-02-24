namespace CSharpDrawLRCText
{
    partial class Form1
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
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.btoOpenMusic = new System.Windows.Forms.Button();
            this.btoOpenLrc = new System.Windows.Forms.Button();
            this.timeLrcTime = new System.Windows.Forms.Timer(this.components);
            this.lblLrcText = new System.Windows.Forms.Label();
            this.lbltime_tmp = new System.Windows.Forms.Label();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.btoTextTimer = new System.Windows.Forms.Button();
            this.wmpPlay = new AxWMPLib.AxWindowsMediaPlayer();
            this.lbl_trim = new System.Windows.Forms.Label();
            this.btoLockingLrc = new System.Windows.Forms.Button();
            this.cboLrcColor = new System.Windows.Forms.ComboBox();
            ((System.ComponentModel.ISupportInitialize)(this.wmpPlay)).BeginInit();
            this.SuspendLayout();
            // 
            // btoOpenMusic
            // 
            this.btoOpenMusic.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btoOpenMusic.Location = new System.Drawing.Point(13, 293);
            this.btoOpenMusic.Name = "btoOpenMusic";
            this.btoOpenMusic.Size = new System.Drawing.Size(75, 23);
            this.btoOpenMusic.TabIndex = 1;
            this.btoOpenMusic.Text = "打开歌曲";
            this.btoOpenMusic.UseVisualStyleBackColor = true;
            this.btoOpenMusic.Click += new System.EventHandler(this.btoOpenMusic_Click);
            // 
            // btoOpenLrc
            // 
            this.btoOpenLrc.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btoOpenLrc.Location = new System.Drawing.Point(94, 293);
            this.btoOpenLrc.Name = "btoOpenLrc";
            this.btoOpenLrc.Size = new System.Drawing.Size(75, 23);
            this.btoOpenLrc.TabIndex = 1;
            this.btoOpenLrc.Text = "打开歌词";
            this.btoOpenLrc.UseVisualStyleBackColor = true;
            this.btoOpenLrc.Click += new System.EventHandler(this.btoOpenLrc_Click);
            // 
            // timeLrcTime
            // 
            this.timeLrcTime.Enabled = true;
            this.timeLrcTime.Tick += new System.EventHandler(this.timeLrcTime_Tick);
            // 
            // lblLrcText
            // 
            this.lblLrcText.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.lblLrcText.Font = new System.Drawing.Font("Arial Narrow", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblLrcText.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(192)))));
            this.lblLrcText.Location = new System.Drawing.Point(12, 334);
            this.lblLrcText.Name = "lblLrcText";
            this.lblLrcText.Size = new System.Drawing.Size(544, 38);
            this.lblLrcText.TabIndex = 2;
            this.lblLrcText.Text = "歌词显示区域";
            this.lblLrcText.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lbltime_tmp
            // 
            this.lbltime_tmp.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.lbltime_tmp.AutoSize = true;
            this.lbltime_tmp.ForeColor = System.Drawing.Color.Red;
            this.lbltime_tmp.Location = new System.Drawing.Point(515, 318);
            this.lbltime_tmp.Name = "lbltime_tmp";
            this.lbltime_tmp.Size = new System.Drawing.Size(41, 12);
            this.lbltime_tmp.TabIndex = 3;
            this.lbltime_tmp.Text = "label1";
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // btoTextTimer
            // 
            this.btoTextTimer.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btoTextTimer.Location = new System.Drawing.Point(481, 293);
            this.btoTextTimer.Name = "btoTextTimer";
            this.btoTextTimer.Size = new System.Drawing.Size(75, 23);
            this.btoTextTimer.TabIndex = 4;
            this.btoTextTimer.Text = "测试计时";
            this.btoTextTimer.UseVisualStyleBackColor = true;
            this.btoTextTimer.Click += new System.EventHandler(this.btoTextTimer_Click);
            // 
            // wmpPlay
            // 
            this.wmpPlay.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.wmpPlay.Enabled = true;
            this.wmpPlay.Location = new System.Drawing.Point(12, 12);
            this.wmpPlay.Name = "wmpPlay";
            this.wmpPlay.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("wmpPlay.OcxState")));
            this.wmpPlay.Size = new System.Drawing.Size(544, 265);
            this.wmpPlay.TabIndex = 0;
            // 
            // lbl_trim
            // 
            this.lbl_trim.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.lbl_trim.AutoSize = true;
            this.lbl_trim.ForeColor = System.Drawing.Color.Coral;
            this.lbl_trim.Location = new System.Drawing.Point(458, 318);
            this.lbl_trim.Name = "lbl_trim";
            this.lbl_trim.Size = new System.Drawing.Size(41, 12);
            this.lbl_trim.TabIndex = 5;
            this.lbl_trim.Text = "label1";
            // 
            // btoLockingLrc
            // 
            this.btoLockingLrc.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btoLockingLrc.Location = new System.Drawing.Point(176, 293);
            this.btoLockingLrc.Name = "btoLockingLrc";
            this.btoLockingLrc.Size = new System.Drawing.Size(75, 23);
            this.btoLockingLrc.TabIndex = 6;
            this.btoLockingLrc.Text = "锁定歌词";
            this.btoLockingLrc.UseVisualStyleBackColor = true;
            this.btoLockingLrc.Click += new System.EventHandler(this.btoLockingLrc_Click);
            // 
            // cboLrcColor
            // 
            this.cboLrcColor.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.cboLrcColor.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboLrcColor.FormattingEnabled = true;
            this.cboLrcColor.Items.AddRange(new object[] {
            "蓝色",
            "绿色",
            "红色",
            "白色",
            "黄色"});
            this.cboLrcColor.Location = new System.Drawing.Point(258, 293);
            this.cboLrcColor.Name = "cboLrcColor";
            this.cboLrcColor.Size = new System.Drawing.Size(121, 20);
            this.cboLrcColor.TabIndex = 7;
            this.cboLrcColor.SelectedIndexChanged += new System.EventHandler(this.cboLrcColor_SelectedIndexChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(568, 381);
            this.Controls.Add(this.cboLrcColor);
            this.Controls.Add(this.btoLockingLrc);
            this.Controls.Add(this.lbl_trim);
            this.Controls.Add(this.btoTextTimer);
            this.Controls.Add(this.lbltime_tmp);
            this.Controls.Add(this.lblLrcText);
            this.Controls.Add(this.btoOpenLrc);
            this.Controls.Add(this.btoOpenMusic);
            this.Controls.Add(this.wmpPlay);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.wmpPlay)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private AxWMPLib.AxWindowsMediaPlayer wmpPlay;
        private System.Windows.Forms.Button btoOpenMusic;
        private System.Windows.Forms.Button btoOpenLrc;
        private System.Windows.Forms.Timer timeLrcTime;
        private System.Windows.Forms.Label lblLrcText;
        private System.Windows.Forms.Label lbltime_tmp;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button btoTextTimer;
        private System.Windows.Forms.Label lbl_trim;
        private System.Windows.Forms.Button btoLockingLrc;
        private System.Windows.Forms.ComboBox cboLrcColor;


    }
}

