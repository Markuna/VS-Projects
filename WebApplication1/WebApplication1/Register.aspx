<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Register.aspx.cs" Inherits="WebApplication1.Register" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title></title>
</head>
<body style="text-align: center">
    <form id="form1" runat="server">
    <div>
    
        用户 &nbsp;&nbsp; 
        <asp:TextBox ID="username" runat="server"></asp:TextBox>
        <br />
        密码&nbsp;&nbsp;&nbsp; 
        <asp:TextBox ID="password" runat="server" ></asp:TextBox>
        <br />
        <br />
        <br />
        <asp:Button ID="Button1" runat="server" OnClick="Button1_Click" Text="注册" />
&nbsp;&nbsp;&nbsp;
        <asp:Label ID="Label1" runat="server" Text=" "></asp:Label>
        <br />
    
    </div>
    </form>
</body>
</html>
