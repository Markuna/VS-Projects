<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Login.aspx.cs" Inherits="WebApplication1.WebForm1" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title></title>
</head>
<body style="text-align: center">
    <form id="form1" runat="server">
    <div>
    
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 用户登录<br />
        <br />
        用户名&nbsp;&nbsp; 
        <asp:TextBox ID="username" runat="server"></asp:TextBox>
        <br />
        <br />
        密码&nbsp;&nbsp;&nbsp; 
        <asp:TextBox ID="password" runat="server"></asp:TextBox>
        <br />
&nbsp;&nbsp;&nbsp;&nbsp;
        <br />
&nbsp;&nbsp;&nbsp;&nbsp;
        <asp:Button ID="denglu" runat="server" OnClick="denglu_Click" Text="登录" />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
        <asp:Button ID="zhuce" runat="server" OnClick="zhuce_Click" Text="注册" />
        <br />
    
    </div>
    </form>
</body>
</html>
