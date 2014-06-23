#include <cstdio>
#include <cstring>

unsigned char table1[] = {
		0x4C, 0x4D, 0x96, 0x02, 0x36, 0x28, 0x32, 0x04, 0x01, 0x18, 0x60, 0x02, 0xE7, 0xBF, 0xC8, 0xC8,
		0xE0, 0xDD, 0xF2, 0xFF, 0x4C, 0xE0, 0xDD, 0x24, 0x1C, 0xED, 0xC8, 0xE0, 0xDD, 0xCC, 0x48, 0x3F,
		0xE8, 0xA2, 0x57, 0x7A, 0xB9, 0xC8, 0xE0, 0xDD, 0x4C, 0xE0, 0xDD, 0x1D, 0xE6, 0xB5, 0xCC, 0x48,
		0x3F, 0xC8, 0xE0, 0xDD, 0xC8, 0xE0, 0xDD, 0x4C, 0xB1, 0x22, 0x7F, 0x7F, 0x4C, 0xC8, 0xE0, 0xDD,
		0xC8, 0xE0, 0xDD, 0xC8, 0xE0, 0xDD, 0xF2, 0xFF, 0x4C, 0xB1, 0x22, 0xC8, 0xE0, 0xDD, 0xC8, 0xE0,
		0x4C, 0xCC, 0x48, 0x3F, 0xC8, 0xE0, 0xDD, 0xC8, 0xE0, 0xDD, 0x7F, 0x7F, 0x7F, 0x24, 0x1C, 0xED,
		0xCC, 0x48, 0x3F, 0xC8, 0x4C, 0xDD, 0xC8, 0xE0, 0xDD, 0x24, 0x1C, 0xED, 0x27, 0x7F, 0xFF, 0xC8,
		0xE0, 0xDD, 0xC8, 0xE0, 0xDD, 0x1D, 0xE6, 0xB5, 0x4C, 0xE0, 0xDD, 0xC8, 0xE0, 0xDD, 0x9A, 0x76,
		0x83, 0xC8, 0xE0, 0xDD, 0x57, 0x7A, 0xB9, 0xC8, 0xE0, 0xDD, 0xC8, 0xE0, 0x4C, 0x4C, 0xB1, 0x22,
		0xE8, 0xA2, 0x24, 0x1C, 0xED, 0xC9, 0xAE, 0xFF, 0x24, 0x1C, 0xED, 0xCC, 0x48, 0x3F, 0xC8, 0xE0,
		0x4C, 0x4C, 0xB1, 0x22, 0xC8, 0xE0, 0xDD, 0xC8, 0xE0, 0xDD, 0xC8, 0xE0, 0xDD, 0xC8, 0xE0, 0xDD,
		0xC8, 0xE0, 0xDD, 0x24, 0x4C, 0xED, 0xC8, 0xE0, 0xDD, 0x27, 0x7F, 0xFF, 0xC8, 0xE0, 0xDD, 0xC8,
		0xE0, 0xDD, 0xC8, 0xE0, 0xDD, 0xC9, 0xAE, 0xFF, 0x4C, 0xE0, 0xDD, 0xC8, 0xE0, 0xDD, 0xC8, 0xE0,
		0xDD, 0x57, 0x7A, 0xB9, 0xC8, 0xE0, 0xDD, 0x24, 0x1C, 0xED, 0xC8, 0xE0, 0x4C, 0xC8, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x52, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

unsigned long long table2[] = {0LU, 12802052153329860865LU, 8820009185778742081LU, 14685377489552175680LU, 17640018371557484162LU, 5001222808098580355LU, 10280337651052205507LU, 4539943136864638146LU, 17341432338162023495LU, 4684625763849092422LU, 10002445616197160710LU, 4280062110716136967LU, 316602082533710533LU, 13100634248527895492LU, 9079886273729276292LU, 14963274562690902149LU, 17897501733861083597LU, 5317261985492633804LU, 9369251527698184844LU, 3723423582462425997LU, 913487729268240207LU, 13620955262905380430LU, 8560124221432273934LU, 14366954754279496975LU, 633204165067421066LU, 13358680690923959435LU, 8263929714660476619LU, 14052751257435785162LU, 18159772547458552584LU, 5597550407013896713LU, 9683459881862848585LU, 4019614330850779464LU, 16857990087893459673LU, 6366289079963902936LU, 10634523970985267608LU, 2467811723213820057LU, 2107248760986682459LU, 12435693181192766810LU, 7446847164924851994LU, 15488585625257915931LU, 1826975458536480414LU, 12173439683542130591LU, 7150678132677832159LU, 15174396786063846622LU, 17120248442864547868LU, 6646558624030161181LU, 10948709051795901277LU, 2763985612781800028LU, 1266408330134842132LU, 11545304407235635733LU, 7779361655113013333LU, 15735540468723620180LU, 16527859429320953238LU, 6121735564803984535LU, 11472980570645085911LU, 3355799167275532246LU, 16229296849668151123LU, 5805155198986245714LU, 11195100814027793426LU, 3095937198970660115LU, 1582984757755146705LU, 11843872025172652240LU, 8039228661701558928LU, 16013416287142937489LU, 14615803668291843313LU, 8899048428036863472LU, 12732578159927805872LU, 79150520633427633LU, 4474375433465270899LU, 10354385063276106610LU, 4935623446427640114LU, 17714027073307729971LU, 4214497521973364918LU, 10076489363471780279LU, 4619022739376356343LU, 17415444152421382902LU, 14893694329849703988LU, 9158930277763952437LU, 13031165019049876853LU, 395746189438786676LU, 3653950917072960828LU, 9448400719772711997LU, 5247686837821935229LU, 17976542301985361788LU, 14301356265355664318LU, 8634132049891203775LU, 13555386688361130239LU, 987536012090714622LU, 13987147085464912251LU, 8337942676947501178LU, 13293117248060322362LU, 707246766990340923LU, 3950144048362858489LU, 9762605042305263352LU, 5527971225563600056LU, 18238815500631856569LU, 2532816660269684264LU, 10559913974953973545LU, 6431325855679964521LU, 16783418621947192424LU, 15558723310226026666LU, 7368371608133366187LU, 12505730857913975787LU, 2028662106208518890LU, 15244539055104240239LU, 7072196343083494254LU, 12243471129607969070LU, 1748393385683114031LU, 2828987067961363693LU, 10874101988421963244LU, 6711598334551064492LU, 17045673492894498477LU, 15800576193451433957LU, 7704791240699207396LU, 11610310397972491428LU, 1191797280968863141LU, 3425835698520258919LU, 11394395061889710182LU, 6191874397941320230LU, 16449382724904454951LU, 3165969515510293410LU, 11116517870173201059LU, 5875296594876879075LU, 16150815932694041058LU, 16078457323403117856LU, 7964652385462699041LU, 11908872151936972385LU, 1508379022269020000LU, 10131266641078737057LU, 4410004592889371040LU, 17798096856073726944LU, 5140168825526102753LU, 8670716169081011747LU, 14555234805916598050LU, 158301041266855266LU, 12941202860444044387LU, 8948750866930541798LU, 14815258492912100839LU, 456743864634120103LU, 13257656692517852838LU, 9871246892855280228LU, 4131964857330238309LU, 17481637986290856229LU, 4841729940931424292LU, 8428995043946729836LU, 14218929242551963757LU, 1053624380493341229LU, 13777988249429435180LU, 9238045478752712686LU, 3575339066338916079LU, 18037715806031398063LU, 5474354525897950638LU, 9534378247750905131LU, 3889680827556506666LU, 18317860555527904874LU, 5736490285322542955LU, 8114648424834075561LU, 13922600231363103400LU, 791492378877573352LU, 13497838642037357033LU, 7307901834145921656LU, 15330507553602878329LU, 2237187716732635449LU, 12584764878905346104LU, 10495373675643870458LU, 2309511369688178171LU, 16988133458179731387LU, 6515582509524938426LU, 10791685920067094079LU, 2623843418910967614LU, 17268264099782407550LU, 6777693344180565119LU, 6993573542732456125LU, 15034190451284582844LU, 1975072024181429244LU, 12304637995111486205LU, 11315948271845454773LU, 3215662927839982260LU, 16675885353895002356LU, 6252865428956987893LU, 7622269527552120119LU, 15595327083218670646LU, 1414493533980681846LU, 11676510867968567159LU, 7900288096725716978LU, 15855327866227330803LU, 1712917849260129459LU, 11992952971560435122LU, 11055942451127200112LU, 2937648297438439537LU, 16359447189075728945LU, 5954436075968486192LU, 5065633320539368528LU, 17863167490362830161LU, 4335358084540505873LU, 10196237172498488848LU, 12862651711359929042LU, 228371932317060051LU, 14476722092561398163LU, 8740818993145428114LU, 13179109757601959959LU, 526812190246670614LU, 14736743216266732374LU, 9018857903015699031LU, 4767189123875452565LU, 17546714481868142484LU, 4057324212417037780LU, 9936212110058308821LU, 13703342794081035677LU, 1118593858366317724LU, 14144392686166988508LU, 8494066729089865693LU, 5395842960033547039LU, 18107817482060808734LU, 3496786771366228062LU, 9308117515145179487LU, 5657974135922727386LU, 18387968464897038555LU, 3811134763776060059LU, 9604445702755445658LU, 13423196669102128984LU, 856458924630064729LU, 13848060740710157337LU, 8179723594537864472LU, 12663878062041173641LU, 2167679042270252936LU, 15409582481398414792LU, 7238361046280699081LU, 6589554878800979979LU, 16922499509938792714LU, 2383594561937726282LU, 10429840010660911691LU, 6851671397040517838LU, 17202625018250245071LU, 2697921480016773519LU, 10726157936520560782LU, 12383748795882640460LU, 1905567381888030029LU, 15113269413396588301LU, 6924030370355078668LU, 6331939031020586820LU, 16606345892305929797LU, 3294777439400489989LU, 11246438269504697604LU, 11750593189753758150LU, 1348960740008386759LU, 15669300325651812999LU, 7556634706698294150LU, 12067032178152160003LU, 1647388719700244994LU, 15929304770925398082LU, 7834650162825906499LU, 6033516089076080001LU, 16289902965173230720LU, 3016758044538040000LU, 10986438861977923521LU, 32LU, 10220828470894112083LU, 4294967296LU, 1LU};

void S(const char s[], int k) {
	for (int i = 0; i < k; i++)
		table1[i * 20] = s[i];
}

unsigned long long C() {
	unsigned long long a = 0;
	for (int i = 0; i < 256; i++) {
		int j = table1[i] ^ (a & 0xff);
		a = (a >> 8) ^ (table2[j]);
	}
	return a;
}

unsigned long long common_crc(unsigned char *buf, int len)
{
    unsigned long long a = 0;
    for (int i = 0; i < len; i++)
    {
        a = (a >> 8) ^ (table2[buf[i] ^ (a & 0xff)]);
        //printf("%d: %016llx\n", i, a);
    }
    return a;
}

int main(int argc, char *argv[])
{
	//S("RLLLLLLLLLLLL", 13);
	unsigned long long t = 0;
    /*
	for (int a = 0; a < 26; a++)
		for (int b = 0; b < 26; b++)
			for (int c = 0; c < 26; c++)
				for (int d = 0; d < 26; d++)
					for (int e = 0; e < 26; e++)
						for (int f = 0; f < 26; f++) {
							t += C();
						}

                        */
    char *buf;
    int i, sum = 0;
    buf = new char[32];
    if (argc > 1)
    {
        strncpy(buf, argv[1], strlen(argv[1]));
    }
    for (int i = 0; i < strlen(buf); i++)
    {
        sum += buf[i];
    }
    //printf("bytes sum: %d\n", sum);

	t = common_crc((unsigned char *)buf, strlen(buf));

	printf("%016llx %d %d", t, sum, strlen(buf));
}
