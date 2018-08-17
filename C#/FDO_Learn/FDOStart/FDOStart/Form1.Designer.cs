namespace FDOStart
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
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.ListViewItem listViewItem1 = new System.Windows.Forms.ListViewItem("ID");
            System.Windows.Forms.ListViewItem listViewItem2 = new System.Windows.Forms.ListViewItem("道路长度");
            System.Windows.Forms.ListViewItem listViewItem3 = new System.Windows.Forms.ListViewItem("Geometry_start");
            System.Windows.Forms.ListViewItem listViewItem4 = new System.Windows.Forms.ListViewItem("Geoemetry_end");
            this.create_db = new System.Windows.Forms.Button();
            this.text_DB_Name = new System.Windows.Forms.TextBox();
            this.Open_DB = new System.Windows.Forms.Button();
            this.text_openDB = new System.Windows.Forms.TextBox();
            this.create_Schema = new System.Windows.Forms.Button();
            this.Write_Data = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.Close_DB = new System.Windows.Forms.Button();
            this.listViewDB = new System.Windows.Forms.ListView();
            this.errorProvider1 = new System.Windows.Forms.ErrorProvider(this.components);
            this.Read_Data = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider1)).BeginInit();
            this.SuspendLayout();
            // 
            // create_db
            // 
            this.create_db.Location = new System.Drawing.Point(175, 84);
            this.create_db.Name = "create_db";
            this.create_db.Size = new System.Drawing.Size(75, 23);
            this.create_db.TabIndex = 0;
            this.create_db.Text = "CreateDB";
            this.create_db.UseVisualStyleBackColor = true;
            this.create_db.Click += new System.EventHandler(this.create_db_Click);
            // 
            // text_DB_Name
            // 
            this.text_DB_Name.Location = new System.Drawing.Point(288, 86);
            this.text_DB_Name.Name = "text_DB_Name";
            this.text_DB_Name.Size = new System.Drawing.Size(258, 21);
            this.text_DB_Name.TabIndex = 1;
            this.text_DB_Name.Text = "D:\\test.sqlite";
            // 
            // Open_DB
            // 
            this.Open_DB.Location = new System.Drawing.Point(175, 127);
            this.Open_DB.Name = "Open_DB";
            this.Open_DB.Size = new System.Drawing.Size(75, 23);
            this.Open_DB.TabIndex = 0;
            this.Open_DB.Text = "OpenDB";
            this.Open_DB.UseVisualStyleBackColor = true;
            this.Open_DB.Click += new System.EventHandler(this.Open_DB_Click);
            // 
            // text_openDB
            // 
            this.text_openDB.Location = new System.Drawing.Point(288, 127);
            this.text_openDB.Name = "text_openDB";
            this.text_openDB.Size = new System.Drawing.Size(258, 21);
            this.text_openDB.TabIndex = 2;
            this.text_openDB.Text = "D:\\Test.sqlite";
            // 
            // create_Schema
            // 
            this.create_Schema.Location = new System.Drawing.Point(175, 185);
            this.create_Schema.Name = "create_Schema";
            this.create_Schema.Size = new System.Drawing.Size(88, 23);
            this.create_Schema.TabIndex = 3;
            this.create_Schema.Text = "CreateSchema";
            this.create_Schema.UseVisualStyleBackColor = true;
            this.create_Schema.Click += new System.EventHandler(this.create_Schema_Click);
            // 
            // Write_Data
            // 
            this.Write_Data.Location = new System.Drawing.Point(175, 238);
            this.Write_Data.Name = "Write_Data";
            this.Write_Data.Size = new System.Drawing.Size(75, 23);
            this.Write_Data.TabIndex = 4;
            this.Write_Data.Text = "WriteData";
            this.Write_Data.UseVisualStyleBackColor = true;
            this.Write_Data.Click += new System.EventHandler(this.Write_Data_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(310, 249);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 5;
            this.label1.Text = "FeatID：";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(391, 239);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(100, 21);
            this.textBox1.TabIndex = 6;
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(391, 288);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(100, 21);
            this.textBox2.TabIndex = 7;
            // 
            // textBox3
            // 
            this.textBox3.Location = new System.Drawing.Point(391, 337);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(100, 21);
            this.textBox3.TabIndex = 8;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(312, 296);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 12);
            this.label2.TabIndex = 9;
            this.label2.Text = "道路长度：";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(312, 345);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(65, 12);
            this.label3.TabIndex = 10;
            this.label3.Text = "Geometry：";
            // 
            // Close_DB
            // 
            this.Close_DB.Location = new System.Drawing.Point(175, 448);
            this.Close_DB.Name = "Close_DB";
            this.Close_DB.Size = new System.Drawing.Size(75, 23);
            this.Close_DB.TabIndex = 11;
            this.Close_DB.Text = "Close";
            this.Close_DB.UseVisualStyleBackColor = true;
            this.Close_DB.Click += new System.EventHandler(this.Close_DB_Click);
            // 
            // listViewDB
            // 
            this.listViewDB.Items.AddRange(new System.Windows.Forms.ListViewItem[] {
            listViewItem1,
            listViewItem2,
            listViewItem3,
            listViewItem4});
            this.listViewDB.Location = new System.Drawing.Point(567, 97);
            this.listViewDB.Name = "listViewDB";
            this.listViewDB.Size = new System.Drawing.Size(555, 97);
            this.listViewDB.TabIndex = 12;
            this.listViewDB.UseCompatibleStateImageBehavior = false;
            this.listViewDB.View = System.Windows.Forms.View.Tile;
            // 
            // errorProvider1
            // 
            this.errorProvider1.ContainerControl = this;
            // 
            // Read_Data
            // 
            this.Read_Data.Location = new System.Drawing.Point(175, 394);
            this.Read_Data.Name = "Read_Data";
            this.Read_Data.Size = new System.Drawing.Size(75, 23);
            this.Read_Data.TabIndex = 13;
            this.Read_Data.Text = "ReadData";
            this.Read_Data.UseVisualStyleBackColor = true;
            this.Read_Data.Click += new System.EventHandler(this.Read_Data_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1256, 535);
            this.Controls.Add(this.Read_Data);
            this.Controls.Add(this.listViewDB);
            this.Controls.Add(this.Close_DB);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBox3);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Write_Data);
            this.Controls.Add(this.create_Schema);
            this.Controls.Add(this.text_openDB);
            this.Controls.Add(this.text_DB_Name);
            this.Controls.Add(this.Open_DB);
            this.Controls.Add(this.create_db);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button create_db;
        private System.Windows.Forms.TextBox text_DB_Name;
        private System.Windows.Forms.Button Open_DB;
        private System.Windows.Forms.TextBox text_openDB;
        private System.Windows.Forms.Button create_Schema;
        private System.Windows.Forms.Button Write_Data;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button Close_DB;
        private System.Windows.Forms.ListView listViewDB;
        private System.Windows.Forms.ErrorProvider errorProvider1;
        private System.Windows.Forms.Button Read_Data;
    }
}

