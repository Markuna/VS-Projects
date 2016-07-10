using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;
using System.Data;

namespace WebApplication1
{
    public partial class Register : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
       
        }

      

        protected void Button1_Click(object sender, EventArgs e)
        {
            if (CheckUserExist())
            {
                Label1.Text = "用户已存在!";
            }
            else
            {
                UserRegister();

            }
        }

        private bool CheckUserExist()
        {
            //创建Connection对象
            string strConn = "server=JF312-PC45\\Local;database=JWGL;Integrated Security=true";
            SqlConnection conn = new SqlConnection(strConn);

            //创建Command对象
            string strCmd = "select * from D where username='" + username.Text + "'";
            SqlCommand cmd = new SqlCommand(strCmd, conn);

            conn.Open();
            SqlDataReader dr = cmd.ExecuteReader();
            if (dr.Read())
            {
                return true;
            }
            else
            {
                return false;
            }

        }


        private void UserRegister()
        {

            //创建Connection对象
            string strConn = "server=JF312-PC45\\Local;database=JWGL;Integrated Security=true";
            SqlConnection conn = new SqlConnection(strConn);

            //创建Command对象
            string strCmd = "insert into D(username,password) values(@username,@password)";

            SqlCommand cmd = new SqlCommand();
            cmd.Connection = conn;
            cmd.CommandType = CommandType.Text;
            cmd.CommandText = strCmd;

            cmd.Parameters.Add("@username", SqlDbType.VarChar).Value = username.Text;
            cmd.Parameters.Add("@password", SqlDbType.VarChar).Value = password.Text;

            try
            {
                conn.Open();

                int n = cmd.ExecuteNonQuery();
                if (n > 0)
                {
                    Label1.Text = "用户添加成功！";
                }
                else
                {
                    Label1.Text = "用户添加失败！";
                }

            }
            catch (Exception ex)
            {
                Label1.Text = ex.Message.ToString();

            }

            conn.Close();

        }


       
    }
}