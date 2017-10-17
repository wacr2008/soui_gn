#include <assert.h>
#include "LunarCalendar.h"


namespace SOUI {

//数组存入阴历1900年到2100年每年中的月天数信息， 
//阴历每月只能是29或30天，一年用12（或13）个二进制位表示，对应位为1表30天，否则为29天 
const int CLunarCalendar::m_lunarInfo[]={ //农历日期信息
0x4bd8,0x4ae0,0xa570,0x54d5,0xd260,0xd950,0x5554,0x56af,0x9ad0,0x55d2,//1900-1909
0x4ae0,0xa5b6,0xa4d0,0xd250,0xd255,0xb54f,0xd6a0,0xada2,0x95b0,0x4977,//1910-1919
0x497f,0xa4b0,0xb4b5,0x6a50,0x6d40,0xab54,0x2b6f,0x9570,0x52f2,0x4970,//1920-1929
0x6566,0xd4a0,0xea50,0x6a95,0x5adf,0x2b60,0x86e3,0x92ef,0xc8d7,0xc95f,//1930-1939
0xd4a0,0xd8a6,0xb55f,0x56a0,0xa5b4,0x25df,0x92d0,0xd2b2,0xa950,0xb557,//1940-1949
0x6ca0,0xb550,0x5355,0x4daf,0xa5b0,0x4573,0x52bf,0xa9a8,0xe950,0x6aa0,//1950-1959
0xaea6,0xab50,0x4b60,0xaae4,0xa570,0x5260,0xf263,0xd950,0x5b57,0x56a0,//1960-1969
0x96d0,0x4dd5,0x4ad0,0xa4d0,0xd4d4,0xd250,0xd558,0xb540,0xb6a0,0x95a6,//1970-1979
0x95bf,0x49b0,0xa974,0xa4b0,0xb27a,0x6a50,0x6d40,0xaf46,0xab60,0x9570,//1980-1989
0x4af5,0x4970,0x64b0,0x74a3,0xea50,0x6b58,0x5ac0,0xab60,0x96d5,0x92e0,//1990-1999
0xc960,0xd954,0xd4a0,0xda50,0x7552,0x56a0,0xabb7,0x25d0,0x92d0,0xcab5,//2000-2009
0xa950,0xb4a0,0xbaa4,0xad50,0x55d9,0x4ba0,0xa5b0,0x5176,0x52bf,0xa930,//2010-2019
0x7954,0x6aa0,0xad50,0x5b52,0x4b60,0xa6e6,0xa4e0,0xd260,0xea65,0xd530,//2020-2029
0x5aa0,0x76a3,0x96d0,0x4afb,0x4ad0,0xa4d0,0xd0b6,0xd25f,0xd520,0xdd45,//2030-2039
0xb5a0,0x56d0,0x55b2,0x49b0,0xa577,0xa4b0,0xaa50,0xb255,0x6d2f,0xada0,//2040-2049

0x4b63,0x937f,0x49f8,0x4970,0x64b0,0x68a6,0xea5f,0x6b20,0xa6c4,0xaaef,//2050-2059
0x92e0,0xd2e3,0xc960,0xd557,0xd4a0,0xda50,0x5d55,0x56a0,0xa6d0,0x55d4,//2060-2069
0x52d0,0xa9b8,0xa950,0xb4a0,0xb6a6,0xad50,0x55a0,0xaba4,0xa5b0,0x52b0,//2070-2079
0xb273,0x6930,0x7337,0x6aa0,0xad50,0x4b55,0x4b6f,0xa570,0x54e4,0xd260,//2080-2089
0xe968,0xd520,0xdaa0,0x6aa6,0x56df,0x4ae0,0xa9d4,0xa4d0,0xd150,0xf252,//2090-2099
0x0d520//2100
};

const SStringT CLunarCalendar::m_TIANGAN[]={ //天干
_T("甲"),_T("乙"),_T("丙"),_T("丁"),_T("戊"),_T("己"),_T("庚"),_T("辛"),
_T("壬"),_T("癸")
};

const SStringT CLunarCalendar::m_DIZHI[]={ //地支
_T("子"),_T("丑"),_T("寅"),_T("卯"),_T("辰"),_T("巳"),_T("午"),_T("未"),
_T("申"),_T("酉"),_T("戌"),_T("亥") 
};

const SStringT CLunarCalendar::m_Animals[]={ //生肖
_T("鼠"),_T("牛"),_T("虎"),_T("兔"),_T("龙"),_T("蛇"),_T("马"),_T("羊"),
_T("猴"),_T("鸡"),_T("狗"),_T("猪")
};

const SStringT CLunarCalendar::m_nStr1[]={ //数字的中文描述
_T("日"),_T("一"),_T("二"),_T("三"),_T("四"),_T("五"),_T("六"),_T("七"),
_T("八"),_T("九"),_T("十"),_T("十一"),_T("十二")
};

//const SStringT CLunarCalendar::m_cMonName[]  = {"*","正","二","三","四","五","六", "七","八","九","十","十一","腊"};//农历月的名称

const SStringT CLunarCalendar::m_nStr2[]={ //数字的中文描述
_T("初"),_T("十"),_T("廿"),_T("卅"),_T("□")
};

const int CLunarCalendar::m_solarMonth[]={ //月的天数
31,28,31,30,31,30,31,31,30,31,30,31
};

const SStringT CLunarCalendar::m_solarTerm[]={ //节气的中文描述
_T("小寒"),_T("大寒"),_T("立春"),_T("雨水"),_T("惊蛰"),_T("春分"),_T("清明"),
_T("谷雨"),_T("立夏"),_T("小满"),_T("芒种"),_T("夏至"),_T("小暑"),_T("大暑"),
_T("立秋"),_T("处暑"),_T("白露"),_T("秋分"),_T("寒露"),_T("霜降"),_T("立冬"),
_T("小雪"),_T("大雪"),_T("冬至")
};

/*
每年的正小寒点到各节期正节期点（即十五度倍数点）的分钟数。   
地球公转每年都一样   
由于公转轨道是椭圆，故这个数列并不是准确的等差数列
*/ 
const int CLunarCalendar::m_sTermInfo[]={ //节气的日期信息
0,21208,42467,63836,85337,107014,128867,150921,173149,195551,218072,240693,
263343,285989,308563,331033,353350,375494,397447,419210,440795,462224,483532,
504758
};

const SStringT CLunarCalendar::m_monthName[]={ //月的英文描述
_T("JAN"),_T("FEB"),_T("MAR"),_T("APR"),_T("MAY"),_T("JUN"),_T("JUL"),_T("AUG"),
_T("SEP"),_T("OCT"),_T("NOV"),_T("DEC")
};

const SStringT CLunarCalendar::m_sFtv[]={ //公历节日 *表示放假日
_T("0101*新年元旦"),
_T("0106 中国13亿人口日[2005]"),
_T("0108 周恩来逝世纪念日[1976]"),
_T("0121 列宁逝世纪念日[1924]"),
_T("0127 宋庆龄诞辰纪念日[1893]"),
//-
_T("0202 世界湿地日[1996]"),
_T("0207 国际声援南非日[1964]"),
_T("0210 世界气象日[1960]"),
_T("0214 西方情人节"),
_T("0215 中国12亿人口日[1995]"),
_T("0219 邓小平逝世纪念日[1997]"),
_T("0221 反对殖民制度斗争日[1949]"),
_T("0224 第三世界青年日"),
_T("0228 世界居住条件调查日"),
//-
_T("0301 国际海豹日[1983]"),
_T("0303 全国爱耳日[2000]"),
_T("0305 中国青年志愿者服务日[2000] 毛泽东题词“向雷锋同志学习”[1963] 周恩来诞辰纪念日[1898] 斯大林逝世纪念日[1953]"),
_T("0308 国际妇女节[1910]"),
_T("0312 植树节[1979] 孙中山逝世纪念日"),
_T("0314 国际警察日(节) 马克思逝世纪念日[1883]"),
_T("0315 国际消费者权益日[1983]"),
_T("0316 手拉手情系贫困小伙伴全国统一行动日"),
_T("0317 中国国医节[1929] 国际航海日"),
_T("0317 中国国医节[1929] 国际航海日"),
_T("0318 全国科技人才活动日 巴黎公社纪念日[1871]"),
_T("0321 世界睡眠日[2001] 世界儿歌日 世界森林日(林业节)[1972] 消除种族歧视国际日[1976]"),
//_T("0321 世界儿歌日"),
_T("0322 世界水日[1993] 中国水周(3月22日至3月28日)[1988设/1994改]"),
_T("0323 世界气象日[1950]"),
_T("0324 世界防治结核病日[1996]"),
//_T("0325 全国中小学生安全教育日"),
_T("0330 巴勒斯坦国土日"),
//-
_T("0401 愚人节 全国爱国卫生运动月(四月) 税收宣传月(四月)"),
_T("0402 国际儿童图书日"),
_T("0407 世界卫生日[1950] 1994年卢旺达境内灭绝种族罪行国际反思日[2004]"),
_T("0421 全国企业家活动日[1994]"),
_T("0422 世界地球日[1970] 列宁诞辰纪念日[1870]"),
_T("0423 世界图书和版权日"),
_T("0424 世界青年反对殖民主义日[1957] 亚非新闻工作者日"),
_T("0425 全国预防接种宣传日[1986]"),
_T("0426 世界知识产权日[2001]"),
_T("0427 联谊城日"),
_T("0430 全国交通安全反思日"),
//-
_T("0501 国际劳动节[1889] 国际示威游行日"),
_T("0503 世界哮喘日"),
_T("0504 中国五四青年节[1939] 五四运动纪念日[1919] 科技传播日"),
_T("0505 碘缺乏病防治日[1994] 马克思诞辰纪念日[1818]"),
_T("0508 世界红十字日[1948] 世界微笑日"),
_T("0512 国际护士节[1912]"),
_T("0515 国际家庭(咨询)日[1994]"),
_T("0517 世界电信日[1969]"),
_T("0518 国际博物馆日"),
_T("0520 全国学生营养日[1990] 全国学生营养日[1990]"),
_T("0522 国际生物多样性日[1994设/2001改]"),
//_T("0523 国际牛奶日"),
_T("0526 世界向人体条件挑战日[1993]"),
_T("0529 宋庆龄逝世纪念日[1981]"),
_T("0530 “五卅”反对帝国主义运动纪念日[1925]"),
_T("0531 世界无烟日[1988]"), 
//-
_T("0601 国际儿童节[1949]"),
_T("0605 世界环境日[1974]"),
_T("0606 全国爱眼日[1996]"),
_T("0611 中国人口日"),
_T("0617 防治荒漠化和干旱日[1995]"),
_T("0620 世界难民日[2001]"),
_T("0622 中国儿童慈善活动日"),
_T("0623 国际奥林匹克日[1894] 世界手球日"),
_T("0625 全国土地日[1991]"),
_T("0626 国际反毒品日[1987] 国际宪章日(联合国宪章日)"),
_T("0630 世界青年联欢节"),
//-
_T("0701 中国共产党建党日[1921] 香港回归纪念日[1997] 国际建筑日[1985] 亚洲“三十亿人口日”[1988]"),
_T("0702 国际体育记者日"),
_T("0706 朱德逝世纪念日[1976]"),
_T("0707 中国人民抗日战争纪念日[1937]"),
_T("0711 中国航海日[2005] 世界(50亿)人口日[1987]"),
_T("0720 人类首次成功登月[1969]"),
_T("0726 世界语(言)创立日"),
_T("0728 第一次世界大战爆发[1914]"),
_T("0730 非洲妇女日"),
//-
_T("0801 中国人民解放军建军节[1927]"),
_T("0805 恩格斯逝世纪念日[1895]"),
_T("0806 国际电影节[1932]"),
_T("0808 中国男子节(爸爸节)[1988]"),
_T("0809 世界土著人民国际日[1994]"),
_T("0812 国际青年人日[1999]"),
_T("0813 国际左撇子日[1975设/1976]"),
_T("0815 日本正式宣布无条件投降日[1945] 世界反法西斯战争胜利纪念日[1945]"),
_T("0826 全国律师咨询日[1993]"),
//-
_T("0903 中国抗日战争胜利纪念日[1945]"),
_T("0908 世界扫盲日[1966] 国际新闻工作者(团结)日[1958]"),
_T("0909 毛泽东逝世纪念日[1976]"),
_T("0910 教师节[1985]"),
_T("0914 世界清洁地球日"),
_T("0916 国际臭氧层保护日[1987]"),
_T("0918 九·一八事变纪念日(中国国耻日)[1931]"),
_T("0920 全国公民道德宣传日[2003] 全国爱牙日[1989]"),
_T("0921 国际和平日(全球停火和非暴力日,2002年以后)[2002]"),
_T("0925 鲁迅诞辰纪念日[1881]"),
_T("0926 (曲阜国际)孔子文化节[1989]"),
_T("0927 世界旅游日[1979]"),
//-
_T("1001*国庆节[1949] 国际音乐日[1980] 国际敬老日(老人节)[1991]"),
//_T("1001 国际音乐日"),
_T("1002 国际和平(与民主自由)斗争日[1949]"),
_T("1004 世界动物日[1949]"),
_T("1008 全国高血压日[1998] 狮子会世界视觉日[1998]"),
_T("1009 世界邮政日(万国邮联日)[1969]"),
_T("1010 辛亥革命纪念日[1911] 世界精神卫生日[1992] 世界居室卫生日"),
_T("1011 声援南非政治犯日"),
_T("1012 世界(60亿)人口日[1999]"),
_T("1013 中国少年先锋队建队纪念日[1949] 世界保健日 国际教师节 采用格林威治时间为国际标准时间日[1884]"),
_T("1014 世界标准日[1969]"),
_T("1015 国际盲人节(白手杖节)[1984]"),
_T("1016 世界粮食日[1979]"),
_T("1017 世界消除贫困日[1992]"),
_T("1019 鲁迅逝世纪念日[1936]"),
_T("1022 世界传统医药日[1992]"),
_T("1024 联合国日[1945] 世界发展信息日"),
_T("1028 世界“男性健康日”[2000]"),
_T("1031 世界勤俭日"),
//-
_T("1107 十月社会主义革命纪念日(现俄“和谐和解日”)[1917]"),
_T("1108 中国记者日[2000]"),
_T("1109 全国消防安全宣传教育日[1992]"),
_T("1110 世界青年节[1946]"),
_T("1111 光棍节 国际科学与和平周(本日所属的一周)"),
_T("1112 孙中山诞辰纪念日[1866, 1926定] 刘少奇逝世纪念日[1969]"),
_T("1114 世界糖尿病日[1991]"),
_T("1117 国际大学生节(世界学生节)[1946]"),
_T("1120 世界儿童日[1986]"),
_T("1121 世界问候日[1973] 世界电视日[1996]"),
_T("1124 刘少奇诞辰纪念日[1893]"),
_T("1128 恩格斯诞辰纪念日[1820]"),
_T("1129 国际声援巴勒斯坦人民国际日[1977]"),
//-
_T("1201 世界艾滋病日[1988] 朱德诞辰纪念日[1886]"),
_T("1202 废除一切形式奴役世界日[1986]"),
_T("1203 世界残疾人日[1992]"),
_T("1204 中国法制宣传日[2001]"),
_T("1205 国际经济和社会发展志愿人员日[1985] 世界弱能人士日"),
_T("1207 国际民航日[纪念1994, 1996定]"),
//_T("1208 国际儿童电视日"),
_T("1209 一二·九运动纪念日[1935] 世界足球日[1995]"),
_T("1210 世界人权日(诺贝尔日)[1950]"),
_T("1211 世界防治哮喘日[1998]"),
_T("1212 西安事变纪念日[1936]"),
_T("1213 南京大屠杀纪念日·勿忘国耻,紧记血泪史![1937]"),
_T("1215 世界强化免疫日"),
_T("1220 澳门回归纪念日[1999]"),
_T("1221 国际篮球日 斯大林诞辰纪念日[1879]"),
_T("1224 平安夜"),
_T("1225 圣诞节"),
_T("1226 毛泽东诞辰纪念日[1893]")
//_T("1229 国际生物多样性日")
};


const SStringT CLunarCalendar::m_wFtv[]={
//某月的第几个星期几。 5,6,7,8 表示到数第 1,2,3,4 个星期几
_T("0110 黑人日"),
_T("0150 国际麻风节(世界防治麻风病日)[1954]"), //一月的最后一个星期日（月倒数第一个星期日）
_T("0351 全国中小学生安全教育日[1996]"),
_T("0430 世界儿童日[1986]"),
_T("0453 秘书节"),
_T("0520 国际母亲节[1914] 救助贫困母亲日[1997]"),
_T("0530 全国助残日[1990]"),
_T("0532 国际牛奶日[1961]"),
_T("0630 父亲节"),
_T("0716 国际合作节"),
_T("0911 美国劳动节[1894]"),
_T("0932 国际和平日(1981至2001年)[1981]"),
_T("0936 全民国防教育日[2001]"),
_T("0940 国际聋人节[1958]"),
_T("0950 世界海事日[1978] 世界心脏日[2000]"),
_T("1011 世界人居日(国际住房日)[1985]"),
_T("1013 国际减轻自然灾害日(减灾日)[1990]"),
_T("1144 感恩节"),
_T("1220 国际儿童电视广播日")
};

const SStringT CLunarCalendar::m_lFtv[]={//农历节日
_T("0101*春节"),
_T("0115 元宵节(中国情人节) 壮族歌墟节 朝鲜族上元节 苗族踩山节 达翰尔族卡钦"),
_T("0116 侗族芦笙节(正月十六至二十)"),
//_T("0202 龙抬头节"),
_T("0125 填仓节"),
_T("0129 送穷日"),
_T("0201 瑶族忌鸟节"),
_T("0202 春龙节(龙抬头节) 畲族会亲节"),
_T("0208 傈傈族刀杆节"),
_T("0315 白族三月街(三月十五至廿一)"),
_T("0323 妈祖生辰 (天上圣母诞辰)"),
_T("0408 牛王诞"),
_T("0418 锡伯族西迁节"),
_T("0505 端午节 黎族朝花节 苗族龙船年"),
_T("0513 阿昌族泼水节"),
_T("0522 鄂温克族米阔鲁节"),
_T("0529 瑶族达努节"),
_T("0606 姑姑节 天贶节 壮族祭田节 瑶族尝新节"),
_T("0624 彝族、阿昌族、白族、佤族、纳西族、基诺族火把节"),
_T("0707 七七中国情人节(女儿节, 乞巧节)"),
_T("0713 侗族吃新节"),
_T("0715 中元节 盂兰盆会 普米族转山会"),
_T("0815*中秋节 拉祜族尝新节"),
_T("0909 重阳节 中国老年节(义务助老活动日)[1989]"),
_T("1001 祭祖节(十月朝)"),
_T("1016 瑶族盘王节"),
_T("1208 腊八节"),
_T("1223 北方灶君节[北方小年(扫房日)]"),
_T("1224 南方祭灶节[南方小年(掸尘日)]"),
//_T("1224 小年"),
_T("1200*除夕")
}; 

CLunarCalendar::CLunarCalendar()
{
	Init();
}

CLunarCalendar::~CLunarCalendar()
{

}

SStringT CLunarCalendar::getWordMonth(int m)//得到中文月描述
{
	assert(m>0 && m<=12);
	return m_nStr1[m];
};

SStringT CLunarCalendar::getEnWordMonth(int m)//得到英文月描述
{
	assert(m>0 && m<=12);
	return m_monthName[m-1];
};

void CLunarCalendar::Init()
{
	m_lYear=0; //公元年4位数字
	m_lMonth=0; //农历月数字
	m_lDay=0; //农历日数字
	m_isLeap=FALSE; //是否为农历闰月?

	//八字
	m_cYear=_T(""); //年柱, 2个中文
	m_cMonth=_T(""); //月柱, 2个中文
	m_cDay=_T(""); //日柱, 2个中文
	m_cAnimal=_T(""); //动物属相 

	//节日
	m_lunarFestival=_T(""); //农历节日
	m_solarFestival=_T(""); //公历节日
	m_solarTerms=_T(""); //节气

	m_cYearName=_T(""); //年号纪年表示
	m_cWordDay=_T(""); //文字表示的日
	m_cWordMonth=_T("");//文字表示的月
	m_cMonthSB=_T(""); //月大 小？
}

//返回农历 y年的总天数
int CLunarCalendar::getYearDays(int y)
{
	int i=0, sum = 348;
	for(i=0x8000; i>0x8; i>>=1)
		sum += (m_lunarInfo[y-1900] & i)? 1: 0;
	return(sum+getLeapDays(y));

}
//返回农历 y年闰月的天数
int CLunarCalendar::getLeapDays(int y)
{
	if(getLeapMonth(y))
		return((m_lunarInfo[y-1899]&0xf)==0xf? 30: 29);
	else
		return(0);

}
//返回农历 y年闰哪个月 1-12 , 没闰返回 0
int CLunarCalendar::getLeapMonth(int y)
{
	int lm = m_lunarInfo[y-1900] & 0xf;
	return(lm==0xf?0:lm);

}
//返回农历 y年m月的总天数
int CLunarCalendar::getMonthDays(int y,int m)
{
	return((m_lunarInfo[y-1900] & (0x10000>>m))? 30: 29 );
}

// 传入 offset 返回干支, 0=甲子
// 年柱 1900年立春后为庚子年(60进制36)
//cyclical(SY-1900+36) + '年 【'+Animals[(SY-4)%12]+'年】
SStringT CLunarCalendar::getGZ(LONGLONG num) 
{
	return m_TIANGAN[num%10] + m_DIZHI[num%12];
}
 
/*
31556925974.7为地球公转周期，是毫秒。
如果换算成天，是265.242199天，所以每四百年就有97个闰年，
同样，我们也可以看到，如果这样做的话，一百三十万年后，
我们的公历算法将有一天的误差）

某个小寒点 (1900,0,6,2,5)
*/
int CLunarCalendar::getSTerm(int y,int n)//某年的第n个节气为几日(从0小寒起算)
{ 
	LONGLONG lUtc1=-22085493000000000; //1900,1,6,2,5,0 unit:100ns
	LONGLONG lUtc2=-116444736000000000; //1601,1,1,0,0,0 unit:100ns

	ULONGLONG lDate=315569259747000;
	lDate *= (y-1900);
	lDate += UInt32x32To64(600000000,m_sTermInfo[n]);
	lDate += lUtc1; //100ns--->ms
	lDate -=lUtc2;
	SYSTEMTIME st;
	FileTimeToSystemTime((FILETIME*)&lDate,&st); 
	return st.wDay;
}

void CLunarCalendar::LunarCalendar(CDuiDateTime &tmMeas)//输入阳历日期，返回阴历日期
{
	Init();
	m_tmMeas = tmMeas;
	int i, leap=0, temp=0; 

	int y = m_tmMeas.GetYear();
	int m = m_tmMeas.GetMonth();
	int d = m_tmMeas.GetDay();
	int w = m_tmMeas.GetDayOfWeek();

	assert(y>1899 && y<2101);
	m_cYearName = getYearName(y);
	INT offset=static_cast<int>(getUTC(y,m,d)/864000000000 - getUTC(1900,1,31)/864000000000);
	
	for(i = 1900; i < 2100 && offset >0; i++) 
	{ 
		temp = getYearDays(i); 
		offset -= temp; 
	}

	if(offset < 0) 
	{ 
		offset+=temp;
		i--; 
	}

	m_lYear = i;

	leap = getLeapMonth(i); //闰哪个月
	m_isLeap = FALSE;

	for(i=1; i<13 && offset>0; i++) 
	{
		//闰月
		if(leap>0 && i==(leap+1) && (!m_isLeap))
		{ 
			--i; 
			m_isLeap = TRUE;
			temp = getLeapDays(m_lYear); 
		}
		else
		{ 
			temp = getMonthDays(m_lYear, i);
		}

		//解除闰月
		if(m_isLeap==TRUE && i==(leap+1)) 
			m_isLeap = FALSE;

		offset -= temp;
	}

	if(offset==0 && leap>0 && i==leap+1)
	{
		if(m_isLeap)
		{ 
			m_isLeap = FALSE;
		}
		else
		{
			m_isLeap = TRUE;
			--i;
		}
	}

	if(offset < 0)
	{
		offset += temp;
		--i;
	}
	m_lMonth = i;
	m_cWordMonth = getWordMonth(i);
	m_lDay = offset + 1;
	m_cWordDay = getWordDay(m_lDay);
	m_cMonthSB = ((m_isLeap?getLeapDays(m_lYear):getMonthDays(m_lYear,m_lMonth))>29)?_T("大"):_T("小");


	//////////////////////////////////////////////////////////////////////////
	//初始化 八字

	//36年一循环 
	////////年柱 1900年立春后为庚子年(60进制36)
	m_cAnimal=m_Animals[(m_lYear-4)%12];
	m_cYear=getGZ(m_lYear-1900+36);
	///////月柱 1900年1月小寒以前为 丙子月(60进制12)
	//m_cMonth= getGZ((y-1900)*12+m+12);
	m_cMonth= getGZ((m_lYear-1900)*12+m_lMonth+1+12);

	////////日柱
	//当月一日与 1900/1/1 相差天数
	//1900/1/1与 1970/1/1 相差25567日, 1900/1/1 日柱为甲戌日(60进制10)
	LONGLONG dayCyclical = getUTC(y,m,d)/864000000000+25567+10;
	m_cDay= getGZ(dayCyclical); 

	//////////////////////////////////////////////////////////////////////////
	//初始化 节日
	//公历节气 
	int nMSterm = getSTerm(y, (m-1)*2);
	(void)nMSterm;

	if(d == getSTerm(y,(m-1)*2))
		m_solarTerms = m_solarTerm[(m-1)*2];
	else if(d==getSTerm(y,(m-1)*2+1))
		m_solarTerms = m_solarTerm[(m-1)*2+1];
	else
		m_solarTerms =_T("");

	//公历节日
	m_solarFestival =_T("");
	m_bStrong = FALSE;
	int nFtvM =0, nFtvD =0;
	SStringT strDesc;
	BOOL bStrong;
	int jtjt=sizeof(m_sFtv)/sizeof(m_sFtv[0]);
	(void)jtjt;
	for(i=0; i<sizeof(m_sFtv)/sizeof(m_sFtv[0]); i++)
	{
		parseFtv(m_sFtv[i], nFtvM, nFtvD, strDesc, bStrong);
		if(m == nFtvM && d == nFtvD)
		{
			if(!m_solarFestival.IsEmpty())
				m_solarFestival += _T(" ");
			m_solarFestival += strDesc;
			m_bStrong = bStrong; 
		}
	}

	//月周节日
	int nWeekNo =0, nWeekDay =0; //第几周，星期几
	for(i=0; i<sizeof(m_wFtv)/sizeof(m_wFtv[0]); i++)
	{
		parseFtv(m_wFtv[i],nFtvM,nFtvD,strDesc,bStrong);
		nWeekNo = nFtvD/10;
		nWeekDay = nFtvD%10; //0--星期日
		if((m == nFtvM) && (w-1) == nWeekDay ) 
		{
			if((nWeekNo<6 && (getWeekOfMonth(y,m,d)==nWeekNo)) || (nWeekNo>=6 && ((getWeeksOfMonth(y,m)-getWeekOfMonth(y,m,d)+6)==nWeekNo)))
			{
				if(!m_solarFestival.IsEmpty())
				m_solarFestival += _T(" ");
				m_solarFestival += strDesc;
				m_bStrong = (m_bStrong? TRUE:bStrong); 
			}
		}
	}

	//黑色星期五
	//COleDateTime tmFirst(y,m,13,1,0,0); //13号是不是星期五
	if(d==13 && w==6)
	{
		if(!m_solarFestival.IsEmpty())
			m_solarFestival +=_T(" ");
		m_solarFestival += _T("黑色星期五");;
	}

//复活节只出现在3或4月 复活节日举行此盛会的日子，这个日子是3月21日或其后月满之后的第一个星期天
//if(m==3 || m==4) {
// var estDay = new easter(y);
// if(m == estDay.m)
// ' 复活节 Easter Sunday';
//}


//农历节日
	m_lunarFestival=_T("");
	for(int j=0;j<sizeof(m_lFtv)/sizeof(m_lFtv[0]);j++) 
	{
		parseFtv(m_lFtv[j],nFtvM,nFtvD,strDesc,bStrong);
		if((m_lMonth==nFtvM && m_lDay==nFtvD) || (m_lMonth==nFtvM && nFtvD==0 && (m_isLeap?getLeapDays(m_lYear):getMonthDays(m_lYear,m_lMonth))==m_lDay)) //最后一天，用0标示
		{
			m_lunarFestival=strDesc;
			m_bStrong=(m_bStrong?TRUE:bStrong);
		} 
	}
}

// 计算指定年代与 UTC时间相差的 100ns 数
LONGLONG CLunarCalendar::getUTC(int nYear,int nMonth,int nDay,int nHour,int nMin,int nSec )
{
	//time()获取自1970年1月1日 0点0分0秒 至当前时间经历的秒数，使用了UTC时间。
	//mktime()函数则返回自1970年1月1日 0点0分0秒至传入参数之间经历的秒数。

	CDuiDateTime tmUtc(1970,1,1,0,0,0);
	CDuiDateTime tmBase(nYear,nMonth,nDay,nHour,nMin,nSec);
	SYSTEMTIME stUtc,stBase;
	ULARGE_INTEGER lUtc,lBase;
 
	tmUtc.GetAsSystemTime(stUtc);
	tmBase.GetAsSystemTime(stBase);
	SystemTimeToFileTime(&stUtc,(LPFILETIME)&lUtc);
	SystemTimeToFileTime(&stBase,(LPFILETIME)&lBase);
	LONGLONG lValue=static_cast<LONGLONG>(lBase.QuadPart-lUtc.QuadPart); 
	return lValue;
}

void CLunarCalendar::parseFtv(SStringT strInfo,int& nFirst,int& nLast,SStringT& strDesc,BOOL& bStrong)
{
	SStringT sInfo(strInfo);
	if(sInfo.IsEmpty())
		return;

	SStringT sFirstNum,sLastNum;
	sFirstNum=sInfo.Left(2);
	sLastNum =sInfo.Mid(2,2);
	nFirst   = _ttoi((const wchar_t *)sFirstNum+2);
	nLast=_ttoi((const wchar_t *)sLastNum+2);

	
	SStringT sStrong=sInfo.Mid(4,1);

	if(sStrong==_T("*"))
		bStrong=TRUE;
	else
		bStrong=FALSE;

	strDesc=sInfo.Mid(5);
}

int CLunarCalendar::getWeekOfMonth(int y, int m, int d)
{
	CDuiDateTime tm(y,m,1,1,0,0);
	CDuiDateTime tmCurr(y,m,d,1,0,0);

	int nSpanDays=d-1;
	int nWeekSpan=nSpanDays/7+1;
	int nWeekDay =tm.GetDayOfWeek()+nSpanDays%7;

	if(nWeekDay>7)
	{
		nWeekDay-=7;
		nWeekSpan++;
	}
	return nWeekSpan;
}

int CLunarCalendar::getWeeksOfMonth(int y, int m)
{
	return getWeekOfMonth(y, m, getSunMonthDays(y,m)); 
}

//得到公历月天数
int CLunarCalendar::getSunMonthDays(int y, int m)
{
	//计算当月天数
	int nMonths=0;
	nMonths = m_solarMonth[m-1];
	if(y % 100 != 0 && y % 4 == 0)
	{
		if(m == 2)
		nMonths += 1;
	}
	return nMonths;
}

//中文日
SStringT CLunarCalendar::getWordDay(int d)
{
	SStringT s;
	switch (d) 
	{
		case 10:
			s = _T("初十");
			break;
		case 20:
			s = _T("二十");
			break;
		case 30:
			s = _T("三十");
			break;
		default :
			s = m_nStr2[d/10];
		s += m_nStr1[d%10];
	}
	return s;
}

//年号
SStringT CLunarCalendar::getYearName(int y)
{
	SStringT cYear,cTmp;
	if(y>1874 && y<1909) //光绪
	{
		(y-1874==1)?cTmp=_T("元"):cTmp.Format(_T("%d"),y-1874);
		cYear.Format(_T("光绪%s年"),cTmp);
	}
	else if(y>1908 && y<1912) //宣统
	{
		(y-1908==1)?cTmp=_T("元"):cTmp.Format(_T("%d"),y-1908);
		cYear.Format(_T("宣统%s年"),cTmp);
	}
	else if(y>1911 && y<1950) //民国
	{
		(y-1911==1)?cTmp=_T("元"):cTmp.Format(_T("%d"),y-1911);
		cYear.Format(_T("民国%s年"),cTmp);
	}
	else if(y>1949) //共和国
	{
		(y-1949==1)?cTmp=_T("元"):cTmp.Format(_T("%d"),y-1949);
		cYear.Format(_T("共和国%s年"),cTmp);
	}
	else
		cYear.Format(_T("公元%d年"),y);

	return cYear;
}


} // namespace DuiLib
