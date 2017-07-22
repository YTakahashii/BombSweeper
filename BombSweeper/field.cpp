#include "field.h"
#include "DxLib.h"

Field::Field(int MAXROW, int MAXCOL, int MAXBOMB, int CLEARNUM, int STX, int STY, int SQUARE_WIDTH, int SQUARE_HEIGHT, int TIME, int CLICKMAX)
{
	/*変数初期化*/
	click = new Click;
	row = MAXROW;
	col = MAXCOL;
	bombnum = MAXBOMB;
	remainderbomb = MAXBOMB; //残り爆弾数描画用
	clearnum = CLEARNUM; //クリアするためのクリック数
	stx = STX; 
	sty = STY; //描画開始座標
	width = SQUARE_WIDTH;
	height = SQUARE_HEIGHT;
	remainderclick = CLICKMAX; //残りクリック数*Removeモード専用*
	clear = false, failure = false, newrecord = false;
	isopened = 0;
	removalnum = 0;
	lastr = 0, lastc = 0;

	/*配列初期化*/
	calc.resize(row*col);
	field.resize(row);
	for(int i=0; i<row; i++){
		field[i].resize(col);
	}
	for(int r=0; r<row; r++){
		for(int c=0; c<col; c++){
			field[r][c].arroundbomb = 0;
			field[r][c].isFlag = false;
			field[r][c].isOpened = false;
			field[r][c].isPointed = false;
		}
	}
	for(int i=0; i<(int)calc.size(); i++){
		calc[i] = 0;
	}
	
	BombShuffle();
	
	/*画像初期化*/
	switch(nowLevel){
	case eLv_Easy:
		mmaspng = LoadGraph("./media/pic/none.png");
		maspng = LoadGraph("./media/pic/none2.png");
		zeropng = LoadGraph("./media/pic/0.png");
		onepng = LoadGraph("./media/pic/1.png");
		twopng = LoadGraph("./media/pic/2.png");
		threepng = LoadGraph("./media/pic/3.png");
		fourpng = LoadGraph("./media/pic/4.png");
		fivepng = LoadGraph("./media/pic/5.png");
		sixpng = LoadGraph("./media/pic/6.png");
		sevenpng = LoadGraph("./media/pic/7.png");
		eightpng = LoadGraph("./media/pic/8.png");
		bombpng = LoadGraph("./media/pic/bomb.png");
		bomb2png = LoadGraph("./media/pic/bomb2.png");
		bomb3png = LoadGraph("./media/pic/bomb3.png");
		flagpng = LoadGraph("./media/pic/flag.png");
		chainmp3 = LoadSoundMem("./media/sound/chain.mp3");
		explodemp3 = LoadSoundMem("./media/sound/explode.mp3");
		normalfont = CreateFontToHandle( "メイリオ",32,1, DX_FONTTYPE_ANTIALIASING );
		break;
	case eLv_Medium:
		mmaspng = LoadGraph("./media/pic/snone.png");
		maspng = LoadGraph("./media/pic/snone2.png");
		zeropng = LoadGraph("./media/pic/s0.png");
		onepng = LoadGraph("./media/pic/s1.png");
		twopng = LoadGraph("./media/pic/s2.png");
		threepng = LoadGraph("./media/pic/s3.png");
		fourpng = LoadGraph("./media/pic/s4.png");
		fivepng = LoadGraph("./media/pic/s5.png");
		sixpng = LoadGraph("./media/pic/s6.png");
		sevenpng = LoadGraph("./media/pic/s7.png");
		eightpng = LoadGraph("./media/pic/s8.png");
		bombpng = LoadGraph("./media/pic/sbomb.png");
		bomb2png = LoadGraph("./media/pic/sbomb2.png");
		bomb3png = LoadGraph("./media/pic/sbomb3.png");
		flagpng = LoadGraph("./media/pic/sflag.png");
		chainmp3 = LoadSoundMem("./media/sound/chain.mp3");
		explodemp3 = LoadSoundMem("./media/sound/explode.mp3");
		normalfont = CreateFontToHandle( "メイリオ",32,1, DX_FONTTYPE_ANTIALIASING );
		break;
	case eLv_Expert:
		mmaspng = LoadGraph("./media/pic/snone.png");
		maspng = LoadGraph("./media/pic/snone2.png");
		zeropng = LoadGraph("./media/pic/s0.png");
		onepng = LoadGraph("./media/pic/s1.png");
		twopng = LoadGraph("./media/pic/s2.png");
		threepng = LoadGraph("./media/pic/s3.png");
		fourpng = LoadGraph("./media/pic/s4.png");
		fivepng = LoadGraph("./media/pic/s5.png");
		sixpng = LoadGraph("./media/pic/s6.png");
		sevenpng = LoadGraph("./media/pic/s7.png");
		eightpng = LoadGraph("./media/pic/s8.png");
		bomb2png = LoadGraph("./media/pic/sbomb2.png");
		bomb3png = LoadGraph("./media/pic/sbomb3.png");
		bombpng = LoadGraph("./media/pic/sbomb.png");
		flagpng = LoadGraph("./media/pic/sflag.png");
		chainmp3 = LoadSoundMem("./media/sound/chain.mp3");
		explodemp3 = LoadSoundMem("./media/sound/explode.mp3");
		normalfont = CreateFontToHandle( "メイリオ",32,1, DX_FONTTYPE_ANTIALIASING );
		break;
	}
	newrecpng = LoadGraph("./media/pic/newrecord.png");
}

Field::~Field()
{
	delete click;
}

void Field::BombShuffle()
{
	for(int i=0; i<bombnum; i++){ //地雷の数だけループ
		calc[i] = 9;
	}
	
	//シャッフル
	srand((unsigned) time(NULL));
	random_shuffle(calc.begin(), calc.end());	
	
	for(int r=0; r<row; r++){
		for(int c=0; c<col; c++){
			field[r][c].arroundbomb = calc[r*9+c];
		}
	}
	for(int r=0; r<row; r++){
		for(int c=0; c<col; c++){
			if(field[r][c].arroundbomb == 9){
				for(int r2=r-1; r2<=r+1; r2++){
					for(int c2=c-1; c2<=c+1; c2++){
						if((r2>-1 && r2<row) && (c2>-1 && c2<col) && (field[r2][c2].arroundbomb != 9)){
							field[r2][c2].arroundbomb++;
						}
					}
				}
			}
		}
	}
}

void Field::Method() //外部からアクセスするのまとめる関数
{
	DrawField();
	CheckClick();
	DrawRemainderBomb();
}

void Field::DrawField()
{
	for(int r=0; r<row; r++){
		for(int c=0; c<col; c++){
			int sx = stx + c * width;
			int sy = sty + r * height;

			if(field[r][c].isOpened == false && field[r][c].isFlag == true){
				DrawGraph( sx, sy, flagpng, true );
			}else if(field[r][c].isOpened == false && field[r][c].isFlag == false && field[r][c].isPointed == false){
				DrawGraph( sx, sy, mmaspng, true );
			}else if(field[r][c].isOpened == false && field[r][c].isFlag == false && field[r][c].isPointed == true){
				DrawGraph( sx, sy, maspng, true );
			}

			if(field[r][c].isOpened == true){
				switch(field[r][c].arroundbomb){
				case 0:
					DrawGraph( sx, sy, zeropng, true );
					break;
				case 1:
					DrawGraph( sx, sy, onepng, true );
					break;
				case 2:
					DrawGraph( sx, sy, twopng, true );
					break;
				case 3:
					DrawGraph( sx, sy, threepng, true );
					break;
				case 4:
					DrawGraph( sx, sy, fourpng, true );
					break;
				case 5:
					DrawGraph( sx, sy, fivepng, true );
					break;
				case 6:
					DrawGraph( sx, sy, sixpng, true );
					break;
				case 7:
					DrawGraph( sx, sy, sevenpng, true );
					break;
				case 8:
					DrawGraph( sx, sy, eightpng, true );
					break;
				case 9:
					DrawGraph( sx, sy, bombpng, true );
					break;
				case 10:
					DrawGraph( sx, sy, bomb2png, true );
					break;
				case 11:
					DrawGraph( sx, sy, bomb3png, true );
					break;
				}
			}
		}
	}
}

void Field::CheckClick()
{
	int mx, my;
	GetMousePoint( &mx, &my );
	
	if(click->LeftClick()) MineOpen(mx, my);
	if(click->RightClick()) SetFlag(mx, my);
	LightCursor(mx, my);
}
void Field::MineOpen(int mx, int my)
{
	for( int r=0; r<row; r++ ){
		for( int c=0; c<col; c++ ){
			if( stx + c * width <= mx &&
				mx < stx + (c+1) * width &&
				sty + r * height <= my &&
				my < sty + (r+1) * height )
			{
				if(field[r][c].isOpened == false && field[r][c].isFlag == false){
					field[r][c].isOpened = true;
					isopened++;
					if(field[r][c].arroundbomb == 9){
						failure = true;
						ChangeVolumeSoundMem(10,explodemp3);
						PlaySoundMem(explodemp3,DX_PLAYTYPE_BACK);
					}
					if(field[r][c].arroundbomb == 0){
						OpenChain(r, c);
						PlaySoundMem(chainmp3,DX_PLAYTYPE_BACK);
					}
					return;
				}
			}
		}
	}
}

void Field::OpenChain(int openr, int openc)
{
	for(int r=openr-1; r<openr+2; r++){
		for(int c=openc-1; c<openc+2; c++){
			if(r>-1 && r<row && c>-1 && c<col && field[r][c].isOpened == false && field[r][c].arroundbomb != 9){
				field[r][c].isOpened = true;
				isopened++;
				if(field[r][c].arroundbomb == 0){
					OpenChain(r, c);
				}
			}
		}
	}
}

void Field::SetFlag(int mx, int my)
{
	for( int r=0; r<row; r++ ){
		for( int c=0; c<col; c++ ){
			if( stx + c * width <= mx &&
				mx < stx + (c+1) * width &&
				sty + r * height <= my &&
				my < sty + (r+1) * height )
			{
				if(field[r][c].isFlag == false && field[r][c].isOpened == false){
					field[r][c].isFlag = true;
					remainderbomb--;
				}else if(field[r][c].isFlag == true){
					field[r][c].isFlag = false;
					remainderbomb++;
				}
				return;
			}
		}
	}
}

void Field::LightCursor(int mx, int my)
{
	field[lastr][lastc].isPointed = false;
	for( int r=0; r<row; r++ ){
		for( int c=0; c<col; c++ ){
			if( stx + c * width <= mx &&
				mx < stx + (c+1) * width &&
				sty + r * height <= my &&
				my < sty + (r+1) * height )
			{
				if(field[r][c].isOpened == false && field[r][c].isFlag == false){
					field[r][c].isPointed = true;
					lastr = r;
					lastc = c;
					return;
					
				}
			}
		}
	}
}

void Field::DrawRemainderBomb()
{
	char buf[32];
	sprintf_s(buf,32,"%d",remainderbomb);
	DrawStringToHandle(560,85,buf,GetColor(255,255,255),normalfont,1);
}

bool Field::CheckClear()
{
	clear = true;
	if(isopened == clearnum && failure == false) return true;
	else return false;
}

bool Field::CheckFailure()
{
	if(failure == true) return true;
	else return false;
}

void Field::ClearAnswerShow()
{
	for(int r=0; r<row; r++){
		for(int c=0; c<col; c++){
			if(field[r][c].arroundbomb == 9){
				field[r][c].arroundbomb = 10;
				field[r][c].isOpened = true;
			}
		}
	}
}

void Field::FailureAnswerShow()
{
	for(int r=0; r<row; r++){
		for(int c=0; c<col; c++){

			if(field[r][c].arroundbomb == 9){
				if(field[r][c].isFlag){
					field[r][c].arroundbomb = 10;
				}
				field[r][c].isOpened = true;
			}
			if(field[r][c].arroundbomb>=0 && field[r][c].arroundbomb<=8 && field[r][c].isFlag){
				field[r][c].arroundbomb = 11;
				field[r][c].isOpened = true;
			}
		}
	}
}

void Field::Failure()
{
	DrawField();
	FailureAnswerShow();
	//DrawRemainderBomb();
}

void Field::Clear()
{
	DrawField();
	ClearAnswerShow();
	//DrawRemainderBomb();
}


/*RemoveMode*/
void Field::RemoveMethod()
{
	DrawField();
	DrawRemainderBomb();
	DrawRemainderClick();
	RemoveModeCheckClick();
}

void Field::RemoveClear()
{
	DrawField();
}

void Field::RemoveFailure()
{
	DrawField();
	RemoveAnswerShow();
	//DrawRemainderBomb();
	//DrawRemainderClick();
}

void Field::RemoveOpen(int mx, int my)
{
	for( int r=0; r<row; r++ ){
		for( int c=0; c<col; c++ ){
			if( stx + c * width <= mx &&
				mx < stx + (c+1) * width &&
				sty + r * height <= my &&
				my < sty + (r+1) * height )
			{
				if(field[r][c].isOpened == false && field[r][c].isFlag == false){
					field[r][c].isOpened = true;
					remainderclick--;
					if(field[r][c].arroundbomb == 9){
						removalnum++;
						remainderbomb--;
					}
					if(field[r][c].arroundbomb == 0){
						OpenChain(r, c);
						PlaySoundMem(chainmp3,DX_PLAYTYPE_BACK);
					}
					return;
				}
			}
		}
	}
}

bool Field::RemoveModeCheckClear()
{
	if(removalnum == bombnum) return true;
	else return false;
}

bool Field::RemoveModeCheckFailure()
{
	if(remainderclick <= 0){
		
		return true;
	}else{
		return false;
	}
}

void Field::RemoveModeCheckClick()
{
	int mx, my;
	GetMousePoint( &mx, &my );

	if(click->LeftClick()) RemoveOpen(mx, my);
	//if(click->RightClick()) SetFlag(row, col, mx, my, stx, sty);
	LightCursor(mx, my);
}

void Field::DrawRemainderClick()
{
	int color = GetColor(255,255,255);
	if(remainderclick <= 5) color = GetColor(255,0,0);
	char buf[32];
	sprintf_s(buf,32,"%d",remainderclick);
	DrawStringToHandle(760,80,buf,color,normalfont,1);
}

void Field::RemoveAnswerShow()
{
	for(int r=0; r<row; r++){
		for(int c=0; c<col; c++){
			if(field[r][c].arroundbomb == 9){
				field[r][c].isOpened = true;
			}
		}
	}
}

void Field::SaveClickBestScore()
{
	int bestscore;
	int clicknum;
	FILE *wfp;
	FILE *rfp;

	switch(nowLevel){
	case eLv_Easy:
		rfp = fopen("./score/easy_click.dat", "rb");
		clicknum = E_CLICKMAX - remainderclick;
		break;
	case eLv_Medium:
		rfp = fopen("./score/med_click.dat", "rb");
		clicknum = M_CLICKMAX - remainderclick;
		break;
	case eLv_Expert:
		rfp = fopen("./score/exp_click.dat", "rb");
		clicknum = EX_CLICKMAX - remainderclick;
		break;
	}
	if(rfp == NULL){
		bestscore = 9999999; //time.datが無かったら適当にでかい値を
	}else{
		fread(&bestscore,sizeof(int), 1, rfp);
		fclose(rfp);
	}

	switch(nowLevel){
	case eLv_Easy:
		wfp = fopen("./score/easy_click.dat", "wb");
		break;
	case eLv_Medium:
		wfp = fopen("./score/med_click.dat", "wb");
		break;
	case eLv_Expert:
		wfp = fopen("./score/exp_click.dat", "wb");
		break;
	}
	if(wfp == NULL){
		fwrite(&clicknum,sizeof(int),1,wfp);
	}else{
		if( clicknum < bestscore || bestscore < 0){
			fwrite(&clicknum,sizeof(int),1,wfp);
			newrecord = true;
		}else{
			fwrite( &bestscore,sizeof(int),1,wfp);
		}
	}

	fclose(wfp);
}

void Field::DrawClickScore()
{
	int bestscore,clicknum;
	FILE *rfp;

	switch(nowLevel){
	case eLv_Easy:
		rfp = fopen("./score/easy_click.dat", "rb");
		clicknum = E_CLICKMAX - remainderclick;
		break;
	case eLv_Medium:
		rfp = fopen("./score/med_click.dat", "rb");
		clicknum = M_CLICKMAX - remainderclick;
		break;
	case eLv_Expert:
		rfp = fopen("./score/exp_click.dat", "rb");
		clicknum = EX_CLICKMAX - remainderclick;
		break;
	}
	if(rfp == NULL){
		return;
	}else{
		fread(&bestscore,sizeof(int), 1, rfp);
		fclose(rfp);
	}
	if(clicknum < bestscore){
		bestscore = clicknum;
	}

	char buf[32];
	sprintf_s(buf,32,"%d",clicknum);
	DrawStringToHandle(650,290,buf,GetColor(255,255,255),normalfont,1); //result
	sprintf_s(buf,32,"%d",bestscore);
	DrawStringToHandle(650,360,buf,GetColor(255,255,255),normalfont,1); //best
	if(newrecord) DrawGraph(450,280,newrecpng,true);
}

void Field::DrawClickBestOnly()
{
	int bestscore;
	FILE *rfp;

	switch(nowLevel){
	case eLv_Easy:
		rfp = fopen("./score/easy_click.dat", "rb");
		break;
	case eLv_Medium:
		rfp = fopen("./score/med_click.dat", "rb");
		break;
	case eLv_Expert:
		rfp = fopen("./score/exp_click.dat", "rb");
		break;
	}
	if(rfp == NULL){
		return;
	}else{
		fread(&bestscore,sizeof(int), 1, rfp);
		fclose(rfp);
	}

	char buf[32];
	sprintf_s(buf,32,"%d",bestscore);
	DrawStringToHandle(650,360,buf,GetColor(255,255,255),normalfont,1);
}
