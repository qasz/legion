
#include "Amos.h"

#include "legion.h"
#include "lgn_opcje.h"
#include "lgn_diskacs.h"
#include "lgn_mapa.h"
#include "lgn_util.h"
#include "utl_locale.h"

void OPCJE(void) {
	//	Procedure OPCJE

	aint KONIEC=0, STREFA=0, JEST=0;
	//_OPCJE_RYSUJ();										//	   Gosub RYSUJ
	do {																//	   Repeat
		rysuj();						//rysujemy mape
		WaitVbl();
		if( MouseClick() ) {							//	      If Mouse Click=1
			STREFA=MouseZone();							//	         STREFA=Mouse Zone
			if( STREFA==1 ) {								//	         If STREFA=1
				ZOKNO();											//	            ZOKNO
				_LOAD_GAME();									//	            _LOAD_GAME
				JEST=Param;										//	            JEST=Param
				if( JEST != 0 ) {							//	            If JEST
					KONIEC=-1;									//	               KONIEC=True
					ResetZone(-1);							//	               Reset Zone
																			//	               Del Block
					SpriteOnOff(2,false);				//	               Sprite Off 2
					SETUP0();										//	               SETUP0
					VISUAL_OBJECTS();						//	               VISUAL_OBJECTS
					ChangeMouse(5);							//	               Change Mouse 5
					Sprite(2,SPX,SPY,1);				//	               Sprite 2,SPX,SPY,1
					CENTER(10,10,0);						//	               CENTER[10,10,0]
				} else {											//	            Else
					//_OPCJE_RYSUJ();						//	               Gosub RYSUJ
				}															//	            End If
			}													//	         End If
		}																	//	      End If
	} while( KONIEC == 0 );							//	   Until KONIEC
																			//	   Goto OVER
																			//	   RYSUJ:
																			//	   OKNO[100,60,140,160]
																			//	   SZMAL$=Str$(GRACZE(1,1))-" "
																			//	   DZIEN$=Str$(DZIEN)-" "
																			//	   GADGET[OKX+10,OKY+8,120,15,"Day "+DZIEN$+"  Treasury:"+SZMAL$,7,0,4,31,-1]
																			//	   GADGET[OKX+10,OKY+28,120,15,"Load Game",8,1,6,31,1]
																			//	   GADGET[OKX+10,OKY+48,120,15,"Save Game",8,1,6,31,2]
																			//	   GADGET[OKX+10,OKY+68,120,15,"Statistics",8,1,6,31,3]
																			//	   GADGET[OKX+10,OKY+88,120,15,"Preferences",8,1,6,31,4]
																			//	   GADGET[OKX+10,OKY+108,120,15,"End Game",8,1,6,31,5]
																			//	   GADGET[OKX+10,OKY+128,120,15,"Exit",8,1,6,31,6]
																			//	   Return
																			//	   OVER:
}
void _STATUS_NAPISZ(astr A_S,astr B_S,astr C_S) {								//	   NAPISZ:
	gad_text(1.0); Text(OKX+8,OKY+16,GS("137")+Str_S(DZIEN));			//	   Ink 1,30 : Text OKX+8,OKY+16,"Report for day: "+Str$(DZIEN)
	Text(OKX+8,OKY+16+10,GS("138"));															//	   Text OKX+8,OKY+16+10,"You rule:"
	Text(OKX+8,OKY+24+20,A_S);																		//	   Text OKX+8,OKY+24+20,A$
	Text(OKX+8,OKY+24+30,B_S);																		//	   Text OKX+8,OKY+24+30,B$
	Text(OKX+8,OKY+34+40,C_S);																		//	   Text OKX+8,OKY+34+40,C$
	Text(OKX+8,OKY+34+50,GS("139")+Str_S(players[1]->gold));					//	   Text OKX+8,OKY+34+50,"Treasury: "+Str$(GRACZE(1,1))
	return;																												//	   Return
}
void STATUS(void) {
																																//	Procedure STATUS
	aint A=0, AM=0, I=0, WOJ=0, M=0, MS=0, LUDZIE=0, POD=0,
			 STREFA=0, KONIEC=0, WYS=0, KOL=0, RES=0;
	astr KON_S="", KON2_S="", A_S="", B_S="", C_S="";

	rysuj();
	OKNO(80,80,160,120);																					//	   OKNO[80,80,160,120]
	GADGET(OKX+4,OKY+4,152,92,"",31,2,30,1,-1);										//	   GADGET[OKX+4,OKY+4,152,92,"",31,2,30,1,-1]
	GADGET(OKX+4,OKY+100,40,15,GS("140"),8,1,6,31,2);							//	   GADGET[OKX+4,OKY+100,40,15,"Graphs",8,1,6,31,2]
	GADGET(OKX+116,OKY+100,40,15,GS("141"),8,1,6,31,1);							//	   GADGET[OKX+116,OKY+100,40,15,"   Ok",8,1,6,31,1]
	for( A=0; A<=19; ++A ) {																			//	   For A=0 To 19
		if( ARMIA[A][0][TE]>0 ) {																		//	      If ARMIA(A,0,TE)>0
			AM++;																											//	         Inc AM
			for( I=1; I<=10; ++I ) {																	//	         For I=1 To 10
				if( ARMIA[A][I][TE]>0 ) {																//	            If ARMIA(A,I,TE)>0
					WOJ++;																								//	               Inc WOJ
				}																												//	            End If
			}																													//	         Next I
		}																														//	      End If
	}																															//	   Next A
	KON_S=GS("142"); KON2_S=GS("143");														//	   KON$="s" : KON2$="s"
	RES=AM % 10;																									//		RES=AM mod 10
	if( RES<=1 || RES>4 ) KON_S=GS("144");												//		If RES<=1 or RES>4 : KON$="�w" : End If
	if( RES> 1 &&	RES<5 ) KON_S=GS("145");												//		If RES>1 and RES<5 : KON$="y" : End If
	if( AM==1 ) KON_S="";																					//	   If AM=1 : KON$="" : End If
	if( WOJ==1 ) KON2_S="";																				//	   If WOJ=1 : KON2$="" : End If
	A_S=Str_S(AM)+GS("146")+KON_S+", "+Str_S(WOJ)+GS("147")+KON2_S;//	   A$=Str$(AM)+" legion"+KON$+", "+Str$(WOJ)+" worrior"+KON2$
	for( M=0; M<=49; M++ ) {																			//	   For M=0 To 49
		if( MIASTA[M][0][M_CZYJE]==1 ) {														//	      If MIASTA(M,0,M_CZYJE)=1
			MS++;																											//	         Inc MS
			LUDZIE+=MIASTA[M][0][M_LUDZIE];														//	         Add LUDZIE,MIASTA(M,0,M_LUDZIE)
			POD+=MIASTA[M][0][M_PODATEK]*MIASTA[M][0][M_LUDZIE]/25;		//	         Add POD,MIASTA(M,0,M_PODATEK)*MIASTA(M,0,M_LUDZIE)/25
		}																														//	      End If
	}																															//	   Next M
	KON_S=GS("148");																							//	   KON$="s"
	RES=MS % 10;																									//		RES=MS mod 10
	if( RES>1 && RES<5 ) KON_S=GS("149");													//		If RES>1 and RES<5 : KON$="a" : End If
	if( MS==1 ) KON_S=GS("150");																	//	   If MS=1 : KON$="" : End If
	B_S=Str_S(MS)+GS("151")+KON_S+", "+Str_S(LUDZIE)+GS("152");		//	   B$=Str$(MS)+" town"+KON$+", "+Str$(LUDZIE)+" inhabitants"
	C_S=GS("153")+Str_S(POD);																			//	   C$="Daily income : "+Str$(POD)
	_STATUS_NAPISZ(A_S,B_S,C_S);																	//	   Gosub NAPISZ
	void *sb = StoreBuffer(OKX-1,OKY-1,160+2,120+2);
	do {																													//	   Repeat
		rysuj(); RestoreBuffer(sb); WaitVbl();
		if( MouseClick()==1 ) {																			//	      If Mouse Click=1
			STREFA=MouseZone();																				//	         STREFA=Mouse Zone
			if( STREFA==1 ) {																					//	         If STREFA=1
				KONIEC=-1;																							//	            KONIEC=True
			}																													//	         End If
			if( STREFA==2 ) {																					//	         If STREFA=2
				rysuj(); RestoreBuffer(sb);
				gad_back(1.0); _Bar(OKX+5,OKY+5,OKX+150,OKY+90);				//	            Ink 30 : Bar OKX+5,OKY+5 To OKX+150,OKY+90
				for( I=1; I<=4; ++I ) {																	//	            For I=1 To 4
					WYS=players[I]->power/250;																	//	               WYS=GRACZE(I,2)/250
					KOL=players[I]->colour;																			//	               KOL=GRACZE(I,3)
					if( WYS>100 ) WYS=100;																//	               If WYS>100 : WYS=100 : End If
					if( WYS<4 ) WYS=4;																		//	               If WYS<4 : WYS=4 : End If
					gad_text(1.0); Text(OKX+8,OKY+4+I*20,players[I]->playerName);		//	               Ink 1,30 : Text OKX+8,OKY+4+I*20,IMIONA$(I)
																																//	               '               Ink KOL+1 : Box OKX+50,OKY-8+I*20 To OKX+50+WYS,OKY-8+I*20+15
					switch(I) {
						case 1: Gfx::Color(1.0f, 0.0f, 0.0f); break;
						case 2: Gfx::Color(0.0f, 0.0f, 1.0f); break;
						case 3: Gfx::Color(0.0f, 1.0f, 0.0f); break;
						case 4: Gfx::Color(1.0f, 1.0f, 0.0f); break;
					}
					_Box(OKX+50,OKY-8+I*20,OKX+49+WYS,OKY-9+I*20+15);			//	               Ink KOL+1 : Box OKX+50,OKY-8+I*20 To OKX+49+WYS,OKY-9+I*20+15

					gad_shadow(1.0); _Box(OKX+51,OKY-7+I*20,OKX+50+WYS,OKY-8+I*20+15);//	               Ink 25 : Box OKX+51,OKY-7+I*20 To OKX+50+WYS,OKY-8+I*20+15

					switch(I) {
						case 1: Gfx::Color(0.7f, 0.0f, 0.0f); break;
						case 2: Gfx::Color(0.0f, 0.0f, 0.7f); break;
						case 3: Gfx::Color(0.0f, 0.7f, 0.0f); break;
						case 4: Gfx::Color(0.7f, 0.7f, 0.0f); break;
					}																											//
					_Bar(OKX+51,OKY-7+I*20,OKX+50+WYS,OKY-9+I*20+15);			//	               Ink KOL : Bar OKX+51,OKY-7+I*20 To OKX+49+WYS,OKY-9+I*20+15
				}																												//	            Next I
				WaitVbl();
				do {																										//	            Repeat
					ProcessEvents();
				} while( MouseClick()!=1 );															//	            Until Mouse Click=1
				//gad_back(1.0); _Bar(OKX+5,OKY+5,OKX+150,OKY+90);			//	            Ink 30 : Bar OKX+5,OKY+5 To OKX+150,OKY+90
				//_STATUS_NAPISZ();																			//	            Gosub NAPISZ
			}																													//	         End If
		}																														//	      End If
	} while( KONIEC==0 );																					//	   Until KONIEC
																																//	   Goto OVER
																																//	   OVER:
	ZOKNO();																											//	   ZOKNO
	FreeBuffer(sb);
																																//
																																//	End Proc
}

