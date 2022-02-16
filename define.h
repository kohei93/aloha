#define NODE 100
#define TIME 100 //micro second

#define X 100
#define Y 100

#define transtime 0.01


struct info{//nodeの情報
    double x = 0;  //x座標
    double y = 0;  //y座標
    int flag_coll = 0;	//衝突フラグ
    int flag_trans = 0;	//送信中フラグ
    double start = 0;	//送信開始時間
    double finish = 0;		//送信終了時間
};