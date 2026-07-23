namespace CX900
{
    partial class DL_form
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(DL_form));
            this.tb_iapfilepath = new System.Windows.Forms.TextBox();
            this.bt_slectfile = new System.Windows.Forms.Button();
            this.progressBar2 = new System.Windows.Forms.ProgressBar();
            this.bt_updataiap = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.lb_downloadrasult = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // tb_iapfilepath
            // 
            this.tb_iapfilepath.Location = new System.Drawing.Point(12, 103);
            this.tb_iapfilepath.Name = "tb_iapfilepath";
            this.tb_iapfilepath.Size = new System.Drawing.Size(402, 21);
            this.tb_iapfilepath.TabIndex = 0;
            // 
            // bt_slectfile
            // 
            this.bt_slectfile.Location = new System.Drawing.Point(420, 103);
            this.bt_slectfile.Name = "bt_slectfile";
            this.bt_slectfile.Size = new System.Drawing.Size(75, 23);
            this.bt_slectfile.TabIndex = 1;
            this.bt_slectfile.Text = "打开文件";
            this.bt_slectfile.UseVisualStyleBackColor = true;
            this.bt_slectfile.Click += new System.EventHandler(this.bt_slectfile_Click);
            // 
            // progressBar2
            // 
            this.progressBar2.BackColor = System.Drawing.SystemColors.Control;
            this.progressBar2.Location = new System.Drawing.Point(12, 76);
            this.progressBar2.Name = "progressBar2";
            this.progressBar2.Size = new System.Drawing.Size(564, 21);
            this.progressBar2.TabIndex = 2;
            // 
            // bt_updataiap
            // 
            this.bt_updataiap.Location = new System.Drawing.Point(501, 103);
            this.bt_updataiap.Name = "bt_updataiap";
            this.bt_updataiap.Size = new System.Drawing.Size(75, 23);
            this.bt_updataiap.TabIndex = 3;
            this.bt_updataiap.Text = "开始升级";
            this.bt_updataiap.UseVisualStyleBackColor = true;
            this.bt_updataiap.Click += new System.EventHandler(this.bt_updataiap_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(-1, 0);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(588, 70);
            this.pictureBox1.TabIndex = 4;
            this.pictureBox1.TabStop = false;
            // 
            // lb_downloadrasult
            // 
            this.lb_downloadrasult.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lb_downloadrasult.AutoSize = true;
            this.lb_downloadrasult.Font = new System.Drawing.Font("宋体", 21.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lb_downloadrasult.Location = new System.Drawing.Point(194, 22);
            this.lb_downloadrasult.Name = "lb_downloadrasult";
            this.lb_downloadrasult.Size = new System.Drawing.Size(0, 29);
            this.lb_downloadrasult.TabIndex = 5;
            // 
            // DL_form
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(587, 145);
            this.Controls.Add(this.lb_downloadrasult);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.bt_updataiap);
            this.Controls.Add(this.progressBar2);
            this.Controls.Add(this.bt_slectfile);
            this.Controls.Add(this.tb_iapfilepath);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "DL_form";
            this.Text = "IAP Updata";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox tb_iapfilepath;
        private System.Windows.Forms.Button bt_slectfile;
        public  System.Windows.Forms.ProgressBar progressBar2;
        private System.Windows.Forms.Button bt_updataiap;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label lb_downloadrasult;
    }
}