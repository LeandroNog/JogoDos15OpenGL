	#include <GL/glut.h>

	#include <stdlib.h>
	#include <string.h>
	#include <time.h>
	#include "OpenAL.h"

	#define SENS_ROT 5.0
	#define SENS_OBS 20.0
	#define SENS_TRANSL 30.0
	typedef struct PosicaoCelula{
		int x;
		int y;
	}PosicaoCelula;
	typedef struct Posicao{
	    int x;
	    int y;
	    int posicao;
	}Posicao;
	int  ex=1,ey=1,ez=1;
	int  tx=0;
	int  ang=0;
	clock_t tInicio, tFim, tDecorrido;
	bool wire = true;
	bool orto=true;
	float win=1000.0f;
	float aspecto;
	float angulo=60.0f;
	bool eixo=true;
	int objeto =0;
	int minuto =0;
	int hora = 0;
	GLfloat rotX=0.0,rotY=0.0,rotX_ini=0.0000,rotY_ini=0.0000;
	GLfloat obsX=0.0,obsY=0.0,obsZ=5.0,obsX_ini,obsY_ini,obsZ_ini=5.0;
	bool minutoInicio= true;
	int x_ini=0,y_ini=0,bot;
	bool start = true;
	int numPartidas=1;
	int primitiva=-1;

	int move1=0;
	static char direction=0;
	GLuint botao1, tabuleiro1, tabuleiro2;
	int dx=0, dy=0,theta1=0,theta2=0,theta3=0;
	Posicao posicaoBlocos[16];
	PosicaoCelula posicaoCelulas[16];
	int corBlocos[15];
	GLuint texture,textureInicial;
	GLuint texture4;
	GLuint textureB1 ;
	GLuint textureB2, textureB3, textureB4, textureB5, textureB6, textureB7, textureB8
	 , textureB9, textureB10, textureB11, textureB12, textureB13, textureB14, textureB15;
	int posicaoVazio=15;
	int varX,varY;
	int flagTempo;
	bool Venceu=false;
	int numJogadas = 0;

	void inicializaCores(){
	  int i;
	  for(i=0;i<15;i++){
	    corBlocos[i]=0;
	  }
	}
	void sleep(time_t delay){
    	time_t timer0,timer1;
    	time(&timer0);
   		do{
        	time(&timer1);
    	}while((timer1-timer0)<delay);
}

	void posicaoInicial(int nivel){
		if(nivel==0){
			for (int j = 0; j< 15; j++)
			{
		     	posicaoBlocos[j].posicao=j;
			}

		}
		else if(nivel>9){
			numPartidas=1;
		}
		else{
			FILE *fPos;
			char mapa[3];
			sprintf(mapa,"%d",nivel);
			strcat(mapa,".txt");
			fPos=fopen(mapa,"r+");
			for (int j =0; j<15; j++)
			{
		     	fscanf(fPos,"%d",&posicaoBlocos[j].posicao);
			}

		}
		/*else if(nivel==2){
		   	fPos=fopen("Mapas/2.txt","r+");
			for (int j = 0; j< 15; j++)
			{
		     	fscanf(fPos,"%d",&posicaoBlocos[j].posicao);
			}

	}
		else if(nivel>=3){
		   	fPos=fopen("Mapas/3.txt","r+");
			for (int j = 0; j< 15; j++)
			{
		     	fscanf(fPos,"%d",&posicaoBlocos[j].posicao);
			}

	}
	*/
	}
	void inicializaPosicaoCelulas(){
		posicaoCelulas[0].x=-150;
		posicaoCelulas[0].y=150;

		posicaoCelulas[1].x=-50;
		posicaoCelulas[1].y=150;

		posicaoCelulas[2].x=50;
		posicaoCelulas[2].y=150;

		posicaoCelulas[3].x=150;
		posicaoCelulas[3].y=150;

		posicaoCelulas[4].x=-150;
		posicaoCelulas[4].y=50;

		posicaoCelulas[5].x=-50;
		posicaoCelulas[5].y=50;

		posicaoCelulas[6].x=50;
		posicaoCelulas[6].y=50;

		posicaoCelulas[7].x=150;
		posicaoCelulas[7].y=50;

		posicaoCelulas[8].x=-150;
		posicaoCelulas[8].y=-50;

		posicaoCelulas[9].x=-50;
		posicaoCelulas[9].y=-50;

		posicaoCelulas[10].x=50;
		posicaoCelulas[10].y=-50;

		posicaoCelulas[11].x=150;
		posicaoCelulas[11].y=-50;

		posicaoCelulas[12].x=-150;
		posicaoCelulas[12].y=-150;

		posicaoCelulas[13].x=-50;
		posicaoCelulas[13].y=-150;

		posicaoCelulas[14].x=50;
		posicaoCelulas[14].y=-150;

		posicaoCelulas[15].x=150;
		posicaoCelulas[15].y=-150;

	}

	void init( void )
	{
	    glClearColor( 0.45, 0.27, 0.07, 0.0 );
	    glMatrixMode( GL_PROJECTION );
	    glOrtho( -325, 325, -325, 325,100 ,-100);
	    //Inicializar sistema de visualizaçao
	    glMatrixMode( GL_MODELVIEW);
	    glLoadIdentity();

	    glutSwapBuffers();

	}

	int incrementoY(int pos){
	if ((pos>=0)&&(pos<=3)){
	    return -20;
	}
	else if ((pos>=4)&&(pos<=7)){
	    return 180;
	}
	else if ((pos>=8)&&(pos<=11)){
	    return 380;
	}
	else if ((pos>=12)&&(pos<=15)){
	    return 580;
	}

	return 0;
	}

	void movemouse(int x, int y){
	inicializaCores();
	int i;
	//printf("y->%d pos->%d\n", y, posicaoCelulas[posicaoBlocos[4].posicao].y);
	 printf("x : %d Y:%d \n",x,y);
	for( i = 0; i<15;i++){
	    if((x>posicaoCelulas[posicaoBlocos[i].posicao].x+280)&&(x<posicaoCelulas[posicaoBlocos[i].posicao].x+280+90)&&(y>posicaoCelulas[posicaoBlocos[i].posicao].y+incrementoY(posicaoBlocos[i].posicao))&&(y<posicaoCelulas[posicaoBlocos[i].posicao].y+incrementoY(posicaoBlocos[i].posicao)+90)&&((posicaoVazio == posicaoBlocos[i].posicao-4)
	    ||(posicaoVazio == posicaoBlocos[i].posicao+4)
	    ||(posicaoVazio == posicaoBlocos[i].posicao+1)
	    ||(posicaoVazio == posicaoBlocos[i].posicao-1))){
	    corBlocos[i] = 1;
	}
	else if ((x>posicaoCelulas[posicaoBlocos[i].posicao].x+280)&&(x<posicaoCelulas[posicaoBlocos[i].posicao].x+280+90)&&(y>posicaoCelulas[posicaoBlocos[i].posicao].y+incrementoY(posicaoBlocos[i].posicao))&&(y<posicaoCelulas[posicaoBlocos[i].posicao].y+incrementoY(posicaoBlocos[i].posicao)+90))corBlocos[i]=2;


	}
	glutPostRedisplay();

	}
	void keyboard(unsigned char tecla, int x, int y){
    switch(tecla){
    	case 'R':
        case 'r':{
        		start=true;
        		tInicio=clock();
        		posicaoInicial(numPartidas);
        		break;
      }
    }
}
	GLuint loadBMP_custom( const char * filename, int width, int height )
	{

	  GLuint texture;

	  //int width, height;

	  unsigned char * data;

	  FILE * file;

	  file = fopen( filename, "rb" );

	  if ( file == NULL ) return 0;
	 // width = 512;
	 // height = 512;
	  data = (unsigned char *)malloc( width * height * 3 );
	  //int size = fseek(file,);
	  fread( data, width * height * 3, 1, file );
	  fclose( file );

	 for(int i = 0; i < width * height ; ++i)
	{
	   int index = i*3;
	   unsigned char B,R;
	   B = data[index];
	   R = data[index+2];

	   data[index] = R;
	   data[index+2] = B;

	}

	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST ); //EDITAR TEXTURA AQUI

	//glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_TEXTURE);
	//glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
	free( data );

	return texture;
	}
	void mouse(int button,int state,int x, int y){
	   // printf("%d %d \n", x, y);
		int i;
	    bool flag = false;
	    if(state==GLUT_DOWN && start==false){
	        for(i=0;i<15;i++){
	        //comparar se o mouse está em cima do bloco
	        if(corBlocos[i]==1){
		        if(posicaoVazio == (posicaoBlocos[i].posicao-4)){
	                  flag=true;
		        	  posicaoVazio=posicaoBlocos[i].posicao;
		        	  posicaoBlocos[i].posicao=posicaoBlocos[i].posicao-4;
		        	//  printf("Posicão Vaiza :%d , i=%d, Posicao Nova Bloco: %d \n",posicaoVazio,i,posicaoBlocos[i].posicao );
		        	  break;

		        }
		        else if(posicaoVazio == (posicaoBlocos[i].posicao+4)){
	                  flag=true;
		         	  posicaoVazio=posicaoBlocos[i].posicao;
		        	  posicaoBlocos[i].posicao=posicaoBlocos[i].posicao+4;
		        	  //printf("Posicão Vaiza :%d , i=%d, Posicao Nova Bloco: %d \n",posicaoVazio,i,posicaoBlocos[i].posicao );
		        	  break;

		        }
	  	       else if(posicaoVazio == (posicaoBlocos[i].posicao+1)){
	                    flag=true;
	  		 			posicaoVazio=posicaoBlocos[i].posicao;
	  		     		posicaoBlocos[i].posicao=posicaoBlocos[i].posicao+1;
	  		 // printf("Posicão Vaiza :%d , i=%d, Posicao Nova Bloco: %d \n",posicaoVazio,i,posicaoBlocos[i].posicao );
	  		  break;


	  		}
	  	   	  else if(posicaoVazio == posicaoBlocos[i].posicao-1){

			          flag=true;
			  	   	  posicaoVazio=posicaoBlocos[i].posicao;
			  	   	  posicaoBlocos[i].posicao=posicaoBlocos[i].posicao-1;
			  	   	 // printf("Posicão Vaiza :%d , i=%d, Posicao Nova Bloco: %d \n",posicaoVazio,i,posicaoBlocos[i].posicao );
			  	   	  break;


		   	}

	}
	}
		if(flag) {
			alSourcePlay(Sources[MOVERY]); //Som
			numJogadas++;
		}
		else alSourcePlay(Sources[MOVERN]); //Som
		}
	else if(state==GLUT_DOWN &&(x>276)&&(x<376)&& (y>299)&&(y<350)){
		start=false;
		tInicio=clock();
		alSourcePlay(Sources[START]);
	}
	  glutPostRedisplay();

	}

	void projecao(){
	    glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();

	    if(orto){
	        glOrtho(-win*aspecto, win*aspecto,-win,win,-win,win);
	    }else{
	        gluPerspective(angulo,aspecto,0.0f,100.0f);
	    }

	    glMatrixMode(GL_MODELVIEW);
	    glLoadIdentity();
	    //9.600000
	    gluLookAt(obsX,obsY,0,0.0,0.0,0.0,0.0,1.0,0.0);
	}

	void reshape(GLsizei w, GLsizei h)
	{
	  /*  if(h==0)
	        h=1;
	    glViewport(0,0,w,h);
	    aspecto=(float) w/h;
	    projecao();*/
	}

	void motion(int x, int y)
	{
	    if(bot==GLUT_LEFT_BUTTON){
	        int deltax=x_ini-x;
	        int deltay=y_ini -y;
	        rotY=rotY_ini - deltax/SENS_ROT;
	        rotX=rotX_ini- deltay/SENS_ROT;
	    }

	    else if(bot==GLUT_RIGHT_BUTTON){
	        int deltaz= y_ini-y;
	        obsZ=obsZ_ini + deltaz/SENS_OBS;

	    }

	    else if(bot==GLUT_MIDDLE_BUTTON)
	    {
	        int deltax=x_ini-x;
	        int deltay=y_ini-y;
	        obsX=obsX_ini +deltax/SENS_TRANSL;
	        obsY=obsY_ini-deltay/SENS_TRANSL;
	    }

	    //glMatrixMode(GL_MODELVIEW);
	    glLoadIdentity();
	    glTranslatef(-obsX,-obsY,-obsZ);
	    glRotatef(rotX,1,0,0);
	    glRotatef(rotY,0,1,0);
	    glutPostRedisplay();


	}

	void desenhaEixos(){
	    glLineWidth(2.0f);
	    glBegin(GL_LINES);
	        glColor3f(1.0f,0.0f,0.0f);
	        glVertex3f(0.0f,0.0f,0.0f);
	        glVertex3f(2.0f,0.0f,0.0f);


	        glColor3f(0.0f,1.0f,0.0f);
	        glVertex3f(0.0f,0.0f,0.0f);
	        glVertex3f(0.0f,2.0f,0.0f);

	        glColor3f(0.0f,0.0f,1.0f);
	        glVertex3f(0.0f,0.0f,0.0f);
	        glVertex3f(0.0f,0.0f,2.0f);
	    glEnd();

	}

	void desenhaBloco1 (){
	    botao1=glGenLists(1);

	    int i;
	    glPushMatrix();
	   //glColor3f( 0.0, 0.0, 0.0 );

	      glNewList(botao1, GL_COMPILE);
	       glPushMatrix();
	     glBegin(GL_QUADS);
	        glTexCoord2f(0, 1); glVertex3f(-40,40,0);
	        glTexCoord2f(1,1);  glVertex3f(40,40,0);
	       glTexCoord2f(1, 0); glVertex3f(40,-40,0);
	        glTexCoord2f(0, 0); glVertex3f(-40,-40,0);

	     glEnd();
	      glPopMatrix();

	 glEndList();
	}

	void desenhaTabuleiro1(){
	  tabuleiro1=glGenLists(2);
	  glNewList(tabuleiro1, GL_COMPILE);

	    // GLuint texture = loadBMP_custom("hard.bmp", 2048, 2048);
	        //glEnable(GL_TEXTURE_2D);

	   //  glColor3f( 1.0, 0.27, 0.07 );
	     glBegin(GL_QUADS);
	       glTexCoord2f(0, 1); glVertex3f(-250,250,0);
	       glTexCoord2f(1,1);  glVertex3f(250,250,0);
	       glTexCoord2f(1, 0);  glVertex3f(250,-250,0);
	       glTexCoord2f(0, 0); glVertex3f(-250,-250,0);
	     glEnd();
	    /// glDisable(GL_TEXTURE_2D);
	     glEndList();
	}

	void desenhaTabuleiro2(){
	 tabuleiro2=glGenLists(3);
	  glNewList(tabuleiro2, GL_COMPILE);

	    // glColor3f(1.0, 1, 1 );
	     glBegin(GL_QUADS);
	        glTexCoord2f(0, 1); glVertex3f(-200,200,0);
	        glTexCoord2f(1,1);  glVertex3f(200,200,0);
	       glTexCoord2f(1, 0); glVertex3f(200,-200,0);
	        glTexCoord2f(0, 0); glVertex3f(-200,-200,0);
	     glEnd();
	        glDisable(GL_TEXTURE_2D);
	glEndList();


	     //glutSwapBuffers();
	/*glBegin(GL_QUADS);
	    // front
	    glVertex3f(0.0f, 0.0f, 0.0f);
	    glVertex3f(1.0f, 0.0f, 0.0f);
	    glVertex3f(1.0f, 1.0f, 0.0f);
	    glVertex3f(0.0f, 1.0f, 0.0f);
	    // back
	    glVertex3f(0.0f, 0.0f, -1.0f);
	    glVertex3f(1.0f, 0.0f, -1.0f);
	    glVertex3f(1.0f, 1.0f, -1.0f);
	    glVertex3f(0.0f, 1.0f, -1.0f);
	    // right
	    glVertex3f(1.0f, 0.0f, 0.0f);
	    glVertex3f(1.0f, 0.0f, -1.0f);
	    glVertex3f(1.0f, 1.0f, -1.0f);
	    glVertex3f(1.0f, 1.0f, 0.0f);
	    // left
	    glVertex3f(0.0f, 0.0f, 0.0f);
	    glVertex3f(0.0f, 0.0f, -1.0f);
	    glVertex3f(0.0f, 1.0f, -1.0f);
	    glVertex3f(0.0f, 1.0f, 0.0f);
	    // top
	    glVertex3f(0.0f, 1.0f, 0.0f);
	    glVertex3f(1.0f, 1.0f, 0.0f);
	    glVertex3f(1.0f, 1.0f, -1.0f);
	    glVertex3f(0.0f, 1.0f, -1.0f);
	    // bottom
	    glVertex3f(0.0f, 0.0f, 0.0f);
	    glVertex3f(1.0f, 0.0f, 0.0f);
	    glVertex3f(1.0f, 0.0f, -1.0f);
	    glVertex3f(0.0f, 0.0f, -1.0f);
	glEnd();*/
	}
	void drawStrokeText(char*string,int x,int y,int z)
	{
	      char *c;
	      glPushMatrix();
	      glTranslatef(x, y+8,z);
	      glScalef(0.09f,-0.08f,z);

	      for (c=string; *c != '\0'; c++)
	      {
	            glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
	      }
	      glPopMatrix();
	}
	void desenhaVitoria(){
    		char vitoria[]="You Win!";
    		glPushMatrix();
    		glColor3f(0,1,0);
			glScalef(3.0f,3.00f,1);
			glRotatef(-180,1,0,0);
			glTranslatef(-30, -80, 1);
			drawStrokeText(vitoria,0,0,0);
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,151515);
			glPopMatrix();

    }
    void inicializa(){
    	glPushMatrix();
		glColor3f(0.62,0.5,0.39);
		glTranslatef(0,0,-250);
	 	glutSolidCube(500);
	 	glPopMatrix();

		glColor3f(0.6,0.6, 0.6);
		glEnable(GL_TEXTURE_2D);
	    glBindTexture( GL_TEXTURE_2D, texture);
	    glCallList(tabuleiro1);
	  	glDisable(GL_TEXTURE_2D);
	  	glPushMatrix();
		glColor3f(0.62,0.5,0.39);
	    glTranslatef(dx,dy,0);
	    glScalef(5,5,1);
	    glBegin( GL_POLYGON );
	        glVertex3f( -45, 45, 0.0 );
	        glVertex3f( 45,45, 0.0 );
	        glVertex3f( 45,-45,0.0 );
	        glVertex3f( -45, -45, 0.0 );
	    glEnd();
	  	glPopMatrix();
	  	glColor3f(0.45,0.27,0.07);
	  	char nome[]="Jogo dos Quinze!";
		glPushMatrix();
		glColor3f(0,0,0);
		glScalef(4.00f,4.00f,1);
		glRotatef(-180,1,0,0);
		glTranslatef(-55,-40, 1);
		drawStrokeText(nome,0,0,0);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,151515);
		glPopMatrix();
	  	glPushMatrix();
		glColor3f(0.62,0.5,0.39);
	    glTranslatef(dx,dy,0);
	    glScalef(5,5,1);
	    glBegin( GL_POLYGON );
	        glVertex3f( -10, 5, 0.0 );
	        glVertex3f( 10,5, 0.0 );
	        glVertex3f( 10,-5, 0.0 );
	        glVertex3f( -10,-5, 0.0 );
	    glEnd();
	  	glPopMatrix();
	  	char play[]="Play";
		glPushMatrix();
		glColor3f(0,0,0);
		glScalef(3.00f,3.00f,1);
		glRotatef(-180,1,0,0);
		glTranslatef(-10,-5, 1);
		drawStrokeText(play,0,0,0);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,151515);
		glPopMatrix();


		glutSwapBuffers();

	}
	void idle(){

	tFim = clock();
	/*calcula aproximadamente o tempo em milisegundos gasto entre as duas chamadas de clock()*/
	tDecorrido = ((tFim - tInicio) / (CLOCKS_PER_SEC / 1000));

	glutPostRedisplay();
	}

	void display( void )
	{
		if(start==true){
	    	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			inicializa();
		}

		else if(start==false){
	    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	    if(eixo){
	        glPushMatrix();
	            glScalef(ex, ey, ez);
	            desenhaEixos();
	        glPopMatrix();
	    }

	    glPushMatrix();
	        glTranslatef(tx, 0, 0);
	        glRotatef(ang, 0, 0, 1);
	        glScalef(ex, ey, ez);

	       // formas();
	    glPopMatrix();

	//Limpar todos os pixels
	  //  glClear( GL_COLOR_BUFFER_BIT );
	   // glMatrixMode(GL_MODELVIEW);
	    //glLoadIdentity();

	    /*******************DESENHO DOS OBJETOS*********************/

	glPushMatrix();
	//glColor3f(0.60,0.50,0.40);
	glColor3f(0.62,0.5,0.39);
	glTranslatef(0,0,-250);
	 glutSolidCube(500);
	 glPopMatrix();

	glColor3f(0.6,0.6, 0.6);
	glEnable(GL_TEXTURE_2D);
	     glBindTexture( GL_TEXTURE_2D, texture );
	    glCallList(tabuleiro1);
	  glDisable(GL_TEXTURE_2D);


	/*
	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, texture4 );
	    glCallList(tabuleiro2);
	      glDisable(GL_TEXTURE_2D);
	*/

	/*BLOCO 1*/
	      //glutStrokeString(GLUT_BITMAP_9_BY_15, "TESTE");

	   glPushMatrix();
	glTranslatef(posicaoCelulas[posicaoBlocos[0].posicao].x,posicaoCelulas[posicaoBlocos[0].posicao].y,0);
	if(corBlocos[0]==1){
	    glColor3f(0.0,1.0,0.0);
	}else if(corBlocos[0]==2){
	    glColor3f(1.0,0.0,0.0);
	//} else glColor3f(0.8039,0.7215,0.6588);
	 } else glColor3f(0.7039,0.6215,0.5588);

	 glutSolidCube(80);
	 glTranslatef(0,0,40);


	 //glColor3f(0.0,0.0,0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, textureB1 );
	glCallList(botao1);
	glDisable(GL_TEXTURE_2D);

	 glPopMatrix();




	/*BLOCO 2*/
	   glPushMatrix();
	glTranslatef(posicaoCelulas[posicaoBlocos[1].posicao].x,posicaoCelulas[posicaoBlocos[1].posicao].y,0);
	if(corBlocos[1]==1){
	    glColor3f(0.0,1.0,0.0);
	}else if (corBlocos[1]==2){
	    glColor3f(1.0,0.0,0.0);
	 } else glColor3f(0.7039,0.6215,0.5588);

	 glutSolidCube(80);
	 glTranslatef(0,0,40);

	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, textureB2 );
	glCallList(botao1);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	/*BLOCO 3*/
	   glPushMatrix();
	glTranslatef(posicaoCelulas[posicaoBlocos[2].posicao].x,posicaoCelulas[posicaoBlocos[2].posicao].y,0);

	if(corBlocos[2]==1){
	    glColor3f(0.0,1.0,0.0);
	}else if (corBlocos[2]==2){
	    glColor3f(1.0,0.0,0.0);
	 } else glColor3f(0.7039,0.6215,0.5588);

	glutSolidCube(80);
	  glTranslatef(0,0,40);


	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, textureB3 );
	glCallList(botao1);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	/*BLOCO 4*/
	   glPushMatrix();
	glTranslatef(posicaoCelulas[posicaoBlocos[3].posicao].x,posicaoCelulas[posicaoBlocos[3].posicao].y,0);

	if(corBlocos[3]==1){
	    glColor3f(0.0,1.0,0.0);
	}else if (corBlocos[3]==2){
	    glColor3f(1.0,0.0,0.0);
	 } else glColor3f(0.7039,0.6215,0.5588);

	 glutSolidCube(80);
	  glTranslatef(0,0,40);

	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, textureB4 );
	glCallList(botao1);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	/*BLOCO 5*/
	   glPushMatrix();
	glTranslatef(posicaoCelulas[posicaoBlocos[4].posicao].x,posicaoCelulas[posicaoBlocos[4].posicao].y,0);

	if(corBlocos[4]==1){
	    glColor3f(0.0,1.0,0.0);
	}else if (corBlocos[4]==2){
	    glColor3f(1.0,0.0,0.0);
	 } else glColor3f(0.7039,0.6215,0.5588);
	glutSolidCube(80);
	  glTranslatef(0,0,40);


	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, textureB5 );
	glCallList(botao1);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	/*BLOCO 6*/
	   glPushMatrix();
	glTranslatef(posicaoCelulas[posicaoBlocos[5].posicao].x,posicaoCelulas[posicaoBlocos[5].posicao].y,0);

	if(corBlocos[5]==1){
	    glColor3f(0.0,1.0,0.0);
	}else if (corBlocos[5]==2){
	    glColor3f(1.0,0.0,0.0);
	 } else glColor3f(0.7039,0.6215,0.5588);
	glutSolidCube(80);
	  glTranslatef(0,0,40);


	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, textureB6 );
	glCallList(botao1);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	/*BLOCO 7*/
	   glPushMatrix();
	glTranslatef(posicaoCelulas[posicaoBlocos[6].posicao].x,posicaoCelulas[posicaoBlocos[6].posicao].y,0);

	if(corBlocos[6]==1){
	    glColor3f(0.0,1.0,0.0);
	}else if (corBlocos[6]==2){
	    glColor3f(1.0,0.0,0.0);
	 } else glColor3f(0.7039,0.6215,0.5588);
	glutSolidCube(80);
	  glTranslatef(0,0,40);


	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, textureB7 );
	glCallList(botao1);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	/*BLOCO 8*/
	   glPushMatrix();
	glTranslatef(posicaoCelulas[posicaoBlocos[7].posicao].x,posicaoCelulas[posicaoBlocos[7].posicao].y,0);

	if(corBlocos[7]==1){
	    glColor3f(0.0,1.0,0.0);
	}else if (corBlocos[7]==2){
	    glColor3f(1.0,0.0,0.0);
	 } else glColor3f(0.7039,0.6215,0.5588);
	glutSolidCube(80);
	  glTranslatef(0,0,40);

	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, textureB8 );
	glCallList(botao1);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();



	/*BLOCO 9*/
	   glPushMatrix();
	glTranslatef(posicaoCelulas[posicaoBlocos[8].posicao].x,posicaoCelulas[posicaoBlocos[8].posicao].y,0);

	if(corBlocos[8]==1){
	    glColor3f(0.0,1.0,0.0);
	}else if (corBlocos[8]==2){
	    glColor3f(1.0,0.0,0.0);
	 } else glColor3f(0.7039,0.6215,0.5588);
	glutSolidCube(80);
	  glTranslatef(0,0,40);

	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, textureB9 );
	glCallList(botao1);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();



	/*BLOCO 10*/
	   glPushMatrix();
	glTranslatef(posicaoCelulas[posicaoBlocos[9].posicao].x,posicaoCelulas[posicaoBlocos[9].posicao].y,0);

	if(corBlocos[9]==1){
	    glColor3f(0.0,1.0,0.0);
	}else if (corBlocos[9]==2){
	    glColor3f(1.0,0.0,0.0);
	 } else glColor3f(0.7039,0.6215,0.5588);
	glutSolidCube(80);
	  glTranslatef(0,0,40);

	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, textureB10 );
	glCallList(botao1);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();



	/*BLOCO 11*/
	   glPushMatrix();
	glTranslatef(posicaoCelulas[posicaoBlocos[10].posicao].x,posicaoCelulas[posicaoBlocos[10].posicao].y,0);

	if(corBlocos[10]==1){
	    glColor3f(0.0,1.0,0.0);
	}else if (corBlocos[10]==2){
	    glColor3f(1.0,0.0,0.0);
	 } else glColor3f(0.7039,0.6215,0.5588);
	glutSolidCube(80);
	  glTranslatef(0,0,40);

	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, textureB11 );
	glCallList(botao1);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	/*BLOCO 12*/
	   glPushMatrix();
	glTranslatef(posicaoCelulas[posicaoBlocos[11].posicao].x,posicaoCelulas[posicaoBlocos[11].posicao].y,0);

	if(corBlocos[11]==1){
	    glColor3f(0.0,1.0,0.0);
	}else if (corBlocos[11]==2){
	    glColor3f(1.0,0.0,0.0);
	 } else glColor3f(0.7039,0.6215,0.5588);
	glutSolidCube(80);
	  glTranslatef(0,0,40);

	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, textureB12 );
	glCallList(botao1);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();



	/*BLOCO 13*/
	glPushMatrix();
	glTranslatef(posicaoCelulas[posicaoBlocos[12].posicao].x,posicaoCelulas[posicaoBlocos[12].posicao].y, 0);
	if(corBlocos[12]==1){
	    glColor3f(0.0,1.0,0.0);
	}else if (corBlocos[12]==2){
	    glColor3f(1.0,0.0,0.0);
	 } else glColor3f(0.7039,0.6215,0.5588);
	glutSolidCube(80);
	 glTranslatef(0,0,40);

	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, textureB13 );
	glCallList(botao1);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();



	/*BLOCO 14*/
	glPushMatrix();
	glTranslatef(posicaoCelulas[posicaoBlocos[13].posicao].x,posicaoCelulas[posicaoBlocos[13].posicao].y,0);

	if(corBlocos[13]==1){
	    glColor3f(0.0,1.0,0.0);
	}else if (corBlocos[13]==2){
	    glColor3f(1.0,0.0,0.0);
	 } else glColor3f(0.7039,0.6215,0.5588);
	glutSolidCube(80);
	  glTranslatef(0,0,40);

	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, textureB14 );
	glCallList(botao1);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();



	/*BLOCO 15*/
	   glPushMatrix();
	glTranslatef(posicaoCelulas[posicaoBlocos[14].posicao].x,posicaoCelulas[posicaoBlocos[14].posicao].y,0);

	if(corBlocos[14]==1){
	    glColor3f(0.0,1.0,0.0);
	}else if (corBlocos[14]==2){
	    glColor3f(1.0,0.0,0.0);
	 } else glColor3f(0.7039,0.6215,0.5588);
	glutSolidCube(80);
	  glTranslatef(0,0,40);

	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, textureB15 );
	glCallList(botao1);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();



	/*

	glEnable(GL_TEXTURE_2D);
	GLuint textureB34= loadBMP_custom("num3.bmp",2048,2048);
	glPushMatrix();

	    glCallList(botao1);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	*/
	/*********ESCREVER********/


	char string[100] ;
	sprintf(string, "%d Movimentos", numJogadas);

	glPushMatrix();

	glScalef(2.00f,2.00f,1);
	glRotatef(-180,1,0,0);
	glTranslatef(-150, -150, 1);
	glColor3f(0.7039,0.6215,0.5588);
	drawStrokeText(string,0,0,0);
	glPopMatrix();


	char milisegundos[100] ;
	char segundos[100] ;
	char minutos[100] ;
	char horas[100] ;



	sprintf(milisegundos, "%02d", tDecorrido%100);
	sprintf(segundos, "%02d", ((tDecorrido)/100)%60);
	if(((((tDecorrido)/100)%60) == 0)&&(tDecorrido%100==0))
	    {
	        minuto++;
	        minutoInicio = false;
	    }
	 if((minuto == 60))
	    {
	        hora++;
	        minuto =0;

	    }


	sprintf(minutos, "%02d", minuto);
	sprintf(horas, "%02d", hora);

	char tempo[100] ;
	strcat(tempo, horas);
	strcat(tempo, ":");
	strcat(tempo, minutos);
	strcat(tempo, ":");
	strcat(tempo, segundos);
	strcat(tempo, ":");
	strcat(tempo, milisegundos);



	//char tempo[] = "00:00:00:00";
	glPushMatrix();
	glColor3f(0.7039,0.6215,0.5588);
	glScalef(2.00f,2.00f,1);
	glRotatef(-180,1,0,0);
	glTranslatef(50, -150, 1);
	drawStrokeText(tempo,0,0,0);
	glPopMatrix();
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,151515);
	/***************************/
    if((posicaoBlocos[0].posicao==0)&&(posicaoBlocos[1].posicao==1)&&(posicaoBlocos[2].posicao==2)&&(posicaoBlocos[3].posicao==3)
    	&&(posicaoBlocos[4].posicao==4)&&(posicaoBlocos[5].posicao==5)&&(posicaoBlocos[6].posicao==6)&&(posicaoBlocos[7].posicao==7)
		&&(posicaoBlocos[8].posicao==8)&&(posicaoBlocos[9].posicao==9)&&(posicaoBlocos[10].posicao==10)&&(posicaoBlocos[11].posicao==11)
		&&(posicaoBlocos[12].posicao==12)&&(posicaoBlocos[13].posicao==13)&&(posicaoBlocos[14].posicao==14))
	{
		Venceu=true;
		//

		if(flagTempo<350 && Venceu==true){

			desenhaVitoria();
			if(flagTempo==10) alSourcePlay(Sources[VENCEU]);
			flagTempo++;
		}
		else{
			flagTempo=0;
			Venceu=false;
			numPartidas++;
			posicaoInicial(numPartidas);
			start=true;

		}


}
}
	glutSwapBuffers();


	}

	int main(int argc, char *argv[])
	{


	/*MUDE AQUI PARA AFETAR O ESTADO INICIAL DA CAIXA*/
	        x_ini = 611;
	        y_ini = 367;
	        obsX_ini = obsX;
	        obsY_ini = obsY;
	        obsZ_ini = 5.0;
	        rotX_ini = 80.60000;
	        rotY_ini = 115.0;



	    glutInit( &argc, argv );
	    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB );
	    glutInitWindowSize(650,650);
	    glutInitWindowPosition(250,250);
	    glutCreateWindow("Jogos dos 15");
		texture = loadBMP_custom("hard.bmp", 512, 512);
		textureInicial= loadBMP_custom("TelaInicial.bmp",256,256);
		init();
	 //texture4 = loadBMP_custom("hard1.bmp",512,512);

		 textureB1 = loadBMP_custom("bloco1.bmp",128,128);
		 textureB2= loadBMP_custom("bloco2.bmp",128,128);
		 textureB3= loadBMP_custom("bloco3.bmp",128,128);
		 textureB4= loadBMP_custom("bloco4.bmp",128,128);

		 textureB5 = loadBMP_custom("bloco5.bmp",128,128);
		 textureB6= loadBMP_custom("bloco6.bmp",128,128);
		 textureB7= loadBMP_custom("bloco7.bmp",128,128);
		 textureB8= loadBMP_custom("bloco8.bmp",128,128);

		 textureB9 = loadBMP_custom("bloco9.bmp",128,128);
		 textureB10= loadBMP_custom("bloco10.bmp",128,128);
		 textureB11= loadBMP_custom("bloco11.bmp",128,128);
		 textureB12= loadBMP_custom("bloco12.bmp",128,128);

		 textureB13 = loadBMP_custom("bloco13.bmp",128,128);
		 textureB14= loadBMP_custom("bloco14.bmp",128,128);
		 textureB15= loadBMP_custom("bloco15.bmp",128,128);



		inicializaPosicaoCelulas();
	   	inicializaCores();
	   	int numb=1;
	   	posicaoInicial(numb);



	// Initialize OpenAL and clear the error bit.
	    alutInit(NULL, 0);
	    alGetError();

	    // Load the wav data.
	    if(LoadALData() == AL_FALSE) return 0;

	    SetListenerValues();

	//alSourcePlay(Sources[START]); //SOM DE START





	    desenhaTabuleiro1();
	    desenhaBloco1 ();


	    glutDisplayFunc( display);
	    glutReshapeFunc(reshape);
	    glutKeyboardFunc(keyboard);
	    glutMouseFunc(mouse);
	    glutPassiveMotionFunc(movemouse);
	    glutIdleFunc(idle);
		  motion(0,0);

	    //glutMotionFunc(motion); //FUNÇÃO DE GIRAR


	    glutMainLoop();

	    return 0;
	}