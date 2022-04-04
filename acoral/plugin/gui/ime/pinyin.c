/*
	Copyright (C) 2004-2005 Li Yudong
*/
/*
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "../include/common.h"
#include "../include/keyboard_pro.h"
#include "../include/imewin.h"
#include "../include/pinyin.h"



extern ImeDataTable imeDataTable;


typedef struct _CodeTable{
	char* pPinyin;
	char* pHanzi;
} CodeTable;
typedef CodeTable* PCodeTable;

#define MAX_ITEMS	406

CodeTable codeTable[] = {
{"a"			,	"阿啊呵腌嗄锕吖"},
{"ai"			,	"爱哀挨碍埃癌艾唉矮哎皑蔼隘暧霭捱嗳瑷嫒锿嗌砹"},
{"an"		,	"安案按暗岸俺谙黯鞍氨庵桉鹌胺铵揞犴埯"},
{"ang"		,	"昂肮盎"},
{"ao"		,	"奥澳傲熬敖凹袄懊坳嗷拗鏖骜鳌翱岙廒遨獒聱媪螯鏊"},
{"ba"		,	"把八吧巴爸罢拔叭芭霸靶扒疤跋坝笆耙粑灞茇菝魃岜捌钯鲅"},
{"bai"		,	"百白败摆伯拜柏呗掰捭佰稗"},
{"ban"		,	"办半版般班板伴搬扮斑颁瓣拌扳绊阪坂瘢钣舨癍"},
{"bang"		,	"帮邦棒膀榜傍绑磅谤浜梆镑蚌蒡"},
{"bao"		,	"报保包暴宝抱薄胞爆鲍饱堡曝刨褒豹雹苞葆褓孢煲鸨龅趵"},
{"bei"		,	"被北备背悲辈杯倍贝碑卑蓓惫悖狈呗焙鹎孛邶陂埤碚褙鐾鞴萆钡"},
{"ben"		,	"本奔笨苯夯畚贲锛坌"},
{"beng"		,	"崩甭绷蹦迸甏泵嘣蚌"},
{"bi"			,	"比必笔毕币避闭鼻彼逼壁臂弊碧鄙毙蔽庇匕璧敝陛弼篦婢愎痹妣濞铋裨俾髀萆薜哔狴庳秕滗舭毖吡嬖蓖贲畀荸埤筚箅芘襞跸荜"},
{"bian"		,	"编便边变遍辩辨贬鞭辫扁卞砭苄匾汴蝙笾碥窆褊弁鳊忭煸缏"},
{"biao"		,	"表标彪镖膘骠镳裱杓飙瘭髟飚婊飑鳔"},
{"bie"		,	"别憋瘪蹩鳖"},
{"bin"		,	"宾滨彬斌鬓缤殡濒槟摈膑傧玢豳髌镔"},
{"bing"		,	"并病兵冰饼丙柄秉炳禀邴摒"},
{"bo"		,	"波播博伯勃薄拨泊柏剥玻驳卜脖搏膊饽簸掰舶跛礴菠帛铂钵渤檗钹擘箔趵孛鹁踣亳啵"},
{"bu"		,	"不部布步补捕怖卜簿哺埔卟埠钸逋醭晡瓿钚"},
{"ca"		,	"擦嚓礤"},
{"cai"		,	"才采菜财材彩裁猜蔡踩睬"},
{"can"		,	"参餐残惨灿惭掺蚕璨孱骖黪粲"},
{"cang"		,	"藏苍仓沧舱伧"},
{"cao"		,	"草操曹糙嘈槽螬艚漕"},
{"ce"		,	"策测侧厕册恻"},
{"cen"		,	"参岑涔"},
{"ceng"		,	"曾层蹭噌"},
{"cha"		,	"查察差茶插刹叉诧茬碴喳岔嚓衩杈楂槎檫镲搽锸猹馇汊姹"},
{"chai"		,	"差柴拆豺钗侪虿瘥"},
{"chan"		,	"产颤缠禅蝉馋铲搀阐掺潺忏蟾婵谄谗廛孱澶冁躔蒇骣觇镡羼"},
{"chang"		,	"长场常唱厂尝昌肠偿畅倡倘敞怅娼猖嫦伥氅徜昶鲳阊菖苌鬯惝"},
{"chao"		,	"超朝潮炒吵抄嘲钞绰巢晁焯怊耖"},
{"che"		,	"车彻撤扯澈掣坼砗"},
{"chen"		,	"称陈沉晨尘臣趁衬辰郴谶琛忱嗔伧抻谌宸榇龀碜"},
{"cheng"		,	"成城程称承诚盛乘呈撑惩澄秤瞠橙噌逞铛丞骋埕枨塍铖裎酲柽蛏"},
{"chi"		,	"吃持迟尺赤斥池痴齿驰耻翅匙侈哧嗤啻弛蚩炽笞敕叱饬踟鸱褫豉坻墀茌篪傺媸螭彳眵魑瘛"},
{"chong"		,	"重冲充崇虫宠憧忡艟茺舂铳"},
{"chou"		,	"抽愁仇丑筹臭酬绸踌瞅惆畴稠雠俦帱瘳"},
{"chu"		,	"出处除初楚触储础厨畜躇橱雏矗怵锄杵搐绌黜褚蜍蹰刍滁楮憷亍樗"},
{"chuai"		,	"揣啜踹嘬膪搋"},
{"chuan"		,	"传穿川船串喘舛遄舡巛氚椽钏"},
{"chuang"	,	"创窗床闯幢疮怆"},
{"chui"		,	"吹垂炊锤捶陲槌棰"},
{"chun"		,	"春纯唇蠢醇淳椿鹑蝽莼"},
{"chuo"		,	"绰戳啜辍踔龊"},
{"ci"			,	"此次词差刺辞慈磁赐瓷兹茨雌祠疵呲鹚糍茈"},
{"cong"		,	"从匆聪丛葱囱琮淙枞苁骢璁"},
{"cou"		,	"凑楱辏腠"},
{"cu"		,	"促粗簇醋卒猝蹴蹙徂殂蔟酢"},
{"cuan"		,	"攒窜篡蹿撺镩汆爨"},
{"cui"		,	"脆粹催摧崔萃翠瘁悴璀隹淬毳榱啐"},
{"cun"		,	"存村寸忖皴"},
{"cuo"		,	"错措搓挫撮磋蹉矬嵯脞痤瘥鹾厝锉"},
{"da"		,	"大打达答搭瘩嗒沓耷褡鞑笪靼怛妲哒疸"},
{"dai"		,	"代带待戴袋呆贷逮歹殆黛怠玳岱迨傣呔骀绐埭甙"},
{"dan"		,	"但单担弹淡旦蛋胆诞丹耽惮眈啖澹掸殚箪瘅赕疸聃氮萏郸儋"},
{"dang"		,	"当党荡档挡裆铛宕凼菪谠砀"},
{"dao"		,	"到道导倒岛刀悼盗蹈捣祷叨稻忉帱氘纛"},
{"de"		,	"的得德锝"},
{"deng"		,	"等登灯邓凳瞪蹬噔磴戥镫簦嶝"},
{"di"			,	"地第提底低帝弟敌抵递滴迪蒂堤笛缔涤嘀诋谛狄邸睇嫡翟砥娣棣荻羝坻柢觌骶氐绨镝碲籴"},
{"dia"		,	"嗲"},
{"dian"		,	"点电店典颠甸淀垫殿滇奠惦掂碘癫巅踮佃玷簟阽坫靛钿癜丶"},
{"diao"		,	"调掉吊雕刁钓凋叼貂碉铫铞鲷"},
{"die"		,	"爹跌叠迭碟谍蝶喋佚踮牒耋蹀堞瓞揲垤鲽"},
{"ding"		,	"定订顶丁盯钉鼎叮町铤腚酊仃锭疔啶玎碇耵"},
{"diu"		,	"丢铥"},
{"dong"		,	"动东懂冬洞冻董栋咚恫侗氡硐鸫岽垌峒胨胴"},
{"dou"		,	"都斗豆抖逗兜陡窦蔸蚪篼痘"},
{"du"		,	"都读度独毒督渡肚杜睹堵赌妒嘟渎笃牍镀犊黩髑椟芏蠹"},
{"duan"		,	"断段短端锻缎煅椴簖"},
{"dui"		,	"对队堆兑碓憝怼镦"},
{"dun"		,	"顿盾吨敦蹲钝炖遁盹沌囤墩趸镦礅砘"},
{"duo"		,	"多夺朵躲舵堕踱咄跺哆剁惰垛驮掇铎裰哚缍沲柁"},
{"e"			,	"额俄恶饿哦鹅扼愕遏噩娥峨呃厄鄂讹婀蛾轭颚鳄锷谔屙锇阏垩腭苊鹗萼莪"},
{"ei"			,	"诶"},
{"en"		,	"恩摁蒽"},
{"er"		,	"而二儿尔耳迩饵洱鸸珥铒鲕贰佴"},
{"fa"		,	"发法罚乏伐阀砝筏垡珐"},
{"fan"		,	"反饭犯翻范凡烦返番贩繁泛帆藩幡梵樊燔蕃畈钒蘩矾蹯"},
{"fang"		,	"方放房访防仿芳妨纺彷坊肪舫钫鲂邡枋"},
{"fei"		,	"非费飞废肥啡沸菲肺匪诽腓扉吠霏绯妃斐翡蜚痱淝悱鲱篚芾狒镄榧"},
{"fen"		,	"分份纷奋愤粉氛芬坟焚粪忿吩汾棼鼢玢酚偾瀵鲼"},
{"feng"		,	"风封丰峰疯锋逢奉缝凤讽冯蜂枫烽俸砜唪酆葑沣"},
{"fo"		,	"佛"},
{"fou"		,	"否缶"},
{"fu"		,	"夫府服复父负副福富付妇附佛幅伏符赴腐浮扶腹抚覆肤赋弗傅辅拂甫俯斧缚咐脯袱俘敷阜芙釜孚腑匐孵辐涪讣氟桴蜉芾苻茯莩菔幞怫拊滏黼艴麸绂绋趺祓砩黻罘蚨跗蝠呋凫郛稃驸赙馥蝮鲋鳆"},
{"ga"		,	"咖尬嘎噶轧伽旮钆尕尜"},
{"gai"		,	"改该概盖丐钙赅溉垓陔戤"},
{"gan"		,	"感干敢赶甘肝杆尴赣橄竿秆擀坩苷柑泔矸澉疳酐淦绀旰"},
{"gang"		,	"刚港钢岗纲缸扛杠冈肛罡戆筻"},
{"gao"		,	"高告稿搞糕膏皋羔睾槁藁缟篙镐诰槔杲郜锆"},
{"ge"		,	"个革各歌格哥戈隔葛割阁胳搁疙咯鸽嗝骼颌屹搿膈镉纥袼仡鬲塥圪哿舸铬硌虼"},
{"gei"		,	"给"},
{"gen"		,	"根跟亘艮哏茛"},
{"geng"		,	"更耿耕颈庚羹梗哽赓鲠埂绠"},
{"gong"		,	"工公共供功攻宫贡恭巩躬龚弓拱肱汞蚣珙觥"},
{"gou"		,	"够购构狗沟勾苟钩觏篝垢佝岣诟鞲笱枸遘媾缑彀"},
{"gu"		,	"故古顾股鼓姑骨固孤谷估雇辜咕沽箍菇汩轱锢蛊梏鸪毂鹄臌瞽罟钴觚鹘菰蛄嘏诂崮酤牿牯痼鲴"},
{"gua"		,	"挂瓜刮寡呱褂卦剐鸹栝胍诖"},
{"guai"		,	"怪乖拐掴"},
{"guan"		,	"关观管官馆惯冠贯罐灌棺莞倌纶掼盥涫鳏鹳"},
{"guang"		,	"广光逛犷咣胱桄"},
{"gui"		,	"规归贵鬼桂跪柜轨瑰诡刽龟硅闺皈傀癸圭晷簋妫鲑匦庋宄炔刿桧炅鳜"},
{"gun"		,	"滚棍鲧绲磙辊衮"},
{"guo"		,	"国过果锅郭裹帼蝈聒馘掴埚虢呙崞猓椁蜾"},
{"ha"		,	"哈蛤铪"},
{"hai"		,	"还海孩害嘿咳亥骇骸嗨胲醢氦"},
{"han"		,	"汉喊含寒汗韩憾涵函翰撼罕旱捍酣悍憨晗瀚鼾顸阚焊蚶焓颔菡撖邗邯"},
{"hang"		,	"行航巷杭夯沆颃绗珩"},
{"hao"		,	"好号毫豪浩耗皓嚎昊郝壕蒿貉灏镐嗥嚆薅濠蚝颢"},
{"he"		,	"和何合河喝赫核吓贺盒呵禾荷鹤壑阂褐诃涸阖嗬貉曷颌劾盍纥蚵翮菏"},
{"hei"		,	"黑嘿嗨"},
{"hen"		,	"很恨狠痕"},
{"heng"		,	"横衡恒哼亨蘅珩桁"},
{"hong"		,	"红轰洪鸿哄宏虹弘烘泓闳薨讧蕻訇黉荭"},
{"hou"		,	"后候後厚侯喉吼猴逅糇骺堠瘊篌鲎"},
{"hu"		,	"乎护呼胡户湖忽互糊虎壶狐沪惚浒唬葫弧蝴囫瑚斛祜猢鹄醐戽扈唿笏琥滹鹕轷烀冱岵怙鹘槲觳瓠鹱煳"},
{"hua"		,	"话华化花划画滑哗桦猾砉铧骅"},
{"huai"		,	"怀坏徊淮槐踝"},
{"huan"		,	"欢换还环缓患幻唤宦焕痪寰鬟涣浣奂桓缳豢锾郇萑圜洹擐獾漶逭鲩"},
{"huang"		,	"黄皇荒晃慌煌惶恍谎璜徨簧凰幌潢蝗蟥遑隍肓磺癀湟篁鳇"},
{"hui"		,	"会回汇挥辉灰惠毁悔恢慧绘徽讳贿徊晦秽诲诙晖彗麾烩荟卉茴喙蛔恚洄珲蕙哕咴浍虺缋桧隳蟪"},
{"hun"		,	"婚混魂昏浑馄荤诨溷阍珲"},
{"huo"		,	"和或活火获货伙祸惑霍豁夥锪耠劐钬攉藿嚯镬蠖"},
{"ji"			,	"几给己机记及计即基济辑级极寄际技集纪击奇急激继既积籍鸡吉挤迹季寂绩疾饥祭缉忌剂圾姬矶肌嫉讥藉叽脊冀稽妓棘骥畸蓟汲悸岌伎笈跻瘠亟诘暨霁羁稷偈戟嵇楫唧鲫髻荠箕觊蒺畿虮齑殛墼佶掎芨丌麂蕺咭嵴芰笄哜洎乩戢屐剞跽玑鲚赍犄"},
{"jia"		,	"家加价假架甲佳驾夹嫁嘉贾稼茄佼挟颊皎侥枷珈戛迦伽浃痂胛笳荚葭钾镓嘏郏挢岬徼湫敫袈瘕恝铗袷蛱跏"},
{"jian"		,	"见间件建简坚监减渐检健兼剑艰肩键荐尖鉴剪践奸捡箭舰拣贱溅煎俭槛碱歼缄茧笺柬谏蹇僭涧菅謇硷睑锏饯毽鲣鞯蒹搛谫囝湔缣枧戬戋犍裥笕翦趼楗牮鹣腱踺"},
{"jiang"		,	"将讲奖降蒋疆酱姜浆僵匠犟缰绛桨耩礓洚豇茳糨"},
{"jiao"		,	"教交觉校叫较角脚焦骄郊轿搅嚼胶缴绞饺椒矫娇佼狡浇跤姣窖剿侥皎蕉酵礁鲛徼湫敫僬鹪峤蛟铰艽茭挢噍醮"},
{"jie"		,	"界解接结节街姐阶介借戒杰届皆捷截洁揭劫竭藉睫诫嗟拮孑碣秸诘桀芥偈颉讦疖疥婕羯鲒蚧骱喈"},
{"jin"		,	"进今金近尽仅紧禁劲津斤谨锦筋晋巾浸襟瑾矜靳缙烬噤觐馑堇衿荩廑妗卺赆槿"},
{"jing"		,	"经京精境警竟静惊景敬睛镜竞净井径晶荆兢颈憬靖鲸泾阱儆旌痉迳茎胫腈菁粳獍肼弪婧刭靓"},
{"jiong"		,	"窘炯迥扃炅"},
{"jiu"		,	"就九究酒久旧救纠揪疚舅韭赳鸠灸咎啾臼鹫阄僦厩玖柩桕鬏"},
{"ju"		,	"局据居句举具剧巨聚拒俱距惧菊拘矩桔驹鞠咀沮瞿锯炬飓趄掬踽踞遽橘倨疽龃屦犋裾钜苴雎鞫椐讵苣锔狙榘莒枸榉窭醵琚"},
{"juan"		,	"捐卷倦眷娟隽绢鹃涓镌锩鄄狷桊蠲"},
{"jue"		,	"觉绝决脚嚼掘诀崛爵抉倔獗嗟厥蹶攫谲矍撅噱孓橛噘珏桷劂爝镢蕨觖"},
{"jun"		,	"军均君俊峻钧隽筠菌郡骏竣麇皲捃浚"},
{"ka"		,	"卡咖喀咔佧胩"},
{"kai"		,	"开慨凯铠揩楷恺垲蒈锎剀锴忾"},
{"kan"		,	"看刊侃堪砍坎槛勘瞰龛阚莰戡"},
{"kang"		,	"抗康慷扛炕亢糠伉闶钪"},
{"kao"		,	"考靠铐烤拷犒栲尻"},
{"ke"		,	"可克科客刻课颗渴柯呵棵恪咳苛磕壳坷嗑瞌轲稞疴蝌溘髁钶窠颏珂岢骒缂氪锞蚵"},
{"ken"		,	"肯恳啃垦龈裉"},
{"keng"		,	"坑吭铿"},
{"kong"		,	"空恐控孔倥崆箜"},
{"kou"		,	"口扣抠寇叩蔻眍芤筘"},
{"ku"		,	"苦哭库裤酷枯窟骷刳堀喾绔"},
{"kua"		,	"夸跨垮挎胯侉"},
{"kuai"		,	"会快块筷脍蒯哙侩狯浍郐"},
{"kuan"		,	"款宽髋"},
{"kuang"		,	"况狂矿框旷眶筐匡哐邝诓夼诳圹纩贶"},
{"kui"		,	"亏愧溃窥魁馈睽盔逵葵奎匮傀喟聩岿馗夔篑喹悝暌隗蒉蝰愦揆跬"},
{"kun"		,	"困昆捆坤鲲悃髡锟醌阃琨"},
{"kuo"		,	"括阔扩廓栝蛞"},
{"la"			,	"拉啦辣腊喇垃蜡剌邋旯瘌砬"},
{"lai"		,	"来赖莱睐癞籁徕涞赉铼崃濑"},
{"lan"		,	"兰蓝栏烂懒览滥拦篮揽澜榄婪缆斓岚阑褴镧罱谰漤"},
{"lang"		,	"浪狼朗郎廊琅螂榔啷莨锒稂阆蒗"},
{"lao"		,	"老劳牢捞姥佬潦唠烙酪涝崂痨醪铹栳铑耢"},
{"le"			,	"了乐勒肋叻泐鳓仂"},
{"lei"		,	"类泪累雷蕾垒磊擂肋儡羸诔镭嘞檑嫘缧酹耒"},
{"leng"		,	"冷愣楞棱塄"},
{"li"			,	"里理力利立李历离例礼丽励黎厉璃莉哩笠粒俐漓栗狸梨隶吏沥篱厘犁雳罹莅戾鲤俚砺藜俪蜊黧郦痢枥逦娌詈骊荔鳢喱鹂嫠蠡鬲鲡悝坜苈砾藓呖唳猁溧澧栎轹蓠傈缡疠疬蛎锂篥粝跞醴"},
{"lia"		,	"俩"},
{"lian"		,	"联连脸练恋怜莲廉炼帘链敛涟镰殓琏楝裢裣蠊鲢濂臁潋蔹奁"},
{"liang"		,	"两量良亮辆梁俩凉粮谅粱晾踉莨墚魉椋靓"},
{"liao"		,	"了料聊疗辽僚廖寥镣潦撩撂缭燎寮嘹钌獠鹩蓼尥"},
{"lie"		,	"列烈裂劣猎咧趔冽洌捩埒躐鬣"},
{"lin"		,	"林临邻琳淋霖麟凛吝鳞磷躏赁嶙辚檩遴粼蔺懔瞵啉膦廪"},
{"ling"		,	"领令另灵零龄凌玲铃陵岭拎伶聆囹棱菱翎苓瓴棂绫呤柃鲮酃泠羚蛉"},
{"liu"		,	"六留流陆刘溜柳碌瘤榴浏硫琉遛馏镏骝绺锍旒熘鎏鹨"},
{"long"		,	"龙隆笼胧拢咙聋垄珑窿陇癃茏栊泷垅砻"},
{"lou"		,	"楼陋漏搂喽篓偻娄髅蝼镂蒌嵝耧瘘"},
{"lu"			,	"路陆录卢露鲁炉鹿碌庐芦噜颅禄辘卤虏麓泸赂漉戮簏轳鹭掳潞鲈撸栌垆胪蓼渌鸬逯璐辂橹镥舻氇"},
{"lv"			,	"律旅绿率虑履屡侣缕驴吕榈滤捋铝褛闾膂氯稆"},
{"luan"		,	"乱卵峦挛孪栾銮娈滦鸾脔"},
{"lue"		,	"略掠锊"},
{"lun"		,	"论轮伦沦仑抡囵纶"},
{"luo"		,	"落罗络洛逻裸骆萝螺锣箩摞烙捋珞骡猡镙椤倮蠃荦瘰泺漯脶硌雒"},
{"m"		,	"呒"},
{"ma"		,	"马吗妈码麻骂嘛抹玛蚂蟆唛杩犸嬷"},
{"mai"		,	"买卖麦埋迈脉霾劢荬"},
{"man"		,	"满慢漫曼蛮馒瞒蔓颟谩墁幔螨鞔鳗缦熳镘"},
{"mang"		,	"忙茫盲芒氓莽蟒邙漭硭"},
{"mao"		,	"毛冒猫贸矛帽貌茅茂髦卯耄瑁锚懋袤铆峁牦蟊泖昴茆旄蝥瞀"},
{"me"		,	"么麽"},
{"mei"		,	"没美每妹眉梅媒枚魅煤昧霉玫媚寐糜袂酶莓嵋楣湄猸镅浼鹛镁"},
{"men"		,	"们门闷扪懑焖钔"},
{"meng"		,	"梦蒙猛盟朦孟萌勐懵檬蠓瞢甍礞蜢虻艋艨锰"},
{"mi"		,	"密米秘迷弥谜觅眯蜜靡咪谧泌糜汨宓麋醚弭敉芈祢脒幂縻嘧蘼猕糸"},
{"mian"		,	"面免棉眠缅绵勉腼冕娩湎沔眄黾渑"},
{"miao"		,	"妙描秒庙苗渺瞄藐缪淼缈喵眇邈鹋杪"},
{"mie"		,	"灭蔑篾咩乜蠛"},
{"min"		,	"民敏悯闽泯珉皿抿闵苠岷缗玟愍黾鳘"},
{"ming"		,	"名明命鸣铭冥茗溟酩瞑暝螟"},
{"miu"		,	"谬缪"},
{"mo"		,	"默莫模麽末磨摸摩寞漠墨抹魔陌嘿沫膜蓦蘑茉馍摹貉谟嫫秣镆殁瘼耱貊貘"},
{"mou"		,	"某谋眸缪鍪哞侔蛑"},
{"mu"		,	"目母木幕姆慕牧墓募暮牟亩穆睦拇沐牡仫坶苜毪钼"},
{"n"			,	"嗯唔"},
{"na"		,	"那拿呢哪纳娜呐捺钠镎肭衲"},
{"nai"		,	"乃奶奈耐氖艿鼐佴萘柰"},
{"nan"		,	"难南男楠喃囡囝腩蝻赧"},
{"nang"		,	"囊囔馕攮曩"},
{"nao"		,	"脑闹恼挠瑙淖呶猱铙孬硇蛲垴"},
{"ne"		,	"呢讷"},
{"nei"		,	"内馁"},
{"nen"		,	"嫩恁"},
{"neng"		,	"能"},
{"ng"		,	"嗯唔"},
{"ni"			,	"你呢尼泥逆倪匿拟腻妮霓昵溺旎睨鲵坭猊怩伲祢慝铌"},
{"nian"		,	"年念廿粘碾捻蔫撵拈黏鲶鲇辇埝"},
{"niang"		,	"娘酿"},
{"niao"		,	"鸟尿袅嬲茑脲"},
{"nie"		,	"捏涅聂孽蹑嗫啮镊镍乜陧颞臬蘖"},
{"nin"		,	"您恁"},
{"ning"		,	"宁凝拧泞咛狞柠佞聍苎甯"},
{"niu"		,	"牛纽扭妞钮拗忸狃"},
{"nong"		,	"农弄浓侬哝脓"},
{"nou"		,	"耨"},
{"nu"		,	"怒努奴弩驽胬孥"},
{"nv"		,	"女钕恧衄"},
{"nuan"		,	"暖"},
{"nue"		,	"虐疟"},
{"nuo"		,	"诺挪懦糯喏搦傩锘"},
{"o"			,	"哦噢喔"},
{"ou"		,	"欧偶殴呕鸥讴瓯藕沤耦怄"},
{"pa"		,	"怕爬帕扒趴啪琶葩耙杷钯筢"},
{"pai"		,	"派排牌拍徘湃俳蒎哌"},
{"pan"		,	"判盘盼叛畔潘攀拚蹒磐爿蟠襻袢泮"},
{"pang"		,	"旁庞胖乓膀磅彷螃滂耪逄"},
{"pao"		,	"跑炮抛泡袍刨咆狍疱脬庖匏"},
{"pei"		,	"配陪培佩赔沛裴呸胚醅锫辔帔旆霈"},
{"pen"		,	"盆喷湓"},
{"peng"		,	"朋鹏碰彭捧棚蓬膨烹抨篷砰澎怦堋蟛嘭硼"},
{"pi"			,	"批否皮屁披疲辟啤脾匹僻劈譬坯痞癖琵毗霹噼媲郫裨纰丕鼙圮蚍蜱貔陂陴砒仳埤擗吡庀邳疋芘枇罴淠铍甓睥"},
{"pian"		,	"便片篇偏骗翩扁犏谝蹁骈缏胼"},
{"piao"		,	"票漂飘瓢嫖瞟骠嘌剽螵缥莩殍"},
{"pie"		,	"撇瞥氕丿苤"},
{"pin"		,	"品贫拼频聘拚姘嫔榀颦牝"},
{"ping"		,	"平评瓶凭萍乒屏苹坪枰娉俜鲆"},
{"po"		,	"破迫颇婆坡泊泼魄粕珀叵攴钷笸钋陂泺鄱皤"},
{"pou"		,	"剖裒掊"},
{"pu"		,	"普铺扑朴谱浦葡蒲仆脯瀑菩溥匍璞噗圃埔氆镨蹼镤濮莆"},
{"qi"			,	"起其期气七奇妻企器汽棋齐旗弃启骑欺歧岂戚凄泣契琪乞祈漆迄脐栖沏祺崎祁琦蹊砌憩淇汔亟绮讫嘁岐萋俟杞芪荠耆槭颀芑屺欹桤綮萁蛴蜞綦鳍麒蕲柒亓骐葺畦圻碛"},
{"qia"		,	"恰洽掐伽袷葜髂"},
{"qian"		,	"前钱千签欠牵浅潜迁谦遣歉纤嵌乾谴铅虔钳骞倩堑黔掮悭芊缱愆荨芡阡佥搴褰肷钎仟犍钤岍箝鬈扦慊椠"},
{"qiang"		,	"强枪墙抢腔呛锵跄羌蔷戕襁樯炝蜣嫱锖戗羟镪"},
{"qiao"		,	"桥悄乔巧侨瞧敲翘俏窍峭锹撬跷憔樵鞘橇诮愀谯荞峤缲硗鞒劁"},
{"qie"		,	"切且窃怯茄趄妾砌惬伽锲挈郄箧慊"},
{"qin"		,	"亲钦琴侵秦勤芹擒寝覃沁禽噙揿檎锓芩嗪螓衾廑溱吣"},
{"qing"		,	"情请青清轻晴庆倾卿擎顷氢罄蜻磬謦苘圊檠黥鲭氰箐綮"},
{"qiong"		,	"穷琼穹茕邛蛩筇跫銎"},
{"qiu"		,	"求球秋邱囚丘酋蚯裘俅虬鳅逑遒赇泅楸犰湫蝤巯鼽糗"},
{"qu"		,	"去取区曲趣屈趋驱渠躯娶觑瞿岖戌蛐衢蛆癯麴阒祛磲鸲诎蠼劬蕖蘧龋苣黢璩氍朐"},
{"quan"		,	"全权圈劝泉券拳犬诠颧蜷绻荃铨痊鬈辁悛畎醛筌"},
{"que"		,	"却确缺雀瘸榷鹊阕阙炔悫"},
{"qun"		,	"群裙逡麇"},
{"ran"		,	"然染燃冉髯苒蚺"},
{"rang"		,	"让嚷攘壤瓤穰禳"},
{"rao"		,	"扰绕饶娆桡荛"},
{"re"		,	"热惹喏"},
{"ren"		,	"人任认忍仁韧刃纫饪壬仞稔葚荏妊轫衽"},
{"reng"		,	"仍扔"},
{"ri"			,	"日"},
{"rong"		,	"容荣融蓉溶绒熔榕戎嵘茸冗肜蝾狨"},
{"rou"		,	"肉柔揉蹂鞣糅"},
{"ru"		,	"如入辱儒乳汝褥嚅茹濡蠕孺缛襦颥薷蓐洳溽铷"},
{"ruan"		,	"软阮朊"},
{"rui"		,	"瑞锐芮睿蕤枘蕊蚋"},
{"run"		,	"润闰"},
{"ruo"		,	"若弱偌箬"},
{"sa"		,	"洒撒萨卅仨飒挲脎"},
{"sai"		,	"赛塞腮噻鳃"},
{"san"		,	"三散伞叁毵馓糁霰"},
{"sang"		,	"丧桑嗓搡磉颡"},
{"sao"		,	"扫骚嫂梢臊搔缲缫鳋埽瘙"},
{"se"		,	"色塞涩瑟啬铯穑"},
{"sen"		,	"森"},
{"seng"		,	"僧"},
{"sha"		,	"杀沙啥傻厦刹纱莎煞砂霎嗄挲歃鲨唼痧裟铩"},
{"shai"		,	"晒筛酾"},
{"shan"		,	"山善闪衫删煽扇陕珊杉擅掺膳栅讪跚汕姗赡潸缮嬗掸膻骟芟埏剡钐鄯舢苫髟疝蟮鳝"},
{"shang"		,	"上商伤尚赏殇裳晌觞熵墒绱垧"},
{"shao"		,	"少绍烧稍勺哨邵梢捎韶苕鞘潲劭杓芍蛸筲艄"},
{"she"		,	"社设舍涉射摄舌蛇奢赦慑佘赊麝畲厍滠歙猞"},
{"shei"		,	"谁"},
{"shen"		,	"什身深神参甚申审沈伸慎渗绅肾呻婶莘蜃葚娠渖矧诜砷糁谂椹胂哂"},
{"sheng"		,	"生声省胜升圣盛剩牲绳甥笙渑眚嵊晟"},
{"shi"		,	"是时十事实使世市识始士师诗式失史视示食室势试石释施适氏驶饰尸拾逝湿誓狮嗜蚀嘘屎侍匙峙仕恃柿轼矢噬拭虱弑蓍埘莳炻谥鲥豕贳铈螫舐筮鲺酾"},
{"shou"		,	"手受收首授守售瘦寿兽狩绶艏"},
{"shu"		,	"书数术属输树述熟束署殊舒叔鼠疏淑抒薯梳暑竖蜀恕墅孰漱枢俞赎黍蔬曙倏庶戍塾澍姝纾秫毹殳疋菽丨沭摅腧"},
{"shua"		,	"刷耍唰"},
{"shuai"		,	"率衰摔甩帅蟀"},
{"shuan"		,	"涮栓拴闩"},
{"shuang"	,	"双爽霜孀泷"},
{"shui"		,	"水谁税睡"},
{"shun"		,	"顺舜瞬吮"},
{"shuo"		,	"说朔硕烁铄妁蒴槊搠"},
{"si"			,	"四死思斯司似私丝寺撕肆厮嘶伺饲嗣祀巳驷鸶俟汜泗厶兕蛳咝姒澌缌耜笥锶"},
{"song"		,	"送松宋诵耸颂讼悚怂忪淞菘崧嵩凇竦"},
{"sou"		,	"搜艘嗽擞馊薮嗾叟嗖溲飕锼瞍螋"},
{"su"		,	"苏诉速素俗肃宿塑稣溯酥粟簌夙嗉谡僳愫涑蔌觫"},
{"suan"		,	"算酸蒜狻"},
{"sui"		,	"岁随虽碎遂祟隧髓邃穗隋绥睢荽燧谇眭濉"},
{"sun"		,	"孙损笋荪狲飧榫隼"},
{"suo"		,	"所索缩锁琐梭嗦唆挲娑睃唢嗍蓑羧桫"},
{"ta"		,	"他她它踏塔塌榻嗒蹋沓遢挞鳎闼铊趿漯溻獭"},
{"tai"		,	"太台态泰抬胎汰苔呔鲐邰薹酞骀炱跆肽钛"},
{"tan"		,	"谈探弹坦叹坛摊贪滩毯谭潭瘫炭覃痰忐坍袒碳澹檀昙镡郯锬钽"},
{"tang"		,	"堂唐汤躺糖趟倘烫淌膛塘棠搪溏螳瑭樘螗铴醣镗耥饧傥帑羰"},
{"tao"		,	"讨套逃涛掏陶桃淘滔萄焘啕韬饕洮绦鼗"},
{"te"		,	"特忑忒慝铽"},
{"tei"		,	"忒"},
{"teng"		,	"腾疼藤誊滕"},
{"ti"			,	"体提题替踢梯啼涕蹄剔剃惕屉嚏悌醍缇鹈锑荑倜绨逖裼"},
{"tian"		,	"天田填甜添腆舔恬钿阗畋忝殄掭"},
{"tiao"		,	"条调跳挑迢眺鲦佻苕窕髫粜笤龆祧蜩"},
{"tie"		,	"铁贴帖餮萜"},
{"ting"		,	"听停庭厅挺亭婷廷艇町霆汀铤蜓莛梃葶烃"},
{"tong"		,	"同通统痛童彤筒铜桶捅桐瞳佟恸酮恫侗砼嗵仝垌茼峒潼"},
{"tou"		,	"头投偷透钭骰"},
{"tu"		,	"土突图途徒屠涂吐兔秃凸荼酴钍菟堍"},
{"tuan"		,	"团湍抟疃彖"},
{"tui"		,	"推退腿褪颓蜕忒煺"},
{"tun"		,	"吞屯饨褪臀囤豚暾氽"},
{"tuo"		,	"托脱拖妥拓陀驼唾椭砣驮沱跎坨鸵乇鼍橐佗庹铊酡柁柝箨"},
{"wa"		,	"瓦挖袜娃哇凹娲蛙洼佤腽"},
{"wai"		,	"外歪崴"},
{"wan"		,	"万完晚湾玩碗弯挽顽腕婉惋宛丸蜿莞畹剜豌皖纨琬脘烷芄菀绾"},
{"wang"		,	"望王往网忘亡汪旺枉妄惘罔尢辋魍"},
{"wei"		,	"为位未委维味围卫威微伟谓唯危慰尾违魏玮蔚伪畏胃喂炜韦惟巍纬萎娓苇尉帷渭猥偎薇痿猬逶帏韪煨鲔桅潍隈圩囗诿隗崴洧葳嵬闱沩涠艉軎"},
{"wen"		,	"文问闻温稳吻纹蚊雯紊瘟汶刎阌璺"},
{"weng"		,	"翁瓮嗡蓊蕹"},
{"wo"		,	"我握窝卧渥沃涡斡蜗幄喔倭挝莴肟硪龌"},
{"wu"		,	"无五物务武午舞於误恶吴屋伍悟吾污乌雾侮捂巫毋呜诬勿梧坞戊兀唔晤芜鹜钨妩痦鹉忤寤骛邬牾鼯圬浯仵阢芴庑婺怃杌焐蜈迕鋈"},
{"xi"			,	"西系息希喜席习细戏吸洗惜稀悉析夕牺袭昔熙兮溪隙嘻锡晰媳樨熄膝郗犀禧曦奚羲蹊唏淅嬉皙汐徙茜玺熹烯翕蟋屣檄浠僖穸蜥隰觋螅铣菥葸蓰舾矽粞硒醯欷鼷歙饩阋禊舄"},
{"xia"		,	"下夏吓峡厦侠狭霞瞎暇虾唬辖遐匣黠瑕呷狎柙硖瘕罅"},
{"xian"		,	"现先显线险限县鲜献闲宪陷贤仙嫌咸羡掀弦纤娴衔馅涎舷腺跣暹岘猃蚬筅跹莶锨鹇痫铣氙祆籼冼藓酰苋燹霰"},
{"xiang"		,	"想相向象香乡像响项享降箱详祥巷厢湘橡翔镶飨襄饷骧葙庠鲞芗缃蟓"},
{"xiao"		,	"小笑校消效晓销潇肖萧孝宵削嚣啸逍硝霄淆哮枭骁箫筱哓枵绡魈蛸崤"},
{"xie"		,	"些写谢协鞋携斜泄胁歇谐邪械屑卸挟懈泻亵蟹偕邂榭撷楔瀣蝎颉勰薤燮躞缬獬绁廨榍渫"},
{"xin"		,	"心新信欣辛薪馨鑫芯衅昕忻锌歆镡囟"},
{"xing"		,	"行性形兴星型姓幸刑醒腥杏悻惺邢猩荇擤荥饧硎陉"},
{"xiong"		,	"雄兄胸凶熊匈汹芎"},
{"xiu"		,	"修休秀袖宿臭羞绣朽锈嗅咻貅髹馐庥鸺岫溴"},
{"xu"		,	"许续需须徐序虚绪吁蓄叙畜嘘恤絮浒墟旭婿栩戌诩胥酗煦砉盱糈醑顼勖洫溆圩蓿"},
{"xuan"		,	"选宣旋悬券喧轩玄炫渲绚眩萱漩暄璇谖铉儇痃泫煊楦癣碹揎镟"},
{"xue"		,	"学血雪削穴谑靴薛踅噱泶鳕"},
{"xun"		,	"寻询训迅讯巡逊循旬熏勋驯荤殉醺巽徇埙荀峋洵薰汛郇曛窨恂獯浔鲟蕈浚"},
{"ya"		,	"亚压雅牙呀押涯讶鸦哑鸭崖丫芽衙轧痖睚娅蚜伢疋岈琊垭揠迓桠氩砑"},
{"yan"		,	"眼言严演研烟验延沿掩颜厌炎燕阎宴盐咽岩雁焰艳焉淹衍阉奄谚俨檐蜒彦腌焱晏唁妍砚嫣胭湮筵堰赝餍鼹芫偃魇闫崦厣剡恹阏兖郾琰罨鄢谳滟阽鼽酽菸"},
{"yang"		,	"样洋阳央杨养扬仰羊痒漾泱氧鸯秧殃恙疡烊佯鞅怏徉炀蛘"},
{"yao"		,	"要摇药耀遥邀腰姚咬尧谣瑶窑夭肴妖吆钥侥杳窈鹞曜舀铫幺爻徭繇鳐珧轺崾"},
{"ye"		,	"也业夜爷叶野页液耶咽曳拽揶噎烨冶椰掖腋谒邺靥晔铘"},
{"yi"			,	"一以意已义议医易衣艺依译移异益亦亿疑遗忆宜椅伊仪谊抑翼矣役艾乙溢毅蛇裔逸姨夷轶怡蚁弈倚翌颐疫绎彝咦佚奕熠贻漪诣迤弋懿呓驿咿揖旖屹痍薏噫镒刈沂臆缢邑胰猗羿钇舣劓仡酏佾埸诒圯荑壹挹嶷饴嗌峄怿悒铱欹殪黟苡肄镱瘗癔翊蜴眙翳"},
{"yin"		,	"因音引印银隐饮阴姻瘾吟寅殷淫茵荫尹蚓垠喑湮胤鄞氤霪圻铟狺吲夤堙龈洇茚窨"},
{"ying"		,	"应英影营迎硬映赢盈颖鹰婴蝇樱莹荧膺萤萦莺罂瀛楹缨颍嬴鹦瑛茔嘤璎荥撄郢瘿蓥滢潆媵"},
{"yo"		,	"哟唷"},
{"yong"		,	"用永拥勇涌踊泳庸佣咏俑雍恿甬臃邕镛痈壅鳙饔喁墉蛹慵"},
{"you"		,	"有又由友游右油优邮幽尤忧犹悠幼诱佑黝攸呦酉柚鱿莠囿鼬铀卣猷牖铕疣蚰蝣釉蝤繇莜侑莸宥蚴尢"},
{"yu"		,	"于与语育余遇狱雨於欲预予鱼玉愈域誉吁宇寓豫愚舆粥郁喻羽娱裕愉禹浴馀御逾渔渝俞萸瑜隅驭迂揄圄谕榆屿淤毓虞禺谀妪腴峪竽芋妤臾欤龉觎盂昱煜熨燠窬蝓嵛狳伛俣舁圉庾菀蓣饫阈鬻瘐窳雩瘀纡聿钰鹆鹬蜮"},
{"yuan"		,	"员元原院远愿园源圆怨缘援冤袁渊苑猿鸳辕垣媛沅橼芫爰螈鼋眢圜鸢箢塬垸掾瑗"},
{"yue"		,	"月乐越约阅跃曰悦岳粤钥刖瀹栎樾龠钺"},
{"yun"		,	"运云允韵晕孕匀蕴酝筠芸耘陨纭殒愠氲狁熨郓恽昀韫郧"},
{"za"		,	"杂扎砸咋咂匝拶"},
{"zai"		,	"在再载灾仔宰哉栽崽甾"},
{"zan"		,	"咱赞暂攒簪糌瓒拶昝趱錾"},
{"zang"		,	"藏脏葬赃臧锗奘驵"},
{"zao"		,	"早造遭糟澡灶躁噪凿枣皂燥蚤藻缲唣"},
{"ze"		,	"则责泽择咋啧仄迮笮箦舴帻赜昃"},
{"zei"		,	"贼"},
{"zen"		,	"怎谮"},
{"zeng"		,	"增赠憎缯罾甑锃"},
{"zha"		,	"炸扎咋诈乍眨渣札栅轧闸榨喳揸柞楂哳吒铡砟齄咤痄蚱"},
{"zhai"		,	"摘债宅窄斋寨翟砦瘵"},
{"zhan"		,	"战展站占沾斩辗粘盏崭瞻绽蘸湛詹毡栈谵搌旃"},
{"zhang"		,	"长张章丈掌涨帐障账胀仗杖彰璋蟑樟瘴漳嶂鄣獐仉幛嫜"},
{"zhao"		,	"着找照招朝赵召罩兆昭肇沼诏钊啁棹笊"},
{"zhe"		,	"这着者折哲浙遮辙辄谪蔗蛰褶鹧锗磔摺蜇赭柘"},
{"zhen"		,	"真阵镇震针珍圳振诊枕斟贞侦赈甄臻箴疹砧桢缜畛轸胗稹祯浈溱蓁椹榛朕鸩"},
{"zheng"		,	"政正证整争征挣郑症睁徵蒸怔筝拯铮峥狰诤鲭钲帧"},
{"zhi"		,	"之只知至制直治指支志职致值织纸止质执智置址枝秩植旨滞徵帜稚挚汁掷殖芝吱肢脂峙侄窒蜘趾炙痔咫芷栉枳踯桎帙栀祉轾贽痣豸卮轵埴陟郅黹忮彘骘酯摭絷跖膣雉鸷胝蛭踬祗觯"},
{"zhong"		,	"中种重众终钟忠衷肿仲锺踵盅冢忪舯螽"},
{"zhou"		,	"周州洲粥舟皱骤轴宙咒昼肘帚胄纣诌绉妯碡啁荮籀繇酎"},
{"zhu"		,	"主住注助著逐诸朱驻珠祝猪筑竹煮嘱柱烛铸株瞩蛛伫拄贮洙诛褚铢箸蛀茱炷躅竺杼翥渚潴麈槠橥苎侏瘃疰邾舳"},
{"zhua"		,	"抓爪"},
{"zhuai"		,	"拽嘬"},
{"zhuan"		,	"传专转赚撰砖篆啭馔颛"},
{"zhuang"	,	"装状壮庄撞妆幢桩奘僮戆"},
{"zhui"		,	"追坠缀锥赘隹椎惴骓缒"},
{"zhun"		,	"准谆窀肫"},
{"zhuo"		,	"着桌捉卓琢灼酌拙浊濯茁啄斫镯涿焯浞倬禚诼擢"},
{"zi"			,	"子自字资咨紫滋仔姿吱兹孜梓渍籽姊恣滓谘龇秭呲辎锱眦笫髭淄茈觜訾缁耔鲻嵫赀孳粢趑"},
{"zong"		,	"总宗纵踪综棕粽鬃偬腙枞"},
{"zou"		,	"走奏邹揍驺鲰诹陬鄹"},
{"zu"		,	"组足族祖租阻卒诅俎镞菹"},
{"zuan"		,	"赚钻攥纂躜缵"},
{"zui"		,	"最罪嘴醉咀觜蕞"},
{"zun"		,	"尊遵樽鳟撙"},
{"zuo"		,	"作做坐座左昨琢佐凿撮柞嘬怍胙唑笮阼祚酢"}

};



static BOOL
InitIme_pinyin();


static void
DestroyIme_pinyin();


static void
ResetIme_pinyin();


static BOOL 
CharArrived_pinyin(
	char c
);

static void
FillBackwardSelection_pinyin();


static void
FillForwardSelection_pinyin();


static char*
GetMatchHZString(
	char* pString
);


static BOOL 
IsBackSpace(
	char ch
);


static BOOL 
IsNumeric(
	char ch
);


static void 
ReCalMatchHZChars();


static void 
ReCalListChars();


LGUIIme pinyinIme = {
	IME_STATUS_PINYIN,
	TASKBAR_IMEBMP_PINYIN,
	InitIme_pinyin,
	DestroyIme_pinyin,
	ResetIme_pinyin,
	CharArrived_pinyin,
	FillBackwardSelection_pinyin,
	FillForwardSelection_pinyin,
	0
};


static BOOL
InitIme_pinyin()
{

	memset(&imeDataTable, 0, sizeof(ImeDataTable));
	return true;
}


static void
DestroyIme_pinyin()
{
	return;
}


static void
ResetIme_pinyin()
{
	memset(&imeDataTable, 0, sizeof(ImeDataTable));
}


static BOOL 
CharArrived_pinyin(
	char ch
)	
{
	char charBuffer[4];
	int iIndex;
	if(IsBackSpace(ch)){
		if(imeDataTable.iTotalInputChars == 0){
			//SendMessage(hWndFocus,MSG_KEYDOWN,SCANCODE_BACKSPACE,(LPARAM)NULL);
			SendKeyDown2Client(SCANCODE_BACKSPACE);
		}
		else{
			imeDataTable.iTotalInputChars -- ;
			imeDataTable.pTotalInputChars[imeDataTable.iTotalInputChars] = 0;
			ReCalMatchHZChars();
			ReCalListChars();
		}
	}
	else if(IsNumeric(ch)){
		//select a chinese charater
		iIndex = ch - 0x30;
		if(iIndex + imeDataTable.iBeginPos > imeDataTable.iTotalHZChars){
			memset(imeDataTable.pCurSelected,0,3);
			return true;
		}
		else{
			iIndex = (imeDataTable.iBeginPos + iIndex) * 2;
			imeDataTable.pCurSelected[0] = imeDataTable.pTotalHZChars[iIndex];
			imeDataTable.pCurSelected[1] = imeDataTable.pTotalHZChars[iIndex+1];
			imeDataTable.pCurSelected[2] = 0;
			strcpy(charBuffer, imeDataTable.pCurSelected);	
			SendString2Client(charBuffer);
			//SendMessage(hWndFocus,MSG_CHAR,(WPARAM)charBuffer,(LPARAM)NULL);
			
			imeDataTable.pListChars[0] = 0;
			imeDataTable.iTotalInputChars = 0;
			imeDataTable.pTotalInputChars[0] = 0;
			imeDataTable.iTotalHZChars = 0;
			imeDataTable.pTotalHZChars[0] =0;
			imeDataTable.iBeginPos = 0;	
		}
	}
	else{//

		imeDataTable.pTotalInputChars[imeDataTable.iTotalInputChars] = ch;
		imeDataTable.iTotalInputChars ++;
		imeDataTable.pTotalInputChars[imeDataTable.iTotalInputChars] = 0;
		ReCalMatchHZChars();
		ReCalListChars();
	}
	return true;
}

static void
FillBackwardSelection_pinyin()
{
	if(imeDataTable.iBeginPos == 0)
		return;
	else
		imeDataTable.iBeginPos -= FRAME_CHARS;
	ReCalListChars();

}


static void
FillForwardSelection_pinyin()
{
	if(imeDataTable.iBeginPos + FRAME_CHARS > imeDataTable.iTotalHZChars)
		return;
	else
		imeDataTable.iBeginPos += FRAME_CHARS;
	ReCalListChars();

}


static char*
GetMatchHZString(
	char* pString
)
{
	int i;
	for(i=0;i<MAX_ITEMS;i++){
		if(strcmp(pString, codeTable[i].pPinyin)==0)
			return codeTable[i].pHanzi;
	}
	return NULL;
}


static BOOL 
IsBackSpace(
	char ch
)
{
	if(ch == 8)
		return true;
	else
		return false;
}

static BOOL 
IsNumeric(
	char ch
)
{
	if((ch >= '0') && (ch <='9'))
		return true;
	else
		return false;

}


static void 
ReCalMatchHZChars()
{

	char* pRes;
	char buffer[10];
	strcpy(buffer,imeDataTable.pTotalInputChars);
	//printf("%s\n",buffer);
	pRes = GetMatchHZString(buffer);
	if(!pRes){
		
		imeDataTable.iTotalHZChars = 0;
		imeDataTable.pTotalHZChars[0] = 0;
	}
	else{
		strcpy(imeDataTable.pTotalHZChars,pRes);
		imeDataTable.iTotalHZChars = strlen(imeDataTable.pTotalHZChars);
	}
	imeDataTable.iBeginPos = 0;
	imeDataTable.pReturnHZChars[0] = 0;
	imeDataTable.pCurSelected[0] =0;
	imeDataTable.pListChars[0] = 0;
	
}


static void 
ReCalListChars()
{
	int i;
	char* pListString;
	//according iBeginPos
	pListString = imeDataTable.pListChars;
	//printf("%s\n",imeDataTable.pTotalHZChars);
	for(i = 0; i<FRAME_CHARS; i++){
		if(imeDataTable.iBeginPos + i >= imeDataTable.iTotalHZChars/2 - 1)
			break;
		
			
		pListString[0] = i+0x30;

		pListString[1] = imeDataTable.pTotalHZChars[(imeDataTable.iBeginPos+i) * 2];
		pListString[2] = imeDataTable.pTotalHZChars[(imeDataTable.iBeginPos+i) * 2 + 1];
		
		pListString[3] = ' ';
		pListString += 4;
	}
	*pListString = 0;
	//printf("%s\n",imeDataTable.pListChars);	
		
}













