using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;

namespace WebApplication1
{
    public partial class WebForm1 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void denglu_Click(object sender, EventArgs e)
        {
            string strConn="server=JF312-PC45\\Local;database=JWGL;Integrated Security=true";
            SqlConnection conn=new SqlConnection(strConn);

            string strCmd = "select * from D where username='" + username.Text + "' and password='" + password.Text + "'";
            SqlCommand cmd = new SqlCommand(strCmd, conn);

            conn.Open();

            SqlDataReader dr = cmd.ExecuteReader();

            if (dr.Read())
            {
                Session["Username"] = dr["username"];
                Response.Redirect("default.aspx");
            }
            else
            {
                Response.Write("<script>alert('登录失败!')</script>");

            }
       }

        protected void zhuce_Click(object sender, EventArgs e)
        {
            Response.Redirect("Register.aspx");
        }


      }
}
