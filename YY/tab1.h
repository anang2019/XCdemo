#include "_G.h"




class intputMy
{
public:
	HWINDOW m_hWindow2;
	HELE INTPUT_EXIT;
	int nResult;
	CString text;
	intputMy(CString name, CString textBT, CString mr){
		int w = 290;
		//m_hWindow2 = XModalWnd_Create(w, 120, textBT, myHwnd, xc_window_style_nothing);

		m_hWindow2 = XModalWnd_CreateEx(0, L"IntPut", textBT, 0, 550, 400, w, 120, myHwnd, xc_window_style_nothing);
		xtrace("%d\n", m_hWindow2);
		XBtn_SetType(XBtn_Create(w - 35, 5, 30, 20, L"x", m_hWindow2), button_type_close);
		XWnd_SetLayoutSize(m_hWindow2, 1, 30, 1, 1);
		//addShapeText(146, 35, 130, 20, (HELE)m_hWindow2, textBT);
		HXCGUI hTextBlock = XShapeText_Create(5, 35, 130, 20, textBT, m_hWindow2);
		XShapeText_SetTextAlign(hTextBlock, textAlignFlag_left);

		INTPUT_EXIT = XRichEdit_Create(10, 60, w - 20, 20, m_hWindow2);
		XRichEdit_SetText(INTPUT_EXIT, mr);

		HELE m_hButton = XBtn_Create(w - 90, 85, 40, 20, L"确定", m_hWindow2);
		XEle_RegEventCPP(m_hButton, XE_BNCLICK, &intputMy::OnEventBtnClick1);
		XEle_EnableFocus(m_hButton, true);
		XEle_EnableSwitchFocus(m_hButton, true);
		XEle_EnableKeyTab(m_hButton, true);
		XEle_EnableDrawFocus(m_hButton, true);
		XEle_IsDrawFocus(m_hButton);

		m_hButton = XBtn_Create(w - 45, 85, 40, 20, L"取消", m_hWindow2);
		XEle_RegEventCPP(m_hButton, XE_BNCLICK, &intputMy::OnEventBtnClick2);


		nResult = XModalWnd_DoModal(m_hWindow2);



	}
	int OnEventBtnClick1(BOOL *pbHandled){
		wchar_t   cknum[256];
		memset(cknum, 0, 256);
		XRichEdit_GetText(INTPUT_EXIT, cknum, 256);
		text = cknum;
		XModalWnd_EndModal(m_hWindow2, 1);
		return 0;
	}
	int OnEventBtnClick2(BOOL *pbHandled){
		wchar_t   cknum[256];
		memset(cknum, 0, 256);
		XRichEdit_GetText(INTPUT_EXIT, cknum, 256);
		text = cknum;
		XModalWnd_EndModal(m_hWindow2, 2);
		return 0;
	}
};

int IntPut(CString name, CString textBT, CString mr, CString &text){
	intputMy ip(name, textBT, mr);
	//return (int)ip.gettext(text);
	text = ip.text;
	//xtrace("666   %d    %s\n", ip.nResult, ip.text);
	return  (int)ip.nResult;
}

//最晚关机线程
DWORD WINAPI maxTimeExit(LPVOID lpParam){
	int ti = (int)lpParam;
	CString text = intToCstr(ti) + " 分钟后关机";
	XShapeText_SetText(tipShapeText, text);
	ti = ti * 60 / 5;
	int n = 0;
	do{
		Sleep(5000);
		n++;
		if (n % 12 == 0) XShapeText_SetText(tipShapeText, intToCstr((ti-n)/12)+L"分钟后关机");
		if (n > ti){
			toQipao("到达最晚关机时间,20秒后关机");
			for (int i = 0; i < 5; i++){
				if (!XBtn_IsCheck(m_hButtonExit) || autoExit == 0){
					toQipao("最晚关机已解除");
					XShapeText_SetText(tipShapeText, L"");
					return 0;
				}
				Sleep(5000);
			}
			EnablePriv();
			while (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0)){
				toQipao("关机中...");
				Sleep(1000);
			}
		}
	} while (autoExit==1);
	toQipao("最晚关机已解除");
	return 0;
}

//自动关机线程
DWORD WINAPI autoTimeExit(LPVOID lpParam){
	autoExit = 1;
	int js = 0;
	XEle_SetTextColor(m_hButtonExit, RGB(255, 0, 0), 255);
	while (XBtn_IsCheck(m_hButtonExit)){
		Sleep(5000);
		for (int i = 0; i < MAXWIN; i++){
			if (getlistbool(i, lbk.run)){
				js = 0;
				continue;
			}
		}
		xtrace("%d\n", js);
		switch (js){
		case 1:
			toQipao("1分钟后关机");
			break;
		case 6:
			toQipao("30秒后关机");
			break;
		case 12:
			EnablePriv();
			while (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0)){
				toQipao("关机中...");
				Sleep(1000);
			}
			break;
		}
		js++;
	}
	XEle_SetTextColor(m_hButtonExit, RGB(0, 0, 0), 255);
	XEle_RedrawEle(m_hButtonExit, true);
	toQipao("自动关机已取消!");
	autoExit = 0;
	return 0;
}

//控件------------------------------------------



class table1
{
public:
	HELE hPage;
	table1(HELE hPage1)
	{
		hPage = hPage1;
		Init();
	}
	//所有下拉框1----------------------------------------------
	void setXiaLaKuang(){
		hComboBoxFS = XComboBox_Create(4, 58, 80, 22, hPage);
		//XComboBox_SetItemTemplateXML(hComboBoxFS, L"ComboBox_ListBox_Item.xml");
		XRichEdit_SetText(hComboBoxFS, L"换号方式");

		HXCGUI hAdapter = XAdTable_Create();
		//xtrace("%d  %d\n", XComboBox_GetAdapter(hComboBoxFS), hAdapter);
		XComboBox_BindAdapter(hComboBoxFS, hAdapter);

		//xtrace("%d\n", XComboBox_GetAdapter(hComboBoxFS));
		XAdTable_AddColumn(hAdapter, L"name1");
		XAdTable_AddItemText(hAdapter, L"不自动换号");
		XAdTable_AddItemText(hAdapter, L"完成退出");
		XAdTable_AddItemText(hAdapter, L"自动换号");
		XAdTable_AddItemText(hAdapter, L"换IP换号");
		XAdTable_AddItemText(hAdapter, L"重开窗口");

		XComboBox_SetSelItem(hComboBoxFS, _ttoi(getini("窗口", "循环上号", (CString)PeiZhiText.c_str(), "1")) - 1);
		XEle_RegEventCPP(hComboBoxFS, XE_COMBOBOX_SELECT, &table1::OnComboBoxPopupListFS);

		//Output("111  %d\n", XEle_RegEventC(hComboBoxFS, XE_COMBOBOX_SELECT, OnComboBoxPopupListFS));

		hComboBoxXL = XComboBox_Create(4, 6, 75, 22, hPage);
		//XComboBox_SetItemTemplateXML(hComboBoxXL, L"ComboBox_ListBox_Item.xml");
		XRichEdit_SetText(hComboBoxXL, L"选择线路");

		hAdapter = XAdTable_Create();
		XComboBox_BindAdapter(hComboBoxXL, hAdapter);
		XAdTable_AddColumn(hAdapter, L"name1");
		XAdTable_AddItemText(hAdapter, L"每队同线");
		XAdTable_AddItemText(hAdapter, L"一号一线");
		XAdTable_AddItemText(hAdapter, L"进摆摊线");
		int a = _ttoi(getini("窗口", "切换方式", (CString)PeiZhiText.c_str(), "1")) - 1;
		XComboBox_SetSelItem(hComboBoxXL, a);
		//Output("111  %d\n", GetLastError() );
		XEle_RegEventCPP(hComboBoxXL, XE_COMBOBOX_SELECT, &table1::OnComboBoxPopupListXL);

		hComboBoxXX = XComboBox_Create(82, 6, 67, 22, hPage);
		//XComboBox_SetItemTemplateXML(hComboBoxXX, L"ComboBox_ListBox_Item.xml");
		XRichEdit_SetText(hComboBoxXX, L"选择线路");

		hAdapter = XAdTable_Create();
		XComboBox_BindAdapter(hComboBoxXX, hAdapter);
		XAdTable_AddColumn(hAdapter, L"name1");
		for (int i = 1; i < 10; i++){
			XAdTable_AddItemText(hAdapter, intToCstr(i) + "线开始");
		}

		a = _ttoi(getini("窗口", "最大线路", (CString)PeiZhiText.c_str(), "9")) - 1;
		XComboBox_SetSelItem(hComboBoxXX, a);
		XEle_RegEventCPP(hComboBoxXX, XE_COMBOBOX_SELECT, &table1::OnComboBoxPopupListXX);


		hComboBoxBT = XComboBox_Create(154, 32, 67, 22, hPage);
		//XComboBox_SetItemTemplateXML(hComboBoxBT, L"ComboBox_ListBox_Item.xml");
		XRichEdit_SetText(hComboBoxBT, L"选摆摊线");

		hAdapter = XAdTable_Create();
		XComboBox_BindAdapter(hComboBoxBT, hAdapter);

		XAdTable_AddColumn(hAdapter, L"name1");
		for (int i = 1; i < 10; i++){
			XAdTable_AddItemText(hAdapter, intToCstr(i) + "线摆摊");
		}

		a = _ttoi(getini("窗口", "收金线路", (CString)PeiZhiText.c_str(), "6")) - 1;
		XComboBox_SetSelItem(hComboBoxBT, a);
		XEle_RegEventCPP(hComboBoxBT, XE_COMBOBOX_SELECT, &table1::OnComboBoxPopupListBT);

		hComboBoxJS = XComboBox_Create(4, 110, 77, 22, hPage);
		//XComboBox_SetItemTemplateXML(hComboBoxJS, L"ComboBox_ListBox_Item.xml");
		XRichEdit_SetText(hComboBoxJS, L"角色");
		hAdapter = XAdTable_Create();
		XComboBox_BindAdapter(hComboBoxJS, hAdapter);
		XAdTable_AddColumn(hAdapter, L"name1");
		XAdTable_AddItemText(hAdapter, L"更换角色");
		XAdTable_AddItemText(hAdapter, L"不换角色");
		XAdTable_AddItemText(hAdapter, L"第1个");
		XAdTable_AddItemText(hAdapter, L"第2个");
		XAdTable_AddItemText(hAdapter, L"第3个");
		XAdTable_AddItemText(hAdapter, L"最后建");
		a = _ttoi(getini("msger", "更换角色", (CString)PeiZhiText.c_str(), "0"));
		if (a != 1)a = 0;
		XComboBox_SetSelItem(hComboBoxJS, a);
		XEle_RegEventCPP(hComboBoxJS, XE_COMBOBOX_SELECT, &table1::OnComboBoxPopupListJS);

		HELE hComboBox = XComboBox_Create(4, 136, 77, 22, hPage);
		//XComboBox_SetItemTemplateXML(hComboBox, L"ComboBox_ListBox_Item.xml");
		XRichEdit_SetText(hComboBox, L"更新");
		hAdapter = XAdTable_Create();
		XComboBox_BindAdapter(hComboBox, hAdapter);
		XAdTable_AddColumn(hAdapter, L"name1");
		XAdTable_AddItemText(hAdapter, L"目录");
		XAdTable_AddItemText(hAdapter, L"output");
		XAdTable_AddItemText(hAdapter, L"插+脚");
		XAdTable_AddItemText(hAdapter, L"插件");
		XAdTable_AddItemText(hAdapter, L"脚本");
		XAdTable_AddItemText(hAdapter, L"基址");
		XAdTable_AddItemText(hAdapter, L"DLL");
		XAdTable_AddItemText(hAdapter, L"演义");
		XAdTable_AddItemText(hAdapter, L"客户端");
		
		XEle_RegEventCPP(hComboBox, XE_COMBOBOX_SELECT, &table1::OnComboBoxPopupListGX);

	}

	//循环上号
	int OnComboBoxPopupListFS(int iItem, BOOL *pbHandled)
	{
		setini("窗口", "循环上号", PeiZhiText, to_string(iItem + 1));
		//*pbHandled = TRUE;
		return 0;
	}
	//切换方式
	int OnComboBoxPopupListXL(int iItem, BOOL *pbHandled)
	{
		setini("窗口", "切换方式", PeiZhiText, to_string(iItem + 1));
		//*pbHandled = TRUE;
		return 0;
	}
	//最大线路
	int OnComboBoxPopupListXX(int iItem, BOOL *pbHandled)
	{
		setini("窗口", "最大线路", PeiZhiText, to_string(iItem + 1));
		//*pbHandled = TRUE;
		return 0;
	}
	//收金线路
	int OnComboBoxPopupListBT(int iItem, BOOL *pbHandled)
	{
		setini("窗口", "收金线路", PeiZhiText, to_string(iItem + 1));
		//*pbHandled = TRUE;
		return 0;
	}
	//更换角色
	int OnComboBoxPopupListJS(int iItem, BOOL *pbHandled)
	{
		if (iItem<2)
			setini("msger", "更换角色", PeiZhiText, to_string(iItem + 1));
		//*pbHandled = TRUE;
		return 0;
	}
	//更新
	int OnComboBoxPopupListGX(int iItem, BOOL *pbHandled)
	{
		string pach = "\\\\DADI-A\\"+replace(textLS,":", "\\");
		string a = pach + "UI.lua";
		string b = textLS + "UI.lua";
		switch (iItem){
		case 1:
			openProgram("D:\\Dbgview.exe");
			break;
		case 2:
			if (!copyFile((char*)a.c_str(), (char*)b.c_str())){
				toQipao("更新插件 失败!");
				return 0;
			}
			else{
				a = pach + "ufo.txt";
				b = textLS + "ufo.txt";
				if (!copyFile((char*)a.c_str(), (char*)b.c_str())){
					toQipao("更新脚本 失败!");
					return 0;
				}
			}
			takeluatext();
			toQipao("更新插件+脚本 成功!");

			break;
		case 3:
			if (!copyFile((char*)a.c_str(), (char*)b.c_str())){
				toQipao("更新插件 失败!");
				return 0;
			}
			toQipao("更新插件 成功!");
			break;
		case 4:
			a = pach + "ufo.txt";
			b = textLS + "ufo.txt";
			if (!copyFile((char*)a.c_str(), (char*)b.c_str())){
				toQipao("更新脚本 失败!");
				return 0;
			}
			toQipao("更新脚本 成功!");
			break;
		case 5:
			a = pach + "data.dat";
			b = textLS + "data.dat";
			if (!copyFile((char*)a.c_str(), (char*)b.c_str())){
				toQipao("更新基址 失败!");
				return 0;
			}
			toQipao("更新基址 成功!");
			break;
		case 6:
			if (!copyFile("\\\\DADI-A\\d\\新QQ三国\\AudioSes.dll", "D:\\新QQ三国\\AudioSes.dll")){
				toQipao("更新dll 失败!");
				return 0;
			}
			toQipao("更新dll 成功!");
			break;
		case 7:
			
			openProgram((CString)textLS.c_str()+ "updata.exe");
			exit(0);
			break;
		case 8:
			openProgram("D:\\新QQ三国\\QQSG.exe");
			break;
		}
		//*pbHandled = TRUE;
		return 0;
	}

	//编辑框------------------------------------------------------------
	void setedit(){
		m_EditXH = XRichEdit_Create(151, 6, 32, 22, hPage);
		XRichEdit_SetText(m_EditXH, getini("窗口", "账号序号", (CString)PeiZhiText.c_str(), "1"));
		XRichEdit_EnableEvent_XE_RICHEDIT_CHANGE(m_EditXH, true);
		XEle_RegEventCPP(m_EditXH, XE_RICHEDIT_CHANGE, &table1::OnRichEditChangeXH);
		
		addShapeText(183, 6, 56, 22, hPage, "账号序号");

		

		//收金编辑框
		m_EditSJ = XRichEdit_Create(4, 32, 84, 22, hPage);
		XRichEdit_SetText(m_EditSJ, getini("msger", "tomoney", (CString)PeiZhiText.c_str(), ""));
		
		HELE m_hButton = XBtn_Create(90, 32, 60, 22, L"收金角色", hPage);
		XEle_RegEventCPP(m_hButton, XE_BNCLICK, &table1::OnEventBtnClickSJ);

		m_hButton = XBtn_Create(224, 32, 61, 22, L"编辑账号", hPage);
		XEle_RegEventCPP(m_hButton, XE_BNCLICK, &table1::OnEventBtnClickBJ);

		addShapeText(123, 58, 54, 22, hPage, "最大换号");

		m_EditZDHH = XRichEdit_Create(175, 58, 30, 22, hPage);
		XRichEdit_SetText(m_EditZDHH, getini("窗口", "最大换号", (CString)PeiZhiText.c_str(), "4"));
		XRichEdit_EnableEvent_XE_RICHEDIT_CHANGE(m_EditZDHH, true);
		XEle_RegEventCPP(m_EditZDHH, XE_RICHEDIT_CHANGE, &table1::OnRichEditChangeZDHH);

		m_hButton = XBtn_Create(208, 58, 77, 22, L"开机自启", hPage);
		//设置功能为选中和未选中
		XBtn_SetType(m_hButton, button_type_check);
		//把外观设置为通常有个小方框的样式，大家可以注释看看效果
		XBtn_SetStyle(m_hButton, button_style_check);
		XBtn_SetCheck(m_hButton, getini("窗口", "开机自启", (CString)PeiZhiText.c_str(), "0")=="1");
		XEle_RegEventCPP(m_hButton, XE_BUTTON_CHECK, &table1::OnButtonCheckKJ);

		m_textKD=addShapeText(4, 84, 64, 22, hPage, "宽带连接");
		XShapeText_SetTextColor(m_textKD, RGB(255, 0, 0), 255);

		m_hButton = XBtn_Create(57, 84, 64, 22, L"重新连接", hPage);
		XEle_RegEventCPP(m_hButton, XE_BNCLICK, &table1::OnEventBtnClickKDCL);

		m_EditIP = XRichEdit_Create(124, 84, 168, 104, hPage);

		m_hButtonExit = XBtn_Create(4, 164, 77, 22, L"完成关机", hPage);
		//设置功能为选中和未选中
		XBtn_SetType(m_hButtonExit, button_type_check);
		//把外观设置为通常有个小方框的样式，大家可以注释看看效果
		XBtn_SetStyle(m_hButtonExit, button_style_check);
		XEle_RegEventCPP(m_hButtonExit, XE_BUTTON_CHECK, &table1::OnButtonCheckExit);
		//提示IP
		tipShapeText = addShapeText(4, 166, 112, 16, hPage, "");
		XShapeText_SetTextColor(tipShapeText, RGB(255, 0, 0), 255);

	}

	//账号序号
	int OnRichEditChangeXH(BOOL *pbHandled){
		wchar_t   cknum[256];
		memset(cknum, 0, 256);
		XRichEdit_GetText(m_EditXH, cknum, 256);

		setini("窗口", "账号序号", PeiZhiText, cknum);
		return 0;
	}

	//收金角色
	int OnEventBtnClickSJ(BOOL *pbHandled)
	{
		wchar_t   cknum[256];
		memset(cknum, 0, 256);
		XRichEdit_GetText(m_EditSJ, cknum, 256);
		
		setini("msger", "tomoney", PeiZhiText, cknum);
		return 0;
	}

	//编辑账号
	int OnEventBtnClickBJ(BOOL *pbHandled)
	{
		string ss = "notepad.exe "+textLS + "base.ini";
		WinExec(ss.c_str(), SW_SHOW);
		
		return 0;
	}

	//最大换号
	int OnRichEditChangeZDHH(BOOL *pbHandled){
		wchar_t   cknum[256];
		memset(cknum, 0, 256);
		XRichEdit_GetText(m_EditZDHH, cknum, 256);

		setini("窗口", "最大换号", PeiZhiText, cknum);
		return 0;
	}

	//开机自启
	int OnButtonCheckKJ(BOOL bCheck, BOOL *pbHandled)
	{
		if (bCheck){
			setini((CString)"窗口", "开机自启", PeiZhiText, "1");
		}
		else{
			setini((CString)"窗口", "开机自启", PeiZhiText, "0");
		}
		return 0;
	}

	//完成关机
	int OnButtonCheckExit(BOOL bCheck, BOOL *pbHandled)
	{
		if (autoExit == 0 && bCheck){
			CString n;
			if (IntPut("最晚定时关机时间", "最晚多少分钟后关机?如不设置请留空!", "", n)==1){
				int ti = _ttoi(n);
				if (ti > 0){
					::CreateThread(0, 0, maxTimeExit, (LPVOID)ti, 0, 0);
					n = "全部完成后关机,设置成功!\n最晚关机时间 " + intToCstr(ti) + " 分钟后";
				}
				else{
					n = "全部完成后关机,设置成功!";
				}
				toQipao(n);
				::CreateThread(0, 0, autoTimeExit, 0, 0, 0);
			}
			else {
				XBtn_SetCheck(m_hButtonExit, false);
			}
		}

		
		return 0;
	}

	//重新连接
	int OnEventBtnClickKDCL(BOOL *pbHandled)
	{
		

		return 0;
	}

	void Init(){
		setXiaLaKuang();
		setedit();
	}
};
