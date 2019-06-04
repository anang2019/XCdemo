#include "tab1.h"



HELE m_Edit1;
HXCGUI hAdapter1;
HELE m_hListBox1;
int text_jb_ks = 0;
int text_jb_js = 0;
int text_jb_hs = -1;
HWINDOW m_hWindow1;

class CWindow_Demo1
{
public:
	
	
	CWindow_Demo1(int num,int hs1)
	{
		Init(num);
		text_jb_hs = hs1;
	}
	void Init(int num)
	{
		m_hWindow1 = XWnd_Create(0, 0, 290, 404, L"�ű������", NULL, xc_window_style_center);
		XBtn_SetType(XBtn_Create(255, 5, 30, 20, L"x", m_hWindow1), button_type_close);
		XWnd_SetLayoutSize(m_hWindow1, 1, 20, 1, 1);
		addShapeText(146, 35, 130, 22, (HELE)m_hWindow1, "˫��ѡ��ִ�нű�����");

		m_Edit1 = XRichEdit_Create(13, 35, 56, 22, m_hWindow1);
		xtrace("1   %d\n", m_Edit1);
		HELE m_hButton = XBtn_Create(80, 35, 56, 22, L"�鿴", m_hWindow1);
		XEle_RegEventCPP(m_hButton, XE_BNCLICK, &CWindow_Demo1::OnEventBtnClick);

		
		m_hListBox1 = XListBox_Create(13, 67, 263, 305, m_hWindow1);
		//XListBox_SetItemTemplateXML(m_hListBox, L"ListBox_Item.xml");
		XSView_SetLineSize(m_hListBox1, 20, 20);
		XListBox_SetItemHeightDefault(m_hListBox1, 22, 22);
		hAdapter1 = XAdTable_Create();
		XListBox_BindAdapter(m_hListBox1, hAdapter1);
		XAdTable_AddColumn(hAdapter1, L"name1");

		dataJB(num);
		
		XEle_RegEventCPP(m_hListBox1, XE_MOUSEWHEEL, &CWindow_Demo1::OnMouseWheel);

		XEle_RegEventCPP1(m_hListBox1, XE_LBUTTONDBCLICK, &CWindow_Demo1::OnLButtonDBClick);

		XWnd_ShowWindow(m_hWindow1, SW_SHOW);
	}

	//ˢ�½ű�
	void dataJB(int num){
		XAdTable_DeleteItemAll(hAdapter1);
		int qj = 7;
		text_jb_ks = max(num - qj, 1);
		text_jb_js = min(num + qj + 1, rumtext.size()-1);
		CString jg = "    ";
		
		for (int i = text_jb_ks; i < text_jb_js;  i++){
			if (i == num)jg = " *  ";
			else jg = "    ";
			int sy=XAdTable_AddItemText(hAdapter1, intToCstr(i) + jg + rumtext[i]);
			//xtrace("2   %d  %d\n", i, sy);
			XListBox_SetItemData(m_hListBox1, sy, i);
			if (i == num)XListBox_SetSelectItem(m_hListBox1, sy);
		}
		XListBox_RefreshData(m_hListBox1);
		XEle_RedrawEle(m_hListBox1, true);
	}

	int OnEventBtnClick(BOOL *pbHandled){
		wchar_t   cknum[256];
		memset(cknum, 0, 256);
		xtrace("2   %d\n", m_Edit1);
		XRichEdit_GetText(m_Edit1, cknum, 256);
		CString ss = cknum;
		int a = _ttoi(ss);
		xtrace("%d\n", a);
		dataJB(a);
		return 0;
	}
	int OnMouseWheel(UINT nFlags, POINT *pPt, BOOL *pbHandled){
		//xtrace("%d %d      %d  %d %d %d  \n", nFlags, XSView_GetScrollBarV(m_hListBox1), XSView_GetViewHeight(XSView_GetScrollBarV(m_hListBox1)));
		if ((int)nFlags < 0){
			if (text_jb_js>rumtext.size()-1)return 0;
			text_jb_js++;
			
			int sy = XAdTable_AddItemText(hAdapter1, intToCstr(text_jb_js) + "    " + rumtext[text_jb_js]);
			XListBox_SetItemData(m_hListBox1, sy, text_jb_js);
			XListBox_RefreshData(m_hListBox1);
			XEle_RedrawEle(m_hListBox1, true);
		}
		else{
			if (text_jb_ks<2)return 0;
			text_jb_ks--;
			int sy = XAdTable_InsertItemText(hAdapter1, 0, intToCstr(text_jb_ks) + "    " + rumtext[text_jb_ks]);
			XListBox_SetItemData(m_hListBox1, sy, text_jb_ks);
			XListBox_RefreshData(m_hListBox1);
			XEle_RedrawEle(m_hListBox1, true);
		}
		return 0;
	}
	int OnLButtonDBClick(HELE hEventEle, UINT nFlags, POINT *pPt, BOOL *pbHandled){
		//xtrace("%d  %d  %d\n", text_jb_hs, XListBox_GetItemData(m_hListBox1, XListBox_GetSelectItem(m_hListBox1)), XListBox_GetSelectItem(m_hListBox1));
		if (winls[text_jb_hs].h > 0){
			int n=XListBox_GetItemData(m_hListBox1, XListBox_GetSelectItem(m_hListBox1));
			PostMessageA(winls[text_jb_hs].h, 52228, 1, n);
			setlisttext(text_jb_hs, lbk.runnum, intToCstr(n));
			text_jb_hs = -1;
		}
		XWnd_CloseWindow(m_hWindow1);

		return 0;
	}



};

//ȡ���ڿ�ʼ����
void getKStoJS(int &k, int &j){
	if (FenKong == 0){
		k = 1;
		j = MAXWIN;
	}
	else{
		k = (FenKong - 1) * 5 + 1;
		j = k + 4;
	}
	if (k > MAXWIN)k = 100;
	if (j > MAXWIN)j = MAXWIN;
	k--;
	j--;
}


//��������
void setXJHS(){
	int num = getEditInt(m_EditHS);
	int k, j;
	getKStoJS(k, j);
	for (k; k <= j; k++){
		if (winls[k].h > 0){
			PostMessageA(winls[k].h, 52228, 1, num);
			winls[k].hsjl = 0;
			setlisttext(k, lbk.runnum, intToCstr(num));
		}
	}
}


//��¼�߳�
DWORD WINAPI rootThread(LPVOID lpParam){
	bool bn = false;
	do{
		bn = false;
		for (int j = 0; j < MAXWIN; j++){
			if (winls[j].rootnum > 0){
				if (winls[j].h > 0){
					int item = XComboBox_GetSelItem(hComboBoxJS);
					if (item > 1){
						PostMessageA(winls[j].h, 52228, 15, item-1);
					}
					PostMessageA(winls[j].h, 52228, 10, winls[j].rootnum);
					int n = 0;
					while (winls[j].rootnum > 0){
						Sleep(3000);
						n++;
						if (n > 30){
							Output("oo,����:��¼��ʱ   %d\n", j);
							break;
						}
					}

					bn = true;

				}
				else winls[j].rootnum = 0;
			}
		}
	} while (bn);
	isRootT = 0;
	return 0;
}

//���õ�¼
void setRoot(int x){
	PostMessageA(winls[x].h, 52228, 3, 1);
	if (getlisttext(x, lbk.name) == "δ��¼"){
		winls[x].rootnum = getEditInt(m_EditXH) + x ;
		if (isRootT == 0){
			isRootT = 1;
			::CreateThread(0, 0, rootThread, 0, 0, 0);
		}
	}
}

//�˳���¼�߳�
DWORD WINAPI exitRootThread(LPVOID lpParam)  {
	int k, j;
	getKStoJS(k, j);
	for (k; k <= j; k++){
		if (winls[k].h > 0){
			PostMessageA(winls[k].h, 52228, 8, 8);
			Sleep(1100);
		}
	}
	return 0;
}

class table3
{
public:
	HELE hPage;
	table3(HELE hPage1)
	{
		hPage = hPage1;
		Init();
	}

	//����������--------------------------------------------
	void setXiaLaKuang(){
		HELE m_hListBoxFK = XListBox_Create(3, 6, 48, 100, hPage);
		//XListBox_SetItemTemplateXML(m_hListBoxFK, L"ListBox_Item.xml");
		XSView_SetLineSize(m_hListBoxFK, 20, 20);

		HXCGUI hAdapter = XAdTable_Create();
		XListBox_SetItemHeightDefault(m_hListBoxFK, 16, 16);
		XListBox_BindAdapter(m_hListBoxFK, hAdapter);
		XAdTable_AddColumn(hAdapter, L"name1");
		XAdTable_AddItemText(hAdapter, L"ȫ��");
		XAdTable_AddItemText(hAdapter, L"1-5");
		XAdTable_AddItemText(hAdapter, L"6-10");
		XAdTable_AddItemText(hAdapter, L"11-15");
		XAdTable_AddItemText(hAdapter, L"16-20");
		XListBox_SetSelectItem(m_hListBoxFK, 0);
		XEle_RegEventCPP(m_hListBoxFK, XE_LISTBOX_SELECT, &table3::OnTemplateCreateFK);


		HELE hComboBox = XComboBox_Create(107, 111, 84, 22, hPage);
		//XComboBox_SetItemTemplateXML(hComboBox, L"ComboBox_ListBox_Item.xml");
		XRichEdit_SetText(hComboBox, L"�Ͻ�");

		hAdapter = XAdTable_Create();
		XComboBox_BindAdapter(hComboBox, hAdapter);
		XAdTable_AddColumn(hAdapter, L"name1");
		XAdTable_AddItemText(hAdapter, L"�Ͻ����");
		XAdTable_AddItemText(hAdapter, L"�Ͻ��󻻺�");
		XAdTable_AddItemText(hAdapter, L"�����Ͻ�");
		XAdTable_AddItemText(hAdapter, L"���Ͻ����");
		int nn = 0;
		if (getini("msger", "�Ͻ�", (CString)PeiZhiText.c_str(), "") == ""){
			if (getini("msger", "ֻ�Ͻ�", (CString)PeiZhiText.c_str(), "") == "1"){
				nn = 1;
			}
			else if (getini("msger", "�����Ͻ�", (CString)PeiZhiText.c_str(), "") == "1"){
				nn = 2;
			}
			
		}
		else nn = 3;

		XComboBox_SetSelItem(hComboBox, nn);
		XEle_RegEventCPP(hComboBox, XE_COMBOBOX_SELECT, &table3::OnComboBoxPopupListSJ);


		hComboBox = XComboBox_Create(157, 136, 70, 22, hPage);
		//XComboBox_SetItemTemplateXML(hComboBox, L"ComboBox_ListBox_Item.xml");
		XRichEdit_SetText(hComboBox, L"�н�");

		hAdapter = XAdTable_Create();
		XComboBox_BindAdapter(hComboBox, hAdapter);
		XAdTable_AddColumn(hAdapter, L"name1");
		XAdTable_AddItemText(hAdapter, L"60�н�");
		XAdTable_AddItemText(hAdapter, L"50�н�");
		XAdTable_AddItemText(hAdapter, L"40�н�");
		nn = 0;
		if (getini("msger", "40�н�", (CString)PeiZhiText.c_str(), "") == "1"){
			nn = 2;
			XComboBox_SetSelItem(hComboBoxJS, 0);
			setini("msger", "������ɫ", PeiZhiText, (string)"0");
		}
		else if (getini("msger", "50�н�", (CString)PeiZhiText.c_str(), "") == "1"){
			nn = 3;
		}
		else{
			nn = 0;
			XComboBox_SetSelItem(hComboBoxJS, 1);
			setini("msger", "������ɫ", PeiZhiText, (string)"1");
		}
		XComboBox_SetSelItem(hComboBox, nn);
		XEle_RegEventCPP(hComboBox, XE_COMBOBOX_SELECT, &table3::OnComboBoxPopupListXJJ);

	}

	//1-5,6-10
	int  OnTemplateCreateFK(int iGroup, int iItem, BOOL *pbHandled){
		xtrace("��ť�Ƿ�ѡ�� %d   %d \r\n", iGroup, iItem);
		if (iGroup>=0)FenKong = iGroup;
		return 0;
	}

	//�Ͻ�
	int OnComboBoxPopupListSJ(int iItem, BOOL *pbHandled)
	{
		switch (iItem){
		case 0:
			setini("msger", "�Ͻ�", PeiZhiText, (string)"");
			setini("msger", "ֻ�Ͻ�", PeiZhiText, (string)"");
			setini("msger", "�����Ͻ�", PeiZhiText, (string)"");
			break;
		case 1:
			setini("msger", "�Ͻ�", PeiZhiText, (string)"");
			setini("msger", "ֻ�Ͻ�", PeiZhiText, (string)"1");
			setini("msger", "�����Ͻ�", PeiZhiText, (string)"");
			break;
		case 2:
			setini("msger", "�Ͻ�", PeiZhiText, (string)"");
			setini("msger", "ֻ�Ͻ�", PeiZhiText, (string)"");
			setini("msger", "�����Ͻ�", PeiZhiText, (string)"1");
			break;
		default:
			setini("msger", "�Ͻ�", PeiZhiText, (string)"1");
			setini("msger", "ֻ�Ͻ�", PeiZhiText, (string)"");
			setini("msger", "�����Ͻ�", PeiZhiText, (string)"");
		}
		//*pbHandled = TRUE;
		return 0;
	}
	//40�н�
	int OnComboBoxPopupListXJJ(int iItem, BOOL *pbHandled)
	{
		switch (iItem){
		case 0:
			setini("msger", "50�н�", PeiZhiText, (string)"");
			setini("msger", "40�н�", PeiZhiText, (string)"");
			XComboBox_SetSelItem(hComboBoxJS, 1);
			setini("msger", "������ɫ", PeiZhiText, (string)"1");
			break;
		case 1:
			setini("msger", "50�н�", PeiZhiText, (string)"1");
			setini("msger", "40�н�", PeiZhiText, (string)"");
			setini("msger", "�����Ͻ�", PeiZhiText, (string)"");
			XComboBox_SetSelItem(hComboBoxJS, 1);
			setini("msger", "������ɫ", PeiZhiText, (string)"1");
			break;
		case 2:
			setini("msger", "50�н�", PeiZhiText, (string)"");
			setini("msger", "40�н�", PeiZhiText, (string)"1");
			XComboBox_SetSelItem(hComboBoxJS, 0);
			setini("msger", "������ɫ", PeiZhiText, (string)"0");
			break;
		
		}
		//*pbHandled = TRUE;
		return 0;
	}

	//���б༭��---------------------------------------------------------------------------
	void setedit(){
		//�����ſ�
		m_EditJQH = XRichEdit_Create(145, 58, 20, 22, hPage);
		CString jq = getini("����", "������", (CString)PeiZhiText.c_str(), "1");
		XRichEdit_SetText(m_EditJQH, jq);
		JiQi = _ttoi(jq);
		XRichEdit_EnableEvent_XE_RICHEDIT_CHANGE(m_EditJQH, true);
		XEle_RegEventCPP(m_EditJQH, XE_RICHEDIT_CHANGE, &table3::OnRichEditChangeJQH);

		//���ر༭��
		m_EditDK = XRichEdit_Create(145, 32, 28, 22, hPage);
		
		addShapeText(167, 58, 29, 22, hPage, "������");

		//�ű�����
		m_EditHS = XRichEdit_Create(56, 84, 48, 22, hPage);
		//����༭��
		m_EditDM = XRichEdit_Create(80, 160, 75, 22, hPage);
		XRichEdit_SetText(m_EditDM, getini("����", "�Զ������˺�", (CString)PeiZhiText.c_str(), ""));

		//�нŴ���
		m_EditXJCS = XRichEdit_Create(82, 111, 23, 22, hPage);
		XRichEdit_SetText(m_EditXJCS, getini("msger", "�нŴ���", (CString)PeiZhiText.c_str(), "10"));
		XRichEdit_EnableEvent_XE_RICHEDIT_CHANGE(m_EditXJCS, true);
		XEle_RegEventCPP(m_EditXJCS, XE_RICHEDIT_CHANGE, &table3::OnRichEditChangeXJCS);
	}

	//�����ſ�
	int OnRichEditChangeJQH(BOOL *pbHandled){
		wchar_t   cknum[256];
		memset(cknum, 0, 256);
		XRichEdit_GetText(m_EditJQH, cknum, 256);
		JiQi = getEditInt(m_EditJQH);
		setini("����", "������", PeiZhiText, cknum);
		return 0;
	}
	//�нŴ���
	int OnRichEditChangeXJCS(BOOL *pbHandled){
		wchar_t   cknum[256];
		memset(cknum, 0, 256);
		XRichEdit_GetText(m_EditJQH, cknum, 256);
		JiQi = getEditInt(m_EditJQH);
		setini("msger", "�нŴ���", PeiZhiText, cknum);
		return 0;
	}

	//���а�ť-----------------------------------------------------------------
	void setBtn(){
		HELE m_hButton = XBtn_Create(56, 6, 40, 22, L"����", hPage);
		XEle_RegEventCPP(m_hButton, XE_BNCLICK, &table3::OnEventBtnClickYX);
		XEle_SetTextColor(m_hButton, RGB(255, 0, 0), 255);

		m_hButton = XBtn_Create(100, 6, 40, 22, L"��ͣ", hPage);
		XEle_RegEventCPP(m_hButton, XE_BNCLICK, &table3::OnEventBtnClickZT);

		m_hButton = XBtn_Create(56,32, 40, 22, L"�н�", hPage);
		XEle_RegEventCPP(m_hButton, XE_BNCLICK, &table3::OnEventBtnClickXJSZ);

		m_hButton = XBtn_Create(100, 32, 40, 22, L"�ر�", hPage);
		XEle_RegEventCPP(m_hButton, XE_BNCLICK, &table3::OnEventBtnClickGB);
		
		m_hButton = XBtn_Create(177, 32, 50, 22, L"����", hPage);
		XEle_RegEventCPP(m_hButton, XE_BNCLICK, &table3::OnEventBtnClickCZ);
		XEle_RegEventCPP(m_hButton, XE_LBUTTONDBCLICK, &table3::OnEventDBtnClickCZ);
		XEle_SetTextColor(m_hButton, RGB(0, 128, 128), 255);

		m_hButton = XBtn_Create(109, 84, 64, 22, L"���ýű�", hPage);
		XEle_RegEventCPP(m_hButton, XE_BNCLICK, &table3::OnEventBtnClickSZ);
		XEle_SetTextColor(m_hButton, RGB(0, 0, 128), 255);

		m_hButton = XBtn_Create(177, 84, 50, 22, L"�˳�", hPage);
		XEle_RegEventCPP(m_hButton, XE_BNCLICK, &table3::OnEventBtnClickTC);


		m_hButton = XBtn_Create(3, 111, 77, 22, L"�нŴ���", hPage);
		XBtn_SetType(m_hButton, button_type_check);
		XBtn_SetStyle(m_hButton, button_style_check);
		XBtn_SetCheck(m_hButton, getini("msger", "�Ƿ��н�", (CString)PeiZhiText.c_str(), "") == "");
		XEle_RegEventCPP(m_hButton, XE_BUTTON_CHECK, &table3::OnButtonCheckXJ);

		m_hButton = XBtn_Create(3, 135, 77, 22, L"�Ͻ���Ʒ", hPage);
		XBtn_SetType(m_hButton, button_type_check);
		XBtn_SetStyle(m_hButton, button_style_check);
		XBtn_SetCheck(m_hButton, getini("msger", "������Ʒ", (CString)PeiZhiText.c_str(), "") == "");
		XEle_RegEventCPP(m_hButton, XE_BUTTON_CHECK, &table3::OnButtonCheckSJ);

		m_hButton = XBtn_Create(80, 135, 77, 22, L"ֱ�ӽ���", hPage);
		XBtn_SetType(m_hButton, button_type_check);
		XBtn_SetStyle(m_hButton, button_style_check);
		XBtn_SetCheck(m_hButton, getini("msger", "ֱ�ӽ���", (CString)PeiZhiText.c_str(), "") == "1");
		XEle_RegEventCPP(m_hButton, XE_BUTTON_CHECK, &table3::OnButtonCheckZJJY);

		m_hButton = XBtn_Create(3, 160, 77, 22, L"���˴���", hPage);
		XBtn_SetType(m_hButton, button_type_check);
		XBtn_SetStyle(m_hButton, button_style_check);
		XBtn_SetCheck(m_hButton, getini("����", "�Զ�����", (CString)PeiZhiText.c_str(), "") == "1");
		XEle_RegEventCPP(m_hButton, XE_BUTTON_CHECK, &table3::OnButtonCheckZDD);

		m_hButtonDMCX = XBtn_Create(157, 160, 70, 22, L"��ѯ��", hPage);
		XEle_RegEventCPP(m_hButtonDMCX, XE_BNCLICK, &table3::OnEventBtnClickDMCX);
	}

	//����
	int OnEventBtnClickYX(BOOL *pbHandled)
	{
		int k, j;
		getKStoJS(k, j);
		for (k; k <= j; k++){
			if (winls[k].h > 0)setRoot(k);
		}
		return 0;
	}
	//��ͣ
	int OnEventBtnClickZT(BOOL *pbHandled)
	{
		int k, j;
		getKStoJS(k, j);
		for (k; k <= j; k++){
			if (winls[k].h > 0)PostMessageA(winls[k].h, 52228, 3, 0);;
		}

		return 0;
	}
	//�н�����
	int OnEventBtnClickXJSZ(BOOL *pbHandled)
	{
		
		XRichEdit_SetText(m_EditHS, L"4");
		setXJHS();
		return 0;
	}

	//�رմ���
	int OnEventBtnClickGB(BOOL *pbHandled)
	{
		CString text = "�Ƿ�ر�������������";
		//xtrace("444   %d", getEditInt(m_EditDK));
		int ck = getEditInt(m_EditDK);
		if (ck > 0){
			text = "�Ƿ�رյ� " + intToCstr(ck) + " ����������";
		}
		else{
			CString t = "";
			switch (FenKong){
			case 0:
				t = "ȫ��";
				break;
			case 1:
				t = "1-5";
				break;
			case 2:
				t = "6-10";
				break;
			case 3:
				t = "11-15";
				break;
			case 4:
				t = "16-20";
				break;
			}
			text = "�Ƿ�رյ� " + t + " ����������";
		}
		if (MessageBox(myHwnd, text, L"��ʾ", MB_YESNO) == 6){
			if (ck > 0){
				if (winls[ck-1].h > 0){
					for (int i = 0; i < 3; i++){
						if (myKillProcess(winls[ck-1].h)){
							break;
							winls[ck-1].h = 0;
						}
						Sleep(100);
					}
				}
			}
			else{
				int k, j;
				getKStoJS(k, j);
				for (k; k <= j; k++){
					if (winls[k].h > 0){
						for (int i = 0; i < 3; i++){
							if (myKillProcess(winls[k].h)){
								break;
								winls[k].h = 0;
							}
							Sleep(100);
						}
					}
				}
			}
		}

		
		return 0;
	}

	//����
	int OnEventBtnClickCZ(BOOL *pbHandled)
	{
		
		int ck = getEditInt(m_EditDK);
		if (ck > 0){
			if (ck<=MAXWIN && winls[ck-1].h>0)
				PostMessageA(winls[ck-1].h, 52228, 2, 0);
		}
		else{
			int k, j;
			getKStoJS(k, j);
			for (k; k <= j; k++){
				if ( winls[k].h>0)
					PostMessageA(winls[k].h, 52228, 2, 0);
			}
		}
		return 0;
	}

	int OnEventDBtnClickCZ(BOOL *pbHandled){
		rumtext.clear();
		vector<CString>().swap(rumtext);
		takeluatext();
		toQipao("���سɹ�!");
		return 0;
	}
	
	//���ýű�����
	int OnEventBtnClickSZ(BOOL *pbHandled)
	{
		setXJHS();
		return 0;
	}

	//�˳�
	int OnEventBtnClickTC(BOOL *pbHandled)
	{

		CString text = "ȷ��Ҫ�˳��� " +( FenKong>0? intToCstr(FenKong):"ȫ��") + " ����?";
		if (MessageBox(myHwnd, text, L"��ʾ", MB_YESNO) == 6){
			::CreateThread(0, 0, exitRootThread, 0, 0, 0);
		}
		return 0;
	}
	

	//�Ƿ��н�
	int OnButtonCheckXJ(BOOL bCheck, BOOL *pbHandled)
	{
		//Output("ddd  %d \n", bCheck);
		setini((string)"msger", "�Ƿ��н�", PeiZhiText, bCheck ? "" : "1");
		xtrace("��ť�Ƿ�ѡ�� %s \r\n", bCheck ? "��" : "δѡ��");
		return 0;
	}
	//�Ͻ���Ʒ
	int OnButtonCheckSJ(BOOL bCheck, BOOL *pbHandled)
	{
		setini((string)"msger", "������Ʒ", PeiZhiText, bCheck ? "" : "1");
		return 0;
	}

	//ֱ�ӽ���
	int OnButtonCheckZJJY(BOOL bCheck, BOOL *pbHandled)
	{
		setini((string)"msger", "ֱ�ӽ���", PeiZhiText, bCheck ? "1" : "");
		return 0;
	}

	//�Զ�����
	int OnButtonCheckZDD(BOOL bCheck, BOOL *pbHandled)
	{
		setini((string)"����", "�Զ�����", PeiZhiText, bCheck ? "1" : "");
		setini("����", "�Զ������˺�", PeiZhiText, getEditS(m_EditDM));
		return 0;
	}

	//��ѯ��
	int OnEventBtnClickDMCX(BOOL *pbHandled)
	{

		vector<string> array;
		split(getini("����", "�Զ������˺�", PeiZhiText, ""), "-", array);
		if (array.size() > 1){
			CString d=GetUserInfo((LPSTR)array[0].c_str(), (LPSTR)array[1].c_str());
			d = "���˳������: " + d + " ��(10��һ��)";

			MessageBox(myHwnd, d, L"�Զ�����", MB_OK);
		}
		return 0;
	}

	

	void Init(){
		setXiaLaKuang();
		setedit();
		setBtn();
	}
};