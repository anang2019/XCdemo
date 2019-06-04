string WindowsYXbt = "QQÈý¹ú1.0";
const static string textLS = "D:\\YY\\";
string PeiZhiText = "D:\\YY\\config.ini";
string PeiZhiXingJiao;
const int MAXWIN = 20;
vector<CString> rumtext;//½Å±¾Êý×é

HELE m_hList; //ÁÐ±í
HXCGUI hAdapter;//ÁÐ±íÊÊÅäÆ÷
HELE m_hButtonAJ1;//°´Å¥1


const string SJ_NAME_H="Üø,Ó±,æÌ,ÎÞÑÕ,Ç§³î,Ò¡Ù¤,Ãô,Ó¯,Ü¾,ÄªÑÔ,ÖÉÇç,·ÆÓ¥,ÆÎ,Ó£,·ï,ÎÞÉ«,Ó¢¹Ã,±ùÑÕ,æ­,Ó«,Öé,ÑÇÄÐ,ÈôÑÕ,ÎÞÐÄ,Á°Ñý,Í®,Ó©,ä¨,ËØÒõ,·É·É,²ØÄñ,ò¯ÎÆ,Í©,Ýº,óÃ,ÈôÄÐ,ÃîÇÛ,Èô±ù,ÈôÄ§,Ö¥,çø,ÂÜ,ÃðÄÐ,ÉºÉº,æÌæ¬,çºçº,ÜÆ,è¬,´ä,¸ßÀö,ÈçÑ©,Î¨Ñ©,ÑÞÑª,×Ë,Ü½,ÝÍ,ÑýÀö,Ñ©Ò»,·ÆÒô,¾øÒô,Üë,ÜÀ,Èá,ÈýÑÕ,ÜøÜø,Èç±ù,ÑªÜø,äÊ,Ïæ,Çß,´úÄÐ,Ó«Ó«,Èçæ¬,·ïÑý,çÎç¿,ÓðÉÑ,ÐùÔ¯,×ÏÝæ,ÉØ»ª,¸¡¹â,ÑÌÓê,µûÎè,²øÃà,¾øÁµ,±ÌÓ°,ÐÇÔ¸,ÂäÏ¼,ÍüÓÇ,»ÃÕæ,ôæ·É,¾ªºè,ÐÇÔÂ,Çé¶¯,»¯Óð,¾øÓ°,×íÃÎ,²¨À½,É½á°,´º»ª,ÐÇÓê,ºÆå«,·çÏô,¸¡²¨,Öð·ç,²×À½,ºèðÀ,ÈçÃÎ,Èë»­,ÇàÒÂ,Á÷Ó°,ÊæºÉ,ÄÞÉÑ,ÇåÇú,×íÔÂ,·çºÍ,ÈðÑ©,ãåÓî,ÎèÉ´,Ò¹Ãì,ÎÞÎ¢,³¿Ñô,¼ÑÈÝ,Íð±Ì,ÎÆÏã,èóÒô,¾²Ïþ,ÈóÓñ,‹ÖÃà,Ã÷Ðã,¹éÔÆ,´º‹„,ÏÄÂ¶,ÇïÑÕ,¶¬Ò«,ç×ç¹,Á°äô,ÈôÏª,Î¢Á¹,Å¯Ñô,°ëÏÄ,ÑÂ»Ú,Âå³¾,ñæÈá,Ñ¤ÀÃ,½ÃÇé,Õæ´¾,Ã÷ÃÄ,ÃÔÀë,ÒþÈÌ,×ÆÈÈ,»ÃÃð,ÂäÍØ,½õÉª,Ñýæ¬,Ð°éä,Àëéä,ÁµÏÄ,»¶Éù,Ð¦Óï,Çã³Ç,¼ÑÈË,ºöÀä,ºöÈÈ,¶ÏÇÅ,²ÐÑ©,¾ÅÌì,¶À×ð,ÍêÃÀ,Ö®µß,°ÁÑª,¿ñÉ³,ÑªÉ·,°ÁÌì,¶ñÄ§,×ðÖ÷,°ÔÕß,¹éÀ´,ÖÚÉñ,Ñ¹ÖÆ,°ÔÆø,ÌìµÛ,Ö÷Ô×,·çÔÆ,·çÖÐ,×·ÔÂ,ÔóÖ®,Õ½Éñ,³¤¿Õ,Ð¡Ë§,ÐÄËÆ,Éîº£,Í¯Äê,ÎÞÏ¾,Çà´º,·ÅËÁ,ÄªÆú,·ÖÀë,Ò°Âù,µ°µ°,ÑÛÀá,ÈÝÑÕ,âùÐ¦,ÌìÏÂ,³ÕÈË,ËµÃÎ,ÉñÅ®,ÓÎÏÀ,Ç§Äê,Ð¡¸Ö,°ÙºÏ,Óù½ã,´¿Çé,Ë®ÊÖ,Èâ¸Ð,Å®Ä£,×±Ä¨,Çå·ç,Ç¹Îè,ÕÜÐã,ÓôÓô,ÂñÏã,Ç¹Îè,ï¬ïÏ,Ãµ¹å,ÓùÛà,ÃÃÃÃ,¶º±È,·¢¹â,Ó£»¨,Ð¡½ã,ÏÂÂä,²»Ã÷,ÍùÊÂ,ÈçÑÌ,´ÌÑÛ,Ï¦Ñô,ÁãÐÇ,¼ÇÒä,Âó¶µ,Âé×í";
const string SJ_NAME_Q = "»¨Î´Ãß,·üÌØ¼Ó,Ò¹Î´Ñë,ÎðÕæÐÄ,Ò¶Î´Áã,éäÁã¾²,éäÁãÑÀ,ÉÙÈÇ¶í,ÄäÃûÕß,¹¥ÐÄ¼Ë,ŒÅË¿·¶,»¥ß£ÍÞ,±ð·¸¼ú,”¡¼ÒÅ®,¼úÄÐ´º,ÌÇÐ¡¶º,Ò¹¹Â»ê,µûÁµ»¨,¯‚ß¹î^,ØˆØˆË®,µÈ¾ý¹é,ÅÝÅÝÓã,¸ú·ç×ß,·¨¿ËöÏ,×íåÐÒ£,Ç³Þ±°²,Éî°­¹ý,º®·ç²Ð,Íí·çÁ¹,ÑÝ¼ËÅÉ,ÑÌÑ¬×±,Ð¡ÀÁÃ¨,Ñª¸£¼À,ß÷Ð¡ÀÁ,ÑáÈËÐÄ,ºÚÃûµ¥,¾ÉÈÝÑÕ,°²Ç³ÏÄ,¹ÂÇ§Óð,¹ËÅ¯³Ç,¾ÉÇàÉÀ,°×ÈÕÃÈ,µØÓü»ð,»¨ÑÕ×í,Ð¡Æ¿¸Ç,¾ÉÉË°Ì,ÖÕÈç³õ,Ä°Â·ÈË,¹ÊÈË¹é,ÌìÈ»´ô,¹Ô¹ÔßÕ,¹ËÇå·ç,ºÎ´¦¹é,ÃÈ¶þ´ú,Ã´Ã´ÐÜ,ÎÒÒÔÎª,Á½ÏàÍü,ÈýÉúÄê,ÎÒÔÚÕâ,Óè¼ºÊé,ËÕÐ¡ÌÃ,¸ñÑÔ¶à,ŒÅË¿Å®,¼¸¸öÊ®,½ôÓµÎÒ,½ûïÀÎÒ,·ð¶àÀï,¾Ã²»¼û,»ª³¿Óî,Àä³¾Ñ©,ÀäÃæ¿×,±ðÔì´Î,»ÆÓã¸ç,ŒÅË¿ÄÐ,µÍÉÝº­,¹Ö¿§Ó´,Ñþ±ùÆÇ,ÐÄÌ«ÂÒ,³¤ÂíÎ²,Å·ÃÀ·¶,³ÁÄ¬¿Ø,Â×¶ØÇé,ÌìÓÐÇé,Ò¹Î´Ñë,ÖÐÇéÈË,ÇéÍ£»ú,³õÓöÄã,ËýÏÈÉú,ÇéÊ§¿Ø,ÉîÓµÄã,ÄãµÄ´½,ÄãµÄÎÇ,»µÄÐÈË,ÆæÝâà»,ÄÌÐ¡°ü,¾ÉÏÄÌì,ÎÒ²»Áô,Ò»¸öÈË,°®Ç··Ñ,Óö¼ûËû,°®ÒÑ¹ý,°é³¤»¶,Ö»ÛÄãÍ÷ÉÙÄê,¸ºÖÇÉÌ,ÁðÁ§Ïã,ºÜ¶ºÃ´,Àë»êÇú,ƒÌ¸á×Ó,Ì«êÓÃÁ,ÇéÒÑÉË,³àÂãÂã,ÂÓ»êÕß,óÏ¸è,µÈ´ý,ËØÖ¸,ÂäÀ¼,¶À¹Â,Å°ÒþÄï,Ç³Äº,Á÷éä,›²Äê,Áb½O,Íí°²,ÇãÌý,ÓêÂä,Ø´ÑÔ,×í×í×í,»¨Òõ,¶¹Þ¢,ÀáÊªÁË";
const string SJ_NAME_Z = "Ø¼,Ùè,Ø°,²·,ØÖ,ØÎ,Úâ,R,Úà,Øç,Ú¢,ÈË,Øé,Èë,ÛÌ,Ùï,…[,Ú¥,ÛÈ,Ü³,áÜ,çÝ,´¨,åÁ,ÞÃ,åæ,Ÿ,½í,å²,áë,áê,â»,ÞÐ,ãß,æù,ËÈ,Ø£,Ï¦,âà,çÛ,ß®,ÞÌ,âº,ìá,…j,ÂS,í±,ãÝ,ìê,Ø³,°h,îÄ,ÀŸ,ñç,ÆH,Ò‚,ôé,¼i,Ø,Þu,õô,ïz,ïL,íf,ÛË,ôY,ñR,ûœ,øB,ô~,a,b,c,d,e,f,g,l,r,t,v,w,m,k,i";
const CString NOT_BJ_TEXT = "|ÕÒ¹úÁî|ÐÐ½Å|ÔËËÍÈÎÎñ,ÔË8ËÍÎï×Ê1|ÔËËÍÈÎÎñ,ÔËËÍÎï×Ê55|¾²ÐÞ,¾²ÐÞÆ¾Ö¤5|Æ´Í¼|¾²ÐÞ,¾²1ÐÞÆ¾Ö¤5|µÈ´ý¶ÓÓÑ,1|µÈ´ý¶ÓÓÑ|";
#define XE_USER_SET 52227

//¿Ø¼þ½á¹ûÈ«¾Ö±äÁ¿------------------------------------------
int JiQi = 1;
int buying = 0;//½»Ò×ºÅ±êÖ¾
bool isDateList = false;


//¸÷ÖÖ¿ª¹Ø±äÁ¿---------------------------------
int DaMaHwend = 0;//´òÂëµÄ´°¿Ú¾ä±ú
int DaMaPos = 0;//´òÂëµÄ×ø±ê
string softId; //´òÂëID
int JingBao = 0;//¾¯±¨±êÖ¾
int JingBaoYin = 0;//¾¯±¨ÉùÒô±êÖ¾
LONGLONG JingBaoTime = 0; //¾¯±¨Ê±¼ä
DWORD JingBaoTime1 = 0; //¾¯±¨Ê±¼ä
int XMgs = 0;//³¬±í×ÜÐÐÊý
int FenKong = 0;//1-5,6-10·Ö¿Ø
int waitteam = 0;//µÈ´ý¶ÓÓÑ
int waitteamall = 0;//µÈ´ý¶ÓÓÑ
int TimerNum = 0; //Ê±ÖÓ¼ÆÊý
int onNum = -0;//ÐÐºÅ
int isRootT = 0;// µÇÂ¼Ïß³ÌÊÇ·ñÆô¶¯
int autoExit = 0;//×Ô¶¯¹Ø»ú
CString Qipao;//
bool isGoWin=false;
int isUpDate = -1;

//tab   1---------------------------------
HELE m_KckEdit;//¿ª´°¿Ú
HELE hComboBoxFS;//»»ºÅ·½Ê½
HELE hComboBoxXL;//µÇÂ¼Ïß
HELE hComboBoxXX;//Ñ¡Ïß
HELE hComboBoxBT;//Ñ¡°ÚÌ¯Ïß
HELE hComboBoxJS;//Ñ¡°ÚÌ¯Ïß

HELE m_EditXH;//ÐòºÅ
HELE m_EditSJ;//ÊÕ½ð±à¼­¿ò
HELE m_EditZDHH;//×î´ó»»ºÅ
HXCGUI m_textKD;//¿í´øÁ¬½Ó
HELE m_EditIP;//IP¼ÇÂ¼
HXCGUI tipShapeText;//ÌáÊ¾IP
HELE m_hButtonExit;//Íê³É¹Ø»ú
//tab   1---------------------------------

//tab   3---------------------------------
HELE m_EditJQH;//»úÆ÷ºÅ¿ò
HELE m_EditDK;//µ¥¿Ø±à¼­¿ò
HELE m_EditHS;//½Å±¾ÐÐÊý
HELE m_EditDM;//´òÂëÕËºÅ
HELE m_EditXJCS;//½Å±¾ÐÐÊý
HELE m_hButtonDMCX;//²éÑ¯µã
//tab   3---------------------------------

HWND myHwnd;

//--------------------½á¹¹Ìå
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

//--------------------½á¹¹Ìå


//ÎÄ±¾¿Ø¼þ
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

	//Output("oo,¹ÜÀí:1111    %s\n", getlisttext( h, l));
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

//luaÈ¡½Å±¾
void takeluatext(){
	ifstream infile;

	string ll = textLS + "ufo.txt";

	infile.open(ll);

	xtrace("È¡½Å±¾   %s", ll.c_str());
	string text;
	rumtext.push_back("");
	while (getline(infile, text)){
		rumtext.push_back((CString)text.c_str());
	}
	xtrace("È¡½Å±¾%d\n", rumtext.size());
	infile.close();

}

//¼ÆÊ±¼ä
int JiShiqi(bool n=false){
	if (n){
		JingBaoTime1 = GetTickCount();
		Output("oo,¹ÜÀí ¼ÆÊ±¿ªÊ¼%d \n", JingBaoTime1);
	}
	else{
		LONGLONG result = GetTickCount();
		Output("oo,¹ÜÀí ¼ÆÊ±Æ÷  %d     \n", result - JingBaoTime1);
	}
	return 0;
}