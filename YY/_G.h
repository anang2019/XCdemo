string WindowsYXbt = "QQ����1.0";
const static string textLS = "D:\\YY\\";
string PeiZhiText = "D:\\YY\\config.ini";
string PeiZhiXingJiao;
const int MAXWIN = 20;
vector<CString> rumtext;//�ű�����

HELE m_hList; //�б�
HXCGUI hAdapter;//�б�������
HELE m_hButtonAJ1;//��ť1


const string SJ_NAME_H="��,ӱ,��,����,ǧ��,ҡ٤,��,ӯ,ܾ,Ī��,����,��ӥ,��,ӣ,��,��ɫ,Ӣ��,����,�,ӫ,��,����,����,����,����,ͮ,ө,�,����,�ɷ�,����,���,ͩ,ݺ,��,����,����,����,��ħ,֥,��,��,����,ɺɺ,���,��,��,�,��,����,��ѩ,Ψѩ,��Ѫ,��,ܽ,��,����,ѩһ,����,����,��,��,��,����,����,���,Ѫ��,��,��,��,����,ӫӫ,���,����,���,����,��ԯ,����,�ػ�,����,����,����,����,����,��Ӱ,��Ը,��ϼ,����,����,���,����,����,�鶯,����,��Ӱ,����,����,ɽ�,����,����,���,����,����,���,����,����,����,�뻭,����,��Ӱ,���,����,����,����,���,��ѩ,����,��ɴ,ҹ��,��΢,����,����,���,����,����,����,����,����,����,����,����,��¶,����,��ҫ,���,����,��Ϫ,΢��,ů��,����,�»�,�峾,����,Ѥ��,����,�派,����,����,����,����,����,����,��ɪ,���,а��,����,����,����,Ц��,���,����,����,����,����,��ѩ,����,����,����,֮��,��Ѫ,��ɳ,Ѫɷ,����,��ħ,����,����,����,����,ѹ��,����,���,����,����,����,׷��,��֮,ս��,����,С˧,����,�,ͯ��,��Ͼ,�ഺ,����,Ī��,����,Ұ��,����,����,����,��Ц,����,����,˵��,��Ů,����,ǧ��,С��,�ٺ�,����,����,ˮ��,���,Ůģ,ױĨ,���,ǹ��,����,����,����,ǹ��,���,õ��,����,����,����,����,ӣ��,С��,����,����,����,����,����,Ϧ��,����,����,��,����";
const string SJ_NAME_Q = "��δ��,���ؼ�,ҹδ��,������,Ҷδ��,���㾲,������,���Ƕ�,������,���ļ�,��˿��,��ߣ��,�𷸼�,����Ů,���д�,��С��,ҹ�»�,������,��߹�^,؈؈ˮ,�Ⱦ���,������,������,������,����ң,ǳޱ��,���,�����,�����,�ݼ���,��Ѭױ,С��è,Ѫ����,��С��,������,������,������,��ǳ��,��ǧ��,��ů��,������,������,������,������,Сƿ��,���˰�,�����,İ·��,���˹�,��Ȼ��,�Թ���,�����,�δ���,�ȶ���,ôô��,����Ϊ,������,������,������,�輺��,��С��,���Զ�,��˿Ů,����ʮ,��ӵ��,������,�����,�ò���,������,�䳾ѩ,�����,�����,�����,��˿��,���ݺ�,�ֿ�Ӵ,������,��̫��,����β,ŷ����,��Ĭ��,�׶���,������,ҹδ��,������,��ͣ��,������,������,��ʧ��,��ӵ��,��Ĵ�,�����,������,�����,��С��,������,�Ҳ���,һ����,��Ƿ��,������,���ѹ�,�鳤��,ֻ����������,������,������,�ܶ�ô,�����,�̸���,̫����,������,������,�ӻ���,�ϸ�,�ȴ�,��ָ,����,����,Ű����,ǳĺ,����,����,�b�O,��,����,����,ش��,������,����,��ޢ,��ʪ��";
const string SJ_NAME_Z = "ؼ,��,ذ,��,��,��,��,�R,��,��,ڢ,��,��,��,��,��,�[,ڥ,��,ܳ,��,��,��,��,��,��,��,��,�,��,��,�,��,��,��,��,أ,Ϧ,��,��,߮,��,�,��,�j,�S,�,��,��,س,�h,��,��,��,�H,҂,��,�i,ؐ,�u,��,�z,�L,�f,��,�Y,�R,��,�B,�~,a,b,c,d,e,f,g,l,r,t,v,w,m,k,i";
const CString NOT_BJ_TEXT = "|�ҹ���|�н�|��������,��8������1|��������,��������55|����,����ƾ֤5|ƴͼ|����,��1��ƾ֤5|�ȴ�����,1|�ȴ�����|";
#define XE_USER_SET 52227

//�ؼ����ȫ�ֱ���------------------------------------------
int JiQi = 1;
int buying = 0;//���׺ű�־
bool isDateList = false;


//���ֿ��ر���---------------------------------
int DaMaHwend = 0;//����Ĵ��ھ��
int DaMaPos = 0;//���������
string softId; //����ID
int JingBao = 0;//������־
int JingBaoYin = 0;//����������־
LONGLONG JingBaoTime = 0; //����ʱ��
DWORD JingBaoTime1 = 0; //����ʱ��
int XMgs = 0;//����������
int FenKong = 0;//1-5,6-10�ֿ�
int waitteam = 0;//�ȴ�����
int waitteamall = 0;//�ȴ�����
int TimerNum = 0; //ʱ�Ӽ���
int onNum = -0;//�к�
int isRootT = 0;// ��¼�߳��Ƿ�����
int autoExit = 0;//�Զ��ػ�
CString Qipao;//
bool isGoWin=false;
int isUpDate = -1;

//tab   1---------------------------------
HELE m_KckEdit;//������
HELE hComboBoxFS;//���ŷ�ʽ
HELE hComboBoxXL;//��¼��
HELE hComboBoxXX;//ѡ��
HELE hComboBoxBT;//ѡ��̯��
HELE hComboBoxJS;//ѡ��̯��

HELE m_EditXH;//���
HELE m_EditSJ;//�ս�༭��
HELE m_EditZDHH;//��󻻺�
HXCGUI m_textKD;//�������
HELE m_EditIP;//IP��¼
HXCGUI tipShapeText;//��ʾIP
HELE m_hButtonExit;//��ɹػ�
//tab   1---------------------------------

//tab   3---------------------------------
HELE m_EditJQH;//�����ſ�
HELE m_EditDK;//���ر༭��
HELE m_EditHS;//�ű�����
HELE m_EditDM;//�����˺�
HELE m_EditXJCS;//�ű�����
HELE m_hButtonDMCX;//��ѯ��
//tab   3---------------------------------

HWND myHwnd;

//--------------------�ṹ��
struct LBK{
	int rootnum = 1;
	int rootp = 2;
	int name = 3;
	int nl = 4;
	int money = 5;
	int xjs = 6;
	int run = 7;
	int look = 8;
	int runnum = 9;
	int csime = 10;
	int text = 11;
}lbk;

struct CKSJ{
	HWND h;
	int hs, rootnum, cstime, hsjl, hskg, notbj,wxy;
}winls[MAXWIN];

//--------------------�ṹ��


//�ı��ؼ�
HXCGUI addShapeText(int x, int y, int w, int h, HELE f, CString text){
	//HELE   hEle = XEle_Create(x, y, w, h, f);
	HXCGUI hTextBlock = XShapeText_Create(x, y, w, h, text, f);
	XShapeText_SetTextAlign(hTextBlock, textAlignFlag_vcenter);
	//XShapeText_SetTextColor(hTextBlock, RGB(128, 0, 64), 255);
	//XShapeText_SetLayoutWidth(hTextBlock, layout_size_type_weight, 0);
	//XShapeText_SetLayoutHeight(hTextBlock, layout_size_type_weight, 0);
	return hTextBlock;
}


void setlistbool(int i, int j, bool bn, bool btn = false, bool isShow = true){
	if (i >= XMgs || j > 11)return ;
	XList_SetItemData(m_hList, i, j, bn);
	if (btn){
		HXCGUI hBtn = XList_GetTemplateObject(m_hList, i,0, j);
		if (XC_GetObjectType(hBtn) == XC_BUTTON)
		{
			XBtn_SetCheck((HELE)hBtn, bn);
		}
	}
	if (isDateList&&isShow)
		XEle_RedrawEle(m_hList, true);

}

BOOL getlistbool(int i, int j){
	if (i >= XMgs || j > 11)return false;
	return XList_GetItemData(m_hList, i, j);
}

CString getlisttext(int h, int l){
	if (h >= XMgs || l > 11)return "";
	wchar_t   cknum[256];
	memset(cknum, 0, 256);
	XAdTable_GetItemText(hAdapter, h, l, cknum, 256);
	CString aaa = cknum;
	return aaa;
}



void setlisttext(int h, int l, CString text, bool bn=false){
	if (h >= XMgs || l > 11)return;
	XAdTable_SetItemText(hAdapter, h, l, text);

	//Output("oo,����:1111    %s\n", getlisttext( h, l));
	if (isUpDate!=h)
	XList_RefreshItem(m_hList, h);

	if (isDateList&&!bn)XEle_RedrawEle(m_hList, true);
}

int getEditInt(HELE edit){
	wchar_t   cknum[256];
	memset(cknum, 0, 256);
	XRichEdit_GetText(edit, cknum, 256);
	return _ttoi(cknum);
}

CString getEditS(HELE edit){
	wchar_t   cknum[256];
	memset(cknum, 0, 256);
	XRichEdit_GetText(edit, cknum, 256);
	return (CString)cknum;
}

void toQipao(CString text){
	Qipao = text;
	PostMessage(myHwnd, 50000, 0, 0);
}
void toQipao1(CString text){
	//XShapeText_SetText(QiPao, text);
	//XEle_RedrawEle(m_EditDK, true);
	XEle_SetToolTip(m_EditDK, text);
	XEle_PopupToolTip(m_EditDK, 100, 0);
}

//luaȡ�ű�
void takeluatext(){
	ifstream infile;

	string ll = textLS + "ufo.txt";

	infile.open(ll);

	xtrace("ȡ�ű�   %s", ll.c_str());
	string text;
	rumtext.push_back("");
	while (getline(infile, text)){
		rumtext.push_back((CString)text.c_str());
	}
	xtrace("ȡ�ű�%d\n", rumtext.size());
	infile.close();

}

//��ʱ��
int JiShiqi(bool n=false){
	if (n){
		JingBaoTime1 = GetTickCount();
		Output("oo,���� ��ʱ��ʼ%d \n", JingBaoTime1);
	}
	else{
		LONGLONG result = GetTickCount();
		Output("oo,���� ��ʱ��  %d     \n", result - JingBaoTime1);
	}
	return 0;
}